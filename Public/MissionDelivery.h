#pragma once
#include "../public/Mission.h"
#include "../public/Location.h"
#include "../public/Player.h"

class MissionDelivery : public Mission {
public:
    MissionDelivery(Player* player, Location* startLoc, Location* endLoc);
    void start() override;
    void update() override;
    bool isCompleted() const override;

private:
    Location* destination;
};
