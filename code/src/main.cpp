#include <Arduino.h>
#include "camera_config.h"
#include "motor_control.h"

// ======================================================================
// ESCOLHA O MODO DE CONTROLE AQUI:
// Se a linha abaixo não tiver barras (//), o robô usa DABBLE (Bluetooth)
// Se você colocar barras (//#define USE_DABBLE), usa WEB (Wi-Fi)
// ======================================================================
#define USE_DABBLE 


#ifdef USE_DABBLE
  // --- Configurações para o Dabble (Bluetooth) ---
  #define CUSTOM_SETTINGS
  #define INCLUDE_GAMEPAD_MODULE
  #include <DabbleESP32.h>
#else
  // --- Configurações para o WebServer (Wi-Fi) ---
  #include <WiFi.h>
  #include <WebServer.h>
  #include "index_html.h"
  
  const char *ssid = "ESP32_Robot";
  const char *password = "12345678";
  WebServer controlServer(8080);

  void handleRoot() {
    controlServer.send_P(200, "text/html", INDEX_HTML);
  }

  void handleAction() {
    if (controlServer.hasArg("go")) {
      char cmd = controlServer.arg("go")[0];
      handleMotorCommand(cmd);
    }
    controlServer.send(200, "text/plain", "OK");
  }
#endif


void setup() {
  Serial.begin(115200);

  // Inicializa motores e câmera
  initMotors();
  if (initCamera() != ESP_OK) {
    Serial.println("Erro ao inicializar a camera!");
  }

#ifdef USE_DABBLE
  // Setup do Dabble
  Serial.println("Iniciando modo Dabble (Bluetooth) com Joystick Analógico...");
  Dabble.begin("ESP32_Robot_BT"); // Nome que vai aparecer no Bluetooth
#else
  // Setup do WebServer
  Serial.println("Iniciando modo Web (Wi-Fi)...");
  WiFi.softAP(ssid, password);
  Serial.print("IP do AP: ");
  Serial.println(WiFi.softAPIP());
  
  controlServer.on("/", HTTP_GET, handleRoot);
  controlServer.on("/action", HTTP_GET, handleAction);
  controlServer.begin();
  Serial.println("Servidor web iniciado na porta 8080!");
#endif
}

void loop() {
#ifdef USE_DABBLE
  // Loop do Dabble
  Dabble.processInput(); // Atualiza os dados recebidos do celular
  
  // O Dabble retorna o ângulo do Joystick (0 a 360) e o raio/distância (0 a 7)
  float angle = GamePad.getAngle();
  float radius = GamePad.getRadius();

  // Verifica se o joystick foi movido além do centro (zona morta)
  if (radius > 1.5) {
    // 90 graus é pra cima, 270 é pra baixo, 180 é esquerda, 0/360 é direita
    if (angle > 45 && angle <= 135) {
      handleMotorCommand('F');  // Frente
    } 
    else if (angle > 135 && angle <= 225) {
      handleMotorCommand('L');  // Esquerda
    } 
    else if (angle > 225 && angle <= 315) {
      handleMotorCommand('B');  // Trás
    } 
    else {
      handleMotorCommand('R');  // Direita (graus restantes: 315 a 360 e 0 a 45)
    }
  } else {
    handleMotorCommand('S'); // Para o motor se o dedo soltar o analógico
  }

#else
  // Loop do WebServer
  controlServer.handleClient();
#endif
}
