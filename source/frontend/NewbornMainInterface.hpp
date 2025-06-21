#pragma once

#include "NewbornInventory.hpp"
#include "NewbornInteractionTypes.hpp"
#include "NewbornItemDescriptor.hpp"
#include "NewbornGameTypes.hpp"
#include "NewbornInterfaceCursor.hpp"
#include "NewbornMainInterfaceTypes.hpp"
#include "NewbornWarping.hpp"

namespace Newborn {

NEWBORN_CLASS(UniverseClient);
NEWBORN_CLASS(WorldPainter);
NEWBORN_CLASS(Item);
NEWBORN_CLASS(Chat);
NEWBORN_CLASS(ClientCommandProcessor);
NEWBORN_CLASS(OptionsMenu);
NEWBORN_CLASS(WirePane);
NEWBORN_CLASS(ActionBar);
NEWBORN_CLASS(TeamBar);
NEWBORN_CLASS(StatusPane);
NEWBORN_CLASS(ContainerPane);
NEWBORN_CLASS(CraftingPane);
NEWBORN_CLASS(MerchantPane);
NEWBORN_CLASS(CodexInterface);
NEWBORN_CLASS(SongbookInterface);
NEWBORN_CLASS(QuestLogInterface);
NEWBORN_CLASS(AiInterface);
NEWBORN_CLASS(PopupInterface);
NEWBORN_CLASS(ConfirmationDialog);
NEWBORN_CLASS(JoinRequestDialog);
NEWBORN_CLASS(TeleportDialog);
NEWBORN_CLASS(LabelWidget);
NEWBORN_CLASS(Cinematic);
NEWBORN_CLASS(NameplatePainter);
NEWBORN_CLASS(QuestIndicatorPainter);
NEWBORN_CLASS(RadioMessagePopup);
NEWBORN_CLASS(Quest);
NEWBORN_CLASS(QuestTrackerPane);
NEWBORN_CLASS(ContainerInteractor);
NEWBORN_CLASS(ScriptPane);
NEWBORN_CLASS(ChatBubbleManager);
NEWBORN_CLASS(CanvasWidget);

NEWBORN_STRUCT(GuiMessage);
NEWBORN_CLASS(MainInterface);

struct GuiMessage {
  GuiMessage();
  GuiMessage(String const& message, float cooldown, float spring = 0);

  String message;
  float cooldown;
  float springState;
};

class MainInterface {
public:
  enum RunningState {
    Running,
    ReturnToTitle
  };

  MainInterface(UniverseClientPtr client, WorldPainterPtr painter, CinematicPtr cinematicOverlay);

  ~MainInterface();

  RunningState currentState() const;

  MainInterfacePaneManager* paneManager();

  bool escapeDialogOpen() const;

  void openCraftingWindow(Json const& config, EntityId sourceEntityId = NullEntityId);
  void openMerchantWindow(Json const& config, EntityId sourceEntityId = NullEntityId);
  void togglePlainCraftingWindow();
  void displayDefaultPanes();


  bool windowsOpen() const;

  MerchantPanePtr activeMerchantPane() const;

  // Return true if this event was consumed or should be handled elsewhere.
  bool handleInputEvent(InputEvent const& event);
  // Return true if mouse / keyboard events are currently locked here
  bool inputFocus() const;
  // If input is focused, should MainInterface also accept text input events?
  bool textInputActive() const;

  void handleInteractAction(InteractAction interactAction);

  void preUpdate(float dt);
  // Handles incoming client messages, aims main player, etc.
  void update(float dt);

  // Render things e.g. quest indicators that should be drawn in the world
  // behind interface e.g. chat bubbles
  void renderInWorldElements();
  void render();

  Vec2F cursorWorldPosition() const;

  bool isDebugDisplayed();

  void doChat(String const& chat, bool addToHistory);

  void queueMessage(String const& message, Maybe<float> cooldown, float spring);
  void queueMessage(String const& message);

  void queueItemPickupText(ItemPtr const& item);
  void queueJoinRequest(pair<String, RpcPromiseKeeper<P2PJoinRequestReply>> request);

  bool fixedCamera() const;
  bool hudVisible() const;
  void setHudVisible(bool visible = true);

  void warpToOrbitedWorld(bool deploy = false);
  void warpToOwnShip();
  void warpTo(WarpAction const& warpAction);

  CanvasWidgetPtr fetchCanvas(String const& canvasName, bool ignoreInterfaceScale = false);

  ClientCommandProcessorPtr commandProcessor() const;

  struct ScriptPaneInfo {
    ScriptPanePtr scriptPane;
    Json config;
    EntityId sourceEntityId;
    bool visible;
    Vec2I position;
  };

  void takeScriptPanes(List<ScriptPaneInfo>& out);
  void reviveScriptPanes(List<ScriptPaneInfo>& panes);
private:
  PanePtr createEscapeDialog();

  float interfaceScale() const;
  unsigned windowHeight() const;
  unsigned windowWidth() const;
  Vec2I mainBarPosition() const;

  void renderBreath();
  void renderMessages();
  void renderMonsterHealthBar();
  void renderSpecialDamageBar();
  void renderMainBar();
  void renderWindows();
  void renderDebug();

  void updateCursor();
  void renderCursor();

  bool overButton(PolyI buttonPoly, Vec2I const& mousePos) const;

  bool overlayClick(Vec2I const& mousePos, MouseButton mouseButton);

  void displayScriptPane(ScriptPanePtr& scriptPane, EntityId sourceEntity);

  GuiContext* m_guiContext{nullptr};
  MainInterfaceConfigConstPtr m_config;
  InterfaceCursor m_cursor;

  RunningState m_state{Running};

  UniverseClientPtr m_client;
  WorldPainterPtr m_worldPainter;
  CinematicPtr m_cinematicOverlay;

  MainInterfacePaneManager m_paneManager;

  QuestLogInterfacePtr m_questLogInterface;

  InventoryPanePtr m_inventoryWindow;
  CraftingPanePtr m_plainCraftingWindow;
  CraftingPanePtr m_craftingWindow;
  MerchantPanePtr m_merchantWindow;
  CodexInterfacePtr m_codexInterface;
  OptionsMenuPtr m_optionsMenu;
  ContainerPanePtr m_containerPane;
  PopupInterfacePtr m_popupInterface;
  ConfirmationDialogPtr m_confirmationDialog;
  JoinRequestDialogPtr m_joinRequestDialog;
  TeleportDialogPtr m_teleportDialog;
  QuestTrackerPanePtr m_questTracker;
  ScriptPanePtr m_mmUpgrade;
  ScriptPanePtr m_collections;
  Map<EntityId, PanePtr> m_interactionScriptPanes;

  StringMap<CanvasWidgetPtr> m_canvases;

  ChatPtr m_chat;
  ClientCommandProcessorPtr m_clientCommandProcessor;
  RadioMessagePopupPtr m_radioMessagePopup;
  WirePanePtr m_wireInterface;

  ActionBarPtr m_actionBar;
  Vec2I m_cursorScreenPos{};
  ItemSlotWidgetPtr m_cursorItem;
  Maybe<String> m_cursorTooltip;

  LabelWidgetPtr m_planetText;
  GameTimer m_planetNameTimer;

  GameTimer m_debugSpatialClearTimer;
  GameTimer m_debugMapClearTimer;
  RectF m_debugTextRect{RectF::null()};

  NameplatePainterPtr m_nameplatePainter;
  QuestIndicatorPainterPtr m_questIndicatorPainter;
  ChatBubbleManagerPtr m_chatBubbleManager;

  bool m_disableHud = false;

  String m_lastCommand;

  LinkedList<GuiMessagePtr> m_messages;
  HashMap<ItemDescriptor, std::pair<size_t, GuiMessagePtr>> m_itemDropMessages;
  unsigned m_messageOverflow{};
  GuiMessagePtr m_overflowMessage;

  List<pair<String, RpcPromiseKeeper<P2PJoinRequestReply>>> m_queuedJoinRequests;

  EntityId m_lastMouseoverTarget{NullEntityId};
  GameTimer m_stickyTargetingTimer;
  int m_portraitScale{};

  EntityId m_specialDamageBarTarget{NullEntityId};
  float m_specialDamageBarValue{};

  ContainerInteractorPtr m_containerInteractor;
};

}
