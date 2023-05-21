#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Configurações da rede Wi-Fi
const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";

// Configurações do servidor MQTT
const char* mqttServer = "IP_DO_SERVIDOR_MQTT";
const int mqttPort = 1883;
const char* mqttUser = "USUARIO_MQTT";
const char* mqttPassword = "SENHA_MQTT";

// Configuração dos pinos da fita LED
#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 7

// Configuração do pino do sensor PIR
#define PIR_PIN 2

// Variável para armazenar o estado do sensor PIR e das luzes
int pirState = LOW;
bool lightsOn = false;

// Objeto WiFi
WiFiClient wifiClient;

// Objeto MQTT
PubSubClient mqttClient(wifiClient);

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Conecta-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando à rede Wi-Fi...");
  }
  Serial.println("Conectado à rede Wi-Fi");

  // Configura o servidor MQTT
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);

  // Conecta-se ao servidor MQTT
  while (!mqttClient.connected()) {
    if (mqttClient.connect("arduino-client", mqttUser, mqttPassword)) {
      Serial.println("Conectado ao servidor MQTT");
    } else {
      Serial.print("Falha na conexão com o servidor MQTT. Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }

  // Define os pinos da fita LED como saída
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Define o pino do sensor PIR como entrada
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }

  // Lê o estado do sensor PIR
  pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH && !lightsOn) {
    // Se o sensor detectar movimento e as luzes estiverem desligadas, liga todas as luzes RGB
    analogWrite(RED_PIN, 255);
    analogWrite(GREEN_PIN, 255);
    analogWrite(BLUE_PIN, 255);
    lightsOn = true;
    Serial.println("Movimento detectado - Luzes ligadas");
    mqttClient.publish("led/status", "ON");
  } else if (pirState == LOW && lightsOn) {
    // Se o sensor não detectar movimento e as luzes estiverem ligadas, desliga todas as luzes RGB
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
    lightsOn = false;
    Serial.println("Nenhum movimento detectado - Luzes desligadas");
    mqttClient.publish("led/status", "OFF");
  }

 
