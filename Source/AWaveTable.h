/*
  ==============================================================================

    AWaveTable.h
    Created: 30 Sep 2020 7:15:08am
    Author:  Brian Arne

  ==============================================================================
 */

#pragma once
#include <JuceHeader.h>
#include "WavetableState.h"

class AWaveTable : public juce::SynthesiserSound{
    
public:
    
    AWaveTable();
    ~AWaveTable() override;
    
    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int midiChannel) override;
    
    void createWaveTable();
   
    /*
    void setIndex (float index);
    void setFrequency (float frequency, float sampleRate);
    void setTableDelta (float tableDelta);
    float getTableDelta () noexcept;
     */
    float getNextSample (WavetableState& state) noexcept;
    
    juce::AudioSampleBuffer* getWavetable ();
    
private:
    const unsigned int tableSize = 2048;
    juce::AudioSampleBuffer wavetable;

    
};
