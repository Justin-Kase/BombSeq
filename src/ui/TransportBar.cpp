#include "TransportBar.h"
#include "../PluginProcessor.h"
#include <BinaryData.h>

TransportBar::TransportBar(BombSeqAudioProcessor& proc) 
    : processor(proc), apvts(proc.getAPVTS()) {
    
    // Load logo from binary resources
    int logoDataSize = 0;
    auto logoData = BinaryData::getNamedResource("logo_png", logoDataSize);
    if (logoData != nullptr && logoDataSize > 0) {
        logoImage = juce::ImageFileFormat::loadFrom(logoData, logoDataSize);
    }
    
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
    // Black background for entire transport bar
    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);
    
    // Draw "BombSeq" title with effects
    auto titleArea = getLocalBounds().reduced(10);
    titleArea.removeFromLeft(320); // Skip BPM + Play button area
    
    juce::String titleText = "BombSeq";
    juce::Font titleFont(juce::FontOptions("Impact", 28.0f, juce::Font::bold));
    g.setFont(titleFont);
    
    // Shadow
    g.setColour(juce::Colours::black.withAlpha(0.6f));
    g.drawText(titleText, titleArea.translated(2, 2), juce::Justification::centredLeft);
    
    // Gradient text (red to amber)
    auto textBounds = titleArea.toFloat();
    g.setGradientFill(juce::ColourGradient(
        juce::Colour(0xFFCC0000), textBounds.getX(), textBounds.getY(),
        juce::Colour(0xFFFFAA00), textBounds.getX(), textBounds.getBottom(), false));
    g.drawText(titleText, titleArea, juce::Justification::centredLeft);
    
    // Draw logo on far right
    if (logoImage.isValid()) {
        const int logoSize = 40;
        const int logoPadding = 10;
        const int logoX = getWidth() - logoSize - logoPadding;
        const int logoY = (getHeight() - logoSize) / 2;
        
        g.drawImage(logoImage, logoX, logoY, logoSize, logoSize,
                   0, 0, logoImage.getWidth(), logoImage.getHeight());
    }
}

void TransportBar::resized() {
    auto area = getLocalBounds().reduced(10);
    
    // BPM section on left
    auto bpmArea = area.removeFromLeft(200);
    bpmHeaderLabel.setBounds(bpmArea.removeFromTop(15));
    
    // LCD bezel around BPM display
    auto lcdBezel = bpmArea.reduced(2);
    bpmDisplay.setBounds(lcdBezel);
    
    // Play button
    area.removeFromLeft(10);
    playButton.setBounds(area.removeFromLeft(100).reduced(0, 5));
    
    // Title and logo drawn in paint()
}

void TransportBar::timerCallback() {
    double bpm = processor.getCurrentBPM();
    bpmDisplay.setText(juce::String(static_cast<int>(bpm + 0.5)) + " BPM", 
                      juce::dontSendNotification);
}
