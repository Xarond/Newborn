#pragma once

#include "NewbornBiMap.hpp"
#include "NewbornJson.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(RadioMessageDatabaseException, NewbornException);
NEWBORN_STRUCT(RadioMessage);
NEWBORN_CLASS(RadioMessageDatabase);

enum class RadioMessageType { Generic, Mission, Quest, Tutorial };
extern EnumMap<RadioMessageType> const RadioMessageTypeNames;

struct RadioMessage {
  String messageId;
  RadioMessageType type;
  bool unique;
  bool important;
  String text;
  String senderName;
  String portraitImage;
  int portraitFrames;
  float portraitSpeed;
  float textSpeed;
  float persistTime;
  String chatterSound;
};

class RadioMessageDatabase {
public:
  RadioMessageDatabase();

  RadioMessage radioMessage(String const& messageName) const;
  RadioMessage createRadioMessage(Json const& config, Maybe<String> const& uniqueId = {}) const;

private:
  StringMap<RadioMessage> m_radioMessages;
};

}
