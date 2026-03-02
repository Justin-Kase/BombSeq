#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "engine/PatternBank.h"

class SaveLoadPanel : public juce::Component {
public:
    explicit SaveLoadPanel(PatternBank& bank);
    
    void paint(juce::Graphics&) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent&) override;

private:
    PatternBank& patternBank;
    
    std::array<juce::Rectangle<int>, 8> saveSlotBounds;
    std::array<juce::Rectangle<int>, 8> loadSlotBounds;
};
