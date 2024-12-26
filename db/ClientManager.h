// find:
};

template<class Func>
Func CClientManager::for_each_peer(Func f)

// add above:
#ifdef ENABLE_VIP_ITEMS
public:
	void SavePremiumTimes(CPeer* peer, TPacketGDPremiumTimes* p);
#endif	