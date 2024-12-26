// add at the end of the file:
#ifdef ENABLE_VIP_ITEMS
bool CHARACTER::AddPremium(BYTE byPremiumType, DWORD dwPremiumTime)
{
	if (!GetDesc())
	{
		return false;
	}

	if (dwPremiumTime <= 0)
	{
		return false;
	}

	std::string premiumStr = "";
	DWORD affect = 0;

	switch (byPremiumType)
	{
	case PREMIUM_EXP:
		premiumStr = "silver_expire";
		affect = AFFECT_EXP_BONUS;
		break;
	case PREMIUM_ITEM:
		premiumStr = "gold_expire";
		affect = AFFECT_ITEM_BONUS;
		break;
	case PREMIUM_GOLD:
		premiumStr = "money_drop_rate_expire";
		affect = AFFECT_GOLD_BONUS;
		break;
	case PREMIUM_AUTOLOOT:
		premiumStr = "autoloot_expire";
		affect = AFFECT_AUTOLOOT;
		break;
	default:
		sys_err("Uknown premium type %d: PID: %d", byPremiumType, GetPlayerID());
		return false;
	}

	if (GetPremiumRemainSeconds(byPremiumType) <= 0)
	{
		m_aiPremiumTimes[byPremiumType] = get_global_time() + dwPremiumTime;
	}
	else
	{
		m_aiPremiumTimes[byPremiumType] += dwPremiumTime;
	}

	AddAffect(affect, POINT_NONE, 0, 0, GetPremiumRemainSeconds(byPremiumType), 0, true);

	std::unique_ptr<SQLMsg> pMsg(
		DBManager::instance().DirectQuery(
			"UPDATE `srv1_account`.`account` SET `%s` = FROM_UNIXTIME(%d) WHERE `id` = %d;",
			premiumStr.c_str(),
			m_aiPremiumTimes[byPremiumType],
			GetDesc()->GetAccountTable().id
		)
	);
	
	if (pMsg->Get()->uiAffectedRows == 0)
	{
		sys_err("Error during adding premium to player account. Error: %d", pMsg->uiSQLErrno);
		return false;
	}

	return true;
}

void CHARACTER::SavePremiumTimes()
{
	if (!GetDesc())
	{
		return;
	}

	TPacketGDPremiumTimes packet{};

	packet.dwID = GetDesc()->GetAccountTable().id;
	thecore_memcpy(packet.iPremiumTimes, m_aiPremiumTimes, sizeof(packet.iPremiumTimes));

	db_clientdesc->DBPacket(HEADER_GD_SAVE_PREMIUM_TIMES, GetDesc()->GetHandle(), &packet, sizeof(packet));
}
#endif