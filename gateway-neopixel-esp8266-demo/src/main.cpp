#include <Arduino.h>
#include <FastLED.h>

// === CONFIGURACIÓN ===
#define NEOPIXEL_PIN_D1       D1
#define NEOPIXEL_PIN_D2       D2  
#define NEOPIXEL_PIN_D3       D3
#define NUM_LEDS_PER_STRIP    10
#define BRIGHTNESS            255

// Arrays para LEDs
CRGB leds_d1[NUM_LEDS_PER_STRIP];
CRGB leds_d2[NUM_LEDS_PER_STRIP];
CRGB leds_d3[NUM_LEDS_PER_STRIP];

// Colores
const CRGB COLOR_TURQUESA = CRGB(64, 224, 208);
const CRGB COLOR_AZUL_MARINO = CRGB(0, 0, 139);
const CRGB COLOR_NARANJA = CRGB(255, 69, 0);

// === FUNCIONES SIMPLES ===
void apagarTodo() {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
        leds_d1[i] = CRGB::Black;
        leds_d2[i] = CRGB::Black;
        leds_d3[i] = CRGB::Black;
    }
    FastLED.show();
}

void ponerNaranja(int strip) {
    if (strip == 1) {
        for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
            leds_d1[i] = COLOR_NARANJA;
        }
    } else if (strip == 2) {
        for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
            leds_d2[i] = COLOR_NARANJA;
        }
    } else if (strip == 3) {
        for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
            leds_d3[i] = COLOR_NARANJA;
        }
    }
    FastLED.show();
}

void ponerAzulMarino(int strip) {
    if (strip == 1) {
        for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
            leds_d1[i] = COLOR_AZUL_MARINO;
        }
    } else if (strip == 2) {
        for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
            leds_d2[i] = COLOR_AZUL_MARINO;
        }
    } else if (strip == 3) {
        for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
            leds_d3[i] = COLOR_AZUL_MARINO;
        }
    }
    FastLED.show();
}

void ponerTurquesa(int strip) {
    if (strip == 1) {
        for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
            leds_d1[i] = COLOR_TURQUESA;
        }
    } else if (strip == 2) {
        for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
            leds_d2[i] = COLOR_TURQUESA;
        }
    } else if (strip == 3) {
        for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
            leds_d3[i] = COLOR_TURQUESA;
        }
    }
    FastLED.show();
}

void encenderLogoCompleto() {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
        leds_d1[i] = COLOR_TURQUESA;      // D1 = TURQUESA
        leds_d2[i] = COLOR_AZUL_MARINO;   // D2 = AZUL MARINO
        leds_d3[i] = COLOR_NARANJA;       // D3 = NARANJA
    }
    FastLED.show();
}

// === FUNCIONES PARA ILUMINAR TODO EL LOGO CON UN COLOR ===
void todoTurquesa() {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
        leds_d1[i] = COLOR_TURQUESA;
        leds_d2[i] = COLOR_TURQUESA;
        leds_d3[i] = COLOR_TURQUESA;
    }
    FastLED.show();
}

void todoAzulMarino() {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
        leds_d1[i] = COLOR_AZUL_MARINO;
        leds_d2[i] = COLOR_AZUL_MARINO;
        leds_d3[i] = COLOR_AZUL_MARINO;
    }
    FastLED.show();
}

void todoNaranja() {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
        leds_d1[i] = COLOR_NARANJA;
        leds_d2[i] = COLOR_NARANJA;
        leds_d3[i] = COLOR_NARANJA;
    }
    FastLED.show();
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    
    Serial.println("=== PRESENTACIÓN SIMPLE DEL LOGO ===");
    
    // Configurar LEDs
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN_D1, GRB>(leds_d1, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN_D2, GRB>(leds_d2, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN_D3, GRB>(leds_d3, NUM_LEDS_PER_STRIP);
    FastLED.setBrightness(BRIGHTNESS);
    
    apagarTodo();
    delay(1000);
    
    Serial.println("Iniciando presentación...");
    
    // === NUEVA SECUENCIA: TODO EL LOGO CON CADA COLOR ===
    Serial.println("=== SECUENCIA DE COLORES COMPLETOS ===");
    
    Serial.println("🔶 TODO EL LOGO - TURQUESA");
    apagarTodo();
    todoTurquesa();
    delay(2000);
    
    Serial.println("🔷 TODO EL LOGO - AZUL MARINO");
    apagarTodo();
    todoAzulMarino();
    delay(2000);
    
    Serial.println("🔸 TODO EL LOGO - NARANJA");
    apagarTodo();
    todoNaranja();
    delay(2000);
    
    Serial.println("=== AHORA LA PRESENTACIÓN DE BAJADA ===");
    
    // === PRESENTACIÓN HARDCODED SIMPLE ===
    
    // PARTE 1: NARANJA baja de arriba → centro → abajo
    Serial.println("🔸 NARANJA: arriba");
    apagarTodo();
    ponerNaranja(1);  // D1 = NARANJA
    delay(1000);
    
    Serial.println("🔸 NARANJA: centro");
    apagarTodo();
    ponerNaranja(2);  // D2 = NARANJA
    delay(1000);
    
    Serial.println("🔸 NARANJA: abajo - SE QUEDA");
    apagarTodo();
    ponerNaranja(3);  // D3 = NARANJA - SE QUEDA
    delay(1500);
    
    // PARTE 2: AZUL MARINO baja de arriba → centro
    Serial.println("🔷 AZUL MARINO: arriba");
    ponerAzulMarino(1);  // D1 = AZUL MARINO (mantener naranja en D3)
    ponerNaranja(3);     // Mantener D3 = NARANJA
    delay(1000);
    
    Serial.println("🔷 AZUL MARINO: centro - SE QUEDA");
    apagarTodo();
    ponerAzulMarino(2);  // D2 = AZUL MARINO - SE QUEDA
    ponerNaranja(3);     // Mantener D3 = NARANJA
    delay(1500);
    
    // PARTE 3: TURQUESA aparece arriba
    Serial.println("🔶 TURQUESA: arriba - SE QUEDA");
    ponerTurquesa(1);    // D1 = TURQUESA - SE QUEDA
    ponerAzulMarino(2);  // Mantener D2 = AZUL MARINO
    ponerNaranja(3);     // Mantener D3 = NARANJA
    delay(2000);
    
    Serial.println("✨ LOGO COMPLETO: D1=TURQUESA, D2=AZUL MARINO, D3=NARANJA");
    
    // PARTE 4: FLASHES del logo completo
    Serial.println("💡 FLASHES DEL LOGO");
    for (int i = 0; i < 6; i++) {
        // ENCENDER todo el logo
        encenderLogoCompleto();
        Serial.println("   LOGO ON");
        delay(300);
        
        // APAGAR todo el logo
        apagarTodo();
        Serial.println("   LOGO OFF");
        delay(300);
    }
    
    // PARTE 5: PAUSA FINAL con logo encendido
    encenderLogoCompleto();
    Serial.println("🎯 LOGO ENCENDIDO - Pausa final 4 segundos");
    delay(4000);
    
    Serial.println("🔄 PRESENTACIÓN TERMINADA - Se repite");
}

void loop() {
    // Repetir la presentación cada 20 segundos
    delay(5000);
    setup();  // Volver a ejecutar la presentación
}