/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MenuTestAudioProcessorEditor::MenuTestAudioProcessorEditor (MenuTestAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible(comboboxMenu);
    comboboxMenu.setTextWhenNothingSelected("Combobox");
    comboboxMenu.addItem("Combobox Text1", 1);
    comboboxMenu.addItem("Combobox Text2", 2);

    addAndMakeVisible(buttonTriggerMenu);
    buttonTriggerMenu.setButtonText("Button with Menu");
    buttonTriggerMenu.onClick = [this]{this->showPopupMenu();};

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

MenuTestAudioProcessorEditor::~MenuTestAudioProcessorEditor()
{
}

//==============================================================================
void MenuTestAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MenuTestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();
    bounds.removeFromTop(30);
    comboboxMenu.setBounds(bounds.removeFromLeft(170).withHeight(50));
    bounds.removeFromLeft(30);
    buttonTriggerMenu.setBounds(bounds.removeFromLeft(170).withHeight(50));
}

void MenuTestAudioProcessorEditor::showPopupMenu()
{
    PopupMenu menu;
    menu.addItem(1, "Menu Text1");
    menu.addItem(2, "Menu Text2");

    // with `showMenuAsync` the popup won't be a modal window
    // also when parent component is NOT nullptr then if menu is shown and the user moves the plugin window,
    // the menu will still be visible but inside the plugin window.
    menu.showMenuAsync (PopupMenu::Options().withParentComponent(this)
                                            .withTargetComponent (&buttonTriggerMenu)
                                            .withItemThatMustBeVisible (1) // change this depending on the current menu state
                                            .withMinimumWidth (buttonTriggerMenu.getWidth())
                                            .withMaximumNumColumns (1)
                                            .withStandardItemHeight (buttonTriggerMenu.getHeight()),
                        ModalCallbackFunction::create([this](int result){this->menuCallback(result);}));
}

void MenuTestAudioProcessorEditor::menuCallback(int result)
{
    if (result > 0)
        buttonTriggerMenu.setButtonText("Menu Text" + String(result));}
