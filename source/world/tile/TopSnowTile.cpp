/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "TopSnowTile.hpp"
#include "world/level/Level.hpp"
#include "world/entity/FallingTile.hpp"

TopSnowTile::TopSnowTile(int a, int b, Material* c) : Tile(a, b, c)
{
	setShape(0, 0, 0, 1, 0.125f, 1);
	setTicking(true);
}

AABB* TopSnowTile::getAABB(const Level*, const TilePos& pos)
{
	return nullptr;
}

bool TopSnowTile::isCubeShaped() const
{
	return false;
}

bool TopSnowTile::isSolidRender() const
{
	return false;
}

int TopSnowTile::getResource(int x, Random* random) const
{
	return 0;
}

int TopSnowTile::getResourceCount(Random* random) const
{
	return 0;
}


bool TopSnowTile::isFree(Level* level, const TilePos& pos)
{
	TileID tile = level->getTile(pos);
	if (!tile)
		return true;

	if (tile == Tile::fire->m_ID)
		return true;

	if (Tile::tiles[tile]->m_pMaterial == Material::water)
		return true;

	if (Tile::tiles[tile]->m_pMaterial == Material::lava)
		return true;

	return false;
}



void TopSnowTile::checkSlide(Level* level, const TilePos& pos)
{
	//TileID tile = level->getTile(pos.below());

	if (!isFree(level, pos.below()))
		// standing on something, don't fall
		return;

	if (pos.y <= 0)
		return;

	if (!level->hasChunksAt(TilePos(pos.x - 32, pos.y - 32, pos.z - 32), TilePos(pos.x + 32, pos.y + 32, pos.z + 32)))
	{
		level->setTile(pos, 0);

		int y2;
		for (y2 = pos.y - 1; y2 >= 0; y2--)
		{
			if (!isFree(level, TilePos(pos.x, y2, pos.z)))
				break;
		}

		if (y2 > -1)
			level->setTile(TilePos(pos.x, y2 + 1, pos.z), m_ID);
	}
	else
	{
		// The original code attempts to spawn a falling tile entity, but it fails since it's not a player.
		// The falling sand tile
#if defined(ORIGINAL_CODE) || defined(ENH_ALLOW_SAND_GRAVITY)
		level->addEntity(new FallingTile(level, Vec3(float(pos.x) + 0.5f, float(pos.y) + 0.5f, float(pos.z) + 0.5f), m_ID));
#endif
	}
}


bool TopSnowTile::mayPlace(const Level* level, const TilePos& pos) const
{
	TileID tile = level->getTile(pos.below());

	if (!tile || !Tile::tiles[tile]->isSolidRender())
		return false;

	return level->getMaterial(pos.below())->blocksMotion();
}

bool TopSnowTile::checkCanSurvive(Level* level, const TilePos& pos)
{
	if (mayPlace(level, pos))
		return true;

	spawnResources(level, pos, level->getData(pos));
	level->setTile(pos, TILE_AIR);
	return false;
}

void TopSnowTile::neighborChanged(Level* level, const TilePos& pos, TileID tile)
{
	checkSlide(level, pos);
	checkCanSurvive(level, pos);
}

bool TopSnowTile::shouldRenderFace(const LevelSource* level, const TilePos& pos, Facing::Name face) const
{
	if (face == Facing::UP)
		return true;

	if (level->getMaterial(pos) == m_pMaterial)
		return false;

	return Tile::shouldRenderFace(level, pos, face);
}

void TopSnowTile::tick(Level* level, const TilePos& pos, Random* random)
{
	if (level->getBrightness(LightLayer::Block, pos) > 11)
	{
		spawnResources(level, pos, level->getData(pos));
		level->setTile(pos, TILE_AIR);
	}
}
