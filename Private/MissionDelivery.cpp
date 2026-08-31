#include "../public/MissionDelivery.h"
#include <iostream>

using namespace std;

MissionDelivery::MissionDelivery(Player* player, Location* targetLocation, const std::string& item, int amount)
    : Mission(player, targetLocation, MissionType::DELIVERY, "Mission de Livraison", false, false),
    requestedItem(item), requestedAmount(amount), deliverySuccess(false) {
}

string MissionDelivery::getRequestedItem() const { return requestedItem; }
int MissionDelivery::getRequestedAmount() const { return requestedAmount; }
bool MissionDelivery::getDeliverySuccess() const { return deliverySuccess; }

void MissionDelivery::start() {
    isActive = true;
    isCompleted = false;
    deliverySuccess = false;

    cout << ">> [" << getTitle() << "] Un survivant a " << getTargetLocation()->getName()
        << " vous demande : " << requestedAmount << "x " << requestedItem << "." << endl;
}

void MissionDelivery::update() {
    if (!isActive || isCompleted) return;

    if (getPlayer()->hasItem(requestedItem, requestedAmount)) {
        getPlayer()->removeItem(requestedItem, requestedAmount);
        cout << ">> Livraison reussie ! Le survivant vous remercie." << endl;
        deliverySuccess = true;
        isCompleted = true;
    }
    else {
        cout << ">> Echec : vous n'avez pas " << requestedAmount << "x " << requestedItem << "." << endl;
        deliverySuccess = false;
        isCompleted = true;
    }

    isActive = false;
}

bool MissionDelivery::checkCompletion() {
    return isCompleted;
}
