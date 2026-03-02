#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "engine/PatternBank.h"

class StepEditor : public juce::Component {
public:
    explicit StepEditor(PatternBank& bank);
    
    void paint(juce::Graphics&) override;
    void resized() override;
    void setSelectedStep(int step);

private:
    PatternBank& patternBank;
    int selectedStep = 0;
    
    juce::Slider noteSlider, velocitySlider, gateSlider, probabilitySlider;
    juce::Label noteLabel, velocityLabel, gateLabel, probabilityLabel;
};
