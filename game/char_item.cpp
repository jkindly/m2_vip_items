// find:
					case USE_SPECIAL:
						switch (item->GetVnum())
						{
							
// add below:
#ifdef ENABLE_VIP_ITEMS
						case ITEM_VIP_DROP_3_DAYS:
						case ITEM_VIP_DROP_7_DAYS:
						case ITEM_VIP_DROP_14_DAYS:
						case ITEM_VIP_EXP_3_DAYS:
						case ITEM_VIP_EXP_7_DAYS:
						case ITEM_VIP_EXP_14_DAYS:
						case ITEM_VIP_GOLD_3_DAYS:
						case ITEM_VIP_GOLD_7_DAYS:
						case ITEM_VIP_GOLD_14_DAYS:
						case ITEM_VIP_GOLD_AUTOLOOT_3_DAYS:
						case ITEM_VIP_GOLD_AUTOLOOT_7_DAYS:
						case ITEM_VIP_GOLD_AUTOLOOT_14_DAYS:
						{
							const auto premiumType = item->GetValue(0);
							const auto premiumDuration = item->GetValue(1);

							if (AddPremium(premiumType, premiumDuration))
							{
								item->SetCount(item->GetCount() - 1);
								SavePremiumTimes();
							}

							break;
						}
#endif