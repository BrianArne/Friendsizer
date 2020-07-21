/*
  ==============================================================================

    SineWaveVoice.h
    Created: 19 Jul 2020 7:45:22pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SineWaveVoice : public juce::SynthesiserVoice
{
public:
    SineWaveVoice();
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
};
