#include <DallasTemperature.h>
#include <OneWire.h>
#include <LowPower.h>

// Data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 2

// Fan output pins in array
uint8_t digitPins[] = {5, 6, 9, 10};

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void setup() {
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  sensors.begin();
}


void loop() {
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures();
  //Serial.print(sensors.getTempFByIndex(0));
  //Serial.print(" - Fahrenheit temperature: ");
  if (sensors.getTempFByIndex(0) > 80) {
    digitalWrite(digitPins, HIGH);
    Serial.println("Fan High");
    
  }
  else {
    digitalWrite(digitPins, LOW);
    Serial.println("Fan Low");
    sleepForTwoMinutes();
  }
  delay(1000);
}

//////////////////////////
void getTemp () {
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures();

  //Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(sensors.getTempFByIndex(0));
  Serial.print(" - Fahrenheit temperature: ");
  delay(1000);
}



//////////////////////////
void sleepForTwoMinutes() {
  for (int i = 0; i < 15; i++)
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
