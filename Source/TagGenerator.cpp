/*
  ==============================================================================

    TagGenerator.cpp
    Created: 3 Jan 2020 9:51:04am
    Author:  Ben

  ==============================================================================
*/

#include "TagGenerator.h"
#include "MainComponent.h"
#include <regex>

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

    currentTags[0] = -1;
    currentTags[1] = -1;
    currentTags[2] = -1;
}
TagGenerator::~TagGenerator()
{

}

void TagGenerator::getThreeTags(StringArray* array)
{
    int tag1 = -1, tag2 = -1, tag3 = -1;
    int tagSize = tagNameArray.size();
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



    currentTags[0] = tag1;
    currentTags[1] = tag2;
    currentTags[2] = tag3;
    if (hasInternet)
    {
        
        String string = "https://store.steampowered.com/search/?category1=998&tags=";
        string += String(tagIDArray[currentTags[0]]);
        string += String("%2C");
        string += String(tagIDArray[currentTags[1]]);
        string += String("%2C");
        string += String(tagIDArray[currentTags[2]]);
        URL searchURL(string);
        std::unique_ptr<WebInputStream> inputStream;
        String data;
        inputStream.reset(dynamic_cast<WebInputStream*>(searchURL.createInputStream(false)));
        data = inputStream->readEntireStreamAsString();
        parseResults(data);
        array->add(tagNameArray[currentTags[0]]);
        array->add(tagNameArray[currentTags[1]]);
        array->add(tagNameArray[currentTags[2]]);
        
    }



    return;
}

void TagGenerator::parsePopularTags()
{
    steamTagJSON = JSON::parse(steamTagFile);
    Array<var> *jsonArray = steamTagJSON.getArray();

    
    for (int i = 0; i < jsonArray->size(); i++)
    {
        tagNameArray.add((*jsonArray)[i].getProperty("name",var()).toString());
        tagIDArray.add((*jsonArray)[i].getProperty("tagid", var()).toString());

    }
}

void TagGenerator::parseResults(String result)
{
   
    std::string cString = result.toStdString();
    std::smatch m;
    std::regex re("<div.*>(.*) results? match(es)? your search.");
    std::regex_search(cString, m, re);
    if (m.size() == 3)
    {
        std::ssub_match base_sub_match = m[1];
        std::string base = base_sub_match.str();
        resultCount = String(base).getIntValue();
    }
    else
    {
        resultCount = 0;
    }

}

void TagGenerator::openSearch()
{

    if (currentTags[0] != -1)
    {
        String string = "https://store.steampowered.com/search/?category1=998&tags=";
        string += String(tagIDArray[currentTags[0]]);
        string += String("%2C");
        string += String(tagIDArray[currentTags[1]]);
        string += String("%2C");
        string += String(tagIDArray[currentTags[2]]);
        URL searchURL(string);


        searchURL.launchInDefaultBrowser();
    }
    
}

void TagGenerator::finished(URL::DownloadTask* task, bool success)
{
    if (task == dlTask.get())
    {
        if (success)
        {
            parsePopularTags();
        }
        else
        {
            AlertWindow::showNativeDialogBox("Tag Download Failed", "Downloading the tag file failed, Check your internet and try again by hitting randomize", false);
        }
    }
    
}