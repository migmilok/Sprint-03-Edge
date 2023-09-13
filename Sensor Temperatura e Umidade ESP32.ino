#include "DHT.h"
#include <HTTPClient.h>
#include "WiFi.h"

char serverAddress[] = "https://api.tago.io/data";  // TagoIO address
char contentHeader[] = "application/json";
char tokenHeader[] = "TOKEN"; // TagoIO Token
const char wifiSsid[] = " ";  // WiFi Name
const char wifiPass[] = " ";  //WiFi Password

WiFiClient wifia;
HTTPClient client;
int status = WL_IDLE_STATUS;
int dhtHumidity;
int  dhtTemperature;

// Configuração DHT
#define DHTPIN 5     // Pino conectado ao DHT
#define DHTTYPE DHT22   // Definindo o modelo do DHT
DHT dht(DHTPIN, DHTTYPE);

void init_wifi(void) {
  Serial.println("Conectando Wifi...");
  Serial.print("SSID: ");
  Serial.println(wifiSsid);
  Serial.print("PASS: ");
  Serial.println(wifiPass);
  WiFi.begin(wifiSsid, wifiPass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Conectado!");
  Serial.print("IP is ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);

  dht.begin();
  init_wifi();
}

void loop() {
    char anyData[30];
    char postData[300];
    char anyData1[30];
    char bAny[30];
    int statusCode=0;

  
  float h = dhtHumidity++;  // Usado para teste
  //float h = dht.readHumidity();

  float t = dhtTemperature++;  // Usado para teste
  //float t = dht.readTemperature();

  send_temperature();
  send_humidity();
  delay(10000);
}

void send_temperature(void){
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;
  strcpy(postData, "{\n\t\"variable\": \"Temperature\",\n\t\"value\": ");
  dtostrf(dhtTemperature, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);
  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}

void send_humidity(void) {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"Humidity\",\n\t\"value\": ");
  dtostrf(dhtHumidity, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"%\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(5000);
  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}
