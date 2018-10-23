/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginAudioProcessorEditor  : public AudioProcessorEditor,
                                    public Button::Listener,
                                    public ComboBox::Listener
{
public:
    //==============================================================================
    PluginAudioProcessorEditor (PluginAudioProcessor& p);
    ~PluginAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginAudioProcessor& processor;
	OwnedArray<File> listaArchivos;
	OwnedArray<AudioFormatReader> listaDatosArchivos;
	OwnedArray<Label> labelList;

	String archivosSurround[6] = { "IR - L.wav", "IR - R.wav", "IR - C.wav", "IR - LFE.wav", "IR - LS.wav", "IR - RS.wav" };

	ScopedPointer<Label> label;
	ScopedPointer<Label> label2;
	ScopedPointer<Label> label3;
	ScopedPointer<Label> label4;
	ScopedPointer<Label> label5;
	ScopedPointer<Label> label6;

	AudioFormatManager formatManager;

	bool imageLoaded;

	Image studioImage;

	ScopedPointer<ImageFileFormat> formatImage;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> loadButton;
    std::unique_ptr<ComboBox> systemComboBox;
    std::unique_ptr<Label> activeSystemLabel;
    std::unique_ptr<Label> systemLabel;
    std::unique_ptr<ComboBox> referenceComboBox;
    std::unique_ptr<Label> placeLabel;
    std::unique_ptr<Label> DescriptionLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]