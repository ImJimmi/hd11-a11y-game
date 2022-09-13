#pragma once

#include "Container.h"

#include <juce_gui_basics/juce_gui_basics.h>

class Room1 : public juce::Component
{
public:
    Room1 (GameState& gameState)
        : m_state {gameState}
    {
        m_door.setButtonText ("Door: Locked, look for a key!");

        m_door.onClick = [this] {
            if (m_state.getPlayerHasKey())
            {
                m_door.setVisible (false);
            }

            else
            {
                m_door.getAccessibilityHandler()->notifyAccessibilityEvent (juce::AccessibilityEvent::titleChanged);
            }
        };

        addAndMakeVisible (m_door);

        auto& rng = juce::Random::getSystemRandom();

        for (auto i = 0; i < 3; i++)
        {
            auto* container = m_containers.add (std::make_unique<Container> (rng.nextInt ({2, 5})));
            addAndMakeVisible (*container);
        }

        auto key = std::make_unique<juce::TextButton> ("Key");
        auto* const containerWithKey = m_containers.getUnchecked (rng.nextInt (m_containers.size()));
        key->onClick = [this, containerWithKey, pKey = key.get()]() {
            m_state.setPlayerHasKey (true);
            containerWithKey->remove (pKey->getButtonText());
        };
        containerWithKey->add (std::move (key));
    }
    ~Room1() override = default;

    void resized() override
    {
        auto bounds = getLocalBounds();
        m_door.setBounds (bounds.removeFromTop (50).removeFromLeft (100));

        for (auto* const container : m_containers)
        {
            container->setBounds (bounds.removeFromTop (50));
        }
    }

private:
    juce::TextButton m_door;
    juce::OwnedArray<Container> m_containers;

    GameState& m_state;
};
