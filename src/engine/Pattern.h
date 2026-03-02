#pragma once

#include "Step.h"
#include <juce_data_structures/juce_data_structures.h>
#include <array>

class Pattern
{
public:
    static constexpr int MAX_STEPS = 64;

    enum class SwingGrid { Sixteenth, Eighth, Triplet };

    Pattern();

    // Step access
    Step&       stepAt (int i)       { return steps[i]; }
    const Step& stepAt (int i) const { return steps[i]; }

    // Length
    int  getNumSteps ()    const { return numSteps; }
    void setNumSteps (int n);
    void setLength   (int n)     { setNumSteps(n); } // Alias for clarity

    // Swing
    float     getSwingAmount () const          { return swingAmount; }
    void      setSwingAmount (float a);
    SwingGrid getSwingGrid ()  const           { return swingGrid; }
    void      setSwingGrid  (SwingGrid g)      { swingGrid = g; }

    // Name
    juce::String getName ()                 const { return name; }
    void         setName (const juce::String& n)  { name = n; }

    // Serialisation
    juce::ValueTree toValueTree   () const;
    void            fromValueTree (const juce::ValueTree& vt);

    // ValueTree type/attribute ids
    static constexpr auto VT_TYPE       = "Pattern";
    static constexpr auto VT_NUM_STEPS  = "numSteps";
    static constexpr auto VT_SWING_AMT  = "swingAmount";
    static constexpr auto VT_SWING_GRID = "swingGrid";
    static constexpr auto VT_NAME       = "name";

private:
    std::array<Step, MAX_STEPS> steps;
    int          numSteps    = 16;
    float        swingAmount = 0.5f;   // 0.5 = straight, 1.0 = max swing
    SwingGrid    swingGrid   = SwingGrid::Sixteenth;
    juce::String name        = "Pattern";
};
