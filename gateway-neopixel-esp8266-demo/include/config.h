/*
 * Archivo de configuración para el proyecto NeoPixel ESP8266
 * Personaliza estos valores según tu hardware específico
 */

#ifndef CONFIG_H
#define CONFIG_H

// === CONFIGURACIÓN DE HARDWARE ===
// El mismo software funciona con dos configuraciones de hardware:
// - Opción 1: 3 pines separados (D1, D2, D3) con 10 LEDs cada uno
// - Opción 2: 1 pin único (D1) con 30 LEDs en serie
// Solo cambia el cableado físico, el software es idéntico

#define NUM_LEDS_PER_STRIP    1     // Número de LEDs por sección lógica (1 LED por sección)
#define BRIGHTNESS            255   // Brillo al MÁXIMO (0-255)
#define MAX_BRIGHTNESS        255   // Brillo máximo permitido

// === SOFTWARE UNIVERSAL ===
// No hay configuraciones que cambiar - el mismo código funciona siempre

// === CONFIGURACIÓN DE EFECTOS ===
#define ANIMATION_SPEED       100   // Velocidad de animación (ms)
#define AUTO_CHANGE_INTERVAL  10000 // Cambio automático de efecto (ms)
#define SPARKLE_DENSITY       3     // Densidad de destellos (0-10)

// === CONFIGURACIÓN DE COLORES ===
// Puedes personalizar estos colores modificando los valores RGB
#define CUSTOM_RED      255, 0, 0
#define CUSTOM_GREEN    0, 255, 0
#define CUSTOM_BLUE     0, 0, 255
#define CUSTOM_YELLOW   255, 255, 0
#define CUSTOM_MAGENTA  255, 0, 255
#define CUSTOM_CYAN     0, 255, 255
#define CUSTOM_WHITE    255, 255, 255
#define CUSTOM_ORANGE   255, 165, 0
#define CUSTOM_PURPLE   128, 0, 128

// === CONFIGURACIÓN DE COMUNICACIÓN ===
#define SERIAL_BAUD_RATE      115200
#define DEBUG_ENABLED         true

// === CONFIGURACIÓN AVANZADA ===
#define LED_TYPE              WS2812B
#define COLOR_ORDER           GRB
#define NUM_EFFECTS           6

#endif // CONFIG_H