// find:
			default:
				sys_err("Unknown header (header: %d handle: %d length: %d)", header, dwHandle, dwLength);
				break;

// add above:
#ifdef ENABLE_VIP_ITEMS
			case HEADER_GD_SAVE_PREMIUM_TIMES:
				SavePremiumTimes(peer, (TPacketGDPremiumTimes*)data);
				break;
#endif

// add at the end of the file:
#ifdef ENABLE_VIP_ITEMS
void CClientManager::SavePremiumTimes(CPeer* peer, TPacketGDPremiumTimes* p)
{
	CLoginData* pkLD = GetLoginDataByAID(p->dwID);
	if (pkLD)
	{
		pkLD->SetPremium(p->iPremiumTimes);
	}
}
#endif