#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#define RXp2 16
#define TXp2 17

const char *ssid = "WIFI_name";
const char *password = "WIFI_password";

WebServer server(80);
float temp = 0;
float um = 0;
char per = '%';//HTML 

void handleRoot() {
  char msg[3000];

  snprintf(msg, 3000,
        "<html lang='pt-bt'>\
  <head>\
      <meta http-equiv='refresh' content='4'/>\
      <meta charset='UTF-8'>\
      <meta name='viewport' content='width=device-width, initial-scale=1.0'>\
      <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css' integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin=''anonymous'>\
      <link rel='shortcut icon' href='pacote-projeto-d010/imagens/favicon.ico' type='image/x-icon'>\
      <title>IKAÁ</title>\
      <style>\
        @charset 'UTF-8';\
        @import url('https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;500;600&display=swap');\    
        :root{\
            --cor0: #ebe5c5;\
            --cor1: #038548;\
            --cor2: #063d1e;\
        }\
        *{\
            margin: 0px;\
            padding: 0px;\
            font-family: 'Poppins', sans-serif;\
        }\
        body{\
            background-color: var(--cor0);\
        }\
        #temp{\
            color: red;\
        }\
        #umi{\
            color: #00add6;\
        }\
        header{\
            background-color: var(--cor1);\
            text-align:left;\
            display: flex;\
        }\
        header > h1{\
            color: white;\
            padding: 10px 0px 10px 10px;\
            font-weight: normal;\
            font-size: 2em;\
            text-shadow: 2px 2px 0px rgba(0, 0, 0, 0.178);\
        }\
        main{background-color: white;text-align: center;min-width: 320px;max-width: 600px;margin: auto;padding: 20px;box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.425);border-bottom-left-radius: 10px;border-bottom-right-radius: 10px;font-weight:bolder;}\
        main h1{\
            color: var(--cor2);\
            font-size: 1.4em;\
        }\
        main p{\
            margin: 15px 0px 15px 0px;\
            font-size: 2em;\
            line-height: 2em; \
        }\
      </style>\
  </head>\
  <body>\
      <header>\
          <h1>IKAÁ</h1>\
      </header>\
      <main>\
          <h1>SENSOR 1</h1>\
          <p>\
              <i class='fas fa-thermometer-half' style='color: #059e8a;'></i> \
              Temperatura <span id='temp'>%.2f</span><sup>o</sup>C\
          </p>\
          <p>\
              <i class='fas fa-tint' style='color: #00add6;'></i>\
              Umidade <span id='umi'>%.2f</span> %c\
          </p>\
      </main>\
  </body>\
  </html>", temp, um, per);
;
  server.send(200, "text/html", msg);
}

void setup(void) {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}
void loop(void) {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');  // Lê a linha do Arduino
    int commaIndex = data.indexOf(',');
    if (commaIndex != -1) {
      temp = data.substring(0, commaIndex).toFloat();  // Pega a temperatura
      um = data.substring(commaIndex + 1).toFloat();   // Pega a umidade
    }
  }

  server.handleClient();
  delay(2); 
}
