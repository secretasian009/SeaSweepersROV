/*
  Receving Code Sensors
  Reads bytes from Transmitting Code and put thems back together
  Then sends the bytes through serial to a raspberry pi
*/
//variables for motorSense
unsigned char motorFirstByte;
unsigned char motorSecondByte;
unsigned char motorThirdByte;

int x;


unsigned char val[48];
//data TWO THREE FIVE are not used but can be later
int insideTemperatureData;
//int dataTwo;
//int dataThree;
int depthData;
//int dataFive;
int pressureData;
int probeTemperatureData;
int joyStickOneData;
int joyStickTwoData;
int joyStickThreeData;
int joyStickFourData;
int joyStickFiveData;
int joyStickSixData;
int servoDataReal;
int lightData;
int totalVoltData;
int totalAmpData;
int xAccelData;
int yAccelData;
int zAccelData;
int angleData;
int waterSenseOne;
int waterSenseTwo;
int servoData;

unsigned char insideTemperatureCheck;
unsigned char checksum1;
unsigned char checksum2;
unsigned char depthCheck;
unsigned char checksum4;
unsigned char pressureCheck;
unsigned char probeTemperatureCheck;
unsigned char joyOneCheck;
unsigned char joyTwoCheck;
unsigned char joyThreeCheck;
unsigned char joyFourCheck;
unsigned char joyFiveCheck;
unsigned char joySixCheck;
unsigned char servoCheck;
unsigned char lightCheck;
unsigned char totalvoltCheck;
unsigned char totalAmpCheck;
unsigned char xAccelCheck;
unsigned char yAccelCheck;
unsigned char zAccelCheck;
unsigned char angleCheck;
unsigned char waterSenseOneCheck;
unsigned char waterSenseTwoCheck;
unsigned char servoDataCheck;
unsigned char last;

unsigned char FirstByte;
unsigned char SecondByte;
unsigned char ThirdByte;
unsigned char LastByte;

unsigned char insideTemperatureCheckit;
unsigned char checkit1;
unsigned char checkit2;
unsigned char depthCheckit;
unsigned char checkit4;
unsigned char pressureCheckit;
unsigned char probeTemperatureCheckit;
unsigned char joyOneCheckit;
unsigned char joyTwoCheckit;
unsigned char joyThreeCheckit;

unsigned char joyFourCheckit;
unsigned char joyFiveCheckit;
unsigned char joySixCheckit;
unsigned char servoCheckit;
unsigned char lightCheckit;
unsigned char totalVoltCheckit;
unsigned char totalAmpCheckit;
unsigned char xAccelCheckit;
unsigned char yAccelCheckit;
unsigned char zAccelCheckit;
unsigned char angleCheckit;

unsigned char waterSenseOneCheckit;
unsigned char waterSenseTwoCheckit;
unsigned char servoDataCheckit;


void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  pinMode(19, INPUT);
  pinMode(18, OUTPUT);
  pinMode(17, INPUT);
  pinMode(16, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
 delay(1000); 
//  digitalWrite(12,LOW);
//  digitalWrite(11,LOW);
//  delay(550);
//  digitalWrite(12,HIGH);
//  digitalWrite(11,LOW);
//  delay(250);
//  digitalWrite(12,LOW);
//  digitalWrite(11,HIGH);
//  delay(250);
//  digitalWrite(12,HIGH);
//  digitalWrite(11,LOW);
//  delay(400);  
//  digitalWrite(12,LOW);
//  digitalWrite(11,HIGH);
//  delay(800);
//  digitalWrite(12,HIGH);
//  digitalWrite(11,HIGH);
//  delay(325);  
//  digitalWrite(12,LOW);
//  digitalWrite(11,LOW);      
//  delay(2000);
//  digitalWrite(12,HIGH);
//  digitalWrite(11,HIGH);
}

void loop() {
  Serial1.write(1);
  Serial1.write(2);
  Serial1.write(3);
  if (Serial1.available() > 2) {
    FirstByte = Serial1.read();
    SecondByte = Serial1.read();
    ThirdByte = Serial1.read();
    if ((FirstByte == 1) && (SecondByte == 2) && (ThirdByte == 3)) {
      val[0] = Serial1.read();       // least significant 8 bits
      val[1] = Serial1.read();       // most significant 2 bits
      insideTemperatureCheck = Serial1.read();   // checksum

      val[6] = Serial1.read();
      val[7] = Serial1.read();
      depthCheck = Serial1.read();

      val[10] = Serial1.read();
      val[11] = Serial1.read();
      pressureCheck = Serial1.read();

      val[12] = Serial1.read();
      val[13] = Serial1.read();
      probeTemperatureCheck = Serial1.read();

      val[42] = Serial1.read();
      val[43] = Serial1.read();
      waterSenseOneCheck = Serial1.read();

      val[44] = Serial1.read();
      val[45] = Serial1.read();
      waterSenseTwoCheck = Serial1.read();
        // end of reading data
      last = Serial1.read();

        
      //check the bytes
      insideTemperatureCheckit = val[0] + val[1] + insideTemperatureCheck;
      depthCheckit = val[6] + val[7] + depthCheck;
      pressureCheckit = val[10] + val[11] + pressureCheck;
      probeTemperatureCheckit = val[12] + val[13] + probeTemperatureCheck;
      waterSenseOneCheckit = val[42] + val[43] + waterSenseOneCheck;
      waterSenseTwoCheckit = val[44] + val[45] + waterSenseTwoCheck;
      if (last==2){
        if (insideTemperatureCheckit == 0)  {
          insideTemperatureData = val[1] << 8 | val[0];
        }
        if (depthCheckit == 0)  {
          depthData = val[7] << 8 | val[6];
        }
        if (pressureCheckit == 0)  {
          pressureData = val[11] << 8 | val[10];
          //pressureData = 5;
        }
        if (probeTemperatureCheckit == 0)  {
          probeTemperatureData = val[13] << 8 | val[12];
        }
        if (waterSenseOneCheckit == 0)  {
          waterSenseOne = val[43] << 8 | val[42];
        }
        if (waterSenseTwoCheckit == 0)  {
          waterSenseTwo = val[45] << 8 | val[44];
        }
      }
    }
  }
  delay(20);
    //read joystick data
  Serial2.write(1);
  Serial2.write(2);
  Serial2.write(3);
    
  if (Serial2.available() > 2) {
    motorFirstByte = Serial2.read();
    motorSecondByte = Serial2.read();
    motorThirdByte = Serial2.read();
    if ((motorFirstByte == 1) && (motorSecondByte == 2) && (motorThirdByte == 3)) {

      val[14] = Serial2.read();
      val[15] = Serial2.read();
      joyOneCheck = Serial2.read();

      val[16] = Serial2.read();
      val[17] = Serial2.read();
      joyTwoCheck = Serial2.read();

      val[18] = Serial2.read();
      val[19] = Serial2.read();
      joyThreeCheck = Serial2.read();

      val[20] = Serial2.read();
      val[21] = Serial2.read();
      joyFourCheck = Serial2.read();

      val[22] = Serial2.read();
      val[23] = Serial2.read();
      joyFiveCheck = Serial2.read();

      val[24] = Serial2.read();
      val[25] = Serial2.read();
      joySixCheck = Serial2.read();

      val[26] = Serial2.read();
      val[27] = Serial2.read();
      servoCheck = Serial2.read();
        
      val[28] = Serial2.read();
      val[29] = Serial2.read();
      lightCheck = Serial2.read();
      
      LastByte = Serial2.read();

      joyOneCheckit = val[14] + val[15] + joyOneCheck;
      joyTwoCheckit = val[16] + val[17] + joyTwoCheck;
      joyThreeCheckit = val[18] + val[19] + joyThreeCheck;
      joyFourCheckit = val[20] + val[21] + joyFourCheck;
      joyFiveCheckit = val[22] + val[23] + joyFiveCheck;
      joySixCheckit = val[24] + val[25] + joySixCheck;
      servoCheckit = val[26] + val[27] + servoCheck;
      lightCheckit = val[28] + val[29] + lightCheck;        
    }
    if (LastByte == 2){
      if (joyOneCheckit == 0)  {
        joyStickOneData = val[15] << 8 | val[14];
      }
      if (joyTwoCheckit == 0)  {
        joyStickTwoData = val[17] << 8 | val[16];
      }
      if (joyThreeCheckit == 0)  {
        joyStickThreeData = val[19] << 8 | val[18];
      }
      if (joyFourCheckit == 0)  {
        joyStickFourData = val[21] << 8 | val[20];
      }
      if (joyFiveCheckit == 0)  {
        joyStickFiveData = val[23] << 8 | val[22];
      }
      if (joySixCheckit == 0)  {
        joyStickSixData = val[25] << 8 | val[24];
      }
      if (servoCheckit == 0)  {
        servoDataReal = val[27] << 8 | val[26];
      }
      if (lightCheckit == 0)  {
        lightData = val[29] << 8 | val[28];
      }
    }
  }
    Serial.print("A");
    Serial.print(insideTemperatureData);
    Serial.print("B");

    Serial.print("C");
    Serial.print(depthData);
    Serial.print("D");

    Serial.print("E");
    Serial.print(pressureData);
    Serial.print("F");

    Serial.print("G");
    Serial.print(probeTemperatureData);
    Serial.print("H");

    Serial.print("I");
    Serial.print(joyStickOneData);
    Serial.print("J");

    Serial.print("K");
    Serial.print(joyStickTwoData);
    Serial.print("L");

    Serial.print("M");
    Serial.print(joyStickThreeData);
    Serial.print("N");

    Serial.print("O");
    Serial.print(joyStickFourData);
    Serial.print("P");

    Serial.print("Q");
    Serial.print(joyStickFiveData);
    Serial.print("R");

    Serial.print("S");
    Serial.print(joyStickSixData);
    Serial.print("T");

    Serial.print("U");
    Serial.print(servoDataReal);
    Serial.print("V");

    Serial.print("W");
    Serial.print(lightData);
    Serial.print("X");

//    Serial.print("Y");
//    Serial.print(totalVoltData);
//    Serial.print("Z");
//
//    Serial.print("a");
//    Serial.print(totalAmpData);
//    Serial.print("b");
//
//    Serial.print("c");
//    Serial.print(xAccelData);
//    Serial.print("d");
//
//    Serial.print("e");
//    Serial.print(yAccelData);
//    Serial.print("f");
//
//    Serial.print("g");
//    Serial.print(zAccelData);
//    Serial.print("h");
//
//    Serial.print("i");
//    Serial.print(angleData);
//    Serial.print("j");

    Serial.print("k");
    Serial.print(waterSenseOne);
    Serial.print("l");

    Serial.print("m");
    Serial.print(waterSenseTwo);
    Serial.println("n");
    //delay(20);
    if (waterSenseOne > 50 || waterSenseTwo >50) {
      digitalWrite(12,LOW);
      digitalWrite(11,LOW);
      } else {
      digitalWrite(12,HIGH);
      digitalWrite(11,HIGH);
      }
    delay(30);
    }


