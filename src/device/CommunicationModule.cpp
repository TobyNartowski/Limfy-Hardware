#include "CommunicationModule.h"

CommunicationModule::CommunicationModule()
{
    com = new SoftwareSerial(PIN_SIM_RX, PIN_SIM_TX);

    pinMode(PIN_SIM_TRANSISTOR, OUTPUT);
    digitalWrite(PIN_SIM_TRANSISTOR, LOW);
    delay(3000);
    digitalWrite(PIN_SIM_TRANSISTOR, HIGH);
    
    pinMode(PIN_SIM_RESET, OUTPUT);
    digitalWrite(PIN_SIM_RESET, HIGH);

    delay(2000);
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
    digitalWrite(PIN_SIM_TRANSISTOR, LOW);
    delay(500);
    digitalWrite(PIN_SIM_TRANSISTOR, HIGH);
    
    delay(500);

    digitalWrite(PIN_SIM_RESET, LOW);
    delay(500);
    digitalWrite(PIN_SIM_RESET, HIGH);
}

bool CommunicationModule::checkConnection()
{
    Serial.println("incheck");
    String result = executeCommand("AT+CREG?", 300);
    return result[result.indexOf("+CREG:") + 9] == '1';
}

void CommunicationModule::initNetwork()
{
    com->flush();
    executeCommand("AT", 300);
    delay(500);
    executeCommand("AT+SAPBR=3, 1, \"APN\", \"internet\"", 1000);
    delay(500);
    executeCommand("AT+SAPBR=1, 1", 1000);
    delay(500);
    executeCommand("AT+HTTPINIT", 1000);
    delay(1000);
}

void CommunicationModule::sendData()
{
    com->flush();
    
    executeCommand("AT+HTTPPARA=\"URL\", \"http://sim800.free.beeceptor.com/api/measurements\"", 300);
    executeCommand("AT+HTTPPARA=\"CONTENT\", \"application/x-www-form-urlencoded\"", 300);
    executeCommand("AT+HTTPDATA=8, 2000", 300);
    executeCommand(String(millis()), 1000);
    executeCommand("AT+HTTPACTION=1", 500);
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
 
    response.remove(0, command.length());
    response.trim();

    return response;
}
 