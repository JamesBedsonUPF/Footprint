/*
  ==============================================================================

    ControlSection.cpp
    Created: 6 May 2023 2:06:39pm
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ControlSection.h"

//==============================================================================
ControlSection::ControlSection(FootprintAudioProcessor* p)
: inputAttachment       (p->apvts, ProcessingConstants::EditorControls::Identifiers::inputGainParam, input),
outputAttachment        (p->apvts, ProcessingConstants::EditorControls::Identifiers::outputGainParam, output),
monoSwitchAttachment    (p->apvts, ProcessingConstants::EditorControls::Identifiers::monoStereoParam, monoStereoSwitch)
{
    monoStereoSwitch.setMouseCursor(juce::MouseCursor::StandardCursorType::PointingHandCursor);
    for (auto& slider : sliders) {
        addAndMakeVisible(slider);
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
        slider->setLookAndFeel(&lookAndFeel);
    }

    for (auto& label : sliderLabels) {
        addAndMakeVisible(label);
        label->setJustificationType(juce::Justification::horizontallyCentred);
    }

    monoStereoSwitch.setLookAndFeel(&lookAndFeel);

    addAndMakeVisible(monoStereoSwitch);
    //toggle.setLookAndFeel(&lookAndFeel);
    
    //switchLabel.setJustificationType(juce::Justification::centred);
    
    inputLabel.attachToComponent(&input, false);
    outputLabel.attachToComponent(&output, false);

    juce::Font font;
    font.setHeight(GUIAttributes::ControlFontSizes::h2);
    font.setTypefaceName("Futura");
    inputLabel.setFont(font);
    outputLabel.setFont(font);
    //switchLabel.setFont(font);

    inputLabel.setText("Input", juce::dontSendNotification);
    outputLabel.setText("Output", juce::dontSendNotification);
    
    
    addAndMakeVisible(switchLabel);
    switchLabel.setJustificationType(juce::Justification::centred);
    switchLabel.attachToComponent(&monoStereoSwitch, false);
    switchLabel.setFont(font);
    
    //juce::Button::Listener::buttonStateChanged(&toggle);
    
    /*if (toggle.getToggleState()){
        switchLabel.setText("Mono", juce::dontSendNotification);
    }else{
        switchLabel.setText("Stereo", juce::dontSendNotification);
    }*/
    
}

ControlSection::~ControlSection()
{
    for (auto* slider : sliders){
        slider->setLookAndFeel(nullptr);
    }
    monoStereoSwitch.setLookAndFeel(nullptr);
}

void ControlSection::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    paintDecor(g);

    
    if (monoStereoSwitch.getToggleState()){
        switchLabel.setText("Stereo", juce::dontSendNotification);
    }
    else {
        switchLabel.setText("Mono", juce::dontSendNotification);
    }
}

void ControlSection::resized()
{
    auto bounds       = getBounds();
    auto width        = getWidth();
    auto height       = getHeight();
    sliderCol1CentreX = getX() + width * 0.25f;
    sliderRow1CentreY = getY() + height * 0.45f;
    sliderCol2CentreX = getX() + width * 0.71f;
    sliderRow2CentreY = getY() + height * 0.685f;
    auto toggleRowCentreX  = getX() + width * 0.25f;
    auto toggleRowCentreY  = getY() + height * 0.72f;

    sliderWidth       = 75;
    sliderHeight      = 75;
    
    toggleWidth       = 55;
    toggleHeight      = 20;

    sliderLabelWidth  = sliderWidth;
    sliderLabelHeight = 15;

    toggleLabelWidth  = toggleWidth;
    toggleLabelHeight = 20;
    
    for (auto& slider : sliders) {
        slider->setSize(sliderWidth, sliderHeight);
    }

    input.setCentrePosition(sliderCol1CentreX, sliderRow1CentreY);
    output.setCentrePosition(sliderCol2CentreX, sliderRow2CentreY);

    for (auto& label : sliderLabels) {

        auto sliderBounds = label->getAttachedComponent()->getBounds();
        auto bottomX = sliderBounds.getBottomLeft().getX();
        auto bottomY = sliderBounds.getBottomLeft().getY();

        label->setBounds(bottomX, bottomY, sliderLabelWidth, sliderLabelHeight);
    }
    
    //toggle.setBounds(width * 0.20f ,height * 0.65f , toggleWidth, toggleHeight);
    monoStereoSwitch.setSize(toggleWidth, toggleHeight);
    monoStereoSwitch.setCentrePosition(toggleRowCentreX, toggleRowCentreY + 35.f);
    
    auto switchBounds = switchLabel.getAttachedComponent()->getBounds();
    auto bottomX = switchBounds.getBottomLeft().getX();
    auto bottomY = switchBounds.getBottomLeft().getY();
    switchLabel.setBounds(bottomX, bottomY, toggleLabelWidth, toggleLabelHeight);
}

void ControlSection::paintDecor(juce::Graphics& g) {

    juce::Line<float> line1(juce::Point<float>((getLocalBounds().getWidth() * (-1.0f)), getLocalBounds().getHeight() * 0.45f), juce::Point<float>((getLocalBounds().getWidth() * (0.07f)), getLocalBounds().getHeight() * 0.45f));
    juce::Line<float> line2(juce::Point<float>((getLocalBounds().getWidth() * 0.5f) - 22.0f, getLocalBounds().getHeight() * 0.87f), juce::Point<float>((getLocalBounds().getWidth() * 0.5f) + 16.0f, getLocalBounds().getHeight() * 0.87f));
    //juce::Line<float> line3(juce::Point<float>((getLocalBounds().getWidth() * 0.75f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.75f) + 20.0f, getLocalBounds().getHeight() * 0.5f));


    g.drawLine(line1, 2.0f);
    g.drawLine(line2, 2.0f);
    //g.drawLine(line3, 2.0f);


}

void ControlSection::buttonClicked(juce::Button* button)
{
    if (button == &monoStereoSwitch)
    {
        repaint();
    }
}

