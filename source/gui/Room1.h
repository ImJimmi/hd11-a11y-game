#pragma once

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
    }
    ~Room1() override = default;

    void resized() override
    {
        auto bounds = getLocalBounds();
        m_door.setBounds (bounds.removeFromTop (50).removeFromLeft (100));

    }

private:
    juce::TextButton m_door;

    GameState& m_state;
};
