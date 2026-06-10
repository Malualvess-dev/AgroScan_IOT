#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 15
#define DHTTYPE DHT22

#define SOIL_PIN 34
#define SCANNER_PIN 35

#define LED_VERDE 26
#define LED_VERMELHO 27
#define BUZZER 25

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* apiUrl =
"http://judicial-whiff-dodgy.ngrok-free.dev/scanner/dados";

String classificarCategoria(int valorScanner) {
  if (valorScanner <= 20) return "Solo";
  if (valorScanner <= 40) return "Planta";
  if (valorScanner <= 60) return "Verdura";
  if (valorScanner <= 80) return "Fruta";
  return "Legume";
}

String gerarStatus(String categoria, int umidadeSolo, float temperatura) {
  if (categoria == "Solo") {
    if (umidadeSolo < 30) return "Solo seco";
    if (umidadeSolo <= 70) return "Solo ideal";
    return "Solo muito umido";
  }

  if (categoria == "Planta" || categoria == "Verdura") {
    if (umidadeSolo < 30) return "Precisa de agua";
    if (temperatura > 35) return "Muito quente";
    return "Saudavel";
  }

  if (categoria == "Fruta" || categoria == "Legume") {
    if (temperatura > 35) return "Risco de deterioracao";
    return "Boa condicao";
  }

  return "Analisado";
}

void enviarParaAPI(String categoria, float temperatura, float umidadeAr, int umidadeSolo) {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado");
    return;
  }

  WiFiClient client;
  HTTPClient http;

  Serial.println("Conectando na API:");
  Serial.println(apiUrl);

  http.begin(client, apiUrl);
  http.setTimeout(15000);
  http.setReuse(false);

  http.addHeader("Content-Type", "application/json");
  http.addHeader("ngrok-skip-browser-warning", "true");

  String json = "{";
  json += "\"categoria\":\"" + categoria + "\",";
  json += "\"temperatura\":" + String(temperatura, 2) + ",";
  json += "\"umidadeAr\":" + String(umidadeAr, 2) + ",";
  json += "\"umidadeSolo\":" + String(umidadeSolo);
  json += "}";

  Serial.println("Enviando para API:");
  Serial.println(json);

  int httpCode = http.POST(json);

  Serial.print("HTTP Code: ");
  Serial.println(httpCode);

  if (httpCode > 0) {
    Serial.println("Resposta API:");
    Serial.println(http.getString());
  } else {
    Serial.print("Erro HTTP: ");
    Serial.println(http.errorToString(httpCode));
  }

  http.end();
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  dht.begin();
  Wire.begin(21, 22);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  WiFi.begin(ssid, password);

  display.setCursor(0, 0);
  display.println("AgroScan IoT");
  display.println("Conectando WiFi...");
  display.display();

  Serial.println("Conectando ao WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("IP ESP32: ");
  Serial.println(WiFi.localIP());

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi conectado!");
  display.println(WiFi.localIP());
  display.display();

  delay(2000);
}

void loop() {
  float temperatura = dht.readTemperature();
  float umidadeAr = dht.readHumidity();

  int leituraSolo = analogRead(SOIL_PIN);
  int umidadeSolo = map(leituraSolo, 0, 4095, 0, 100);

  int leituraScanner = analogRead(SCANNER_PIN);
  int valorScanner = map(leituraScanner, 0, 4095, 0, 100);

  String categoria = classificarCategoria(valorScanner);
  String status = gerarStatus(categoria, umidadeSolo, temperatura);

  bool alerta =
    status == "Solo seco" ||
    status == "Precisa de agua" ||
    status == "Muito quente" ||
    status == "Risco de deterioracao";

  if (alerta) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    tone(BUZZER, 1000);
  } else {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
  }

  display.clearDisplay();
  display.setCursor(0, 0);

  display.println("AgroScan IoT");
  display.println("----------------");

  display.print("Categoria: ");
  display.println(categoria);

  display.print("Temp: ");
  display.print(temperatura);
  display.println(" C");

  display.print("Solo: ");
  display.print(umidadeSolo);
  display.println("%");

  display.print("Status: ");
  display.println(status);

  if (alerta) {
    display.println("ALERTA!");
  } else {
    display.println("OK");
  }

  display.display();

  Serial.println("===== AgroScan =====");
  Serial.print("Categoria: ");
  Serial.println(categoria);
  Serial.print("Scanner: ");
  Serial.println(valorScanner);
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Umidade Ar: ");
  Serial.println(umidadeAr);
  Serial.print("Umidade Solo: ");
  Serial.println(umidadeSolo);
  Serial.print("Status: ");
  Serial.println(status);

  enviarParaAPI(categoria, temperatura, umidadeAr, umidadeSolo);

  Serial.println("====================");

  delay(5000);
}
