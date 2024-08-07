#pragma once

#include "NewbornJson.hpp"

namespace Newborn {

NEWBORN_CLASS(UserGeneratedContentService);

class UserGeneratedContentService {
public: 
    ~UserGeneratedContentService() = default;

    virtual StringList subscribedContentIds() const = 0;

    virtual Maybe<String> contentDownloadDirectory(String const& contentId) const = 0

    virtual bool triggerContentDownload() = 0
};

}