/*
  ==============================================================================

    Tuning.cpp
    Created: 2 Aug 2020 12:36:34pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "Tuning.h"
#include <cstdlib>
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
    int distanceFromA = midiNote-69;
    int scaleDegree = distanceFromA % (int)(scaleMapping.size()-1);
    int octavesFromA = distanceFromA / (int)(scaleMapping.size() - 1);
    if (scaleDegree < 0){
        scaleDegree += (int)scaleMapping.size()-1;
        octavesFromA -= 1;
    }
    float octaveFundamental = 440.0f * std::pow(2, octavesFromA);
    if (scaleDegree == 0){
        return octaveFundamental;
    }else{
        return octaveFundamental * std::pow(2.0f, (scaleMapping[scaleDegree] / 1200.0f));
    }
}

