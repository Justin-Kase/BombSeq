#include "MpcLookAndFeel.h"

MpcLookAndFeel::MpcLookAndFeel() {
    setColour(juce::TextButton::buttonColourId, creamButton);
    setColour(juce::TextButton::buttonOnColourId, redButton);
    setColour(juce::TextButton::textColourOffId, text);
    setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    setColour(juce::Slider::thumbColourId, redButton);
    setColour(juce::Slider::trackColourId, panelBorder);
    setColour(juce::Label::textColourId, lcdText);
    setColour(juce::Label::backgroundColourId, lcdBackground);
}

void MpcLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, 
                                          const juce::Colour& backgroundColour,
                                          bool isMouseOverButton, bool isButtonDown) {
    auto bounds = button.getLocalBounds().toFloat().reduced(1.5f);
    
    juce::Colour fillColour = creamButton;
    if (button.getToggleState())
        fillColour = redButton;
    else if (isMouseOverButton)
        fillColour = creamButton.darker(0.1f);
    
    if (isButtonDown)
        fillColour = fillColour.darker(0.15f);
    
    // Vintage raised button look
    g.setColour(fillColour);
    g.fillRoundedRectangle(bounds, 3.0f);
    
    // Highlight (top-left)
    g.setColour(fillColour.brighter(0.3f));
    g.drawLine(bounds.getX() + 3, bounds.getY() + 1, 
               bounds.getRight() - 3, bounds.getY() + 1, 1.0f);
    g.drawLine(bounds.getX() + 1, bounds.getY() + 3,
               bounds.getX() + 1, bounds.getBottom() - 3, 1.0f);
    
    // Shadow (bottom-right)
    g.setColour(fillColour.darker(0.4f));
    g.drawLine(bounds.getX() + 3, bounds.getBottom() - 1,
               bounds.getRight() - 3, bounds.getBottom() - 1, 1.0f);
    g.drawLine(bounds.getRight() - 1, bounds.getY() + 3,
               bounds.getRight() - 1, bounds.getBottom() - 3, 1.0f);
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
