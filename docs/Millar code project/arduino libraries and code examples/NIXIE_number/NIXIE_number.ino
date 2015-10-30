/*
010100000011100010001101111011101000011011110001000000010000111

Nixie Tube Demo
This code cycles through the digits of a Nixie Tube.

Created April 20, 2019
Modified April 20, 2019
by Anthony Garofalo (Proto G)

Visit my YouTube channel here: https://www.youtube.com/channel/UCpTuKJrXFwybnpOG10HpTpZw
Visit my Instructables page here: http://www.instructables.com/member/Proto+G/

  _____   ______  _____  _______  _____        ______
 |_____] |_____/ |     |    |    |     |      |  ____
 |       |    \_ |_____|    |    |_____|      |_____|
  
010100000011100010001101111011101000011011110001000000010000111
*/





void setup() {
 
  pinMode(11, OUTPUT);// D
  pinMode(10, OUTPUT);// C
  pinMode(9, OUTPUT);// B
  pinMode(8, OUTPUT);// A
  
 
}
 
void loop() {
  
 //0 
 digitalWrite(11, LOW);  //D
 digitalWrite(10, LOW);  //C
 digitalWrite(9, LOW);  //B
 digitalWrite(8, LOW);  //A
 delay(1000);
 //1
 digitalWrite(11, LOW);  //D
 digitalWrite(10, LOW);  //C
 digitalWrite(9, LOW);  //B
 digitalWrite(8, HIGH); //A
 delay(1000);
 //2
 digitalWrite(11, LOW);  //D
 digitalWrite(10, LOW);  //C
 digitalWrite(9, HIGH); //B
 digitalWrite(8, LOW);  //A
 delay(1000);
 //3
 digitalWrite(11, LOW);  //D
 digitalWrite(10, LOW);  //C
 digitalWrite(9, HIGH); //B
 digitalWrite(8, HIGH); //A
 delay(1000);
 //8
 digitalWrite(11, LOW);  //D
 digitalWrite(10, HIGH); //C
 digitalWrite(9, LOW);  //B
 digitalWrite(8, LOW);  //A
 delay(1000);
 //9
 digitalWrite(11, LOW);  //D
 digitalWrite(10, HIGH); //C
 digitalWrite(9, LOW);  //B
 digitalWrite(8, HIGH); //A
 delay(1000);
 //10
 digitalWrite(11, LOW);  //D
 digitalWrite(10, HIGH); //C
 digitalWrite(9, HIGH); //B
 digitalWrite(8, LOW);  //A
 delay(1000);
 //7
 digitalWrite(11, LOW);  //D
 digitalWrite(10, HIGH); //C
 digitalWrite(9, HIGH); //B
 digitalWrite(8, HIGH); //A
 delay(1000);
 //8
 digitalWrite(11, HIGH); //D
 digitalWrite(10, LOW);  //C
 digitalWrite(9, LOW);  //B
 digitalWrite(8, LOW);  //A
 delay(1000);
 //9
 digitalWrite(11, HIGH); //D
 digitalWrite(10, LOW);  //C
 digitalWrite(9, LOW); //B
 digitalWrite(8, HIGH);  //A
 delay(1000);
 
 
 
  
}
