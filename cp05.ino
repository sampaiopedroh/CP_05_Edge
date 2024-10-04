#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Configurações - variáveis editáveis
const char* default_SSID = "wifi"; 
const char* default_PASSWORD = "senhaWifi"; 
const char* default_BROKER_MQTT = "ipServidor";
const int default_BROKER_PORT = 1883; 
const char* topicPrefix = "dispositivo";

// Variáveis para configurações editáveis
char* SSID = const_cast<char*>(default_SSID);
char* PASSWORD = const_cast<char*>(default_PASSWORD);
char* BROKER_MQTT = const_cast<char*>(default_BROKER_MQTT);
int BROKER_PORT = default_BROKER_PORT;

// Pinos dos sensores
#define DHTPIN 4     // Pino do DHT22
#define LDRPIN 34    // Pino do LDR
#define DHTTYPE DHT22 // Tipo de sensor DHT

// Tópicos MQTT
const char* TOPICO_LDR = "/TEF/dispositivo/ldr";
const char* TOPICO_DHT_TEMP = "/TEF/dispositivo/dht/temperatura";
const char* TOPICO_DHT_UMIDADE = "/TEF/dispositivo/dht/umidade";

// Inicializa os objetos
WiFiClient espClient;
PubSubClient MQTT(espClient);
DHT dht(DHTPIN, DHTTYPE);

void initSerial() {
  Serial.begin(115200);
}

void initWiFi() {
  delay(10);
  Serial.println("------Conexao WI-FI------");
  Serial.print("Conectando-se na rede: ");
  Serial.println(SSID);
  Serial.println("Aguarde");
  reconectWiFi();
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  // Não precisa de callback se não vai receber mensagens
}

void setup() {
  initSerial();
  initWiFi();
  initMQTT();
  dht.begin();
  
  Serial.println("Dispositivo iniciado.");
}

void loop() {
  VerificaConexoesWiFIEMQTT();

  // Lê os sensores
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  int valorLDR = analogRead(LDRPIN);

  // Mapeia o valor do LDR de 0-4095 para 0-100
  int luminosidade = map(valorLDR, 0, 4095, 0, 100); 

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Falha na leitura do DHT22!");
    return;
  }

  // Publica os dados
  MQTT.publish(TOPICO_LDR, String(luminosidade).c_str());
  MQTT.publish(TOPICO_DHT_TEMP, String(temperatura).c_str());
  MQTT.publish(TOPICO_DHT_UMIDADE, String(umidade).c_str());

  Serial.println("Dados enviados:");
  Serial.print("Luminosidade: "); Serial.println(luminosidade);
  Serial.print("Temperatura: "); Serial.println(temperatura);
  Serial.print("Umidade: "); Serial.println(umidade);

  delay(5000); 
}

void reconectWiFi() {
  if (WiFi.status() == WL_CONNECTED)
    return;
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado com sucesso na rede ");
  Serial.print(SSID);
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());
}


void VerificaConexoesWiFIEMQTT() {
  if (!MQTT.connected()) {
    Serial.println("MQTT Desconectado. Reconectando...");
    while (!MQTT.connect(topicPrefix)) { // Conecta com o nome do dispositivo
      Serial.print(".");
      delay(1000);
    }
    Serial.println("MQTT Conectado!");
  }
  reconectWiFi();
}
