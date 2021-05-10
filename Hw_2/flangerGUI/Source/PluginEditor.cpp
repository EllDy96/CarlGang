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
    setSize (600, 450);

    //Feedforward Gain
    feedforwardGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedforwardGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    feedforwardGainLabel.setText("FORWARD", juce::dontSendNotification);
    feedforwardGainLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    feedforwardGainLabel.attachToComponent(&feedforwardGainSlider, false);
    feedforwardGainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(feedforwardGainSlider);
    addAndMakeVisible(feedforwardGainLabel);
    feedforwardGainSlider.setLookAndFeel(&mageKnob);



    //Feedback Gain
    feedbackGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    feedbackGainLabel.setText("FEEDBACK", juce::dontSendNotification);
    feedbackGainLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    feedbackGainLabel.attachToComponent(&feedbackGainSlider, false);
    feedbackGainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(feedbackGainSlider);
    addAndMakeVisible(feedbackGainLabel);
    feedbackGainSlider.setLookAndFeel(&mageKnob);

    //Base Delay
    baseDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    baseDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);
    baseDelayLabel.setText("DELAY", juce::dontSendNotification);
    baseDelayLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    baseDelayLabel.attachToComponent(&baseDelaySlider, false);
    baseDelayLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(baseDelaySlider);
    addAndMakeVisible(baseDelayLabel);
    baseDelaySlider.setLookAndFeel(&mageKnob);

    //LFO Sweep Width
    sweepWidthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sweepWidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);
    sweepWidthLabel.setText("LFO WIDTH", juce::dontSendNotification);
    sweepWidthLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    sweepWidthLabel.attachToComponent(&sweepWidthSlider, false);
    sweepWidthLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(sweepWidthSlider);
    addAndMakeVisible(sweepWidthLabel);
    sweepWidthSlider.setLookAndFeel(&blueKnob);

    //LFO Frequency
    lfoFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);
    lfoFrequencyLabel.setText("LFO FREQ", juce::dontSendNotification);
    lfoFrequencyLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    lfoFrequencyLabel.attachToComponent(&lfoFrequencySlider,false);
    lfoFrequencyLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lfoFrequencySlider);
    addAndMakeVisible(lfoFrequencyLabel);
    lfoFrequencySlider.setLookAndFeel(&blueKnob);

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
    g.fillAll (juce::Colours::lightseagreen);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    feedforwardGainLabel.setBounds(90, 80, 100, 20);
    feedforwardGainSlider.setBounds(90, 80, 80, 80);

    feedbackGainLabel.setBounds(260, 80, 130, 20);
    feedbackGainSlider.setBounds(260, 80, 80, 80);

    baseDelayLabel.setBounds(430, 80, 100, 20);
    baseDelaySlider.setBounds(430, 80, 80, 80);

    sweepWidthLabel.setBounds(140, 295, 150, 20);
    sweepWidthSlider.setBounds(140, 295, 90, 90);

    lfoFrequencyLabel.setBounds(370, 295, 150, 20);
    lfoFrequencySlider.setBounds(370, 295, 90,90);

    lfoWaveformBox.setBounds(235, 215, 130, 20);
}
