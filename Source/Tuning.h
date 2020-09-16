/*
  ==============================================================================

    Tuning.h
    Created: 2 Aug 2020 12:36:34pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <unordered_map>

class Tuning{
    
public:

    Tuning();
    Tuning(const juce::String& description, std::unordered_map<int, double> scaleMapping);
     ~Tuning();
    
    double getMidiNoteInHertz(const int midiNote,const int velocity, const double frequencyOfA );

private:
    juce::String description;
    std::unordered_map<int, double> scaleMapping;
};
