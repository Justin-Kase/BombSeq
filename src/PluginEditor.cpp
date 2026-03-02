#include "PluginEditor.h"
#include <BinaryData.h>

BombSeqAudioProcessorEditor::BombSeqAudioProcessorEditor(BombSeqAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p),
      stepGrid(p.getPatternBank()),
      patternSelector(p.getPatternBank()),
      transportBar(p.getAPVTS()),
      stepEditor(p.getPatternBank()),
      saveLoadPanel(p.getPatternBank()) {
    
    setLookAndFeel(&mpcLookAndFeel);
    
    // Load logo from binary resources
    int logoDataSize = 0;
    auto logoData = BinaryData::getNamedResource("logo_png", logoDataSize);
    if (logoData != nullptr && logoDataSize > 0) {
        logoImage = juce::ImageFileFormat::loadFrom(logoData, logoDataSize);
    }
    
    addAndMakeVisible(stepGrid);
    addAndMakeVisible(patternSelector);
    addAndMakeVisible(transportBar);
    addAndMakeVisible(stepEditor);
    addAndMakeVisible(saveLoadPanel);
    
    // Wire step selection: when a step is clicked, update StepEditor
    stepGrid.onStepSelected = [this](int step) {
        stepEditor.setSelectedStep(step);
    };
    
    // Initialize StepEditor to step 0
    stepEditor.setSelectedStep(0);
    
    setSize(840, 580);
    setResizable(false, false);
    
    startTimerHz(30);
}

BombSeqAudioProcessorEditor::~BombSeqAudioProcessorEditor() {
    stopTimer();
    setLookAndFeel(nullptr);
}

void BombSeqAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(mpcLookAndFeel.getBackgroundColour());
    
    // Draw logo in upper left corner (60x60px)
    if (logoImage.isValid()) {
        const int logoSize = 60;
        g.drawImage(logoImage, 10, 10, logoSize, logoSize,
                   0, 0, logoImage.getWidth(), logoImage.getHeight());
    }
}

void BombSeqAudioProcessorEditor::resized() {
    auto area = getLocalBounds().reduced(10);
    
    transportBar.setBounds(area.removeFromTop(60));
    area.removeFromTop(10);
    
    auto topRow = area.removeFromTop(320);
    stepGrid.setBounds(topRow.removeFromLeft(320));
    topRow.removeFromLeft(10);
    stepEditor.setBounds(topRow);
    
    area.removeFromTop(10);
    patternSelector.setBounds(area.removeFromTop(60));
    
    area.removeFromTop(10);
    saveLoadPanel.setBounds(area.removeFromTop(110));
}

void BombSeqAudioProcessorEditor::timerCallback() {
    const int currentStep = processor.getEngine().getCurrentStep();
    stepGrid.setCurrentStep(currentStep);
}
