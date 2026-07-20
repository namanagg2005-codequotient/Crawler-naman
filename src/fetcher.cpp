#include "fetcher.h"
#include <string>

std::string Fetcher::fetch(const std::string& url)
{
    CURL* curl = curl_easy_init();

    if (curl == nullptr)
        return "";

    std::string html;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

    curl_easy_setopt(
        curl,
        CURLOPT_USERAGENT,
        "CodeQuotientCrawler/1.0 (https://github.com/yourusername/yourrepo; your-namanaggarwal98124@gmail.com)"
    );

    CURLcode result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if (result != CURLE_OK)
        return "";

    return html;
}

size_t Fetcher::writeCallback(void* contents,size_t size,size_t nmemb,void* userp)
{
    size_t totalBytes = size * nmemb;

    std::string* html = static_cast<std::string*>(userp);
    html->append(static_cast<char*>(contents), totalBytes);

    return totalBytes;
}