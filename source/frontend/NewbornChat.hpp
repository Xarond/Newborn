#pragma once

#include "NewbornBaseScriptPane.hpp"
#include "NewbornChatTypes.hpp"

namespace Newborn {

NEWBORN_CLASS(UniverseClient);
NEWBORN_CLASS(TextBoxWidget);
NEWBORN_CLASS(LabelWidget);
NEWBORN_CLASS(ButtonWidget);
NEWBORN_CLASS(ImageStretchWidget);
NEWBORN_CLASS(CanvasWidget);
NEWBORN_CLASS(Chat);

class Chat : public BaseScriptPane {
public:
  Chat(UniverseClientPtr client, Json const&);

  void startChat();
  void startCommand();
  bool hasFocus() const override;
  virtual bool sendEvent(InputEvent const& event) override;
  void stopChat();
  virtual void renderImpl() override;
  virtual void hide() override;

  virtual void update(float dt) override;

  void addLine(String const& text, bool showPane = true);
  void addMessages(List<ChatReceivedMessage> const& messages, bool showPane = true);
  void addHistory(String const& chat);
  void clear(size_t count = std::numeric_limits<size_t>::max());

  String currentChat() const;
  bool setCurrentChat(String const& chat, bool moveCursor = false);
  void clearCurrentChat();

  ChatSendMode sendMode() const;

  void incrementIndex();
  void decrementIndex();

  float visible() const;

  void scrollUp();
  void scrollDown();
  void scrollBottom();

private:
  struct LogMessage {
    MessageContext::Mode mode;
    String portrait;
    String text;
  };

  void updateBottomButton();

  UniverseClientPtr m_client;
  bool m_scripted;

  TextBoxWidgetPtr m_textBox;
  LabelWidgetPtr m_say;
  ButtonWidgetPtr m_bottomButton;
  ButtonWidgetPtr m_upButton;
  Deque<String> m_chatHistory;
  unsigned m_chatPrevIndex;
  int64_t m_timeChatLastActive;
  float m_chatVisTime;
  float m_fadeRate;
  TextStyle m_chatTextStyle;
  unsigned m_chatHistoryLimit;
  int m_historyOffset;
  String m_chatFormatString;

  CanvasWidgetPtr m_chatLog;
  Vec2I m_chatLogPadding;

  ImageStretchWidgetPtr m_background;
  int m_defaultHeight;
  int m_bodyHeight;
  int m_expandedBodyHeight;
  bool m_expanded;

  void updateSize();

  Vec2I m_portraitTextOffset;
  Vec2I m_portraitImageOffset;
  float m_portraitScale;
  int m_portraitVerticalMargin;
  String m_portraitBackground;

  Map<MessageContext::Mode, String> m_colorCodes;
  Deque<LogMessage> m_receivedMessages;

  Set<MessageContext::Mode> m_modeFilter;
  ChatSendMode m_sendMode;
};

}
