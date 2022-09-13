#pragma once

#include "off-screen-components/OffScreenLabel.h"

#include <juce_gui_basics/juce_gui_basics.h>

class Room4 : public juce::Component
{
public:
    Room4 ()
    {
        m_puzzleDescription.innerComponent.setText ("Congratulations, you escaped!", juce::dontSendNotification);
        addAndMakeVisible (m_puzzleDescription);
    }

    ~Room4() override = default;

    void resized() override
    {
        auto bounds = getLocalBounds();
        m_puzzleDescription.setBounds (bounds.removeFromTop(50));
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
};
