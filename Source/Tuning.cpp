/*
  ==============================================================================

    Tuning.cpp
    Created: 2 Aug 2020 12:36:34pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "Tuning.h"
#include <unordered_map>

Tuning::Tuning()
{

}

Tuning::Tuning(const juce::String& desc, std::unordered_map<int, double> scaleMapping) : description(desc), scaleMapping(scaleMapping)
{

}

Tuning::~Tuning()
{
    
}

double Tuning::getMidiNoteInHertz(const int midiNote, const int velocity, const double frequencyOfA)
{
    return 0.0f;
}

