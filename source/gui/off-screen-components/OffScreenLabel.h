#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class OffScreenLabel : public juce::Component
{
public:
    OffScreenLabel ()
    {
        addAndMakeVisible (innerComponent);
    }

    OffScreenLabel (const juce::String& text)
        : OffScreenLabel {}
    {
        innerComponent.setText (text, juce::sendNotification);
    }

    void resized() override
    {
        innerComponent.setBounds (getLocalBounds());
    }

    class OffScreenLabelAccessibilityHandler : public juce::AccessibilityHandler
    {
    public:
        explicit OffScreenLabelAccessibilityHandler (OffScreenLabel& component)
                : juce::AccessibilityHandler {component,
                                              juce::AccessibilityRole::label}
              , m_wrappedComponent {component}
        {
        }

        juce::AccessibleState getCurrentState() const override
        {
            return juce::AccessibilityHandler::getCurrentState().withAccessibleOffscreen();
        }

        juce::String getTitle() const override
        {
            return m_wrappedComponent.innerComponent.getAccessibilityHandler()->getTitle();
        }

        OffScreenLabel& m_wrappedComponent;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OffScreenLabelAccessibilityHandler)
    };

    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler() override
    {
        return std::make_unique<OffScreenLabelAccessibilityHandler> (*this);
    }

    juce::Label innerComponent;
};
