/*
  ==============================================================================

    TagGenerator.h
    Created: 3 Jan 2020 9:51:04am
    Author:  Ben

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class TagGenerator : public URL::DownloadTask::Listener
{
public:
    TagGenerator();
    ~TagGenerator();

    void getThreeTags(StringArray* array);
    virtual void finished(URL::DownloadTask* task, bool success);


private:
    URL steamTagURL;
    URL googleCheckURL;
    var steamTagJSON;
    bool hasInternet = false;
    bool hasFile = false;
    File steamTagFile;
    std::unique_ptr<URL::DownloadTask> dlTask;
    StringArray tagArray;
    void parsePopularTags();
};