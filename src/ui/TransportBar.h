#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

class TransportBar : public juce::Component {
public:
    explicit TransportBar(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& apvts;
    
    juce::Slider bpmSlider;
    juce::Label bpmLabel;
    juce::TextButton playButton{"Play"};
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bpmAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> playAttachment;
};
