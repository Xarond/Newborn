#pragma once

#include "NewbornRootBase.hpp"
#include "NewbornJson.hpp"
#include "NewbornLogging.hpp"
#include "NewbornListener.hpp"
#include "NewbornConfiguration.hpp"

namespace Newborn {

NEWBORN_CLASS(ItemDatabase);
NEWBORN_CLASS(MaterialDatabase);
NEWBORN_CLASS(ObjectDatabase);
NEWBORN_CLASS(PlantDatabase);
NEWBORN_CLASS(ProjectileDatabase);
NEWBORN_CLASS(MonsterDatabase);
NEWBORN_CLASS(NpcDatabase);
NEWBORN_CLASS(StagehandDatabase);
NEWBORN_CLASS(VehicleDatabase);
NEWBORN_CLASS(PlayerFactory);
NEWBORN_CLASS(EntityFactory);
NEWBORN_CLASS(TerrainDatabase);
NEWBORN_CLASS(BiomeDatabase);
NEWBORN_CLASS(LiquidsDatabase);
NEWBORN_CLASS(StatusEffectDatabase);
NEWBORN_CLASS(DamageDatabase);
NEWBORN_CLASS(ParticleDatabase);
NEWBORN_CLASS(EffectSourceDatabase);
NEWBORN_CLASS(FunctionDatabase);
NEWBORN_CLASS(TreasureDatabase);
NEWBORN_CLASS(DungeonDefinitions);
NEWBORN_CLASS(TilesetDatabase);
NEWBORN_CLASS(StatisticsDatabase);
NEWBORN_CLASS(EmoteProcessor);
NEWBORN_CLASS(SpeciesDatabase);
NEWBORN_CLASS(ImageMetadataDatabase);
NEWBORN_CLASS(VersioningDatabase);
NEWBORN_CLASS(QuestTemplateDatabase);
NEWBORN_CLASS(AiDatabase);
NEWBORN_CLASS(TechDatabase);
NEWBORN_CLASS(CodexDatabase);
NEWBORN_CLASS(BehaviorDatabase);
NEWBORN_CLASS(TenantDatabase);
NEWBORN_CLASS(PatternedNameGenerator);
NEWBORN_CLASS(DanceDatabase);
NEWBORN_CLASS(SpawnTypeDatabase);
NEWBORN_CLASS(RadioMessageDatabase);
NEWBORN_CLASS(CollectionDatabase);

NEWBORN_CLASS(Root);

// Singleton Root object for newborn providing access to the unique
// Configuration class, as well as the assets, root factories, and databases.
// Root, and all members of Root, should be thread safe.  Root initialization
// should be completed before any code dependent on Root is started in any
// thread, and all Root dependent code in any thread should be finished before
// letting Root destruct.

class Root : public RootBase {
public:
    struct Settings {
        Assets::Settings assetsSettings;

        StringList assetSources;

        Json defaultConfiguration;

        String storageDirectory;

        Maybe<String> logDirectory;

        Maybe<String> logFile;

        unsigned logfileBackups;

        LogLevel logLevel;

        bool quiet;

        Maybe<String> runtimeConfigFile;
    };

    static Root* singletonPtr();

    static Root& singleton();

    Root(Settings settings);

    Root(Root const&) = delete;
    Root& operator=(Root const&) = delete;

    ~Root();

    void reload();

    void reloadWithMods(StringList modDirectories);

    void fullyLoad();
    
    void registerReloadListener(ListenerWeakPtr reloadListener);

    String toStoragePath(String const& path) const;

    AssetsConstPtr assets() override;
    ConfigurationPtr configuration() override;

    ObjectDatabaseConstPtr objectDatabase();
    PlantDatabaseConstPtr plantDatabase();
    ProjectileDatabaseConstPtr projectileDatabase();
    MonsterDatabaseConstPtr monsterDatabase();
    NpcDatabaseConstPtr npcDatabase();
    StagehandDatabaseConstPtr stagehandDatabase();
    VehicleDatabaseConstPtr vehicleDatabase();
    PlayerFactoryConstPtr playerFactory();

    EntityFactoryConstPtr entityFactory();

    PatternedNameGeneratorConstPtr nameGenerator();

    ItemDatabaseConstPtr itemDatabase();
    MaterialDatabaseConstPtr materialDatabase();
    TerrainDatabaseConstPtr terrainDatabase();
    BiomeDatabaseConstPtr biomeDatabase();
    LiquidsDatabaseConstPtr liquidsDatabase();
    StatusEffectDatabaseConstPtr statusEffectDatabase();
    DamageDatabaseConstPtr damageDatabase();
    ParticleDatabaseConstPtr particleDatabase();
    EffectSourceDatabaseConstPtr effectSourceDatabase();
    FunctionDatabaseConstPtr functionDatabase();
    TreasureDatabaseConstPtr treasureDatabase();
    DungeonDefinitionsConstPtr dungeonDefinitions();
    TilesetDatabaseConstPtr tilesetDatabase();
    StatisticsDatabaseConstPtr statisticsDatabase();
    EmoteProcessorConstPtr emoteProcessor();
    SpeciesDatabaseConstPtr speciesDatabase();
    ImageMetadataDatabaseConstPtr imageMetadataDatabase();
    VersioningDatabaseConstPtr versioningDatabase();
    QuestTemplateDatabaseConstPtr questTemplateDatabase();
    AiDatabaseConstPtr aiDatabase();
    TechDatabaseConstPtr techDatabase();
    CodexDatabaseConstPtr codexDatabase();
    BehaviorDatabaseConstPtr behaviorDatabase();
    TenantDatabaseConstPtr tenantDatabase();
    DanceDatabaseConstPtr danceDatabase();
    SpawnTypeDatabaseConstPtr spawnTypeDatabase();
    RadioMessageDatabaseConstPtr radioMessageDatabase();
    CollectionDatabaseConstPtr collectionDatabase();

private:
    static StringList scanForAssetSources(StringList const& directories, StringList const& manual = {});
    template <typename T, typename... Params>
    static shared_ptr<T> loadMember(shared_ptr<T>& ptr, Mutex& mutex, char const* name, Params&&... params);
    template <typename T>
    static shared_ptr<T> loadMemberFunction(shared_ptr<T>& ptr, Mutex& mutex, char const* name, function<shared_ptr<T>()> loadFunction);

    // m_configurationMutex must be held when calling
    void writeConfig();

    Settings m_settings;

    Mutex m_modsMutex;
    StringList m_modDirectories;

    ListenerGroup m_reloadListeners;

    Json m_lastRuntimeConfig;
    Maybe<String> m_runtimeConfigFile;

    ThreadFunction<void> m_maintenanceThread;
    Mutex m_maintenanceStopMutex;
    ConditionVariable m_maintenanceStopCondition;
    bool m_stopMaintenanceThread;

    AssetsPtr m_assets;
    Mutex m_assetsMutex;

    ConfigurationPtr m_configuration;
    Mutex m_configurationMutex;

    ObjectDatabasePtr m_objectDatabase;
    Mutex m_objectDatabaseMutex;

    PlantDatabasePtr m_plantDatabase;
    Mutex m_plantDatabaseMutex;

    ProjectileDatabasePtr m_projectileDatabase;
    Mutex m_projectileDatabaseMutex;

    MonsterDatabasePtr m_monsterDatabase;
    Mutex m_monsterDatabaseMutex;

    NpcDatabasePtr m_npcDatabase;
    Mutex m_npcDatabaseMutex;

    StagehandDatabasePtr m_stagehandDatabase;
    Mutex m_stagehandDatabaseMutex;

    VehicleDatabasePtr m_vehicleDatabase;
    Mutex m_vehicleDatabaseMutex;

    PlayerFactoryPtr m_playerFactory;
    Mutex m_playerFactoryMutex;

    EntityFactoryPtr m_entityFactory;
    Mutex m_entityFactoryMutex;

    PatternedNameGeneratorPtr m_nameGenerator;
    Mutex m_nameGeneratorMutex;

    ItemDatabasePtr m_itemDatabase;
    Mutex m_itemDatabaseMutex;

    MaterialDatabasePtr m_materialDatabase;
    Mutex m_materialDatabaseMutex;

    TerrainDatabasePtr m_terrainDatabase;
    Mutex m_terrainDatabaseMutex;

    BiomeDatabasePtr m_biomeDatabase;
    Mutex m_biomeDatabaseMutex;

    LiquidsDatabasePtr m_liquidsDatabase;
    Mutex m_liquidsDatabaseMutex;

    StatusEffectDatabasePtr m_statusEffectDatabase;
    Mutex m_statusEffectDatabaseMutex;

    DamageDatabasePtr m_damageDatabase;
    Mutex m_damageDatabaseMutex;

    ParticleDatabasePtr m_particleDatabase;
    Mutex m_particleDatabaseMutex;

    EffectSourceDatabasePtr m_effectSourceDatabase;
    Mutex m_effectSourceDatabaseMutex;

    FunctionDatabasePtr m_functionDatabase;
    Mutex m_functionDatabaseMutex;

    TreasureDatabasePtr m_treasureDatabase;
    Mutex m_treasureDatabaseMutex;

    DungeonDefinitionsPtr m_dungeonDefinitions;
    Mutex m_dungeonDefinitionsMutex;

    TilesetDatabasePtr m_tilesetDatabase;
    Mutex m_tilesetDatabaseMutex;

    StatisticsDatabasePtr m_statisticsDatabase;
    Mutex m_statisticsDatabaseMutex;

    EmoteProcessorPtr m_emoteProcessor;
    Mutex m_emoteProcessorMutex;

    SpeciesDatabasePtr m_speciesDatabase;
    Mutex m_speciesDatabaseMutex;

    ImageMetadataDatabasePtr m_imageMetadataDatabase;
    Mutex m_imageMetadataDatabaseMutex;

    VersioningDatabasePtr m_versioningDatabase;
    Mutex m_versioningDatabaseMutex;

    QuestTemplateDatabasePtr m_questTemplateDatabase;
    Mutex m_questTemplateDatabaseMutex;

    AiDatabasePtr m_aiDatabase;
    Mutex m_aiDatabaseMutex;

    TechDatabasePtr m_techDatabase;
    Mutex m_techDatabaseMutex;

    CodexDatabasePtr m_codexDatabase;
    Mutex m_codexDatabaseMutex;

    BehaviorDatabasePtr m_behaviorDatabase;
    Mutex m_behaviorDatabaseMutex;

    TenantDatabasePtr m_tenantDatabase;
    Mutex m_tenantDatabaseMutex;

    DanceDatabasePtr m_danceDatabase;
    Mutex m_danceDatabaseMutex;

    SpawnTypeDatabasePtr m_spawnTypeDatabase;
    Mutex m_spawnTypeDatabaseMutex;

    RadioMessageDatabasePtr m_radioMessageDatabase;
    Mutex m_radioMessageDatabaseMutex;

    CollectionDatabasePtr m_collectionDatabase;
    Mutex m_collectionDatabaseMutex;
    };

}
