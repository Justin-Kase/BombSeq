# BombSeq 💣

VST3 MIDI sequencer with 64-step engine, MPC-style swing, and hardware-inspired UI.

## Features
- 64-step sequencer with per-step parameters
- MPC-inspired swing/groove (50-100%, three grid modes)
- Sample-accurate timing with host sync
- 16 pattern storage banks
- Hardware aesthetic UI (charcoal/red/amber theme)

## Build

```bash
cmake -B build
cmake --build build --config Release
```

VST3 output: `build/BombSeq_artefacts/Release/VST3/BombSeq.vst3`

## Tech Stack
- JUCE 8.x (fetched via CMake)
- C++20
- VST3 + Standalone

## License
MIT
