/*
  ==============================================================================

    SynthesiserSineSound.h
    Created: 20 Jul 2020 7:31:55am
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "WavetableState.h"

class SineWavetable : public juce::SynthesiserSound
{
public:
    SineWavetable();
    ~SineWavetable() override;
     
    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int midiChannel) override;
    
    void createWaveTable();
    const juce::AudioSampleBuffer* getWavetable();
    const float getNextSample (WavetableState& state) noexcept;
    
private:
    const unsigned int _tableSize = 2048;
    juce::AudioSampleBuffer _wavetable;

};
