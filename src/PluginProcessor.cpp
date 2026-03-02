#include "PluginProcessor.h"
#include "PluginEditor.h"

BombSeqAudioProcessor::BombSeqAudioProcessor()
    : AudioProcessor(BusesProperties()
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", createParameterLayout()) {
    engine.setPatternBank(&patternBank);
}

BombSeqAudioProcessor::~BombSeqAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout BombSeqAudioProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("bpm", "BPM", 
        juce::NormalisableRange<float>(60.0f, 240.0f, 0.1f), 120.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>("playing", "Playing", false));
    
    return layout;
}

void BombSeqAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    engine.prepare(sampleRate, samplesPerBlock);
}

void BombSeqAudioProcessor::releaseResources() {
    engine.reset();
}

void BombSeqAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();
    
    auto posInfo = getPlayHead()->getPosition();
    if (!posInfo.hasValue()) return;
    
    const bool shouldPlay = *apvts.getRawParameterValue("playing") > 0.5f;
    const double bpm = *apvts.getRawParameterValue("bpm");
    
    engine.setBPM(bpm);
    engine.setPlaying(shouldPlay && posInfo->getIsPlaying());
    engine.processBlock(midiMessages, buffer.getNumSamples(), *posInfo);
}

juce::AudioProcessorEditor* BombSeqAudioProcessor::createEditor() {
    return new BombSeqAudioProcessorEditor(*this);
}

void BombSeqAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
    juce::ValueTree root("BombSeqState");
    root.appendChild(apvts.copyState(), nullptr);
    root.appendChild(patternBank.toValueTree(), nullptr);
    
    juce::MemoryOutputStream stream(destData, false);
    root.writeToStream(stream);
}

void BombSeqAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    juce::ValueTree root = juce::ValueTree::readFromData(data, (size_t)sizeInBytes);
    if (!root.isValid()) return;
    
    auto apvtsState = root.getChildWithName(apvts.state.getType());
    if (apvtsState.isValid())
        apvts.replaceState(apvtsState);
    
    auto bankState = root.getChildWithName(PatternBank::VT_TYPE);
    if (bankState.isValid())
        patternBank.fromValueTree(bankState);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new BombSeqAudioProcessor();
}
