# Control NeoPixel ESP8266 - Dual Mode

## Hardware Soportado

El mismo código funciona con **2 configuraciones diferentes sin recompilar**:

1. **3 LEDs en serie en D1** (D2 y D3 vacíos)
2. **3 LEDs separados**: D1, D2, D3 (1 LED por pin)

## Cómo Funciona

### Arrays
```cpp
CRGB leds_serie[3];    // Para D1 (3 LEDs)
CRGB leds_d2[1];       // Para D2 (1 LED)
CRGB leds_d3[1];       // Para D3 (1 LED)
```

### Patrón de Actualización
Todas las funciones actualizan **ambos sistemas** a la vez:

```cpp
void ponerNaranja(int strip) {
    if (strip == 1) {
        leds_serie[0] = COLOR_NARANJA;           // LED 0
    } else if (strip == 2) {
        leds_serie[1] = COLOR_NARANJA;           // LED 1 modo serie
        leds_d2[0] = COLOR_NARANJA;              // LED 1 modo separado
    } else if (strip == 3) {
        leds_serie[2] = COLOR_NARANJA;           // LED 2 modo serie
        leds_d3[0] = COLOR_NARANJA;              // LED 2 modo separado
    }
    FastLED.show();
}
```

### Por Qué Funciona
- **Serie en D1**: `leds_serie[0/1/2]` controla los 3 LEDs, los arrays D2/D3 no hacen nada
- **Separados**: `leds_serie[0]` controla D1, `leds_d2[0]` controla D2, `leds_d3[0]` controla D3

## Sensor de Flujo de Agua

### Configuración
- **Pin D6**: Entrada con pullup para sensor de flujo
- **Interrupción**: FALLING (cada pulso del sensor)

### Modos de Funcionamiento

**MODO NORMAL** (por defecto):
- Presentación del logo con secuencias de colores
- Delay de 5 segundos entre ciclos

**MODO FLUJO** (cuando detecta pulsos):
- LED turquesa avanza 0→1→2 con cada pulso
- Vuelve automático a modo normal tras 3 segundos sin pulsos

### Código Clave
```cpp
// Variables interrupt
volatile bool modoFlujo = false;
volatile unsigned long ultimoPulso = 0;
volatile int ledActual = 0;

// Handler interrupt
void IRAM_ATTR pulsosAgua() {
    modoFlujo = true;
    ultimoPulso = millis();
    ledActual = (ledActual + 1) % 3;  // Rota 0→1→2→0
}

// Loop principal
void loop() {
    // Timeout: volver a modo normal
    if (modoFlujo && (millis() - ultimoPulso > TIMEOUT_FLUJO)) {
        modoFlujo = false;
    }
    
    // Ejecutar modo activo
    if (modoFlujo) {
        mostrarFlujoAgua();
        delay(50);
    } else {
        presentacionNormal();
        delay(5000);
    }
}
```

## Añadir Nuevo Color

1. Define el color:
```cpp
#define COLOR_NUEVO CRGB(R, G, B)
```

2. Crea funciones siguiendo el patrón:
```cpp
void ponerNuevo(int strip) { /* patrón dual */ }
void todoNuevo() { ponerNuevo(1); ponerNuevo(2); ponerNuevo(3); }
```

## Debug
Monitor serial (115200 baud) muestra:
- Test inicial RGB
- Configuración FastLED
- Estado del sensor de flujo
- Secuencias de presentación

✅ **Sin recompilación, sin cambios de código, funciona en ambos modos**
