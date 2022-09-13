#include <juce_gui_basics/juce_gui_basics.h>

class MainWindow : public juce::Component
{
public:
    explicit MainWindow ()
    {
        setSize (1280, 720);
    }

    ~MainWindow() override = default;

private:
    // juce::Component
    //======================================================================

    //======================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
