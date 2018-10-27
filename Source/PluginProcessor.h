/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class PluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PluginAudioProcessor();
    ~PluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void loadImpulseResponseToEngine (AudioBuffer<float>& LoadedIR, int position, double sampleRate, int fileSize);
    
    void loadImpulseResponseHeadphones (AudioBuffer<float>& LoadedIR, double sampleRate, int fileSize);

    bool isLoaded, shouldProcessHeadphones, headphonesReady;
    
    float outputGain, previousOutputGain;

private:

	// dsp::Convolution convolutionEngine;
	dsp::ProcessSpec convolutionProperties, headphoneConvolutionProperties;

	OwnedArray<dsp::Convolution> convolutionEngineListL, convolutionEngineListR;
    dsp::Convolution headphoneConvolutionEngineL, headphoneConvolutionEngineR;
    
	OwnedArray<AudioBuffer<float>> audioBufferList;
	AudioBuffer<float> nBufferL, nBufferR;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioProcessor)
};
