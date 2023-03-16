#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//SSID and Password to your ESP Access Point
const char* ssid = "TamimX";
const char* password = "def_Tamim_2023";

#define ENA   4     // Enable/speed motors Right    GPIO4(D2)
#define IN_1  0     // L298N in1 motors Right       GPIO0(D3)
#define IN_2  2     // L298N in2 motors Right       GPIO2(D4)
#define IN_3  12    // L298N in3 motors Left        GPIO12(D6)
#define IN_4  13    // L298N in4 motors Left        GPIO13(D7)
#define ENB   15    // Enable/speed motors Left     GPIO15(D8)

#define Light  16 // Light  GPIO16(D0)

String command;             //String to store app command state.
int speedCar = 150; // 0 to 255
int speed_0 = 60;

ESP8266WebServer server(80);

void setup() {

    Serial.begin(115200);

    pinMode(ENA, OUTPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(Light, OUTPUT);


    // Connecting WiFi

    WiFi.mode(WIFI_AP);           //Only Access point
    WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // Starting WEB-server 
    server.on("/", HTTP_handleRoot);
    server.onNotFound(HTTP_handleRoot);
    server.begin();
}

void loop() {
    server.handleClient();

    command = server.arg("State");
    if (command == "F") goForword();
    else if (command == "B") goBack();
    else if (command == "L") goLeft();
    else if (command == "R") goRight();
    else if (command == "I") goForwordRight();
    else if (command == "G") goForwordLeft();
    else if (command == "J") goBackRight();
    else if (command == "H") goBackLeft();
    else if (command == "W") digitalWrite(Light, 1); // light is on
    else if (command == "w") digitalWrite(Light, 0);  // light is off
    else if (command == "0") speedCar = 100;
    else if (command == "1") speedCar = 120;
    else if (command == "2") speedCar = 140;
    else if (command == "3") speedCar = 160;
    else if (command == "4") speedCar = 180;
    else if (command == "5") speedCar = 200;
    else if (command == "6") speedCar = 215;
    else if (command == "7") speedCar = 230;
    else if (command == "8") speedCar = 240;
    else if (command == "9") speedCar = 255;
    else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {

    if (server.hasArg("State")) {
        Serial.println(server.arg("State"));
    }
    server.send(200, "text/html", "");
    delay(1);
}

void goForword(){

    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 0);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 1);
    analogWrite(ENB, speedCar);
}

void goBack(){

    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 1);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 0);
    analogWrite(ENB, speedCar);
}

void goRight(){

    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 1);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 1);
    analogWrite(ENB, speedCar);
}

void goLeft(){

    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 0);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 0);
    analogWrite(ENB, speedCar);
}

void goForwordRight(){

    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 0);
    analogWrite(ENA, speedCar - speed_0);

    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 1);
    analogWrite(ENB, speedCar);
}

void goForwordLeft(){

    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 0);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 1);
    analogWrite(ENB, speedCar - speed_0);
}

void goBackRight(){

    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 1);
    analogWrite(ENA, speedCar - speed_0);

    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 0);
    analogWrite(ENB, speedCar);
}

void goBackLeft(){

    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 1);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 0);
    analogWrite(ENB, speedCar - speed_0);
}

void stopRobot(){

    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 0);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 0);
    analogWrite(ENB, speedCar);
}