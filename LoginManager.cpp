#include "LoginManager.h"
#include <ESP8266WebServer.h>

extern ESP8266WebServer server; // Asegúrate de tener una instancia de ESP8266WebServer

const int MAX_LOGIN_ATTEMPTS = 5;
const unsigned long BLOCK_TIME_MS = 1800000; // 30 minutos en milisegundos

LoginManager::LoginManager() : loginAttempts(0), authenticated(false), blockStartTime(0) {}

bool LoginManager::login(const String& username, const String& password) {
    unsigned long currentMillis = millis();

    if (authenticated) {
        return true; // Ya está autenticado
    }

    if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
        if (currentMillis - blockStartTime < BLOCK_TIME_MS) {
            return false; // Está bloqueado
        } else {
            // Restablecer intentos después del tiempo de bloqueo
            loginAttempts = 0;
        }
    }

    if (username == "Saluduino" && password == "SaluduinoWeb") {
        authenticated = true;
        loginAttempts = 0;
        return true;
    } else {
        loginAttempts++;
        if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
            blockStartTime = currentMillis; // Guardar tiempo de inicio del bloqueo
        }
        return false;
    }
}

bool LoginManager::isAuthenticated() const {
    return authenticated;
}

void LoginManager::logout() {
    authenticated = false;
}

void LoginManager::readPage() {
    String page = R"rawliteral(
    <!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Saluduino System Login</title>
  <style>
    @import "https://fonts.googleapis.com/css?family=Ubuntu:400,700italic|Cabin:400";

    /* Estilos Globales */
    * {
      box-sizing: border-box;
    }

    html {
      height: 100%;
      width: 100%;
    }

    body {
      margin: 0;
      padding: 0;
      height: 100%;
      width: 100%;
      background: linear-gradient(135deg, #6e6e6e, #4d4d4d);
      background-size: cover;
      font-size: 10px;
      text-align: center;
    }

    /* Logo */
    #logo {
      animation: logo-entry 4s ease-in;
      width: 500px;
      margin: 0 auto; /* Centra el logo horizontalmente */
      position: relative;
      z-index: 40;
      padding-top: 50px; /* Ajusta la posición vertical del logo */
    }

    h1 {
      animation: text-glow 2s ease-out infinite alternate;
      font-family: 'Ubuntu', sans-serif;
      color: #00a4a2;
      font-size: 48px;
      font-size: 4.8rem;
      font-weight: bold;
      position: relative;
      text-shadow: 0 0 10px #000, 0 0 20px #000, 0 0 30px #000, 0 0 40px #000, 0 0 50px #000, 0 0 60px #000, 0 0 70px #000;
    }

    /* Formulario de Login */
    .stark-login {
      margin: 0 auto;
      width: 500px;
      position: relative;
      z-index: 4;
      padding-top: 20px; /* Espacio entre el logo y el formulario */
    }

    .stark-login form {
      animation: form-entry 3s ease-in-out;
      background: linear-gradient(#333, #222);
      border: 6px solid #00a4a2;
      box-shadow: 0 0 15px #00fffd;
      border-radius: 5px;
      height: 220px;
      position: relative;
      transition: 1s all;
    }

    .stark-login form:hover {
      border: 6px solid #00fffd;
      box-shadow: 0 0 25px #00fffd;
      transition: 1s all;
    }

    .stark-login input {
      background: linear-gradient(#333, #222);
      border: 1px solid #444;
      border-radius: 5px;
      box-shadow: 0 2px 0 #000;
      color: #888;
      display: block;
      font-family: 'Cabin', helvetica, arial, sans-serif;
      font-size: 13px;
      height: 40px;
      margin: 20px auto 10px;
      padding: 0 10px;
      text-shadow: 0 -1px 0 #000;
      width: 100%; /* Asegura que los campos de entrada ocupen todo el ancho del formulario */
      max-width: 400px; /* Ajusta el ancho máximo del formulario */
    }

    .stark-login input:focus {
      animation: box-glow 1s ease-out infinite alternate;
      background: linear-gradient(#333933, #222922);
      border-color: #00fffc;
      box-shadow: 0 0 5px rgba(0, 255, 253, .2), inset 0 0 5px rgba(0, 255, 253, .1), 0 2px 0 #000;
      color: #efe;
      outline: none;
    }

    .stark-login input:invalid {
      border: 2px solid red;
      box-shadow: 0 0 5px rgba(255, 0, 0, .2), inset 0 0 5px rgba(255, 0, 0, .1), 0 2px 0 #000;
    }

    .stark-login button {
      animation: input-entry 3s ease-in;
      background: linear-gradient(#333, #222);
      border: 1px solid #444;
      border-radius: 5px;
      box-shadow: 0 2px 0 #000;
      color: #fff;
      display: block;
      font-family: 'Cabin', helvetica, arial, sans-serif;
      font-size: 13px;
      height: 40px;
      line-height: 40px;
      margin: 20px auto;
      padding: 0;
      text-shadow: 0 -1px 0 #000;
      width: 100%; /* Asegura que el botón ocupe todo el ancho del formulario */
      max-width: 400px; /* Ajusta el ancho máximo del botón */
      transition: 1s all;
    }

    .stark-login button:hover,
    .stark-login button:focus {
      background: linear-gradient(#393939, #292929);
      color: #00fffc;
      outline: none;
      transition: 1s all;
    }

    .stark-login button:active {
      background: linear-gradient(#393939, #292929);
      box-shadow: 0 1px 0 #000, inset 1px 0 1px #222;
      top: 1px;
    }

    /* Círculo de Fondo */
    #circle1 {
      animation: circle1 4s linear infinite, circle-entry 6s ease-in-out;
      background: #000;
      border-radius: 50%;
      border: 10px solid #00a4a2;
      box-shadow: 0 0 0 2px black, 0 0 0 6px #00fffd;
      height: 500px;
      width: 500px;
      position: absolute;
      top: 50%;
      left: 50%;
      margin-top: -250px;
      margin-left: -250px;
      overflow: hidden;
      opacity: 0.4;
      z-index: -3;
    }

    #inner-cirlce1 {
      background: #000;
      border-radius: 50%;
      border: 36px solid #00fffd;
      height: 460px;
      width: 460px;
      margin: 10px;
    }

    /* Malla de Hexágonos */
    .hexagons {
      position: absolute;
      top: 0;
      left: 0;
      height: 100%;
      width: 100%;
      overflow: hidden;
      z-index: -2;
    }

    .hexagon {
      position: absolute;
      width: 100px;
      height: 100px;
      background-color: rgba(255, 255, 255, 0.1);
      clip-path: polygon(50% 0%, 100% 25%, 100% 75%, 50% 100%, 0% 75%, 0% 25%);
      border: 1px solid rgba(255, 255, 255, 0.3);
    }

    /* Animaciones */
    @keyframes logo-entry {
      0% { opacity: 0; }
      80% { opacity: 0; }
      100% { opacity: 1; }
    }

    @keyframes circle-entry {
      0% { opacity: 0; }
      20% { opacity: 0; }
      100% { opacity: 0.4; }
    }

    @keyframes input-entry {
      0% { opacity: 0; }
      90% { opacity: 0; }
      100% { opacity: 1; }
    }

    @keyframes form-entry {
      0% {
        height: 0;
        width: 0;
        opacity: 0;
        padding: 0;
      }
      20% {
        height: 0;
        border: 1px solid #00a4a2;
        width: 0;
        opacity: 0;
        padding: 0;
      }
      40% {
        width: 0;
        height: 220px;
        border: 6px solid #00a4a2;
        opacity: 1;
        padding: 0;
      }
      100% {
        height: 220px;
        width: 500px;
      }
    }

    @keyframes box-glow {
      0% {
        border-color: #00b8b6;
        box-shadow: 0 0 5px rgba(0, 255, 253, .2), inset 0 0 5px rgba(0, 255, 253, .1), 0 2px 0 #000;
      }
      100% {
        border-color: #00fffc;
        box-shadow: 0 0 10px rgba(0, 255, 253, .4), inset 0 0 20px rgba(0, 255, 253, .2), 0 2px 0 #000;
      }
    }

    @keyframes text-glow {
      0% {
        color: #00a4a2;
        text-shadow: 0 0 10px #000, 0 0 20px #000, 0 0 30px #000, 0 0 40px #000, 0 0 50px #000, 0 0 60px #000, 0 0 70px #000;
      }
      100% {
        color: #00fffd;
        text-shadow: 0 0 10px #00fffd, 0 0 20px #00fffd, 0 0 30px #00fffd, 0 0 40px #00fffd, 0 0 50px #00fffd, 0 0 60px #00fffd, 0 0 70px #00fffd;
      }
    }

    /* Posiciona los hexágonos aleatoriamente */
    .hexagon:nth-child(1) { top: 10%; left: 10%; }
    .hexagon:nth-child(2) { top: 20%; left: 20%; }
    .hexagon:nth-child(3) { top: 30%; left: 30%; }
    .hexagon:nth-child(4) { top: 40%; left: 40%; }
    .hexagon:nth-child(5) { top: 50%; left: 50%; }
    .hexagon:nth-child(6) { top: 60%; left: 60%; }
    .hexagon:nth-child(7) { top: 70%; left: 70%; }
    .hexagon:nth-child(8) { top: 80%; left: 80%; }
    .hexagon:nth-child(9) { top: 90%; left: 90%; }
  </style>
</head>
<body>
  <div id="logo">
    <h1>SerraIOT Systems</h1>
  </div>

  <div class="stark-login">
    <form action="/login" method="post">
      <input type="text" name="username" placeholder="Usuario" required>
      <input type="password" name="password" placeholder="Contraseña" required>
      <button type="submit">Entrar</button>
    </form>
  </div>

  <div id="circle1">
    <div id="inner-cirlce1"></div>
  </div>

  <div class="hexagons">
    <!-- Añade más hexágonos si es necesario -->
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
  </div>
</body>
</html>
    )rawliteral";

    server.send(200, "text/html", page);
}

