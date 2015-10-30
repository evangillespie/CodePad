#include <DynamixelSerial1.h>

int Temperature,Voltage,Position; 

void setup(){
Serial.begin(9600);              // Begin Serial Comunication
Dynamixel.begin(1000000,2);  // Inicialize the servo at 1Mbps and Pin Control 2
delay(1000);
Dynamixel.ledStatus (1, ON) ;
Dynamixel.ledStatus (2, ON) ;
Dynamixel.ledStatus (3, ON) ;
Dynamixel.ledStatus (4, ON) ;

}

void loop(){

  Temperature = Dynamixel.readTemperature(1); // Request and Print the Temperature
  Voltage = Dynamixel.readVoltage(1);         // Request and Print the Voltage
  Position = Dynamixel.readPosition(1);       // Request and Print the Position 
  
  Serial.print(" *** Temperature: ");   // Print the variables in the Serial Monitor
  Serial.print(Temperature);
  Serial.print(" Celcius  Voltage: ");
  Serial.print(Voltage);
  Serial.print("  Volts   Position: ");
  Serial.print(Position);
  Serial.println(" of 1023 resolution");
  
  Temperature = Dynamixel.readTemperature(2); // Request and Print the Temperature
  Voltage = Dynamixel.readVoltage(2);         // Request and Print the Voltage
  Position = Dynamixel.readPosition(2);       // Request and Print the Position 
  
  Serial.print(" *** Temperature: ");   // Print the variables in the Serial Monitor
  Serial.print(Temperature);
  Serial.print(" Celcius  Voltage: ");
  Serial.print(Voltage);
  Serial.print("  Volts   Position: ");
  Serial.print(Position);
  Serial.println(" of 1023 resolution");
  
  
  
  Dynamixel.moveSpeed(1,500,60);  
  Dynamixel.moveSpeed(2,500,60); 
  Dynamixel.moveSpeed(3,1000,71);
  Dynamixel.moveSpeed(4,0,71);
  
  delay (15000);
 
   Dynamixel.moveSpeed(1,955,60);  
   Dynamixel.moveSpeed(2,45,60); 
   Dynamixel.moveSpeed(3,460,71);
   Dynamixel.moveSpeed(4,540,71);
   
   delay (15000);
  
  

}
