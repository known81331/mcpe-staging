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

	// 5, 4, 3 ,2
	// 4, 5, 3, 2
	Facing::Name facing = Facing::Name((int)(Facing::EAST) - data);

	if (face == facing)
		return TEXTURE_FURNACE_FRONT;

	switch (face)
	{
	case Facing::UP:
	case Facing::DOWN:
		return TEXTURE_FURNACE_TOP;
	}

	return TEXTURE_FURNACE_SIDE;
}


int FurnaceTile::getTexture(Facing::Name face) const
{
	Facing::Name facing = Facing::EAST;

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
	return Tile::furnace->m_ID; // would be Book
}

int FurnaceTile::getResourceCount(Random* random) const
{
	return 1;
}


void FurnaceTile::setPlacedBy(Level* level, const TilePos& pos, Mob* mob)
{
	int rot = Mth::floor(0.5f + (mob->m_rot.x * 4.0f / 360.0f)) & 3;

	int data = ((uint8_t)level->getData(pos)); //0;

	switch (rot)
	{
		case 0: data = 3; break;
		case 1: data = 0; break;
		case 2: data = 2; break;
		default: data = 1; break;
	}

	level->setData(pos, data);
}



int FurnaceTile::use(Level* level, const TilePos& pos, Player* player)
{
	if (player) {
		
	}


}
