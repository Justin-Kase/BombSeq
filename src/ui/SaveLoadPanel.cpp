#include "SaveLoadPanel.h"

SaveLoadPanel::SaveLoadPanel(PatternBank& bank) : patternBank(bank) {}

void SaveLoadPanel::paint(juce::Graphics& g) {
    g.setColour(juce::Colour(0xFF2A2A2A));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);
    
    // Header
    g.setColour(juce::Colour(0xFF888888));
    g.setFont(10.0f);
    g.drawText("USER BANK", getLocalBounds().removeFromTop(15), juce::Justification::centred);
    
    // SAVE label
    g.setColour(juce::Colours::white);
    g.setFont(9.0f);
    g.drawText("SAVE", 10, 20, 40, 15, juce::Justification::centredLeft);
    
    // LOAD label
    g.drawText("LOAD", 10, 70, 40, 15, juce::Justification::centredLeft);
    
    // Draw save slots (1-8)
    for (int i = 0; i < 8; ++i) {
        const auto& bounds = saveSlotBounds[i];
        bool occupied = patternBank.isUserSlotOccupied(i);
        
        g.setColour(occupied ? juce::Colour(0xFFFF8C00) : juce::Colour(0xFF3A3A3A));
        g.fillRoundedRectangle(bounds.toFloat(), 2.0f);
        
        g.setColour(juce::Colour(0xFF2A2A2A));
        g.drawRoundedRectangle(bounds.toFloat(), 2.0f, 1.0f);
        
        g.setColour(juce::Colours::white);
        g.setFont(11.0f);
        g.drawText(juce::String(i + 1), bounds, juce::Justification::centred);
    }
    
    // Draw load slots (1-8)
    for (int i = 0; i < 8; ++i) {
        const auto& bounds = loadSlotBounds[i];
        bool occupied = patternBank.isUserSlotOccupied(i);
        
        g.setColour(occupied ? juce::Colour(0xFFD63031) : juce::Colour(0xFF3A3A3A));
        g.fillRoundedRectangle(bounds.toFloat(), 2.0f);
        
        g.setColour(juce::Colour(0xFF2A2A2A));
        g.drawRoundedRectangle(bounds.toFloat(), 2.0f, 1.0f);
        
        g.setColour(juce::Colours::white);
        g.setFont(11.0f);
        g.drawText(juce::String(i + 1), bounds, juce::Justification::centred);
    }
}

void SaveLoadPanel::resized() {
    const int padding = 4;
    const int labelWidth = 45;
    const int buttonWidth = 30;
    const int buttonHeight = 30;
    
    // Save slots row
    int x = labelWidth + padding;
    int y = 20;
    for (int i = 0; i < 8; ++i) {
        saveSlotBounds[i] = juce::Rectangle<int>(x, y, buttonWidth, buttonHeight);
        x += buttonWidth + padding;
    }
    
    // Load slots row
    x = labelWidth + padding;
    y = 70;
    for (int i = 0; i < 8; ++i) {
        loadSlotBounds[i] = juce::Rectangle<int>(x, y, buttonWidth, buttonHeight);
        x += buttonWidth + padding;
    }
}

void SaveLoadPanel::mouseDown(const juce::MouseEvent& e) {
    // Check save slots
    for (int i = 0; i < 8; ++i) {
        if (saveSlotBounds[i].contains(e.getPosition())) {
            if (patternBank.isUserSlotOccupied(i)) {
                // Slot occupied: clear it
                patternBank.clearUserSlot(i);
            } else {
                // Slot empty: save to it
                patternBank.saveToUserSlot(i);
            }
            repaint();
            return;
        }
    }
    
    // Check load slots
    for (int i = 0; i < 8; ++i) {
        if (loadSlotBounds[i].contains(e.getPosition())) {
            patternBank.loadFromUserSlot(i);
            repaint();
            return;
        }
    }
}
