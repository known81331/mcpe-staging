/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "CactusTile.hpp"
#include "world/level/Level.hpp"
#include "world/entity/FallingTile.hpp"

CactusTile::CactusTile(int a, int b, Material* c) : Tile(a, b, c)
{
	setShape(0.125, 0, 0.125, 0.875, 0.9375f, 0.875);
	setTicking(true);
}

int CactusTile::getRenderShape() const
{
	return SHAPE_CACTUS;
}

AABB* CactusTile::getAABB(const Level* lvl, const TilePos& pos)
{
	return Tile::getAABB(lvl, pos); //&m_aabb;
}

bool CactusTile::isCubeShaped() const
{
	return false;
}

bool CactusTile::isSolidRender() const
{
	return false;
}

int CactusTile::getResource(int x, Random* random) const
{
	return m_ID;
}

int CactusTile::getResourceCount(Random* random) const
{
	return 1;
}


int CactusTile::getTexture(Facing::Name face, int data) const
{
	if (face == Facing::UP)
		return TEXTURE_CACTUS_TOP;
	if (face == Facing::DOWN)
		return TEXTURE_CACTUS_BOTTOM;

	return TEXTURE_CACTUS_SIDE;
}
	


bool CactusTile::isFree(Level* level, const TilePos& pos)
{
	return false;
}


bool CactusTile::mayPlace(const Level* level, const TilePos& pos) const
{

	if (level->getTile(pos.relative(Facing::NORTH)) || level->getMaterial(pos.relative(Facing::NORTH))->isSolid())
		return false;
	if (level->getTile(pos.relative(Facing::SOUTH)) || level->getMaterial(pos.relative(Facing::SOUTH))->isSolid())
		return false;
	if (level->getTile(pos.relative(Facing::EAST)) || level->getMaterial(pos.relative(Facing::EAST))->isSolid())
		return false;
	if (level->getTile(pos.relative(Facing::WEST)) || level->getMaterial(pos.relative(Facing::WEST))->isSolid())
		return false;

	TileID tile = level->getTile(pos.below());

	return Tile::mayPlace(level, pos) && (tile == Tile::sand->m_ID || tile == m_ID);
}

bool CactusTile::checkCanSurvive(Level* level, const TilePos& pos)
{

	if (level->getTile(pos.relative(Facing::NORTH)) || level->getMaterial(pos.relative(Facing::NORTH))->isSolid())
		return false;
	if (level->getTile(pos.relative(Facing::SOUTH)) || level->getMaterial(pos.relative(Facing::SOUTH))->isSolid())
		return false;
	if (level->getTile(pos.relative(Facing::EAST)) || level->getMaterial(pos.relative(Facing::EAST))->isSolid())
		return false;
	if (level->getTile(pos.relative(Facing::WEST)) || level->getMaterial(pos.relative(Facing::WEST))->isSolid())
		return false;

	TileID tile = level->getTile(pos.below());

	return (tile == Tile::sand->m_ID || tile == m_ID);
}

void CactusTile::neighborChanged(Level* level, const TilePos& pos, TileID tile)
{
	if (!checkCanSurvive(level, pos)) {
		spawnResources(level, pos, level->getData(pos));
		level->setTile(pos, TILE_AIR);
	}
}

bool CactusTile::shouldRenderFace(const LevelSource* level, const TilePos& pos, Facing::Name face) const
{
	if (face == Facing::UP)
		return true;

	if (level->getMaterial(pos) == m_pMaterial)
		return false;

	return Tile::shouldRenderFace(level, pos, face);
}

void CactusTile::tick(Level* level, const TilePos& pos, Random* random)
{
	checkCanSurvive(level, pos);
	if (level->getBrightness(LightLayer::Block, pos) > 11)
	{
		spawnResources(level, pos, level->getData(pos));
		level->setTile(pos, TILE_AIR);
	}
}
