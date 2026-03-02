#pragma once

#include "PatternBank.h"
#include <juce_audio_processors/juce_audio_processors.h>

class SequencerEngine {
public:
    SequencerEngine();
    
    void prepare(double sampleRate, int maxBlockSize);
    void reset();
    void processBlock(juce::MidiBuffer& midiOut, int numSamples, const juce::AudioPlayHead::PositionInfo& posInfo);
    
    void setPatternBank(PatternBank* bank) { patternBank = bank; }
    void setBPM(double bpm) { currentBPM = bpm; }
    void setPlaying(bool shouldPlay) { isPlaying = shouldPlay; }
    
    int getCurrentStep() const { return currentStep.load(); }
    
private:
    struct NoteOff {
        int sampleOffset;
        int noteNumber;
        int channel;
    };
    
    PatternBank* patternBank = nullptr;
    double sampleRate = 44100.0;
    double currentBPM = 120.0;
    bool isPlaying = false;
    
    std::atomic<int> currentStep{-1};
    std::vector<NoteOff> noteOffQueue;
    
    void processNoteOffs(juce::MidiBuffer& midiOut, int numSamples);
    void advanceSequencer(juce::MidiBuffer& midiOut, int numSamples, const juce::AudioPlayHead::PositionInfo& posInfo);
    float calculateSwingOffset(const Pattern& pattern, int stepIndex) const;
};
