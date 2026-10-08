#ifndef INDEX_HTML_H
#define INDEX_HTML_H

#include <Arduino.h>

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no">
  <title>Controle Robô</title>
  <style>
    body {
      background-color: #111;
      color: white;
      text-align: center;
      font-family: Arial, sans-serif;
      margin: 0;
      padding: 10px;
    }
    .header {
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 5px;
      margin-top: 10px;
      margin-bottom: 15px;
    }
    .logo {
      width: 45px;
      height: auto;
    }
    .dpad {
      display: inline-block;
      margin-top: 10px;
    }
    .row {
      display: flex;
      justify-content: center;
    }
    .btn {
      background-color: #d32f2f;
      border: none;
      color: white;
      font-size: 32px;
      border-radius: 15px;
      margin: 6px;
      width: 80px;
      height: 80px;
      touch-action: manipulation;
      cursor: pointer;
      user-select: none;
    }
    .btn:active {
      background-color: #9a0007;
    }
    .stream-container {
      margin: 10px auto;
      max-width: 100%;
    }
    .stream-container img {
      width: 100%;
      max-width: 400px;
      border-radius: 10px;
    }
  </style>
</head>
<body>

  <div class="header">
    <img class="logo" alt="Titans" src="data:image/png;base64,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">
    <h2>Controle ESP32</h2>
  </div>

  <div class="dpad">
    <div class="row">
      <button class="btn" onpointerdown="sendCommand('F')" onpointerup="sendCommand('S')">&#9650;</button>
    </div>
    <div class="row">
      <button class="btn" onpointerdown="sendCommand('L')" onpointerup="sendCommand('S')">&#9664;</button>
      <button class="btn" onpointerdown="sendCommand('S')">&#9632;</button>
      <button class="btn" onpointerdown="sendCommand('R')" onpointerup="sendCommand('S')">&#9654;</button>
    </div>
    <div class="row">
      <button class="btn" onpointerdown="sendCommand('B')" onpointerup="sendCommand('S')">&#9660;</button>
    </div>
  </div>

  <script>
    function sendCommand(cmd) {
      fetch('/action?go=' + cmd).catch(() => {});
    }
  </script>
</body>
</html>
)rawliteral";

#endif
