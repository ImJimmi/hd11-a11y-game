#include <juce_gui_basics/juce_gui_basics.h>

#include <model/GameState.h>
#include "Room1.h"

class MainWindow : public juce::Component
{
public:
    explicit MainWindow (GameState& gameState)
        : m_room1 {gameState}
    {
        setSize (1280, 720);

        addAndMakeVisible (m_room1);
    }

    ~MainWindow() override = default;

    void resized() override
    {
//        m_room1.setBounds (getLocalBounds().translated (10000000, 0));
        m_room1.setBounds (getLocalBounds());
    }

private:
    Room1 m_room1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
