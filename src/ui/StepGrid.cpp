#include "StepGrid.h"

StepGrid::StepGrid(PatternBank& bank) : patternBank(bank) {
    startTimerHz(30);
}

void StepGrid::paint(juce::Graphics& g) {
    const auto& pattern = patternBank.currentPattern();
    
    const int patternLength = pattern.getNumSteps();
    
    for (int i = 0; i < 64; ++i) {
        const auto& bounds = stepBounds[i];
        const auto& step = pattern.stepAt(i);
        
        bool isOutsidePattern = (i >= patternLength);
        bool isPlaying = (i == playingStep);
        bool isSelected = (i == selectedStep);
        juce::Colour padColour;
        
        if (isOutsidePattern) {
            // Grey out steps beyond pattern length
            padColour = juce::Colour(0xFF4A4A4A).darker(0.3f); // Dark grey
        } else if (isPlaying) {
            const float brightness = 0.7f + 0.3f * std::sin(pulsePhase);
            padColour = juce::Colour(0xFFFFAA00).withBrightness(brightness); // Amber pulse
        } else if (step.active) {
            padColour = juce::Colour(0xFFCC2020); // Red active
        } else {
            padColour = juce::Colour(0xFF7A7672); // Grey rubber pad
        }
        
        // MPC60-style rubber pad rendering
        auto padBounds = bounds.toFloat().reduced(3.0f);
        
        // Main pad fill
        g.setColour(padColour);
        g.fillRoundedRectangle(padBounds, 4.0f);
        
        // Rubber texture (subtle gradient) - skip for outside-pattern steps
        if (!isOutsidePattern) {
            g.setGradientFill(juce::ColourGradient(
                padColour.brighter(0.15f), padBounds.getX(), padBounds.getY(),
                padColour.darker(0.15f), padBounds.getRight(), padBounds.getBottom(), false));
            g.fillRoundedRectangle(padBounds, 4.0f);
            
            // Raised edge highlight (top-left)
            g.setColour(padColour.brighter(0.3f));
            juce::Path topLeft;
            topLeft.addRoundedRectangle(padBounds, 4.0f);
            g.strokePath(topLeft, juce::PathStrokeType(1.5f));
            
            // Shadow (bottom-right)
            g.setColour(padColour.darker(0.4f));
            g.drawRoundedRectangle(padBounds.translated(1, 1), 4.0f, 1.0f);
        }
        
        // Selected step gets bright border
        if (isSelected && !isOutsidePattern) {
            g.setColour(juce::Colour(0xFFFFAA00)); // Amber selection
            g.drawRoundedRectangle(padBounds, 4.0f, 3.0f);
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
