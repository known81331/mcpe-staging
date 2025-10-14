#include "Inventory.hpp"
#include "Item.hpp"
#include "nbt/CompoundTag.hpp"

Inventory::Inventory(Player* pPlayer)
{
	m_pPlayer = pPlayer;
	m_selectedHotbarSlot = 0;

	for (int i = 0; i < C_MAX_HOTBAR_ITEMS; i++)
		m_hotbar[i] = -1;
}

Inventory::~Inventory()
{
	for (std::vector<ItemInstance*>::iterator it = m_items.begin(); it != m_items.end(); it++)
	{
		ItemInstance* item = *it;
		delete item;
	}
}

void Inventory::prepareCreativeInventory()
{
	clear();

	// When we've got a proper creative inventory, use this method for aux tiles/items
	//for (int i = 0; i < 16; i++) // <-- This is an example for all wool colors in order

	// Original list of items.
	addCreativeItem(Tile::rock->m_ID);
	addCreativeItem(Tile::stoneBrick->m_ID);
	addCreativeItem(Tile::dirt->m_ID);
	addCreativeItem(Tile::wood->m_ID);
	addCreativeItem(Tile::wood->m_ID,5);
	addCreativeItem(Tile::torch->m_ID);
	addCreativeItem(Tile::stairs_stone->m_ID, 5 );
	addCreativeItem(Tile::fence->m_ID);
	addCreativeItem(Tile::fence->m_ID,1);
	addCreativeItem(Tile::fence->m_ID,2);
	addCreativeItem(Tile::fence->m_ID,3);
	addCreativeItem(Tile::fence->m_ID,4);
	addCreativeItem(Tile::fence->m_ID,5);
	addCreativeItem(Tile::sandStone->m_ID);
	addCreativeItem(Tile::stairs_stone->m_ID);
	addCreativeItem(Tile::stairs_stone->m_ID, 1 );
	addCreativeItem(Tile::stairs_stone->m_ID, 2 );
	addCreativeItem(Tile::stairs_stone->m_ID, 3 );
	addCreativeItem(Tile::stairs_stone->m_ID, 4 );
	addCreativeItem(Tile::stairs_stone->m_ID, 6 );
	addCreativeItem(Tile::stairs_stone->m_ID, 7 );
	addCreativeItem(Tile::stairs_stone->m_ID, 8 );
	addCreativeItem(Tile::wood->m_ID,1);
	addCreativeItem(Tile::wood->m_ID,2);
	addCreativeItem(Tile::wood->m_ID,3);
	addCreativeItem(Tile::wood->m_ID,4);
	addCreativeItem(Tile::treeTrunk->m_ID);
	addCreativeItem(Tile::treeTrunk->m_ID,1);
	addCreativeItem(Tile::treeTrunk->m_ID,2);
	addCreativeItem(Tile::treeTrunk->m_ID,3);
	addCreativeItem(Tile::treeTrunk->m_ID,4);
	addCreativeItem(Tile::treeTrunk->m_ID,5);
	addCreativeItem(Tile::goldBlock->m_ID);
	addCreativeItem(Tile::ironBlock->m_ID);
	addCreativeItem(Tile::emeraldBlock->m_ID);
	addCreativeItem(Tile::rubyBlock->m_ID);
	addCreativeItem(Tile::redstoneBlock->m_ID);
	addCreativeItem(Tile::redBrick->m_ID);
	addCreativeItem(Tile::leaves->m_ID);
	addCreativeItem(Tile::leaves->m_ID,1);
	addCreativeItem(Tile::leaves->m_ID,2);
	addCreativeItem(Tile::leaves->m_ID,3);
	addCreativeItem(Tile::leaves->m_ID,4);
	addCreativeItem(Tile::leaves->m_ID,5);
	addCreativeItem(Tile::cloth->m_ID,0);
	addCreativeItem(Tile::cloth->m_ID,1);
	addCreativeItem(Tile::cloth->m_ID,2);
	addCreativeItem(Tile::cloth->m_ID,3);
	addCreativeItem(Tile::cloth->m_ID,4);
	addCreativeItem(Tile::cloth->m_ID,5);
	addCreativeItem(Tile::cloth->m_ID,6);
	addCreativeItem(Tile::cloth->m_ID,7);
	addCreativeItem(Tile::cloth->m_ID,8);
	addCreativeItem(Tile::cloth->m_ID,9);
	addCreativeItem(Tile::cloth->m_ID,10);
	addCreativeItem(Tile::cloth->m_ID,11);
	addCreativeItem(Tile::cloth->m_ID,12);
	addCreativeItem(Tile::cloth->m_ID,13);
	addCreativeItem(Tile::cloth->m_ID,14);
	addCreativeItem(Tile::cloth->m_ID,15);

	addCreativeItem(Tile::carpet->m_ID,0);
	addCreativeItem(Tile::carpet->m_ID,1);
	addCreativeItem(Tile::carpet->m_ID,2);
	addCreativeItem(Tile::carpet->m_ID,3);
	addCreativeItem(Tile::carpet->m_ID,4);
	addCreativeItem(Tile::carpet->m_ID,5);
	addCreativeItem(Tile::carpet->m_ID,6);
	addCreativeItem(Tile::carpet->m_ID,7);
	addCreativeItem(Tile::carpet->m_ID,8);
	addCreativeItem(Tile::carpet->m_ID,9);
	addCreativeItem(Tile::carpet->m_ID,10);
	addCreativeItem(Tile::carpet->m_ID,11);
	addCreativeItem(Tile::carpet->m_ID,12);
	addCreativeItem(Tile::carpet->m_ID,13);
	addCreativeItem(Tile::carpet->m_ID,14);
	addCreativeItem(Tile::carpet->m_ID,15);

	addCreativeItem(Tile::glass->m_ID);
	addCreativeItem(Tile::stairs_wood->m_ID);
	addCreativeItem(Tile::stairs_wood->m_ID,1);
	addCreativeItem(Tile::stairs_wood->m_ID,2);
	addCreativeItem(Tile::stairs_wood->m_ID,3);
	addCreativeItem(Tile::stairs_wood->m_ID,4);
	addCreativeItem(Tile::stairs_wood->m_ID,5);
	addCreativeItem(Tile::stoneSlabHalf->m_ID);
	addCreativeItem(Tile::sand->m_ID);
	addCreativeItem(Tile::cactus->m_ID);
	addCreativeItem(Tile::ladder->m_ID);
	addCreativeItem(Tile::shortgrass->m_ID);
	addCreativeItem(Tile::flower->m_ID);
	addCreativeItem(Tile::rose->m_ID);
	addCreativeItem(Tile::mushroom1->m_ID);
	addCreativeItem(Tile::mushroom2->m_ID);
	addCreativeItem(Tile::obsidian->m_ID);
	addCreativeItem(Tile::workbench->m_ID);
	addCreativeItem(Tile::furnace->m_ID);

	addCreativeItem(Tile::stained_hardened_clay->m_ID, 0);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 1);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 2);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 3);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 4);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 5);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 6);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 7);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 8);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 9);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 10);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 11);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 12);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 13);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 14);
	addCreativeItem(Tile::stained_hardened_clay->m_ID, 15);
	addCreativeItem(Tile::hardened_clay->m_ID);

	// New items that weren't in the inventory before.
	addCreativeItem(Tile::grass->m_ID);
	addCreativeItem(Tile::tnt->m_ID);
	addCreativeItem(Tile::gravel->m_ID);
	addCreativeItem(Tile::mossStone->m_ID);
	addCreativeItem(Tile::bookshelf->m_ID);
	addCreativeItem(Tile::lapisBlock->m_ID);
	addCreativeItem(Tile::sponge->m_ID);
	addCreativeItem(Tile::sapling->m_ID);
//	addCreativeItem(Tile::cryingObsidian->m_ID);
//	addCreativeItem(Tile::rocketLauncher->m_ID);
	
	//addCreativeItem(Tile::wheat->m_ID);
	addCreativeItem(Tile::snow->m_ID);
	addCreativeItem(Tile::ice->m_ID);
	addCreativeItem(Tile::farmland->m_ID);
	addCreativeItem(Tile::topSnow->m_ID);
	addCreativeItem(Tile::lapisOre->m_ID);
	addCreativeItem(Tile::coalOre->m_ID);
	addCreativeItem(Tile::redStoneOre->m_ID);
	addCreativeItem(Tile::ironOre->m_ID);
	addCreativeItem(Tile::goldOre->m_ID);
	addCreativeItem(Tile::emeraldOre->m_ID);
	addCreativeItem(Tile::rubyOre->m_ID);
	addCreativeItem(Tile::unbreakable->m_ID);
	
	// test stuff
	//addCreativeItem(Tile::water->m_ID);
	//addCreativeItem(Tile::lava->m_ID);
	//addCreativeItem(Tile::fire->m_ID);

	// items
	addCreativeItem(Item::shovel_iron->m_itemID);
	addCreativeItem(Item::pickAxe_iron->m_itemID);
	addCreativeItem(Item::hatchet_iron->m_itemID);
	addCreativeItem(Item::flintAndSteel->m_itemID);
	addCreativeItem(Item::apple->m_itemID);
	addCreativeItem(Item::bow->m_itemID);
	addCreativeItem(Item::arrow->m_itemID);
	addCreativeItem(Item::coal->m_itemID);
	addCreativeItem(Item::emerald->m_itemID);
	addCreativeItem(Item::ironIngot->m_itemID);
	addCreativeItem(Item::goldIngot->m_itemID);
	addCreativeItem(Item::sword_iron->m_itemID);
	addCreativeItem(Item::sword_wood->m_itemID);
	addCreativeItem(Item::shovel_wood->m_itemID);
	addCreativeItem(Item::pickAxe_wood->m_itemID);
	addCreativeItem(Item::hatchet_wood->m_itemID);
	addCreativeItem(Item::sword_stone->m_itemID);
	addCreativeItem(Item::shovel_stone->m_itemID);
	addCreativeItem(Item::pickAxe_stone->m_itemID);
	addCreativeItem(Item::hatchet_stone->m_itemID);
	addCreativeItem(Item::sword_emerald->m_itemID);
	addCreativeItem(Item::shovel_emerald->m_itemID);
	addCreativeItem(Item::pickAxe_emerald->m_itemID);
	addCreativeItem(Item::hatchet_emerald->m_itemID);
	addCreativeItem(Item::stick->m_itemID);
	addCreativeItem(Item::bowl->m_itemID);
	addCreativeItem(Item::mushroomStew->m_itemID);
	addCreativeItem(Item::sword_gold->m_itemID);
	addCreativeItem(Item::shovel_gold->m_itemID);
	addCreativeItem(Item::pickAxe_gold->m_itemID);
	addCreativeItem(Item::hatchet_gold->m_itemID);
	addCreativeItem(Item::string->m_itemID);
	addCreativeItem(Item::feather->m_itemID);
	addCreativeItem(Item::sulphur->m_itemID);
	addCreativeItem(Item::hoe_wood->m_itemID);
	addCreativeItem(Item::hoe_stone->m_itemID);
	addCreativeItem(Item::hoe_iron->m_itemID);
	addCreativeItem(Item::hoe_emerald->m_itemID);
	addCreativeItem(Item::hoe_gold->m_itemID);
	addCreativeItem(Item::seeds->m_itemID);
	addCreativeItem(Item::wheat->m_itemID);
	addCreativeItem(Item::bread->m_itemID);
	addCreativeItem(Item::helmet_cloth->m_itemID);
	addCreativeItem(Item::chestplate_cloth->m_itemID);
	addCreativeItem(Item::leggings_cloth->m_itemID);
	addCreativeItem(Item::boots_cloth->m_itemID);
	addCreativeItem(Item::helmet_iron->m_itemID);
	addCreativeItem(Item::chestplate_iron->m_itemID);
	addCreativeItem(Item::leggings_iron->m_itemID);
	addCreativeItem(Item::boots_iron->m_itemID);
	addCreativeItem(Item::helmet_diamond->m_itemID);
	addCreativeItem(Item::chestplate_diamond->m_itemID);
	addCreativeItem(Item::leggings_diamond->m_itemID);
	addCreativeItem(Item::boots_diamond->m_itemID);
	addCreativeItem(Item::helmet_gold->m_itemID);
	addCreativeItem(Item::chestplate_gold->m_itemID);
	addCreativeItem(Item::leggings_gold->m_itemID);
	addCreativeItem(Item::boots_gold->m_itemID);
	addCreativeItem(Item::flint->m_itemID);
	addCreativeItem(Item::porkChop_raw->m_itemID);
	addCreativeItem(Item::porkChop_cooked->m_itemID);
	addCreativeItem(Item::painting->m_itemID);
	addCreativeItem(Item::apple_gold->m_itemID);
	addCreativeItem(Item::sign->m_itemID);
	addCreativeItem(Item::door_wood->m_itemID);
	addCreativeItem(Item::bucket_empty->m_itemID);
	addCreativeItem(Item::bucket_water->m_itemID);
	addCreativeItem(Item::bucket_lava->m_itemID);
	addCreativeItem(Item::minecart->m_itemID);
	addCreativeItem(Item::saddle->m_itemID);
	addCreativeItem(Item::door_iron->m_itemID);
	addCreativeItem(Item::redStone->m_itemID);
	addCreativeItem(Item::snowBall->m_itemID);
	addCreativeItem(Item::boat->m_itemID);
	addCreativeItem(Item::leather->m_itemID);
	addCreativeItem(Item::milk->m_itemID);
	addCreativeItem(Item::brick->m_itemID);
	addCreativeItem(Item::clay->m_itemID);
	addCreativeItem(Item::reeds->m_itemID);
	addCreativeItem(Item::paper->m_itemID);
	addCreativeItem(Item::book->m_itemID);
	addCreativeItem(Item::slimeBall->m_itemID);
	addCreativeItem(Item::minecart_chest->m_itemID);
	addCreativeItem(Item::minecart_furnace->m_itemID);
	addCreativeItem(Item::egg->m_itemID);
	addCreativeItem(Item::compass->m_itemID);
	addCreativeItem(Item::fishingRod->m_itemID);
	addCreativeItem(Item::clock->m_itemID);
	addCreativeItem(Item::yellowDust->m_itemID);
	addCreativeItem(Item::fish_raw->m_itemID);
	addCreativeItem(Item::fish_cooked->m_itemID);

	addCreativeItem(Item::dye_powder->m_itemID,0);
	addCreativeItem(Item::dye_powder->m_itemID,1);
	addCreativeItem(Item::dye_powder->m_itemID,2);
	addCreativeItem(Item::dye_powder->m_itemID,3);
	addCreativeItem(Item::dye_powder->m_itemID,4);
	addCreativeItem(Item::dye_powder->m_itemID,5);
	addCreativeItem(Item::dye_powder->m_itemID,6);
	addCreativeItem(Item::dye_powder->m_itemID,7);
	addCreativeItem(Item::dye_powder->m_itemID,8);
	addCreativeItem(Item::dye_powder->m_itemID,9);
	addCreativeItem(Item::dye_powder->m_itemID,10);
	addCreativeItem(Item::dye_powder->m_itemID,11);
	addCreativeItem(Item::dye_powder->m_itemID,12);
	addCreativeItem(Item::dye_powder->m_itemID,13);
	addCreativeItem(Item::dye_powder->m_itemID,14);
	addCreativeItem(Item::dye_powder->m_itemID,15);


	addCreativeItem(Item::bone->m_itemID);
	addCreativeItem(Item::sugar->m_itemID);
	addCreativeItem(Item::cake->m_itemID);
	addCreativeItem(Item::bed->m_itemID);
	addCreativeItem(Item::diode->m_itemID);
	addCreativeItem(Item::record_01->m_itemID);
	addCreativeItem(Item::record_02->m_itemID);
	addCreativeItem(Item::camera->m_itemID);
	addCreativeItem(Item::rocket->m_itemID);


	addCreativeItem(Item::mobPlacer->m_itemID,0);
	addCreativeItem(Item::mobPlacer->m_itemID,1);
	addCreativeItem(Item::mobPlacer->m_itemID,2);
	addCreativeItem(Item::mobPlacer->m_itemID,3);
	addCreativeItem(Item::mobPlacer->m_itemID,4);
	addCreativeItem(Item::mobPlacer->m_itemID,5);
	addCreativeItem(Item::mobPlacer->m_itemID,6);
	addCreativeItem(Item::mobPlacer->m_itemID,7);
	addCreativeItem(Item::mobPlacer->m_itemID,8);
	addCreativeItem(Item::mobPlacer->m_itemID,9);
	addCreativeItem(Item::mobPlacer->m_itemID,10);
	addCreativeItem(Item::mobPlacer->m_itemID,11);
	addCreativeItem(Item::mobPlacer->m_itemID,12);
	addCreativeItem(Item::mobPlacer->m_itemID,13);
	addCreativeItem(Item::mobPlacer->m_itemID,14);
	addCreativeItem(Item::mobPlacer->m_itemID,15);

	// more stuff
	addCreativeItem(Tile::stoneSlabHalf->m_ID, 1);
	addCreativeItem(Tile::stoneSlabHalf->m_ID, 2);
	addCreativeItem(Tile::stoneSlabHalf->m_ID, 3);
	addCreativeItem(Tile::deadBush->m_ID);
	addCreativeItem(Tile::pumpkin->m_ID);
	addCreativeItem(Tile::pumpkinLantern->m_ID);
	addCreativeItem(Tile::netherrack->m_ID);
	addCreativeItem(Tile::soulSand->m_ID);
	addCreativeItem(Tile::glowstone->m_ID);
	addCreativeItem(Tile::web->m_ID);

	for (int i = 0; i < C_MAX_HOTBAR_ITEMS; i++)
		m_hotbar[i] = i;
}

void Inventory::prepareSurvivalInventory()
{
	clear();
	m_items.resize(C_NUM_SURVIVAL_SLOTS);

	// Add some items for testing
	addTestItem(Item::stick->m_itemID, 64);
	addTestItem(Item::wheat->m_itemID, 64);
	addTestItem(Item::sugar->m_itemID, 64);
	addTestItem(Item::camera->m_itemID, 64);
	addTestItem(Tile::ladder->m_ID, 64);
	addTestItem(Tile::obsidian->m_ID, 64);
	addTestItem(Tile::fire->m_ID, 64);

	for (int i = 0; i < C_MAX_HOTBAR_ITEMS; i++)
		m_hotbar[i] = i;
}

int Inventory::getNumSlots()
{
	switch (_getGameMode())
	{
	case GAME_TYPE_SURVIVAL:
		return C_NUM_SURVIVAL_SLOTS;
	default:
		return getNumItems();
	}
}

int Inventory::getNumItems()
{
	return int(m_items.size());
}

void Inventory::addCreativeItem(int itemID, int auxValue)
{
	m_items.push_back(new ItemInstance(itemID, 1, auxValue));
}

void Inventory::empty()
{
	for (int i = 0; i < m_items.size(); i++)
	{
		delete m_items[i];
		m_items[i] = nullptr;
	}
}

void Inventory::clear()
{
	for (int i = 0; i < m_items.size(); i++)
	{
		delete m_items[i];
	}
	m_items.clear();
}

// This code, and this function, don't exist in b1.2_02
// "add" exists with these same arguments, which calls "addResource",
// but addResource's code is entirely different somehow. Did we write this from scratch?
bool Inventory::addItem(ItemInstance& instance)
{
	if (_getGameMode() == GAME_TYPE_CREATIVE)
	{
		// Just get rid of the item.
		instance.m_count = 0;
		return true;
	}
	
	// look for an item with the same ID
	for (int i = 0; i < getNumItems(); i++)
	{
		ItemInstance* item = m_items[i];
		if (!item || item->m_itemID != instance.m_itemID)
			continue;

		int maxStackSize = item->getMaxStackSize();
		bool bIsStackedByData = instance.getItem()->isStackedByData();
		if (bIsStackedByData && item->getAuxValue() != instance.getAuxValue())
			continue;

		// try to collate.
		int combinedItemAmount = instance.m_count + item->m_count;

		int leftover = combinedItemAmount - maxStackSize;
		if (leftover < 0)
			leftover = 0;
		else
			combinedItemAmount = C_MAX_AMOUNT;

		item->m_count = combinedItemAmount;
		item->m_popTime = 5;

		instance.m_count = leftover;

		if (!bIsStackedByData)
			item->setAuxValue(0);
	}

	// If there's nothing leftover:
	if (instance.m_count <= 0)
		return true;

	// try to add it to an empty slot
	for (int i = 0; i < getNumItems(); i++)
	{
		ItemInstance* item = m_items[i];

		if (item)
		{
			if (item->m_itemID != 0)
				continue;
			delete item;
		}

		item = m_items[i] = new ItemInstance(instance);
        item->m_popTime = 5;
		instance.m_count = 0;
		return true;
	}

	return false;
}

// Doesn't exist in PE
void Inventory::tick()
{
    for (int i = 0; i < m_items.size(); i++)
    {
		ItemInstance* item = m_items[i];

        if (!ItemInstance::isNull(item) && item->m_popTime > 0)
        {
			item->m_popTime--;
        }
    }
}

void Inventory::addTestItem(int itemID, int amount, int auxValue)
{
	ItemInstance inst(itemID, amount, auxValue);
	addItem(inst);

	if (inst.m_count != 0)
	{
		LOG_I("AddTestItem: Couldn't add all %d of %s, only gave %d",
			amount, Item::items[itemID]->m_DescriptionID.c_str(), amount - inst.m_count);
	}
}

ItemInstance* Inventory::getItem(int slotNo)
{
	if (slotNo < 0 || slotNo >= int(m_items.size()))
		return nullptr;

	ItemInstance* item = m_items[slotNo];
	if (!item)
		return nullptr;

	if (item->m_count <= 0)
		item->m_itemID = 0;

	return item;
}

int Inventory::getQuickSlotItemId(int slotNo)
{
	ItemInstance* pInst = getQuickSlotItem(slotNo);
	if (!pInst)
		return -1;

	return pInst->m_itemID;
}

ItemInstance* Inventory::getQuickSlotItem(int slotNo)
{
	if (slotNo < 0 || slotNo >= C_MAX_HOTBAR_ITEMS)
		return nullptr;
	
	ItemInstance* pInst = getItem(m_hotbar[slotNo]);

	return !ItemInstance::isNull(pInst) ? pInst : nullptr;
}

ItemInstance* Inventory::getSelectedItem()
{
	return getQuickSlotItem(m_selectedHotbarSlot);
}

int Inventory::getSelectedItemId()
{
	return getQuickSlotItemId(m_selectedHotbarSlot);
}

void Inventory::selectItem(int slotNo, int maxHotBarSlot)
{
	if (slotNo < 0 || slotNo >= getNumItems())
		return;

	// look for it in the hotbar
	for (int i = 0; i < maxHotBarSlot; i++)
	{
		if (m_hotbar[i] == slotNo)
		{
			m_selectedHotbarSlot = i;
			return;
		}
	}

	for (int i = maxHotBarSlot - 2; i >= 0; i--)
		m_hotbar[i + 1] = m_hotbar[i];

	m_hotbar[0] = slotNo;
	m_selectedHotbarSlot = 0;
}

void Inventory::selectSlot(int slotNo)
{
	if (slotNo < 0 || slotNo >= C_MAX_HOTBAR_ITEMS)
		return;

	m_selectedHotbarSlot = slotNo;
}

void Inventory::setQuickSlotIndexByItemId(int slotNo, int itemID)
{
	if (slotNo < 0 || slotNo >= C_MAX_HOTBAR_ITEMS)
		return;

	if (_getGameMode() == GAME_TYPE_SURVIVAL)
		return; // TODO

	for (int i = 0; i < getNumItems(); i++)
	{
		ItemInstance* item = m_items[i];
		if (item && item->m_itemID == itemID)
		{
			m_hotbar[slotNo] = i;
			return;
		}
	}

	m_hotbar[slotNo] = -1;
}

void Inventory::selectItemById(int itemID, int maxHotBarSlot)
{
	for (int i = 0; i < getNumItems(); i++)
	{
		ItemInstance* item = m_items[i];
		if (!item || item->m_itemID != itemID)
			continue;

		selectItem(i, maxHotBarSlot);
		return;
	}

	LOG_W("selectItemById: %d doesn't exist", itemID);
}

void Inventory::selectItemByIdAux(int itemID, int auxValue, int maxHotBarSlot)
{
	for (int i = 0; i < getNumItems(); i++)
	{
		ItemInstance* item = m_items[i];
		if (!item || item->m_itemID != itemID || item->getAuxValue() != auxValue)
			continue;

		selectItem(i, maxHotBarSlot);
		return;
	}

	LOG_W("selectItemByIdAux: %d:%d doesn't exist", itemID, auxValue);
}

int Inventory::getAttackDamage(Entity* pEnt)
{
	ItemInstance* pInst = getSelected();
	if (ItemInstance::isNull(pInst))
		return 1;

	return pInst->getAttackDamage(pEnt);
}

void Inventory::dropAll(bool onlyClearContainer)
{
	for (int i = 0; i < getNumItems(); i++)
	{
		ItemInstance* item = m_items[i];
		if (item && item->m_count > 0)
		{
			if (!onlyClearContainer)
				m_pPlayer->drop(*item, true);
			item->m_count = 0;
		}
	}
}

void Inventory::save(ListTag& tag) const
{
	if (_getGameMode() == GAME_TYPE_CREATIVE)
		return;

	for (int i = 0; i < m_items.size(); i++)
	{
		const ItemInstance* item = m_items[i];

		if (ItemInstance::isNull(item))
			continue;

		CompoundTag* itemTag = new CompoundTag();
		itemTag->putInt8("Slot", i);
		/* On PE, Mojang for some reason limited something saved as a 16-bit signed integer to a 0-255 range.
		if (item.getAuxValue() < 0)
		{
			item.setAuxValue(0);
		}
		else if (item.getAuxValue > 255)
		{
			item.setAuxValue(255);
		}
		*/
		item->save(*itemTag);
		tag.add(itemTag);
	}
}

void Inventory::load(const ListTag& tag)
{
	if (_getGameMode() == GAME_TYPE_CREATIVE)
		return;

	clear();
	m_items.resize(C_NUM_SURVIVAL_SLOTS);

	const std::vector<Tag*>& itemTags = tag.rawView();

	for (std::vector<Tag*>::const_iterator it = itemTags.begin(); it != itemTags.end(); it++)
	{
		const CompoundTag* itemTag = (const CompoundTag*)*it;
		int slot = itemTag->getInt8("Slot") & 255;
		ItemInstance* item = ItemInstance::fromTag(*itemTag);
		if (item)
		{
			if (slot >= 0 && slot < m_items.size())
			{
				m_items[slot] = item;
			}

			/*if (slot >= 100 && slot < m_armor.size() + 100)
			{
				m_armor[slot - 100] = item;
			}*/
		}
	}
}

GameType Inventory::_getGameMode() const
{
	return m_pPlayer->getPlayerGameType();
}
