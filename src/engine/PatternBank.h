#pragma once

#include "Pattern.h"
#include <juce_data_structures/juce_data_structures.h>
#include <array>

class PatternBank
{
public:
    static constexpr int NUM_PATTERNS   = 16;
    static constexpr int NUM_USER_SLOTS = 8;

    PatternBank();

    Pattern&       pattern (int i)       { return patterns[i]; }
    const Pattern& pattern (int i) const { return patterns[i]; }

    int  getCurrentIndex () const      { return currentIndex; }
    void setCurrentIndex (int i);

    Pattern&       currentPattern ()       { return patterns[currentIndex]; }
    const Pattern& currentPattern () const { return patterns[currentIndex]; }

    // User bank slots
    void saveToUserSlot   (int slot);
    void loadFromUserSlot (int slot);
    void clearUserSlot    (int slot);
    bool isUserSlotOccupied (int slot) const
    {
        return slot >= 0 && slot < NUM_USER_SLOTS && userSlotOccupied[slot];
    }

    // Serialisation
    juce::ValueTree toValueTree   () const;
    void            fromValueTree (const juce::ValueTree& vt);

    static constexpr auto VT_TYPE      = "PatternBank";
    static constexpr auto VT_CURRENT   = "currentIndex";
    static constexpr auto VT_USER_BANK = "UserBank";
    static constexpr auto VT_OCCUPIED  = "occupied";

private:
    std::array<Pattern, NUM_PATTERNS>   patterns;
    std::array<Pattern, NUM_USER_SLOTS> userPatterns;
    std::array<bool,    NUM_USER_SLOTS> userSlotOccupied{};
    int currentIndex = 0;
};
