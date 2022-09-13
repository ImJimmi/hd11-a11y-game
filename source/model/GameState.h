#pragma once

class GameState
{
public:
    GameState() = default;

    bool getPlayerHasKey() const
    {
        return m_playerHasKey;
    }

private:
    bool m_playerHasKey = false;
};
