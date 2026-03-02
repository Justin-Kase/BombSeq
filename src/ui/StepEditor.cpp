#include "StepEditor.h"
#include <juce_audio_basics/juce_audio_basics.h>

StepEditor::StepEditor(PatternBank& bank) : patternBank(bank) {
    // Setup sliders (no attachToComponent - manual layout)
    auto setupSlider = [this](juce::Slider& slider, juce::Label& label, const juce::String& text) {
        slider.setSliderStyle(juce::Slider::LinearHorizontal);
        slider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);
        addAndMakeVisible(slider);
        
        label.setText(text, juce::dontSendNotification);
        label.setColour(juce::Label::textColourId, juce::Colour(0xFFFFAA00)); // Amber
        label.setFont(juce::Font(13.0f, juce::Font::bold));
        label.setJustificationType(juce::Justification::centredLeft);
        addAndMakeVisible(label);
    };
    
    setupSlider(noteSlider, noteLabel, "NOTE (PITCH)");
    noteSlider.setRange(0, 127, 1);
    noteSlider.setValue(60);
    
    setupSlider(velocitySlider, velocityLabel, "VELOCITY (VOLUME)");
    velocitySlider.setRange(0, 127, 1);
    velocitySlider.setValue(100);
    
    setupSlider(gateSlider, gateLabel, "GATE (LENGTH)");
    gateSlider.setRange(0.0, 1.0, 0.01);
    gateSlider.setValue(0.5);
    
    setupSlider(probabilitySlider, probabilityLabel, "PROBABILITY (%)");
    probabilitySlider.setRange(0.0, 1.0, 0.01);
    probabilitySlider.setValue(1.0);
    
    auto updateStep = [this] {
        auto& step = patternBank.currentPattern().stepAt(selectedStep);
        step.note = static_cast<uint8_t>(noteSlider.getValue());
        step.velocity = static_cast<uint8_t>(velocitySlider.getValue());
        step.gate = static_cast<float>(gateSlider.getValue());
        step.probability = static_cast<float>(probabilitySlider.getValue());
        repaint(); // Update note name display
    };
    
    noteSlider.onValueChange = updateStep;
    velocitySlider.onValueChange = updateStep;
    gateSlider.onValueChange = updateStep;
    probabilitySlider.onValueChange = updateStep;
}

void StepEditor::paint(juce::Graphics& g) {
    // Dark panel background
    g.setColour(juce::Colour(0xFF3A3838));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);
    
    // LCD bezel for header
    auto headerArea = getLocalBounds().removeFromTop(30).reduced(8, 5);
    g.setColour(juce::Colour(0xFF404040)); // LCD bezel
    g.fillRoundedRectangle(headerArea.toFloat(), 2.0f);
    
    headerArea.reduce(2, 2);
    g.setColour(juce::Colour(0xFF2A3525)); // LCD background
    g.fillRoundedRectangle(headerArea.toFloat(), 1.0f);
    
    g.setColour(juce::Colour(0xFFFFAA00)); // Amber text
    g.setFont(juce::Font(16.0f, juce::Font::bold));
    g.drawText("STEP EDITOR", headerArea, juce::Justification::centred);
    
    // Note name display below header
    auto noteNameArea = getLocalBounds().withTop(35).withHeight(25).reduced(10, 3);
    g.setColour(juce::Colour(0xFF404040));
    g.fillRoundedRectangle(noteNameArea.toFloat(), 2.0f);
    
    noteNameArea.reduce(2, 2);
    g.setColour(juce::Colour(0xFF2A3525));
    g.fillRoundedRectangle(noteNameArea.toFloat(), 1.0f);
    
    const auto& step = patternBank.currentPattern().stepAt(selectedStep);
    juce::String noteName = juce::MidiMessage::getMidiNoteName(step.note, true, true, 3);
    
    g.setColour(juce::Colour(0xFFFFAA00));
    g.setFont(juce::Font(14.0f, juce::Font::bold));
    g.drawText(juce::String::formatted("STEP %02d: ", selectedStep + 1) + noteName,
              noteNameArea, juce::Justification::centred);
}

void StepEditor::resized() {
    auto area = getLocalBounds().reduced(10);
    area.removeFromTop(30);  // Header
    area.removeFromTop(25);  // Note name display
    area.removeFromTop(15);  // Spacing
    
    const int labelHeight = 20;
    const int sliderHeight = 30;
    const int padding = 10;
    
    // Note slider with label above
    noteLabel.setBounds(area.removeFromTop(labelHeight));
    noteSlider.setBounds(area.removeFromTop(sliderHeight));
    area.removeFromTop(padding);
    
    // Velocity slider with label above
    velocityLabel.setBounds(area.removeFromTop(labelHeight));
    velocitySlider.setBounds(area.removeFromTop(sliderHeight));
    area.removeFromTop(padding);
    
    // Gate slider with label above
    gateLabel.setBounds(area.removeFromTop(labelHeight));
    gateSlider.setBounds(area.removeFromTop(sliderHeight));
    area.removeFromTop(padding);
    
    // Probability slider with label above
    probabilityLabel.setBounds(area.removeFromTop(labelHeight));
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
