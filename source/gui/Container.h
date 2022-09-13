#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "off-screen-components/OffScreenTextButton.h"

class Container : public juce::Component
{
public:
    explicit Container (int numItems)
    {
        setTitle ("Box");
        setFocusContainerType (FocusContainerType::focusContainer);

        while (m_items.size() < numItems)
        {
            auto* item = m_items.add (createRandomItem());
            addAndMakeVisible (*item);
        }
    }

    void resized() final
    {
        juce::FlexBox flexBox;

        for (auto* const item : m_items)
        {
            flexBox.items.add (juce::FlexItem {*item}.withFlex (1.0f));
        }

        flexBox.performLayout (getLocalBounds());
    }

    void add (std::unique_ptr<OffScreenTextButton> item)
    {
        addAndMakeVisible (*item);

        auto& rng = juce::Random::getSystemRandom();
        const auto insertIndex = rng.nextInt (m_items.size() + 1);
        m_items.insert (insertIndex, std::move (item));

        resized();
    }

    void remove (const juce::String& itemName)
    {
        for (auto i = m_items.size() - 1; i >= 0; i--)
        {
            if (m_items[i]->innerComponent.getButtonText() == itemName)
                m_items.remove (i);
        }

        resized();
    }

private:
    static std::unique_ptr<OffScreenTextButton> createRandomItem()
    {
        static const std::vector<juce::String> possibleItems {
            "Bell",
            "Book",
            "Bottle",
            "Bracelet",
            "Butter knife",
            "Can of paint",
            "Chalk",
            "Clay pot",
            "Dice",
            "Feather",
            "Fork",
            "Hair brush",
            "Hair pin",
            "Pack of cards",
            "Pair of glasses",
            "Paper",
            "Ribbon",
            "Sock",
            "Toy car",
            "Whistle",
        };

        auto& rng = juce::Random::getSystemRandom();
        const auto itemIndex = rng.nextInt (std::size (possibleItems));

        return std::make_unique<OffScreenTextButton> (possibleItems[itemIndex]);
    };

    class ContainerAccessibilityHandler : public juce::AccessibilityHandler
    {
    public:
        explicit ContainerAccessibilityHandler (juce::Component& component)
                : juce::AccessibilityHandler {component,
                                              juce::AccessibilityRole::group}
        {
        }

        juce::AccessibleState getCurrentState() const override
        {
            return juce::AccessibilityHandler::getCurrentState().withAccessibleOffscreen();
        }

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContainerAccessibilityHandler)
    };

    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler() override
    {
        return std::make_unique<ContainerAccessibilityHandler> (*this);
    }

    juce::OwnedArray<OffScreenTextButton> m_items;
};
