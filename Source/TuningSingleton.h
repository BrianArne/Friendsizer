/*
  ==============================================================================

    TuningSingleton.h
    Created: 1 Nov 2020 7:07:24pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include "Tuning.h"

class TuningSingleton {
    
public:
    TuningSingleton();
    ~TuningSingleton();
    
    static Tuning* instance(Tuning* tuning);
    static double getMidiNoteInHertz(const int midiNote,const int velocity, const double frequencyOfA );

private:
    static Tuning* _tuning;
};
