/*
  ==============================================================================

    ScalaReader.cpp
    Created: 24 Aug 2020 7:48:12am
    Author:  Brian Arne

  ==============================================================================
*/

#include "ScalaReader.h"

ScalaReader::ScalaReader(){}

ScalaReader::~ScalaReader(){}

Tuning* ScalaReader::createTuningMappings(const juce::File& file){
    
    if (file.getFileExtension() != ".scl")
        return nullptr;

    Tuning nullTuning;
    juce::String description;
    auto pitchCount = 0;

    // Init HashMappings
    std::unordered_map<int, double> scaleMapping;
    auto count = 0;
    scaleMapping.insert(std::make_pair(count, 0.0f));
    count++;

    if (!file.existsAsFile()){
        //return nullTuning;
        return nullptr;

    }
    juce::FileInputStream fstream(file);
    if (!fstream.openedOk()){
        //return nullTuning;
        return nullptr;
    }
    
    while( !fstream.isExhausted()){
        juce::String exclamaion = "!";
        juce::String slash = "/";
        auto line = fstream.readNextLine();
        if (line.startsWith(exclamaion)) continue;
        if (description.isEmpty())
        {
            description = line;
            continue;
        }
        if (pitchCount == 0 && description.isNotEmpty())
        {
            pitchCount = line.getIntValue();
            continue;
        }
        if (line.contains(slash)){
            auto slashIndex = line.indexOf(slash);
            if (slashIndex == -1) continue;
            auto numerator = line.substring(0, slashIndex).trim();
            auto denominator = line.substring(slashIndex+1).trim();
            scaleMapping.insert(std::make_pair(count, numerator.getDoubleValue() / denominator.getDoubleValue()));
            count++;
        }else{
            scaleMapping.insert(std::make_pair(count, line.getDoubleValue()));
            count++;
        }
    }
    return new Tuning(description, scaleMapping);
}
