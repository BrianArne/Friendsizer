/*
  ==============================================================================

    AWaveTable.cpp
    Created: 30 Sep 2020 7:15:08am
    Author:  Brian Arne

  ==============================================================================
*/

#include "AWaveTable.h"

AWaveTable::AWaveTable()
{
    createWaveTable();
}

AWaveTable::~AWaveTable()
{
    
}

bool AWaveTable::appliesToNote( int midiNoteNumber)     { return true;}
bool AWaveTable::appliesToChannel( int midiNoteNumber)  { return true;}

void AWaveTable::createWaveTable(){
    // Allocate table and get a write pointer to it
    wavetable.setSize (1, (int) tableSize); // First Param = number of channels
    auto* samples = wavetable.getWritePointer (0);

    auto angleDelta = juce::MathConstants<double>::twoPi / (double) (tableSize - 1); // angleDelta is the increment we need to make for each index so that at the end of the table, it is 1 period of a sinewave
    auto currentAngle = 0.0; // initialization at 0.0 so that we can start adding to the table
 
    for (unsigned int i = 0; i < tableSize; ++i)
    {
        auto sample = std::sin (currentAngle);                                       // [5]
        samples[i] = (float) sample;
        currentAngle += angleDelta;
   }
}

void AWaveTable::setIndex (float index)
{
    currentIndex = index;
}

void AWaveTable::setFrequency(float frequency, float sampleRate)
{
    auto tableSizeOverSampleRate = (float) wavetable.getNumSamples() / sampleRate;
    tableDelta = frequency * tableSizeOverSampleRate;
}

void AWaveTable::setTableDelta(float tableDelta)
{
    tableDelta = tableDelta;
}

float AWaveTable::getTableDelta() noexcept
{
    return tableDelta;
}

float AWaveTable::getNextSample() noexcept
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
