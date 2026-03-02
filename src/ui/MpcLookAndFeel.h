#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class MpcLookAndFeel : public juce::LookAndFeel_V4 {
public:
    MpcLookAndFeel();
    
    juce::Colour getBackgroundColour() const { return background; }
    juce::Colour getPanelColour() const { return panel; }
    juce::Colour getLEDInactive() const { return ledInactive; }
    juce::Colour getLEDActive() const { return ledActive; }
    juce::Colour getLEDPlaying() const { return ledPlaying; }
    juce::Colour getLCDText() const { return lcdText; }
    
    void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool) override;
    void drawLinearSlider(juce::Graphics&, int x, int y, int width, int height,
                         float sliderPos, float minSliderPos, float maxSliderPos,
                         juce::Slider::SliderStyle, juce::Slider&) override;

private:
    juce::Colour background{0xFF1A1A1A};
    juce::Colour panel{0xFF2A2A2A};
    juce::Colour panelBorder{0xFF3A3A3A};
    juce::Colour ledInactive{0xFF3A3A3A};
    juce::Colour ledActive{0xFFD63031};
    juce::Colour ledPlaying{0xFFFF8C00};
    juce::Colour lcdText{0xFF33FF33};
    juce::Colour text{0xFFE0E0E0};
};
