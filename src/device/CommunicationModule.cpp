#include "CommunicationModule.h"

CommunicationModule::CommunicationModule()
{
    com = new SoftwareSerial(PIN_SIM_RX, PIN_SIM_TX);
    pinMode(PIN_SIM_RESET, OUTPUT);
    digitalWrite(PIN_SIM_RESET, LOW);

    pinMode(PIN_SIM_TRANSISTOR, OUTPUT);
    digitalWrite(PIN_SIM_TRANSISTOR, LOW);
    delay(3000);
    digitalWrite(PIN_SIM_TRANSISTOR, HIGH);
    
    delay(1000);
    digitalWrite(PIN_SIM_RESET, HIGH);

    com->begin(9600);
}

String CommunicationModule::readSerial(unsigned long timeout)
{
    unsigned long timestamp = millis();

    while (!com->available() && !(millis() - timestamp > timeout)) {
        delay(13);
    }

    String response = "";
    while (com->available()) {
        response.concat(com->readString());
    }

    return response;
}

void CommunicationModule::reset()
{
    digitalWrite(PIN_SIM_RESET, LOW);
    delay(500);

    digitalWrite(PIN_SIM_TRANSISTOR, LOW);
    delay(500);
    digitalWrite(PIN_SIM_TRANSISTOR, HIGH);
    
    delay(500);
    digitalWrite(PIN_SIM_RESET, HIGH);
}

void CommunicationModule::checkConnection()
{
    String result = executeCommand("AT+CREG?", 700);

    while (result[result.indexOf("+CREG:") + 9] != '1') {
        delay(3000);
        bootCounter++;

        if (bootCounter > 5) {
            Serial.println("[SIM800L] reset");
            reset();
            bootCounter = 0;
        }
        result = executeCommand("AT+CREG?", 700);
    } 
}

void CommunicationModule::initNetwork()
{
    com->flush();

    executeCommand("AT", 1000);
    executeCommand("AT+SAPBR=3, 1, \"APN\", \"internet\"", 2000);
    executeCommand("AT+SAPBR=1, 1", 3000);
    executeCommand("AT+HTTPINIT", 1000);
}

void CommunicationModule::check()
{
    String connection = executeCommand("AT+CREG?", 700);
    if (connection[connection.indexOf("+CREG:") + 9] != '1') {
        Serial.println("[SIM800L] not ok");
        do {
            Serial.println("[SIM800L] check");
            checkConnection();
            delay(1000);
            
            Serial.println("[SIM800L] init");
            initNetwork();
            delay(300);
            connection = executeCommand("AT+CREG?", 700);
        } while (connection[connection.indexOf("+CREG:") + 9] != '1');
    }
    Serial.println("[SIM800L] ok");
}

void CommunicationModule::sendData(String data)
{
    com->flush();
    
    executeCommand("AT+HTTPPARA=\"URL\", \"http://limfy.free.beeceptor.com/api/measurements\"", 1000);
    executeCommand("AT+HTTPPARA=\"CONTENT\", \"application/json\"", 600);
    executeCommand("AT+HTTPDATA=64, 3000", 1000);
    executeCommand(data, 500);
    delay(3000);

    executeCommand("AT+HTTPACTION=1", 1000);
}

String CommunicationModule::executeCommand(String command, unsigned long delayMs) {
    com->flush();
 
    com->println(command.c_str());
    delay(delayMs);
 
    String response = "";
    while (com->available()) {
        response.concat(com->readString());
        delay(10);
    }

    return response;
}
