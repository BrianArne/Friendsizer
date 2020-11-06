/*
  ==============================================================================

    SineWaveVoice.cpp
    Created: 19 Jul 2020 7:45:22pm
    Author:  Brian Arne

  ==============================================================================
*/
#include <JuceHeader.h>
#include "SineWaveVoice.h"
#include "SineWavetable.h"
#include "Tuning.h"
#include "TuningSingleton.h"

SineWaveVoice::SineWaveVoice() : _sound(nullptr) {}

SineWaveVoice::~SineWaveVoice(){}
 
bool SineWaveVoice::canPlaySound (juce::SynthesiserSound* sound){
    return dynamic_cast<SineWavetable*>(sound) != nullptr;
}

void SineWaveVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    _sound = sound;
    SineWavetable* wavetableSound = dynamic_cast<SineWavetable*>(sound);
    _wavetableState.setCurrentIndex(0.0f);
    // TODO: Redesign wavetableSound so that it doesn't maintain it's own delta. Put in the State Class
    _wavetableState.setFrequency(TuningSingleton::getMidiNoteInHertz(midiNoteNumber, velocity, 440.0f), getSampleRate(), wavetableSound->getWavetable());

    _level = velocity * 0.15;
    _tailOff = 0.0;
}

void SineWaveVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff){
        if (_tailOff == 0.0)
            _tailOff = 1.0;
    }else{
        clearCurrentNote();
        _wavetableState.setTableDelta(0.0f);
    }
}

void SineWaveVoice::pitchWheelMoved (int newPitchWheelValue) {}
void SineWaveVoice::controllerMoved (int controllerNumber, int newControllerValue) {}
      
void SineWaveVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (_sound != nullptr){
      auto* wavetableSound = dynamic_cast<SineWavetable*>(_sound);
      if (_wavetableState.getTableDelta() != 0.0){
            if (_tailOff > 0.0){
                while (--numSamples >= 0){
                    auto currentSample = wavetableSound->getNextSample(_wavetableState);

                    for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample * _level);
                    ++startSample;
                    _tailOff *= 0.99;

                    if (_tailOff <= 0.005){
                        clearCurrentNote();
                        _wavetableState.setTableDelta(0.0f);
                        break;
                    }
                }
            }else{
                while (--numSamples >= 0){
                    auto currentSample = wavetableSound->getNextSample(_wavetableState);
        
                    for (auto i = outputBuffer.getNumChannels(); --i >=0;)
                        outputBuffer.addSample (i, startSample, currentSample * _level);
                    ++startSample;
                }
            }
        }
    }
}


