/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "FurnaceTile.hpp"
#include "world/level/Level.hpp"

FurnaceTile::FurnaceTile(int a, int b, Material* c) : Tile(a, b, c)
{
}

int FurnaceTile::getTexture(Facing::Name face, int data) const
{

	int doorDir = 5;

	if (doorDir == face)
		return TEXTURE_FURNACE_FRONT;


	switch (face)
	{
	case Facing::NORTH:
	case Facing::WEST:
	case Facing::SOUTH:
	case Facing::EAST:	
		return TEXTURE_FURNACE_SIDE;
	case Facing::UP:
	default:
		return TEXTURE_FURNACE_TOP;
	}

	return m_TextureFrame;
}


int FurnaceTile::getTexture(Facing::Name face) const
{

	switch (face)
	{
	case Facing::NORTH:
	case Facing::WEST:
	case Facing::SOUTH:
		return TEXTURE_FURNACE_SIDE;
	case Facing::EAST:	
		return TEXTURE_FURNACE_FRONT;
	case Facing::UP:
	default:
		return TEXTURE_FURNACE_TOP;
	}

	return m_TextureFrame;
}


int FurnaceTile::getResource(int data, Random* random) const
{
	return 0; // would be Book
}

int FurnaceTile::getResourceCount(Random* random) const
{
	return 1;
}


int FurnaceTile::use(Level* level, const TilePos& pos, Player* player)
{
	if (player) {
		
	}


}
