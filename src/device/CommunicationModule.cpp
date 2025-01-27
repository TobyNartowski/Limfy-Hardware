#include "CommunicationModule.h"

CommunicationModule::CommunicationModule()
{
    BLEDevice::init("LimfyDevice");
    server = BLEDevice::createServer();
    service = server->createService("43428fb9-22dd-4d10-96e1-b32477365024");

    heartbeatCharacteristic = new BLECharacteristic("5168996b-625b-4d5d-ad14-fc30d0b91fcc", 
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
    stepsCharacteristic = new BLECharacteristic("72a590ba-09fe-4e88-a8d0-508d6c001b43", 
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
    shakinessCharacteristic = new BLECharacteristic("cc4616ac-b55a-4d4d-8cd4-034ba13dd56a", 
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
    fallCharacteristic = new BLECharacteristic("ec8357c6-6bde-4275-b03b-bbfa16cd2a47", 
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
        

    service->addCharacteristic(fallCharacteristic);
    service->addCharacteristic(shakinessCharacteristic);
    service->addCharacteristic(stepsCharacteristic);
    service->addCharacteristic(heartbeatCharacteristic);
    server->setCallbacks(new ServerCallbacks());

    service->start();
    server->getAdvertising()->start();
}

void CommunicationModule::setHeartbeat(uint8_t heartbeat)
{
    heartbeatCharacteristic->setValue(&heartbeat, sizeof(uint8_t));
    heartbeatCharacteristic->notify();
}

void CommunicationModule::setSteps(uint8_t steps)
{
    stepsCharacteristic->setValue(&steps, sizeof(uint8_t));    
    stepsCharacteristic->notify();
}

void CommunicationModule::setShakiness(uint8_t shakiness)
{
    shakinessCharacteristic->setValue(&shakiness, sizeof(uint8_t));
    shakinessCharacteristic->notify();
}

void CommunicationModule::fallDetected(uint8_t value)
{
    fallCharacteristic->setValue(&value, sizeof(uint8_t));
    fallCharacteristic->notify();
}