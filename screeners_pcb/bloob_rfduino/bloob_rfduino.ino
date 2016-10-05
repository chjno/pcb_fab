#include <RFduinoBLE.h>

const int transistorPin = 2;
const int interval = 500;

void setup()
{
  Serial.begin(9600);
  pinMode(transistorPin, OUTPUT);
  digitalWrite(transistorPin, LOW);

  // Check RFduino CPU temperature, and print to log
//  float CPU_temperature = RFduino_temperature(CELSIUS);
//  Serial.print("RFduino_temperature is: ");
//  Serial.print(CPU_temperature);
//  Serial.println(" deg C");

  // this is the data we want to appear in the advertisement
  // (the deviceName length plus the advertisement length must be <= 18 bytes
//   RFduinoBLE.advertisementData = "data";
  RFduinoBLE.advertisementInterval = interval;
  RFduinoBLE.deviceName = "RFchino";

  // start the BLE stack
  RFduinoBLE.begin();
  Serial.println("RFduino BLE stack started");
}

// This function is called continuously, after setup() completes.
void loop()
{
  // switch to lower power mode
  RFduino_ULPDelay(INFINITE);
}


void RFduinoBLE_onAdvertisement(bool start)
{
  Serial.println("RFduino is doing BLE advertising ...");
}

void RFduinoBLE_onConnect()
{
  Serial.println("RFduino BLE connection successful");
}

void RFduinoBLE_onDisconnect()
{
  Serial.println("RFduino BLE disconnected");
  // don't leave the glasses on after disconnection
  digitalWrite(transistorPin, LOW);
}

void RFduinoBLE_onReceive(char *data, int len)
{
  // if the first byte is 0x01 / on / true
  Serial.println("Received data over BLE");
  Serial.println(data[0]);
  if (data[0] == '1')
  
  {
    digitalWrite(transistorPin, HIGH);
//    Serial.println("High");
  }
  else
  {
    digitalWrite(transistorPin, LOW);
//    Serial.println("Low");
  }
}
