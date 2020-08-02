/*
  ==============================================================================

    SynthesiserSineSound.h
    Created: 20 Jul 2020 7:31:55am
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct SineWavetable : public juce::SynthesiserSound
{
    SineWavetable();
    ~SineWavetable() override;
     
    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int midiChannel) override;
    
    //void createWaveTable();
    
    //void setFrequency(float frequency, float sampleRate);
    //float getNextSample() noexcept;
    
    //const unsigned int tableSize = 1 << 7;
    //float currentIndex = 0.0f, tableDelta = 0.0f, level = 0.0f;

    /* This is our wavetable. AudioSampleBuffer that gets filled with
    the correct samples by calling createWaveTable() */
    juce::AudioSampleBuffer wavetable;

};
