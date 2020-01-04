/*
  ==============================================================================

    TagGenerator.h
    Created: 3 Jan 2020 9:51:04am
    Author:  Ben

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#define NUMBEROFTAGS 3

class TagGenerator : public URL::DownloadTask::Listener
{
public:
    TagGenerator();
    ~TagGenerator();

    void getThreeTags(StringArray* array);
    virtual void finished(URL::DownloadTask* task, bool success);
    void openSearch();
    int getResultCount() { return resultCount; };

private:
    URL steamTagURL;
    URL googleCheckURL;
    var steamTagJSON;
    bool hasInternet = false;
    bool hasFile = false;
    File steamTagFile;
    std::unique_ptr<URL::DownloadTask> dlTask;
    std::unique_ptr<URL::DownloadTask> searchTask0;
    std::unique_ptr<URL::DownloadTask> searchTask1;
    int nextSearchTask = 0;
    StringArray tagNameArray;
    StringArray tagIDArray;
    void parsePopularTags();
    void parseResults(String result);
    int resultCount = 0;

    int currentTags[NUMBEROFTAGS];
};