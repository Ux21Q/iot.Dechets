#include <WiFi.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

String apiKey = "9EGD7HYDY1RO3S9T";

const int trigPin = 5;
const int echoPin = 18;

long duration;
float distance;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Connexion WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connexion WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnecté !");
}

void loop() {
  // Mesure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Envoi vers ThingSpeak
  if (client.connect("api.thingspeak.com", 80)) {
    String url = "/update?api_key=" + apiKey + "&field1=" + String(distance);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: api.thingspeak.com\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("Donnée envoyée !");
  }

  client.stop();

  delay(15000); // ThingSpeak limite
}
