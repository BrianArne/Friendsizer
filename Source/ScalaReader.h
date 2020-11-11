/*
  ==============================================================================

    ScalaReader.h
    Created: 24 Aug 2020 7:48:12am
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Tuning.h"

class ScalaReader{
    
public:
    ScalaReader();
    ~ScalaReader();
    
    Tuning createTuningMappings(const juce::File& file);
    
private:

};
