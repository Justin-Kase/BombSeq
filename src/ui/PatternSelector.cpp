#include "PatternSelector.h"

PatternSelector::PatternSelector(PatternBank& bank) : patternBank(bank) {}

void PatternSelector::paint(juce::Graphics& g) {
    const int current = patternBank.getCurrentIndex();
    
    for (int i = 0; i < 16; ++i) {
        const auto& bounds = buttonBounds[i];
        const bool isActive = (i == current);
        
        juce::Colour fillColour = isActive ? juce::Colour(0xFFD63031) : juce::Colour(0xFF3A3A3A);
        
        g.setColour(fillColour);
        g.fillRoundedRectangle(bounds.toFloat().reduced(1.0f), 2.0f);
        
        g.setColour(juce::Colour(0xFF2A2A2A));
        g.drawRoundedRectangle(bounds.toFloat().reduced(1.0f), 2.0f, 1.0f);
        
        g.setColour(juce::Colours::white);
        g.drawText(juce::String(i + 1), bounds, juce::Justification::centred);
    }
}

void PatternSelector::resized() {
    const int padding = 4;
    const int buttonWidth = (getWidth() - padding * 17) / 16;
    const int buttonHeight = getHeight() - padding * 2;
    
    for (int i = 0; i < 16; ++i) {
        const int x = padding + i * (buttonWidth + padding);
        buttonBounds[i] = juce::Rectangle<int>(x, padding, buttonWidth, buttonHeight);
    }
}

void PatternSelector::mouseDown(const juce::MouseEvent& e) {
    for (int i = 0; i < 16; ++i) {
        if (buttonBounds[i].contains(e.getPosition())) {
            patternBank.setCurrentIndex(i);
            repaint();
            break;
        }
    }
}
