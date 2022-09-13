#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class OffScreenSlider : public juce::Component
{
public:
    OffScreenSlider ()
    {
        addAndMakeVisible (innerComponent);
    }

    void resized() override
    {
        innerComponent.setBounds (getLocalBounds());
    }

    static double getStepSize (const juce::Slider& slider)
    {
        const auto interval = slider.getInterval();

        return interval != 0.0 ? interval
                               : slider.getRange().getLength() * 0.01;
    }

    class OffScreenSliderAccessibilityHandler : public juce::AccessibilityHandler
    {
    public:
        explicit OffScreenSliderAccessibilityHandler (OffScreenSlider& component)
        : AccessibilityHandler (component,
                juce::AccessibilityRole::slider,
                juce::AccessibilityActions{},
                AccessibilityHandler::Interfaces { std::make_unique<ValueInterface> (component.innerComponent) })
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

    private:
        class ValueInterface  : public juce::AccessibilityValueInterface
        {
        public:
            explicit ValueInterface (juce::Slider& sliderToWrap)
                    : slider (sliderToWrap),
                      useMaxValue (slider.isTwoValue())
            {
            }

            bool isReadOnly() const override  { return false; }

            double getCurrentValue() const override
            {
                return useMaxValue ? slider.getMaximum()
                                   : slider.getValue();
            }

            void setValue (double newValue) override
            {
                juce::Slider::ScopedDragNotification drag (slider);

                if (useMaxValue)
                    slider.setMaxValue (newValue, juce::sendNotificationSync);
                else
                    slider.setValue (newValue, juce::sendNotificationSync);
            }

            juce::String getCurrentValueAsString() const override          { return slider.getTextFromValue (getCurrentValue()); }
            void setValueAsString (const juce::String& newValue) override  { setValue (slider.getValueFromText (newValue)); }

            AccessibleValueRange getRange() const override
            {
                return { { slider.getMinimum(), slider.getMaximum() },
                         getStepSize (slider) };
            }

        private:
            juce::Slider& slider;
            const bool useMaxValue;

            //==============================================================================
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ValueInterface)
        };

        OffScreenSlider& m_wrappedComponent;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OffScreenSliderAccessibilityHandler)
    };

    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler() override
    {
        return std::make_unique<OffScreenSliderAccessibilityHandler> (*this);
    }

    juce::Slider innerComponent;
};
