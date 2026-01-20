// Définition des pins
const int trigPin = 9;
const int echoPin = 10;
const int ledVerte = 12;
const int ledRouge = 13;

// Variables pour les mesures
long duration;
int distance;
int hauteurPoubelle = 100; // Hauteur totale de la poubelle en cm (exemple)
int seuilAlerte = 10;      // Alerte si moins de 10 cm d'espace vide

// Clé API ThingSpeak (Simulée ici)
String apiKey = "GRAZEU3KL2ZTXK5D";

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledVerte, OUTPUT);
  pinMode(ledRouge, OUTPUT);
  Serial.begin(9600); // Démarrage de la communication série
}

void loop() {
  // 1. Activation du capteur ultrason
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 2. Lecture de l'écho
  duration = pulseIn(echoPin, HIGH);

  // 3. Calcul de la distance (vitesse son = 0.034 cm/us)
  distance = duration * 0.034 / 2;

  // 4. Logique de gestion (Niveau de la poubelle)
  // Distance = Espace vide. Si Distance est petite, poubelle est pleine.
  
  Serial.print("Espace vide: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < seuilAlerte) {
    // ALERTE : POUBELLE PLEINE
    digitalWrite(ledRouge, HIGH);
    digitalWrite(ledVerte, LOW);
    Serial.println("ALERTE: Poubelle pleine ! Collecte requise.");
  } else {
    // NORMAL
    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVerte, HIGH);
  }

  // 5. Simulation de l'envoi vers ThingSpeak (Format MQTT/HTTP)
  // Dans un vrai projet avec module WiFi (ESP8266), on utiliserait client.print()
  sendToThingSpeak(distance);

  delay(1000); // ThingSpeak accepte une donnée toutes les 15 sec (version gratuite)
}

void sendToThingSpeak(int value) {
  // Simulation de la requête HTTP
  Serial.println("--- ENVOI CLOUD ---");
  Serial.print("GET /update?api_key=");
  Serial.print(apiKey);
  Serial.print("&field1=");
  Serial.println(value);
  Serial.println("-------------------");
}
