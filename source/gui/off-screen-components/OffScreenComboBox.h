#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class OffScreenComboBox : public juce::Component
{
public:
    OffScreenComboBox()
    {
        addAndMakeVisible (innerComponent);
    }

    OffScreenComboBox (const juce::String& text)
        : OffScreenComboBox {}
    {
        innerComponent.setText (text, juce::sendNotification);
    }

    void resized() override
    {
        innerComponent.setBounds (getLocalBounds());
    }

    class OffScreenComboBoxAccessibilityHandler : public juce::AccessibilityHandler
    {
    public:
        explicit OffScreenComboBoxAccessibilityHandler (OffScreenComboBox& component,
                                                        juce::AccessibilityActions actions)
            : juce::AccessibilityHandler {component,
                                          juce::AccessibilityRole::comboBox,
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

        OffScreenComboBox& m_wrappedComponent;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OffScreenComboBoxAccessibilityHandler)
    };

    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler() override
    {
        juce::AccessibilityActions actions;
        actions.addAction (juce::AccessibilityActionType::press, [this] {
            innerComponent.showPopup();
        });

        return std::make_unique<OffScreenComboBoxAccessibilityHandler> (*this, actions);
    }

    juce::ComboBox innerComponent;
};
