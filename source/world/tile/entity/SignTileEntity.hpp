#pragma once

#include <memory>
#include <string>
#include "TileEntity.hpp"
#include "world/level/Level.hpp"

class SignTileEntity : public TileEntity {
public:
    SignTileEntity();
    ~SignTileEntity();

    void load(CompoundTag tag) override;
    void save(CompoundTag tag) override;
    Packet* getUpdatePacket() override;

public:
    std::string m_messages[4];
    int m_selectedLine;
};