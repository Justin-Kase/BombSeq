cmake_minimum_required(VERSION 3.22)
project(BombSeq VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        8.0.4
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(JUCE)

juce_add_plugin(BombSeq
    PLUGIN_MANUFACTURER_CODE  MCLS
    PLUGIN_CODE               Seq1
    FORMATS                   VST3 Standalone
    PRODUCT_NAME              "BombSeq"
    COMPANY_NAME              "McLarenSynth"
    IS_SYNTH                  FALSE
    NEEDS_MIDI_INPUT          FALSE
    NEEDS_MIDI_OUTPUT         TRUE
    IS_MIDI_EFFECT            TRUE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD   FALSE
)

target_sources(BombSeq
    PRIVATE
        src/PluginProcessor.cpp
        src/PluginEditor.cpp
        src/engine/Pattern.cpp
        src/engine/PatternBank.cpp
        src/engine/SequencerEngine.cpp
        src/ui/MpcLookAndFeel.cpp
        src/ui/StepGrid.cpp
        src/ui/PatternSelector.cpp
        src/ui/TransportBar.cpp
        src/ui/StepEditor.cpp
        src/ui/SaveLoadPanel.cpp
)

target_include_directories(BombSeq
    PRIVATE
        src
)

target_compile_definitions(BombSeq
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(BombSeq
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_plugin_client
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
