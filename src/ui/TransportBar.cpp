#include "TransportBar.h"
#include "../PluginProcessor.h"

TransportBar::TransportBar(BombSeqAudioProcessor& proc) 
    : processor(proc), apvts(proc.getAPVTS()) {
    
    // BPM header label
    bpmHeaderLabel.setText("BPM", juce::dontSendNotification);
    bpmHeaderLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF888888));
    bpmHeaderLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    bpmHeaderLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(bpmHeaderLabel);
    
    // BPM display (read-only, shows host tempo)
    bpmDisplay.setColour(juce::Label::textColourId, juce::Colour(0xFFFFAA00)); // Amber
    bpmDisplay.setColour(juce::Label::backgroundColourId, juce::Colour(0xFF2A3525)); // LCD background
    bpmDisplay.setFont(juce::Font(18.0f, juce::Font::bold));
    bpmDisplay.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(bpmDisplay);
    
    playButton.setClickingTogglesState(true);
    addAndMakeVisible(playButton);
    
    playAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, "playing", playButton);
    
    startTimerHz(10); // Update BPM display frequently
}

void TransportBar::paint(juce::Graphics& g) {
    // Dark panel background
    g.setColour(juce::Colour(0xFF3A3838));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);
}

void TransportBar::resized() {
    auto area = getLocalBounds().reduced(10);
    
    // BPM section on left
    auto bpmArea = area.removeFromLeft(200);
    bpmHeaderLabel.setBounds(bpmArea.removeFromTop(15));
    
    // LCD bezel around BPM display
    auto lcdBezel = bpmArea.reduced(2);
    bpmDisplay.setBounds(lcdBezel);
    
    // Play button on right
    area.removeFromLeft(10);
    playButton.setBounds(area.removeFromLeft(100).reduced(0, 5));
}

void TransportBar::timerCallback() {
    double bpm = processor.getCurrentBPM();
    bpmDisplay.setText(juce::String(static_cast<int>(bpm + 0.5)) + " BPM", 
                      juce::dontSendNotification);
}
