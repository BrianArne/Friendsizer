#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    : synthAudioSource (keyboardState),
    keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    // GUI laybout
    leftButton.setButtonText("Left Button");
    rightButton.setButtonText("Right Button");
    addAndMakeVisible(keyboardComponent);
    //addAndMakeVisible(leftButton);
    //addAndMakeVisible(rightButton);
    addAndMakeVisible (midiInputList);
    midiInputListLabel.setText ("MIDI Input:", juce::dontSendNotification);
    midiInputListLabel.attachToComponent(&midiInputList, true);
    
    auto midiInputs = juce::MidiInput::getAvailableDevices();
    addAndMakeVisible(midiInputList);
    midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
    
    juce::StringArray midiInputNames;
    for (auto input : midiInputs)
        midiInputNames.add (input.name);
    
    midiInputList.addItemList (midiInputNames, 1);
    midiInputList.onChange = [this] { setMidiInput (midiInputList.getSelectedItemIndex());};
    
    for (auto input : midiInputs)
    {
        if (deviceManager.isMidiInputEnabled( input.identifier)){
            setMidiInput (midiInputs.indexOf (input));
            break;
        }
    }
    
    if (midiInputList.getSelectedId() == 0)
        setMidiInput(0);

    
    
    setSize (800, 600);
    
    
    
    // Audio
    setAudioChannels(0, 2);
    
    // Timer
    startTimer(400);

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    synthAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    synthAudioSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    synthAudioSource.releaseResources();
}

void MainComponent::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto r = getLocalBounds();
    //keyboardComponent.setBounds(r.removeFromBottom(100));
    leftButton.setBounds(r.removeFromLeft(150));
    rightButton.setBounds(r);
    
    midiInputList.setBounds (200, 10, getWidth() - 210, 20);
    keyboardComponent.setBounds (10, 40, getWidth() - 20, getHeight() - 50);
}

void MainComponent::setMidiInput (int index){
    auto list = juce::MidiInput::getAvailableDevices();
    
    deviceManager.removeMidiInputCallback (list[lastInputIndex].identifier, synthAudioSource.getMidiCollector());
    
    auto newInput = list[index];
    
    if (! deviceManager.isMidiInputEnabled (newInput.identifier))
        deviceManager.setMidiInputDeviceEnabled (newInput.identifier, true);
    
    deviceManager.addMidiInputDeviceCallback (newInput.identifier, synthAudioSource.getMidiCollector());
    midiInputList.setSelectedId (index + 1, juce::dontSendNotification);
    
    lastInputIndex = index;
    
}
