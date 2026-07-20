#include "urlNormalizer.h"

#include <algorithm>
#include <cctype>
#include <string>

bool URLNormalizer::isAbsoluteURL(const std::string& url) const {
    return (url.length() >= 7 && url.compare(0, 7, "http://") == 0) || (url.length() >= 8 && url.compare(0, 8, "https://") == 0);
}

