/*
  ==============================================================================

    SineWaveVoice.h
    Created: 19 Jul 2020 7:45:22pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AWaveTable.h"
#include "Tuning.h"

class SineWaveVoice : public juce::SynthesiserVoice
{
public:
    SineWaveVoice(); // Equal Temperment Constructor
    //SineWaveVoice(Tuning::Tunings tuning);
    ~SineWaveVoice() override;
    
    //=========================================================
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    
    //=========================================================
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    
    //=========================================================

    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
private:
    // Level might be changed by GUI, tailOff is for startNote and stopNote
    double level = 0.0, tailOff = 0.0;
    
    // This we might allow for changing, but for now std tuning
    double fundamental = 440.0;
    
    // Add ownership of a wavetable? Init in the constuctor?
    AWaveTable wavetable;
   
    std::unique_ptr<Tuning> tuning; // I think we can remove tuning;
};
