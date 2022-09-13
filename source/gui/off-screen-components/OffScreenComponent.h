#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class OffScreenComponent : public juce::Component
{
public:
    OffScreenComponent()
    {
    }

    class OffScreenComponentAccessibilityHandler : public juce::AccessibilityHandler
    {
    public:
        explicit OffScreenComponentAccessibilityHandler (OffScreenComponent& component)
            : juce::AccessibilityHandler {component,
                                          juce::AccessibilityRole::group}
            , m_wrappedComponent {component}
        {
        }

        juce::AccessibleState getCurrentState() const override
        {
            return juce::AccessibilityHandler::getCurrentState().withAccessibleOffscreen();
        }

        OffScreenComponent& m_wrappedComponent;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OffScreenComponentAccessibilityHandler)
    };

    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler() override
    {
        return std::make_unique<OffScreenComponentAccessibilityHandler> (*this);
    }
};
