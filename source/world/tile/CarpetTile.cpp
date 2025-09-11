/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "CarpetTile.hpp"
#include "world/level/Level.hpp"
#include "world/entity/FallingTile.hpp"

CarpetTile::CarpetTile(int a, int b, Material* c) : Tile(a, b, c)
{
	setShape(0, 0, 0, 1, 0.1f, 1);
	setTicking(true);
}

AABB* CarpetTile::getAABB(const Level*, const TilePos& pos)
{
	return nullptr;
}

bool CarpetTile::isCubeShaped() const
{
	return false;
}

bool CarpetTile::isSolidRender() const
{
	return false;
}

int CarpetTile::getResource(int x, Random* random) const
{
	return 0;
}

int CarpetTile::getResourceCount(Random* random) const
{
	return 0;
}

/*
int CarpetTile::getTexture(Facing::Name face, int data) const
{
	return m_TextureFrame + ((field_6C > 0) ? field_6C : data);
}
*/

bool CarpetTile::isFree(Level* level, const TilePos& pos)
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


bool CarpetTile::mayPlace(const Level* level, const TilePos& pos) const
{
	TileID tile = level->getTile(pos.below());

	if (!tile || !Tile::tiles[tile]->isSolidRender())
		return false;

	return level->getMaterial(pos.below())->blocksMotion();
}

bool CarpetTile::checkCanSurvive(Level* level, const TilePos& pos)
{
	if (mayPlace(level, pos))
		return true;

	spawnResources(level, pos, level->getData(pos));
	level->setTile(pos, TILE_AIR);
	return false;
}

void CarpetTile::neighborChanged(Level* level, const TilePos& pos, TileID tile)
{
	checkCanSurvive(level, pos);
}

bool CarpetTile::shouldRenderFace(const LevelSource* level, const TilePos& pos, Facing::Name face) const
{
	if (face == Facing::UP)
		return true;

	if (level->getMaterial(pos) == m_pMaterial)
		return false;

	return Tile::shouldRenderFace(level, pos, face);
}

void CarpetTile::tick(Level* level, const TilePos& pos, Random* random)
{
	if (level->getBrightness(LightLayer::Block, pos) > 11)
	{
		spawnResources(level, pos, level->getData(pos));
		level->setTile(pos, TILE_AIR);
	}
}
