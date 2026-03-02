#include "MpcLookAndFeel.h"

MpcLookAndFeel::MpcLookAndFeel() {
    setColour(juce::TextButton::buttonColourId, ledInactive);
    setColour(juce::TextButton::buttonOnColourId, ledActive);
    setColour(juce::TextButton::textColourOffId, text);
    setColour(juce::TextButton::textColourOnId, text);
    setColour(juce::Slider::thumbColourId, ledActive);
    setColour(juce::Slider::trackColourId, panelBorder);
    setColour(juce::Label::textColourId, lcdText);
}

void MpcLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, 
                                          const juce::Colour& backgroundColour,
                                          bool isMouseOverButton, bool isButtonDown) {
    auto bounds = button.getLocalBounds().toFloat().reduced(2.0f);
    
    juce::Colour fillColour = ledInactive;
    if (button.getToggleState())
        fillColour = ledActive;
    else if (isMouseOverButton)
        fillColour = ledInactive.brighter(0.2f);
    
    g.setColour(fillColour);
    g.fillRoundedRectangle(bounds, 2.0f);
    
    g.setColour(panelBorder);
    g.drawRoundedRectangle(bounds, 2.0f, 1.0f);
}

void MpcLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                                      float sliderPos, float minSliderPos, float maxSliderPos,
                                      juce::Slider::SliderStyle style, juce::Slider& slider) {
    auto trackBounds = juce::Rectangle<float>(x, y, width, height).reduced(2.0f);
    
    g.setColour(panelBorder);
    g.fillRoundedRectangle(trackBounds, 2.0f);
    
    auto fillBounds = trackBounds;
    if (slider.isHorizontal()) {
        fillBounds.setWidth((sliderPos - x) * trackBounds.getWidth() / width);
    } else {
        const float fillHeight = (y + height - sliderPos) * trackBounds.getHeight() / height;
        fillBounds.setY(trackBounds.getBottom() - fillHeight);
        fillBounds.setHeight(fillHeight);
    }
    
    g.setColour(ledActive);
    g.fillRoundedRectangle(fillBounds, 2.0f);
}
