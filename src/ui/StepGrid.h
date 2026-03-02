#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "engine/PatternBank.h"

class StepGrid : public juce::Component, public juce::Timer {
public:
    explicit StepGrid(PatternBank& bank);
    
    void paint(juce::Graphics&) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent&) override;
    void timerCallback() override;
    
    void setCurrentStep(int step) { playingStep = step; }

private:
    PatternBank& patternBank;
    int playingStep = -1;
    float pulsePhase = 0.0f;
    
    static constexpr int gridSize = 8;
    std::array<juce::Rectangle<int>, 64> stepBounds;
};
