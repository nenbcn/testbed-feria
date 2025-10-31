# Prompt para Generar Efecto de Agua con Calentamiento Gradual

## Descripción del Efecto Deseado

Crear un efecto de simulación de agua que fluye de manera realista a través de una tira de LEDs WS2812B, donde el agua comienza fría (color turquesa) y gradualmente se va calentando hasta llegar a rojo (agua caliente). El efecto debe simular el flujo continuo de agua en un sistema de refrigeración líquida.

## Especificaciones Técnicas

### Hardware
- **Microcontrolador**: ESP8266
- **Pin de datos**: D1 (GPIO5)
- **Tipo de LEDs**: WS2812B (NeoPixel)
- **Cantidad de LEDs**: 144 LEDs
- **Configuración**: NEO_GRB + NEO_KHZ800

### Biblioteca Requerida
```cpp
#include <Adafruit_NeoPixel.h>
```

## Lógica del Efecto

### 1. Comportamiento del Flujo
- El agua debe fluir desde el LED 0 hasta el LED 143
- Velocidad de flujo: aproximadamente 80ms por paso
- El efecto debe ser continuo y cíclico
- Cada "gota" de agua debe propagarse a través de toda la tira

### 2. Sistema de Colores
- **Color inicial (agua fría)**: RGB(0, 200, 100) - Turquesa
- **Color final (agua caliente)**: RGB(255, 0, 0) - Rojo
- **Interpolación**: Gradiente lineal suave entre ambos colores
- **Progresión de calentamiento**: 300 pasos para completar la transición

### 3. Algoritmo de Calentamiento
```
heatRatio = heatPhase / 300.0
colorR = coldR + heatRatio * (hotR - coldR)
colorG = coldG + heatRatio * (hotG - coldG)
colorB = coldB + heatRatio * (hotB - coldB)
```

### 4. Gestión de Memoria
- Usar array bidimensional para almacenar colores: `uint8_t ledColors[144][3]`
- Almacenar RGB por separado para cada LED
- Propagar colores mediante desplazamiento de array

## Estructura del Código

### Variables Globales
```cpp
#define LED_PIN D1
#define LED_COUNT 144

// Colores base
const uint8_t coldR = 0, coldG = 200, coldB = 100;    // Turquesa
const uint8_t hotR = 255, hotG = 0, hotB = 0;         // Rojo

// Estado del sistema
uint8_t ledColors[LED_COUNT][3];  // [LED][RGB]
int heatPhase = 0;                // Fase de calentamiento
unsigned long lastUpdate = 0;    // Control de timing
```

### Loop Principal
1. **Control de timing**: Verificar si han pasado 80ms
2. **Propagación**: Mover colores desde LED[i] hacia LED[i+1]
3. **Cálculo de color inicial**: Determinar color del LED 0 basado en heatPhase
4. **Actualización de LEDs**: Aplicar colores calculados a la tira
5. **Incremento de fase**: Aumentar heatPhase cada ciclo
6. **Detección de ciclo completo**: Reiniciar cuando el color llegue al LED 143

### Algoritmo de Propagación
```cpp
// Mover colores hacia adelante
for (int i = LED_COUNT - 1; i > 0; i--) {
    ledColors[i][0] = ledColors[i-1][0];  // R
    ledColors[i][1] = ledColors[i-1][1];  // G
    ledColors[i][2] = ledColors[i-1][2];  // B
}
```

### Detección de Final de Ciclo
- Detectar cuando el LED 143 tiene un color que no sea negro (0,0,0)
- Reiniciar heatPhase a 0 para comenzar nuevo ciclo
- Limpiar array de colores

## Parámetros de Optimización

### Timing
- **Velocidad de flujo**: 80ms (ajustable para efectos más rápidos/lentos)
- **Fase de calentamiento**: 300 pasos (reducir para calentamiento más rápido)

### Colores
- **Turquesa inicial**: RGB(0, 200, 100) - Agua fría realista
- **Rojo final**: RGB(255, 0, 0) - Agua caliente intensa
- **Interpolación**: Lineal (puede cambiarse a exponencial si se desea)

## Comportamiento Visual Esperado

1. **Inicio**: LED 0 muestra color turquesa
2. **Flujo**: El color turquesa se propaga LED por LED hacia el final
3. **Calentamiento gradual**: Cada nuevo "pulso" en LED 0 es ligeramente más rojizo
4. **Progresión**: Después de ~24 segundos (300 ciclos × 80ms), LED 0 muestra rojo puro
5. **Continuidad**: El efecto continúa con agua roja fluyendo
6. **Reinicio**: Cuando el color llega al LED 143, se reinicia el ciclo

## Consideraciones de Implementación

### Eficiencia
- Usar arrays estáticos para evitar malloc/free
- Propagación mediante copia de valores en lugar de cálculos complejos
- Control de timing con millis() en lugar de delay()

### Robustez
- Validar límites de array
- Controlar overflow en heatPhase
- Gestión adecuada de la reinicialización del ciclo

### Extensibilidad
- Parámetros fácilmente ajustables
- Estructura modular para agregar efectos adicionales
- Compatibilidad con diferentes tamaños de tira LED

## Ejemplo de Uso

Este efecto es ideal para:
- Simulación de sistemas de refrigeración líquida
- Efectos decorativos de flujo de agua
- Indicadores visuales de temperatura
- Ambientación de PC gaming
- Proyectos de domótica con feedback visual

---

*Fecha de creación: 21 de septiembre de 2025*
*Versión: 1.0*
*Hardware testado: ESP8266 + 144 LEDs WS2812B*
