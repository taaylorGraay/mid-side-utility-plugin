/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MsutilityAudioProcessorEditor::MsutilityAudioProcessorEditor (MsutilityAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    
    // Stereo Width Slider
    
    stereoWidth.setSliderStyle(Slider::LinearHorizontal);
    
    stereoWidth.setRange(0.0f, 2.0f, 0.0f);
    
    stereoWidth.setValue(1.0f);
    
    stereoWidth.addListener(this);
    
    addAndMakeVisible(&stereoWidth);
    
    
    
    // Input Selection Combo Box
    inSelection.addItem("Mid Side", 1);
    inSelection.addItem("Stereo", 2);
    
    inSelection.setJustificationType(Justification::centred);
    
    inSelection.setSelectedItemIndex(1);
    
    inSelection.addListener(this);
    
    addAndMakeVisible(&inSelection);
    
    
    
    //Invert Polarity Left Toggle Button
    invPolarityL.setButtonText("+/- Left Channel");
    
    invPolarityL.addListener(this);
    
    addAndMakeVisible(&invPolarityL);
}

MsutilityAudioProcessorEditor::~MsutilityAudioProcessorEditor()
{
}

//==============================================================================
void MsutilityAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void MsutilityAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    stereoWidth.setBounds
    inSelection.setBounds
    invPolarityL.setBounds
}



void MsutilityAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    processor.sWidth = stereoWidth.getValue();
}



void MsutilityAudioProcessorEditor::comboBoxChanged(ComboBox* box)
{
    processor.inSel = inSelection.getSelectedItemIndex();
}



void MsutilityAudioProcessorEditor::buttonClicked(Button* button)
{
    processor.invertPolL = invPolarityL.getToggleState();
}

