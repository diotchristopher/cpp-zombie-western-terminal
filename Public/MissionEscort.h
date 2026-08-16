#pragma once
#include "../public/Mission.h"
#include "../public/Location.h"
#include "../public/Player.h"
#include "../public/Npc.h"

class MissionEscort : public Mission {
public:
    MissionEscort(Player* player, Location* startLoc, Location* endLoc);
    void start() override;
    void update() override;
    bool isCompleted() const override;

private:
    Location* destination;
    Npc* escortedNpc;
};
