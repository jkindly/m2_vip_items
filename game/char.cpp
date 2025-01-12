#ifdef ENABLE_VIP_ITEMS

#include <memory>
#include <stdexcept>

// Add a premium type to the character
bool CHARACTER::AddPremium(BYTE premiumType, DWORD premiumTime)
{
    if (!GetDesc() || premiumTime == 0)
        return false;

    struct PremiumInfo {
        const char* dbField;
        DWORD affectType;
    };

    static const PremiumInfo premiumInfo[] = {
        {"silver_expire", AFFECT_EXP_BONUS},        // PREMIUM_EXP
        {"gold_expire", AFFECT_ITEM_BONUS},        // PREMIUM_ITEM
        {"money_drop_rate_expire", AFFECT_GOLD_BONUS}, // PREMIUM_GOLD
        {"autoloot_expire", AFFECT_AUTOLOOT}       // PREMIUM_AUTOLOOT
    };

    if (premiumType >= std::size(premiumInfo)) {
        sys_err("Unknown premium type %d: PID: %d", premiumType, GetPlayerID());
        return false;
    }

    const auto& info = premiumInfo[premiumType];

    // Update premium time
    m_aiPremiumTimes[premiumType] = std::max(m_aiPremiumTimes[premiumType], get_global_time()) + premiumTime;

    // Add the affect
    AddAffect(info.affectType, POINT_NONE, 0, 0, GetPremiumRemainSeconds(premiumType), 0, true);

    // Update the database
    char query[256];
    snprintf(query, sizeof(query),
             "UPDATE `srv1_account`.`account` SET `%s` = FROM_UNIXTIME(%d) WHERE `id` = %d;",
             info.dbField,
             m_aiPremiumTimes[premiumType],
             GetDesc()->GetAccountTable().id);

    auto pMsg = DBManager::instance().DirectQuery(query);
    if (pMsg->Get()->uiAffectedRows == 0) {
        sys_err("Failed to update premium for account ID %d", GetDesc()->GetAccountTable().id);
        return false;
    }

    return true;
}

// Save premium times to the database
void CHARACTER::SavePremiumTimes()
{
    if (!GetDesc())
        return;

    TPacketGDPremiumTimes packet = {};
    packet.dwID = GetDesc()->GetAccountTable().id;

    // Copy premium times
    std::copy(std::begin(m_aiPremiumTimes), std::end(m_aiPremiumTimes), std::begin(packet.iPremiumTimes));

    // Send the data to the database
    db_clientdesc->DBPacket(HEADER_GD_SAVE_PREMIUM_TIMES, GetDesc()->GetHandle(), &packet, sizeof(packet));
}

#endif
