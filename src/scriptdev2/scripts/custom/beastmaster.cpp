/*
<--------------------------------------------------------------------------->
- Developer: Funnygirl, Mireno, Trix'
- Complete: 100%
- ScriptName: 'Beastmaster_Trainer'
- Developed: 06/03/2016
- Update: 06/04/2016
<--------------------------------------------------------------------------->
*/
#include "precompiled.h"
#include "Pet.h"
#include <cstring>
#include "Player.h"
#include "Creature.h"
#include "Unit.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "Map.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "MapManager.h"
#include "Common.h"
#include "Language.h"
#include "ObjectGuid.h"
#include "World.h"
#include "AI/CreatureAI.h"
#include "Util.h"

#define MAINMENU "|TInterface/ICONS/Ability_Spy:30:30:-18:0|t <= Main Menu"
#define MORE "|TInterface/ICONS/Spell_chargepositive:30:30:-18:0|t More =>"
#define LESS "|TInterface/ICONS/Spell_chargenegative:30:30:-18:0|t <= Back"

void CreatePet(Player* player, Creature* creature, uint32 entry)
{
    if (player->getClass() != CLASS_HUNTER)
    {
        creature->MonsterWhisper("I can only train Hunters in the way of the beast.", player, false);
        player->GetSession()->SendNotification("%s , you are not a Hunter!", player->GetName());
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    if (player->GetPet()) {
        creature->MonsterWhisper("First you must drop your pet!", player, false);
        player->PlayerTalkClass->CloseGossip();
        return;
    }

    Map *map = player->GetMap();
    Creature* creatureTarget = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 500); // TEMPSUMMON_CORPSE_TIMED_DESPAWN, 0
    if (!creatureTarget) return;

    uint32 spell_id = 13481;
    SpellEntry const* spellInfo = sSpellStore.LookupEntry(spell_id);

    Pet* pet = new Pet(HUNTER_PET);
    if (!pet->CreateBaseAtCreature(creatureTarget))
    {
        delete pet;
        return;
    }

    creatureTarget->SetDeathState(JUST_DIED);
    creatureTarget->RemoveCorpse();
    creatureTarget->SetHealth(0);
    pet->SetPower(POWER_HAPPINESS, 10480000);    
    pet->SetByteValue(UNIT_FIELD_BYTES_1, 1, 6);// loyalty
    pet->SetTP(350);    // pet->SetTP(pet->getLevel() * (pet->GetLoyaltyLevel() - 1));    
    pet->GetCharmInfo()->SetReactState(ReactStates(1));// react state

    pet->SetOwnerGuid(player->GetObjectGuid());
    pet->SetCreatorGuid(player->GetObjectGuid());
    pet->setFaction(player->getFaction());
    pet->SetUInt32Value(UNIT_CREATED_BY_SPELL, spell_id);

    pet->SetUInt32Value(UNIT_FIELD_LEVEL, 69);
    pet->GetMap()->Add((Creature*)pet);
    pet->SetUInt32Value(UNIT_FIELD_LEVEL, 70);
    pet->InitStatsForLevel(70);
    pet->UpdateAllStats();
    player->SetPet(pet);
    pet->SavePetToDB(PET_SAVE_AS_CURRENT);
    player->PetSpellInitialize();
    if (player->IsPvP())
        pet->SetPvP(true);
    player->CLOSE_GOSSIP_MENU();
    creature->MonsterWhisper("You have learned a way of the beast, congratulations.", player, false);
}

bool GossipHello_Npc_Beastmaster(Player* player, Creature* m_creature)
{
    player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Ability_hunter_beasttaming:26:26:-15:0|t Obtain a New Pet.", GOSSIP_SENDER_MAIN, 10);
    player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Ability_hunter_beasttaming:26:26:-15:0|t New Pet levelup.", GOSSIP_SENDER_MAIN, 5000);
    player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Ability_hunter_beastcall:26:26:-15:0|t Take me to the Stable.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
    player->ADD_GOSSIP_ITEM(6, "|TInterface\\icons\\Inv_misc_food_58:26:26:-15:0|t Sell me some Food for my Pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
    player->ADD_GOSSIP_ITEM(5, "|TInterface\\icons\\Ability_spy:26:26:-15:0|t Close Beastmaster Window.", GOSSIP_SENDER_MAIN, 150);
    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
    return true;
}

bool GossipSelect_Npc_Beastmaster(Player* player, Creature* m_creature, uint32 /*sender*/, uint32 action)
{
    player->PlayerTalkClass->ClearMenus();

    switch (action)
    {

    case 100:
        player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Ability_hunter_beasttaming:26:26:-15:0|t Obtain a New Pet.", GOSSIP_SENDER_MAIN, 10);
        player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Ability_hunter_beasttaming:26:26:-15:0|t New Pet levelup.", GOSSIP_SENDER_MAIN, 5000);
        player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Ability_hunter_beastcall:26:26:-15:0|t Take me to the Stable.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
        player->ADD_GOSSIP_ITEM(6, "|TInterface\\icons\\Inv_misc_food_58:26:26:-15:0|t Sell me some Food for my Pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
        player->ADD_GOSSIP_ITEM(5, "|TInterface\\icons\\Ability_spy:26:26:-15:0|t Close Beastmaster Window.", GOSSIP_SENDER_MAIN, 150);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        break;

        // Close
    case 150:
        player->CLOSE_GOSSIP_MENU();
        break;
        // Stable master
    case GOSSIP_OPTION_STABLEPET:
        player->GetSession()->SendStablePet(m_creature->GetObjectGuid());
        break;
        // Food vendor
    case GOSSIP_OPTION_VENDOR:
        player->GetSession()->SendListInventory(m_creature->GetObjectGuid());
        break;
        // pet 70 lvl
    case 5000:
        if (player->getClass() != CLASS_HUNTER)
        {
            m_creature->MonsterWhisper("You are not a Hunter!", player, false);
            player->GetSession()->SendNotification("%s , you are not a Hunter!", player->GetName());
            player->CLOSE_GOSSIP_MENU();
            return false;
        }

        if (!player->GetPet())
        {
            m_creature->MonsterWhisper("You do not have pet!", player, false);
            player->CLOSE_GOSSIP_MENU();
            return false;
        }

        // Pet* newpet = player->GetPet();
        if (player->GetPet()->getLevel() <= 69)
        {
            player->GetPet()->SetLevel(70);
            // happiness
            player->GetPet()->SetPower(POWER_HAPPINESS, 10480000);
            // loyalty
            player->GetPet()->SetByteValue(UNIT_FIELD_BYTES_1, 1, 6);
            // Initialize spell, stat
            // newpet->InitStatsForLevel(70);
            // SET Training Points
            player->GetPet()->SetTP(0);
            m_creature->MonsterWhisper("Your pet got level 70.", player, false);
        }
        else
            m_creature->MonsterWhisper("Your pet already has 70 levels.", player, false);

        player->CLOSE_GOSSIP_MENU();
        break;

        // rozdelenie petov
    case 10:
        if (player->GetPet())
        {
            m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
            player->CLOSE_GOSSIP_MENU();
            return false;
        }
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_AnimalHandler:26:26:-15:0|t|r Cunning (PvP)", GOSSIP_SENDER_MAIN, 1000);	// PVP	Ability_hunter_dragonhawk
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_druid_primaltenacity:26:26:-15:0|t|r Ferocity (Dmg)", GOSSIP_SENDER_MAIN, 2000);  // Dmg
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Spell_nature_shamanrage.:26:26:-15:0|t|r Tenacity (Tank)", GOSSIP_SENDER_MAIN, 3000); // Tank
        player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        break;

        // Cunning pets
    case 1000:
        if (player->GetPet())
        {
            m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
            player->CLOSE_GOSSIP_MENU();
            return false;
        }
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_bat:26:26:-15:0|t|r Bat (Cower-6, Screech-4)", GOSSIP_SENDER_MAIN, 1001);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_vulture:26:26:-15:0|t|r Bird", GOSSIP_SENDER_MAIN, 1002);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_ravager:26:26:-15:0|t|r Ravager.", GOSSIP_SENDER_MAIN, 1003);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_windserpent:26:26:-15:0|t|r Serpent.", GOSSIP_SENDER_MAIN, 1004);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_scorpid:26:26:-15:0|t|r Scorpid.", GOSSIP_SENDER_MAIN, 1005);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_spider:26:26:-15:0|t|r Spider.", GOSSIP_SENDER_MAIN, 1006);
        player->ADD_GOSSIP_ITEM(2, LESS, GOSSIP_SENDER_MAIN, 10);
        player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        break;

        // Ferocity pets
    case 2000:
        if (player->GetPet())
        {
            m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
            player->CLOSE_GOSSIP_MENU();
            return false;
        }
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_cat:26:26:-15:0|t|r Bangalash.", GOSSIP_SENDER_MAIN, 2001);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_wolf:26:26:-15:0|t|r Cat.", GOSSIP_SENDER_MAIN, 2002);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_boar:26:26:-15:0|t|r Boar.", GOSSIP_SENDER_MAIN, 2003);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_crab:26:26:-15:0|t|r Crab.", GOSSIP_SENDER_MAIN, 2004);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_crocolisk:26:26:-15:0|t|r Crocolisk.", GOSSIP_SENDER_MAIN, 2005);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_dragonhawk:26:26:-15:0|t|r Dragonhawk.", GOSSIP_SENDER_MAIN, 2006);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_owl:26:26:-15:0|t|r Owl (Claw-9, Dive-3)", GOSSIP_SENDER_MAIN, 2007);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_raptor:26:26:-15:0|t|r Raptor.", GOSSIP_SENDER_MAIN, 2008);
        player->ADD_GOSSIP_ITEM(2, MORE, GOSSIP_SENDER_MAIN, 2100);
        player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        break;

        // NEXT FEROCITY
    case 2100:
        if (player->GetPet())
        {
            m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
            player->CLOSE_GOSSIP_MENU();
            return false;
        }
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_tallstrider:26:26:-15:0|t|r Strider.", GOSSIP_SENDER_MAIN, 2009);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_hyena:26:26:-15:0|t|r Hyena.", GOSSIP_SENDER_MAIN, 2010);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_cat:26:26:-15:0|t|r Mountain Lion - Prowl.", GOSSIP_SENDER_MAIN, 2011);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_wolf:26:26:-15:0|t|r Wolf.", GOSSIP_SENDER_MAIN, 2012);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_cat:26:26:-15:0|t|r Amani Elder Lynx.", GOSSIP_SENDER_MAIN, 2013); 
        player->ADD_GOSSIP_ITEM(2, LESS, GOSSIP_SENDER_MAIN, 2000);
        player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        break;

        // Tenacity pets
    case 3000:
        if (player->GetPet())
        {
            m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
            player->CLOSE_GOSSIP_MENU();
            return false;
        }
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_turtle:26:26:-15:0|t|r Turtle.", GOSSIP_SENDER_MAIN, 3001);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_bear:26:26:-15:0|t|r Bear.", GOSSIP_SENDER_MAIN, 3002);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_gorilla:26:26:-15:0|t|r Gorilla.", GOSSIP_SENDER_MAIN, 3003); // Ability_hunter_pet_gorill		
        player->ADD_GOSSIP_ITEM(2, LESS, GOSSIP_SENDER_MAIN, 10);
        player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        break;
        // ======================================================================================================================================================================

    case 1001: // Bat
        CreatePet(player, m_creature, 8602);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1002: // Bird, Rock
        CreatePet(player, m_creature, 5430); // 23051
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1003: // Ravager
        CreatePet(player, m_creature, 22123); // 19349
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1004: // Serpent
        CreatePet(player, m_creature, 5349);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1005: // Scorpid
        CreatePet(player, m_creature, 4696);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1006: // Spider
        CreatePet(player, m_creature, 18467);
        player->CLOSE_GOSSIP_MENU();
        break;
        // ============================================            
    case 2001: // Bangalash
        CreatePet(player, m_creature, 731);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2002: // Tiger - cat
        CreatePet(player, m_creature, 21723); // 772
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2003: // Boar
        CreatePet(player, m_creature, 157); // 1984
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2004: // Crab 
        CreatePet(player, m_creature, 3106); // 
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2005: // Crokolisk
        CreatePet(player, m_creature, 4344); // 
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2006: // Dragonhawk
        CreatePet(player, m_creature, 20749); // 
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2007: // Owl 
        CreatePet(player, m_creature, 22265); // 
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2008: // Raptor
        CreatePet(player, m_creature, 22052); // 
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2009: // Talonstrider 
        CreatePet(player, m_creature, 2955); // 
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2010: // Hyena
        CreatePet(player, m_creature, 5426); // 3425
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2011: // Mountain Lion Prowl 
        CreatePet(player, m_creature, 2406); // 
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2012: // Wolf
        CreatePet(player, m_creature, 20330); // 1131
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2013: // Amani Elder Lynx
        CreatePet(player, m_creature, 24530); // 
        player->CLOSE_GOSSIP_MENU();
        break;
        // ============================================
    case 3001: // Turtle
        CreatePet(player, m_creature, 14123);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 3002: // Bear
        CreatePet(player, m_creature, 7443);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 3003: // Gorila
        CreatePet(player, m_creature, 1114);
        player->CLOSE_GOSSIP_MENU();
        break;
    }
    return true;
}

void AddSC_Npc_Beastmaster()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_beastmaster";
    newscript->pGossipHello = &GossipHello_Npc_Beastmaster;
    newscript->pGossipSelect = &GossipSelect_Npc_Beastmaster;
    newscript->RegisterSelf();
}
