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
	setShape(0, 0, 0, 1, 0.05f, 1);
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
	return 1;
}

int CarpetTile::getResourceCount(Random* random) const
{
	return 1;
}


int CarpetTile::getTexture(Facing::Name face) const
{
	return getTexture(face, 0);
}


int CarpetTile::getTexture(Facing::Name face, TileData data) const
{
	return m_TextureFrame + data;
}
int CarpetTile::getTexture(Facing::Name face, int data) const
{
	return m_TextureFrame + data;
}

bool CarpetTile::mayPlace(const Level* level, const TilePos& pos) const
{
	TileID tile = level->getTile(pos.below());

	if ((tile == Tile::carpet->m_ID) || (tile == Tile::fence->m_ID))
		return true;
		
	if (!tile || ( !Tile::tiles[tile]->isSolidRender() ) )
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
