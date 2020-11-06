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
    createWaveTable();
}

SineWavetable::~SineWavetable(){}

bool SineWavetable::appliesToNote(int midiNoteNumber) { return true; }

bool SineWavetable::appliesToChannel(int midiChannel) { return true; }

/*
    Sets the size of the waveTable from the _tableSize. Writes samples from std::sin()
 */
void SineWavetable::createWaveTable()
{
     _wavetable.setSize (1, (int) _tableSize);
     auto* samples = _wavetable.getWritePointer (0);
    
     auto angleDelta = juce::MathConstants<double>::twoPi / (double) (_tableSize - 1);
     auto currentAngle = 0.0;
    
     for (unsigned int i = 0; i < _tableSize; ++i)
     {
         auto sample = std::sin (currentAngle);                                       // [5]
         samples[i] = (float) sample;
         currentAngle += angleDelta;
     }
}

const juce::AudioSampleBuffer* SineWavetable::getWavetable () { return &_wavetable; }

const float SineWavetable::getNextSample(WavetableState& state) noexcept
{
    auto tableSize = (unsigned int) _wavetable.getNumSamples();
    auto currentIndex = state.getCurrentIndex();
    
    auto index0 = (unsigned int) currentIndex;
    auto index1 = index0 == (tableSize - 1) ? (unsigned int) 0 : index0 + 1;
    
    auto frac = currentIndex - (float) index0;
    
    auto* table = _wavetable.getReadPointer (0);
    auto value0 = table[index0];
    auto value1 = table[index1];
    
    auto currentSample = value0 + frac * (value1 - value0);
    
    if((currentIndex += state.getTableDelta()) > (float) tableSize){
        state.setCurrentIndex(currentIndex - (float) tableSize);
    }else{
        state.setCurrentIndex(currentIndex);
    }
    
    return currentSample;

}


