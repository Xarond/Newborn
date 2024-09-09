#pragma once

#include "NewbornNetElementBasicFields.hpp"
#include "NewbornNetElementFloatFields.hpp"
#include "NewbornItem.hpp"
#include "NewbornToolUserItem.hpp"
#include "NewbornLuaComponents.hpp"
#include "NewbornLuaActorMovementComponent.hpp"
#include "NewbornNetworkedAnimator.hpp"
#include "NewbornLuaAnimationComponent.hpp"
#include "NewbornDurabilityItem.hpp"

namespace Newborn {

NEWBORN_CLASS(AudioInstance);
NEWBORN_CLASS(ActiveItem);

class ActiveItem :
  public Item,
  public DurabilityItem,
  public virtual ToolUserItem,
  public virtual NetElementGroup {
public:
  ActiveItem(Json const& config, String const& directory, Json const& parameters = JsonObject());
  ActiveItem(ActiveItem const& rhs);

  ItemPtr clone() const override;

  void init(ToolUserEntity* owner, ToolHand hand) override;
  void uninit() override;

  void update(float dt, FireMode fireMode, bool shifting, HashSet<MoveControlType> const& moves) override;

  List<DamageSource> damageSources() const override;
  List<PolyF> shieldPolys() const override;

  List<PhysicsForceRegion> forceRegions() const override;

  bool holdingItem() const;
  Maybe<String> backArmFrame() const;
  Maybe<String> frontArmFrame() const;
  bool twoHandedGrip() const;
  bool recoil() const;
  bool outsideOfHand() const;

  float armAngle() const;
  Maybe<Direction> facingDirection() const;

  // Hand drawables are in hand-space, everything else is in world space.
  List<Drawable> handDrawables() const;
  List<pair<Drawable, Maybe<EntityRenderLayer>>> entityDrawables() const;
  List<LightSource> lights() const;
  List<AudioInstancePtr> pullNewAudios();
  List<Particle> pullNewParticles();

  Maybe<String> cursor() const;

  Maybe<Json> receiveMessage(String const& message, bool localMessage, JsonArray const& args = {});

  float durabilityStatus() override;

private:
  Vec2F armPosition(Vec2F const& offset) const;
  Vec2F handPosition(Vec2F const& offset) const;

  LuaCallbacks makeActiveItemCallbacks();
  LuaCallbacks makeScriptedAnimationCallbacks();

  mutable LuaMessageHandlingComponent<LuaActorMovementComponent<LuaUpdatableComponent<LuaStorableComponent<LuaWorldComponent<LuaBaseComponent>>>>> m_script;

  NetworkedAnimator m_itemAnimator;
  NetworkedAnimator::DynamicTarget m_itemAnimatorDynamicTarget;

  mutable LuaAnimationComponent<LuaUpdatableComponent<LuaWorldComponent<LuaBaseComponent>>> m_scriptedAnimator;

  HashMap<AudioInstancePtr, Vec2F> m_activeAudio;

  FireMode m_currentFireMode;
  Maybe<String> m_cursor;

  NetElementBool m_holdingItem;
  NetElementData<Maybe<String>> m_backArmFrame;
  NetElementData<Maybe<String>> m_frontArmFrame;
  NetElementBool m_twoHandedGrip;
  NetElementBool m_recoil;
  NetElementBool m_outsideOfHand;
  NetElementFloat m_armAngle;
  NetElementData<Maybe<Direction>> m_facingDirection;
  NetElementData<List<DamageSource>> m_damageSources;
  NetElementData<List<DamageSource>> m_itemDamageSources;
  NetElementData<List<PolyF>> m_shieldPolys;
  NetElementData<List<PolyF>> m_itemShieldPolys;
  NetElementData<List<PhysicsForceRegion>> m_forceRegions;
  NetElementData<List<PhysicsForceRegion>> m_itemForceRegions;
  NetElementHashMap<String, Json> m_scriptedAnimationParameters;
};

}
