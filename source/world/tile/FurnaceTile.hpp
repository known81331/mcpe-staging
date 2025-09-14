/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp

	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include "Tile.hpp"

class FurnaceTile : public Tile
{
public:
	FurnaceTile(int ID, int texture, Material*);

	int use(Level*, const TilePos& pos, Player*) override;
	
	int getTexture(Facing::Name face) const override;
	int getTexture(Facing::Name face, int data) const override;
	int getResource(int data, Random* random) const override;
	int getResourceCount(Random* random) const override;
	virtual void setPlacedBy(Level*, const TilePos& pos, Mob*) override;
};
