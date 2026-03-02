#include "PluginEditor.h"
#include <BinaryData.h>

BombSeqAudioProcessorEditor::BombSeqAudioProcessorEditor(BombSeqAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p),
      stepGrid(p.getPatternBank()),
      patternSelector(p.getPatternBank()),
      transportBar(p),
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
    
    setSize(840, 620);
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
    
    // Main chassis background with subtle gradient
    auto bgBounds = getLocalBounds();
    g.setGradientFill(juce::ColourGradient(
        mpcLookAndFeel.getBackgroundColour().brighter(0.05f), 0, 0,
        mpcLookAndFeel.getBackgroundColour().darker(0.05f), 0, getHeight(), false));
    g.fillAll();
    
    // BOMB branding (upper left) with subtle shadow
    g.setColour(juce::Colours::black.withAlpha(0.3f));
    g.setFont(juce::Font(juce::FontOptions("Arial Black", 36.0f, juce::Font::bold)));
    g.drawText("BOMB", 52, 17, 150, 40, juce::Justification::centredLeft);
    
    g.setColour(mpcLookAndFeel.getBrandRed());
    g.drawText("BOMB", 50, 15, 150, 40, juce::Justification::centredLeft);
    
    // Logo in upper right corner with black circular background
    if (logoImage.isValid()) {
        const int logoSize = 50;
        const int logoX = getWidth() - logoSize - 50;
        const int logoY = 15;
        
        // Black circle background
        g.setColour(juce::Colours::black);
        g.fillEllipse(logoX - 3, logoY - 3, logoSize + 6, logoSize + 6);
        
        // Logo
        g.drawImage(logoImage, logoX, logoY, logoSize, logoSize,
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
