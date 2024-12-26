// find:
};

ESex GET_SEX(LPCHARACTER ch);

// add above:
#ifdef ENABLE_VIP_ITEMS
	public:
		bool AddPremium(BYTE byPremiumType, DWORD dwPremiumTime);
		void SavePremiumTimes();
#endif