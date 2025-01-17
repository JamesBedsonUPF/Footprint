/*
  ==============================================================================

    PedalLookAndFeel.h
    Created: 14 May 2023 10:43:50am
    Author:  James Bedson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PedalLookAndFeel  : public juce::LookAndFeel_V4
{
public:
    PedalLookAndFeel();
    ~PedalLookAndFeel() override;

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                           juce::Slider&) override;

    void drawToggleButton(juce::Graphics&, juce::ToggleButton&, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
private:

    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PedalLookAndFeel)
};
