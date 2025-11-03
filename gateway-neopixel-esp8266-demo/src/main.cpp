#include <Arduino.h>
#include <FastLED.h>
#include "config.h"

// === CONFIGURACIÓN DE PINES ===
#define NEOPIXEL_PIN_D1       D1
#define NEOPIXEL_PIN_D2       D2  
#define NEOPIXEL_PIN_D3       D3
#define SENSOR_PIN            D6  // Pin para sensor de flujo de agua

// === ARRAYS DE LEDs ===
// Software universal - doble lógica:
// D1 → leds_serie[3] (controla 3 LEDs en serie O solo el primero si está separado)
// D2 → leds_d2[1] (solo se usa en modo separado)
// D3 → leds_d3[1] (solo se usa en modo separado)
CRGB leds_serie[3];     // D1: 3 LEDs serie O 1 LED separado (usa leds_serie[0])
CRGB leds_d2[1];        // D2: 1 LED (solo modo separado)
CRGB leds_d3[1];        // D3: 1 LED (solo modo separado)

// === MODO FLUJO DE AGUA ===
volatile bool modoFlujo = false;
volatile unsigned long ultimoPulso = 0;
volatile int ledActual = 0;
volatile unsigned long contadorPulsos = 0;  // Contador de pulsos (para debug)
#define TIMEOUT_FLUJO 3000  // 3 segundos sin pulsos vuelve a modo normal
#define DEBOUNCE_MS 20      // Debounce reducido para detectar flujo rápido

// Interrupción para pulsos de agua con debounce
void IRAM_ATTR pulsosAgua() {
    unsigned long ahora = millis();
    
    // Ignorar si el pulso es muy rápido (debounce)
    if (ahora - ultimoPulso < DEBOUNCE_MS) {
        return;
    }
    
    contadorPulsos++;
    modoFlujo = true;
    ultimoPulso = ahora;
    ledActual = (ledActual + 1) % 3;  // Rotar entre 0, 1, 2
}

// Colores
const CRGB COLOR_TURQUESA = CRGB(64, 224, 208);
const CRGB COLOR_AZUL_MARINO = CRGB(0, 0, 139);
const CRGB COLOR_NARANJA = CRGB(255, 69, 0);

// === FUNCIONES SIMPLES ===
void apagarTodo() {
    // Apagar todos los LEDs (serie y separados)
    leds_serie[0] = CRGB::Black;
    leds_serie[1] = CRGB::Black;
    leds_serie[2] = CRGB::Black;
    leds_d2[0] = CRGB::Black;
    leds_d3[0] = CRGB::Black;
    FastLED.show();
}

// === MODO FLUJO DE AGUA ===
void mostrarFlujoAgua() {
    // Efecto secuencial: cada pulso enciende el siguiente LED
    // La velocidad de los pulsos = velocidad del efecto visual
    
    apagarTodo();
    
    // Encender SOLO el LED actual (efecto de movimiento)
    if (ledActual == 0) {
        leds_serie[0] = COLOR_TURQUESA;
    } else if (ledActual == 1) {
        leds_serie[1] = COLOR_TURQUESA;
        leds_d2[0] = COLOR_TURQUESA;
    } else if (ledActual == 2) {
        leds_serie[2] = COLOR_TURQUESA;
        leds_d3[0] = COLOR_TURQUESA;
    }
    
    FastLED.show();
}

void ponerNaranja(int strip) {
    if (strip == 1) {
        // Strip 1: D1 → siempre es leds_serie[0]
        leds_serie[0] = COLOR_NARANJA;
    } else if (strip == 2) {
        // Strip 2: leds_serie[1] (serie) Y leds_d2[0] (separado)
        leds_serie[1] = COLOR_NARANJA;
        leds_d2[0] = COLOR_NARANJA;
    } else if (strip == 3) {
        // Strip 3: leds_serie[2] (serie) Y leds_d3[0] (separado)
        leds_serie[2] = COLOR_NARANJA;
        leds_d3[0] = COLOR_NARANJA;
    }
    FastLED.show();
}

void ponerAzulMarino(int strip) {
    if (strip == 1) {
        // Strip 1: D1 → siempre es leds_serie[0]
        leds_serie[0] = COLOR_AZUL_MARINO;
    } else if (strip == 2) {
        // Strip 2: leds_serie[1] (serie) Y leds_d2[0] (separado)
        leds_serie[1] = COLOR_AZUL_MARINO;
        leds_d2[0] = COLOR_AZUL_MARINO;
    } else if (strip == 3) {
        // Strip 3: leds_serie[2] (serie) Y leds_d3[0] (separado)
        leds_serie[2] = COLOR_AZUL_MARINO;
        leds_d3[0] = COLOR_AZUL_MARINO;
    }
    FastLED.show();
}

void ponerTurquesa(int strip) {
    if (strip == 1) {
        // Strip 1: D1 → siempre es leds_serie[0]
        leds_serie[0] = COLOR_TURQUESA;
    } else if (strip == 2) {
        // Strip 2: leds_serie[1] (serie) Y leds_d2[0] (separado)
        leds_serie[1] = COLOR_TURQUESA;
        leds_d2[0] = COLOR_TURQUESA;
    } else if (strip == 3) {
        // Strip 3: leds_serie[2] (serie) Y leds_d3[0] (separado)
        leds_serie[2] = COLOR_TURQUESA;
        leds_d3[0] = COLOR_TURQUESA;
    }
    FastLED.show();
}

void encenderLogoCompleto() {
    // D1 serie: 3 LEDs con sus colores
    leds_serie[0] = COLOR_TURQUESA;
    leds_serie[1] = COLOR_AZUL_MARINO;
    leds_serie[2] = COLOR_NARANJA;
    // Separados: D2 y D3
    leds_d2[0] = COLOR_AZUL_MARINO;
    leds_d3[0] = COLOR_NARANJA;
    FastLED.show();
}

// === FUNCIONES PARA ILUMINAR TODO EL LOGO CON UN COLOR ===
void todoTurquesa() {
    leds_serie[0] = COLOR_TURQUESA;
    leds_serie[1] = COLOR_TURQUESA;
    leds_serie[2] = COLOR_TURQUESA;
    leds_d2[0] = COLOR_TURQUESA;
    leds_d3[0] = COLOR_TURQUESA;
    FastLED.show();
}

void todoAzulMarino() {
    leds_serie[0] = COLOR_AZUL_MARINO;
    leds_serie[1] = COLOR_AZUL_MARINO;
    leds_serie[2] = COLOR_AZUL_MARINO;
    leds_d2[0] = COLOR_AZUL_MARINO;
    leds_d3[0] = COLOR_AZUL_MARINO;
    FastLED.show();
}

void todoNaranja() {
    leds_serie[0] = COLOR_NARANJA;
    leds_serie[1] = COLOR_NARANJA;
    leds_serie[2] = COLOR_NARANJA;
    leds_d2[0] = COLOR_NARANJA;
    leds_d3[0] = COLOR_NARANJA;
    FastLED.show();
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    
    Serial.println("=== CONTROL NEOPIXEL CON SENSOR DE FLUJO ===");
    
    // Configurar pin de sensor con interrupción
    pinMode(SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulsosAgua, RISING);
    Serial.println("✅ Sensor de flujo en D6 - Modo: RISING (solo flancos de subida)");
    Serial.print("💡 Debounce: ");
    Serial.print(DEBOUNCE_MS);
    Serial.println("ms - ignora pulsos muy rápidos");
    
    Serial.print("LEDs por tira: ");
    Serial.println(NUM_LEDS_PER_STRIP);
    Serial.print("Brillo configurado: ");
    Serial.println(BRIGHTNESS);
    
    // Configurar LEDs - DOBLE LÓGICA CORREGIDA
    Serial.println("Configurando FastLED...");
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN_D1, GRB>(leds_serie, 3);
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN_D2, GRB>(leds_d2, 1);
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN_D3, GRB>(leds_d3, 1);
    Serial.println("CONFIGURACIÓN: D1→3serie, D2→1, D3→1");
    
    FastLED.setBrightness(BRIGHTNESS);
    
    // Test inicial rápido
    Serial.println("=== TEST INICIAL ===");
    leds_serie[0] = CRGB::Red;
    FastLED.show();
    delay(500);
    leds_serie[1] = CRGB::Green;
    leds_d2[0] = CRGB::Green;
    FastLED.show();
    delay(500);
    leds_serie[2] = CRGB::Blue;
    leds_d3[0] = CRGB::Blue;
    FastLED.show();
    delay(500);
    apagarTodo();
    
    Serial.println("✅ Sistema listo - Esperando señal...");
}

void presentacionNormal() {
    static unsigned long tiempoInicio = 0;
    static int paso = 0;
    static bool presentacionIniciada = false;
    
    // Iniciar presentación
    if (!presentacionIniciada) {
        Serial.println("=== FORMACIÓN DEL LOGO ===");
        tiempoInicio = millis();
        paso = 0;
        presentacionIniciada = true;
        apagarTodo();
    }
    
    unsigned long tiempoTranscurrido = millis() - tiempoInicio;
    
    // Secuencia simplificada - solo formación del logo
    if (paso == 0 && tiempoTranscurrido >= 500) {
        Serial.println("🔸 NARANJA: arriba");
        apagarTodo();
        ponerNaranja(1);
        paso = 1;
        tiempoInicio = millis();
    }
    else if (paso == 1 && tiempoTranscurrido >= 800) {
        Serial.println("🔸 NARANJA: centro");
        apagarTodo();
        ponerNaranja(2);
        paso = 2;
        tiempoInicio = millis();
    }
    else if (paso == 2 && tiempoTranscurrido >= 800) {
        Serial.println("🔸 NARANJA: abajo - SE QUEDA");
        apagarTodo();
        ponerNaranja(3);
        paso = 3;
        tiempoInicio = millis();
    }
    else if (paso == 3 && tiempoTranscurrido >= 1000) {
        Serial.println("🔷 AZUL MARINO: arriba");
        ponerAzulMarino(1);
        ponerNaranja(3);
        paso = 4;
        tiempoInicio = millis();
    }
    else if (paso == 4 && tiempoTranscurrido >= 800) {
        Serial.println("🔷 AZUL MARINO: centro - SE QUEDA");
        apagarTodo();
        ponerAzulMarino(2);
        ponerNaranja(3);
        paso = 5;
        tiempoInicio = millis();
    }
    else if (paso == 5 && tiempoTranscurrido >= 1000) {
        Serial.println("🔶 TURQUESA: arriba - SE QUEDA");
        ponerTurquesa(1);
        ponerAzulMarino(2);
        ponerNaranja(3);
        paso = 6;
        tiempoInicio = millis();
    }
    else if (paso == 6 && tiempoTranscurrido >= 1000) {
        Serial.println("✨ LOGO COMPLETO");
        encenderLogoCompleto();
        paso = 7;
        tiempoInicio = millis();
    }
    else if (paso == 7 && tiempoTranscurrido >= 5000) {
        Serial.println("🔄 REINICIANDO");
        presentacionIniciada = false;
        paso = 0;
    }
}

void loop() {
    static unsigned long ultimoReporte = 0;
    static unsigned long pulsosAnteriores = 0;
    
    // Reportar estado cada 5 segundos
    if (millis() - ultimoReporte > 5000) {
        Serial.print("📊 Estado: Modo=");
        Serial.print(modoFlujo ? "FLUJO" : "NORMAL");
        Serial.print(" | Pulsos totales=");
        Serial.print(contadorPulsos);
        Serial.print(" | LED actual=");
        Serial.println(ledActual);
        
        if (contadorPulsos > pulsosAnteriores) {
            Serial.print("🌊 ¡");
            Serial.print(contadorPulsos - pulsosAnteriores);
            Serial.println(" pulsos detectados en últimos 5 seg!");
        }
        
        pulsosAnteriores = contadorPulsos;
        ultimoReporte = millis();
    }
    
    // Verificar timeout del modo flujo
    if (modoFlujo && (millis() - ultimoPulso > TIMEOUT_FLUJO)) {
        modoFlujo = false;
        Serial.println("⏰ Timeout - Volviendo a modo normal");
    }
    
    // Ejecutar según el modo activo
    if (modoFlujo) {
        // MODO FLUJO: Mostrar LED según pulsos
        // Sin delay - la velocidad la marca el sensor!
        mostrarFlujoAgua();
        // Sin delay para máxima respuesta
    } else {
        // MODO NORMAL: Presentación del logo (sin delays bloqueantes)
        presentacionNormal();
        // Sin delay - la función usa millis() internamente
    }
}