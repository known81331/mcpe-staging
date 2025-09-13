
#include "MobSpawner.hpp"

void MobSpawner::tick(Level *level, bool allowHostile, bool allowFriendly) {
   
}

TilePos MobSpawner::getRandomPosWithin(Level *level, int chunkX, int chunkZ) {
    return TilePos();
}

//todo: bool?
int MobSpawner::addMob(Level *level, Mob *mob, const Vec3& pos, const Vec2& rot) {
    if (!level || !mob)
        return 0;

    if (!mob->canSpawn() || !mob->isAlive())
        return 0;

    mob->moveTo(pos, rot);
    level->addEntity(mob);
    finalizeMobSettings(mob, level, pos);

    return 1;
}

bool MobSpawner::isSpawnPositionOk(MobCategory *category, Level *level, const TilePos& pos) {
    return false;
}

void MobSpawner::finalizeMobSettings(Mob *mob, Level *level, const Vec3& pos) {
    
}


void MobSpawner::makeBabyMob(Mob *mob, float param_2) {



}


void MobSpawner::postProcessSpawnMobs(Level *level, Biome *biome, const Vec3& pos) {

}