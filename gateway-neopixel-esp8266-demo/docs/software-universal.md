# Software Universal - Control NeoPixel ESP8266

## 🎯 Objetivo

Crear un **software único** que funcione con **dos configuraciones de hardware diferentes** sin necesidad de cambiar código ni configuraciones:

1. **Modo Serie**: 3 LEDs conectados en serie en el pin D1
2. **Modo Separado**: 3 LEDs conectados independientemente en D1, D2 y D3

## ✅ Solución Implementada

### Arquitectura del Software

El software utiliza una **doble lógica simultánea** que actualiza múltiples arrays de LEDs en cada operación:

```cpp
// Arrays de LEDs
CRGB leds_serie[3];     // D1: 3 LEDs en serie O 1 LED separado (usa leds_serie[0])
CRGB leds_d2[1];        // D2: 1 LED (solo modo separado)
CRGB leds_d3[1];        // D3: 1 LED (solo modo separado)
```

### Configuración de FastLED

```cpp
// D1 → 3 LEDs en serie
FastLED.addLeds<WS2812B, NEOPIXEL_PIN_D1, GRB>(leds_serie, 3);
// D2 → 1 LED individual
FastLED.addLeds<WS2812B, NEOPIXEL_PIN_D2, GRB>(leds_d2, 1);
// D3 → 1 LED individual
FastLED.addLeds<WS2812B, NEOPIXEL_PIN_D3, GRB>(leds_d3, 1);
```

## 🔌 Configuraciones de Hardware Soportadas

### Configuración 1: LEDs en Serie (D1)

**Conexión física:**
```
ESP8266 D1 → LED0 → LED1 → LED2
D2: sin conectar
D3: sin conectar
```

**Funcionamiento:**
- `leds_serie[0]` controla LED0
- `leds_serie[1]` controla LED1
- `leds_serie[2]` controla LED2
- `leds_d2` y `leds_d3` envían datos al aire (sin efecto)

### Configuración 2: LEDs Separados (D1, D2, D3)

**Conexión física:**
```
ESP8266 D1 → LED0
ESP8266 D2 → LED1
ESP8266 D3 → LED2
```

**Funcionamiento:**
- `leds_serie[0]` controla LED0 en D1
- `leds_d2[0]` controla LED1 en D2
- `leds_d3[0]` controla LED2 en D3
- `leds_serie[1]` y `leds_serie[2]` se envían a D1 pero solo hay 1 LED conectado

## 💡 Lógica de las Funciones

Todas las funciones de control actualizan **ambos sistemas simultáneamente**:

### Ejemplo: `ponerNaranja(int strip)`

```cpp
void ponerNaranja(int strip) {
    if (strip == 1) {
        // LED 0: siempre usa leds_serie[0]
        leds_serie[0] = COLOR_NARANJA;
    } else if (strip == 2) {
        // LED 1: actualiza serie[1] (para modo serie) Y d2[0] (para modo separado)
        leds_serie[1] = COLOR_NARANJA;
        leds_d2[0] = COLOR_NARANJA;
    } else if (strip == 3) {
        // LED 2: actualiza serie[2] (para modo serie) Y d3[0] (para modo separado)
        leds_serie[2] = COLOR_NARANJA;
        leds_d3[0] = COLOR_NARANJA;
    }
    FastLED.show();
}
```

### Funciones Principales

- `apagarTodo()`: Apaga todos los LEDs en ambos sistemas
- `ponerNaranja(strip)`: Pone un LED específico en naranja
- `ponerAzulMarino(strip)`: Pone un LED específico en azul marino
- `ponerTurquesa(strip)`: Pone un LED específico en turquesa
- `encenderLogoCompleto()`: Enciende los 3 LEDs con sus colores característicos
- `todoTurquesa()`: Todos los LEDs en turquesa
- `todoAzulMarino()`: Todos los LEDs en azul marino
- `todoNaranja()`: Todos los LEDs en naranja

## 🎨 Colores Definidos

```cpp
const CRGB COLOR_TURQUESA = CRGB(64, 224, 208);
const CRGB COLOR_AZUL_MARINO = CRGB(0, 0, 139);
const CRGB COLOR_NARANJA = CRGB(255, 69, 0);
```

## 🔧 Configuración

### `include/config.h`

```cpp
#define NUM_LEDS_PER_STRIP    1     // 1 LED por sección
#define BRIGHTNESS            255   // Brillo al MÁXIMO
#define MAX_BRIGHTNESS        255   // Brillo máximo permitido
```

**No hay variables de modo** - el mismo código funciona siempre.

## 📋 Secuencia de Presentación

El programa ejecuta la siguiente secuencia en bucle:

1. **Test inicial**: 
   - LED 0 → Rojo
   - LED 1 → Verde
   - LED 2 → Azul

2. **Colores completos**:
   - Todo turquesa (2s)
   - Todo azul marino (2s)
   - Todo naranja (2s)

3. **Presentación de bajada**:
   - Naranja baja: arriba → centro → abajo
   - Azul marino baja: arriba → centro (queda)
   - Turquesa aparece arriba

4. **Logo completo**:
   - D1/LED0 = Turquesa
   - D2/LED1 = Azul Marino
   - D3/LED2 = Naranja

5. **Flashes**: 6 parpadeos del logo completo

6. **Pausa final**: 4 segundos con logo encendido

7. **Reinicio**: La secuencia se repite cada 5 segundos

## ✨ Ventajas del Software Universal

### ✅ Sin Configuración
- No hay que cambiar constantes
- No hay que recompilar para cambiar de modo
- No hay detección de hardware

### ✅ Simplicidad
- Un solo código fuente
- Fácil mantenimiento
- Sin errores de configuración

### ✅ Flexibilidad Total
- Cambias solo el cableado físico
- El software se adapta automáticamente
- Mismo comportamiento visual en ambos modos

### ✅ Instalación Rápida
- Programa una vez
- Usa en cualquier configuración
- Perfecto para prototipos y producción

## 🔍 Debugging

### Monitor Serie

Al iniciar, verás:

```
=== PRESENTACIÓN SIMPLE DEL LOGO ===
LEDs por tira: 1
Brillo configurado: 255
Configurando FastLED...
CONFIGURACIÓN: D1→3serie, D2→1, D3→1

=== TEST INICIAL DE CADA POSICIÓN ===
🔴 TEST LED 0 - ROJO
🟢 TEST LED 1 - VERDE
🔵 TEST LED 2 - AZUL
```

### Verificación Visual

**Modo Serie (3 LEDs en D1):**
- Deberías ver los 3 LEDs encenderse secuencialmente en rojo, verde, azul

**Modo Separado (D1, D2, D3):**
- Deberías ver D1 rojo, luego D2 verde, luego D3 azul

## 📊 Comparación de Modos

| Aspecto | Modo Serie | Modo Separado |
|---------|------------|---------------|
| **Conexión** | D1 → LED0→LED1→LED2 | D1→LED0, D2→LED1, D3→LED2 |
| **Cables** | 1 pin de datos | 3 pines de datos |
| **Arrays activos** | `leds_serie[3]` | `leds_serie[0]`, `leds_d2[0]`, `leds_d3[0]` |
| **Instalación** | Más simple | Más flexible |
| **Rendimiento** | Secuencial | Paralelo |
| **Uso ideal** | Producción/demo | Desarrollo/prototipo |

## 🛠 Mantenimiento

### Para Añadir Nuevos Efectos

Sigue el patrón de las funciones existentes:

```cpp
void miNuevoEfecto() {
    // Actualizar leds_serie para modo serie
    leds_serie[0] = COLOR_PERSONALIZADO;
    leds_serie[1] = COLOR_PERSONALIZADO;
    leds_serie[2] = COLOR_PERSONALIZADO;
    
    // Actualizar leds_d2 y leds_d3 para modo separado
    leds_d2[0] = COLOR_PERSONALIZADO;
    leds_d3[0] = COLOR_PERSONALIZADO;
    
    FastLED.show();
}
```

### Para Añadir Nuevos Colores

Define nuevas constantes:

```cpp
const CRGB COLOR_PERSONALIZADO = CRGB(R, G, B);
```

## 📝 Notas Técnicas

### Limitación de FastLED
- No se puede configurar el mismo pin (D1) dos veces con diferentes arrays
- Por eso usamos `leds_serie[]` para D1 en ambos modos
- D2 y D3 tienen sus propios arrays independientes

### GND Común
- **Importante**: Todos los LEDs deben compartir GND con el ESP8266
- Usar fuente externa para alimentación si son más de 5 LEDs

### Alimentación
- 1 LED @ 255 brillo ≈ 60mA máximo
- 3 LEDs @ 255 brillo ≈ 180mA máximo
- ESP8266 pin 3V3 puede suministrar ~200mA
- ESP8266 pin 5V puede suministrar ~500mA (USB)

## 🎓 Conclusión

Este software universal es la solución perfecta para aplicaciones que requieren flexibilidad en el hardware sin complicaciones en el software. El mismo código funciona en cualquier configuración, facilitando:

- Desarrollo rápido
- Pruebas sencillas
- Instalación flexible
- Mantenimiento simple
- Documentación clara

**¡Un código, infinitas posibilidades!** 🚀
