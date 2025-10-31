# Control de Lavadora - Simulador ESP8266

## Descripción del Proyecto

Este proyecto implementa un simulador para el control de una lavadora utilizando un ESP8266 (NodeMCU). El sistema simula el comportamiento completo de una lavadora con controles físicos y retroalimentación visual mediante LEDs NeoPixel.

## Hardware Utilizado

### Microcontrolador
- **ESP8266** (NodeMCU v2)
- Pines de entrada digital para botones
- Salida digital para válvula
- Salida PWM para control de NeoPixels

### Componentes de Entrada
- **Correspondencia entre botones y pines físicos:**

| Botón                        | Pin físico NodeMCU |
|------------------------------|--------------------|
| Reducción de Centrifugado    | D2                 |
| Flat (Plancha fácil)         | D4                 |
| Inicio/Paro                  | D5                 |
- **3 Pulsadores** conectados a tierra:
  - Botón Reducción de Centrifugado
  - Botón Flat (Plancha fácil)
  - Botón Inicio/Paro


### Componentes de Salida
**Correspondencia entre LEDs y botones:**

- **LED 1:** Reducción de Centrifugado (botón Reducción de Centrifugado, D2)
- **LED 2:** Flat (botón Flat, D4)
- **LED 3:** Inicio/Paro (botón Inicio/Paro, D5)
- **LED 4:** Lavado (automático)
| Botón                        | Pin físico NodeMCU |
|------------------------------|--------------------|
| Inicio/Paro                  | D2                 |
| Flat (Plancha fácil)         | D5                 |
| Reducción de Centrifugado    | D4                 |
- **LED 5:** Aclarado (automático)
- **LED 6:** Centrifugado (automático)

Los tres primeros LEDs (LED 1, 2 y 3) corresponden a los botones físicos. Los tres siguientes (LED 4, 5 y 6) indican el estado de las fases automáticas del ciclo de lavado.

**LED 1:** Inicio/Paro (botón Inicio/Paro, D2)
**LED 2:** Flat (botón Flat, D5)
**LED 3:** Reducción de Centrifugado (botón Reducción de Centrifugado, D4)
## Configuración de Pines

```cpp
// Pines de entrada (Botones)
#define BTN_START_STOP     ... // Botón Inicio/Paro
#define BTN_FLAT           ... // Botón Flat
#define BTN_SPIN_REDUCE    ... // Botón Reducción Centrifugado

// Pines de salida
#define NEOPIXEL_PIN       D1    // Tira de 6 NeoPixels
#define VALVE_PIN          D6    // Válvula digital (ahora en D6)

// Configuración NeoPixels
#define NUM_PIXELS         6     // 6 LEDs en total
```

## Funcionalidad del Sistema

### Estados de los LEDs
1. **LED Inicio/Paro (0)**: Se enciende en verde al presionar el botón de inicio y se desactiva si se vuelve a pulsar
2. **LED Flat (1)**: Se activa en verde cuando se presiona el botón Flat y se desactiva cuando se vuelve a presionar
3. **LED Reducción Velocidad Centrifugación (2)**: Se activa en verde cuando se pulsa y se desactiva cuando se vuelve a pulsar
4. **LED Lavado (3)**: Se activa durante el ciclo de lavado cuando el relé esté activo
5. **LED Aclarado (4)**: Se activa durante el ciclo de aclarado cuando el relé esté activo
6. **LED Centrifugado (5)**: Se activa durante el ciclo de centrifugado 

### Secuencia de Funcionamiento

#### 1. Inicio del Ciclo
- Presionar **Botón Inicio/Paro** → LED Inicio/Paro se enciende en verde
- Presionar **Botón Flat** → LED Flat se enciende en verde
- Presionar **Botón Reducción Centrifugado** → LED correspondiente se enciende en verde

#### 2. Ciclo de Lavado
Cuando el LED de Inicio/Paro está en verde (máquina en funcionamiento):

1. **Fase de Lavado**: Se activa el LED de lavado y la electroválvula 5 veces en intervalos de 5 segundos ON / 5 segundos OFF
2. **Fase de Aclarado**: El LED de aclarado se enciende en verde durante 20 segundos (sin electroválvula), luego en azul durante 20 segundos (con electroválvula)
3. **Fase de Centrifugado**: Se activa el LED de centrifugado durante 30 segundos, 30 segundos después del ciclo anterior (pero si el botón Flat está activado, se espera a que se desactive antes de pasar a esta fase)
4. **Finalización**: Se apaga todo de nuevo, el LED de inicio/paro se pone en rojo



## Instalación y Configuración

### Requisitos
- PlatformIO IDE
- ESP8266 (NodeMCU v2)
- Biblioteca FastLED para NeoPixels

### Librerías Necesarias
```ini
lib_deps = 
    fastled/FastLED@^3.6.0
    ESP8266WiFi
    ArduinoJson
```

### Entorno Virtual de PlatformIO
PlatformIO está instalado en su propio entorno virtual:
- **Ubicación**: `~/.platformio/penv/`
- **Ejecutable**: `~/.platformio/penv/bin/pio`
- **Versión**: PlatformIO Core 6.1.18

### Compilación y Carga

### Estados de los LEDs de Control
Todos los LEDs de control (Inicio/Paro, Flat, Reducción) comienzan en ROJO (inactivos).

- Al presionar el botón correspondiente:
  - Si el LED está en rojo, pasa a VERDE (activo).
  - Si el LED está en verde, vuelve a ROJO (inactivo).
- Esto aplica para:
  - **LED 1:** Reducción de Centrifugado
  - **LED 2:** Flat
  - **LED 3:** Inicio/Paro

### Secuencia Automática de Lavado
La secuencia solo se ejecuta si el LED de Inicio/Paro está en VERDE.

1. **Fase de Lavado:**
  - El LED de Lavado se enciende.
  - Durante 5 ciclos:
    - La electroválvula se activa durante 5 segundos (LED lavado AZUL).
    - Luego se apaga 5 segundos (LED lavado VERDE).
  - Al terminar, se apaga el LED de lavado.

2. **Fase de Aclarado:**
  - El LED de Aclarado se enciende en VERDE durante 20 segundos (sin electroválvula).
  - Después, el LED de Aclarado se pone en AZUL durante 20 segundos y la electroválvula se activa.
  - Luego se apaga el LED y la electroválvula.
  - Si el botón Flat está activado, el sistema espera a que se desactive antes de pasar a la fase de centrifugado (el LED de aclarado y la electroválvula permanecen apagados durante la espera).

3. **Fase de Centrifugado:**
  - El LED de Centrifugado se enciende en TURQUESA durante 30 segundos.
  - Luego se apaga.

4. **Finalización:**
  - El LED de Inicio/Paro vuelve a ROJO (inactivo).
  - Todos los LEDs de ciclo (Lavado, Aclarado, Centrifugado) se apagan.

### Resumen de Colores
- **ROJO:** Inactivo (estado inicial de los LEDs de control)
- **VERDE:** Activo (botón presionado o fase activa)
- **AZUL:** Fase de lavado/aclarado con electroválvula activa
pio device monitor
```

## Esquema de Conexiones

```
ESP8266 (NodeMCU)    Componente
─────────────────    ──────────
D1                → Tira de 6 LEDs NeoPixel
...               ← Botón Reducción de Centrifugado (a GND)
...               ← Botón Flat (a GND)
...               ← Botón Inicio/Paro (a GND)
D6                → Válvula Digital
GND               → GND común
3.3V              → VCC NeoPixels (o 5V externa)
```

