#pragma once

#include "Pattern.h"
#include <juce_data_structures/juce_data_structures.h>
#include <array>

class PatternBank
{
public:
    static constexpr int NUM_PATTERNS = 16;

    PatternBank();

    Pattern&       pattern (int i)       { return patterns[i]; }
    const Pattern& pattern (int i) const { return patterns[i]; }

    int  getCurrentIndex () const      { return currentIndex; }
    void setCurrentIndex (int i);

    Pattern&       currentPattern ()       { return patterns[currentIndex]; }
    const Pattern& currentPattern () const { return patterns[currentIndex]; }

    // Serialisation
    juce::ValueTree toValueTree   () const;
    void            fromValueTree (const juce::ValueTree& vt);

    static constexpr auto VT_TYPE    = "PatternBank";
    static constexpr auto VT_CURRENT = "currentIndex";

private:
    std::array<Pattern, NUM_PATTERNS> patterns;
    int currentIndex = 0;
};
