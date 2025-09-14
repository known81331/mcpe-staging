/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp

	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include "Tile.hpp"

class CarpetTile : public Tile
{
public:
	CarpetTile(int id, int texture, Material* pMtl);

	bool isCubeShaped() const override;
	bool isSolidRender() const override;
	int getResource(int, Random*) const override;
	int getResourceCount(Random*) const override;
	bool mayPlace(const Level*, const TilePos& pos) const override;
	void neighborChanged(Level*, const TilePos& pos, TileID tile) override;
	bool shouldRenderFace(const LevelSource*, const TilePos& pos, Facing::Name face) const override;

	int getTexture(Facing::Name face) const override;
	int getTexture(Facing::Name face, int data) const override;

	static bool isFree(Level* level, const TilePos& pos);

	bool checkCanSurvive(Level*, const TilePos& pos);
};
