#include "SequencerEngine.h"
#include <random>

SequencerEngine::SequencerEngine() {}

void SequencerEngine::prepare(double sr, int maxBlockSize) {
    sampleRate = sr;
    noteOffQueue.reserve(128);
}

void SequencerEngine::reset() {
    currentStep = -1;
    noteOffQueue.clear();
}

void SequencerEngine::processBlock(juce::MidiBuffer& midiOut, int numSamples, const juce::AudioPlayHead::PositionInfo& posInfo) {
    processNoteOffs(midiOut, numSamples);
    
    if (!isPlaying || !patternBank || !posInfo.getIsPlaying()) {
        currentStep = -1;
        return;
    }
    
    advanceSequencer(midiOut, numSamples, posInfo);
}

void SequencerEngine::processNoteOffs(juce::MidiBuffer& midiOut, int numSamples) {
    auto it = noteOffQueue.begin();
    while (it != noteOffQueue.end()) {
        if (it->sampleOffset < numSamples) {
            midiOut.addEvent(juce::MidiMessage::noteOff(it->channel, it->noteNumber), it->sampleOffset);
            it = noteOffQueue.erase(it);
        } else {
            it->sampleOffset -= numSamples;
            ++it;
        }
    }
}

void SequencerEngine::advanceSequencer(juce::MidiBuffer& midiOut, int numSamples, const juce::AudioPlayHead::PositionInfo& posInfo) {
    auto& pattern = patternBank->currentPattern();
    const int numSteps = pattern.getNumSteps();
    
    const double bpm = posInfo.getBpm().orFallback(currentBPM);
    const double ppqPos = posInfo.getPpqPosition().orFallback(0.0);
    const double ppqPerQN = 1.0;
    const double ppqPerBar = ppqPerQN * 4.0;
    
    // Determine grid division
    double ppqPerStep;
    switch (pattern.getSwingGrid()) {
        case Pattern::SwingGrid::Eighth:   ppqPerStep = ppqPerQN / 2.0; break;
        case Pattern::SwingGrid::Triplet:  ppqPerStep = ppqPerQN / 3.0; break;
        default:                           ppqPerStep = ppqPerQN / 4.0; break;
    }
    
    const double patternLengthPPQ = numSteps * ppqPerStep;
    const double samplesPerQN = sampleRate * 60.0 / bpm;
    
    const double bufferStartPPQ = ppqPos;
    const double bufferEndPPQ = ppqPos + (numSamples / samplesPerQN);
    
    // Find pattern-relative position
    const double ppqInPattern = std::fmod(ppqPos, patternLengthPPQ);
    if (ppqInPattern < 0.0) return;
    
    const int baseStep = static_cast<int>(ppqInPattern / ppqPerStep);
    
    // Check if we cross into next step(s) during this buffer
    for (int step = baseStep; step < numSteps; ++step) {
        double stepPPQ = step * ppqPerStep;
        
        // Apply swing
        const float swingOffset = calculateSwingOffset(pattern, step);
        stepPPQ += swingOffset * ppqPerStep;
        
        // Wrap to pattern start
        const double absoluteStepPPQ = std::floor(ppqPos / patternLengthPPQ) * patternLengthPPQ + stepPPQ;
        
        if (absoluteStepPPQ < bufferStartPPQ || absoluteStepPPQ >= bufferEndPPQ) {
            continue;
        }
        
        const auto& stepData = pattern.stepAt(step);
        if (!stepData.active) continue;
        
        // Probability check
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        if (dist(gen) > stepData.probability) continue;
        
        // Calculate sample offset
        const double offsetPPQ = absoluteStepPPQ - bufferStartPPQ + stepData.microTiming * ppqPerStep;
        int sampleOffset = static_cast<int>(offsetPPQ * samplesPerQN);
        sampleOffset = juce::jlimit(0, numSamples - 1, sampleOffset);
        
        // Ratchet (retriggering)
        const int ratchets = juce::jlimit(1, 8, stepData.ratchet);
        const double ratchetInterval = ppqPerStep / ratchets;
        
        for (int r = 0; r < ratchets; ++r) {
            const double ratchetPPQ = offsetPPQ + r * ratchetInterval;
            const int ratchetSample = static_cast<int>(ratchetPPQ * samplesPerQN);
            
            if (ratchetSample >= numSamples) break;
            
            const int finalSample = juce::jlimit(0, numSamples - 1, ratchetSample);
            const int noteNum = juce::jlimit(0, 127, static_cast<int>(stepData.note));
            const int vel = juce::jlimit(1, 127, static_cast<int>(stepData.velocity));
            
            midiOut.addEvent(juce::MidiMessage::noteOn(1, noteNum, (juce::uint8)vel), finalSample);
            
            // Schedule note-off
            const int gateSamples = static_cast<int>(stepData.gate * ppqPerStep * samplesPerQN);
            const int noteOffSample = finalSample + gateSamples;
            
            if (noteOffSample < numSamples) {
                midiOut.addEvent(juce::MidiMessage::noteOff(1, noteNum), noteOffSample);
            } else {
                noteOffQueue.push_back({noteOffSample - numSamples, noteNum, 1});
            }
        }
        
        currentStep = step;
    }
}

float SequencerEngine::calculateSwingOffset(const Pattern& pattern, int stepIndex) const {
    const float swingAmount = pattern.getSwingAmount();
    if (swingAmount <= 0.5f) return 0.0f;
    
    // MPC-style: delay the "odd" step in each pair
    const bool isOddInPair = (stepIndex % 2) == 1;
    if (!isOddInPair) return 0.0f;
    
    // Map 0.5-1.0 → 0.0-1.0 swing ratio
    return (swingAmount - 0.5f) * 2.0f;
}
