#include "PatternBank.h"

PatternBank::PatternBank() {
    for (int i = 0; i < NUM_PATTERNS; ++i) {
        patterns[i].setName("Pattern " + juce::String(i + 1));
    }
    for (int i = 0; i < NUM_USER_SLOTS; ++i) {
        userPatterns[i].setName("User " + juce::String(i + 1));
    }
}

void PatternBank::setCurrentIndex(int i) {
    currentIndex = juce::jlimit(0, NUM_PATTERNS - 1, i);
}

void PatternBank::saveToUserSlot(int slot) {
    if (slot < 0 || slot >= NUM_USER_SLOTS) return;
    userPatterns[slot]     = currentPattern();
    userSlotOccupied[slot] = true;
}

void PatternBank::loadFromUserSlot(int slot) {
    if (slot < 0 || slot >= NUM_USER_SLOTS) return;
    if (!userSlotOccupied[slot]) return;
    currentPattern() = userPatterns[slot];
}

juce::ValueTree PatternBank::toValueTree() const {
    juce::ValueTree vt(VT_TYPE);
    vt.setProperty(VT_CURRENT, currentIndex, nullptr);

    for (const auto& pat : patterns)
        vt.appendChild(pat.toValueTree(), nullptr);

    juce::ValueTree userBank(VT_USER_BANK);
    for (int i = 0; i < NUM_USER_SLOTS; ++i) {
        auto slotVt = userPatterns[i].toValueTree();
        slotVt.setProperty(VT_OCCUPIED, userSlotOccupied[i], nullptr);
        userBank.appendChild(slotVt, nullptr);
    }
    vt.appendChild(userBank, nullptr);

    return vt;
}

void PatternBank::fromValueTree(const juce::ValueTree& vt) {
    if (!vt.hasType(VT_TYPE)) return;

    currentIndex = vt.getProperty(VT_CURRENT, 0);

    int patIdx = 0;
    for (int i = 0; i < vt.getNumChildren(); ++i) {
        auto child = vt.getChild(i);
        if (child.hasType(Pattern::VT_TYPE) && patIdx < NUM_PATTERNS) {
            patterns[patIdx++].fromValueTree(child);
        } else if (child.hasType(VT_USER_BANK)) {
            for (int j = 0; j < child.getNumChildren() && j < NUM_USER_SLOTS; ++j) {
                auto slotVt = child.getChild(j);
                userSlotOccupied[j] = static_cast<bool>((int)slotVt.getProperty(VT_OCCUPIED, 0));
                userPatterns[j].fromValueTree(slotVt);
            }
        }
    }
}
