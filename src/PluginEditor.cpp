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
    auto bounds = getLocalBounds();
    
    // Wood side panels (40px each side)
    g.setColour(mpcLookAndFeel.getWoodPanel());
    g.fillRect(bounds.removeFromLeft(40));
    g.fillRect(bounds.removeFromRight(40));
    
    // Main chassis background
    g.setColour(mpcLookAndFeel.getBackgroundColour());
    g.fillAll();
    
    // BOMB branding (upper left)
    g.setColour(mpcLookAndFeel.getBrandRed());
    juce::Font bombFont(juce::FontOptions("Arial Black", 36.0f, juce::Font::bold));
    g.setFont(bombFont);
    g.drawText("BOMB", 50, 15, 150, 40, juce::Justification::centredLeft);
    
    // Logo in upper right corner (keep existing bomb emoji logo)
    if (logoImage.isValid()) {
        const int logoSize = 50;
        g.drawImage(logoImage, getWidth() - logoSize - 50, 15, logoSize, logoSize,
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
