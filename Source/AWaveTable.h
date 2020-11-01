/*
  ==============================================================================

    AWaveTable.h
    Created: 30 Sep 2020 7:15:08am
    Author:  Brian Arne

  ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

class AWaveTable : public juce::SynthesiserSound{
    
public:
    
    AWaveTable();
    ~AWaveTable() override;
    
    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int midiChannel) override;
    
    void createWaveTable();
    
    void setIndex (float index);
    void setFrequency (float frequency, float sampleRate);
    void setTableDelta (float tableDelta);
    float getTableDelta () noexcept;
    float getNextSample () noexcept;
    
private:

    const unsigned int tableSize = 2048;
    // Removed level as it is probably better suited to the Voice not the WaveTable
    float currentIndex = 0.0f, tableDelta = 0.0f;
    
    juce::AudioSampleBuffer wavetable;

    
};


/*
 1) How do we determine the wavetable size?
    * Ideal table size is the frequency you want to play / number of samples;
        440.0f/sampleSize;
 2) What is the table Delta?
 3) What is the angelDelta?
 4) What is the currentAngle?
 5) What is the phaseAccumulator?
 6) What is the phaseIncrement?
 
 
 
 */
