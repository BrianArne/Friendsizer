/*
  ==============================================================================

    SineWaveVoice.cpp
    Created: 19 Jul 2020 7:45:22pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "SineWaveVoice.h"
#include "SineWavetable.h"
#include "AWaveTable.h"
#include "Tuning.h"
#include "TuningSingleton.h"

SineWaveVoice::SineWaveVoice(){
    //tuning = tuningFactory.createTuning(Tuning::Tunings::equalTemperment);
}

SineWaveVoice::~SineWaveVoice(){}
 
bool SineWaveVoice::canPlaySound (juce::SynthesiserSound* sound){
    return dynamic_cast<AWaveTable*>(sound) != nullptr;
}

void SineWaveVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    _sound = sound;
    AWaveTable* wavetableSound = dynamic_cast<AWaveTable*>(sound);
    wavetableState.setCurrentIndex(0.0f);
    //wavetableState.setFrequency(440.0f, getSampleRate(), wavetableSound->getWavetable()); // change this to ScalaReader.getNoteInHertz()

    wavetableState.setFrequency(TuningSingleton::getMidiNoteInHertz(midiNoteNumber, velocity, 440.0f), getSampleRate(), wavetableSound->getWavetable()); // change this to ScalaReader.getNoteInHertz()

    level = velocity * 0.15;
    tailOff = 0.0;
}

void SineWaveVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff){
        if (tailOff == 0.0)
            tailOff = 1.0;
    }else{
        clearCurrentNote();
        wavetableState.setTableDelta(0.0f);
    }
}

void SineWaveVoice::pitchWheelMoved (int newPitchWheelValue) {}
void SineWaveVoice::controllerMoved (int controllerNumber, int newControllerValue) {}
      
void SineWaveVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    auto* wavetableSound = dynamic_cast<AWaveTable*>(_sound);
    if (wavetableState.getTableDelta() != 0.0){
        if (tailOff > 0.0){
            while (--numSamples >= 0){
               // auto currentSample = wavetableSound->getNextSample(wavetableState.getCurrentIndex(), wavetableState.getTableDelta());
                
                auto currentSample = wavetableSound->getNextSample(wavetableState);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                ++startSample;
                tailOff *= 0.99;

                if (tailOff <= 0.005){
                    clearCurrentNote();
                    wavetableState.setTableDelta(0.0f);
                    break;
                }
            }
        }else{
            while (--numSamples >= 0){
                auto currentSample = wavetableSound->getNextSample(wavetableState);
                                      
                for (auto i = outputBuffer.getNumChannels(); --i >=0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                ++startSample;
            }
        }
    }
}


