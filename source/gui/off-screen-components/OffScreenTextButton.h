#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class OffScreenTextButton : public juce::Component
{
public:
    OffScreenTextButton ()
        : OffScreenTextButton ("")
    {
    }

    explicit OffScreenTextButton (const juce::String& buttonText)
    {
        innerComponent.setButtonText (buttonText);
        addAndMakeVisible (innerComponent);
    }

    void resized() override
    {
        innerComponent.setBounds (getLocalBounds());
    }

    class OffScreenTextButtonAccessibilityHandler : public juce::AccessibilityHandler
    {
    public:
        explicit OffScreenTextButtonAccessibilityHandler (OffScreenTextButton& component, juce::AccessibilityActions actions)
                : juce::AccessibilityHandler {component,
                                              juce::AccessibilityRole::button,
                                              actions}
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

        OffScreenTextButton& m_wrappedComponent;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OffScreenTextButtonAccessibilityHandler)
    };

    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler() override
    {
        juce::AccessibilityActions actions;
        actions.addAction (juce::AccessibilityActionType::press, [this]{
            innerComponent.onClick();
        });

        return std::make_unique<OffScreenTextButtonAccessibilityHandler> (*this, actions);
    }

    juce::TextButton innerComponent;
};
