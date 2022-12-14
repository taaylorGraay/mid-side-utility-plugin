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
    setSize (500, 300);
    
    // Timer
    startTimer(17); // refreshes every 17ms
    
    
    // Stereo Width Slider
    stereoWidth.setSliderStyle(Slider::LinearHorizontal);
    
    stereoWidth.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    
    stereoWidth.setPopupDisplayEnabled(true, false, getParentComponent(), 1000);
    
    stereoWidth.setNumDecimalPlacesToDisplay(2);
    
    stereoWidth.setRange(0.0f, 2.0f, 0.0f);
    
    stereoWidth.setValue(1.0f);
    
    stereoWidth.addListener(this);
    
    addAndMakeVisible(&stereoWidth);
    
    stereoWidthLabel.setText("Stereo Width", dontSendNotification);
    
    addAndMakeVisible(stereoWidthLabel);
    
    stereoWidthLabel.attachToComponent (&stereoWidth, true);
    
    
    
    // Stereo Width Modulation Rate
    modRate.setSliderStyle(Slider::LinearHorizontal);
    
    modRate.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    
    modRate.setPopupDisplayEnabled(true, false, getParentComponent(), 1000);
    
    modRate.setRange(0.0f, 20.0f, 0.0f);
    
    modRate.setValue(1.0f);
    
    modRate.addListener(this);
    
    modRate.setTextValueSuffix("Hz");
    
    addAndMakeVisible(&modRate);
    
    modRateLabel.setText("Modulation Rate", dontSendNotification);
    
    addAndMakeVisible(modRateLabel);
    
    modRateLabel.attachToComponent (&modRate, true);
    
    
    
    // Stereo Width Modulation Amount
    modAmount.setSliderStyle(Slider::LinearHorizontal);
    
    modAmount.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    
    modAmount.setPopupDisplayEnabled(true, false, getParentComponent(), 1000);
    
    modAmount.setRange(0.0f, 1.0f, 0.0f);
    
    modAmount.setValue(0.5f);
    
    modAmount.addListener(this);
    
    addAndMakeVisible(&modAmount);
    
    modAmountLabel.setText("Modulation Amount", dontSendNotification);
    
    addAndMakeVisible(modAmountLabel);
    
    modAmountLabel.attachToComponent (&modAmount, true);
    
    
    
    // Input Selection Combo Box
    inSelection.addItem("Mid Side", 1);
    inSelection.addItem("Stereo", 2);
    
    inSelection.setJustificationType(Justification::centred);
    
    inSelection.setSelectedItemIndex(1);
    
    inSelection.addListener(this);
    
    addAndMakeVisible(&inSelection);
    
    inSelectionLabel.setText("Input Type", dontSendNotification);
    
    addAndMakeVisible(inSelectionLabel);
    
    inSelectionLabel.attachToComponent (&inSelection, true);
    
    
    
    // Output Selection Combo Box
    outSelection.addItem("Mid Side", 1);
    outSelection.addItem("Stereo", 2);
    outSelection.addItem("Mids", 3);
    outSelection.addItem("Sides", 4);
    
    outSelection.setJustificationType(Justification::centred);
    
    outSelection.setSelectedItemIndex(1);
    
    outSelection.addListener(this);
    
    addAndMakeVisible(&outSelection);
    
    outSelectionLabel.setText("Output Type", dontSendNotification);
    
    addAndMakeVisible(outSelectionLabel);
    
    outSelectionLabel.attachToComponent (&outSelection, true);
    
    
    
    // Stereo Width Modulation Toggle Button
    stereoWidthMod.setButtonText("Stereo Width Modulator");
    
    //stereoWidthMod.setTextBoxStyle(Button::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    
    stereoWidthMod.addListener(this);
    
    addAndMakeVisible(&stereoWidthMod);
    
    
    
    // Invert Polarity Left Toggle Button
    invPolarityL.setButtonText("+/- Left Channel");
    
    invPolarityL.addListener(this);
    
    addAndMakeVisible(&invPolarityL);
    
    
    
    // Invert Polarity Right Toggle Button
    invPolarityR.setButtonText("+/- Right Channel");
    
    invPolarityR.addListener(this);
    
    addAndMakeVisible(&invPolarityR);
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
    g.drawFittedText("MS Utility", 200, 10, 100, 50, Justification::centred, 1);
}

void MsutilityAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    stereoWidth.setBounds(100, 65, 200, 20);
    modRate.setBounds(100, 165, 200, 20);
    modAmount.setBounds(100, 215, 200, 20);
    stereoWidthMod.setBounds(185, 115, 60, 30);
    inSelection.setBounds(400, 65, 70, 20);
    outSelection.setBounds(400, 95, 70, 20);
    invPolarityL.setBounds(140, 260, 60, 30);
    invPolarityR.setBounds(330, 260, 60, 30);
}



void MsutilityAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    processor.sWidth = stereoWidth.getValue();
    processor.modDepth = modAmount.getValue();
    processor.modFrequency = modRate.getValue();
}



void MsutilityAudioProcessorEditor::comboBoxChanged(ComboBox* box)
{
    processor.inSel = inSelection.getSelectedItemIndex();
    processor.outSel = outSelection.getSelectedItemIndex();
}



void MsutilityAudioProcessorEditor::buttonClicked(Button* button)
{
    processor.invertPolL = invPolarityL.getToggleState();
    processor.invertPolR = invPolarityR.getToggleState();
    processor.sWidthMod = stereoWidthMod.getToggleState();
}



void MsutilityAudioProcessorEditor::timerCallback()
{
    stereoWidth.setValue(processor.sWidth, dontSendNotification);
}
