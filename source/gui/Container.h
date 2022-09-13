#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Container : public juce::Component
{
public:
    explicit Container (int numItems)
    {
        setTitle ("Container");
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

    void add (std::unique_ptr<juce::TextButton> item)
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
            if (m_items[i]->getButtonText() == itemName)
                m_items.remove (i);
        }

        resized();
    }

private:
    static std::unique_ptr<juce::TextButton> createRandomItem()
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

        return std::make_unique<juce::TextButton> (possibleItems[itemIndex]);
    };

    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler() final
    {
        return std::make_unique<juce::AccessibilityHandler> (*this, juce::AccessibilityRole::group);
    }

    juce::OwnedArray<juce::TextButton> m_items;
};
