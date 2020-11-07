/*
  ==============================================================================

    TuningSingleton.cpp
    Created: 1 Nov 2020 7:07:24pm
    Author:  Brian Arne

  ==============================================================================
*/
#include "TuningSingleton.h"

Tuning* TuningSingleton::_tuning = nullptr;

TuningSingleton::TuningSingleton() {}

TuningSingleton::~TuningSingleton() {
    if (TuningSingleton::_tuning != nullptr)
        delete TuningSingleton::_tuning;
}

Tuning* TuningSingleton::instance(Tuning* tuning)
{
    if (_tuning != nullptr) {
        return TuningSingleton::_tuning;
    }else{
        TuningSingleton::_tuning = tuning;
        return TuningSingleton::_tuning;
    }
}
double TuningSingleton::getMidiNoteInHertz(const int midiNote,const int velocity, const double frequencyOfA )
{
    if (_tuning == nullptr){
        return juce::MidiMessage::getMidiNoteInHertz (midiNote, frequencyOfA);
    }else{
        return TuningSingleton::_tuning->getMidiNoteInHertz (midiNote, velocity, frequencyOfA);
    }
}

