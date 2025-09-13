#pragma once

#include <map>

#include "world/tile/Tile.hpp"
#include "world/entity/Entity.hpp"
#include "world/entity/MobCategory.hpp"
#include "world/level/levelgen/chunk/LevelChunk.hpp"
#include "world/level/levelgen/chunk/ChunkSource.hpp"
#include "world/level/storage/LevelStorageSource.hpp"
#include "world/level/storage/LevelSource.hpp"
#include "world/level/storage/LevelData.hpp"
#include "world/level/path/PathFinder.hpp"
#include "Dimension.hpp"
#include "LevelListener.hpp"
#include "TickNextTickData.hpp"
#include "client/renderer/LightUpdate.hpp"


class MobSpawner {
public:
    static bool isSpawnPositionOk(MobCategory *category, Level *level, const TilePos& pos);
    static void finalizeMobSettings(Mob *mob, Level *level, const Vec3& pos);
    static void makeBabyMob(Mob *mob, float param_2);
    static void postProcessSpawnMobs(Level *level, Biome *biome, const Vec3& pos);
    static int addMob(Level *level, Mob *mob, const Vec3& pos, const Vec2& rot = Vec2::ZERO);

    TilePos getRandomPosWithin(Level *level, int chunkX, int chunkZ);
    void tick(Level *level, bool allowHostile, bool allowFriendly);
private:
    std::map<int, ChunkPos> chunksToPoll;
};