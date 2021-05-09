/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FlangerAudioProcessorEditor::FlangerAudioProcessorEditor (FlangerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    //Feedforward Gain
    feedforwardGainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    feedforwardGainLabel.setText("Feedforward", juce::dontSendNotification);
    addAndMakeVisible(feedforwardGainSlider);
    addAndMakeVisible(feedforwardGainLabel);

    //Feedback Gain
    feedbackGainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    feedbackGainLabel.setText("Feedback", juce::dontSendNotification);
    addAndMakeVisible(feedbackGainSlider);
    addAndMakeVisible(feedbackGainLabel);

    //Base Delay
    baseDelaySlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    baseDelayLabel.setText("Delay", juce::dontSendNotification);
    addAndMakeVisible(baseDelaySlider);
    addAndMakeVisible(baseDelayLabel);

    //LFO Sweep Width
    sweepWidthSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    sweepWidthLabel.setText("LFO Width", juce::dontSendNotification);
    addAndMakeVisible(sweepWidthSlider);
    addAndMakeVisible(sweepWidthLabel);

    //LFO Frequency
    lfoFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    lfoFrequencyLabel.setText("LFO Frequency", juce::dontSendNotification);
    addAndMakeVisible(lfoFrequencySlider);
    addAndMakeVisible(lfoFrequencyLabel);

    //LFO Waveform
    lfoWaveformBox.addItem("Sine", 1);
    lfoWaveformBox.addItem("Triangle", 2);
    lfoWaveformBox.addItem("Sawtooth", 3);
    lfoWaveformBox.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lfoWaveformBox);


    
    feedforwardGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GFF", feedforwardGainSlider);
    feedbackGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GFB", feedbackGainSlider);
    baseDelaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DELAY", baseDelaySlider);
    sweepWidthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WIDTH", sweepWidthSlider);
    lfoFrequencySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ", lfoFrequencySlider);
    lfoWaveformBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "WVFORM", lfoWaveformBox);;

}

FlangerAudioProcessorEditor::~FlangerAudioProcessorEditor()
{
}

//==============================================================================
void FlangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    feedforwardGainLabel.setBounds(10, 10, 90, 20);
    feedforwardGainSlider.setBounds(100, 10, getWidth() - 110, 20);

    feedbackGainLabel.setBounds(10, 50, 90, 20);
    feedbackGainSlider.setBounds(100, 50, getWidth() - 110, 20);

    baseDelayLabel.setBounds(10, 90, 90, 20);
    baseDelaySlider.setBounds(100, 90, getWidth() - 110, 20);

    sweepWidthLabel.setBounds(10, 130, 90, 20);
    sweepWidthSlider.setBounds(100, 130, getWidth() - 110, 20);

    lfoFrequencyLabel.setBounds(10, 170, 90, 20);
    lfoFrequencySlider.setBounds(100, 170, getWidth() - 110, 20);

    lfoWaveformBox.setBounds(10, 210, 130, 20);
}
