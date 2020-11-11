#include "MainComponent.h"
#include "TuningSingleton.h"

//==============================================================================
MainComponent::MainComponent()
    : keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
    synthAudioSource (keyboardState),
    fileBrowser(juce::FileBrowserComponent::FileChooserFlags::openMode |
                juce::FileBrowserComponent::FileChooserFlags::canSelectFiles |
                juce::FileBrowserComponent::FileChooserFlags::useTreeView,
                juce::File("/"), nullptr, nullptr)
                  
{

    stdTuningButton.setButtonText("Use Standard Tuning");
    textContent.setMultiLine(true);
    textContent.setReadOnly(true);
    textContent.setCaretVisible(false);
    updateDetails();

    
    addAndMakeVisible(keyboardComponent);
    addAndMakeVisible(fileBrowser);
    addAndMakeVisible(description);
    addAndMakeVisible(stdTuningButton);
    addAndMakeVisible(textContent);
    
    // Listeners
    fileBrowser.addListener(this);
    stdTuningButton.addListener(this);
    
    //Midi ComboBox
    midiInputListLabel.setText ("MIDI Input:", juce::dontSendNotification);
    midiInputListLabel.attachToComponent(&midiInputList, true);
    auto midiInputs = juce::MidiInput::getAvailableDevices();
    addAndMakeVisible(midiInputList);
    midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
    
    // Midi
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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto r = getLocalBounds().removeFromBottom(getHeight()-50);
    midiInputList.setBounds (200, 10, getWidth() - 210, 20);
    
    auto tuningBounds = r.removeFromLeft(r.getWidth()/4.f);
    auto fileAdd = tuningBounds.removeFromTop(tuningBounds.getHeight() / 5);
    stdTuningButton.setBounds(fileAdd);
    fileBrowser.setBounds(tuningBounds);
    
    auto keyboardBounds = r.removeFromBottom(getHeight()/3.f);
    keyboardComponent.setBounds(keyboardBounds);
    
    textContent.setBounds(r);
}

void MainComponent::setMidiInput (int index)
{
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
void MainComponent::buttonClicked (juce::Button* button)
{
    if (button == &stdTuningButton)
        TuningSingleton::setTuning(Tuning::Status::Valid);
    updateDetails();
}

void MainComponent::buttonStateChanged (juce::Button* button) {}

//==============================================================================
void MainComponent::selectionChanged() {} // Null implementation

void MainComponent::fileClicked(const juce::File&, const juce::MouseEvent&) {} // Null implementation

void MainComponent::fileDoubleClicked(const juce::File &file)
{
    auto holder = TuningSingleton::setTuning(scalaReader.createTuningMappings(file));
    updateDetails();
}

void MainComponent::updateDetails()
{
    auto tuning = TuningSingleton::getTuning();

    switch (tuning.getStatus())
    {
        case Tuning::Status::Invalid :
            updateWarning(tuning);
            break;
        case Tuning::Status::Malformed :
            updateWarning(tuning);
        default:
            updateText(tuning);
    }
}

void MainComponent::updateWarning (Tuning& tuning)
{
    auto normalFont = textContent.getFont();
    auto boldFont = normalFont.withHeight(normalFont.getHeight() * 1.15).boldened();

    textContent.clear();
    textContent.setFont(boldFont);
    textContent.insertTextAtCaret(tuning.getDescription() + juce::newLine + juce::newLine);
    textContent.setFont(normalFont);
}

void MainComponent::updateText (Tuning& tuning)
{
    auto normalFont = textContent.getFont();
    auto boldFont = normalFont.withHeight(normalFont.getHeight() * 1.15).boldened();

    textContent.clear();
    textContent.setFont(boldFont);
    textContent.insertTextAtCaret("Description: ");
    textContent.setFont(normalFont);
    textContent.insertTextAtCaret(tuning.getDescription() + juce::newLine + juce::newLine);
    
    textContent.setFont(boldFont);
    textContent.insertTextAtCaret("Notes Per Scale: ");
    textContent.setFont(normalFont);
    textContent.insertTextAtCaret(tuning.getNotesPerScale() + juce::newLine + juce::newLine);
    
    textContent.setFont(boldFont);
    textContent.insertTextAtCaret("Cent Intervals: \n");
    textContent.setFont(normalFont);
    textContent.insertTextAtCaret(tuning.getCents() + juce::newLine);
    
    textContent.setFont(boldFont);
    textContent.insertTextAtCaret("Fundamental: ");
    textContent.insertTextAtCaret(tuning.getFundamental());
    textContent.setFont(normalFont);


}

void MainComponent::browserRootChanged(const juce::File& newFile) {} // Null implementation
