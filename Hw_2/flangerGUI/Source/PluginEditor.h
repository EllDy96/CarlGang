/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class BlueKnobStyle  : public juce::LookAndFeel_V4
{
public:

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override
    {
        float diameter = juce::jmin(width, height) - 0.1* juce::jmin(width, height);
        float radius = diameter / 2;
        float centreX = x + width / 2;
        float centreY = y + height / 2;
        float rx = centreX - radius;
        float ry = centreY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
        float knobDiameter = 0.25 * radius;

        juce::Rectangle<float> dialArea(rx, ry, diameter, diameter);

        g.setColour(juce::Colours::lightslategrey);
        g.fillEllipse(dialArea);

        g.setColour(juce::Colours::black);

        juce::Path dialTick;
        //dialTick.addRectangle(0, - radius, 10.0f, radius);
        dialTick.addRectangle(-knobDiameter / 2, -radius + 0.01 * radius, knobDiameter, 2 * knobDiameter);

        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centreX, centreY));
        // translation is perfomed before the rotation

        g.setColour(juce::Colours::black);
        //g.drawEllipse(rx, ry, diameter,diameter, 0.01*radius);

        g.setColour(juce::Colours::royalblue);
        g.fillEllipse(rx + 0.4 * radius, ry + 0.4 * radius, diameter * 0.6f, diameter * 0.6f);

    }

};

class MagentaKnobStyle : public juce::LookAndFeel_V4
{
public:

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override
    {
        float diameter = juce::jmin(width, height) - 0.1 * juce::jmin(width, height);
        float radius = diameter / 2;
        float centreX = x + width / 2;
        float centreY = y + height / 2;
        float rx = centreX - radius;
        float ry = centreY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
        float knobDiameter = 0.25 * radius;

        juce::Rectangle<float> dialArea(rx, ry, diameter, diameter);

        g.setColour(juce::Colours::lightslategrey);
        g.fillEllipse(dialArea);

        g.setColour(juce::Colours::black);

        juce::Path dialTick;
        //dialTick.addRectangle(0, - radius, 10.0f, radius);
        dialTick.addRectangle(-knobDiameter / 2, -radius + 0.01 * radius, knobDiameter, 2 * knobDiameter);

        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centreX, centreY));
        // translation is perfomed before the rotation

        g.setColour(juce::Colours::black);
        //g.drawEllipse(rx, ry, diameter,diameter, 0.01*radius);

        g.setColour(juce::Colours::darkmagenta);
        g.fillEllipse(rx + 0.4 * radius, ry + 0.4 * radius, diameter * 0.6f, diameter * 0.6f);

    }

};


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

    juce::ComboBox lfoWaveformBox;

    BlueKnobStyle blueKnob;
    MagentaKnobStyle mageKnob;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedforwardGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> baseDelaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sweepWidthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoFrequencySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> lfoWaveformBoxAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessorEditor)
};
