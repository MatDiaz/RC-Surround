/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "GUI.h"

//==============================================================================
PluginAudioProcessor::PluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::create5point1(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	isLoaded = false;
    shouldProcessHeadphones = false;
    headphonesReady = false;
    outputGain = 1;
    previousOutputGain = 1;
}

PluginAudioProcessor::~PluginAudioProcessor()
{
}

//==============================================================================
const String PluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginAudioProcessor::setCurrentProgram (int index)
{
}

const String PluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	convolutionProperties.sampleRate = sampleRate;
	convolutionProperties.maximumBlockSize = samplesPerBlock;
	convolutionProperties.numChannels = 2;
    
    headphoneConvolutionProperties.sampleRate = sampleRate;
    headphoneConvolutionProperties.maximumBlockSize = samplesPerBlock;
    headphoneConvolutionProperties.numChannels = 1;
	
	for (int i = 0; i < 6; i++)
	{
		audioBufferList.add(new AudioBuffer<float>);
		audioBufferList[i]->setSize(1, samplesPerBlock, false, false, false);
		audioBufferList[i]->clear();
	}
    
    nBufferL.setSize(1, samplesPerBlock);
    nBufferL.clear();
    
    nBufferR.setSize(1, samplesPerBlock);
    nBufferR.clear();
}

void PluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void PluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	if (isLoaded && totalNumInputChannels == 6 && totalNumOutputChannels == 2)
	{	
		for (int i = 0; i < totalNumInputChannels; i++)
		{
			const float* channelK = buffer.getReadPointer(i);
			float* channelN = audioBufferList[i]->getWritePointer(0);

			memcpy(channelN, channelK, sizeof(float) * buffer.getNumSamples());

			AudioBuffer<float> bufferCopy = *audioBufferList[i];

			dsp::AudioBlock<float> tempAudioBufferL(*audioBufferList[i]), tempAudioBufferR(bufferCopy);
			dsp::ProcessContextReplacing<float> ctxL(tempAudioBufferL), ctxR(tempAudioBufferR);

			convolutionEngineListL[i]->process(ctxL);
			convolutionEngineListR[i]->process(ctxR);

			float* channelL = buffer.getWritePointer(0);
			float* channelR = buffer.getWritePointer(1);
			
			for (int j = 0; j < buffer.getNumSamples(); j++)
			{	
				if (i == 0)
					channelL[j] = tempAudioBufferL.getSample(0, j);
				else if (i == 1)
					channelR[j] = tempAudioBufferR.getSample(0, j);
				else
				{
					channelL[j] += tempAudioBufferL.getSample(0, j);
					channelR[j] += tempAudioBufferR.getSample(0, j);
				}
			}
		}
        
        if (shouldProcessHeadphones && headphonesReady)
        {
            float* channelL = buffer.getWritePointer(0);
            float* channelR = buffer.getWritePointer(1);
            
            float* channelNL = nBufferL.getWritePointer(0);
            float* channelNR = nBufferR.getWritePointer(0);
            
            memcpy(channelNL, channelL, sizeof(float) * buffer.getNumSamples());
            memcpy(channelNR, channelR, sizeof(float) * buffer.getNumSamples());
            
            dsp::AudioBlock<float> headphoneBufferL(nBufferL), headphoneBufferR(nBufferR);
            dsp::ProcessContextReplacing<float> ctxxL(headphoneBufferL), ctxxR(headphoneBufferR);
            
            headphoneConvolutionEngineL.process(ctxxL);
            headphoneConvolutionEngineR.process(ctxxR);
            
            for (auto i = 0; i < buffer.getNumSamples(); i++)
            {
                channelL[i] = headphoneBufferL.getSample(0, i);
                channelR[i] = headphoneBufferR.getSample(0, i);
            }
            
        }

        buffer.applyGainRamp(0, buffer.getNumSamples(), previousOutputGain, outputGain);
        
        previousOutputGain = outputGain;
        
	}
}

//==============================================================================
bool PluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginAudioProcessor::createEditor()
{
    return new PluginAudioProcessorEditor (*this);
}

//==============================================================================
void PluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void PluginAudioProcessor::loadImpulseResponseToEngine(AudioBuffer<float>& LoadedIR, int position, double sampleRate, int fileSize)
{
	AudioBuffer<float> tempBufferL, tempBufferR;
	tempBufferL.setSize(1, fileSize, false, false, false);
	tempBufferR = tempBufferL;

	tempBufferL.clear();
	tempBufferR.clear();

	float* channelL = LoadedIR.getWritePointer(0);
	float* channelR = LoadedIR.getWritePointer(1);

	for (int i = 0; i < fileSize; i++)
	{
		tempBufferL.setSample(0, i, channelL[i]);
		tempBufferR.setSample(0, i, channelR[i]);
	}

	convolutionEngineListL.add(new dsp::Convolution());
	convolutionEngineListL[position]->prepare(convolutionProperties);
	convolutionEngineListL[position]->copyAndLoadImpulseResponseFromBuffer(tempBufferL, sampleRate, false, false, false, 0);

	convolutionEngineListR.add(new dsp::Convolution());
	convolutionEngineListR[position]->prepare(convolutionProperties);
	convolutionEngineListR[position]->copyAndLoadImpulseResponseFromBuffer(tempBufferR, sampleRate, false, false, false, 0);
}

void PluginAudioProcessor::loadImpulseResponseHeadphones(AudioBuffer<float> &LoadedIR, double sampleRate, int fileSize)
{
    AudioBuffer<float> tempBufferL, tempBufferR;
    tempBufferL.setSize(1, fileSize);
    tempBufferR = tempBufferL;
    
    float* channelL = LoadedIR.getWritePointer(0);
    float* channelR = LoadedIR.getWritePointer(1);
    
    for (int i = 0; i < fileSize; i++)
    {
        tempBufferL.setSample(0, i, channelL[i]);
        tempBufferR.setSample(0, i, channelR[i]);
    }
    
    headphoneConvolutionEngineL.prepare(headphoneConvolutionProperties);
    headphoneConvolutionEngineL.copyAndLoadImpulseResponseFromBuffer(tempBufferL, sampleRate, false, false, false, 0);
    
    headphoneConvolutionEngineR.prepare(headphoneConvolutionProperties);
    headphoneConvolutionEngineR.copyAndLoadImpulseResponseFromBuffer(tempBufferR, sampleRate, false, false, false, 0);
    
    headphonesReady = true;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginAudioProcessor();
}
