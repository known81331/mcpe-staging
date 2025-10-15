/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include <unordered_map>
#include <string>
#include "common/Utils.hpp"
#include "world/level/levelgen/synth/PerlinNoise.hpp"
#include "world/level/levelgen/feature/Feature.hpp"
#include "world/entity/EntityType.hpp"
#include "world/entity/MobCategory.hpp"

class Biome
{
public: // Static Functions
	static Biome* getBiome(float hum, float temp);
	static void initBiomes();

public: // Virtual functions
	virtual float adjustDepth(float depth);
	virtual float adjustScale(float scale);
	virtual int getSkyColor(float x);
	virtual Feature* getTreeFeature(Random*);
	virtual std::unordered_map<uint32_t, int> getMobs(MobCategory*);

public: // Instance Functions
	Biome();
	virtual ~Biome();
	Biome* setColor(int color);
	Biome* setLeafColor(int color);
	Biome* setName(const std::string& name);
	Biome* setSnowCovered();

public: // Static Variables
	static Biome
		* rainForest,
		* swampland,
		* seasonalForest,
		* forest,
		* savanna,
		* shrubland,
		* taiga,
		* desert,
		* plains,
		* iceDesert,
		* tundra,

		// pe 0.9
		* jungles,
		* mesa,
		* mushroomIslands,
		* megaTaiga,
		* megaSpruceTaiga,
		* deepOcean
		;
	static Biome* map[4096];

private: // Private Functions
	static Biome* _getBiome(float hum, float temp);
	static void recalc();

	static std::unordered_map<uint32_t, int> monsterList;
	static std::unordered_map<uint32_t, int> creatureList;
	static std::unordered_map<uint32_t, int> waterCreatureList;
public: // Instance Variables
	std::string m_name;
	int m_Color;
	TileID field_20;
	TileID field_21;
	int m_LeafColor;
};

class RainforestBiome : public Biome
{
public:
	Feature* getTreeFeature(Random*) override;
};

class SwampBiome : public Biome
{
};

class ForestBiome : public Biome
{
public:
	Feature* getTreeFeature(Random*) override;
};

class TaigaBiome : public Biome
{
public:
	Feature* getTreeFeature(Random*) override;
};

class FlatBiome : public Biome
{
};
