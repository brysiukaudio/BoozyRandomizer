/*
  ==============================================================================

    TagGenerator.cpp
    Created: 3 Jan 2020 9:51:04am
    Author:  Ben

  ==============================================================================
*/

#include "TagGenerator.h"
#include "TagGenerator.h"

TagGenerator::TagGenerator() :
    steamTagURL("https://store.steampowered.com/tagdata/populartags/english"),
    googleCheckURL("https://www.google.com"),
    steamTagFile(File::getCurrentWorkingDirectory().getChildFile("tags.json"))
{
    int checkStatus = 0;

    std::unique_ptr<InputStream> checkStream;
    checkStream.reset(googleCheckURL.createInputStream(false, nullptr, nullptr, {}, 1000, nullptr, &checkStatus));
    hasInternet = (checkStatus == 200);
    if (hasInternet)
    {
        dlTask.reset(steamTagURL.downloadToFile(steamTagFile, String(), this));
    }

}
TagGenerator::~TagGenerator()
{

}

void TagGenerator::getThreeTags(StringArray* array)
{
    int tag1 = -1, tag2 = -1, tag3 = -1;
    int tagSize = tagArray.size();
    Random rnd;
    tag1 = rnd.nextInt(tagSize);
    do
    {
        tag2 = rnd.nextInt(tagSize);
    } while (tag2 == tag1);
    do
    {
        tag3 = rnd.nextInt(tagSize);
    } while (tag3 == tag1 || tag3 == tag2);

    array->add(tagArray[tag1]);
    array->add(tagArray[tag2]);
    array->add(tagArray[tag3]);

    return;
}

void TagGenerator::parsePopularTags()
{
    steamTagJSON = JSON::parse(steamTagFile);
    Array<var> *jsonArray = steamTagJSON.getArray();

    
    for (int i = 0; i < jsonArray->size(); i++)
    {
        tagArray.add((*jsonArray)[i].getProperty("name",var()).toString());
    }
}

void TagGenerator::finished(URL::DownloadTask* task, bool success)
{
    if (success)
    {
        parsePopularTags();
    }
    else
    {
        AlertWindow::showNativeDialogBox("Tag Download Failed", "Downloading the tag file failed, Check your internet and try again by hitting randomize",false);
    }
}