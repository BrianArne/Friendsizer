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
#include "SineWavetable.h"

//==============================================================================
SynthAudioSource::SynthAudioSource(juce::MidiKeyboardState& keyState) : keyboardState( keyState )
{
    for (auto i = 0; i <= 5; ++i){
        synth.addVoice(new SineWaveVoice());
    }
    synth.addSound(new SineWavetable());
}

SynthAudioSource::~SynthAudioSource()
{
    
}

void SynthAudioSource::setUsingSineWaveSounds()
{
    synth.clearSounds();
}

void SynthAudioSource::prepareToPlay(int /*samplesPerBlockExpectedi*/, double sampleRate)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
    midiCollector.reset (sampleRate);
}

void SynthAudioSource::releaseResources()
{
    
}

void SynthAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    
    juce::MidiBuffer incomingMidi;
    midiCollector.removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples);
    
    keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample, bufferToFill.numSamples, true);
    
    synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, bufferToFill.startSample, bufferToFill.numSamples);
    
}

juce::MidiMessageCollector* SynthAudioSource::getMidiCollector()
{
    return &midiCollector;
}

