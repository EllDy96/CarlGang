/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

// Adding some constant for the lfo 

//#define SAMPLE_RATE(48000)
#ifndef M_PI
#define M_PI 3.14159265
#endif


//==============================================================================
DelayLineAudioProcessor::DelayLineAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

DelayLineAudioProcessor::~DelayLineAudioProcessor()
{
}

//==============================================================================
const juce::String DelayLineAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayLineAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayLineAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DelayLineAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DelayLineAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DelayLineAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayLineAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DelayLineAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DelayLineAudioProcessor::getProgramName (int index)
{
    return {};
}

void DelayLineAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DelayLineAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    //********************************************************************************************//
    // 9) Initialize the variables that we are going to need in processBlock function: 
    // the buffer, the write and read pointer, the delay value
  
    dBuf.setSize(2, (int)ceil((20*20)*sampleRate)); // TODO check the size
    dBuf.clear(); 
    dBufLength= dBuf.getNumSamples();
    
    dw = 0;
    dr = 1;
    ds = 0.0025;
    
    sweepWidth=1;
    speed=0.2;
    phase=0;

    dry = 0.5;
    wet = 0.5;
    feedback = 0;

    
    
    //********************************************************************************************//

}

void DelayLineAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayLineAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void DelayLineAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
    //********************************************************************************************//
    // 3) Delay line implementation
    int numSamples = buffer.getNumSamples();
    float wet_now = wet;
    float dry_now = dry;
    float ds_now = ds;
    float sweepWidth_now = sweepWidth;
    float speed_now = speed;
    float feedback_now = feedback;
   
    
    
    float* channelOutDataL = buffer.getWritePointer(0);
    float* channelOutDataR = buffer.getWritePointer(1);
    
    const float* channelInData = buffer.getReadPointer(0);
    
    for (int i = 0; i < numSamples; ++i) {
        // setSample(int destChannel, int destSample, Type newValue)	
        const float in = channelInData[i];
        float interpolatedSample1 = 0.0;
        float interpolatedSample2 = 0.0;
        
        
        float currentDelay = ds_now + 0.5f * sweepWidth_now * (1.0f + sinf(2.0 * M_PI * phase));
        
        float temp = (float)dw - (float)(currentDelay * getSampleRate()) + (float)dBufLength - 3.0;
        //(float)dw - (float)(currentDelay * getSampleRate()) + (float)dBufLength - 3.0;
        dr = fmodf(temp,(float)dBufLength);

        // Use linear interpolation to read a fractional index
        // into the buffer.
        float fraction = dr - floorf(dr);
        
        
        int previousSample = (int)floorf(dr);
        
        int nextSample = (previousSample + 1) %dBufLength;
        
        interpolatedSample1 = fraction * dBuf.getSample(0,nextSample) + (1.0f-fraction)*dBuf.getSample(0 , previousSample);
        interpolatedSample2 = fraction * dBuf.getSample(1, nextSample) + (1.0f - fraction) * dBuf.getSample(1, previousSample);
        // Store the current information in the delay buffer.
        // With feedback, what we read is included in what gets
        // stored in the buffer, otherwise it’s just a simple
        // delay line of the input signal.
        dBuf.setSample(0, dw, in + interpolatedSample1 * feedback_now);
        dBuf.setSample(1, dw, in + interpolatedSample2 * feedback_now);

        if (++dw >= dBufLength)
            dw = 0;

        channelOutDataL[i] = dry_now * in + wet_now * interpolatedSample1;
        channelOutDataR[i] = channelOutDataL[i];
        
        
                                                        
        // Store the output in the buffer, replacing the input
        //channelInData[i] = in + wet_now * interpolatedSample1;
        
        // Update the LFO phase, keeping it in the range 0-1
        phase += speed_now*(1/getSampleRate());
        if(phase >= 1.0)
            phase -= 1.0;
        
        
        

        //annelOutDataL[i] = dry_now * channelInData[i] + wet_now * dBuf.getSample(0, dr); 
        //channelOutDataR[i] = dry_now * channelInData[i] + wet_now * dBuf.getSample(1, dr);
        
        //dw = (dw + 1 ) % ds_now ;
        //dr = (dr + 1 ) % ds_now ;
    }
 
    
    //********************************************************************************************//
}

//==============================================================================
bool DelayLineAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DelayLineAudioProcessor::createEditor()
{
    return new DelayLineAudioProcessorEditor (*this);
}

//==============================================================================
void DelayLineAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DelayLineAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayLineAudioProcessor();
}


//********************************************************************************************//
// 10) define the functions that will be used by the Editor to update slider values

void DelayLineAudioProcessor::set_wet(float val)
{
    wet = val;
}
void DelayLineAudioProcessor::set_dry(float val)
{
    dry = val;
}
void DelayLineAudioProcessor::set_ds(int val)
{
    ds = (float) val*0.001;
}
void DelayLineAudioProcessor::setSweepWidth( float val)
{
    sweepWidth= (float)val*0.001;
}
void DelayLineAudioProcessor::setSpeed( float val)
{
    speed= val;
}

void DelayLineAudioProcessor::setFeedback(float val)
{
    feedback = val;
}
    
//********************************************************************************************//
