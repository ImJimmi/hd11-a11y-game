#pragma once

#include "Container.h"
#include "off-screen-components/OffScreenComboBox.h"
#include "off-screen-components/OffScreenComponent.h"
#include "off-screen-components/OffScreenLabel.h"
#include "off-screen-components/OffScreenSlider.h"
#include "off-screen-components/OffScreenTextButton.h"

#include <juce_gui_basics/juce_gui_basics.h>

class Room3 : public juce::Component {
public:
    Room3(GameState &gameState)
            : m_state {gameState}
    {
        m_puzzleDescription.innerComponent.setText ("You open the safe to find a handle which seems to fit in a slot next to the large sliding door.",
                juce::dontSendNotification);

        addAndMakeVisible(m_puzzleDescription);

        m_door.innerComponent.setButtonText ("Large sliding door, closed");
        m_door.innerComponent.onClick = [this] {
            if (m_state.getSlidingDoorIsOpen())
            {
                m_state.setRoomNumber (4);
            }
            else
            {
                m_door.getAccessibilityHandler()->notifyAccessibilityEvent (juce::AccessibilityEvent::titleChanged);
            }
        };
        addAndMakeVisible (m_door);

        m_handleSlot.innerComponent.setButtonText ("Handle slot, press to insert handle");
        m_handleSlot.innerComponent.onClick = [this] {
            m_handleSlot.innerComponent.setButtonText("Kerchunk, the handle fits in the slot and can be turned");
            m_handleSlot.getAccessibilityHandler()->notifyAccessibilityEvent (juce::AccessibilityEvent::titleChanged);

            m_crank.setVisible(true);
            m_crank.getAccessibilityHandler()->grabFocus();
        };

        addAndMakeVisible(m_handleSlot);

        m_crank.innerComponent.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
        m_crank.innerComponent.setRange (0.0, 50.0, 1.0);
        m_crank.innerComponent.setValue (0.0, juce::dontSendNotification);
        m_crank.innerComponent.setTitle ("Door crank");
        m_crank.setTitle ("Door crank");

        m_crank.innerComponent.onValueChange = [this]{
            if (m_crank.innerComponent.getValue() == 50.0)
            {
                m_state.setSlidingDoorIsOpen (true);
                m_handleSlot.setVisible (false);
                m_door.innerComponent.setButtonText ("Large sliding door, open!");
            }
            else
            {
                m_state.setSlidingDoorIsOpen (false);
            }
        };
        addChildComponent(m_crank);
    }

    ~Room3() override = default;

    void resized() override
    {
        auto bounds = juce::Rectangle<int> {100000, 0, 10000, 10000};
        m_puzzleDescription.setBounds(bounds.removeFromTop(50));
        m_door.setBounds (bounds.removeFromTop (50));
        m_handleSlot.setBounds(bounds.removeFromTop(50));
        m_crank.setBounds (bounds.removeFromTop (100).removeFromLeft (100));
    }

    void visibilityChanged() final
    {
        if (isShowing())
            m_puzzleDescription.getAccessibilityHandler()->grabFocus();
    }

    void parentHierarchyChanged() final
    {
        if (isShowing())
            m_puzzleDescription.getAccessibilityHandler()->grabFocus();
    }

private:
    OffScreenLabel m_puzzleDescription;
    OffScreenTextButton m_handleSlot;
    OffScreenSlider m_crank;
    OffScreenTextButton m_door;

    GameState &m_state;
};
