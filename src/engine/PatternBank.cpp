#include "PatternBank.h"

PatternBank::PatternBank() {
    for (int i = 0; i < NUM_PATTERNS; ++i) {
        patterns[i].setName("Pattern " + juce::String(i + 1));
    }
}

void PatternBank::setCurrentIndex(int i) {
    currentIndex = juce::jlimit(0, NUM_PATTERNS - 1, i);
}

juce::ValueTree PatternBank::toValueTree() const {
    juce::ValueTree vt(VT_TYPE);
    vt.setProperty(VT_CURRENT, currentIndex, nullptr);
    
    for (const auto& pat : patterns) {
        vt.appendChild(pat.toValueTree(), nullptr);
    }
    return vt;
}

void PatternBank::fromValueTree(const juce::ValueTree& vt) {
    if (!vt.hasType(VT_TYPE)) return;
    
    currentIndex = vt.getProperty(VT_CURRENT, 0);
    
    for (int i = 0; i < vt.getNumChildren() && i < NUM_PATTERNS; ++i) {
        patterns[i].fromValueTree(vt.getChild(i));
    }
}
