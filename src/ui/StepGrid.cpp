#include "StepGrid.h"

StepGrid::StepGrid(PatternBank& bank) : patternBank(bank) {
    startTimerHz(30);
}

void StepGrid::paint(juce::Graphics& g) {
    const auto& pattern = patternBank.currentPattern();
    
    for (int i = 0; i < 64; ++i) {
        const auto& bounds = stepBounds[i];
        const auto& step = pattern.stepAt(i);
        
        bool isPlaying = (i == playingStep);
        bool isSelected = (i == selectedStep);
        juce::Colour fillColour;
        
        if (isPlaying) {
            const float brightness = 0.7f + 0.3f * std::sin(pulsePhase);
            fillColour = juce::Colour(0xFFFF8C00).withBrightness(brightness);
        } else if (step.active) {
            fillColour = juce::Colour(0xFFD63031);
        } else {
            fillColour = juce::Colour(0xFF3A3A3A);
        }
        
        g.setColour(fillColour);
        g.fillRoundedRectangle(bounds.toFloat().reduced(2.0f), 2.0f);
        
        // Selected step gets white border
        if (isSelected) {
            g.setColour(juce::Colours::white);
            g.drawRoundedRectangle(bounds.toFloat().reduced(2.0f), 2.0f, 2.0f);
        } else {
            g.setColour(juce::Colour(0xFF2A2A2A));
            g.drawRoundedRectangle(bounds.toFloat().reduced(2.0f), 2.0f, 1.0f);
        }
    }
}

void StepGrid::resized() {
    const int padding = 4;
    const int buttonSize = (getWidth() - padding * (gridSize + 1)) / gridSize;
    
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            const int idx = row * gridSize + col;
            const int x = padding + col * (buttonSize + padding);
            const int y = padding + row * (buttonSize + padding);
            stepBounds[idx] = juce::Rectangle<int>(x, y, buttonSize, buttonSize);
        }
    }
}

void StepGrid::mouseDown(const juce::MouseEvent& e) {
    for (int i = 0; i < 64; ++i) {
        if (stepBounds[i].contains(e.getPosition())) {
            // Right-click or shift-click toggles active/inactive
            if (e.mods.isRightButtonDown() || e.mods.isShiftDown()) {
                auto& step = patternBank.currentPattern().stepAt(i);
                step.active = !step.active;
            } else {
                // Left-click selects the step
                selectedStep = i;
                if (onStepSelected)
                    onStepSelected(i);
            }
            repaint();
            break;
        }
    }
}

void StepGrid::timerCallback() {
    pulsePhase += 0.15f;
    if (pulsePhase > juce::MathConstants<float>::twoPi)
        pulsePhase -= juce::MathConstants<float>::twoPi;
    repaint();
}
