/*
 * Archivo de configuración para el proyecto NeoPixel ESP8266
 * Personaliza estos valores según tu hardware específico
 */

#ifndef CONFIG_H
#define CONFIG_H

// === CONFIGURACIÓN DE HARDWARE ===
#define NUM_LEDS_PER_STRIP    10    // Número de LEDs por tira
#define BRIGHTNESS            50    // Brillo inicial (0-255)
#define MAX_BRIGHTNESS        150   // Brillo máximo permitido

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