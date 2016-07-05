/* ScriptData
SDName:
SD%Complete: 100
SDComment:
SDCategory: Custom
Authors:
Year: 2010
EndScriptData */

#include "precompiled.h"

#define SINGLE_COST 10000  // 1 golds
#define CLASS_COST 50000  // 5 golds

#define TEXT_NEXT		"|cffff0000==[Next Page]==>> |r"		// red 
#define TEXT_BACK		"<<==[ Back ]=="						// black
#define TEXT_BACK_BLUE	"|cff0000ff<<==[ Back ]== |r"			// blue
#define TEXT_MAIN_MENU	"|cff0000ff<==[[ Main Menu ]]==> |r"	// blue 
#define TEXT_BYE		"|cff00ff00Bye, bye.... |r"				// green

#define MAINMENU "|TInterface/ICONS/Ability_Spy:30:30:-18:0|t|cff0000ff<==[[ Main Menu ]]==>|r"
#define MORE "|TInterface/ICONS/Spell_chargepositive:30:30:-18:0|t|cffff0000==[Next Page]==>>|r"
#define LESS "|TInterface/ICONS/Spell_chargenegative:30:30:-18:0|t|cff0000ff<<==[ Back ]== |r"


enum spells
{
    THORNS = 26992,
    ARCANE_INTELECT = 27126,
    BLESSING_OF_KINGS = 20217,
    BLESSING_OF_MIGHT = 27140, // 10 min
    BLESSING_OF_SALVATION = 1038, // 10 min
    BLESSING_OF_WISDOM = 27142, // 10 min
    SHADOW_PROTECTION = 25433, // 10 min
    WATER_WALKING = 11319, // 10 min
    DIVINE_SPIRIT = 25312,
    MARK_OF_THE_WILD = 26990,
    POWER_WORD_FORTITUDE = 25389,
    SPIRIT = 33080,
    STAMINA = 33081,
    STRENGHT = 33082,
    INTELLECT = 33078,
    AGILITY = 33077,
    SONGFLOWER_SERENADE = 15366, // 1 hour
};

bool GossipHello_MCBuffer(Player *player, Creature *_Creature)
{
    ////////////////// MAIN MENU ///////////////////////////
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, " |cffff0000 Choose from menu: |r", GOSSIP_SENDER_MAIN, 9999);
    // kontrola kombatu
    if (player->isInCombat())
    {
        player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Combat Check|r|cffffffff]:|r |cffffffffYou're in combat %s ! |r", player->GetName());
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|cff0000ffYou are in combat!!! |r", GOSSIP_SENDER_MAIN, 9999);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TEXT_BYE, GOSSIP_SENDER_MAIN, 9998);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
        //player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
        //player->PlayerTalkClass->SendCloseGossip();
        return true;
    }
    else {
        if (player->getLevel() >= 70)
        {

            // kontrola goldov
            if (player->GetMoney() >= SINGLE_COST)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, " |TInterface/ICONS/Spell_holy_spellwarding:30:30:-18:0|t  --[[ BUFFS ]]--", GOSSIP_SENDER_MAIN, 100);
            }
            else {
                player->GetSession()->SendAreaTriggerMessage("%s , You haven't enough money to buy Buffs!", player->GetName());
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cff0000ff>>> You haven't enough money! <<< |r", GOSSIP_SENDER_MAIN, 9999);
            }
            if (player->GetMoney() >= CLASS_COST)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, " |TInterface/ICONS/Spell_holy_prayerofhealing:30:30:-18:0|t  --[Buffs for Specialization]--", GOSSIP_SENDER_MAIN, 2000);
            }
            else {
                player->GetSession()->SendAreaTriggerMessage("%s ,You haven't enough money to buy Buffs for Specialization!", player->GetName());
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cff0000ff>>> You haven't enough money! <<< |r", GOSSIP_SENDER_MAIN, 9999);
            }
        }
        else {
            //player->GetSession()->SendAreaTriggerMessage("Enough level!");
            player->GetSession()->SendNotification("|cffffffffYou must be at least level 70+ %s ! |r", player->GetName());
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cff12300ff>>> You must be at least level 70+! <<<", GOSSIP_SENDER_MAIN, 9999);
        }
    }
    if (player->isGameMaster())
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cff00ff05-[ Heal me ]- visible only GM (.gm on) |r", GOSSIP_SENDER_MAIN, 8000);
    }
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TEXT_BYE, GOSSIP_SENDER_MAIN, 9998);
    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
    return true;
}

void SendDefaultMenu_MCBuffer(Player *player, Creature *_Creature, uint32 action)
{
    player->PlayerTalkClass->ClearMenus();
    // switch(player->getClass())
    switch (action)
    {
        ////////////////// BUFFS SUBMENU ///////////////////////////
    case 1000: // Buffs
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, " |cff0000ff Buff cost: 1 gold |r", GOSSIP_SENDER_MAIN, 9999);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_wordfortitude:30:30:-18:0|t POWER WORD: FORTITUDE", GOSSIP_SENDER_MAIN, 1010);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_divinespirit:30:30:-18:0|t DIVINE SPIRIT", GOSSIP_SENDER_MAIN, 1020);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_shadow_antishadow:30:30:-18:0|t SHADOW PROTECTION", GOSSIP_SENDER_MAIN, 1030);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_fistofjustice:30:30:-18:0|t BLESSING OF MIGHT", GOSSIP_SENDER_MAIN, 1070);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_magic_magearmor:30:30:-18:0|t BLESSING OF KINGS", GOSSIP_SENDER_MAIN, 1080);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_sealofwisdom:30:30:-18:0|t BLESSING OF WISDOM", GOSSIP_SENDER_MAIN, 1090);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_greaterblessingofsalvation:30:30:-18:0|t BLESSING OF SALVATION", GOSSIP_SENDER_MAIN, 1100);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, MORE, GOSSIP_SENDER_MAIN, 1200);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, LESS, GOSSIP_SENDER_MAIN, 9999);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
        break;
    case 1200: // Buffs Next Page 1
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, " |cff0000ff Buff cost: 1 gold |r", GOSSIP_SENDER_MAIN, 9999);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_nature_regeneration:30:30:-18:0|t MARK OF THE WILD", GOSSIP_SENDER_MAIN, 1040);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_nature_thorns:30:30:-18:0|t THORNS", GOSSIP_SENDER_MAIN, 1050);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_magicalsentry:30:30:-18:0|t ARCANE INTELECT", GOSSIP_SENDER_MAIN, 1060);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_mindvision:30:30:-18:0|t SONGFLOWER SERENADE", GOSSIP_SENDER_MAIN, 1270);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, MAINMENU, GOSSIP_SENDER_MAIN, 9999);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, LESS, GOSSIP_SENDER_MAIN, 1000);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TEXT_BYE, GOSSIP_SENDER_MAIN, 9998);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
        break;

        ////////////////// BUFFS for Specialization SUBMENU ///////////////////////////
    case 2000: // Buff for Specialization
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, " |cff0000ff Buffs cost: 5 golds |r", GOSSIP_SENDER_MAIN, 9999);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/Ability_warrior_defensivestance:30:30:-18:0|t TANK", GOSSIP_SENDER_MAIN, 2001);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/Spell_holy_circleofrenewal:30:30:-18:0|t HEAL", GOSSIP_SENDER_MAIN, 2002);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/Spell_fire_flamebolt:30:30:-18:0|t SPELL DMG", GOSSIP_SENDER_MAIN, 2003);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/Spell_holy_fistofjustice:30:30:-18:0|t MELLE DMG", GOSSIP_SENDER_MAIN, 2004);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/Inv_ammo_arrow_02:30:30:-18:0|t RANGED DMG", GOSSIP_SENDER_MAIN, 2005);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, LESS, GOSSIP_SENDER_MAIN, 9999);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TEXT_BYE, GOSSIP_SENDER_MAIN, 9998);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
        break;

    case 2001: // TANK
        _Creature->CastSpell(player, POWER_WORD_FORTITUDE, false);
        _Creature->CastSpell(player, ARCANE_INTELECT, false);
        _Creature->CastSpell(player, THORNS, false);
        _Creature->CastSpell(player, MARK_OF_THE_WILD, false);
        _Creature->CastSpell(player, BLESSING_OF_KINGS, false);
        player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
        player->PlayDirectSound(3337); 
        player->ModifyMoney(-CLASS_COST);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2002: // HEAL
        _Creature->CastSpell(player, MARK_OF_THE_WILD, false);
        _Creature->CastSpell(player, POWER_WORD_FORTITUDE, false);
        _Creature->CastSpell(player, ARCANE_INTELECT, false);
        _Creature->CastSpell(player, BLESSING_OF_SALVATION, false);
        _Creature->CastSpell(player, DIVINE_SPIRIT, false);
        player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
        player->PlayDirectSound(3337);
        player->ModifyMoney(-CLASS_COST);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2003: // SPELL DMG
        _Creature->CastSpell(player, MARK_OF_THE_WILD, false);
        _Creature->CastSpell(player, POWER_WORD_FORTITUDE, false);
        _Creature->CastSpell(player, ARCANE_INTELECT, false);
        _Creature->CastSpell(player, BLESSING_OF_SALVATION, false);
        _Creature->CastSpell(player, DIVINE_SPIRIT, false);
        player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
        player->PlayDirectSound(3337);
        player->ModifyMoney(-CLASS_COST);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2004: // MELE DMG
        _Creature->CastSpell(player, POWER_WORD_FORTITUDE, false);
        _Creature->CastSpell(player, ARCANE_INTELECT, false);
        _Creature->CastSpell(player, BLESSING_OF_MIGHT, false);
        _Creature->CastSpell(player, MARK_OF_THE_WILD, false);
        _Creature->CastSpell(player, DIVINE_SPIRIT, false);
        player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
        player->PlayDirectSound(3337);
        player->ModifyMoney(-CLASS_COST);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2005: // RANGED DMG
        _Creature->CastSpell(player, MARK_OF_THE_WILD, false);
        _Creature->CastSpell(player, POWER_WORD_FORTITUDE, false);
        _Creature->CastSpell(player, BLESSING_OF_SALVATION, false);
        _Creature->CastSpell(player, ARCANE_INTELECT, false);
        _Creature->CastSpell(player, DIVINE_SPIRIT, false);
        player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
        player->PlayDirectSound(3337);
        player->ModifyMoney(-CLASS_COST);
        player->CLOSE_GOSSIP_MENU();
        break;

        /////////////////////////////////////////// BUFFS ///////////////////////////////////////////////

    case 1010: // POWER_WORD_FORTITUDE		
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, POWER_WORD_FORTITUDE, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed %s !", player->GetName());
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
    case 1020: // DIVINE_SPIRIT		
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, DIVINE_SPIRIT, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
    case 1030: // SHADOW_PROTECTION		
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, SHADOW_PROTECTION, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
    case 1040: // MARK_OF_THE_WILD 		
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, MARK_OF_THE_WILD, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
    case 1050: // THORNS		
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, THORNS, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
    case 1060: // ARCANE_INTELECT		
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, ARCANE_INTELECT, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
    case 1070: // BLESSING_OF_MIGHT	
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, BLESSING_OF_MIGHT, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
    case 1080: // BLESSING_OF_KINGS		
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, BLESSING_OF_KINGS, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
    case 1090: // BLESSING_OF_WISDOM	
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, BLESSING_OF_WISDOM, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
    case 1100: // BLESSING_OF_SALVATION		
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, BLESSING_OF_SALVATION, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;

    case 1270: // SONGFLOWER SERENADE	
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, SONGFLOWER_SERENADE, false);
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
        player->PlayDirectSound(3337); //
        player->ModifyMoney(-SINGLE_COST);
        break;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    case 8000: // Heal me			
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player, 38588, false);  //  38588 Flash Heal efect, 31782 Rejuvenation
        if (player->GetPowerType() == POWER_MANA){
            player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
            player->SetHealth(player->GetMaxHealth());
            player->GetSession()->SendNotification("You are now healed and Mana regen %s !", player->GetName());
            player->GetSession()->SendAreaTriggerMessage("You are now Healed and Mana regen %s !", player->GetName());
        }
        else {
            player->SetHealth(player->GetMaxHealth());
            player->GetSession()->SendNotification("You are now healed %s !", player->GetName());
            player->GetSession()->SendAreaTriggerMessage("You are now healed %s !", player->GetName());
        }

        //player->GetSession()->SendAreaTriggerMessage("You are now healed!");
        player->PlayDirectSound(2676); //
        _Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
        player->ModifyMoney(-SINGLE_COST);
        break;

    case 9998: // Bye
        player->CLOSE_GOSSIP_MENU();
        break;

    case 9999: //<- Back
        GossipHello_MCBuffer(player, _Creature);
        break;

        player->CLOSE_GOSSIP_MENU();
    }
}

bool GossipSelect_MCBuffer(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    // Main menu
    if (sender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_MCBuffer(player, _Creature, action);
    return true;
}

void AddSC_MCBuffer()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_buffer";
    newscript->pGossipHello = &GossipHello_MCBuffer;
    newscript->pGossipSelect = &GossipSelect_MCBuffer;
    newscript->RegisterSelf();
}
