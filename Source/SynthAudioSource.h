/*
  ==============================================================================

    SynthAudioSource.h
    Created: 19 Jul 2020 7:13:04pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SynthAudioSource  : public juce::AudioSource
{
public:
    SynthAudioSource(juce::MidiKeyboardState& keyState);
    ~SynthAudioSource() override;
    
    //=========================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;


private:
    juce::MidiKeyboardState &keyboardState;
    juce::Synthesiser synth;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioSource)
};
