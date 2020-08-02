/*
  ==============================================================================

    SynthesiserSineSound.cpp
    Created: 23 Jul 2020 7:25:49am
    Author:  Brian Arne

  ==============================================================================
*/

#include "SineWavetable.h"

SineWavetable::SineWavetable()
{
    //createWaveTable();
}

SineWavetable::~SineWavetable(){}

bool SineWavetable::appliesToNote(int midiNoteNumber) { return true; }

bool SineWavetable::appliesToChannel(int midiChannel) { return true; }

/*
// Fills the member wavetable with samples
void SineWavetable::createWaveTable()
{
    wavetable.setSize(1, (int) tableSize);
    auto* samples = wavetable.getWritePointer (0);
    
    auto angleDelta = juce::MathConstants<double>::twoPi / (double) (tableSize - 1);
    
    auto currentAngle = 0.0;
    
    for (unsigned int i = 0; i < tableSize; ++i)
    {
        auto sample = std::sin (currentAngle);
        samples[i] = (float) sample;
        currentAngle += angleDelta;
    }
}

// Wavetable implementation Later
void SineWavetable::setFrequency(float frequency, float sampleRate)
{
    auto tableSizeOverSampleRate = (float) wavetable.getNumSamples() / sampleRate;
    tableDelta = frequency * tableSizeOverSampleRate;
}

float SineWavetable::getNextSample() noexcept
{
    auto tableSize = (unsigned int) wavetable.getNumSamples();
    
    auto index0 = (unsigned int) currentIndex;
    auto index1 = index0 == (tableSize - 1) ? (unsigned int) 0 : index0 + 1;
    
    auto frac = currentIndex - (float) index0;
    
    auto* table = wavetable.getReadPointer (0);
    auto value0 = table[index0];
    auto value1 = table[index1];
    
    auto currentSample = value0 + frac * (value1 - value0);
    
    if((currentIndex += tableDelta) > (float) tableSize)
        currentIndex -= (float) tableSize;
    
    return currentSample;
    
}
 */


