#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "OneButton.h"

#define SmartBank_SERVICE_UUID        "9fe167e8-2827-41b3-8d66-e9a35d4ff261"
#define FMD_SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define FMD_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define TEMP_SERVICE_UUID        "e72e9720-5596-49c1-88ad-6953414fd6f4"
#define TEMP_CHARACTERISTIC_UUID "b64560f3-abe5-4271-809b-29480f0ddddc"
#define FLASH_SERVICE_UUID        "363bd9f9-8618-4281-9471-d7aaab6318e6"
#define FLASH_CHARACTERISTIC_UUID "28e13b07-c9d4-4a1a-8b66-3c512325a5b9"

BLEServer *pServer;

BLEService *SmartBank_ServiceID;
BLEService *FMD_Service;
BLECharacteristic *FMD_Characteristic;

BLEService *TEMP_Service;
BLECharacteristic *TEMP_Characteristic;

BLEService *FLASH_Service;
BLECharacteristic *FLASH_Characteristic;

int ledpin = 15;
int buzzerpin = 5;
const int oneWireBus = 4;
OneButton button1(18, true);     

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

bool deviceConnected_1 = false;

class MyServerCallbacks1: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected_1 = true;
      Serial.println("DEVICE CONNECTED");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected_1 = false;
      Serial.println("DEVICE NOT CONNECTED");
    }
};

unsigned long prevTime = millis();

long interval = 1000;

void setup() {
  Serial.begin(115200);
  BLEDevice::init("SmartBank BLE");
  sensors.begin();
  
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks1());

  //SmartBank ServiceID
  SmartBank_ServiceID = pServer->createService(SmartBank_SERVICE_UUID);
  SmartBank_ServiceID->start();
  BLEAdvertising *SmartBank_Advertising = BLEDevice::getAdvertising();
  SmartBank_Advertising->addServiceUUID(SmartBank_SERVICE_UUID);
  SmartBank_Advertising->setScanResponse(true);
  SmartBank_Advertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  SmartBank_Advertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
  //FMD SERVICE
  FMD_Service = pServer->createService(FMD_SERVICE_UUID);
  FMD_Characteristic = FMD_Service->createCharacteristic(
                                         FMD_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       ); 
                                       
  FMD_Characteristic->setValue("OFF");
  FMD_Characteristic->addDescriptor(new BLE2902());
  FMD_Service->start();
  
  BLEAdvertising *FMD_Advertising = BLEDevice::getAdvertising();
  FMD_Advertising->addServiceUUID(FMD_SERVICE_UUID);
  FMD_Advertising->setScanResponse(true);
  FMD_Advertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  FMD_Advertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  //TEMP SERVICE
  TEMP_Service = pServer->createService(TEMP_SERVICE_UUID);
  TEMP_Characteristic = TEMP_Service->createCharacteristic(
                                         TEMP_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );
                                       
  TEMP_Characteristic->addDescriptor(new BLE2902());
  TEMP_Service->start();
  
  BLEAdvertising *TEMP_Advertising = BLEDevice::getAdvertising();
  TEMP_Advertising->addServiceUUID(TEMP_SERVICE_UUID);
  TEMP_Advertising->setScanResponse(true);
  TEMP_Advertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  TEMP_Advertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  //FLASH SERVICE
  FLASH_Service = pServer->createService(FLASH_SERVICE_UUID);
  FLASH_Characteristic = FLASH_Service->createCharacteristic(
                                         FLASH_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );
                                       
  FLASH_Characteristic->setValue("OFF");
  FLASH_Characteristic->addDescriptor(new BLE2902());                                     
  FLASH_Service->start();
  
  BLEAdvertising *FLASH_Advertising = BLEDevice::getAdvertising();
  FLASH_Advertising->addServiceUUID(FLASH_SERVICE_UUID);
  FLASH_Advertising->setScanResponse(true);
  FLASH_Advertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  FLASH_Advertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
  pinMode(ledpin, OUTPUT);
  pinMode(buzzerpin, OUTPUT);
  button1.attachDuringLongPress(longPress1);
  button1.attachClick(click1);
  Serial.println("Characteristic defined! Now you can read it in the Client!");
}

void loop() {
  button1.tick();
  unsigned long currTime = millis();
  std::string value = FMD_Characteristic->getValue();
  if (value == "ON"){
    ledOn();
    buzzOn();
  }
  else{
    flashOn();
    if (currTime - prevTime > 1000){
    sendData();
    prevTime = currTime;
    }
  }
}

void sendData(){
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  std::string value = TEMP_Characteristic->getValue();
  if (deviceConnected_1) {
    //Serial.print(temperatureC);
    //Serial.println(" C");
    char txString[8]; 
    dtostrf(temperatureC, 1, 2, txString);
    TEMP_Characteristic->setValue(txString);
    TEMP_Characteristic->notify();
  }
}

void ledOn(){
  std::string value = FMD_Characteristic->getValue();
  if (value == "ON")
  {
    //Serial.println("LED ON");
    digitalWrite(ledpin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);
    digitalWrite(ledpin, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
  }
  else{
    //Serial.println("LED OFF");
    digitalWrite(ledpin, LOW);    // turn the LED off by making the voltage LOW
  }
}

void buzzOn(){
  std::string value = FMD_Characteristic->getValue();
  if (value == "ON")
  {
    //Serial.println("Buzzer ON");
    digitalWrite(buzzerpin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);
    digitalWrite(buzzerpin, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
  }
  else{
    //Serial.println("Buzzer OFF");
    digitalWrite(buzzerpin, LOW);    // turn the LED off by making the voltage LOW
  }
}

void flashOn(){
  std::string value = FLASH_Characteristic->getValue();
  if (value == "ON")
  {
    //Serial.println("Flash ON");
    digitalWrite(ledpin, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else{
    //Serial.println("Flash OFF");
    digitalWrite(ledpin, LOW);    // turn the LED off by making the voltage LOW
  }
}

void click1() {
  for (int i=1; i<=5; i=i+1) {     // Start our for loop
  FLASH_Characteristic->setValue("OFF"); 
  FMD_Characteristic->setValue("OFF");
  FMD_Characteristic->notify();
  FLASH_Characteristic->notify();
  digitalWrite(ledpin, LOW); 
  delay(200);
  }
} // click1

void longPress1() {
   FLASH_Characteristic->setValue("ON"); 
   digitalWrite(ledpin, HIGH); 
   FLASH_Characteristic->notify();
} // longPress1
