/*
  ==============================================================================

    ARAverager.h
    Created: 21 May 2023 7:34:51pm
    Author:  James Bedson

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioProcessingModule.h"
#define MIN_TIME_CONST 0.000001

class ARAverager : AudioProcessingModule{
    
public:
    
    ARAverager();
    ~ARAverager() override;
    
    void prepare(double sampleRate, int samplesPerBlock, int numChannels) override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiMessages) override;
    
    void setAttack(std::atomic<float>* attack);
    void setRelease(std::atomic<float>* release);
    
private:
    std::atomic<float>*    attack;
    std::atomic<float>*    release;
    bool firstIteration;
    double                  alphaA, alphaR;
    double                  sampleRate;
    std::vector<float>      previousOuts;
    
    
};
