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
/*
SineWaveVoice::SineWaveVoice(Tuning::Tunings tuningEnum){
    //tuning = tuningFactory.createTuning(tuningEnum);
}
 */

SineWaveVoice::~SineWaveVoice(){}
 
bool SineWaveVoice::canPlaySound (juce::SynthesiserSound* sound){
    return dynamic_cast<SineWavetable*>(sound) != nullptr;
}

void SineWaveVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    currentAngle = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;
    
    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber, velocity);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();
    
    angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
}

void SineWaveVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff){
        if (tailOff == 0.0)
            tailOff = 1.0;
            
    }else{
        clearCurrentNote();
        angleDelta = 0.0;
    }
    
}

void SineWaveVoice::pitchWheelMoved (int newPitchWheelValue) {}
void SineWaveVoice::controllerMoved (int controllerNumber, int newControllerValue) {}
      
void SineWaveVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (angleDelta != 0.0){
        if (tailOff > 0.0){
            while (--numSamples >= 0){
                auto currentSample = (float) (std::sin (currentAngle) * level * tailOff);
                
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                
                currentAngle += angleDelta;
                ++startSample;
                
                tailOff *= 0.99;
                
                if (tailOff <= 0.005){
                    clearCurrentNote();
                    
                    angleDelta = 0.0;
                    break;
                }
            }
        }else{
            while (--numSamples >= 0){
                auto currentSample = (float) (std::sin (currentAngle) * level);
                
                for (auto i = outputBuffer.getNumChannels(); --i >=0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                currentAngle += angleDelta;
                ++startSample;
            }
        }
    }
    
}


