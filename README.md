# Testbed Feria - Proyectos para Demostración

Este repositorio contiene proyectos de demostración para feria/eventos, basados en ESP8266 y ESP32-C3 con control de LEDs NeoPixel.

## 📁 Proyectos Incluidos

### 🎯 gateway-neopixel-esp8266-demo
- **Hardware**: ESP8266 NodeMCU v2
- **Función**: Control de 3 tiras NeoPixel (D1, D2, D3)
- **Características**: Presentación automática del logo corporativo
- **LEDs**: 10 por tira, efectos visuales con colores turquesa, azul marino y naranja

### 🌆 tira-leds-esp32c3-feria  
- **Hardware**: Seeeduino XIAO ESP32-C3
- **Función**: Control de flujo dinámico para SmartCity
- **Características**: Control por pulsos de entrada, velocidad variable
- **LEDs**: 144 LEDs con efectos de flujo de agua

### 🏠 control-lavadora-feria
- **Hardware**: ESP8266 NodeMCU v2  
- **Función**: Automatización doméstica con LEDs
- **Características**: Control de dispositivos con feedback visual
- **LEDs**: Múltiples efectos para indicar estados

## 🚀 Instalación Rápida

Cada proyecto tiene su propia documentación en su carpeta correspondiente.

```bash
# Clonar el repositorio
git clone https://github.com/nenbcn/testbed-feria.git
cd testbed-feria

# Compilar cualquier proyecto
cd gateway-neopixel-esp8266-demo
pio run

# Subir al dispositivo
pio run --target upload
```

## 🎨 Para Ferias y Demostraciones

Estos proyectos están optimizados para:
- ✅ Demostraciones visuales impactantes
- ✅ Configuración rápida y sencilla
- ✅ Código bien documentado
- ✅ Efectos llamativos para público

## 📊 Hardware Requerido

| Proyecto | Microcontrolador | LEDs | Alimentación |
|----------|------------------|------|--------------|
| Gateway Demo | ESP8266 NodeMCU v2 | 3 tiras x 10 LEDs | 5V externa |
| Tira SmartCity | ESP32-C3 XIAO | 1 tira x 144 LEDs | 5V externa |
| Control Lavadora | ESP8266 NodeMCU v2 | Variable | 3.3V/5V |

## 🔧 Configuración

Cada proyecto incluye:
- `platformio.ini` configurado
- Diagramas de conexión en `/docs`
- Tests unitarios básicos
- README específico

---

**Desarrollado para demostraciones técnicas y ferias tecnológicas** 🎪✨
