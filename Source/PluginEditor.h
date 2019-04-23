/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class MsutilityAudioProcessorEditor  : public AudioProcessorEditor,
private Slider::Listener,
private ComboBox::Listener,
private Button::Listener,
private Timer
{
public:
    MsutilityAudioProcessorEditor (MsutilityAudioProcessor&);
    ~MsutilityAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback();

    
private:
    
    void sliderValueChanged(Slider* slider) override;
    
    void comboBoxChanged(ComboBox*) override;
    
    void buttonClicked(Button* button) override;
    
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MsutilityAudioProcessor& processor;
    
    Slider stereoWidth;
    Label stereoWidthLabel;
    Slider modRate;
    Label modRateLabel;
    Slider modAmount;
    Label modAmountLabel;
    ComboBox inSelection;
    Label inSelectionLabel;
    ComboBox outSelection;
    Label outSelectionLabel;
    ToggleButton stereoWidthMod;
    ToggleButton invPolarityL;
    ToggleButton invPolarityR;
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MsutilityAudioProcessorEditor)
};
