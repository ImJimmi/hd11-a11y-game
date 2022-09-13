#include <juce_gui_basics/juce_gui_basics.h>

#include <model/GameState.h>
#include "Room1.h"
#include "Room2.h"
#include "Room3.h"
#include "Room4.h"

class MainWindow
    : public juce::Component
    , private GameState::Listener
{
public:
    explicit MainWindow (GameState& gameState)
        : m_room1 {gameState}
        , m_room2 {gameState}
        , m_room3 {gameState}
    {
        setSize (500, 200);

        addChildComponent (m_room1);
        addChildComponent (m_room2);
        addChildComponent (m_room3);

        m_label.setText ("This game has no on screen visuals. Use your favourite screenreader to play!",
                         juce::dontSendNotification);
        m_label.setJustificationType (juce::Justification::centred);
        m_label.setAccessible (false;)
        addAndMakeVisible (m_label);

        gameState.addListener (*this);
        gameState.setRoomNumber (3);
    }

    ~MainWindow() override = default;

    void resized() override
    {
        m_label.setBounds (getLocalBounds());

        m_room1.setBounds (getLocalBounds().translated (10000000, 0));
        m_room2.setBounds (getLocalBounds().translated (10000000, 0));
        m_room3.setBounds (getLocalBounds().translated (10000000, 0));
    }

private:
    void onRoomNumberChanged (int newRoomNum) final
    {
        m_room1.setVisible (newRoomNum == 1);
        m_room2.setVisible (newRoomNum == 2);
        m_room3.setVisible (newRoomNum == 3);
    }

    Room1 m_room1;
    Room2 m_room2;
    Room3 m_room3;

    juce::Label m_label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
