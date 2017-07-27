#include <SpacebrewYun.h>
//#include <SPI.h>
//#include <Andee.h>
#include "Arduino.h"
#include <SoftwareSerial.h>

const int START_MESS = 0;
const int END_MESS = 1;
const char start_ch = '~';
const char stop_ch = '$';
int state = -1;

//const int speaker = 5;


const int bluetoothTx = 2;
const int bluetoothRx = 3;
const int buttonSend = 8;
const int buttonScan = 9;
boolean connected = false;
String scanedAdress = "";
boolean scanned = false;
const boolean debug = true;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {


  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(buttonSend, INPUT);
  //  pinMode(speaker, OUTPUT);
  pinMode(buttonScan, INPUT);
  while (!Serial) {}


  bluetooth.write("AT+ADDR?");
  delay(100);

  bluetooth.write("AT+POWE3");
  delay(500);
  while (bluetooth.available())
  {
    Serial.write(bluetooth.read());
  }
  delay(100);
  Serial.println("");


  delay(200);
  bluetooth.write("AT+NAMEStationary");
  delay(500);
  while (bluetooth.available()) {
    Serial.write((char)bluetooth.read());

  }

  delay(200);
  Serial.println("");
  bluetooth.write("AT+IMME1");
  delay(500);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
  Serial.println("");

  delay(200);
  Serial.println("");
  bluetooth.write("AT+ROLE1");
  delay(500);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
  delay(200);
  Serial.println("");
  bluetooth.write("AT+RELI0");
  delay(500);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }


  delay(200);
  Serial.println("");
  bluetooth.write("AT+NOTI1");
  delay(500);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());

  }
  Serial.println("");

  delay(100);
  Serial.println("");
  bluetooth.write("AT+SHOW1");
  delay(500);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());

  }


  delay(100);
  Serial.println("");
  bluetooth.write("AT+ROLE1");
  delay(500);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());

  }
  Serial.println("");

  delay(100);
  Serial.println("");
  bluetooth.write("AT+IMME1");
  delay(500);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());

  }
  Serial.println("");
  delay(100);
  Serial.println("");
  bluetooth.write("AT+MODE1");
  delay(500);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());

  }
  Serial.println("");
  delay(500);
}

//Depricated
//boolean scanDevice() {
//  bluetooth.write("AT+DISC?");
//  delay(500);
//  while (bluetooth.available()) {
//    String result = bluetooth.readString();
//    int startAdressIdx = result.indexOf("DIS0:");
//    if (startAdressIdx > 0) {
//      String adressStr = result.substring(startAdressIdx + 5, startAdressIdx + 17);
//      if (debug) {
//        Serial.println("Found adress : " + adressStr);
//
//      }
//      scanedAdress = adressStr;
//      return true;
//    }
//  }
//  return false;
//}





boolean connect(String mac) {
  if (mac.length() != 12) {
    return false;
  }
  String messStr = "AT+CON" + mac;
  char messData[messStr.length() + 1];
  messStr.toCharArray(messData, messStr.length() + 1);
  bluetooth.write(messData);
  //  for (int idx = 0; idx <= messStr.length()+1; idx++) {
  //    Serial.print(messData[idx]);
  //  }
  if (debug) {
    Serial.println("Connecting to :" + mac);
  }
  delay(500);
  while (bluetooth.available()) {
    String result = bluetooth.readString();
    if (debug) {
      Serial.println("Conection result : " + result);
    }

    if (result.indexOf("CONNA") > 0) {
      if (debug) {
        Serial.println("Device " + mac + " connected");
      }
      return true;
    }
  }
  if (debug) {
    Serial.println("Device " + mac + " not connected");
  }
  return false;
}

boolean hasBLEConnected() {
  //  if (debug) {
  //    Serial.println("CheckingBLE");
  //  }
  bluetooth.write("AT+PIO1?");
  delay(500);
  while (bluetooth.available())
  {
    String str = bluetooth.readString();

    if (str.equals("OK+Get:0")) {
      if (debug) {
        Serial.println("No connection");
      }
      return false;
    }
  }
  //  if (debug) {
  //    Serial.println("Device Connected");
  //  }
  return true;

}

//String firstSignalStr = "0";
//String secondSignalStr = "0";
//String firstAdr = "";
//String secondAdr = "";
const  String mac = "5CF821F97771";
void scan() {
  bluetooth.write("AT+DISI?");
  //bluetooth.write("AT+DISC?");
  delay(1000);
  String ss;

  while (bluetooth.available()) {
    //    String scanStr =  bluetooth.readString();
    //    Serial.println(scanStr);
    ss = bluetooth.readString();
    if (ss.indexOf(mac) > 0) {
      scanned = true;
    } else {
      Serial.println("No mac");
    }
    Serial.println(ss);
    //for future
    //    int firstIdx = scanStr.indexOf(':');
    //    int ffdx = firstIdx + 67;
    //    int fldx =  ffdx + 4;
    //    //firstSignalStr = scanStr.substring(ffdx, fldx);
    //    firstAdr = scanStr.substring(ffdx - 13, fldx - 5);
    //
    //    int secondIdx = scanStr.indexOf(':', fldx);
    //    int sfdx = secondIdx + 67;
    //    int sldx = sfdx + 4;
    //    //secondSignalStr = scanStr.substring(sfdx, sldx );
    //    secondAdr = scanStr.substring(sfdx - 13, sldx - 5);
    //    scanStr = "";
    //    if (debug) {
    //Serial.println(scanStr);
    //      10 ^ ((-69 – (-60))/(10 * 2))
    //      /double meters = pow(10, ((-60 - firstSignalStr.toInt()) / (10 * 2)));
    //     / Serial.println(firstAdr);
    //      /Serial.println(secondAdr);
    //      Serial.print(firstSignalStr.toInt()); Serial.println(" " + firstAdr);
    //      Serial.print(secondSignalStr.toInt());   Serial.println(" " + secondAdr);
    //    }

  }

}

//for pmj test only
void connectoMac(String mess, String mac) {
  if (mess.indexOf(mac) > 0) {
    Serial.println("Has mac");

    connected = connect(mac);
    connected = connect(mac);
    scanned = connected;
  } else {
    Serial.println("No mac");

  }
}

void loop()
{
  if (scanned && connected) {
    while (bluetooth.available()) {
      Serial.println(bluetooth.readString());
    }
  }

  //todo need to check, work not correctly sometimes
  //  boolean needFirst = firstSignalStr.toInt() != 0 && firstSignalStr.toInt() > -45;
  //  boolean needSecond = secondSignalStr.toInt() != 0 && secondSignalStr.toInt() > -45;
  //  if (needFirst || needSecond) {
  //    scanned = true;
  //  }

  if (scanned && !connected) {
    connected = connect(mac);
  }



  //commit for pmj test
  //
  //  if (scanned && !connected) {
  //
  //    if (needFirst) {
  //      connected = connect(firstAdr);
  //
  //    } else if (needSecond) {
  //      connected = connect(secondAdr);
  //    }
  //  }


  if (!scanned) {
    scan();
  }


  //todo check this and maby implement this to STM32 or bigger chip
  //  if (connected && scanned) {
  //
  //    bluetooth.write("AT+RSSI?");
  //
  //
  //    delay(500);
  //    while (bluetooth.available()) {
  //      Serial.println("RSSI " + bluetooth.readString());
  //    }
  //  }
  //
  //
  //  if (connected) {
  //    connected = hasBLEConnected();
  //    scanned = connected;
  //
  //    if (connected) {
  //      bluetooth.write("AT+MEAS?");
  //      delay(500);
  //      while (bluetooth.available()) {
  //        Serial.println("Distance is: " + bluetooth.readString());
  //      }
  //    }
  //
  //  }
  //
  //  if (scanned == true && connected == false) {
  //    //    if (debug) {
  //    //      Serial.print("scanned "); Serial.println(scanned, DEC);
  //    //      Serial.print("connected "); Serial.println(connected, DEC);
  //    //    }
  //    connected = connect();
  //    delay(500);
  //  }
  //
  //  if (scanned == false) {
  //    scanned = scanDevice();
  //    delay(300);
  //  }

}

