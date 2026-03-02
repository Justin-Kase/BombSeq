#pragma once

#include <cstdint>

// Per-step data for BombSeq. All fields are plain data; no JUCE dependency here
// so this header can be included in both audio-thread and UI code cheaply.
struct Step
{
    bool    active      = false;
    uint8_t note        = 60;    // MIDI note 0-127
    uint8_t velocity    = 100;   // 0-127
    float   gate        = 0.5f;  // fraction of step duration (0.0-1.0)
    float   probability = 1.0f;  // 0.0-1.0; 1.0 = always fires
    int     ratchet     = 1;     // repetitions per step slot (1-8)
    float   microTiming = 0.0f;  // PPQ offset: negative = early, positive = late (-0.5..+0.5)

    // ValueTree attribute name constants
    static constexpr auto ID          = "Step";
    static constexpr auto A_ACTIVE    = "active";
    static constexpr auto A_NOTE      = "note";
    static constexpr auto A_VELOCITY  = "velocity";
    static constexpr auto A_GATE      = "gate";
    static constexpr auto A_PROB      = "probability";
    static constexpr auto A_RATCHET   = "ratchet";
    static constexpr auto A_MICRO     = "micro";
};
