/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "WorkbenchTile.hpp"
#include "world/level/Level.hpp"
#include "client/app/Minecraft.hpp"

WorkbenchTile::WorkbenchTile(int a, int b, Material* c) : Tile(a, b, c)
{
}

int WorkbenchTile::getTexture(Facing::Name face) const
{
	switch (face)
	{
	case Facing::NORTH:
	case Facing::SOUTH:	
		return TEXTURE_WORKBENCH_SIDE_1;
	case Facing::WEST:
	case Facing::EAST:
		return TEXTURE_WORKBENCH_SIDE_2;
	case Facing::UP:
		return TEXTURE_WORKBENCH_TOP;
	default:
		return TEXTURE_PLANKS;
	}

	return m_TextureFrame;
}

int WorkbenchTile::getResource(int data, Random* random) const
{
	return 0; // would be Book
}

int WorkbenchTile::getResourceCount(Random* random) const
{
	return 1;
}


int WorkbenchTile::use(Level* level, const TilePos& pos, Player* player)
{
	if (player->isSneaking() && player->getSelectedItem())
	{
		return false;
	}
	if (level->m_bIsOnline) 
	{
		return true;
	}
	else 
	{
		player->startCrafting(pos);
		return true;
	}
}
