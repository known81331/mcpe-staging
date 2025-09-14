
#include "MobSpawner.hpp"
#include "world/entity/MobFactory.hpp"

void MobSpawner::tick(Level *level, bool allowHostile, bool allowFriendly) {
    if (!allowHostile && !allowFriendly)
        return;

    chunksToPoll.clear();

    for (auto& player : level->m_players)
    {
        int cx = Mth::floor(player->m_pos.x / 16.0f);
        int cz = Mth::floor(player->m_pos.z / 16.0f);

        for (int dx = -8; dx <= 8; ++dx) {
            for (int dz = -8; dz <= 8; ++dz) {
                chunksToPoll.insert(std::make_pair(cx + dx, cz + dz));
            }
        }
    }

    int totalSpawned = 0;

    for (int i = 0; i < MobCategory::numValues; i++)
    {
        MobCategory category = ((MobCategory*)&(MobCategory::monster))[i];

        if ((!category.isFriendly() || allowFriendly) && (category.isFriendly() || allowHostile) 
            && level->getEntityCountOfCategory(category.getBaseType().getCategoryMask()) <= (category.getMaxInstancesPerChunk() * (int)chunksToPoll.size() / 256))
        {    
            for (const auto& ___pos : chunksToPoll) {
                ChunkPos pos(___pos.first, ___pos.second);

                Biome* biome = level->getBiomeSource()->getBiome(pos);
                auto spawnList = biome->getMobs(&category);
               


                if (spawnList.empty()) continue;

                EntityType::ID type = (EntityType::ID)(spawnList.begin()->first);

                int spawnWeight = 0;

                for (auto it = spawnList.begin(); it != spawnList.end(); spawnWeight += it->second, ++it)
                {
                }


                int randomRate = level->m_random.nextInt(spawnWeight);

                for (auto it = spawnList.begin(); it != spawnList.end(); ++it)
                {
                    randomRate -= it->second;
                    if (randomRate < 0) {
                        type = (EntityType::ID)(it->first);
                        break;
                    }
                }

               // if (!type->getCategory().contains(EntityCategories::MOB)) continue;

                int idx = level->m_random.nextInt((int)spawnList.size());
                TilePos tpos = getRandomPosWithin(level, pos.x * 16, pos.z * 16);

                if (level->isSolidTile(tpos)) continue;
              
                if (level->getMaterial(tpos) != category.getSpawnPositionMaterial()) continue;

                int spawned = 0;
                for (int i = 0; i < 3; ++i)
                {
                    TilePos tp(tpos);

                    if (spawned == -1)
                        break;

                    for (int j = 0; j < 4; ++j) {
                        tp.x += level->m_random.nextInt(6) - level->m_random.nextInt(6);
                        tp.y += level->m_random.nextInt(1) - level->m_random.nextInt(1);
                        tp.z += level->m_random.nextInt(6) - level->m_random.nextInt(6);

                        if (isSpawnPositionOk(&category, level, tp)) {
                            Vec3 pPos(tp.x + 0.5, tp.y, tp.z + 0.5);

                            if (!level->getNearestPlayer(pPos, 24.0f, false)) {
                                Vec3 dPos = pPos - level->getSharedSpawnPos();
                                if (dPos.lengthSqr() >= 576.0f) {

                                    
                                    auto entity = MobFactory::CreateMob(type, level);
                                    if (!entity) break;
                                    Mob *mob = (Mob*)(entity);

                                    mob->moveTo(pPos, Vec2(level->m_random.nextFloat() * 360.0f, 0.0f));
                                    if (mob->canSpawn()) {
                                        ++spawned;
                                        level->addEntity(mob);
                                        finalizeMobSettings(mob, level, pPos);
                                        if (spawned >= mob->getMaxSpawnClusterSize())
                                        {
                                            totalSpawned += spawned;
                                            spawned = -1;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (spawned != -1)
                    totalSpawned += spawned;
            }
        }
    }

    return; // totalSpawned;
}

TilePos MobSpawner::getRandomPosWithin(Level *level, int chunkX, int chunkZ) {
    int px = chunkX + level->m_random.nextInt(16);
    int py = level->m_random.nextInt(128);
    int pz = chunkZ + level->m_random.nextInt(16);
    return TilePos(px, py, pz);
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
    if (!level->isEmptyTile(pos)) 
        return false;

    if (category->getSpawnPositionMaterial() == Material::water) 
        return level->getMaterial(pos)->isLiquid() && !level->isSolidTile(pos.above());

    return level->isSolidTile(pos.below()) && !level->isSolidTile(pos) && !level->getMaterial(pos)->isLiquid() && !level->isSolidTile(pos.above());
}

void MobSpawner::finalizeMobSettings(Mob *mob, Level *level, const Vec3& pos) {
    if (!level || !mob)
        return;

    mob->finalizeMobSpawn();
    makeBabyMob(mob, level);
}


void MobSpawner::makeBabyMob(Mob *mob, Level *level) {
    level->m_random.setSeed(0x5deea8f);

    if (mob->isBaby())
        return;

    // todo
}


void MobSpawner::postProcessSpawnMobs(Level *level, Biome *biome, const Vec3& pos) {

}