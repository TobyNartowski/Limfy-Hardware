#include "CommunicationModule.h"

CommunicationModule::CommunicationModule()
{
    com = new SoftwareSerial(PIN_SIM_RX, PIN_SIM_TX);
    com->begin(9600);

    pinMode(PIN_SIM_TRANSISTOR, OUTPUT);
    pinMode(PIN_SIM_RESET, OUTPUT);

    digitalWrite(PIN_SIM_TRANSISTOR, LOW);
    delay(1000);
    digitalWrite(PIN_SIM_TRANSISTOR, HIGH);
    digitalWrite(PIN_SIM_RESET, HIGH);
    
    delay(3000);
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

bool CommunicationModule::checkConnection()
{
    com->flush();
    com->print("AT+CREG?\r\n");
    String output = readSerial(200);
    if (output.indexOf("+CREG:") >= 0) {
        return output[output.indexOf("+CREG:") + 9] == '1' ? true : false;
    } 
    
    return false;
}

void CommunicationModule::initNetwork()
{
    com->print("AT\r\n");
    com->print("AT+SAPBR=3, 1, \"APN\", \"internet\"\r\n");
    com->print("AT+SAPBR=1, 1\r\n");
    com->print("AT+HTTPINIT\r\n");
}