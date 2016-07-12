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

#define COST_PROFF 100*GOLD // 100g

bool GossipHello_Npc_Profession(Player* player, Creature* m_creature)
{
    if (player->isInCombat())
    {
        player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Combat Check|r|cffffffff]:|r |cffffffffYou're in combat %s ! |r", player->GetName());
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff0000ffYou are in combat!!! |r", GOSSIP_SENDER_MAIN, 9999);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        return false;
    }
    if (player->GetMoney() < COST_PROFF)
    {
        player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Money Check|r|cffffffff]:|r |cffffffff %s You need 100 golds for profession training! |r", player->GetName());
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff0000ffYou need 100 golds for profession training!!! |r", GOSSIP_SENDER_MAIN, 9999);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        return false;
    }
    if (player->HasSkill(SKILL_ALCHEMY)) // 171
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Trade_alchemy:26:26:-15:0|t         Set Alchemy skill to 300 (100g)", GOSSIP_SENDER_MAIN, 100);
    if (player->HasSkill(SKILL_BLACKSMITHING)) // 164
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Trade_blacksmithing:26:26:-15:0|t   Set Blacksmithing skill to 300 (100g)", GOSSIP_SENDER_MAIN, 200);
    if (player->HasSkill(SKILL_ENCHANTING)) // 333
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Trade_engraving:26:26:-15:0|t       Set Enchanting skill to 300 (100g)", GOSSIP_SENDER_MAIN, 300);
    if(player->HasSkill(SKILL_ENGINEERING)) // 202
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Trade_engineering:26:26:-15:0|t     Set Engineering skill to 300 (100g)", GOSSIP_SENDER_MAIN, 400);
    if(player->HasSkill(SKILL_HERBALISM)) // 182
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Trade_herbalism:26:26:-15:0|t       Set Herbalism skill to 300 (100g)", GOSSIP_SENDER_MAIN, 500);
    if(player->HasSkill(SKILL_JEWELCRAFTING)) // 755
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Inv_misc_gem_01:26:26:-15:0|t       Set Jewelcrafting skill to 300 (100g)", GOSSIP_SENDER_MAIN, 600);
    if(player->HasSkill(SKILL_LEATHERWORKING)) //165 
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Trade_leatherworking:26:26:-15:0|t  Set Leatherworking skill to 300 (100g)", GOSSIP_SENDER_MAIN, 700);
    if(player->HasSkill(SKILL_MINING)) // 186
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Trade_mining:26:26:-15:0|t          Set Mining skill to 300 (100g)", GOSSIP_SENDER_MAIN, 800);
    if(player->HasSkill(SKILL_SKINNING)) // 393
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Inv_misc_pelt_wolf_01:26:26:-15:0|t Set Skinnning skill to 300 (100g)", GOSSIP_SENDER_MAIN, 900);
    if(player->HasSkill(SKILL_TAILORING)) // 197
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Trade_tailoring:26:26:-15:0|t       Set Tailoring skill to 300 (100g)", GOSSIP_SENDER_MAIN, 1000);
    // player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Error|r|cffffffff]:|r |cffffffff First you learn any profession! |r");
    // player->ADD_GOSSIP_ITEM(5, "|TInterface\\icons\\Ability_spy:26:26:-15:0|t Close Window.", GOSSIP_SENDER_MAIN, 9999);
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
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Alchemy training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Alchemy already now! |r");
        }
        break;
        // Blacksmithing
    case 200:
        if (player->GetBaseSkillValue(164) >= 1 && player->GetBaseSkillValue(164) < 300)
        {
            player->SetSkill(164, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Blacksmithing training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Blacksmithing already now! |r");
        }
        break;
        // Enchanting
    case 300:
        if (player->GetBaseSkillValue(333) >= 1 && player->GetBaseSkillValue(333) < 300)
        {
            player->SetSkill(333, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Enchanting training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Enchanting already now! |r");
        }
        break;
        // Engineering
    case 400:
        if (player->GetBaseSkillValue(202) >= 1 && player->GetBaseSkillValue(202) < 300)
        {
            player->SetSkill(202, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Engineering training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Engineering already now! |r");
        }
        break;
        // Herbalism
    case 500:
        if (player->GetBaseSkillValue(182) >= 1 && player->GetBaseSkillValue(182) < 300)
        {
            player->SetSkill(182, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Herbalism training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Herbalism already now! |r");
        }
        break;
        // Jewelcrafting
    case 600:
        if (player->GetBaseSkillValue(755) >= 1 && player->GetBaseSkillValue(755) < 300)
        {
            player->SetSkill(755, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Jewelcrafting training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Jewelcrafting already now! |r");
        }
        break;
        // Leatherworking
    case 700:
        if (player->GetBaseSkillValue(165) >= 1 && player->GetBaseSkillValue(165) < 300)
        {
            player->SetSkill(165, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Leatherworking training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Leatherworking already now! |r");
        }
        break;
        // Mining
    case 800:
        if (player->GetBaseSkillValue(186) >= 1 && player->GetBaseSkillValue(186) < 300)
        {
            player->SetSkill(186, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Mining training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Mining already now! |r");
        }
        break;
        // Skinning
    case 900:
        if (player->GetBaseSkillValue(393) >= 1 && player->GetBaseSkillValue(393) < 300)
        {
            player->SetSkill(393, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Skinning training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Skinning already now! |r");
        }
        break;
        // Tailoring
    case 1000:
        if (player->GetBaseSkillValue(197) >= 1 && player->GetBaseSkillValue(197) < 300)
        {
            player->SetSkill(197, 300, 375, 0);
            player->ModifyMoney(-1 * COST_PROFF);
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Tailoring training 300/375! |r");
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Profession|r|cffffffff]:|r |cffffffff Tailoring already now! |r");
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
