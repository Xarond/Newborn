#pragma once

#include "NewbornGameTypes.hpp"
#include "NewbornItem.hpp"
#include "NewbornStatusEffectItem.hpp"
#include "NewbornEffectSourceItem.hpp"
#include "NewbornPreviewableItem.hpp"
#include "NewbornSwingableItem.hpp"
namespace Newborn {

NEWBORN_CLASS(ArmorItem);
NEWBORN_CLASS(HeadArmor);
NEWBORN_CLASS(ChestArmor);
NEWBORN_CLASS(LegsArmor);
NEWBORN_CLASS(BackArmor);

class ArmorItem : public Item, public EffectSourceItem, public SwingableItem {
public:
  ArmorItem(Json const& config, String const& directory, Json const& data);
  virtual ~ArmorItem() {}

  virtual List<PersistentStatusEffect> statusEffects() const override;
  virtual StringSet effectSources() const override;

  virtual List<Drawable> drawables() const override;

  virtual float getAngle(float aimAngle) override;

  virtual void fire(FireMode mode, bool shifting, bool edgeTriggered) override;
  virtual void fireTriggered() override;

  List<String> const& colorOptions();

  Directives const& directives() const;

  bool hideBody() const;

  Maybe<String> const& techModule() const;

private:
  void refreshIconDrawables();
  void refreshStatusEffects();

  List<String> m_colorOptions;
  List<PersistentStatusEffect> m_statusEffects;
  StringSet m_effectSources;
  Directives m_directives;
  bool m_hideBody;
  Maybe<String> m_techModule;
};

class HeadArmor : public ArmorItem, public PreviewableItem {
public:
  HeadArmor(Json const& config, String const& directory, Json const& data);
  virtual ~HeadArmor() {}

  virtual ItemPtr clone() const;

  String const& frameset(Gender gender) const;
  Directives const& maskDirectives() const;

  virtual List<Drawable> preview(PlayerPtr const& viewer = {}) const;

private:
  String m_maleImage;
  String m_femaleImage;
  Directives m_maskDirectives;
};

class ChestArmor : public ArmorItem, public PreviewableItem {
public:
  ChestArmor(Json const& config, String const& directory, Json const& data);
  virtual ~ChestArmor() {}

  virtual ItemPtr clone() const;

  // Will have :run, :normal, :duck, and :portrait
  String const& bodyFrameset(Gender gender) const;
  // Will have :idle[1-5], :duck, :rotation, :walk[1-5], :run[1-5], :jump[1-4],
  // :fall[1-4]
  String const& frontSleeveFrameset(Gender gender) const;
  // Same as FSleeve
  String const& backSleeveFrameset(Gender gender) const;

  virtual List<Drawable> preview(PlayerPtr const& viewer = {}) const;

private:
  String m_maleBodyImage;
  String m_maleFrontSleeveImage;
  String m_maleBackSleeveImage;

  String m_femaleBodyImage;
  String m_femaleFrontSleeveImage;
  String m_femaleBackSleeveImage;
};

class LegsArmor : public ArmorItem, public PreviewableItem {
public:
  LegsArmor(Json const& config, String const& directory, Json const& data);
  virtual ~LegsArmor() {}

  virtual ItemPtr clone() const;

  // Will have :idle, :duck, :walk[1-8], :run[1-8], :jump[1-4], :fall[1-4]
  String const& frameset(Gender gender) const;

  virtual List<Drawable> preview(PlayerPtr const& viewer = {}) const;

private:
  String m_maleImage;
  String m_femaleImage;
};

class BackArmor : public ArmorItem, public PreviewableItem {
public:
  BackArmor(Json const& config, String const& directory, Json const& data);
  virtual ~BackArmor() {}

  virtual ItemPtr clone() const;

  // Will have :idle, :duck, :walk[1-8], :run[1-8], :jump[1-4], :fall[1-4]
  String const& frameset(Gender gender) const;

  virtual List<Drawable> preview(PlayerPtr const& viewer = {}) const;

private:
  String m_maleImage;
  String m_femaleImage;
};

}
