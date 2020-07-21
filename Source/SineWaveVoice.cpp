/*
  ==============================================================================

    SineWaveVoice.cpp
    Created: 19 Jul 2020 7:45:22pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "SineWaveVoice.h"
#include "SynthesiserSineSound.h"

SineWaveVoice::SineWaveVoice(){}

SineWaveVoice::~SineWaveVoice(){}
 
bool SineWaveVoice::canPlaySound (juce::SynthesiserSound* sound){
    return dynamic_cast<SynthesiserSineSound*>(sound) != nullptr;
}

void SineWaveVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition){
    
}

void SineWaveVoice::stopNote (float velocity, bool allowTailOff){
    
}

void SineWaveVoice::pitchWheelMoved (int newPitchWheelValue) {}
void SineWaveVoice::controllerMoved (int controllerNumber, int newControllerValue) {}
      
void SineWaveVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples){
    
}


