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
#include <string>

class Tuning{
    
public:
    
    Tuning();
    Tuning(const juce::String& description, std::unordered_map<int, double> scaleMapping);
     ~Tuning();
    
    double getMidiNoteInHertz(const int midiNote,const int velocity, const double frequencyOfA );
    std::string getInformation();
    
    juce::String getDescription();
    juce::String getNotesPerScale();
    juce::String getCents();
    juce::String getFundamental();
    juce::String getDetails();
    
    bool isStandard();

private:
    bool standardTuning;
    juce::String description;
    std::unordered_map<int, double> scaleMapping;
};
