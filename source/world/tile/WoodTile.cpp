/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "WoodTile.hpp"
#include "world/level/Level.hpp"

WoodTile::WoodTile(int id, int type) : Tile(id, TEXTURE_PLANKS, Material::wood)
{

}

int WoodTile::getTexture(Facing::Name face) const
{
	return getTexture(face, field_6C);
}


int WoodTile::getTexture(Facing::Name face, TileData data) const
{
	return getTexture(face, (int)data);
}

int WoodTile::getTexture(Facing::Name face, int data) const
{
	switch (data)
	{
		case 1:
			return TEXTURE_PLANKS_SPRUCE;
		case 2:
			return TEXTURE_PLANKS_BIRCH;
		case 3:
			return TEXTURE_PLANKS_JUNGLE;
		case 4:
			return TEXTURE_PLANKS_ACACIA;
		case 5:
			return TEXTURE_PLANKS_DARK_OAK;
	}
	return m_TextureFrame;
}

int WoodTile::getSpawnResourcesAuxValue(int val) const
{
	return val;
}
