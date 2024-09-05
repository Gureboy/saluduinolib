#include "PageManager.h"

void PageManager::setupPages(ESP8266WebServer& server, LoginManager& loginManager) {
    // Página de Inicio
    server.on("/", [&]() {
        if (!loginManager.isAuthenticated()) {
            server.sendHeader("Location", "/login", true);
            server.send(302, "text/plain", "");
            return;
        }
        String page = "<html><body><h1>Inicio</h1>";
        page += "<p><a href='/agregar'>Agregar Paciente</a></p>";
        page += "<p><a href='/ver'>Ver Pacientes</a></p>";
        page += "<p><a href='/eliminar'>Eliminar Paciente</a></p>";
        page += "<p><a href='/opciones'>Opciones Avanzadas</a></p>";
        page += "<p><a href='/hub'>Hub Enfermero</a></p>";
        page += "<p><a href='/logout'>Cerrar sesión</a></p>";
        page += "</body></html>";
        server.send(200, "text/html", page);
    });

    // Página de Login
    server.on("/login", [&]() {
        String page = "<html><body><h1>Login</h1><form method='POST' action='/login'>";
        page += "Usuario: <input type='text' name='username'><br>";
        page += "Contraseña: <input type='password' name='password'><br>";
        page += "<input type='submit' value='Login'></form></body></html>";
        server.send(200, "text/html", page);
    });

    server.on("/login", HTTP_POST, [&]() {
        String username = server.arg("username");
        String password = server.arg("password");
        if (loginManager.login(username, password)) {
            server.sendHeader("Location", "/", true);
            server.send(302, "text/plain", "");
        } else {
            server.send(200, "text/html", "<html><body><h1>Login fallido</h1></body></html>");
        }
    });

    // Página para agregar pacientes
    server.on("/agregar", [&]() {
        if (!loginManager.isAuthenticated()) {
            server.sendHeader("Location", "/login", true);
            server.send(302, "text/plain", "");
            return;
        }
        String page = "<html><body><h1>Agregar Paciente</h1>";
        page += "<form method='POST' action='/agregar'>";
        page += "Nombre: <input type='text' name='nombre'><br>";
        page += "Edad: <input type='number' name='edad'><br>";
        page += "<input type='submit' value='Agregar'></form></body></html>";
        server.send(200, "text/html", page);
    });

    // Página para ver pacientes
    server.on("/ver", [&]() {
        if (!loginManager.isAuthenticated()) {
            server.sendHeader("Location", "/login", true);
            server.send(302, "text/plain", "");
            return;
        }
        String page = "<html><body><h1>Ver Pacientes</h1>";
        page += "</body></html>";
        server.send(200, "text/html", page);
    });

    // Similarmente, define las rutas para las demás páginas...
}
