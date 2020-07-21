/*
  ==============================================================================

    SynthAudioSource.cpp
    Created: 19 Jul 2020 7:13:04pm
    Author:  Brian Arne

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SynthAudioSource.h"
#include "SineWaveVoice.h"
#include "SynthesiserSineSound.h"

//==============================================================================
SynthAudioSource::SynthAudioSource(juce::MidiKeyboardState& keyState) : keyboardState( keyState )
{
    for (auto i = 0; i < 4; ++i){
        synth.addVoice(new SineWaveVoice());
    }
    synth.addSound(new SynthesiserSineSound());
}

SynthAudioSource::~SynthAudioSource()
{
}

void SynthAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
}

void SynthAudioSource::releaseResources()
{
    
}

void SynthAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    
}

