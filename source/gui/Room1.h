#pragma once

#include "Container.h"
#include "off-screen-components/OffScreenLabel.h"
#include "off-screen-components/OffScreenTextButton.h"

#include <juce_gui_basics/juce_gui_basics.h>

class Room1 : public juce::Component
{
public:
    Room1 (GameState& gameState)
        : m_state {gameState}
    {
        m_puzzleDescription.innerComponent.setText ("You are in a room filled with boxes with a locked door. The door looks like it needs a key to unlock. Maybe it's hidden somewhere in the room?", juce::dontSendNotification);
        addAndMakeVisible (m_puzzleDescription);

        m_door.innerComponent.setButtonText ("Door: Locked, look for a key!");
        m_door.innerComponent.onClick = [this] {
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

        auto key = std::make_unique<OffScreenTextButton> ("Key");
        auto* const containerWithKey = m_containers.getUnchecked (rng.nextInt (m_containers.size()));
        key->innerComponent.onClick = [this, containerWithKey, pKey = key.get()]() {
            m_state.setPlayerHasKey (true);
            pKey->innerComponent.setButtonText ("Key, collected.");
            pKey->getAccessibilityHandler()->notifyAccessibilityEvent (juce::AccessibilityEvent::titleChanged);

            m_door.innerComponent.setButtonText ("Door, press to unlock with key.");
            m_door.getAccessibilityHandler()->notifyAccessibilityEvent (juce::AccessibilityEvent::titleChanged);
//            containerWithKey->remove (pKey->getButtonText());
        };
        containerWithKey->add (std::move (key));
    }

    ~Room1() override = default;

    void resized() override
    {
        auto bounds = getLocalBounds();
        m_puzzleDescription.setBounds (bounds.removeFromTop(50));

        m_door.setBounds (bounds.removeFromTop (50).removeFromLeft (100));

        for (auto* const container : m_containers)
        {
            container->setBounds (bounds.removeFromTop (50));
        }
    }

private:
    OffScreenLabel m_puzzleDescription;
    OffScreenTextButton m_door;
    juce::OwnedArray<Container> m_containers;

    GameState& m_state;
};
