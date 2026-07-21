#include "pageStore.h"

#include <fstream>
#include <sstream>
#include <iostream>

PageStorage::PageStorage(const std::string& path)
{
    filePath = path;
    cachedCount = 0;
    initialized = false;
}

void PageStorage::initializeCount()
{
    if (initialized)
        return;

    std::ifstream file(filePath);

    if (!file.is_open())
    {
        initialized = true;
        cachedCount = 0;
        return;
    }

    cachedCount = 0;

    std::string line;

    while (getline(file, line))
    {
        if (line == "###PAGE###")
            cachedCount++;
    }

    initialized = true;
}

int PageStorage::pageCount()
{
    initializeCount();
    return cachedCount;
}

bool PageStorage::hasPage(const std::string& url)
{
    std::ifstream file(filePath);

    if (!file.is_open())
        return false;

    std::string line;

    while (getline(file, line))
    {
        if (line == "###PAGE###")
        {
            getline(file, line);

            if (line == "URL:" + url)
                return true;
        }
    }

    return false;
}

