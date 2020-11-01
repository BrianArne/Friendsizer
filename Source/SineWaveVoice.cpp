/*
  ==============================================================================

    SineWaveVoice.cpp
    Created: 19 Jul 2020 7:45:22pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "SineWaveVoice.h"
#include "SineWavetable.h"
#include "Tuning.h"

SineWaveVoice::SineWaveVoice(){
    //tuning = tuningFactory.createTuning(Tuning::Tunings::equalTemperment);
}

SineWaveVoice::~SineWaveVoice(){}
 
bool SineWaveVoice::canPlaySound (juce::SynthesiserSound* sound){
    return dynamic_cast<AWaveTable*>(sound) != nullptr;
}

void SineWaveVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    wavetable.setIndex(0.0f);
    wavetable.setFrequency(440.0f, getSampleRate()); // change this to ScalaReader.getNoteInHertz()

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
        wavetable.setTableDelta(0.0f);
    }
}

void SineWaveVoice::pitchWheelMoved (int newPitchWheelValue) {}
void SineWaveVoice::controllerMoved (int controllerNumber, int newControllerValue) {}
      
void SineWaveVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    auto holder = wavetable.getTableDelta();
    if (wavetable.getTableDelta() != 0.0){
        if (tailOff > 0.0){
            while (--numSamples >= 0){
                auto currentSample = wavetable.getNextSample();
                
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                ++startSample;
                tailOff *= 0.99;
                std::cout << "TailOff Val: " << tailOff << std::endl;
                
                if (tailOff <= 0.005){
                    clearCurrentNote();
                    wavetable.setTableDelta(0.0f);
                    break;
                }
            }
        }else{
            while (--numSamples >= 0){
                auto currentSample = wavetable.getNextSample();
                
                for (auto i = outputBuffer.getNumChannels(); --i >=0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                ++startSample;
            }
        }
    }
}


