#include <juce_gui_basics/juce_gui_basics.h>

#include <model/GameState.h>

class MainWindow : public juce::Component
{
public:
    explicit MainWindow (GameState& gameState)
    {
        setSize (1280, 720);
    }

    ~MainWindow() override = default;

private:


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
