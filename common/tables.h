// add to the GD headers with free number, for me its 154, but you can have different

#ifdef ENABLE_VIP_ITEMS
	HEADER_GD_SAVE_PREMIUM_TIMES	  = 154,
#endif

// find:
#pragma pack()

// add above:
#ifdef ENABLE_VIP_ITEMS
typedef struct SPacketGDPremiumTimes
{
	DWORD dwID;
	int iPremiumTimes[PREMIUM_MAX_NUM];
} TPacketGDPremiumTimes;
#endif