//Code for smart irrigation system
//@authors: Guillermo Nasif

#include <LiquidCrystal.h>  
// Includes the LiquidCrystal library to control the LCD screen


// Creates an LCD object and tells Arduino which pins are connected
// RS = 12, E = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int soilPin = A0;     
// Soil moisture sensor connected to analog pin A0

const int relayPin = 6;     
// Relay module connected to digital pin 6

int soilValue;              
// Variable to store raw sensor reading

void setup() {

  pinMode(relayPin, OUTPUT);    
  // Sets relay pin as output

  digitalWrite(relayPin, HIGH); 
  // Starts with pump OFF
  // (Many relay modules are active LOW)

  Serial.begin(9600);           
  // Starts serial monitor communication at 9600 baud

  lcd.begin(16, 2);            
  // Starts LCD screen with 16 columns and 2 rows

  lcd.print("Smart Irrigation"); 
  // Displays startup message

  delay(2000);                 
  // Waits 2 seconds

  lcd.clear();                 
  // Clears LCD screen
}

void loop() {

  soilValue = analogRead(soilPin);  
  // Reads analog value from soil sensor (0 to 1023)

  Serial.println(soilValue);        
  // Prints sensor value to Serial Monitor

  int moisturePercent = map(soilValue, 950, 400, 0, 100);
  // Converts sensor reading into percentage
  // 950 = dry soil = 0%
  // 400 = wet soil = 100%

  moisturePercent = constrain(moisturePercent, 0, 100);
  // Keeps result between 0% and 100%

  if (moisturePercent < 50) {      

    digitalWrite(relayPin, HIGH);  
    // Turns pump ON if soil is dry
    // (Depends on relay type)

  } else {

    digitalWrite(relayPin, LOW);   
    // Turns pump OFF if soil is wet enough
  }

  // ----- LCD FIRST ROW -----
  lcd.setCursor(0, 0);        
  // Moves cursor to column 0, row 0

  lcd.print("Moisture: ");    
  // Prints label

  lcd.print(moisturePercent); 
  // Prints moisture percentage number

  lcd.print("%");             
  // Prints % symbol

  lcd.print("                "); 
  // Clears leftover characters

  // ----- LCD SECOND ROW -----
  lcd.setCursor(0, 1);        
  // Moves cursor to column 0, row 1

  if (moisturePercent < 50) {

    lcd.print("WATERING...     ");
    // Shows watering message

  } else {

    lcd.print("NO WATER NEEDED ");
    // Shows no watering message
  }

  delay(2000);               
  // Waits 2 seconds before next reading
}
