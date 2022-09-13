#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Application : public juce::JUCEApplication
{
public:
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
        DBG ("Hello, World!");
    }

    void shutdown() final
    {
        DBG ("Goodbye, World!");
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Application)
};
