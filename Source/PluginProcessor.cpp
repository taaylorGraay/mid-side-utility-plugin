/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MsutilityAudioProcessor::MsutilityAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    stereoWidth = new AudioParameterFloat("stereoWidth", "Stereo Width", 0.0f, 2.0f, 1.0f);
    addParameter(stereoWidth);
    
    inSelection = new AudioParameterChoice("inSelection", "Input Type", {"Mid Side", "Stereo"}, 1);
    addParameter(inSelection);
    
    outSelection = new AudioParameterChoice("outSelection", "Output Type", {"Mid Side", "Stereo"}, 1);
    addParameter(outSelection);
    
    invPolarityL = new AudioParameterBool("invPolarityL", "+/- Left Channel)", 0);
    addParameter(invPolarityL);
    
    invPolarityR = new AudioParameterBool("invPolarityR", "+/- Right Channel)", 0);
    addParameter(invPolarityR);
}

MsutilityAudioProcessor::~MsutilityAudioProcessor()
{
}

//==============================================================================
const String MsutilityAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MsutilityAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MsutilityAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MsutilityAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MsutilityAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MsutilityAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MsutilityAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MsutilityAudioProcessor::setCurrentProgram (int index)
{
}

const String MsutilityAudioProcessor::getProgramName (int index)
{
    return {};
}

void MsutilityAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MsutilityAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MsutilityAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MsutilityAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MsutilityAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Storing the array of the samples for each channel
    auto* channelDataL = buffer.getWritePointer (0);
    auto* channelDataR = buffer.getWritePointer (1);
    
    // Loop runs through the array of samples
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        float side;
        float mid;
        
        // Getting the value from the user parameter and storing as a new variable
        float sWidth = stereoWidth->get();
        
        int inSel = inSelection->getIndex();
        
        if (inSel == 1)
        {
            // Stereo Image Widening (Encoding stereo to MS and giving it a width control)
            side = sWidth *(0.5 * (channelDataL[i] - channelDataR[i]));
            mid = (2.0 - sWidth) *(0.5 * (channelDataL[i] + channelDataR[i]));
        }
        else
        {
            side = sWidth * (channelDataL[i] - channelDataR[i]);
            mid = (2.0 - sWidth) * (channelDataL[i] + channelDataR[i]);
        }
        
        int outSel = outSelection->getIndex();
        
        if (outSel ==1)
        {
            //Decoding MS
            channelDataL[i] = mid + side;
            channelDataR[i] = mid - side;
        }
        else
        {
            channelDataL[i] = side;
            channelDataR[i] = mid;
        }
        
        int invertPolL = invPolarityL->get();
        
        if (invertPolL == 0)
        {
            channelDataL[i] = channelDataL[i];
        }
        else
        {
            channelDataL[i] = channelDataL[i] * -1;
        }
        
        int invertPolR = invPolarityR->get();
        
        if (invertPolR == 0)
        {
            channelDataR[i] = channelDataR[i];
        }
        else
        {
            channelDataR[i] = channelDataR[i] * -1;
        }
    }
        

        
   
}

//==============================================================================
bool MsutilityAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MsutilityAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor (this);
}

//==============================================================================
void MsutilityAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MsutilityAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MsutilityAudioProcessor();
}
