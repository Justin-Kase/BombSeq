#include "TransportBar.h"

TransportBar::TransportBar(juce::AudioProcessorValueTreeState& vts) : apvts(vts) {
    // BPM label above slider
    bpmHeaderLabel.setText("BPM", juce::dontSendNotification);
    bpmHeaderLabel.setJustificationType(juce::Justification::centred);
    bpmHeaderLabel.setFont(juce::Font(10.0f));
    bpmHeaderLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF888888));
    addAndMakeVisible(bpmHeaderLabel);
    
    bpmSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    bpmSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(bpmSlider);
    
    bpmLabel.setText("120.0", juce::dontSendNotification);
    bpmLabel.setJustificationType(juce::Justification::centred);
    bpmLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), 24.0f, juce::Font::bold));
    bpmLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF00FF00)); // Green LCD
    addAndMakeVisible(bpmLabel);
    
    playButton.setClickingTogglesState(true);
    addAndMakeVisible(playButton);
    
    bpmAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "bpm", bpmSlider);
    playAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "playing", playButton);
    
    bpmSlider.onValueChange = [this] {
        bpmLabel.setText(juce::String(bpmSlider.getValue(), 1) + " BPM", juce::dontSendNotification);
    };
    bpmSlider.onValueChange(); // Initialize label
}

void TransportBar::paint(juce::Graphics& g) {
    g.setColour(juce::Colour(0xFF2A2A2A));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);
}

void TransportBar::resized() {
    auto area = getLocalBounds().reduced(10);
    
    auto bpmArea = area.removeFromLeft(120);
    bpmHeaderLabel.setBounds(bpmArea.removeFromTop(15));
    bpmLabel.setBounds(bpmArea);
    
    area.removeFromLeft(10);
    
    bpmSlider.setBounds(area.removeFromLeft(300).withSizeKeepingCentre(300, 30));
    area.removeFromLeft(10);
    
    playButton.setBounds(area.removeFromLeft(80).withSizeKeepingCentre(80, 40));
}
