/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TagGenerator.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
                        public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    virtual void buttonClicked(Button*);

private:
    //==============================================================================
    // Your private member variables go here...
    std::unique_ptr<TextButton> randomizeButton;
    std::unique_ptr<TextButton> openButton;
    Label title;
    Label tag1;
    Label tag2;
    Label tag3;
    Label result;
    Label failedResults;
    int numOfResults = 0;
    int totalFailed = 0;
    bool runningRandomizer = false;
    bool updateText = false;
    StringArray tagsArray;
    std::shared_ptr<TagGenerator> tagGenerator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)

};

class RandomizerTask : public ThreadWithProgressWindow
{
public:
    RandomizerTask(std::shared_ptr<TagGenerator> tagGenerator, int* resultPointer, int* failedResultsPointer, StringArray* stringArray) : ThreadWithProgressWindow("Randomizing...", true, true)
    {
        result = resultPointer;
        this->tagGenerator = tagGenerator;
        array = stringArray;
        failed = failedResultsPointer;
    }

    void run()
    {
        int countresult = 0;
        int i = 0;
        while (countresult == 0)
        {
            tagGenerator->getThreeTags(array);
            countresult = tagGenerator->getResultCount();
            setProgress(-1);
            wait(50);
            i++;
        }
        *failed = i;
        *result = countresult;
        bool stop = true;
    }
private:
    std::shared_ptr<TagGenerator> tagGenerator;
    int* result;
    int* failed;
    StringArray* array;
};
