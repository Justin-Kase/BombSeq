# BombSeq 💣

VST3 MIDI sequencer with 64-step engine, MPC-style swing, and hardware-inspired UI.

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
- 64-step sequencer with per-step parameters (note, velocity, gate, probability)
- **Step selection system:** Left-click to select steps, right-click/shift-click to toggle active
- **Per-step editing:** Selected step parameters displayed with note name (C4, D#5, etc.)
- MPC-inspired swing/groove (50-100%, three grid modes)
- Sample-accurate timing with host sync
- 16 runtime pattern banks
- **8 user save slots:** Persistent pattern storage with save/load buttons
- Hardware aesthetic UI (charcoal/red/amber theme, green LCD text)
- Clear parameter labeling (BPM units, PATTERN header, formatted displays)

## UI Improvements (March 2, 2026)
- ✅ Better labeling on all parameters (BPM slider shows "XXX BPM", Pattern selector has "PATTERN" header)
- ✅ Step selection with white border indicator
- ✅ StepEditor shows selected step with formatted note display
- ✅ SaveLoadPanel with 8 user bank slots (amber = saved, red = load)
- ✅ All step editing wired to selected step

## Build

```bash
cmake -B build
cmake --build build --config Release
```

VST3 output: `build/BombSeq_artefacts/Release/VST3/BombSeq.vst3`
Standalone: `build/BombSeq_artefacts/Standalone/BombSeq.app`

## Tech Stack
- JUCE 8.x (fetched via CMake)
- C++20
- VST3 + Standalone + AU

## License
MIT
