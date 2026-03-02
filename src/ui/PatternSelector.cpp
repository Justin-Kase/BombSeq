#include "PatternSelector.h"

PatternSelector::PatternSelector(PatternBank& bank) : patternBank(bank) {
    // Pattern length slider
    lengthSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    lengthSlider.setRange(1, 64, 1);
    lengthSlider.setValue(patternBank.currentPattern().getNumSteps());
    lengthSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 20);
    lengthSlider.onValueChange = [this] {
        patternBank.currentPattern().setLength(static_cast<int>(lengthSlider.getValue()));
    };
    addAndMakeVisible(lengthSlider);
    
    lengthLabel.setText("LENGTH", juce::dontSendNotification);
    lengthLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFFFAA00));
    lengthLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    lengthLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(lengthLabel);
}

void PatternSelector::paint(juce::Graphics& g) {
    // Sync slider with current pattern length
    lengthSlider.setValue(patternBank.currentPattern().getNumSteps(), juce::dontSendNotification);
    
    // Header label
    g.setColour(juce::Colour(0xFF888888));
    g.setFont(10.0f);
    g.drawText("PATTERN", getLocalBounds().removeFromTop(15), juce::Justification::centred);
    
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
    auto area = getLocalBounds();
    area.removeFromTop(15); // Header space
    
    // Pattern buttons (left 2/3)
    auto buttonArea = area.removeFromLeft(area.getWidth() * 2 / 3);
    
    const int padding = 4;
    const int buttonWidth = (buttonArea.getWidth() - padding * 17) / 16;
    const int buttonHeight = buttonArea.getHeight() - padding * 2;
    
    for (int i = 0; i < 16; ++i) {
        const int x = padding + i * (buttonWidth + padding);
        buttonBounds[i] = juce::Rectangle<int>(x, buttonArea.getY() + padding, buttonWidth, buttonHeight);
    }
    
    // Length control (right 1/3)
    auto lengthArea = area.reduced(10, 8);
    lengthLabel.setBounds(lengthArea.removeFromTop(18));
    lengthSlider.setBounds(lengthArea);
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
