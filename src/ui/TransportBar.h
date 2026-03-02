#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

class BombSeqAudioProcessor; // Forward declaration

class TransportBar : public juce::Component, private juce::Timer {
public:
    explicit TransportBar(BombSeqAudioProcessor& proc);
    
    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    BombSeqAudioProcessor& processor;
    juce::AudioProcessorValueTreeState& apvts;
    
    juce::Label bpmDisplay;
    juce::Label bpmHeaderLabel;
    juce::TextButton playButton{"Play"};
    juce::Image logoImage;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> playAttachment;
};
