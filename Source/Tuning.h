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
    
    enum Status
    {
        Valid,      // Indicates valid .scl file
        Invalid,    // Indicates an invalid file type
        Malformed   // Indicates an invalid format to the .scl file
    };
    
    Tuning(Status);
    Tuning(const juce::String& description, std::unordered_map<int, double> scaleMapping, Status status);
     ~Tuning();
    
    const double getMidiNoteInHertz(const int midiNote,const int velocity, const double frequencyOfA );

    const juce::String getDescription();
    const juce::String getNotesPerScale();
    const juce::String getCents();
    const juce::String getFundamental();
    const Status getStatus();
    const bool isStandard();

private:
    Status _status;
    bool _standard;
    juce::String description;
    std::unordered_map<int, double> scaleMapping;
};
