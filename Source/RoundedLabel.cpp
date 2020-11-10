/*
  ==============================================================================

    RoundedLabels.cpp
    Created: 8 Nov 2020 3:55:28pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "RoundedLabel.h"

RoundedLabel::RoundedLabel() {}

RoundedLabel::~RoundedLabel() {}

void RoundedLabel::drawLabel(juce::Graphics& g, juce::Label &label)
{
    auto cornerSize = 6.0f;
    auto bounds = label.getLocalBounds().toFloat().reduced (0.5f, 0.5f);
   
    g.setColour(findColour(juce::ResizableWindow::backgroundColourId));
    g.fillRoundedRectangle (bounds, cornerSize);
    g.setColour (label.findColour (juce::ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
    
    LookAndFeel_V4::drawLabel(g, label);
}
