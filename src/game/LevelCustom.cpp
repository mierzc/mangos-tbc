#include "Chat.h"
#include "Language.h"
#include "World.h"
#include "SpellMgr.h"
#include "Player.h"
#include "BattleGround/BattleGround.h"
#include "BattleGround/BattleGroundMgr.h"
#include "ObjectMgr.h"
#include "ObjectGuid.h"
#include "SpellAuras.h"
#include "Spell.h"
#include "WorldSession.h"
#include "DBCStores.h"
#include "SpellAuras.h"

bool ChatHandler::HandleMCCommand(char* /*args*/)
{
    Player *chr = m_session->GetPlayer();

    // Osetrenie aby sa neportovali za letu
    if (chr->IsFlying())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    //Zakaz portovania
    if (chr->isInCombat()          // Pocas combatu
        || chr->InBattleGround()   // V BattleGrounde (aj arene)
        || chr->HasStealthAura()   // Pocas stealth-u
        || chr->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH)) // S Feign Death (hunter)
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    // Suradnice Mysteria centra
    chr->TeleportTo(1, -10710.190f, 2482.4848f, 9.1479f, 3.5000f);

    // sicko tak jak ma byc
    return true;
}

bool ChatHandler::HandleFlyMountCommand(char* /*args*/)
{
    Player *chr = m_session->GetPlayer();

    // Osetrenie aby sa nemountovali za letu
    if (chr->IsFlying())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    // Musíš mať riding 300
    if (!chr->HasSpell(34091))
    {
        SendSysMessage("Required riding 300!");
        SetSentErrorMessage(true);
        return false;
    }

    // zakaz
    if (chr->isInCombat()				// Pocas combatu
        || chr->GetMap()->Instanceable()  // V instancii
        || !chr->CanFreeMove())         // ak sa nemoze volne pohybovat (sap, taxi ...)
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    // smrt
    if (chr->isDead())
    {
        SendSysMessage("You are dead!");
        SetSentErrorMessage(true);
        return false;
    }

    // zakaz pre low lvl
    if (chr->getLevel() != 70)
    {
        SendSysMessage("Required 70 level!");
        SetSentErrorMessage(true);
        return false;
    }

    switch (chr->GetAreaId())
    {
    case 1637: // orgrimmar
    case 1519: // stormwind
        //case 3487: // silvermoon
        //case 168:  // Tirisfal glades sea
        //case 1256: // Azshara sea
        //case 4080: // ioqd
        SendSysMessage("Not allowed here!");
        SetSentErrorMessage(true);
        return false;
    }

    /*
        // cely ioqd a Diremaul
        if(chr->GetZoneId() == 4080 || chr->GetZoneId() == 2557)
        {
        SendSysMessage("Not allowed here!");
        SetSentErrorMessage(true);
        return false;
        }
        */

    // ine mapy ako azeroth
    if (chr->GetMapId() != 0 && chr->GetMapId() != 1 && chr->GetMapId() != 530)
    {
        SendSysMessage("Not allowed here!");
        SetSentErrorMessage(true);
        return false;
    }

    // dismount
    chr->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);

    Item * firstpositem = chr->GetItemByPos(INVENTORY_SLOT_BAG_0, 23);
    if (firstpositem && (
        firstpositem->GetProto()->RequiredSkill == 762 && firstpositem->GetProto()->RequiredSkillRank > 150 || // 762 = riding skill
        firstpositem->GetProto()->ItemId == 34060 || // Flying Machine Control
        firstpositem->GetProto()->ItemId == 34061))  // Turbo-Charged Flying Machine Control
        chr->CastSpell(chr, firstpositem->GetProto()->Spells[0].SpellId, false);
    // Druidi dostanu switft flight form
    else if (chr->getClass() == CLASS_DRUID)
    {
        // odstranenie formy
        chr->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT);
        chr->CastSpell(chr, 40120, false);
    }
    // alici grifina
    else if (chr->GetTeam() == ALLIANCE)
        chr->CastSpell(chr, 32290, false);
    // horda netopiera
    else
        chr->CastSpell(chr, 32295, false);

    return true;
}

bool ChatHandler::HandleGuildHouseCommand(char* /*args*/)
{
    Player *chr = m_session->GetPlayer();

    // Osetrenie aby sa neportovali za letu
    if (chr->IsFlying())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    //Zakaz portovania
    if (chr->isInCombat()		// Pocas combatu
        || chr->InBattleGround()   // V BattleGrounde (aj arene)
        || chr->HasStealthAura()   // Pocas stealth-u
        || chr->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH)) // S Feign Death (hunter)
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    if (!chr->TeleportToGuildHouse())
    {
        SendSysMessage("You have no guild, or your guild have no guildhouse!");
        SetSentErrorMessage(true);
        return false;
    }

    return true;
}

bool ChatHandler::HandleWSGCommand(char* args)
{
    Player *_player = m_session->GetPlayer();

    if (_player->getLevel() < 70)
    {
        PSendSysMessage(LANG_LEVEL_MINREQUIRED, 70);
        SetSentErrorMessage(true);
        return false;
    }

    // Zakaz prihlasovania za letu
    if (_player->IsFlying())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    // Zakaz prihlasovania v combate, bg a instanciach
    if (_player->isInCombat() || _player->GetMap()->Instanceable())
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    m_session->JoinIntoBattleground(BATTLEGROUND_WS, 0, 0);

    return true;
}
bool ChatHandler::HandleABCommand(char* args)
{
    Player *_player = m_session->GetPlayer();

    if (_player->getLevel() < 70)
    {
        PSendSysMessage(LANG_LEVEL_MINREQUIRED, 70);
        SetSentErrorMessage(true);
        return false;
    }

    // Zakaz prihlasovania za letu
    if (_player->IsFlying())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    // Zakaz prihlasovania v combate, bg a instanciach
    if (_player->isInCombat() || _player->GetMap()->Instanceable())
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    m_session->JoinIntoBattleground(BATTLEGROUND_AB, 0, 0);

    return true;
}

bool ChatHandler::HandleAVCommand(char* args)
{
    Player *_player = m_session->GetPlayer();

    if (_player->getLevel() < 70)
    {
        PSendSysMessage(LANG_LEVEL_MINREQUIRED, 70);
        SetSentErrorMessage(true);
        return false;
    }

    // Zakaz prihlasovania za letu
    if (_player->IsFlying())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    // Zakaz prihlasovania v combate, bg a instanciach
    if (_player->isInCombat() || _player->GetMap()->Instanceable())
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    m_session->JoinIntoBattleground(BATTLEGROUND_AV, 0, 0);

    return true;
}

bool ChatHandler::HandleEOSCommand(char* args)
{
    Player *_player = m_session->GetPlayer();

    if (_player->getLevel() < 70)
    {
        PSendSysMessage(LANG_LEVEL_MINREQUIRED, 70);
        SetSentErrorMessage(true);
        return false;
    }

    // Zakaz prihlasovania za letu
    if (_player->IsFlying())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    // Zakaz prihlasovania v combate, bg a instanciach
    if (_player->isInCombat() || _player->GetMap()->Instanceable())
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    m_session->JoinIntoBattleground(BATTLEGROUND_EY, 0, 0);

    return true;
}
// ==================================================================================================================================================================================
bool ChatHandler::HandleFreezeCommand(char *args)
{
    std::string name;
    Player* player;
    char* TargetName = strtok((char*)args, " "); //get entered #name
    if (!TargetName) //if no #name entered use target
    {
        player = getSelectedPlayer();
        if (player) //prevent crash with creature as target
        {
            name = player->GetName();
            normalizePlayerName(name);
        }
    }
    else // if #name entered
    {
        name = TargetName;
        normalizePlayerName(name);
        player = sObjectMgr.GetPlayer(name.c_str()); //get player by #name
    }


    //effect
    if ((player) && (!(player == m_session->GetPlayer())))
    {
        PSendSysMessage(LANG_COMMAND_FREEZE, name.c_str());

        //stop combat + unattackable + duel block + stop some spells
        player->setFaction(35);
        player->CombatStop();
        if (player->IsNonMeleeSpellCasted(true))
            player->InterruptNonMeleeSpells(true);
        player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        player->SetUInt32Value(PLAYER_DUEL_TEAM, 1);

        //if player class = hunter || warlock remove pet if alive
        if ((player->getClass() == CLASS_HUNTER) || (player->getClass() == CLASS_WARLOCK))
        {
            if (Pet* pet = player->GetPet())
            {
                pet->SavePetToDB(PET_SAVE_AS_CURRENT);
                // not let dismiss dead pet
                if (pet && pet->isAlive())
                    player->RemovePet(PET_SAVE_NOT_IN_SLOT);
            }
        }

        //stop movement and disable spells
        uint32 spellID = 9454; 	// uint32 spellID1 = 23775; // Stun Forever
        player->CastSpell(player, spellID, true);

        //save player
        player->SaveToDB();
    }

    if (!player)
    {
        SendSysMessage(LANG_COMMAND_FREEZE_WRONG);
        return true;
    }

    if (player == m_session->GetPlayer())
    {
        SendSysMessage(LANG_COMMAND_FREEZE_ERROR);
        return true;
    }

    return true;
}

bool ChatHandler::HandleUnFreezeCommand(char *args)
{
    std::string name;
    Player* player;
    char* TargetName = strtok((char*)args, " "); //get entered #name
    if (!TargetName) //if no #name entered use target
    {
        player = getSelectedPlayer();
        if (player) //prevent crash with creature as target
        {
            name = player->GetName();
        }
    }

    else // if #name entered
    {
        name = TargetName;
        normalizePlayerName(name);
        player = sObjectMgr.GetPlayer(name.c_str()); //get player by #name
    }

    //effect
    if (player)
    {
        PSendSysMessage(LANG_COMMAND_UNFREEZE, name.c_str());

        //Reset player faction + allow combat + allow duels
        player->setFactionForRace(player->getRace());
        player->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        //allow movement and spells
        uint32 spellID = 9454; // uint32 spellID1 = 23775;
        player->RemoveAurasDueToSpell(spellID);

        //save player
        player->SaveToDB();
    }

    if (!player)
    {
        if (TargetName)
        {
            //check for offline players
            QueryResult *result = CharacterDatabase.PQuery("SELECT characters.guid FROM `characters` WHERE characters.name = '%s'", name.c_str());
            if (!result)
            {
                SendSysMessage(LANG_COMMAND_FREEZE_WRONG);
                return true;
            }
            //if player found: delete his freeze aura
            Field *fields = result->Fetch();
            uint64 pguid = fields[0].GetUInt64();
            delete result;
            CharacterDatabase.PQuery("DELETE FROM `character_aura` WHERE character_aura.spell = 9454 AND character_aura.guid = '%u'", pguid);
            PSendSysMessage(LANG_COMMAND_UNFREEZE, name.c_str());
            return true;
        }
        else
        {
            SendSysMessage(LANG_COMMAND_FREEZE_WRONG);
            return true;
        }
    }

    return true;
}

bool ChatHandler::HandleListFreezeCommand(char* args)
{
    //Get names from DB
    QueryResult *result = CharacterDatabase.PQuery("SELECT characters.name FROM `characters` LEFT JOIN `character_aura` ON (characters.guid = character_aura.guid) WHERE character_aura.spell = 9454");
    if (!result)
    {
        SendSysMessage(LANG_COMMAND_NO_FROZEN_PLAYERS);
        return true;
    }
    //Header of the names
    PSendSysMessage(LANG_COMMAND_LIST_FREEZE);

    //Output of the results
    do
    {
        Field *fields = result->Fetch();
        std::string fplayers = fields[0].GetCppString();
        PSendSysMessage(LANG_COMMAND_FROZEN_PLAYERS, fplayers.c_str());
    } while (result->NextRow());

    delete result;
    return true;
}

bool ChatHandler::HandleReloadDBCCommand(char* args)
{
    sWorld.CustomizeDBCData();
    SendGlobalSysMessage("DB tables `DBC_*` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadCreatureTemplateCommand(char* args)
{
    sLog.outString("Re-Loading `creature_template` Table!");
    sObjectMgr.LoadCreatureTemplates();
    SendGlobalSysMessage("DB table `creature_template` reloaded.");
    return true;
}

bool ChatHandler::HandleUnsicknessCommand(char* args)
{
    std::string name;
    Player* player;
    char* TargetName = strtok((char*)args, " "); //get entered #name
    if (!TargetName) //if no #name entered use target
    {
        player = getSelectedPlayer();
        if (player) //prevent crash with creature as target
        {
            name = player->GetName();
            normalizePlayerName(name);
        }
    }
    else // if #name entered
    {
        name = TargetName;
        normalizePlayerName(name);
        player = sObjectMgr.GetPlayer(name.c_str()); //get player by #name
    }

    //effect
    if ((player) && (!(player == m_session->GetPlayer())))
    {
        if (player->HasSpell(15007)) // 15007 SPELL_ID_PASSIVE_RESURRECTION_SICKNESS
            player->RemoveAurasDueToSpell(15007); // SPELL_ID_PASSIVE_RESURRECTION_SICKNESS
        else
            PSendSysMessage("You not a Ressurection Sickness!", name.c_str());

        return true;
    }
}

bool ChatHandler::HandleAddItemToAllCommand(char* args)
{
    if (!*args)
        return false;

    uint32 itemId = 0;

    // Vyextrahovanie mena itemu
    if (args[0] == '[')                                        // [name] manual form
    {
        char* citemName = citemName = strtok((char*)args, "]");

        if (citemName && citemName[0])
        {
            std::string itemName = citemName + 1;
            WorldDatabase.escape_string(itemName);
            QueryResult *result = WorldDatabase.PQuery("SELECT entry FROM item_template WHERE name = '%s'", itemName.c_str());
            if (!result)
            {
                PSendSysMessage(LANG_COMMAND_COULDNOTFIND, citemName + 1);
                SetSentErrorMessage(true);
                return false;
            }
            itemId = result->Fetch()->GetUInt16();
            delete result;
        }
        else
            return false;
    }
    else                                                    // item_id or [name] Shift-click form |color|Hitem:item_id:0:0:0|h[name]|h|r
    {
        char* cId = ExtractKeyFromLink(&args, "Hitem");
        if (!cId)
            return false;
        itemId = atol(cId);
    }

    // Ziskanie poctu itemov (nepovinny parameter, defaultne 1)
    char* ccount = strtok(NULL, " ");

    int32 countproto = 1;

    if (ccount)
        countproto = strtol(ccount, NULL, 10);

    if (countproto == 0)
        countproto = 1;

    //Odrstranenie itemov sa nepovoluje
    if (countproto < 0)
    {
        // TODO bodol by aj vypis
        return false;
    }
    // Ziskanie typu itemu
    ItemPrototype const *pProto = sObjectMgr.GetItemPrototype(itemId);
    if (!pProto)
    {
        PSendSysMessage(LANG_COMMAND_ITEMIDINVALID, itemId);
        SetSentErrorMessage(true);
        return false;
    }
    Player* pl = m_session->GetPlayer();

    // Prechod vsetkymi hracmi servra
    HashMapHolder<Player>::MapType& m = ObjectAccessor::Instance().GetPlayers();
    for (HashMapHolder<Player>::MapType::iterator itr = m.begin(); itr != m.end(); ++itr)
    {
        int32 count = countproto;

        Player* plTarget = itr->second;

        //Adding items
        uint32 noSpaceForCount = 0;

        // check space and find places
        ItemPosCountVec dest;
        uint8 msg = plTarget->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount);
        if (msg != EQUIP_ERR_OK)                               // convert to possible store amount
            count -= noSpaceForCount;

        if (count == 0 || dest.empty())                         // can't add any
        {
            PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);
            SetSentErrorMessage(true);
            continue;
        }

        Item* item = plTarget->StoreNewItem(dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));
        if (count > 0 && item)
        {
            pl->SendNewItem(item, count, false, true);
            if (pl != plTarget)
                plTarget->SendNewItem(item, count, true, false);
        }

        if (noSpaceForCount > 0)
            PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);
    }

    return true;
}

bool ChatHandler::HandleSetGHCommand(char* args)
{
	// Vyhladanie postavy v db
	std::string strargs = args;
	CharacterDatabase.escape_string(strargs);

	//                                                        0      1
	QueryResult* result = CharacterDatabase.PQuery("SELECT account, guid FROM characters WHERE name = '%s'", strargs.c_str());
	if (!result)
	{
		SendSysMessage("Chyba: Hrac sa nenasiel.");
		SetSentErrorMessage(true);
		return false;
	}

	// Ziskanie ID accountu a guid postavy
	Field* fields = result->Fetch();
	uint32 account_id = fields[0].GetUInt32();
	uint32 guid = fields[1].GetUInt32();

	// Zmazanie dotazu na postavu
	delete result;

	// Udaje o accounte
	//                                                      0         1            2
	QueryResult* result2 = LoginDatabase.PQuery("SELECT username, gmlevel, GuildHouse_comment FROM account WHERE id = '%u'", account_id);
	if (!result2)
	{
		SendSysMessage("wtf: postava nema ziaden account ?!");
		SetSentErrorMessage(true);
		return false;
	}

	Field* fields2 = result2->Fetch();
	/*
	// Len pre VIP hracov
	if(fields2[1].GetUInt32() != SEC_MODERATOR)
	{
	SendSysMessage("Chyba: Postava nie je na VIP accounte!");
	SetSentErrorMessage(true);
	return false;
	}
	*/
	// Len pre tych, ktori este nemaju gh na svojom acce
	if (!fields2[2].IsNULL())
	{
		PSendSysMessage("Chyba: Account '%s' uz ma nastaveny GH '%s' !", fields2[0].GetString(), fields2[2].GetString());
		SetSentErrorMessage(true);
		return false;
	}

	// Zmazanie dotazu na account
	delete result2;

	// Ziskanie guildy
	//                                                       0
	QueryResult* result3 = CharacterDatabase.PQuery("SELECT name FROM guild_member JOIN guild ON guild_member.guildid = guild.guildid WHERE guild_member.guid = %u", guid);
	if (!result3)
	{
		SendSysMessage("Chyba: Hrac nie je v guilde!");
		SetSentErrorMessage(true);
		return false;
	}

	// Nazov guildy
	Field* fields3 = result3->Fetch();
	std::string guildname = fields3[0].GetCppString();
	LoginDatabase.escape_string(guildname);

	// Zaznam do db
	LoginDatabase.PExecute("UPDATE account SET GuildHouse_comment='%s' WHERE id = %u", guildname.c_str(), account_id);

	PSendSysMessage("Hracovi '%s'(%u) bola nastavena guilda '%s'", strargs.c_str(), guid, fields3[0].GetString());

	// Zmazanie dotazu na guildu
	delete result3;

return true;
}

//Play sound for all online players
bool ChatHandler::HandlePlaySoundToAllCommand(char* args)
{
    // USAGE: .debug playsound #soundid
    // #soundid - ID decimal number from SoundEntries.dbc (1st column)
    uint32 dwSoundId;
    if (!ExtractUInt32(&args, dwSoundId))
        return false;

    if (!sSoundEntriesStore.LookupEntry(dwSoundId))
    {
        PSendSysMessage(LANG_SOUND_NOT_EXIST, dwSoundId);
        SetSentErrorMessage(true);
        return false;
    }

    HashMapHolder<Player>::MapType& m = ObjectAccessor::Instance().GetPlayers();
    for (HashMapHolder<Player>::MapType::iterator itr = m.begin(); itr != m.end(); ++itr)
        itr->second->PlayDirectSound(dwSoundId, itr->second);

    PSendSysMessage(LANG_YOU_HEAR_SOUND, dwSoundId);
    return true;
}

// Mysteria Star
bool ChatHandler::HandleMarkCommand(char* args)
{
    uint32 itemId = 38186;
    int32 count;

    // ak nieje parameter, pocet je defaultne 1
    if (!*args)
        count = 1;
    else
        count = strtol(args, NULL, 10);

    // ak je vlozena hodnota chybna, vrati 0
    if (count == 0)
        return false;

    // Ziskanie targetu hraca
    Player* pl = m_session->GetPlayer();
    Player* plTarget = getSelectedPlayer();
    // Ak nieje target, da Eventerovi samotnemu.
    //TODO: ma to vobec vyznam?
    if (!plTarget)
        plTarget = pl;

    // Sprava do Logu (len pri detajlnom log-ovani)
    sLog.outDetail(GetMangosString(LANG_ADDITEM), itemId, count);

    // Snaha vytvorit objekt (malo by sa podarit ale aj motyka vystreli...)
    ItemPrototype const *pProto = ObjectMgr::GetItemPrototype(itemId);
    if (!pProto)
    {
        PSendSysMessage(LANG_COMMAND_ITEMIDINVALID, itemId);
        SetSentErrorMessage(true);
        return false;
    }

    // odobratie itemu (zaporny pocet)
    if (count < 0)
    {
        if (!plTarget->HasItemCount(itemId, -count, false)) // itemId, count, inBankAlso
        {
            ChatHandler(pl->GetSession()).PSendSysMessage("You do not have enough Mysteria Star!");
            pl->GetSession()->SendNotification("You do not have enough Mysteria Star!");
            return false;
        }

        plTarget->DestroyItemCount(itemId, -count, true, false);
        PSendSysMessage(LANG_REMOVEITEM, itemId, -count, GetNameLink(plTarget).c_str());
        return true;
    }

    // Pridanie itemu
    uint32 noSpaceForCount = 0;

    // kontrola miesta v bagu a najdenie miesta
    ItemPosCountVec dest;
    uint8 msg = plTarget->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount);
    if (msg != EQUIP_ERR_OK)                               // convert to possible store amount
        count -= noSpaceForCount;

    if (count == 0 || dest.empty())                         // can't add any
    {
        PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);
        SetSentErrorMessage(true);
        return false;
    }

    Item* item = plTarget->StoreNewItem(dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));

    // Odstranenie bindovania ak gm si da item sam aby ho mohol tradeovat
    // 
    // TODO ma to vyznam?
    /*
    if(pl==plTarget)
    for(ItemPosCountVec::const_iterator itr = dest.begin(); itr != dest.end(); ++itr)
    if(Item* item1 = pl->GetItemByPos(itr->pos))
    item1->SetBinding( false );
    */

    // Pridanie itemu
    if (count > 0 && item)
    {
        pl->SendNewItem(item, count, false, true);
        if (pl != plTarget)
            plTarget->SendNewItem(item, count, true, false);
    }

    // Chyba pri nedostatku miesta
    if (noSpaceForCount > 0)
        PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);

    return true;
}
