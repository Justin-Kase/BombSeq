#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "engine/PatternBank.h"
#include <functional>

class StepGrid : public juce::Component, public juce::Timer {
public:
    explicit StepGrid(PatternBank& bank);

    void paint(juce::Graphics&) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent&) override;
    void timerCallback() override;

    void setCurrentStep(int step) { playingStep = step; }
    void setSelectedStep(int step) { selectedStep = juce::jlimit(0, 63, step); repaint(); }
    int  getSelectedStep() const   { return selectedStep; }

    std::function<void(int)> onStepSelected;

private:
    PatternBank& patternBank;
    int playingStep  = -1;
    int selectedStep = 0;
    float pulsePhase = 0.0f;

    static constexpr int gridSize = 8;
    std::array<juce::Rectangle<int>, 64> stepBounds;
};
