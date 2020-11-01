/*
  ==============================================================================

    ScalaReader.cpp
    Created: 24 Aug 2020 7:48:12am
    Author:  Brian Arne

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ScalaReader.h"
#include "Tuning.h"

ScalaReader::ScalaReader(){}

//ScalaReader::ScalaReader(const juce::File& file) : file(file){}

ScalaReader::~ScalaReader(){}

Tuning ScalaReader::createTuningMappings(const juce::File& file){
    jassert(file.getFileExtension() == ".scl");
    
    Tuning nullTuning;
    juce::String description;
    auto pitchCount = 0;

    // Init HashMappings
    std::unordered_map<int, double> scaleMapping;
    auto count = 0;
    scaleMapping.insert(std::make_pair(count, 0.0f));
    count++;

    if (!file.existsAsFile()){
        return nullTuning;
    }
    juce::FileInputStream fstream(file);
    if (!fstream.openedOk()){
        return nullTuning;
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
    Tuning tuning(description, scaleMapping);
    
    std::cout << "0 index: " << tuning.getMidiNoteInHertz(0, 0, 440.0f) << std::endl;
    std::cout << "0 index: " << tuning.getMidiNoteInHertz(68, 0, 440.0f) << std::endl;
    std::cout << "0 index: " << tuning.getMidiNoteInHertz(67, 0, 440.0f) << std::endl;
    std::cout << "0 index: " << tuning.getMidiNoteInHertz(66, 0, 440.0f) << std::endl;
    std::cout << "0 index: " << tuning.getMidiNoteInHertz(65, 0, 440.0f) << std::endl;
    std::cout << "0 index: " << tuning.getMidiNoteInHertz(64, 0, 440.0f) << std::endl;
    std::cout << "0 index: " << tuning.getMidiNoteInHertz(63, 0, 440.0f) << std::endl;
    /*
    std::cout << "1 index: " << tuning.getMidiNoteInHertz(70, 0, 440.0f) << std::endl;
    std::cout << "2 index: " << tuning.getMidiNoteInHertz(71, 0, 440.0f) << std::endl;
    std::cout << "3 index: " << tuning.getMidiNoteInHertz(72, 0, 440.0f) << std::endl;
    std::cout << "4 index: " << tuning.getMidiNoteInHertz(73, 0, 440.0f) << std::endl;
    std::cout << "5 index: " << tuning.getMidiNoteInHertz(74, 0, 440.0f) << std::endl;
    std::cout << "0 next octave index: " << tuning.getMidiNoteInHertz(75, 0, 440.0f) << std::endl;
     */
    return tuning;
}
