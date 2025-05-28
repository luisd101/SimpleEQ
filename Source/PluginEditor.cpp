/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
peakFreqLabel("peakFreqLabel", "Peak Frequency"),
peakGainLabel("peakGainLabel", "Peak Gain"),
peakQualityLabel("peakQualityLabel", "Peak Quality"),
lowCutFreqLabel("lowCutFreqLabel", "LowCut Frequency"),
highCutFreqLabel("highCutFreqLabel", "HighCut Frequency"),
lowCutSlopeLabel("lowCutSlopeLabel", "LowCut Slope"),
highCutSlopeLabel("highCutSlopeLabel", "HighCut Slope"),
peakFreqSliderAttachment(audioProcessor.apvts, "Peak Freq", peakFreqSlider),
peakGainSliderAttachment(audioProcessor.apvts, "Peak Gain", peakGainSlider),
peakQualitySliderAttachment(audioProcessor.apvts, "Peak Quality", peakQualitySlider),
lowCutFreqSliderAttachment(audioProcessor.apvts, "LowCut Freq", lowCutFreqSlider),
highCutFreqSliderAttachment(audioProcessor.apvts, "HighCut Freq", highCutFreqSlider),
lowCutSlopeSliderAttachment(audioProcessor.apvts, "LowCut Slope", lowCutSlopeSlider),
highCutSlopeSliderAttachment(audioProcessor.apvts, "HighCut Slope", highCutSlopeSlider)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    for ( auto* comp : getComps() ) {
        addAndMakeVisible(comp);
    }
    peakFreqLabel.attachToComponent(&peakFreqSlider, true);
    peakGainLabel.attachToComponent(&peakGainSlider, true);
    peakQualityLabel.attachToComponent(&peakQualitySlider, true);
    lowCutFreqLabel.attachToComponent(&lowCutFreqSlider, true);
    highCutFreqLabel.attachToComponent(&highCutFreqSlider, true);
    lowCutSlopeLabel.attachToComponent(&lowCutSlopeSlider, true);
    highCutSlopeLabel.attachToComponent(&highCutSlopeSlider, true);
    
    // Making the labels visible:
    addAndMakeVisible(peakFreqLabel);
    addAndMakeVisible(peakGainLabel);
    addAndMakeVisible(peakQualityLabel);
    addAndMakeVisible(lowCutFreqLabel);
    addAndMakeVisible(highCutFreqLabel);
    addAndMakeVisible(lowCutSlopeLabel);
    addAndMakeVisible(highCutSlopeLabel);
    
    setSize (600, 400);
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
}

//==============================================================================
void SimpleEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    
}

void SimpleEQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto bounds = getLocalBounds();
    auto responseArea = bounds.removeFromTop(bounds.getHeight()*0.33);
    
    auto lowCutArea = bounds.removeFromLeft(bounds.getWidth()*0.33);
    auto highCutArea = bounds.removeFromRight(bounds.getWidth()*0.5);
    
    lowCutFreqSlider.setBounds(lowCutArea.removeFromTop(lowCutArea.getHeight()*0.5));
    lowCutSlopeSlider.setBounds(lowCutArea);
    highCutFreqSlider.setBounds(highCutArea.removeFromTop(highCutArea.getHeight()*0.5));
    highCutSlopeSlider.setBounds(highCutArea);
    
    peakFreqSlider.setBounds(bounds.removeFromTop(bounds.getHeight()*0.33));
    peakGainSlider.setBounds(bounds.removeFromTop(bounds.getHeight()*0.5));
    peakQualitySlider.setBounds(bounds);
}

std::vector<juce::Component*> SimpleEQAudioProcessorEditor::getComps() {
    return {
        &peakFreqSlider,
        &peakGainSlider,
        &peakQualitySlider,
        &lowCutFreqSlider,
        &highCutFreqSlider,
        &lowCutSlopeSlider,
        &highCutSlopeSlider
    };
}
