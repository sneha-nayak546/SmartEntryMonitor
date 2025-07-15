#define BLYNK_TEMPLATE_ID "TMPL3SrngiWeI"
#define BLYNK_TEMPLATE_NAME "LED1"
#define BLYNK_AUTH_TOKEN "utr7ATuK5fITBphYwrMsrNGJ92xN8EVo"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <WebServer.h>

const int greenLED = 27;
const int redLED = 13;
const int trigPin = 5;
const int echoPin = 18;
const int buzzer = 21;

long duration;
int distance;
bool objectDetected = false;
bool notificationSent = false;  

WebServer server(80);

char ssid[] = "POCO C65";
char pass[] = "12345678";

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  server.on("/led", HTTP_GET, []() {
    String color = server.arg("color");
    Serial.println(color);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    //if (objectDetected) {
      Serial.println(color);
      if (color == "green") {
        Serial.println(color);
        digitalWrite(greenLED, HIGH);
      } else if (color == "red") {
        Serial.println(color);
        digitalWrite(redLED, HIGH);
      }
    //}

    server.send(200, "text/plain", "LED set to " + color);
  });

  server.begin();
  Serial.println(WiFi.localIP());
}

void loop() {
  Blynk.run();
  server.handleClient();
  detectObject();
}

void detectObject() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > 0 && distance < 15) {
    Serial.println("Person detected");
    objectDetected = true;
    digitalWrite(buzzer, HIGH);

    if (!notificationSent) {
      Blynk.logEvent("door_alert", "Someone is at the door! http://192.168.53.191:5000");
      notificationSent = true;
    }
  } else {
    objectDetected = false;
    notificationSent = false;
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(500);
}