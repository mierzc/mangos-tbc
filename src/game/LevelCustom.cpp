#include "Chat.h"
#include "Language.h"

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
