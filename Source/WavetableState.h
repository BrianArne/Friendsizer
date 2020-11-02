/*
  ==============================================================================

    WavetableState.h
    Created: 1 Nov 2020 12:43:43pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WavetableState {
    
public:
    WavetableState();
    ~WavetableState();

    float getTableDelta ();
    void setTableDelta (float delta);
    
    void setFrequency (float frequency, float sampleRate, juce::AudioSampleBuffer* buffer);
                                                          
    float getCurrentIndex();
    void setCurrentIndex (float index);

private:
    float _index, _tableDelta;
    
};
