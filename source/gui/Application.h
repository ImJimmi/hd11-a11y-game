#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "MainWindow.h"
#include "model/GameState.h"

class Application : public juce::JUCEApplication
{
public:
    //==============================================================================
    //ApplicationWindow
    class ApplicationWindow : public juce::DocumentWindow
    {
    public:
        explicit ApplicationWindow (const juce::String& name, GameState& gameState)
                : DocumentWindow {name,
                                  juce::Colours::black,
                                  TitleBarButtons::allButtons - TitleBarButtons::maximiseButton}
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainWindow {gameState}, true);
            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }

        void activeWindowStatusChanged() override
        {
            DocumentWindow::activeWindowStatusChanged();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ApplicationWindow)
    };

    Application() = default;

    const juce::String getApplicationName() final
    {
        return JUCE_APPLICATION_NAME_STRING;
    }

    const juce::String getApplicationVersion() final
    {
        return JUCE_APPLICATION_VERSION_STRING;
    }

    void initialise (const juce::String&) final
    {
        m_application = std::make_unique<ApplicationWindow>("A11y Game", m_state);
    }

    void shutdown() final
    {
        DBG ("Goodbye, World!");
    }

private:
    std::unique_ptr<ApplicationWindow> m_application;

    GameState m_state;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Application)
};
