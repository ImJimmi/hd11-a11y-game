#pragma once

class GameState
{
public:
    struct Listener
    {
        virtual ~Listener() = default;

        virtual void onRoomNumberChanged (int newRoomNum) = 0;
    };

    GameState() = default;

    bool getPlayerHasKey() const
    {
        return m_playerHasKey;
    }

    void setPlayerHasKey (bool hasKey)
    {
        m_playerHasKey = hasKey;
    }

    void setRoomNumber (int roomNum)
    {
        m_roomNumber = roomNum;

        m_listeners.call ([this] (auto& listener) {
            listener.onRoomNumberChanged (m_roomNumber);
        });
    }

    void addListener (Listener& listener)
    {
        m_listeners.add (&listener);
    }

private:
    bool m_playerHasKey = false;
    int m_roomNumber {1};

    juce::ListenerList<Listener> m_listeners;
};
