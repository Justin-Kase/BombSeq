#pragma once

#include "PluginProcessor.h"
#include "ui/MpcLookAndFeel.h"
#include "ui/StepGrid.h"
#include "ui/PatternSelector.h"
#include "ui/TransportBar.h"
#include "ui/StepEditor.h"
#include "ui/SaveLoadPanel.h"

class BombSeqAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::Timer {
public:
    explicit BombSeqAudioProcessorEditor(BombSeqAudioProcessor&);
    ~BombSeqAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    BombSeqAudioProcessor& processor;
    MpcLookAndFeel mpcLookAndFeel;
    
    StepGrid stepGrid;
    PatternSelector patternSelector;
    TransportBar transportBar;
    StepEditor stepEditor;
    SaveLoadPanel saveLoadPanel;
    
    juce::Image logoImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BombSeqAudioProcessorEditor)
};
