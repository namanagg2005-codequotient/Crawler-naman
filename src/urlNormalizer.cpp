#include "urlNormalizer.h"

#include <algorithm>
#include <cctype>
#include <string>

bool URLNormalizer::isAbsoluteURL(const std::string& url) const {
    return (url.length() >= 7 && url.compare(0, 7, "http://") == 0) || (url.length() >= 8 && url.compare(0, 8, "https://") == 0);
}

std::string URLNormalizer::resolveRelativeURL(const std::string& url,const std::string& baseUrl) const {
    if (url.empty())
        return "";

    // Root-relative URL
    if (url[0] == '/') {
        std::size_t schemePos = baseUrl.find("://");
        if (schemePos == std::string::npos)
            return "";
        std::size_t hostEnd = baseUrl.find('/', schemePos + 3);

        if (hostEnd == std::string::npos)
            return baseUrl + url;

        return baseUrl.substr(0, hostEnd) + url;
    }

    // Relative URL
    std::size_t lastSlash = baseUrl.find_last_of('/');

    if (lastSlash == std::string::npos)
        return "";

    return baseUrl.substr(0, lastSlash + 1) + url;
}

std::string URLNormalizer::normalizePath(const std::string& path) const {
    std::string result;
    int i = 0;
    while (i < static_cast<int>(path.length())) {

        // Skip duplicate '/'
        while (i < static_cast<int>(path.length()) &&
               path[i] == '/')
            i++;

        std::string token;

        while (i < static_cast<int>(path.length()) &&
               path[i] != '/') {

            token += path[i];
            i++;
        }

        if (token.empty() || token == ".")
            continue;

        if (token == "..") {

            if (!result.empty()) {

                if (result.back() == '/')
                    result.pop_back();

                while (!result.empty() &&
                       result.back() != '/')
                    result.pop_back();
            }

            continue;
        }

        result += "/";
        result += token;
    }

    if (result.empty())
        return "/";

    return result;
}

