# BombSeq 💣

VST3 MIDI sequencer with 64-step engine, MPC-style swing, and vintage hardware aesthetic.

## Download

**Pre-built VST3 binaries:**
- [macOS (Universal)](../../releases/latest/download/BombSeq-macOS.zip)
- [Windows (x64)](../../releases/latest/download/BombSeq-Windows.zip)
- [Linux (x64)](../../releases/latest/download/BombSeq-Linux.zip)

### Installation
- **macOS:** Extract and copy `BombSeq.vst3` to `~/Library/Audio/Plug-Ins/VST3/`
- **Windows:** Extract and copy `BombSeq.vst3` to `C:\Program Files\Common Files\VST3\`
- **Linux:** Extract and copy `BombSeq.vst3` to `~/.vst3/`

## Features

### Sequencer Engine
- **64-step MIDI sequencer** with per-step parameters:
  - Note (pitch, 0-127)
  - Velocity (volume, 0-127)
  - Gate (note length, 0.0-1.0)
  - Probability (trigger chance, 0.0-1.0)
- **Variable pattern length** (1-64 steps) with visual feedback
- **MPC-inspired swing/groove** (50-100%, three grid modes: 16th, 8th, triplet)
- **Sample-accurate timing** with host sync
- **Host tempo sync** - automatically follows DAW tempo changes
- **Step-1 fix** - all steps trigger correctly with zero timing drift

### Pattern Management
- **16 runtime pattern banks** for quick switching
- **8 persistent user save slots** with serialization
- Each pattern stores its own length and step data independently

### User Interface (MPC60 Vintage Aesthetic)
- **Grey/beige chassis** with wood side panels
- **8×8 rubber pad grid** with 3D raised rendering
- **Amber LCD displays** with vintage bezels
- **Cream hardware buttons** with red toggles
- **BOMB branding** in red (upper left)
- **Step selection:** Left-click selects (amber border), right-click toggles active/inactive (red)
- **Pattern length feedback:** Steps outside pattern length appear dark grey
- **Clear parameter labels:** "NOTE (PITCH)", "VELOCITY (VOLUME)", "GATE (LENGTH)", "PROBABILITY (%)"
- **Real-time note name display:** Shows selected step as "STEP 01: C4" with live updates

### Technical
- **MIDI FX plugin** (appears in MIDI FX browser, not Instruments)
- **Host transport integration** - Play button + DAW transport both required
- **Pattern persistence** - Length and step data saved with project
- **Cross-platform** builds for macOS, Windows, Linux

## Usage

1. **Load in DAW:** Add BombSeq as a MIDI FX device on a MIDI track
2. **Activate steps:** Right-click pads to toggle them red (active)
3. **Edit steps:** Left-click a pad to select it, adjust sliders on the right
4. **Set pattern length:** Adjust LENGTH slider (1-64 steps) - grey pads are outside pattern
5. **Play:** Press BombSeq's Play button + start DAW transport
6. **Save patterns:** Use SAVE buttons to store patterns, LOAD buttons to recall them

## Build

```bash
cmake -B build
cmake --build build --config Release
```

**Output:**
- VST3: `build/BombSeq_artefacts/Release/VST3/BombSeq.vst3`
- Standalone: `build/BombSeq_artefacts/Standalone/BombSeq.app`
- AU (macOS): `build/BombSeq_artefacts/Release/AU/BombSeq.component`

## Changelog

### v1.2.0 (March 2, 2026)
- ✅ **Host tempo sync** - BPM display now shows DAW tempo (read-only)
- ✅ **Pattern length control** - LENGTH slider (1-64) with visual feedback
- ✅ **Step labels above sliders** - Clear amber labels for all parameters
- ✅ **Grey-out inactive steps** - Steps beyond pattern length appear dark grey
- ✅ **Fixed step-1 trigger bug** - All steps now trigger correctly
- ✅ **Fixed timing drift** - Sample-accurate sync with host PPQ
- ✅ **Fixed note name display** - Updates in real-time when NOTE slider moves
- ✅ **Increased window height** - All UI elements visible (620px)

### v1.1.0 (March 2, 2026)
- ✅ **MPC60 vintage UI redesign** - Complete aesthetic overhaul
- Grey/beige chassis, rubber pads, amber LCDs, wood accents
- BOMB branding and vintage color palette

### v1.0.0 (March 2, 2026)
- Initial release with step selection, user save slots, and per-step editing

## Tech Stack
- JUCE 8.x (fetched via CMake)
- C++20
- VST3 + Standalone + AU

## License
MIT

---

**Developed with OpenClaw AI + GitHub Copilot**
