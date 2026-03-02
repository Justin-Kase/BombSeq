#include "Pattern.h"

Pattern::Pattern() {
    // Initialize all steps as inactive
    for (auto& step : steps) {
        step = Step{};
    }
}

void Pattern::setNumSteps(int n) {
    numSteps = juce::jlimit(1, MAX_STEPS, n);
}

void Pattern::setSwingAmount(float a) {
    swingAmount = juce::jlimit(0.5f, 1.0f, a);
}

juce::ValueTree Pattern::toValueTree() const {
    juce::ValueTree vt(VT_TYPE);
    vt.setProperty(VT_NUM_STEPS, numSteps, nullptr);
    vt.setProperty(VT_SWING_AMT, swingAmount, nullptr);
    vt.setProperty(VT_SWING_GRID, static_cast<int>(swingGrid), nullptr);
    vt.setProperty(VT_NAME, name, nullptr);
    
    for (int i = 0; i < MAX_STEPS; ++i) {
        const auto& s = steps[i];
        juce::ValueTree stepVT(Step::ID);
        stepVT.setProperty(Step::A_ACTIVE, s.active, nullptr);
        stepVT.setProperty(Step::A_NOTE, s.note, nullptr);
        stepVT.setProperty(Step::A_VELOCITY, s.velocity, nullptr);
        stepVT.setProperty(Step::A_GATE, s.gate, nullptr);
        stepVT.setProperty(Step::A_PROB, s.probability, nullptr);
        stepVT.setProperty(Step::A_RATCHET, s.ratchet, nullptr);
        stepVT.setProperty(Step::A_MICRO, s.microTiming, nullptr);
        vt.appendChild(stepVT, nullptr);
    }
    return vt;
}

void Pattern::fromValueTree(const juce::ValueTree& vt) {
    if (!vt.hasType(VT_TYPE)) return;
    
    numSteps = vt.getProperty(VT_NUM_STEPS, 16);
    swingAmount = vt.getProperty(VT_SWING_AMT, 0.5f);
    swingGrid = static_cast<SwingGrid>(static_cast<int>(vt.getProperty(VT_SWING_GRID, 0)));
    name = vt.getProperty(VT_NAME, "Pattern").toString();
    
    for (int i = 0; i < vt.getNumChildren() && i < MAX_STEPS; ++i) {
        auto stepVT = vt.getChild(i);
        if (!stepVT.hasType(Step::ID)) continue;
        
        auto& s = steps[i];
        s.active = stepVT.getProperty(Step::A_ACTIVE, false);
        s.note = static_cast<uint8_t>(static_cast<int>(stepVT.getProperty(Step::A_NOTE, 60)));
        s.velocity = static_cast<uint8_t>(static_cast<int>(stepVT.getProperty(Step::A_VELOCITY, 100)));
        s.gate = stepVT.getProperty(Step::A_GATE, 0.5f);
        s.probability = stepVT.getProperty(Step::A_PROB, 1.0f);
        s.ratchet = stepVT.getProperty(Step::A_RATCHET, 1);
        s.microTiming = stepVT.getProperty(Step::A_MICRO, 0.0f);
    }
}
