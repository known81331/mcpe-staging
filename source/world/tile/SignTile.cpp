#include "SignTile.hpp"
#include "world/level/Level.hpp"
#include "entity/SignTileEntity.hpp"

SignTile::SignTile(int id, bool isWall) : Tile(id, TEXTURE_PLANKS, Material::wood)
{
	m_bIsWall = isWall;
	setShape(0.25F, 0.0F, 0.25F, 0.75F, 1.0F, 0.75F);
}

void SignTile::neighborChanged(Level* level, const TilePos& pos, TileID tile)
{
	bool var6 = false;
	if (!m_bIsWall) {
		if (!level->getMaterial(pos.below())->isSolid()) {
			var6 = true;
		}
	}
	else {
		int var7 = level->getData(pos);
		var6 = true;
		if (var7 == 2 && level->getMaterial(pos.south())->isSolid())
			var6 = false;

		if (var7 == 3 && level->getMaterial(pos.north())->isSolid())
			var6 = false;

		if (var7 == 4 && level->getMaterial(pos.east())->isSolid())
			var6 = false;

		if (var7 == 5 && level->getMaterial(pos.west())->isSolid())
			var6 = false;
	}

	if (var6) {
		spawnResources(level, pos, level->getData(pos));
		level->setTile(pos, TILE_AIR);
	}

	Tile::neighborChanged(level, pos, tile);
}

bool SignTile::isSolidRender() const
{
	return false;
}

bool SignTile::isCubeShaped() const
{
	return false;
}

AABB* SignTile::getAABB(const Level* level, const TilePos& pos)
{
	return nullptr;
}

int SignTile::getRenderShape() const
{
	return -1;
}

bool SignTile::hasTileEntity() const
{
	return true;
}
