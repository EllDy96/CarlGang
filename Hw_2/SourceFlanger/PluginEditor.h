/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FlangerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FlangerAudioProcessorEditor (FlangerAudioProcessor&);
    ~FlangerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FlangerAudioProcessor& audioProcessor;

    // 1) Loop Parameters
    juce::Slider feedforwardGainSlider;
    juce::Label feedforwardGainLabel;

    juce::Slider feedbackGainSlider;
    juce::Label feedbackGainLabel;

    //juce::Slider drySlider;
    //juce::Label dryLabel;

    juce::Slider baseDelaySlider;
    juce::Label baseDelayLabel;

    //LFO Parameters
    juce::Slider sweepWidthSlider;
    juce::Label sweepWidthLabel;

    juce::Slider lfoFrequencySlider;
    juce::Label lfoFrequencyLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedforwardGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> baseDelaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sweepWidthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoFrequencySliderAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessorEditor)
};
