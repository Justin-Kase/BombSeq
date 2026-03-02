#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class MpcLookAndFeel : public juce::LookAndFeel_V4 {
public:
    MpcLookAndFeel();
    
    juce::Colour getBackgroundColour() const { return background; }
    juce::Colour getPanelColour() const { return panel; }
    juce::Colour getPadGrey() const { return padGrey; }
    juce::Colour getLEDInactive() const { return ledInactive; }
    juce::Colour getLEDActive() const { return ledActive; }
    juce::Colour getLEDPlaying() const { return ledPlaying; }
    juce::Colour getLCDText() const { return lcdText; }
    juce::Colour getLCDBackground() const { return lcdBackground; }
    juce::Colour getCreamButton() const { return creamButton; }
    juce::Colour getRedButton() const { return redButton; }
    juce::Colour getWoodPanel() const { return woodPanel; }
    juce::Colour getBrandRed() const { return brandRed; }
    
    void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool) override;
    void drawLinearSlider(juce::Graphics&, int x, int y, int width, int height,
                         float sliderPos, float minSliderPos, float maxSliderPos,
                         juce::Slider::SliderStyle, juce::Slider&) override;

private:
    // MPC60 vintage color scheme
    juce::Colour background{0xFFA8A095};      // Warm putty grey chassis
    juce::Colour panel{0xFF3A3838};           // Dark bottom section
    juce::Colour panelBorder{0xFF404040};     // LCD bezel grey
    juce::Colour padGrey{0xFF7A7672};         // Rubber pad grey
    juce::Colour ledInactive{0xFF7A7672};     // Pad grey (inactive)
    juce::Colour ledActive{0xFFCC2020};       // Red (active)
    juce::Colour ledPlaying{0xFFFFAA00};      // Amber (playing)
    juce::Colour lcdText{0xFFFFAA00};         // Amber LCD
    juce::Colour lcdBackground{0xFF2A3525};   // LCD dark background
    juce::Colour creamButton{0xFFE8E0D0};     // Cream/ivory buttons
    juce::Colour redButton{0xFFCC2020};       // Red function buttons
    juce::Colour woodPanel{0xFFB07830};       // Oak side panels
    juce::Colour brandRed{0xFFCC0000};        // BOMB logo red
    juce::Colour text{0xFF2A2A2A};            // Dark text
};
