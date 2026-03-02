#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "engine/SequencerEngine.h"
#include "engine/PatternBank.h"

class BombSeqAudioProcessor : public juce::AudioProcessor {
public:
    BombSeqAudioProcessor();
    ~BombSeqAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "BombSeq"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return true; }
    bool isMidiEffect() const override { return true; }
    
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& getAPVTS() { return apvts; }
    PatternBank& getPatternBank() { return patternBank; }
    SequencerEngine& getEngine() { return engine; }

private:
    juce::AudioProcessorValueTreeState apvts;
    PatternBank patternBank;
    SequencerEngine engine;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BombSeqAudioProcessor)
};
