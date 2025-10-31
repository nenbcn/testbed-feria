# Control de LEDs NeoPixel con ESP8266

Este proyecto permite controlar tiras de LEDs NeoPixel conectadas a los pines D1, D2 y D3 de un ESP8266 NodeMCU, con múltiples efectos de iluminación y control por puerto serie.

## 🔧 Hardware Requerido

- **ESP8266 NodeMCU v1.0**
- **Tiras de LEDs NeoPixel (WS2812B)** - 3 unidades
- **Fuente de alimentación externa** (recomendada para múltiples LEDs)
- **Resistencias de 470Ω** (opcional, para protección de datos)
- **Cables de conexión**

## 📐 Conexiones

| Pin ESP8266 | Conexión | Descripción |
|-------------|----------|-------------|
| D1 (GPIO5)  | Data Pin Tira 1 | Primera tira de LEDs NeoPixel |
| D2 (GPIO4)  | Data Pin Tira 2 | Segunda tira de LEDs NeoPixel |
| D3 (GPIO0)  | Data Pin Tira 3 | Tercera tira de LEDs NeoPixel |
| 3V3         | VCC LEDs | Alimentación (solo para pocos LEDs) |
| GND         | GND LEDs | Tierra común |

### ⚠️ Notas Importantes sobre Alimentación

- **Para 1-5 LEDs por tira**: Puedes alimentar desde el pin 3V3 del ESP8266
- **Para más de 5 LEDs por tira**: Usa una fuente externa de 5V
- **Cálculo de corriente**: Cada LED consume ~60mA a máximo brillo
- **Ejemplo**: 10 LEDs x 3 tiras x 60mA = 1.8A mínimo requerido

## 🚀 Instalación y Configuración

### 1. Configuración del Entorno

```bash
# Instalar PlatformIO (si no está instalado)
pip install platformio

# Clonar o descargar este proyecto
cd control-neopixel-esp8266

# Compilar el proyecto
pio run

# Subir al ESP8266
pio run --target upload

# Monitorear puerto serie
pio device monitor
```

### 2. Configuración en el Código

Edita las siguientes constantes en `src/main.cpp` según tu configuración:

```cpp
#define NUM_LEDS_PER_STRIP    10    // Cambia según tus LEDs
#define BRIGHTNESS            50    // Brillo inicial (0-255)
```

## 🎨 Efectos Disponibles

El sistema incluye 6 efectos diferentes que rotan automáticamente cada 10 segundos:

| Efecto | Descripción |
|--------|-------------|
| **0** | Colores sólidos rotando |
| **1** | Arcoíris deslizante |
| **2** | Respiración con colores diferentes |
| **3** | Luz corriendo con cola |
| **4** | Destellos aleatorios |
| **5** | Efecto onda |

## 📟 Comandos por Puerto Serie

Puedes controlar el sistema enviando comandos por el puerto serie a 115200 baudios:

```
effect0    - Cambiar a efecto 0 (colores sólidos)
effect1    - Cambiar a efecto 1 (arcoíris)
effect2    - Cambiar a efecto 2 (respiración)
effect3    - Cambiar a efecto 3 (luz corriendo)
effect4    - Cambiar a efecto 4 (destellos)
effect5    - Cambiar a efecto 5 (onda)
status     - Mostrar estado actual del sistema
clear      - Apagar todos los LEDs
```

## 🛠️ Personalización

### Cambiar Colores

Modifica las constantes de color en el código:

```cpp
const CRGB COLOR_PERSONALIZADO = CRGB(255, 128, 64); // RGB personalizado
```

### Agregar Nuevos Efectos

1. Crea una nueva función de efecto:
```cpp
void miNuevoEfecto(CRGB* strip) {
    // Tu código aquí
}
```

2. Agrégala al switch en `executeEffect()`:
```cpp
case 6: // Nuevo efecto
    miNuevoEfecto(leds_d1);
    miNuevoEfecto(leds_d2);
    miNuevoEfecto(leds_d3);
    break;
```

3. Actualiza `NUM_EFFECTS` en las variables globales.

### Velocidad de Animación

Cambia el intervalo de actualización:

```cpp
const long interval = 50;  // Más rápido (50ms)
const long interval = 200; // Más lento (200ms)
```

## 📊 Monitoreo y Debug

El sistema proporciona información detallada por puerto serie:

```
=== Control de LEDs NeoPixel ESP8266 ===
Inicializando sistema...
LEDs inicializados en pines D1, D2 y D3
Número de LEDs por tira: 10
Brillo configurado: 50
Sistema inicializado correctamente
```

### Resolución de Problemas

| Problema | Solución |
|----------|----------|
| LEDs no encienden | Verificar conexiones y alimentación |
| Colores incorrectos | Cambiar orden de colores (GRB vs RGB) |
| Parpadeo | Usar fuente de alimentación externa |
| No responde a comandos | Verificar velocidad de puerto serie (115200) |

## 📚 Librerías Utilizadas

- **FastLED 3.6.0+**: Control avanzado de LEDs programables
- **Arduino Core for ESP8266**: Framework base

## 🔄 Futuras Mejoras

- [ ] Control por WiFi y aplicación móvil
- [ ] Sincronización con música
- [ ] Sensor de sonido para efectos reactivos
- [ ] Configuración por web interface
- [ ] Almacenamiento de configuraciones en EEPROM
- [ ] Control por MQTT
- [ ] Integración con Home Assistant

## 📝 Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/NuevoEfecto`)
3. Commit tus cambios (`git commit -am 'Agregar nuevo efecto'`)
4. Push a la rama (`git push origin feature/NuevoEfecto`)
5. Abre un Pull Request

## 📞 Soporte

Si tienes problemas o preguntas:

- Abre un issue en GitHub
- Revisa la documentación de FastLED
- Consulta los foros de ESP8266

---

**¡Disfruta creando efectos increíbles con tus LEDs NeoPixel!** ✨