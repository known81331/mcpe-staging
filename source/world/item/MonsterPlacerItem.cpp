/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "MonsterPlacerItem.hpp"
#include "world/level/Level.hpp"
#include "world/entity/TripodCamera.hpp"
#include "world/entity/Pig.hpp"
#include "world/entity/Chicken.hpp"
#include "world/entity/Cow.hpp"
#include "world/entity/Sheep.hpp"
#include "world/entity/Player.hpp"
#include "world/entity/Creeper.hpp"
#include "world/entity/Skeleton.hpp"
#include "world/entity/Spider.hpp"
#include "world/entity/Zombie.hpp"

MonsterPlacerItem::MonsterPlacerItem(int id) : Item(id)
{
}


std::string MonsterPlacerItem::getDescriptionId(ItemInstance* item)
{
	return Item::getDescriptionId(item);
}

int MonsterPlacerItem::getIcon(const ItemInstance* item) const
{
	int id = item->getAuxValue();
	return (id >= 0 && id <= 15) ? m_icon + id : m_icon;
}

ItemInstance* MonsterPlacerItem::use(ItemInstance* inst, Level* level, Player* player)
{
	/*
#ifndef ORIGINAL_CODE
	// prevent players from using this in multiplayer, to prevent a desync of entity IDs
	if (level->m_bIsClientSide)
		return inst;
#endif

	Mob* entity = new Pig(level);
	entity->setPos(player->m_pos);
	level->addEntity(entity);

 	entity = new Chicken(level);
	entity->setPos(player->m_pos);
	level->addEntity(entity);

	entity = new Cow(level);
	entity->setPos(player->m_pos);
	level->addEntity(entity);
	*/

	return inst;
}


bool MonsterPlacerItem::useOn(ItemInstance* instance, Player* player, Level* level, const TilePos& pos, Facing::Name face)
{
	// prevent players from using this in multiplayer, to prevent a desync of entity IDs
	if (level->m_bIsClientSide)
		return false;

	TilePos placePos = pos;
	if (face != Facing::DOWN && face != Facing::UP)
		placePos = placePos.above();
	else if (face == Facing::UP)
		placePos = placePos.above();
	else
		placePos = placePos.below();

	int id = instance->getAuxValue();
	Mob* entity = nullptr;

	switch (id)
	{
		case 0: entity = new Chicken(level); break;
		case 1: entity = new Cow(level); break;
		case 2: entity = new Pig(level); break;
		case 3: entity = new Sheep(level); break;
	//	case 4: entity = new Wolf(level); break;
	//	case 5: entity = new MushroomCow(level); break;
		case 6: entity = new Creeper(level); break;
	//	case 7: entity = new Enderman(level); break;
	//	case 8: entity = new Silverfish(level); break;
		case 9: entity = new Skeleton(level); break;
	//	case 10: entity = new Slime(level); break;
		case 11: entity = new Spider(level); break;
		case 12: entity = new Zombie(level); break;
	//	case 13: entity = new Pigman(level); break;
	//	case 14: entity = new Villager(level); break;
		default: return false;
	}

	if (entity != nullptr)
	{
		entity->setPos(Vec3(placePos.x + 0.5f, placePos.y, placePos.z + 0.5f));
		level->addEntity(entity);

		if (!player->isCreative())
			instance->m_count--;
		
		return true;
	}

	return false;
}