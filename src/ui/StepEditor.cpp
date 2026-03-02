#include "StepEditor.h"

StepEditor::StepEditor(PatternBank& bank) : patternBank(bank) {
    auto setupSlider = [this](juce::Slider& slider, juce::Label& label, const juce::String& text) {
        slider.setSliderStyle(juce::Slider::LinearHorizontal);
        slider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);
        addAndMakeVisible(slider);
        
        label.setText(text, juce::dontSendNotification);
        label.attachToComponent(&slider, true);
        addAndMakeVisible(label);
    };
    
    setupSlider(noteSlider, noteLabel, "Note");
    noteSlider.setRange(0, 127, 1);
    noteSlider.setValue(60);
    
    setupSlider(velocitySlider, velocityLabel, "Velocity");
    velocitySlider.setRange(0, 127, 1);
    velocitySlider.setValue(100);
    
    setupSlider(gateSlider, gateLabel, "Gate");
    gateSlider.setRange(0.0, 1.0, 0.01);
    gateSlider.setValue(0.5);
    
    setupSlider(probabilitySlider, probabilityLabel, "Probability");
    probabilitySlider.setRange(0.0, 1.0, 0.01);
    probabilitySlider.setValue(1.0);
    
    auto updateStep = [this] {
        auto& step = patternBank.currentPattern().stepAt(selectedStep);
        step.note = static_cast<uint8_t>(noteSlider.getValue());
        step.velocity = static_cast<uint8_t>(velocitySlider.getValue());
        step.gate = static_cast<float>(gateSlider.getValue());
        step.probability = static_cast<float>(probabilitySlider.getValue());
    };
    
    noteSlider.onValueChange = updateStep;
    velocitySlider.onValueChange = updateStep;
    gateSlider.onValueChange = updateStep;
    probabilitySlider.onValueChange = updateStep;
}

void StepEditor::paint(juce::Graphics& g) {
    g.setColour(juce::Colour(0xFF2A2A2A));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);
    
    g.setColour(juce::Colour(0xFFE0E0E0));
    g.setFont(16.0f);
    g.drawText("Step " + juce::String(selectedStep + 1), getLocalBounds().removeFromTop(30), juce::Justification::centred);
}

void StepEditor::resized() {
    auto area = getLocalBounds().reduced(10);
    area.removeFromTop(30);
    
    const int sliderHeight = 40;
    const int padding = 10;
    
    noteSlider.setBounds(area.removeFromTop(sliderHeight));
    area.removeFromTop(padding);
    
    velocitySlider.setBounds(area.removeFromTop(sliderHeight));
    area.removeFromTop(padding);
    
    gateSlider.setBounds(area.removeFromTop(sliderHeight));
    area.removeFromTop(padding);
    
    probabilitySlider.setBounds(area.removeFromTop(sliderHeight));
}

void StepEditor::setSelectedStep(int step) {
    selectedStep = juce::jlimit(0, 63, step);
    
    const auto& s = patternBank.currentPattern().stepAt(selectedStep);
    noteSlider.setValue(s.note, juce::dontSendNotification);
    velocitySlider.setValue(s.velocity, juce::dontSendNotification);
    gateSlider.setValue(s.gate, juce::dontSendNotification);
    probabilitySlider.setValue(s.probability, juce::dontSendNotification);
    
    repaint();
}
