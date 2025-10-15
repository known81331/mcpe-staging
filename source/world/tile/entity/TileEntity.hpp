#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cmath>
#include <nbt/CompoundTag.hpp>
#include <world/level/TilePos.hpp>
#include <functional>

#include "TileEntityType.hpp"

class Tile;
class Level;
class Packet;

class TileEntity
{
public:
    virtual ~TileEntity();

    static std::shared_ptr<TileEntity> loadStatic(CompoundTag tag);

    virtual void load(CompoundTag tag);
    virtual void save(CompoundTag tag);
    virtual void tick() {}

    bool isRemoved() const;
    void setRemoved();
    void clearRemoved();

    virtual Packet* getUpdatePacket() { return nullptr; }

    const TileEntityType* getType() const { return m_pType; }

    virtual int getData() const;
    void setData(int data);
    void setChanged();

    float distanceToSqr(const Vec3& vec) const;

    virtual Tile* getTile() const;

    Level* m_pLevel = nullptr;
    TilePos m_pos;


protected:
    const TileEntityType* m_pType;
    bool m_bRemove = false;

    virtual std::string getId() const;
};