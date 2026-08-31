#pragma once

// game
#include "../public/Mission.h"
#include "../public/Player.h"
#include "../public/Location.h"

// cpp
#include <string>

class MissionDelivery : public Mission {
private:
    std::string requestedItem;
    int requestedAmount;
    bool deliverySuccess;

public:
    MissionDelivery(Player* player, Location* targetLocation, const std::string& item, int amount);

    std::string getRequestedItem() const;
    int getRequestedAmount() const;
    bool getDeliverySuccess() const;

    void start() override;
    void update() override;
    bool checkCompletion() override;
};
