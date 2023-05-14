/*
  ==============================================================================

    CompressorPedal.cpp
    Created: 14 May 2023 10:42:45am
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CompressorPedal.h"

//==============================================================================
CompressorPedal::CompressorPedal()
{
    for (auto& slider : sliders){
        addAndMakeVisible(slider);
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        //slider->setTextBoxStyle(<#TextEntryBoxPosition newPosition#>, <#bool isReadOnly#>, <#int textEntryBoxWidth#>, <#int textEntryBoxHeight#>)
    }

}

CompressorPedal::~CompressorPedal()
{
}

void CompressorPedal::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    juce::Rectangle<int> textBounds = getLocalBounds().withY(getHeight() * -0.4f); // Adjust the vertical position here
    g.drawText ("CompressorPedal", textBounds,
                juce::Justification::centred, true);   // draw some placeholder text

    /*
    juce::Rectangle<int> topLeft, topRight, bottomLeft, bottomRight, bypass;
    auto rectWidth = 10;
    auto rectHeight = 10;

    topLeft.setSize(rectWidth, rectHeight);
    topLeft.setCentre(sliderCol1CentreX, sliderRow1CentreY);

    topRight.setSize(rectWidth, rectHeight);
    topRight.setCentre(sliderCol3CentreX, sliderRow1CentreY);

    bottomLeft.setSize(rectWidth, rectHeight);
    bottomLeft.setCentre(sliderCol1CentreX, sliderRow2CentreY);

    bottomRight.setSize(rectWidth, rectHeight);
    bottomRight.setCentre(sliderCol3CentreX, sliderRow2CentreY);

    g.setColour(juce::Colours::white);
    g.drawEllipse(topLeft.toFloat(), 1.5f);

    g.setColour(juce::Colours::red);
    g.drawEllipse(topRight.toFloat(), 1.5f);

    g.setColour(juce::Colours::blue);
    g.drawEllipse(bottomLeft.toFloat(), 1.5f);

    g.setColour(juce::Colours::green);
    g.drawEllipse(bottomRight.toFloat(), 1.5f);

    juce::Rectangle<float> led;
    led.setSize(7, 7);
    led.setCentre(sliderCol2CentreX, bypassSwitch.getBounds().getY() - 0.08f * getHeight());
    g.fillEllipse(led);*/
}


void CompressorPedal::resizeChild(){
    
    for (auto& slider : sliders){
        slider->setSize(sliderWidth, sliderHeight);
    }
    
    threshold.setCentrePosition (sliderCol1CentreX, sliderRow1CentreY);
    ratio.setCentrePosition     (sliderCol1CentreX, sliderRow2CentreY);
    attack.setCentrePosition    (sliderCol3CentreX, sliderRow1CentreY);
    release.setCentrePosition   (sliderCol3CentreX, sliderRow2CentreY);
    
    
}
