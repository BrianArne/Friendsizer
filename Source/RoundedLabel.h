/*
  ==============================================================================

    RoundedLabels.h
    Created: 8 Nov 2020 3:55:28pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class RoundedLabel : public juce::LookAndFeel_V4
{
    
public:
    RoundedLabel();
    ~RoundedLabel();
    
    void drawLabel (juce::Graphics& g, juce::Label& label);

private:

};
