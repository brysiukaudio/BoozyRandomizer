/*
  ==============================================================================

    This file was auto-generated!
    Tag url https://store.steampowered.com/tagdata/populartags/english
  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
    title("title", "BOOZY'S GREAT RANDOMIZER"),
    tag1("tag1", "We"),
    tag2("tag2", "Love"),
    tag3("tag3", "Boozy")
{
    addAndMakeVisible(title);
    title.setFont(Font(25));
    title.setJustificationType(Justification::centred);
    addAndMakeVisible(tag1);
    tag1.setJustificationType(Justification::centred);
    addAndMakeVisible(tag2);
    tag2.setJustificationType(Justification::centred);
    addAndMakeVisible(tag3);
    tag3.setJustificationType(Justification::centred);
    
    randomizeButton.reset(new TextButton("RANDOMIZE"));
    addAndMakeVisible(randomizeButton.get());
    randomizeButton->addListener(this);
    tagGenerator.reset(new TagGenerator());

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    title.setBounds(getWidth()/2 - 200, 35, 400, 25);
    tag1.setBounds(getWidth()/4 - 50, getHeight()/2 - 60, 100, 50);
    tag2.setBounds(getWidth()/2 - 50, getHeight() / 2 - 60, 100, 50);
    tag3.setBounds(getWidth()*3/4 - 50, getHeight() / 2 - 60, 100, 50);
    randomizeButton->setBounds(getWidth() / 2 - 50, getHeight() /2 + 10, 100, 50);

}

void MainComponent::buttonClicked(Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == randomizeButton.get())
    {
        StringArray array;
        tagGenerator->getThreeTags(&array);
        tag1.setText(array[0], sendNotification);
        tag2.setText(array[1], sendNotification);
        tag3.setText(array[2], sendNotification);
    }
}