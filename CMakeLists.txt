cmake_minimum_required(VERSION 3.12)
project("a11y-game"
    VERSION 1.0.0
)

add_subdirectory(JUCE)

juce_add_gui_app(a11y-game
    PRODUCT_NAME "A11y Game"
    COMPANY_NAME "Cool Game Guys"
)

target_sources(a11y-game
PRIVATE
    source/gui/off-screen-components/OffScreenComboBox.h
    source/gui/off-screen-components/OffScreenComponent.h
    source/gui/off-screen-components/OffScreenLabel.h
    source/gui/off-screen-components/OffScreenSlider.h
    source/gui/off-screen-components/OffScreenTextButton.h
    source/gui/Application.h
    source/gui/MainWindow.h
    source/gui/Room1.h
    source/gui/Room2.h
    source/gui/Room3.h
    source/model/GameState.h
    source/main.cpp
)

target_compile_definitions(a11y-game
PRIVATE
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:a11y-game,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:a11y-game,JUCE_VERSION>"
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0
)

target_include_directories(a11y-game
PRIVATE
    source
)

target_link_libraries(a11y-game
PRIVATE
    juce::juce_gui_extra
)

target_compile_features(a11y-game
PRIVATE
    cxx_std_17
)
