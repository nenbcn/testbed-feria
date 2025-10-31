
#include <Arduino.h>
#include <FastLED.h>


// === CORRESPONDENCIA ENTRE PINES, BOTONES Y LEDS ===
// Botón Inicio/Paro:              Pin D2, LED 1
// Botón Flat:                     Pin D5, LED 2
// Botón Reducción de Centrifugado: Pin D4, LED 3
// LED 4: Lavado (automático)
// LED 5: Aclarado (automático)
// LED 6: Centrifugado (automático)

#define PIN_BOTON_INICIO      D2
#define PIN_BOTON_FLAT        D5
#define PIN_BOTON_REDUCCION   D4
#define NEOPIXEL_PIN          D1
#define VALVE_PIN             D6
#define NUM_PIXELS            6

#define LED_INICIO            0   // LED 1
#define LED_FLAT              1   // LED 2
#define LED_REDUCCION         2   // LED 3
#define LED_LAVADO            5   // LED 4
#define LED_ACLARADO          4   // LED 5
#define LED_CENTRIFUGADO      3   // LED 6

// Colores
const CRGB COLOR_ROJO   = CRGB::Red;
const CRGB COLOR_VERDE  = CRGB::Green;
const CRGB COLOR_AZUL   = CRGB::Blue;
const CRGB COLOR_TURQUESA = CRGB(0, 255, 255); // Turquesa para centrifugado
const CRGB COLOR_NEGRO  = CRGB::Black;

CRGB leds[NUM_PIXELS];

// Estados de los LEDs de control
bool estadoInicio = false;      // false = rojo, true = verde
bool estadoFlat = false;
bool estadoReduccion = false;

// Debounce
unsigned long lastDebounce[3] = {0, 0, 0};
const unsigned long debounceDelay = 80;

// Estado de ciclo automático
bool cicloEnCurso = false;
unsigned long cicloTimestamp = 0;
int fase = 0;
int subfase = 0;
int repeticionesLavado = 0;

void setLedControl(int idx, bool activo) {
    leds[idx] = activo ? COLOR_VERDE : COLOR_ROJO;
    FastLED.show();
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(PIN_BOTON_REDUCCION, INPUT_PULLUP);
    pinMode(PIN_BOTON_FLAT, INPUT_PULLUP);
    pinMode(PIN_BOTON_INICIO, INPUT_PULLUP);
    pinMode(VALVE_PIN, OUTPUT);
    digitalWrite(VALVE_PIN, LOW);
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN, GRB>(leds, NUM_PIXELS);
    FastLED.setBrightness(255);
    // Inicializar todos los LEDs de control en rojo
    for (int i = 0; i < NUM_PIXELS; i++) leds[i] = COLOR_NEGRO;
    setLedControl(LED_REDUCCION, false);
    setLedControl(LED_FLAT, false);
    setLedControl(LED_INICIO, false);
    leds[LED_LAVADO] = COLOR_NEGRO;
    leds[LED_ACLARADO] = COLOR_NEGRO;
    leds[LED_CENTRIFUGADO] = COLOR_NEGRO;
    FastLED.show();
    Serial.println("Sistema listo. Esperando interacción.");
}

void loop() {
    // --- Gestión de botones con debounce ---
    static bool lastBtn[3] = {HIGH, HIGH, HIGH};
    bool btn[3] = {
        digitalRead(PIN_BOTON_REDUCCION), // Botón Reducción de Centrifugado
        digitalRead(PIN_BOTON_FLAT),      // Botón Flat
        digitalRead(PIN_BOTON_INICIO)     // Botón Inicio/Paro
    };
    unsigned long now = millis();

    // Botón Reducción de Centrifugado (LED 1)
    if (btn[0] != lastBtn[0] && (now - lastDebounce[0] > debounceDelay)) {
        lastDebounce[0] = now;
        lastBtn[0] = btn[0];
        if (btn[0] == LOW) {
            estadoReduccion = !estadoReduccion;
            setLedControl(LED_REDUCCION, estadoReduccion);
        }
    }
    // Botón Flat (LED 2)
    if (btn[1] != lastBtn[1] && (now - lastDebounce[1] > debounceDelay)) {
        lastDebounce[1] = now;
        lastBtn[1] = btn[1];
        if (btn[1] == LOW) {
            estadoFlat = !estadoFlat;
            setLedControl(LED_FLAT, estadoFlat);
        }
    }
    // Botón Inicio/Paro (LED 3)
    if (btn[2] != lastBtn[2] && (now - lastDebounce[2] > debounceDelay)) {
        lastDebounce[2] = now;
        lastBtn[2] = btn[2];
        if (btn[2] == LOW) {
            if (!cicloEnCurso) {
                estadoInicio = !estadoInicio;
                setLedControl(LED_INICIO, estadoInicio);
                if (!estadoInicio) {
                    // Si se apaga, reinicia todo
                    cicloEnCurso = false;
                    fase = 0;
                    subfase = 0;
                    repeticionesLavado = 0;
                    leds[LED_LAVADO] = COLOR_NEGRO;
                    leds[LED_ACLARADO] = COLOR_NEGRO;
                    leds[LED_CENTRIFUGADO] = COLOR_NEGRO;
                    digitalWrite(VALVE_PIN, LOW);
                    FastLED.show();
                }
            } else {
                // Si el ciclo está en curso, permite detenerlo
                estadoInicio = false;
                setLedControl(LED_INICIO, false);
                cicloEnCurso = false;
                fase = 0;
                subfase = 0;
                repeticionesLavado = 0;
                leds[LED_LAVADO] = COLOR_NEGRO;
                leds[LED_ACLARADO] = COLOR_NEGRO;
                leds[LED_CENTRIFUGADO] = COLOR_NEGRO;
                digitalWrite(VALVE_PIN, LOW);
                FastLED.show();
                Serial.println("Ciclo de lavado DETENIDO por el usuario");
            }
        }
    }

    // --- Secuencia automática de lavado ---
    if (estadoInicio && !cicloEnCurso) {
        cicloEnCurso = true;
        cicloTimestamp = now;
        fase = 1; // 1=lavado, 2=aclarado, 3=centrifugado
        subfase = 0;
        repeticionesLavado = 0;
        Serial.println("Ciclo de lavado INICIADO");
    }

    if (cicloEnCurso) {
        switch (fase) {
            case 1: // Lavado (5 ciclos de 5s ON/5s OFF)
                if (subfase == 0) {
                    leds[LED_LAVADO] = COLOR_VERDE;
                    FastLED.show();
                    subfase = 1;
                    cicloTimestamp = now;
                } else if (subfase == 1) { // Electroválvula ON (azul)
                    leds[LED_LAVADO] = COLOR_AZUL;
                    digitalWrite(VALVE_PIN, HIGH);
                    FastLED.show();
                    if (now - cicloTimestamp >= 5000) {
                        subfase = 2;
                        cicloTimestamp = now;
                    }
                } else if (subfase == 2) { // Electroválvula OFF (verde)
                    leds[LED_LAVADO] = COLOR_VERDE;
                    digitalWrite(VALVE_PIN, LOW);
                    FastLED.show();
                    if (now - cicloTimestamp >= 5000) {
                        repeticionesLavado++;
                        if (repeticionesLavado < 5) {
                            subfase = 1;
                            cicloTimestamp = now;
                        } else {
                            leds[LED_LAVADO] = COLOR_NEGRO;
                            FastLED.show();
                            fase = 2;
                            subfase = 0;
                            cicloTimestamp = now;
                        }
                    }
                }
                break;
            case 2: // Aclarado: 20s verde (sin válvula), 20s azul (con válvula), 20s verde (espera)
                if (subfase == 0) {
                    leds[LED_ACLARADO] = COLOR_VERDE;
                    digitalWrite(VALVE_PIN, LOW);
                    FastLED.show();
                    cicloTimestamp = now;
                    subfase = 1;
                } else if (subfase == 1) { // 20s LED verde (inicio aclarado)
                    if (now - cicloTimestamp >= 20000) {
                        leds[LED_ACLARADO] = COLOR_AZUL;
                        digitalWrite(VALVE_PIN, HIGH);
                        FastLED.show();
                        cicloTimestamp = now;
                        subfase = 2;
                    }
                } else if (subfase == 2) { // 20s LED azul + válvula
                    if (now - cicloTimestamp >= 20000) {
                        leds[LED_ACLARADO] = COLOR_VERDE;
                        digitalWrite(VALVE_PIN, LOW);
                        FastLED.show();
                        cicloTimestamp = now;
                        subfase = 3;
                    }
                } else if (subfase == 3) { // 20s LED verde (espera post-aclarado)
                    if (!estadoFlat && (now - cicloTimestamp >= 20000)) {
                        leds[LED_ACLARADO] = COLOR_NEGRO;
                        FastLED.show();
                        fase = 3;
                        subfase = 0;
                        cicloTimestamp = now;
                    } else if (estadoFlat) {
                        // Si Flat está activado, esperar indefinidamente en verde
                        // y pasar a centrifugado solo cuando se desactive
                        if (!estadoFlat) {
                            leds[LED_ACLARADO] = COLOR_NEGRO;
                            FastLED.show();
                            fase = 3;
                            subfase = 0;
                            cicloTimestamp = now;
                        }
                    }
                }
                break;
            case 3: // Centrifugado (30s turquesa)
                if (subfase == 0) {
                    leds[LED_CENTRIFUGADO] = COLOR_TURQUESA;
                    FastLED.show();
                    cicloTimestamp = now;
                    subfase = 1;
                } else if (subfase == 1) {
                    if (now - cicloTimestamp >= 30000) {
                        leds[LED_CENTRIFUGADO] = COLOR_NEGRO;
                        FastLED.show();
                        fase = 4;
                        subfase = 0;
                        cicloTimestamp = now;
                    }
                }
                break;
            case 4: // Finalización
                estadoInicio = false;
                setLedControl(LED_INICIO, false);
                leds[LED_LAVADO] = COLOR_NEGRO;
                leds[LED_ACLARADO] = COLOR_NEGRO;
                leds[LED_CENTRIFUGADO] = COLOR_NEGRO;
                digitalWrite(VALVE_PIN, LOW);
                FastLED.show();
                cicloEnCurso = false;
                fase = 0;
                subfase = 0;
                repeticionesLavado = 0;
                Serial.println("Ciclo de lavado FINALIZADO");
                break;
        }
    }

    delay(10);
}
