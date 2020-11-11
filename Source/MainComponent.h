#pragma once

#include <JuceHeader.h>
#include "ScalaReader.h"
#include "SynthAudioSource.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       public juce::FileBrowserListener,
                       public juce::Button::Listener,
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
    void buttonClicked (juce::Button* button) override;
    void buttonStateChanged (juce::Button* button) override;

    //==============================================================================
    void fileDoubleClicked (const juce::File& file) override;
    void selectionChanged() override;
    void fileClicked(const juce::File&, const juce::MouseEvent&) override;
    void updateDetails();
    void updateWarning(Tuning& tuning);
    void updateText(Tuning& tuning);
    void browserRootChanged(const juce::File& newFile) override;


private:
    //==============================================================================
    // Synth Related
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;
    SynthAudioSource synthAudioSource;
    ScalaReader scalaReader;

    // GUI Related
    juce::Label description;
    juce::TextButton stdTuningButton;
    
    juce::ComboBox midiInputList;
    juce::Label midiInputListLabel;
    juce::ComboBox binaryTuningList;
    juce::Label binaryTuningListLabel;
    juce::FileBrowserComponent fileBrowser;
    
    juce::TextEditor textContent;

    int lastInputIndex = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
