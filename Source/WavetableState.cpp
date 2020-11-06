/*
  ==============================================================================

    WavetableState.cpp
    Created: 1 Nov 2020 12:43:43pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "WavetableState.h"

WavetableState::WavetableState() {}

WavetableState::~WavetableState() {}

float WavetableState::getTableDelta()
{
    return _tableDelta;
}

void WavetableState::setTableDelta (float tableDelta)
{
    _tableDelta = tableDelta;
}

void WavetableState::setFrequency (const float frequency, const float sampleRate, const juce::AudioSampleBuffer* buffer)
{
    auto tableSizeOverSampleRate = (float) buffer->getNumSamples() / sampleRate;
    _tableDelta = frequency * tableSizeOverSampleRate;
}

float WavetableState::getCurrentIndex()
{
    return _index;
}

void WavetableState::setCurrentIndex (float index)
{
    _index = index;
}
