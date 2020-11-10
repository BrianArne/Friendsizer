/*
  ==============================================================================

    Tuning.cpp
    Created: 2 Aug 2020 12:36:34pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "Tuning.h"

Tuning::Tuning() {
    scaleMapping = {    {0 , 0.0},
                        {1 , 100.0f},
                        {2 , 200.0f},
                        {3 , 300.0f},
                        {4 , 400.0f},
                        {5 , 500.0f},
                        {6 , 600.0f},
                        {7 , 700.0f},
                        {8 , 800.0f},
                        {9 , 900.0f},
                        {10 , 1000.0f},
                        {11 , 1100.0f},
                        {12 , 2.0}};
                            
    description = "Standard Tuning";
    standardTuning = true;
}
 
Tuning::Tuning(const juce::String& desc, std::unordered_map<int, double> scaleMapping) : description(desc), scaleMapping(scaleMapping) {}

Tuning::~Tuning() {}

juce::String Tuning::getDescription()
{
    return description;
}

juce::String Tuning::getNotesPerScale()
{
    return juce::String(scaleMapping.size()-1);
}

juce::String Tuning::getCents()
{
    juce::String cents = "";
    for (auto& i : scaleMapping)
    {
        if (i.first != scaleMapping.size()-1){
            if (i.second == 0){
                cents = cents + "Root\n";
            }else{
                cents = cents + std::to_string(i.second) + "\n";
            }
        }
    }
    return cents;
}

juce::String Tuning::getFundamental()
{
    return juce::String(440.0f);
}

juce::String Tuning::getDetails()
{
    return getDescription() + juce::newLine + juce::newLine +
           getNotesPerScale() + juce::newLine + juce::newLine +
           getCents() + juce::newLine + juce::newLine +
           getFundamental();
    
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

std::string Tuning::getInformation()
{
    return std::string("Description: \n Cent Intervals: \n Fundamental: \n");
}

bool Tuning::isStandard()
{
    return standardTuning;
}

