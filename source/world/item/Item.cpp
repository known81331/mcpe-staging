/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "Item.hpp"

#include "CameraItem.hpp"
#include "DoorItem.hpp"
#include "TileItem.hpp"
#include "TilePlanterItem.hpp"
#include "RocketItem.hpp"
#include "DyePowderItem.hpp"

#define ITEM(x) ((x) - 256)

#define NEW_ITEM(id) (new Item(ITEM(id)))
#define NEW_X_ITEM(Type, id, ...) (new Type(ITEM(id), __VA_ARGS__))
#define NEW_X_ITEMN(Type, id) (new Type(ITEM(id)))

static bool g_bInittedItems = false;

Item* Item::items[C_MAX_ITEMS];

Item::Item(int itemID)
{
	m_bHandEquipped = 0;
	m_itemID = itemID + 256;
	m_bStackedByData = 0;
	m_pCraftingRemainingItem = 0;
	m_maxStackSize = 64;
	m_maxDamage = 32;

#ifndef ORIGINAL_CODE
	//@UB: Not initializing m_icon.
	m_icon = 0;
#endif


	if (Item::items[m_itemID])
	{
		LOG_W("Item conflict id @ %d! Id already used\n", m_itemID);
	}

	Item::items[m_itemID] = this;
}

Item* Item::setIcon(int icon)
{
	m_icon = icon;
	return this;
}

Item* Item::setIcon(int ix, int iy)
{
	return setIcon(ix + 16 * iy);
}

Item* Item::setMaxStackSize(int mss)
{
	m_maxStackSize = mss;
	return this;
}

Item* Item::setCraftingRemainingItem(Item* pItem)
{
	if (m_maxStackSize > 1)
		LOG_W("Max stack size must be 1 for items with crafting results");

	m_pCraftingRemainingItem = pItem;

	return this;
}

Item* Item::setDescriptionId(const std::string& desc)
{
	m_DescriptionID = ICON_DESCRIPTION_PREFIX + desc;
	return this;
}

Item* Item::handEquipped()
{
	//@NOTE: This refers to the in-hand renderer when one is in 3rd person mode.
	// Instead of holding the item nearly parallel to the ground, the item is held
	// perpendicular to the ground. It can be seen in swords (where this is true)
	// vs. compasses (where this is false).
	m_bHandEquipped = true;
	return this;
}

void Item::initItems()
{
	if (g_bInittedItems)
		return;

	g_bInittedItems = true;

	Item::arrow = NEW_ITEM(ITEM_ARROW)
		->setIcon(2, 0)
		->setDescriptionId("arrow");

	Item::coal = NEW_ITEM(ITEM_COAL)
		->setIcon(7, 0)
		->setDescriptionId("coal");

	Item::emerald = NEW_ITEM(ITEM_EMERALD)
		->setIcon(6, 3)
		->setDescriptionId("emerald");

	Item::ironIngot = NEW_ITEM(ITEM_INGOT_IRON)
		->setIcon(1, 7)
		->setDescriptionId("ingotIron");

	Item::goldIngot = NEW_ITEM(ITEM_INGOT_GOLD)
		->setIcon(2, 6)
		->setDescriptionId("ingotGold");

	Item::stick = NEW_ITEM(ITEM_STICK)
		->setIcon(2, 13)
		->handEquipped()
		->setDescriptionId("stick");

	Item::bowl = NEW_ITEM(ITEM_BOWL)
		->setIcon(8, 1)
		->setDescriptionId("bowl");

	Item::mushroomStew = NEW_ITEM(ITEM_STEW_MUSHROOM)
		->setIcon(8, 4)
		->setDescriptionId("mushroomStew");

	Item::string = NEW_ITEM(ITEM_STRING)
		->setIcon(3, 13)
		->setDescriptionId("string");

	Item::feather = NEW_ITEM(ITEM_FEATHER)
		->setIcon(3, 5)
		->setDescriptionId("feather");

	Item::sulphur = NEW_ITEM(ITEM_SULPHUR)
		->setIcon(4, 6)
		->setDescriptionId("sulphur");

	Item::seeds = NEW_ITEM(ITEM_SEEDS)
		->setIcon(9, 0)
		->setDescriptionId("seeds");

	Item::reeds = NEW_X_ITEM(TilePlanterItem, ITEM_REEDS, TILE_REEDS)
		->setIcon(11, 1)
		->setDescriptionId("reeds");

	Item::wheat = NEW_ITEM(ITEM_WHEAT)
		->setIcon(10, 13)
		->setDescriptionId("wheat");

	Item::bread = NEW_ITEM(ITEM_BREAD)
		->setIcon(9, 2)
		->setDescriptionId("bread");

	Item::flint = NEW_ITEM(ITEM_FLINT)
		->setIcon(12, 5)
		->setDescriptionId("flint");

	Item::porkChop_raw = NEW_ITEM(ITEM_PORKCHOP_RAW)
		->setIcon(2, 9)
		->setDescriptionId("porkchopRaw");

	Item::porkChop_cooked = NEW_ITEM(ITEM_PORKCHOP_COOKED)
		->setIcon(1, 9)
		->setDescriptionId("porkchopCooked");

	Item::apple = NEW_ITEM(ITEM_APPLE)
		->setIcon(10, 0)
		->setDescriptionId("appleGold");

	Item::apple_gold = NEW_ITEM(ITEM_APPLE_GOLD)
		->setIcon(11, 0)
		->setDescriptionId("appleGold");

	Item::door_wood = NEW_X_ITEM(DoorItem, ITEM_DOOR_WOOD, Material::wood)
		->setIcon(9, 3)
		->setDescriptionId("doorWood");

	Item::bucket_empty = NEW_ITEM(ITEM_BUCKET)
		->setIcon(10, 4)
		->setDescriptionId("bucket");

	Item::bucket_water = NEW_ITEM(ITEM_BUCKET_WATER)
		->setIcon(11, 4)
		->setDescriptionId("bucketWater");
		//->setCraftingRemainingItem(emptyBucket);

	Item::bucket_lava = NEW_ITEM(ITEM_BUCKET_LAVA)
		->setIcon(12, 4)
		->setDescriptionId("bucketLava");
		//>setCraftingRemainingItem(emptyBucket);

	Item::minecart = NEW_ITEM(ITEM_MINECART)
		->setIcon(7, 8)
		->setDescriptionId("minecart");

	Item::minecart_chest = NEW_ITEM(ITEM_MINECART_CHEST)
		->setIcon(7, 9)
		->setDescriptionId("minecartChest");

	Item::minecart_furnace = NEW_ITEM(ITEM_MINECART_FURNACE)
		->setIcon(7, 10)
		->setDescriptionId("minecartFurnace");

	Item::boat = NEW_ITEM(ITEM_BOAT)
		->setIcon(8, 8)
		->setDescriptionId("boat");

	Item::door_iron = NEW_X_ITEM(DoorItem, ITEM_DOOR_IRON, Material::metal)
		->setIcon(8, 3)
		->setDescriptionId("doorIron");
	
	Item::redStone = NEW_ITEM(ITEM_REDSTONE)
		->setIcon(8, 3)
		->setDescriptionId("redstone");

	Item::snowBall = NEW_ITEM(ITEM_SNOWBALL)
		->setIcon(14, 0)
		->setDescriptionId("snowball");

	Item::saddle = NEW_ITEM(ITEM_SADDLE)
		->setIcon(8, 6)
		->setDescriptionId("saddle");

	Item::leather = NEW_ITEM(ITEM_LEATHER)
		->setIcon(4, 7)
		->setDescriptionId("leather");

	Item::milk = NEW_ITEM(ITEM_BUCKET_MILK)
		->setIcon(13, 4)
		->setDescriptionId("milk");
		//->setCraftingRemainingItem(emptyBucket);

	Item::brick = NEW_ITEM(ITEM_BRICK)
		->setIcon(15, 1)
		->setDescriptionId("brick");

	Item::clay = NEW_ITEM(ITEM_CLAY)
		->setIcon(2, 3)
		->setDescriptionId("clay");

	Item::reeds = NEW_X_ITEM(TilePlanterItem, ITEM_REEDS, TILE_REEDS)
		->setIcon(10, 10)
		->setDescriptionId("reeds");

		/////////////
	Item::paper = NEW_ITEM(ITEM_PAPER)
		->setIcon(11, 8)
		->setDescriptionId("paper");

	Item::book = NEW_ITEM(ITEM_BOOK)
		->setIcon(0, 1)
		->setDescriptionId("book");

	Item::slimeBall = NEW_ITEM(ITEM_SLIME_BALL)
		->setIcon(15, 11)
		->setDescriptionId("slimeball");

	Item::egg = NEW_ITEM(ITEM_EGG)
		->setIcon(10, 4)
		->setDescriptionId("egg");

	Item::compass = NEW_ITEM(ITEM_COMPASS)
		->setIcon(12, 13)
		->setDescriptionId("compass");

	Item::fishingRod = NEW_ITEM(ITEM_FISHING_ROD)
		->setIcon(5, 4)
		->setDescriptionId("fishingRod");

	Item::dye_powder = NEW_ITEM(ITEM_DYE_POWDER)
		->setIcon(14, 4)
		->setDescriptionId("dyePowder");

	Item::clock = NEW_ITEM(ITEM_CLOCK)
		->setIcon(11, 13)
		->setDescriptionId("clock");

	Item::yellowDust = NEW_ITEM(ITEM_YELLOW_DUST)
		->setIcon(9, 4)
		->setDescriptionId("yellowDust");

	Item::fish_raw = NEW_ITEM(ITEM_FISH_RAW)
		->setIcon(9, 5)
		->setDescriptionId("fishRaw");

	Item::fish_cooked = NEW_ITEM(ITEM_FISH_COOKED)
		->setIcon(10, 5)
		->setDescriptionId("fishCooked");

	Item::bone = NEW_ITEM(ITEM_BONE)
		->setIcon(14, 0)
		->setDescriptionId("bone")
		->handEquipped();

	Item::sugar = NEW_ITEM(ITEM_SUGAR)
		->setIcon(4, 13)
		->setDescriptionId("sugar")
		->handEquipped(); // weirdly also in JE

	Item::cake = NEW_ITEM(ITEM_CAKE)
		->setIcon(13, 1)
		->setMaxStackSize(1)
		->setDescriptionId("cake");

	Item::bed = NEW_ITEM(ITEM_BED)
		->setIcon(13, 2)
		->setDescriptionId("bed");

	Item::diode = NEW_ITEM(ITEM_DIODE)
		->setIcon(6, 5)
		->setDescriptionId("diode");

	Item::cookie = NEW_ITEM(ITEM_COOKIE)
		->setMaxStackSize(8)
		->setIcon(12, 5)
		->setDescriptionId("cookie");

	Item::sign = NEW_ITEM(ITEM_SIGN)
		->setIcon(10, 2)
		->setDescriptionId("sign");

	Item::painting = NEW_ITEM(ITEM_PAINTING)
		->setIcon(10, 1)
		->setDescriptionId("painting");

	Item::record_01 = NEW_ITEM(ITEM_RECORD_01)
		->setIcon(0, 15)
		->setDescriptionId("record");

	Item::record_02 = NEW_ITEM(ITEM_RECORD_02)
		->setIcon(1, 15)
		->setDescriptionId("record");

	Item::camera = NEW_X_ITEMN(CameraItem, ITEM_CAMERA)
		->setIcon(2, 15)
		->setDescriptionId("camera");

	Item::rocket = NEW_X_ITEMN(RocketItem, ITEM_ROCKET)
		->setIcon(14, 2)
		->setDescriptionId("rocket");


	Item::shovel_iron = NEW_ITEM(ITEM_SHOVEL_IRON)
		->setIcon(6, 11)
		->setDescriptionId("clock");

	Item::pickAxe_iron = NEW_ITEM(ITEM_PICKAXE_IRON)
		->setIcon(14, 8)
		->setDescriptionId("clock");

	Item::hatchet_iron = NEW_ITEM(ITEM_HATCHET_IRON)
		->setIcon(5, 0)
		->setDescriptionId("clock");

	Item::flintAndSteel = NEW_X_ITEM(TilePlanterItem, ITEM_FLINT_AND_STEEL, TILE_FIRE) 
		->setIcon(13, 5)
		->setDescriptionId("flintAndSteel");

	Item::apple = NEW_ITEM(ITEM_APPLE)
		->setIcon(0, 0)
		->setDescriptionId("clock");

	Item::bow = NEW_ITEM(ITEM_BOW)
		->setIcon(12, 1)
		->setDescriptionId("clock");

	Item::coal = NEW_ITEM(ITEM_COAL)
		->setIcon(3, 3)
		->setDescriptionId("clock");

	Item::sword_iron = NEW_ITEM(ITEM_SWORD_IRON)
		->setIcon(7, 13)
		->setDescriptionId("clock");

	Item::sword_wood = NEW_ITEM(ITEM_SWORD_WOOD)
		->setIcon(5, 13)
		->setDescriptionId("clock");

	Item::shovel_wood = NEW_ITEM(ITEM_SHOVEL_WOOD)
		->setIcon(4, 11)
		->setDescriptionId("clock");

	Item::pickAxe_wood = NEW_ITEM(ITEM_PICKAXE_WOOD)
		->setIcon(12, 8)
		->setDescriptionId("clock");

	Item::hatchet_wood = NEW_ITEM(ITEM_HATCHET_WOOD)
		->setIcon(3, 0)
		->setDescriptionId("clock");
		
	Item::sword_stone = NEW_ITEM(ITEM_SWORD_STONE)
		->setIcon(6, 13)
		->setDescriptionId("clock");
		
	Item::shovel_stone = NEW_ITEM(ITEM_SHOVEL_STONE)
		->setIcon(5, 11)
		->setDescriptionId("clock");
		
	Item::pickAxe_stone = NEW_ITEM(ITEM_PICKAXE_STONE)
		->setIcon(13, 8)
		->setDescriptionId("clock");
		
	Item::hatchet_stone = NEW_ITEM(ITEM_HATCHET_STONE)
		->setIcon(4, 0)
		->setDescriptionId("clock");
		
	Item::sword_emerald = NEW_ITEM(ITEM_SWORD_EMERALD)
		->setIcon(9, 13)
		->setDescriptionId("clock");
		
	Item::shovel_emerald = NEW_ITEM(ITEM_SHOVEL_EMERALD)
		->setIcon(8, 11)
		->setDescriptionId("clock");
		
	Item::pickAxe_emerald = NEW_ITEM(ITEM_PICKAXE_EMERALD)
		->setIcon(0, 9)
		->setDescriptionId("clock");
		
	Item::hatchet_emerald = NEW_ITEM(ITEM_HATCHET_EMERALD)
		->setIcon(7, 0)
		->setDescriptionId("clock");
		
	Item::mushroomStew = NEW_ITEM(ITEM_STEW_MUSHROOM)
		->setIcon(4, 8)
		->setDescriptionId("clock");
		
	Item::sword_gold = NEW_ITEM(ITEM_SWORD_GOLD)
		->setIcon(8, 13)
		->setDescriptionId("clock");
		
	Item::shovel_gold = NEW_ITEM(ITEM_SHOVEL_GOLD)
		->setIcon(7, 11)
		->setDescriptionId("clock");
		
	Item::pickAxe_gold = NEW_ITEM(ITEM_PICKAXE_GOLD)
		->setIcon(15, 8)
		->setDescriptionId("clock");
		
	Item::hatchet_gold = NEW_ITEM(ITEM_HATCHET_GOLD)
		->setIcon(6, 0)
		->setDescriptionId("clock");
		
	Item::hoe_wood = NEW_ITEM(ITEM_HOE_WOOD)
		->setIcon(10, 6)
		->setDescriptionId("clock");
		
	Item::hoe_stone = NEW_ITEM(ITEM_HOE_STONE)
		->setIcon(11, 6)
		->setDescriptionId("clock");
		
	Item::hoe_iron = NEW_ITEM(ITEM_HOE_IRON)
		->setIcon(12, 6)
		->setDescriptionId("clock");
		
	Item::hoe_emerald = NEW_ITEM(ITEM_HOE_EMERALD)
		->setIcon(14, 6)
		->setDescriptionId("clock");
		
	Item::hoe_gold = NEW_ITEM(ITEM_HOE_GOLD)
		->setIcon(13, 6)
		->setDescriptionId("clock");
		
	Item::seeds = NEW_ITEM(ITEM_SEEDS)
		->setIcon(1, 11)
		->setDescriptionId("clock");
		
	Item::bread = NEW_ITEM(ITEM_BREAD)
		->setIcon(13, 1)
		->setDescriptionId("clock");
		
	Item::helmet_cloth = NEW_ITEM(ITEM_HELMET_CLOTH)
		->setIcon(5, 6)
		->setDescriptionId("clock");
		
	Item::chestplate_cloth = NEW_ITEM(ITEM_CHESTPLATE_CLOTH)
		->setIcon(11, 2)
		->setDescriptionId("clock");
		
	Item::leggings_cloth = NEW_ITEM(ITEM_LEGGINGS_CLOTH)
		->setIcon(5, 7)
		->setDescriptionId("clock");
		
	Item::boots_cloth = NEW_ITEM(ITEM_BOOTS_CLOTH)
		->setIcon(3, 1)
		->setDescriptionId("clock");
		
	Item::helmet_iron = NEW_ITEM(ITEM_HELMET_IRON)
		->setIcon(7, 6)
		->setDescriptionId("clock");
		
	Item::chestplate_iron = NEW_ITEM(ITEM_CHESTPLATE_IRON)
		->setIcon(13, 2)
		->setDescriptionId("clock");
		
	Item::leggings_iron = NEW_ITEM(ITEM_LEGGINGS_IRON)
		->setIcon(7, 7)
		->setDescriptionId("clock");
		
	Item::boots_iron = NEW_ITEM(ITEM_BOOTS_IRON)
		->setIcon(5, 1)
		->setDescriptionId("clock");
		
	Item::helmet_diamond = NEW_ITEM(ITEM_HELMET_EMERALD)
		->setIcon(9, 6)
		->setDescriptionId("clock");
		
	Item::chestplate_diamond = NEW_ITEM(ITEM_CHESTPLATE_EMERALD)
		->setIcon(15, 2)
		->setDescriptionId("clock");
		
	Item::leggings_diamond = NEW_ITEM(ITEM_LEGGINGS_EMERALD)
		->setIcon(9, 7)
		->setDescriptionId("clock");
		
	Item::boots_diamond = NEW_ITEM(ITEM_BOOTS_EMERALD)
		->setIcon(7, 1)
		->setDescriptionId("clock");
		
	Item::helmet_gold = NEW_ITEM(ITEM_HELMET_GOLD)
		->setIcon(8, 6)
		->setDescriptionId("clock");
		
	Item::chestplate_gold = NEW_ITEM(ITEM_CHESTPLATE_GOLD)
		->setIcon(14, 2)
		->setDescriptionId("clock");
		
	Item::leggings_gold = NEW_ITEM(ITEM_LEGGINGS_GOLD)
		->setIcon(8, 7)
		->setDescriptionId("clock");
		
	Item::boots_gold = NEW_ITEM(ITEM_BOOTS_GOLD)
		->setIcon(6, 1)
		->setDescriptionId("clock");
		
	Item::painting = NEW_ITEM(ITEM_PAINTING)
		->setIcon(10, 8)
		->setDescriptionId("clock");
		
	Item::apple_gold = NEW_ITEM(ITEM_APPLE_GOLD)
		->setIcon(1, 0)
		->setDescriptionId("clock");
		
	Item::sign = NEW_ITEM(ITEM_SIGN)
		->setIcon(9, 11)
		->setDescriptionId("clock");
		
	Item::bucket_empty = NEW_ITEM(ITEM_BUCKET)
		->setIcon(0, 2)
		->setDescriptionId("clock");
		
	Item::bucket_water = NEW_X_ITEM(TilePlanterItem, ITEM_BUCKET_WATER, TILE_WATER) 
		->setIcon(2, 2)
		->setDescriptionId("bucketOfWater");
		
	Item::bucket_lava = NEW_X_ITEM(TilePlanterItem, ITEM_BUCKET_LAVA, TILE_LAVA) 
		->setIcon(3, 2)
		->setDescriptionId("bucketOfLava");
		
	Item::minecart = NEW_ITEM(ITEM_MINECART)
		->setIcon(2, 8)
		->setDescriptionId("clock");
		
	Item::saddle = NEW_ITEM(ITEM_SADDLE)
		->setIcon(14, 10)
		->setDescriptionId("clock");
		
	Item::redStone = NEW_ITEM(ITEM_REDSTONE)
		->setIcon(9, 10)
		->setDescriptionId("clock");
		
	Item::snowBall = NEW_ITEM(ITEM_SNOWBALL)
		->setIcon(0, 12)
		->setDescriptionId("clock");
		
	Item::boat = NEW_ITEM(ITEM_BOAT)
		->setIcon(13, 0)
		->setDescriptionId("clock");
		
	Item::milk = NEW_ITEM(ITEM_BUCKET_MILK)
		->setIcon(1, 2)
		->setDescriptionId("clock");
		
	Item::minecart_chest = NEW_ITEM(ITEM_MINECART_CHEST)
		->setIcon(15, 7)
		->setDescriptionId("clock");
		
	Item::minecart_furnace = NEW_ITEM(ITEM_MINECART_FURNACE)
		->setIcon(0, 8)
		->setDescriptionId("clock");
		
	Item::fishingRod = NEW_ITEM(ITEM_FISHING_ROD)
		->setIcon(8, 5)
		->setDescriptionId("clock");
		
	Item::dye_powder = (new DyePowderItem(ITEM_DYE_POWDER))
		->setIcon(11, 3)
		->setDescriptionId("dye_powder");
		
	Item::yellowDust = NEW_ITEM(ITEM_YELLOW_DUST)
		->setIcon(0, 6)
		->setDescriptionId("yellowDust");
		
	Item::fish_raw = NEW_ITEM(ITEM_FISH_RAW)
		->setIcon(11, 5)
		->setDescriptionId("clock");
		
	Item::fish_cooked = NEW_ITEM(ITEM_FISH_COOKED)
		->setIcon(10, 5)
		->setDescriptionId("clock");
		
	Item::cake = NEW_ITEM(ITEM_CAKE)
		->setIcon(4, 2)
		->setDescriptionId("clock");
		
	Item::bed = NEW_ITEM(ITEM_BED)
		->setIcon(8, 0)
		->setDescriptionId("clock");
		
	Item::diode = NEW_ITEM(ITEM_DIODE)
		->setIcon(11, 10)
		->setDescriptionId("clock");
		
	Item::record_01 = NEW_ITEM(ITEM_RECORD_01)
		->setIcon(0, 10)
		->setDescriptionId("clock");
		
	Item::record_02 = NEW_ITEM(ITEM_RECORD_02)
		->setIcon(1, 10)
		->setDescriptionId("clock");
}

int Item::getIcon(const ItemInstance* pInstance) const
{
	return m_icon;
}

bool Item::useOn(ItemInstance* instance, Level* level, const TilePos& pos, Facing::Name face)
{
	return false;
}

bool Item::useOn(ItemInstance* instance, Player* player, Level* level, const TilePos& pos, Facing::Name face)
{
	return false;
}

float Item::getDestroySpeed(ItemInstance* instance, Tile* tile)
{
	return 1.0f;
}

ItemInstance* Item::use(ItemInstance* instance, Level* level, Player* player)
{
	return instance;
}

int Item::getMaxStackSize()
{
	return m_maxStackSize;
}

int Item::getLevelDataForAuxValue(int x)
{
	return 0;
}

bool Item::isStackedByData()
{
	return m_bStackedByData;
}

int Item::getMaxDamage()
{
	return m_maxDamage;
}

void Item::hurtEnemy(ItemInstance* instance, Mob* mob)
{

}

void Item::mineBlock(ItemInstance* instance, const TilePos& pos, Facing::Name face)
{

}

int Item::getAttackDamage(Entity* ent)
{
	return 1;
}

bool Item::canDestroySpecial(Tile* tile)
{
	return false;
}

void Item::interactEnemy(ItemInstance* instance, Mob* mob)
{

}

bool Item::isHandEquipped()
{
	return m_bHandEquipped;
}

bool Item::isMirroredArt()
{
	return false;
}

std::string Item::getDescription()
{
	return m_DescriptionID;
}

std::string Item::getDescription(ItemInstance* inst)
{
	return m_DescriptionID;
}

std::string Item::getDescriptionId()
{
	return m_DescriptionID;
}

std::string Item::getDescriptionId(ItemInstance* inst)
{
	return m_DescriptionID;
}

Item* Item::getCraftingRemainingItem()
{
	return m_pCraftingRemainingItem;
}

bool Item::hasCraftingRemainingItem()
{
	return m_pCraftingRemainingItem != 0;
}

std::string Item::getName()
{
	return getDescriptionId() + ".name";
}

int Item::buildIdAux(int16_t auxValue, const CompoundTag* userData)
{
	return auxValue | (unsigned int)(m_itemID << 16);
}

Item
	*Item::shovel_iron,
	*Item::pickAxe_iron,
	*Item::hatchet_iron,
	*Item::flintAndSteel,
	*Item::apple,
	*Item::bow,
	*Item::arrow,
	*Item::coal,
	*Item::emerald,
	*Item::ironIngot,
	*Item::goldIngot,
	*Item::sword_iron,
	*Item::sword_wood,
	*Item::shovel_wood,
	*Item::pickAxe_wood,
	*Item::hatchet_wood,
	*Item::sword_stone,
	*Item::shovel_stone,
	*Item::pickAxe_stone,
	*Item::hatchet_stone,
	*Item::sword_emerald,
	*Item::shovel_emerald,
	*Item::pickAxe_emerald,
	*Item::hatchet_emerald,
	*Item::stick,
	*Item::bowl,
	*Item::mushroomStew,
	*Item::sword_gold,
	*Item::shovel_gold,
	*Item::pickAxe_gold,
	*Item::hatchet_gold,
	*Item::string,
	*Item::feather,
	*Item::sulphur,
	*Item::hoe_wood,
	*Item::hoe_stone,
	*Item::hoe_iron,
	*Item::hoe_emerald,
	*Item::hoe_gold,
	*Item::seeds,
	*Item::wheat,
	*Item::bread,
	*Item::helmet_cloth,
	*Item::chestplate_cloth,
	*Item::leggings_cloth,
	*Item::boots_cloth,
	*Item::helmet_iron,
	*Item::chestplate_iron,
	*Item::leggings_iron,
	*Item::boots_iron,
	*Item::helmet_diamond,
	*Item::chestplate_diamond,
	*Item::leggings_diamond,
	*Item::boots_diamond,
	*Item::helmet_gold,
	*Item::chestplate_gold,
	*Item::leggings_gold,
	*Item::boots_gold,
	*Item::flint,
	*Item::porkChop_raw,
	*Item::porkChop_cooked,
	*Item::painting,
	*Item::apple_gold,
	*Item::sign,
	*Item::door_wood,
	*Item::bucket_empty,
	*Item::bucket_water,
	*Item::bucket_lava,
	*Item::minecart,
	*Item::saddle,
	*Item::door_iron,
	*Item::redStone,
	*Item::snowBall,
	*Item::boat,
	*Item::leather,
	*Item::milk,
	*Item::brick,
	*Item::clay,
	*Item::reeds,
	*Item::paper,
	*Item::book,
	*Item::slimeBall,
	*Item::minecart_chest,
	*Item::minecart_furnace,
	*Item::egg,
	*Item::compass,
	*Item::fishingRod,
	*Item::clock,
	*Item::yellowDust,
	*Item::fish_raw,
	*Item::fish_cooked,
	*Item::dye_powder,
	*Item::bone,
	*Item::sugar,
	*Item::cake,
	*Item::bed,
	*Item::diode,
	*Item::cookie,
	*Item::record_01,
	*Item::record_02,
	*Item::camera,
	*Item::rocket,
	*Item::quiver;

Item::Tier
	Item::Tier::WOOD   (0, 59,   2.0f,  0),
	Item::Tier::STONE  (1, 131,  4.0f,  1),
	Item::Tier::IRON   (2, 250,  6.0f,  2),
	Item::Tier::EMERALD(3, 1561, 8.0f,  3),
	Item::Tier::GOLD   (0, 32,   12.0f, 0);

std::string Item::ICON_DESCRIPTION_PREFIX = "item.";
