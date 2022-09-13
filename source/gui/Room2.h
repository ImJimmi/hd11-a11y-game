#pragma once

#include "Container.h"
#include "off-screen-components/OffScreenComboBox.h"
#include "off-screen-components/OffScreenComponent.h"
#include "off-screen-components/OffScreenLabel.h"
#include "off-screen-components/OffScreenTextButton.h"

#include <juce_gui_basics/juce_gui_basics.h>

juce::String generateRandomFourDigitPassCode()
{
    auto& rng = juce::Random::getSystemRandom();

    juce::String result;

    for (auto i = 0; i < 4; i++)
    {
        result += juce::String {rng.nextInt (10)};
    }

    return result;
}

class Room2 : public juce::Component
{
public:
    Room2 (GameState& gameState)
        : m_state {gameState}
        , m_comboLockPassCode {generateRandomFourDigitPassCode()}
    {
        m_puzzleDescription.innerComponent.setText ("You leave the first room through the unlocked door. In the garage outside, there is a safe in with a combination lock. Maybe the code is around here somewhere?", juce::dontSendNotification);
        addAndMakeVisible (m_puzzleDescription);

        m_safe.innerComponent.setButtonText ("Safe: Locked.");
        m_safe.innerComponent.setHelpText ("Enter the right combination to the lock, then press this button.");
        m_safe.innerComponent.onClick = [this] {
            juce::String currentCode;

            for (auto* const number : m_comboLockNumbers)
                currentCode += number->innerComponent.getText();

            if (currentCode == m_comboLockPassCode)
            {
                m_state.setRoomNumber (3);
            }
            else
            {
                m_safe.getAccessibilityHandler()->notifyAccessibilityEvent (juce::AccessibilityEvent::titleChanged);
            }
        };
        addAndMakeVisible (m_safe);

        m_comboLock.setFocusContainerType (FocusContainerType::focusContainer);
        m_comboLock.setTitle ("Combination lock");
        addAndMakeVisible (m_comboLock);

        auto& rng = juce::Random::getSystemRandom();

        for (auto i = 0; i < 4; i++)
        {
            auto* number = m_comboLockNumbers.add (std::make_unique<OffScreenComboBox>());

            for (auto j = 0; j < 10; j++)
                number->innerComponent.addItem (juce::String {j}, j + 1);

            number->innerComponent.setSelectedItemIndex (rng.nextInt (10));
            number->innerComponent.setAlpha (0.0f);

            m_comboLock.addAndMakeVisible (*number);
        }

        static const std::vector<juce::String> possibleClues {
            "A poster on the wall of David Bowie",
            "A Rubik's Cube, unsolved",
            "A clock on the desk - 3:15pm",
            "The 8 of clubs and King of hearts",
            "A creepy doll, its eyes ever watching",
            "78 grains of rice",
            "The third season of Game of Thrones box set",
            "Twenty Thousand Leagues Under the Seas, by Jules Verne",
            "The Holy Grain",
            "98 bottles of beer on a wall - broken glass at your feet",
            "A Green Bay Packer's jersey signed by Aaron Rodgers, number 12",
            "A printed document titled \"Nuclear Launch Codes\" - the code is Up Up Down Down Left Right Left Right B A Start",
        };

        std::unordered_set<int> indices;

        while (indices.size() < 7)
            indices.insert (rng.nextInt (possibleClues.size()));

        for (const auto index : indices)
            addAndMakeVisible (m_clues.add (std::make_unique<OffScreenLabel> (possibleClues[index])));

        juce::String finalClue = "A hastily written note, you make out the number " + m_comboLockPassCode;
        addAndMakeVisible (m_clues.insert (rng.nextInt (m_clues.size() + 1),
                                           std::make_unique<OffScreenLabel> (finalClue)));
    }

    ~Room2() override = default;

    void resized() override
    {
        auto bounds = getLocalBounds();
        m_puzzleDescription.setBounds (bounds.removeFromTop (50));

        m_safe.setBounds (bounds.removeFromTop (50).removeFromLeft (100));

        m_comboLock.setBounds (bounds.removeFromTop (50).removeFromLeft (400));

        for (auto* const number : m_comboLockNumbers)
        {
            static auto lockBounds = m_comboLock.getLocalBounds();
            number->setBounds (lockBounds.removeFromLeft (100));
        }

        for (auto* const clue : m_clues)
        {
            clue->setBounds (bounds.removeFromTop (25));
        }
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
    OffScreenTextButton m_safe;

    OffScreenComponent m_comboLock;
    juce::OwnedArray<OffScreenComboBox> m_comboLockNumbers;
    const juce::String m_comboLockPassCode;

    juce::OwnedArray<OffScreenLabel> m_clues;

    GameState& m_state;
};
