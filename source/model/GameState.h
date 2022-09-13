#pragma once

class GameState
{
public:
    GameState() = default;

    bool getPlayerHasKey() const
    {
        return m_playerHasKey;
    }

    void setPlayerHasKey (bool hasKey)
    {
        m_playerHasKey = hasKey;
    }

private:
    bool m_playerHasKey = false;
};
