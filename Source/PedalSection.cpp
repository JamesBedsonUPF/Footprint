/*
  ==============================================================================

    PedalSection.cpp
    Created: 6 May 2023 2:06:57pm
    Author:  James Bedson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PedalSection.h"

//==============================================================================
PedalSection::PedalSection()
{
    activeComponents.resize(4);
    
    for (int componentIdx = 0; componentIdx < activeComponents.size(); componentIdx++){
        activeComponents[componentIdx] = std::make_unique<juce::ComboBox>();
        addAndMakeVisible(activeComponents[componentIdx].get());
    }
    
    
    
    addAndMakeVisible(compressorPedal);
    addAndMakeVisible(reverbPedal);
    addAndMakeVisible(envelopePedal);
    addAndMakeVisible(distortionPedal);

}

PedalSection::~PedalSection()
{
}

void PedalSection::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white.darker().darker());
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 15.0f, 1.0f);
    g.setColour(juce::Colours::transparentBlack);
    //g.fillRoundedRectangle(getLocalBounds().toFloat(), 15.0f);
    g.setFont (14.0f);
    g.setColour(juce::Colours::white);
    
    //paintDecor(g);
    
    
    g.drawRect(boxSlot1);
    g.drawRect(boxSlot2);
    g.drawRect(boxSlot3);
    g.drawRect(boxSlot4);
    

}

void PedalSection::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    
    compressorPedal.setSlot(1);
    distortionPedal.setSlot(2);
    reverbPedal.setSlot(3);
    envelopePedal.setSlot(4);
    
    int slotSizeWidth   = 200;
    int slotSizeHeight  = 300;
    
    juce::Point<int> slot1Centre(bounds.getX() + getWidth() * 0.25f - slotSizeWidth * 0.58f, bounds.getCentreY());
    juce::Point<int> slot2Centre(bounds.getX() + getWidth() * 0.5f - slotSizeWidth * 0.58f, bounds.getCentreY());
    juce::Point<int> slot3Centre(bounds.getX() + getWidth() * 0.75f - slotSizeWidth * 0.58f, bounds.getCentreY());
    juce::Point<int> slot4Centre(bounds.getX() + getWidth() - slotSizeWidth * 0.58f, bounds.getCentreY());
    
    pedalSlot1.setSize(slotSizeWidth, slotSizeHeight);
    pedalSlot1.setCentre(slot1Centre);
    
    pedalSlot2.setSize(slotSizeWidth, slotSizeHeight);
    pedalSlot2.setCentre(slot2Centre);
    
    pedalSlot3.setSize(slotSizeWidth, slotSizeHeight);
    pedalSlot3.setCentre(slot3Centre);
    
    pedalSlot4.setSize(slotSizeWidth, slotSizeHeight);
    pedalSlot4.setCentre(slot4Centre);
    
    boxSlot1.setSize(slotSizeWidth, slotSizeHeight * 0.5f);
    boxSlot1.setCentre(slot1Centre);
    
    boxSlot2.setSize(slotSizeWidth, slotSizeHeight * 0.5f);
    boxSlot2.setCentre(slot2Centre);
    
    boxSlot3.setSize(slotSizeWidth, slotSizeHeight * 0.5f);
    boxSlot3.setCentre(slot3Centre);
    
    boxSlot4.setSize(slotSizeWidth, slotSizeHeight * 0.5f);
    boxSlot4.setCentre(slot4Centre);
    
    /*
    compressorPedal.setBounds(pedalSlot4);
    envelopePedal.setBounds(pedalSlot1);
    reverbPedal.setBounds(pedalSlot3);
    distortionPedal.setBounds(pedalSlot2);*/
}

void PedalSection::paintDecor(juce::Graphics &g){
    
    juce::Line<float> line1 (juce::Point<float>((getLocalBounds().getWidth() * 0.25f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.25f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line2(juce::Point<float>((getLocalBounds().getWidth() * 0.5f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.5f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line3(juce::Point<float>((getLocalBounds().getWidth() * 0.75f) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth() * 0.75f) + 20.0f, getLocalBounds().getHeight() * 0.5f));
    juce::Line<float> line4(juce::Point<float>((getLocalBounds().getWidth()) - 17.0f, getLocalBounds().getHeight() * 0.5f), juce::Point<float>((getLocalBounds().getWidth()) + 50.0f, getLocalBounds().getHeight() * 0.5f));
    
    g.drawLine(line1, 2.0f);
    g.drawLine(line2, 2.0f);
    g.drawLine(line3, 2.0f);
    g.drawLine(line4, 2.0f);
    
}

void PedalSection::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged){
    
    for (int componentIdx = 0; componentIdx < activeComponents.size(); componentIdx++){
        auto& component = activeComponents[componentIdx];
        
        if (dynamic_cast<juce::ComboBox*>(component.get())){
            if (component.get() == comboBoxThatHasChanged){
                auto optionSelected = comboBoxThatHasChanged->getSelectedId();
                
                if (optionSelected == 1) { // Compressor
                    
                    auto compressorPedal = std::make_unique<CompressorPedal>();
                    activeComponents[componentIdx] = std::move(compressorPedal);
                    
                }
            }
        }
    }
}
