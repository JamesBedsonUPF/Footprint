/*
  ==============================================================================

    EnvelopePedal.cpp
    Created: 14 May 2023 10:43:40am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopePedal.h"

//==============================================================================
EnvelopePedal::EnvelopePedal()
{
    for (auto& slider : sliders){
        addAndMakeVisible(slider);
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    }
}

EnvelopePedal::~EnvelopePedal()
{
}

void EnvelopePedal::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.43f); // Adjust the vertical position here
    g.drawText ("EnvelopePedal", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text
    
    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.08f * getHeight());
    g.fillEllipse(led);
}

void EnvelopePedal::resizeChild(){
    
    for (auto& slider : sliders){
        slider->setSize(sliderWidth, sliderHeight);
    }
    
    sensitivity.setCentrePosition(sliderCol1CentreX, sliderRow1CentreY);
    qualityFactor.setCentrePosition(sliderCol2CentreX, sliderRow2CentreY);
    cutoffThreshold.setCentrePosition(sliderCol3CentreX, sliderRow1CentreY);
}

