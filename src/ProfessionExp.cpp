/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "Chat.h"
#include "Config.h"
#include "ConfigValueCache.h"
#include "Player.h"
#include "ScriptMgr.h"

enum class PEConfig
{
    ALCHEMY_ENABLED,
    ALCHEMY_EXPERIENCE,
    BLACKSMITH_ENABLED,
    BLACKSMITH_EXPERIENCE,
    COOKING_ENABLED,
    COOKING_EXPERIENCE,
    DISENCHANTING_ENABLED,
    DISENCHANTING_EXPERIENCE,
    ENCHANTING_ENABLED,
    ENCHANTING_EXPERIENCE,
    ENGINEERING_ENABLED,
    ENGINEERING_EXPERIENCE,
    FISHING_ENABLED,
    FISHING_EXPERIENCE,
    FIRST_AID_ENABLED,
    FIRST_AID_EXPERIENCE,
    HERBALISM_ENABLED,
    HERBALISM_EXPERIENCE,
    INSCRIPTION_ENABLED,
    INSCRIPTION_EXPERIENCE,
    JEWELCRAFTING_ENABLED,
    JEWELCRAFTING_EXPERIENCE,
    LEATHERWORKING_ENABLED,
    LEATHERWORKING_EXPERIENCE,
    LOCKPICK_ENABLED,
    LOCKPICK_EXPERIENCE,
    MILLING_ENABLED,
    MILLING_EXPERIENCE,
    MINING_ENABLED,
    MINING_EXPERIENCE,
    PROSPECTING_ENABLED,
    PROSPECTING_EXPERIENCE,
    SKINNING_ENABLED,
    SKINNING_EXPERIENCE,
    SMELTING_ENABLED,
    SMELTING_EXPERIENCE,
    TAILORING_ENABLED,
    TAILORING_EXPERIENCE,
    MULT_GRAY,
    MULT_GREEN,
    MULT_YELLOW,
    MULT_ORANGE,

    NUM_CONFIGS,
};

class PEConfigData : public ConfigValueCache<PEConfig>
{
public:
    PEConfigData() : ConfigValueCache(PEConfig::NUM_CONFIGS) { };

    void BuildConfigCache() override
    {
        SetConfigValue<bool>(PEConfig::ALCHEMY_ENABLED,            "ProfessionExperience.Alchemy.Enabled",           false);
        SetConfigValue<float>(PEConfig::ALCHEMY_EXPERIENCE,        "ProfessionExperience.Alchemy.Experience",        0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::BLACKSMITH_ENABLED,         "ProfessionExperience.Blacksmith.Enabled",        false);
        SetConfigValue<float>(PEConfig::BLACKSMITH_EXPERIENCE,     "ProfessionExperience.Blacksmith.Experience",     0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::COOKING_ENABLED,            "ProfessionExperience.Cooking.Enabled",           false);
        SetConfigValue<float>(PEConfig::COOKING_EXPERIENCE,        "ProfessionExperience.Cooking.Experience",        0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::DISENCHANTING_ENABLED,      "ProfessionExperience.Disenchanting.Enabled",     false);
        SetConfigValue<float>(PEConfig::DISENCHANTING_EXPERIENCE,  "ProfessionExperience.Disenchanting.Experience",  0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::ENCHANTING_ENABLED,         "ProfessionExperience.Enchanting.Enabled",        false);
        SetConfigValue<float>(PEConfig::ENCHANTING_EXPERIENCE,     "ProfessionExperience.Enchanting.Experience",     0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::ENGINEERING_ENABLED,        "ProfessionExperience.Engineering.Enabled",       false);
        SetConfigValue<float>(PEConfig::ENGINEERING_EXPERIENCE,    "ProfessionExperience.Engineering.Experience",    0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::FISHING_ENABLED,            "ProfessionExperience.Fishing.Enabled",           true);
        SetConfigValue<float>(PEConfig::FISHING_EXPERIENCE,        "ProfessionExperience.Fishing.Experience",        0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::FIRST_AID_ENABLED,          "ProfessionExperience.FirstAid.Enabled",          false);
        SetConfigValue<float>(PEConfig::FIRST_AID_EXPERIENCE,      "ProfessionExperience.FirstAid.Experience",       0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::HERBALISM_ENABLED,          "ProfessionExperience.Herbalism.Enabled",         true);
        SetConfigValue<float>(PEConfig::HERBALISM_EXPERIENCE,      "ProfessionExperience.Herbalism.Experience",      0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::INSCRIPTION_ENABLED,        "ProfessionExperience.Inscription.Enabled",       false);
        SetConfigValue<float>(PEConfig::INSCRIPTION_EXPERIENCE,    "ProfessionExperience.Inscription.Experience",    0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::JEWELCRAFTING_ENABLED,      "ProfessionExperience.Jewelcrafting.Enabled",     false);
        SetConfigValue<float>(PEConfig::JEWELCRAFTING_EXPERIENCE,  "ProfessionExperience.Jewelcrafting.Experience",  0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::LEATHERWORKING_ENABLED,     "ProfessionExperience.Leatherworking.Enabled",    false);
        SetConfigValue<float>(PEConfig::LEATHERWORKING_EXPERIENCE, "ProfessionExperience.Leatherworking.Experience", 0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::LOCKPICK_ENABLED,           "ProfessionExperience.Lockpick.Enabled",          false);
        SetConfigValue<float>(PEConfig::LOCKPICK_EXPERIENCE,       "ProfessionExperience.Lockpick.Experience",       0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::MINING_ENABLED,             "ProfessionExperience.Mining.Enabled",            true);
        SetConfigValue<float>(PEConfig::MINING_EXPERIENCE,         "ProfessionExperience.Mining.Experience",         0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::SKINNING_ENABLED,           "ProfessionExperience.Skinning.Enabled",          false);
        SetConfigValue<float>(PEConfig::SKINNING_EXPERIENCE,       "ProfessionExperience.Skinning.Experience",       0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::SMELTING_ENABLED,           "ProfessionExperience.Smelting.Enabled",          false);
        SetConfigValue<float>(PEConfig::SMELTING_EXPERIENCE,       "ProfessionExperience.Smelting.Experience",       0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<bool>(PEConfig::TAILORING_ENABLED,          "ProfessionExperience.Tailoring.Enabled",         false);
        SetConfigValue<float>(PEConfig::TAILORING_EXPERIENCE,      "ProfessionExperience.Tailoring.Experience",      0.01, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value > 0.0f; }, "> 0");

        SetConfigValue<float>(PEConfig::MULT_GRAY,   "ProfessionExperience.MultGray",   0.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_GREEN,  "ProfessionExperience.MultGreen",  0.75f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_YELLOW, "ProfessionExperience.MultYellow", 1.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_ORANGE, "ProfessionExperience.MultOrange", 1.25f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
    }
};
static PEConfigData peConfigData;

class RewardExperienceScript : public PlayerScript
{
public:
RewardExperienceScript() : PlayerScript("RewardExperienceScript", {
        PLAYERHOOK_ON_UPDATE_CRAFTING_SKILL,
        PLAYERHOOK_ON_UPDATE_GATHERING_SKILL,
        PLAYERHOOK_ON_UPDATE_FISHING_SKILL,
     }) { }

    bool OnPlayerUpdateFishingSkill(Player* player, int32 skill, int32 zone_skill, int32 /*chance*/, int32 /*roll*/) override
    {
        if (peConfigData.GetConfigValue<bool>(PEConfig::FISHING_ENABLED))
            RewardXP(player, skill, zone_skill + 100, zone_skill + 50, zone_skill + 25, peConfigData.GetConfigValue<float>(PEConfig::FISHING_EXPERIENCE));

        return true;
    }

    void OnPlayerUpdateGatheringSkill(Player* player, uint32 skillId, uint32 currentLevel, uint32 gray, uint32 green, uint32 yellow, uint32& /*gain*/) override
    {
        PEConfig enabledSetting;
        PEConfig experienceSetting;
        switch (skillId)
        {
            case SKILL_HERBALISM:
                enabledSetting = PEConfig::HERBALISM_ENABLED;
                experienceSetting = PEConfig::HERBALISM_EXPERIENCE;
                break;
            case SKILL_MINING:
                enabledSetting = PEConfig::MINING_ENABLED;
                experienceSetting = PEConfig::MINING_EXPERIENCE;
                break;
            case SKILL_SKINNING:
                enabledSetting = PEConfig::SKINNING_ENABLED;
                experienceSetting = PEConfig::SKINNING_EXPERIENCE;
                break;
            case SKILL_LOCKPICKING:
                enabledSetting = PEConfig::LOCKPICK_ENABLED;
                experienceSetting = PEConfig::LOCKPICK_EXPERIENCE;
                break;
            default:
                return;
        }

        if (peConfigData.GetConfigValue<bool>(enabledSetting))
            RewardXP(player, currentLevel, gray, green, yellow, peConfigData.GetConfigValue<float>(experienceSetting));
    }

    void OnPlayerUpdateCraftingSkill(Player *player, SkillLineAbilityEntry const* skill, uint32 currentLevel, uint32& /*gain*/) override
    {
        PEConfig enabledSetting;
        PEConfig experienceSetting;
        switch (skill->SkillLine)
        {
            case SKILL_ALCHEMY:
                enabledSetting = PEConfig::ALCHEMY_ENABLED;
                experienceSetting = PEConfig::ALCHEMY_EXPERIENCE;
                break;
            case SKILL_BLACKSMITHING:
                enabledSetting = PEConfig::BLACKSMITH_ENABLED;
                experienceSetting = PEConfig::BLACKSMITH_EXPERIENCE;
                break;
            case SKILL_COOKING:
                enabledSetting = PEConfig::COOKING_ENABLED;
                experienceSetting = PEConfig::COOKING_EXPERIENCE;
                break;
            case SKILL_ENCHANTING:
                if (skill->Spell == 13262)
                {
                    enabledSetting = PEConfig::DISENCHANTING_ENABLED;
                    experienceSetting = PEConfig::DISENCHANTING_EXPERIENCE;
                }
                else
                {
                    enabledSetting = PEConfig::ENCHANTING_ENABLED;
                    experienceSetting = PEConfig::ENCHANTING_EXPERIENCE;
                }
                break;
            case SKILL_ENGINEERING:
                enabledSetting = PEConfig::ENGINEERING_ENABLED;
                experienceSetting = PEConfig::ENGINEERING_EXPERIENCE;
                break;
            case SKILL_FIRST_AID:
                enabledSetting = PEConfig::FIRST_AID_ENABLED;
                experienceSetting = PEConfig::FIRST_AID_EXPERIENCE;
                break;
            case SKILL_INSCRIPTION:
                enabledSetting = PEConfig::INSCRIPTION_ENABLED;
                experienceSetting = PEConfig::INSCRIPTION_EXPERIENCE;
                break;
            case SKILL_JEWELCRAFTING:
                enabledSetting = PEConfig::JEWELCRAFTING_ENABLED;
                experienceSetting = PEConfig::JEWELCRAFTING_EXPERIENCE;
                break;
            case SKILL_LEATHERWORKING:
                enabledSetting = PEConfig::LEATHERWORKING_ENABLED;
                experienceSetting = PEConfig::LEATHERWORKING_EXPERIENCE;
                break;
            case SKILL_MINING:
                enabledSetting = PEConfig::SMELTING_ENABLED;
                experienceSetting = PEConfig::SMELTING_EXPERIENCE;
                break;
            case SKILL_TAILORING:
                enabledSetting = PEConfig::TAILORING_ENABLED;
                experienceSetting = PEConfig::TAILORING_EXPERIENCE;
                break;
            default:
                return;
        }
        if (peConfigData.GetConfigValue<bool>(enabledSetting))
        {
            uint32 gray = skill->TrivialSkillLineRankHigh;
            uint32 green = (skill->TrivialSkillLineRankHigh + skill->TrivialSkillLineRankLow) / 2;
            uint32 yellow = skill->TrivialSkillLineRankLow;
            RewardXP(player, currentLevel, gray, green, yellow, peConfigData.GetConfigValue<float>(experienceSetting));
        }
    }

    void RewardXP(Player* player, uint32 currentLevel, uint32 gray, uint32 green, uint32 yellow, float xpFraction)
    {
        uint32 xp = player->GetUInt32Value(PLAYER_NEXT_LEVEL_XP) * xpFraction;
        if (currentLevel >= gray)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_GRAY);
        else if (currentLevel >= green)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_GREEN);
        else if (currentLevel >= yellow)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_YELLOW);
        else
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_ORANGE);

        player->GiveXP(xp, nullptr);
    }
};

class LoadPEConfigScript : public WorldScript
{
public:
LoadPEConfigScript() : WorldScript("LoadPEConfigScript", {
        WORLDHOOK_ON_BEFORE_CONFIG_LOAD
    }) { }

    void OnBeforeConfigLoad(bool reload) override
    {
        peConfigData.Initialize(reload);
    }
};

// Add all scripts in one
void AddProfessionExpScripts()
{
    new RewardExperienceScript();
    new LoadPEConfigScript();
}
