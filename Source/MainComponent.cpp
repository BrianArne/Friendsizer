#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    : keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
    synthAudioSource (keyboardState),
    fileBrowser(juce::FileBrowserComponent::FileChooserFlags::openMode |
                juce::FileBrowserComponent::FileChooserFlags::canSelectFiles |
                juce::FileBrowserComponent::FileChooserFlags::useTreeView,
                juce::File("/"), nullptr, nullptr)
                  
{
    // GUI laybout
    

    // List Box is what we want to list Binary Data Scala files
    // ListBox, ListBoxModel,
    leftButton.setButtonText("Left Button");
    rightButton.setButtonText("Right Button");
    addSclButton.setButtonText("Add User Scala File");
    addAndMakeVisible(keyboardComponent);
    addAndMakeVisible(addSclButton);
    addAndMakeVisible(fileBrowser);
    fileBrowser.addListener(this);
    addAndMakeVisible(rightButton);
    addAndMakeVisible(addSclButton);
    
    
    //Midi ComboBox
    midiInputListLabel.setText ("MIDI Input:", juce::dontSendNotification);
    midiInputListLabel.attachToComponent(&midiInputList, true);
    auto midiInputs = juce::MidiInput::getAvailableDevices();
    addAndMakeVisible(midiInputList);
    midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
    
    // Tuning Combo Box
    addAndMakeVisible (binaryTuningList);
    binaryTuningListLabel.setText("Tuning:", juce::dontSendNotification);
    binaryTuningListLabel.attachToComponent(&binaryTuningList, true);
    binaryTuningList.setTextWhenNothingSelected("No Tuning Selected");


    
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
    fileBrowser.removeListener(this);
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
    auto r = getLocalBounds().removeFromBottom(getHeight()-50);
    midiInputList.setBounds (200, 10, getWidth() - 210, 20);
    
    auto tuningBounds = r.removeFromLeft(r.getWidth()/4.f);
    auto fileAdd = tuningBounds.removeFromTop(tuningBounds.getHeight() / 5);
    addSclButton.setBounds(fileAdd);
    fileBrowser.setBounds(tuningBounds);
    
    auto keyboardBounds = r.removeFromBottom(getHeight()/3.f);
    keyboardComponent.setBounds(keyboardBounds);
    
    rightButton.setBounds(r);
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


//==============================================================================
void MainComponent::selectionChanged() {} // Null implementation

void MainComponent::fileClicked(const juce::File&, const juce::MouseEvent&) {} // Null implementation

void MainComponent::fileDoubleClicked(const juce::File &file)
{
    TuningSingleton::instance(scalaReader.createTuningMappings(file));
}

void MainComponent::browserRootChanged(const juce::File& newFile) {} // Null implementation
