#include "TransportBar.h"

TransportBar::TransportBar(juce::AudioProcessorValueTreeState& vts) : apvts(vts) {
    bpmSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    bpmSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(bpmSlider);
    
    bpmLabel.setText("120.0", juce::dontSendNotification);
    bpmLabel.setJustificationType(juce::Justification::centred);
    bpmLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), 24.0f, juce::Font::bold));
    addAndMakeVisible(bpmLabel);
    
    playButton.setClickingTogglesState(true);
    addAndMakeVisible(playButton);
    
    bpmAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "bpm", bpmSlider);
    playAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "playing", playButton);
    
    bpmSlider.onValueChange = [this] {
        bpmLabel.setText(juce::String(bpmSlider.getValue(), 1), juce::dontSendNotification);
    };
}

void TransportBar::paint(juce::Graphics& g) {
    g.setColour(juce::Colour(0xFF2A2A2A));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);
}

void TransportBar::resized() {
    auto area = getLocalBounds().reduced(10);
    
    bpmLabel.setBounds(area.removeFromLeft(120));
    area.removeFromLeft(10);
    
    bpmSlider.setBounds(area.removeFromLeft(300).withSizeKeepingCentre(300, 30));
    area.removeFromLeft(10);
    
    playButton.setBounds(area.removeFromLeft(80).withSizeKeepingCentre(80, 40));
}
