
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Configuración de la tira de LEDs para Seeeduino XIAO ESP32-C3
#define LED_PIN D3              // Pin D3 donde está conectada la tira
#define INTERRUPT_PIN D6        // Pin D6 para pulsos de entrada
#define NUM_LEDS 144            // Número de LEDs en la tira (144 LEDs)

// Configuración de velocidad
#define SPEED_MIN 1500          // ms por LED a 1 Hz (muy lento)
#define SPEED_MAX 15            // ms por LED a 100 Hz (super rápido)
#define TIMEOUT_MS 2000         // Timeout sin pulsos para apagar (2 segundos)

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Variables para interrupciones (deben ser volatile)
volatile unsigned long lastPulseTime = 0;
volatile unsigned long pulseInterval = 0;
volatile bool newPulseReceived = false;

// Variables para el efecto
unsigned long previousMillis = 0;
unsigned long currentSpeed = 80;        // Velocidad actual en ms
bool stripActive = false;               // Estado de la tira (encendida/apagada)
int flowPosition = 0;                   // Posición actual del flujo

// Color del agua (azul turquesa fijo)
const uint8_t waterR = 0;
const uint8_t waterG = 200;
const uint8_t waterB = 100;

// Configuración del patrón de flujo
#define DROP_LENGTH 2                   // Longitud de cada "gota" (1-2 LEDs)
#define DROP_SPACING 10                 // Espaciado entre gotas

// Función de interrupción para contar pulsos
void IRAM_ATTR handlePulse() {
    unsigned long currentTime = millis();
    
    if (lastPulseTime > 0) {
        pulseInterval = currentTime - lastPulseTime;
        newPulseReceived = true;
    }
    
    lastPulseTime = currentTime;
}

// Actualizar velocidad basada en los pulsos recibidos
void updateSpeed() {
    if (newPulseReceived && pulseInterval > 0) {
        newPulseReceived = false;
        
        // Mapear intervalo de pulsos a velocidad de LEDs
        // pulseInterval: 1000ms (1Hz) -> speed: 500ms (lento)
        // pulseInterval: 10ms (100Hz) -> speed: 40ms (rápido)
        // Relación inversa: más frecuencia = más rápido
        currentSpeed = map(pulseInterval, 10, 1000, SPEED_MAX, SPEED_MIN);
        
        // Limitar valores
        currentSpeed = constrain(currentSpeed, SPEED_MAX, SPEED_MIN);
        
        stripActive = true;  // Activar la tira cuando hay pulsos
        
        Serial.print("Intervalo: ");
        Serial.print(pulseInterval);
        Serial.print("ms -> Velocidad: ");
        Serial.print(currentSpeed);
        Serial.println("ms");
    }
}

// Verificar timeout - apagar si no hay pulsos
void checkTimeout() {
    if (stripActive && (millis() - lastPulseTime > TIMEOUT_MS)) {
        stripActive = false;
        strip.clear();
        strip.show();
        flowPosition = 0;  // Reiniciar posición
        
        Serial.println("Timeout - Tira apagada");
    }
}

void setup() {
    Serial.begin(115200);
    strip.begin();
    strip.show();
    
    // Configurar pin de interrupción
    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), handlePulse, RISING);
    
    Serial.println("Sistema de flujo de agua SmartCity iniciado");
    Serial.println("Esperando pulsos en D3...");
}

void loop() {
    // Actualizar velocidad basada en pulsos
    updateSpeed();
    
    // Verificar timeout
    checkTimeout();
    
    // Solo procesar si la tira está activa
    if (stripActive) {
        unsigned long currentMillis = millis();
        
        if (currentMillis - previousMillis >= currentSpeed) {
            previousMillis = currentMillis;
            
            // Limpiar toda la tira
            strip.clear();
            
            // Dibujar múltiples "gotas" que fluyen por la tira
            for (int pos = 0; pos < NUM_LEDS; pos++) {
                // Calcular si en esta posición debe haber una gota
                int relativePos = (pos + flowPosition) % (DROP_LENGTH + DROP_SPACING);
                
                if (relativePos < DROP_LENGTH) {
                    // Esta posición es parte de una gota
                    // Intensidad uniforme en toda la gota
                    strip.setPixelColor(pos, strip.Color(waterR, waterG, waterB));
                }
            }
            
            strip.show();
            
            // Avanzar posición del flujo
            flowPosition++;
            if (flowPosition >= DROP_LENGTH + DROP_SPACING) {
                flowPosition = 0;  // Reiniciar ciclo del patrón
            }
        }
    }
}
