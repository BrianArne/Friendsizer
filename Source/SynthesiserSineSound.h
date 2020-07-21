/*
  ==============================================================================

    SynthesiserSineSound.h
    Created: 20 Jul 2020 7:31:55am
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once

struct SynthesiserSineSound : public juce::SynthesiserSound
{
    SynthesiserSineSound(){}
    
    bool appliesToNote (int midiNoteNumber) override {return true;}
    bool appliesToChannel (int midiChannel) override {return true;}
};
