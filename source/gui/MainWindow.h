#include <juce_gui_basics/juce_gui_basics.h>

#include <model/GameState.h>
#include "Room1.h"
#include "Room2.h"

class MainWindow
    : public juce::Component
    , private GameState::Listener
{
public:
    explicit MainWindow (GameState& gameState)
        : m_room1 {gameState}
        , m_room2 {gameState}
    {
        setSize (1280, 720);

        addChildComponent (m_room1);
        addChildComponent (m_room2);

        gameState.addListener (*this);
        gameState.setRoomNumber (1);
    }

    ~MainWindow() override = default;

    void resized() override
    {
        m_room1.setBounds (getLocalBounds().translated (10000000, 0));
        m_room2.setBounds (getLocalBounds().translated (10000000, 0));
    }

private:
    void onRoomNumberChanged (int newRoomNum) final
    {
        m_room1.setVisible (newRoomNum == 1);
        m_room2.setVisible (newRoomNum == 2);
    }

    Room1 m_room1;
    Room2 m_room2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
