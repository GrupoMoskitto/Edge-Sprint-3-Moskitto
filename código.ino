// Autores: João Vitor de Matos, Gabriel Couto, Gabriel Kato, Ana Luiza
// Grupo moskitto - FIAP
// Resumo: Display OLED com ESP32-C3 que realiza requisição HTTP GET para o Orion Context Broker e a cada 20 segundos
// atualiza o texto exibido conforme o valor do atributo text da entidade Display001.

#include <U8g2lib.h>
#include <WiFi.h>
#include <HTTPClient.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(
  U8G2_R0, /* clock=*/ 5, /* data=*/ 4, /* reset=*/ U8X8_PIN_NONE
);

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// URL direta para o atributo 'text' da entidade Display001
const char* serverName = "http://20.197.240.85:1026/v2/entities/Display001/attrs/text";

String textoAtual = "Esperando...";

void requisitarTexto(bool usarCabecalho = true) {
  HTTPClient http;
  http.begin(serverName);

  if (usarCabecalho) {
    http.addHeader("Fiware-Service", "default");
    http.addHeader("Fiware-ServicePath", "/");
  }

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("Código HTTP: ");
    Serial.println(httpResponseCode);

    String payload = http.getString();
    Serial.println("Resposta: " + payload);

    // Extrai valor do JSON no formato: {"value":"Texto Atual","type":"String"}
    int startIndex = payload.indexOf("\"value\":\"") + 9;
    int endIndex = payload.indexOf("\"", startIndex);

    if (startIndex > 8 && endIndex > startIndex) {
      textoAtual = payload.substring(startIndex, endIndex);
    } else {
      textoAtual = "Erro JSON";
    }

  } else {
    Serial.print("Erro HTTP: ");
    Serial.println(httpResponseCode);
    textoAtual = "Erro na conexão";
  }

  http.end();

  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB08_tr);
  int largura = u8g2.getStrWidth(textoAtual.c_str());
  int x = (128 - largura) / 2;
  u8g2.drawStr(x, 35, textoAtual.c_str());
  u8g2.sendBuffer();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado!");
}

void loop() {
  requisitarTexto();
  delay(20000);
}
