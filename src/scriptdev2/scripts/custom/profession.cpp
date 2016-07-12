/*
Profesion trainer
2016 by Mireno
*/
#include "precompiled.h"
#include "Chat.h"
#include "Language.h"
#include "Spell.h"
#include "WorldSession.h"
#include "World.h"
#include "Player.h"

#define COST_PROFF 300*GOLD // 300g

#define MENU_ALCHEMY        "|TInterface\\icons\\Trade_alchemy:26:26:-15:0|t Set Alchemy skill to 300"
#define MENU_BLACKSMITHING  "|TInterface\\icons\\Trade_blacksmithing:26:26:-15:0|t Set Blacksmithing skill to 300"
#define MENU_ENCHANTING     "|TInterface\\icons\\Trade_engraving:26:26:-15:0|t Set Enchanting skill to 300"
#define MENU_ENGINEERING    "|TInterface\\icons\\Trade_engineering:26:26:-15:0|t Set Engineering skill to 300"
#define MENU_HERBALISM      "|TInterface\\icons\\Trade_herbalism:26:26:-15:0|t Set Herbalism skill to 300"
#define MENU_JEWELCRAFTING  "|TInterface\\icons\\Inv_misc_gem_01:26:26:-15:0|t Set Jewelcrafting skill to 300"
#define MENU_LEATHERWORKING "|TInterface\\icons\\Trade_leatherworking:26:26:-15:0|t Set Leatherworking skill to 300"
#define MENU_MINING         "|TInterface\\icons\\Trade_mining:26:26:-15:0|t Set Mining skill to 300"
#define MENU_SKINNING       "|TInterface\\icons\\Inv_misc_pelt_wolf_01:26:26:-15:0|t Set Skinnning skill to 300"
#define MENU_TAILORING      "|TInterface\\icons\\Trade_tailoring:26:26:-15:0|t Set Tailoring skill to 300"
#define MENU_CLOSE          "|TInterface\\icons\\Ability_spy:26:26:-15:0|t Close Window."

bool GossipHello_Npc_Profession(Player* player, Creature* m_creature)
{
    if (player->isInCombat())
    {
        player->GetSession()->SendNotification("|cff0000ff Check You're in combat %s ! |r", player->GetName());
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff0000ff You are in combat!!! |r", GOSSIP_SENDER_MAIN, 9999);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        return false;
    }
    if (player->GetMoney() < COST_PROFF)
    {
        player->GetSession()->SendNotification("|cff0000ff %s You need 300 gold to learn this skill!|r", player->GetName());
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff0000ff You need 300 gold to learn this skill!|r", GOSSIP_SENDER_MAIN, 9999);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        return false;
    }
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "You must pay 300 gold for every profession.", GOSSIP_SENDER_MAIN, 9999);
    if (player->HasSkill(SKILL_ALCHEMY)) // 171
        player->ADD_GOSSIP_ITEM(2, MENU_ALCHEMY, GOSSIP_SENDER_MAIN, 100);
    if (player->HasSkill(SKILL_BLACKSMITHING)) // 164
        player->ADD_GOSSIP_ITEM(2, MENU_BLACKSMITHING, GOSSIP_SENDER_MAIN, 200);
    if (player->HasSkill(SKILL_ENCHANTING)) // 333
        player->ADD_GOSSIP_ITEM(2, MENU_ENCHANTING, GOSSIP_SENDER_MAIN, 300);
    if (player->HasSkill(SKILL_ENGINEERING)) // 202
        player->ADD_GOSSIP_ITEM(2, MENU_ENGINEERING, GOSSIP_SENDER_MAIN, 400);
    if (player->HasSkill(SKILL_HERBALISM)) // 182
        player->ADD_GOSSIP_ITEM(2, MENU_HERBALISM, GOSSIP_SENDER_MAIN, 500);
    if (player->HasSkill(SKILL_JEWELCRAFTING)) // 755
        player->ADD_GOSSIP_ITEM(2, MENU_JEWELCRAFTING, GOSSIP_SENDER_MAIN, 600);
    if (player->HasSkill(SKILL_LEATHERWORKING)) //165 
        player->ADD_GOSSIP_ITEM(2, MENU_LEATHERWORKING, GOSSIP_SENDER_MAIN, 700);
    if (player->HasSkill(SKILL_MINING)) // 186
        player->ADD_GOSSIP_ITEM(2, MENU_MINING, GOSSIP_SENDER_MAIN, 800);
    if (player->HasSkill(SKILL_SKINNING)) // 393
        player->ADD_GOSSIP_ITEM(2, MENU_SKINNING, GOSSIP_SENDER_MAIN, 900);
    if (player->HasSkill(SKILL_TAILORING)) // 197
        player->ADD_GOSSIP_ITEM(2, MENU_TAILORING, GOSSIP_SENDER_MAIN, 1000);

    player->ADD_GOSSIP_ITEM(5, MENU_CLOSE, GOSSIP_SENDER_MAIN, 9999);
    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
    return true;
}

bool GossipSelect_Npc_Profession(Player* player, Creature* m_creature, uint32 /*sender*/, uint32 action)
{
    player->PlayerTalkClass->ClearMenus();

    switch (action)
    {
        // Alchemy
    case 100:
        if (player->GetBaseSkillValue(171) >= 1 && player->GetBaseSkillValue(171) < 300)
        {
            player->SetSkill(171, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Blacksmithing
    case 200:
        if (player->GetBaseSkillValue(164) >= 1 && player->GetBaseSkillValue(164) < 300)
        {
            player->SetSkill(164, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Enchanting
    case 300:
        if (player->GetBaseSkillValue(333) >= 1 && player->GetBaseSkillValue(333) < 300)
        {
            player->SetSkill(333, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Engineering
    case 400:
        if (player->GetBaseSkillValue(202) >= 1 && player->GetBaseSkillValue(202) < 300)
        {
            player->SetSkill(202, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Herbalism
    case 500:
        if (player->GetBaseSkillValue(182) >= 1 && player->GetBaseSkillValue(182) < 300)
        {
            player->SetSkill(182, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Jewelcrafting
    case 600:
        if (player->GetBaseSkillValue(755) >= 1 && player->GetBaseSkillValue(755) < 300)
        {
            player->SetSkill(755, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Leatherworking
    case 700:
        if (player->GetBaseSkillValue(165) >= 1 && player->GetBaseSkillValue(165) < 300)
        {
            player->SetSkill(165, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Mining
    case 800:
        if (player->GetBaseSkillValue(186) >= 1 && player->GetBaseSkillValue(186) < 300)
        {
            player->SetSkill(186, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Skinning
    case 900:
        if (player->GetBaseSkillValue(393) >= 1 && player->GetBaseSkillValue(393) < 300)
        {
            player->SetSkill(393, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Tailoring
    case 1000:
        if (player->GetBaseSkillValue(197) >= 1 && player->GetBaseSkillValue(197) < 300)
        {
            player->SetSkill(197, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 The profession was set to skill 300!|r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cFFFF4500 You already have skill for this profession!|r");
        }
        break;
        // Close
    case 9999:
        player->CLOSE_GOSSIP_MENU();
        break;
    }
}

void AddSC_Npc_Profession()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_profession";
    newscript->pGossipHello = &GossipHello_Npc_Profession;
    newscript->pGossipSelect = &GossipSelect_Npc_Profession;
    newscript->RegisterSelf();
}
