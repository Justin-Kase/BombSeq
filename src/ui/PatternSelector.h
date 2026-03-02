#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "engine/PatternBank.h"

class PatternSelector : public juce::Component {
public:
    explicit PatternSelector(PatternBank& bank);
    
    void paint(juce::Graphics&) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent&) override;

private:
    PatternBank& patternBank;
    std::array<juce::Rectangle<int>, 16> buttonBounds;
};
