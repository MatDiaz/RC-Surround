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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "GUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginAudioProcessorEditor::PluginAudioProcessorEditor (PluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    //[Constructor_pre] You can add your own custom stuff here..
	imageLoaded = false;
    //[/Constructor_pre]

    loadButton.reset (new TextButton ("loadButton"));
    addAndMakeVisible (loadButton.get());
    loadButton->setButtonText (TRANS("Cargar Recinto"));
    loadButton->addListener (this);
    loadButton->setColour (TextButton::buttonColourId, Colour (0xff5c9ba4));
    loadButton->setColour (TextButton::textColourOffId, Colours::white);

    loadButton->setBounds (40, 392, 480, 32);

    systemComboBox.reset (new ComboBox ("systemComboBox"));
    addAndMakeVisible (systemComboBox.get());
    systemComboBox->setEditableText (false);
    systemComboBox->setJustificationType (Justification::centredLeft);
    systemComboBox->setTextWhenNothingSelected (String());
    systemComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    systemComboBox->addItem (CharPointer_UTF8 ("Aud\xc3\xad""fonos"), 1);
    systemComboBox->addItem (TRANS("Opsodis"), 2);
    systemComboBox->addListener (this);

    systemComboBox->setBounds (580, 249, 300, 40);

    activeSystemLabel.reset (new Label ("activeSystemLabel",
                                        TRANS("Sistema Activo")));
    addAndMakeVisible (activeSystemLabel.get());
    activeSystemLabel->setFont (Font ("Maiandra GD", 20.00f, Font::plain));
    activeSystemLabel->setJustificationType (Justification::centred);
    activeSystemLabel->setEditable (false, false, false);
    activeSystemLabel->setColour (Label::textColourId, Colours::white);
    activeSystemLabel->setColour (TextEditor::textColourId, Colours::black);
    activeSystemLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    activeSystemLabel->setColour (TextEditor::highlightColourId, Colour (0xbf5cd206));

    activeSystemLabel->setBounds (585, 340, 290, 30);

    systemLabel.reset (new Label ("systemLabel",
                                  TRANS("Opsodis")));
    addAndMakeVisible (systemLabel.get());
    systemLabel->setFont (Font ("Maiandra GD", 20.00f, Font::plain));
    systemLabel->setJustificationType (Justification::centred);
    systemLabel->setEditable (false, false, false);
    systemLabel->setColour (Label::textColourId, Colours::white);
    systemLabel->setColour (TextEditor::textColourId, Colours::black);
    systemLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    systemLabel->setBounds (587, 389, 285, 32);

    referenceComboBox.reset (new ComboBox ("referenceComboBox"));
    addAndMakeVisible (referenceComboBox.get());
    referenceComboBox->setEditableText (false);
    referenceComboBox->setJustificationType (Justification::centredLeft);
    referenceComboBox->setTextWhenNothingSelected (String());
    referenceComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    referenceComboBox->addListener (this);

    referenceComboBox->setBounds (589, 447, 284, 32);

    placeLabel.reset (new Label ("placeLabel",
                                 TRANS("Recinto:")));
    addAndMakeVisible (placeLabel.get());
    placeLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    placeLabel->setJustificationType (Justification::centredLeft);
    placeLabel->setEditable (false, false, false);
    placeLabel->setColour (TextEditor::textColourId, Colours::black);
    placeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    placeLabel->setBounds (584, 512, 296, 20);

    DescriptionLabel.reset (new Label ("DescriptionLabel",
                                       CharPointer_UTF8 ("Decripci\xc3\xb3n:")));
    addAndMakeVisible (DescriptionLabel.get());
    DescriptionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    DescriptionLabel->setJustificationType (Justification::topLeft);
    DescriptionLabel->setEditable (false, false, false);
    DescriptionLabel->setColour (TextEditor::textColourId, Colours::black);
    DescriptionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    DescriptionLabel->setBounds (584, 547, 296, 93);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (900, 700);


    //[Constructor] You can add your own custom stuff here..

	label.reset(new Label("new label",
		TRANS("IR - L:")));
	addAndMakeVisible(label.get());
	label->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	label->setJustificationType(Justification::centredLeft);
	label->setEditable(false, false, false);
	label->setColour(TextEditor::textColourId, Colours::black);
	label->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	label->setBounds(40, 440, 300, 30);

	label2.reset(new Label("new label",
		TRANS("IR - R: ")));
	addAndMakeVisible(label2.get());
	label2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	label2->setJustificationType(Justification::centredLeft);
	label2->setEditable(false, false, false);
	label2->setColour(TextEditor::textColourId, Colours::black);
	label2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	label2->setBounds(40, 480, 300, 30);

	label3.reset(new Label("new label",
		TRANS("IR - C:")));
	addAndMakeVisible(label3.get());
	label3->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	label3->setJustificationType(Justification::centredLeft);
	label3->setEditable(false, false, false);
	label3->setColour(TextEditor::textColourId, Colours::black);
	label3->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	label3->setBounds(40, 520, 300, 30);

	label4.reset(new Label("new label",
		TRANS("IR - LFE: ")));
	addAndMakeVisible(label4.get());
	label4->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	label4->setJustificationType(Justification::centredLeft);
	label4->setEditable(false, false, false);
	label4->setColour(TextEditor::textColourId, Colours::black);
	label4->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	label4->setBounds(40, 560, 300, 30);

	label5.reset(new Label("new label",
		TRANS("IR - LS: ")));
	addAndMakeVisible(label5.get());
	label5->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	label5->setJustificationType(Justification::centredLeft);
	label5->setEditable(false, false, false);
	label5->setColour(TextEditor::textColourId, Colours::black);
	label5->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	label5->setBounds(40, 600, 300, 30);

	label6.reset(new Label("new label",
		TRANS("IR - RS: ")));
	addAndMakeVisible(label6.get());
	label6->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	label6->setJustificationType(Justification::centredLeft);
	label6->setEditable(false, false, false);
	label6->setColour(TextEditor::textColourId, Colours::black);
	label6->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	label6->setBounds(40, 640, 300, 30);

	activeSystemLabel->setBounds(595, 258, 273, 32);

	labelList.add(label);
	labelList.add(label2);
	labelList.add(label3);
	labelList.add(label4);
	labelList.add(label5);
	labelList.add(label6);

	formatManager.registerBasicFormats();

    //[/Constructor]
}

PluginAudioProcessorEditor::~PluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

	labelList.clearQuick(false);

    //[/Destructor_pre]

    loadButton = nullptr;
    systemComboBox = nullptr;
    activeSystemLabel = nullptr;
    systemLabel = nullptr;
    referenceComboBox = nullptr;
    placeLabel = nullptr;
    DescriptionLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

	label = nullptr;
	label2 = nullptr;
	label3 = nullptr;
	label4 = nullptr;
	label5 = nullptr;
	label6 = nullptr;

    //[/Destructor]
}

//==============================================================================
void PluginAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff0f0f0f));

    {
        int x = 30, y = 30, width = 500, height = 340;
        Colour fillColour = Colour (0x54373636);
        Colour strokeColour = Colour (0xff8b8b8b);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 40, y = 40, width = 480, height = 320;
        //[UserPaintCustomArguments] Customize the painting arguments here..
    		if (imageLoaded)
    		{
    			RectanglePlacement rectanglePosition(RectanglePlacement::stretchToFit);
    			g.drawImageWithin(studioImage, x, y, width, height, rectanglePosition);
    		}
        //[/UserPaintCustomArguments]
    }

    {
        float x = 580.0f, y = 320.0f, width = 300.0f, height = 180.0f;
        Colour fillColour1 = Colour (0xd7bcbcbc), fillColour2 = Colour (0x8d29a4b2);
        Colour strokeColour1 = Colour (0xff00d5ff), strokeColour2 = Colour (0xffe4dcdc);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       352.0f - 580.0f + x,
                                       128.0f - 320.0f + y,
                                       fillColour2,
                                       480.0f - 580.0f + x,
                                       672.0f - 320.0f + y,
                                       false));
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setGradientFill (ColourGradient (strokeColour1,
                                       552.0f - 580.0f + x,
                                       200.0f - 320.0f + y,
                                       strokeColour2,
                                       888.0f - 580.0f + x,
                                       568.0f - 320.0f + y,
                                       false));
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        int x = 580, y = 40, width = 300, height = 180;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
    }

    //[UserPaint] Add your own custom painting code here..

    //[/UserPaint]
}

void PluginAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loadButton.get())
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
		FileChooser abreCarpeta("Seleccione Carpeta con Respuestas al Impulso");

		if (abreCarpeta.browseForDirectory())
		{
			File Carpeta;

			File archivoImagen = Carpeta;

			Carpeta = abreCarpeta.getResult();

			archivoImagen = Carpeta.getFullPathName() + "/"  + "background.jpg";

			studioImage = formatImage->loadFrom(archivoImagen);

			imageLoaded = true;

			repaint();

			for (int i = 0; i < 6; i++)
			{
				 File archivoActual = Carpeta;

				 archivoActual = Carpeta.getFullPathName() + "/" + archivosSurround[i];

				 ScopedPointer<AudioFormatReader> readOperator;

				 readOperator = formatManager.createReaderFor(archivoActual);

				 if (readOperator != nullptr)
				 {
					 int numSamples = readOperator->lengthInSamples;
					 int frecMuestreo = readOperator->sampleRate;
					 int cantCanales = readOperator->numChannels;

					 AudioBuffer<float> localAudioBuffer;

					 localAudioBuffer.setSize(cantCanales, numSamples, false);

					 readOperator->read(&localAudioBuffer, 0, numSamples, 0, true, true);

					 processor.loadImpulseResponseToEngine(localAudioBuffer, i, readOperator->sampleRate, readOperator->lengthInSamples);

					 if (archivoActual.getFileName() == archivosSurround[i])
					 {
						 labelList[i]->setText(archivosSurround[i] + ": Cargado", dontSendNotification);
					 }

					 if (i >= 5)
						 processor.isLoaded = true;

				 }
				 else
				 {
					 AlertWindow errorMessage("Hola", "Hola", AlertWindow::AlertIconType::WarningIcon);
					 addAndMakeVisible(errorMessage);

					 errorMessage.showMessageBoxAsync(AlertWindow::AlertIconType::WarningIcon, "Error", "Error Cargando Archivo");

					 imageLoaded = false;
					 break;
				 }
			}

		}
        //[/UserButtonCode_loadButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == systemComboBox.get())
    {
        //[UserComboBoxCode_systemComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_systemComboBox]
    }
    else if (comboBoxThatHasChanged == referenceComboBox.get())
    {
        //[UserComboBoxCode_referenceComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_referenceComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor"
                 constructorParams="PluginAudioProcessor&amp; p" variableInitialisers="AudioProcessorEditor (&amp;p), processor (p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="900" initialHeight="700">
  <BACKGROUND backgroundColour="ff0f0f0f">
    <RECT pos="30 30 500 340" fill="solid: 54373636" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: ff8b8b8b"/>
    <IMAGE pos="40 40 480 320" resource="" opacity="1.00000000000000000000"
           mode="0"/>
    <ROUNDRECT pos="580 320 300 180" cornerSize="10.00000000000000000000" fill="linear: 352 128, 480 672, 0=d7bcbcbc, 1=8d29a4b2"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="linear: 552 200, 888 568, 0=ff00d5ff, 1=ffe4dcdc"/>
    <IMAGE pos="580 40 300 180" resource="" opacity="1.00000000000000000000"
           mode="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="loadButton" id="cf389aeffe3b5c1d" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="40 392 480 32" bgColOff="ff5c9ba4"
              textCol="ffffffff" buttonText="Cargar Recinto" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="systemComboBox" id="80bab03fb03b0987" memberName="systemComboBox"
            virtualName="" explicitFocusOrder="0" pos="580 249 300 40" editable="0"
            layout="33" items="Aud&#237;fonos&#10;Opsodis" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="activeSystemLabel" id="512db482e2caaf6b" memberName="activeSystemLabel"
         virtualName="" explicitFocusOrder="0" pos="585 340 290 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" hiliteCol="bf5cd206" labelText="Sistema Activo"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Maiandra GD" fontsize="20.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
  <LABEL name="systemLabel" id="1c0390452250b5c3" memberName="systemLabel"
         virtualName="" explicitFocusOrder="0" pos="587 389 285 32" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Opsodis" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Maiandra GD"
         fontsize="20.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
  <COMBOBOX name="referenceComboBox" id="b174913a4e65211c" memberName="referenceComboBox"
            virtualName="" explicitFocusOrder="0" pos="589 447 284 32" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="placeLabel" id="29d73d257d591145" memberName="placeLabel"
         virtualName="" explicitFocusOrder="0" pos="584 512 296 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Recinto:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="DescriptionLabel" id="6cd39c0359dce971" memberName="DescriptionLabel"
         virtualName="" explicitFocusOrder="0" pos="584 547 296 93" edTextCol="ff000000"
         edBkgCol="0" labelText="Decripci&#243;n:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="9"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
