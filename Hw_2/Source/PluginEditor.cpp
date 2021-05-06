/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayLineAudioProcessorEditor::DelayLineAudioProcessorEditor (DelayLineAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    //********************************************************************************************//
    // 4) Set all properties of the sliders and of the labels
    wetSlider.setRange (0.0, 1.0);
    wetSlider.setTextBoxStyle (juce::Slider::TextBoxRight, false, 100, 20);
    wetSlider.addListener(this);
    wetLabel.setText ("Wet Level", juce::dontSendNotification);
    
    addAndMakeVisible (wetSlider);
    addAndMakeVisible (wetLabel);
    
    drySlider.setRange (0.0, 1.0);
    drySlider.setTextBoxStyle (juce::Slider::TextBoxRight, false, 100, 20);
    drySlider.addListener(this);
    dryLabel.setText ("Dry Level", juce::dontSendNotification);
    
    addAndMakeVisible (drySlider);
    addAndMakeVisible (dryLabel);
    
    timeSlider.setRange (10, 950, 100); // to guarantee a low dalay value we set the interval bellow the 20ms
    timeSlider.setTextBoxStyle (juce::Slider::TextBoxRight, false, 100, 20);
    timeSlider.addListener(this);
    timeLabel.setText ("Time", juce::dontSendNotification);
    
    addAndMakeVisible (timeSlider);
    addAndMakeVisible (timeLabel);
    
    //setting the LFO value
    lfoSpeed.setRange(0.1, 10,0.1);
    lfoSpeed.addListener(this);
    //lfoSpeed.setSliderStyle(juce::Slider::Rotary);
    
    lfoSpeed.setTextBoxStyle (juce::Slider::TextBoxRight, false, 100, 20);
    speedLabel.setText("Speed", juce::dontSendNotification);
    
    sweepWidth.setRange(1,50); //TODO da controllare 
    //sweepWidth.setSliderStyle(juce::Slider::Rotary);
    
    sweepWidth.setTextBoxStyle (juce::Slider::TextBoxRight, false, 100, 20);
    sweepWidth.addListener(this);
    amplitude.setText("Amount", juce::dontSendNotification);
    
    addAndMakeVisible (lfoSpeed);
    addAndMakeVisible (sweepWidth);
    addAndMakeVisible(amplitude);
    addAndMakeVisible(speedLabel);
    
    
    setSize (400, 300);
    //********************************************************************************************//
}

DelayLineAudioProcessorEditor::~DelayLineAudioProcessorEditor()
{
}

//==============================================================================
void DelayLineAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Delay Line 1", getLocalBounds(), juce::Justification::centred, 1);
}

void DelayLineAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //********************************************************************************************//
    // 5) Set the positions for all the sliders and listeners

    wetLabel.setBounds (10, 10, 90, 20);
    wetSlider.setBounds (100, 10, getWidth() - 110, 20);
    
    dryLabel.setBounds (10, 50, 90, 20);
    drySlider.setBounds (100, 50, getWidth() - 110, 20);
    
    timeLabel.setBounds (10, 90, 90, 20);
    timeSlider.setBounds (100, 90, getWidth() - 110, 20);
    
    speedLabel.setBounds (10, 130, 90, 20);
    lfoSpeed.setBounds (100, 130, getWidth() - 110, 20);
    
    amplitude.setBounds (10, 170, 90, 20);
    sweepWidth.setBounds (100, 170, getWidth() - 110, 20);
    
    
    //********************************************************************************************//

}

//********************************************************************************************//
// 6) Define the function to be called when the slider changes
void DelayLineAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &wetSlider)
        audioProcessor.set_wet(wetSlider.getValue());
        
    else if (slider == &drySlider)
        audioProcessor.set_dry(drySlider.getValue());
        
    else if (slider == &timeSlider)
        audioProcessor.set_ds(timeSlider.getValue());
        
    else if (slider == &sweepWidth)
    {
        audioProcessor.setSweepWidth(sweepWidth.getValue());
    }
    else if (slider == &lfoSpeed)
    {
        audioProcessor.setSpeed(lfoSpeed.getValue());
    }
    
}
//********************************************************************************************//
