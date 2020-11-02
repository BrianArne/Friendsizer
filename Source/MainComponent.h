#pragma once

#include <JuceHeader.h>
#include "ScalaReader.h"
#include "SynthAudioSource.h"
#include "TuningSingleton.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       public juce::FileBrowserListener,
                       private juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void timerCallback() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    void setMidiInput (int index);
    
    //==============================================================================
    void fileDoubleClicked (const juce::File& file) override;
    void selectionChanged() override;
    void fileClicked(const juce::File&, const juce::MouseEvent&) override;
    void browserRootChanged(const juce::File& newFile) override;


private:
    //==============================================================================
    // Synth Related
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;
    SynthAudioSource synthAudioSource;
    ScalaReader scalaReader;
    Tuning* tuning;

    // GUI Related
    juce::TextButton leftButton;
    juce::TextButton rightButton;
    juce::TextButton addSclButton;
    
    juce::ComboBox midiInputList;
    juce::Label midiInputListLabel;
    juce::ComboBox binaryTuningList;
    juce::Label binaryTuningListLabel;
    juce::FileBrowserComponent fileBrowser;

    int lastInputIndex = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
