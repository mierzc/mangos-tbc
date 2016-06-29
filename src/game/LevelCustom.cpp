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
