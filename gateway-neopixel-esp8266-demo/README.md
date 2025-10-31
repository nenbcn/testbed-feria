# Iluminación Logo Gateway - ESP8266

Este proyecto controla la iluminación del logo corporativo en la caja del gateway para demostraciones en feria. El ESP8266 se conecta a 3 tiras de LEDs NeoPixel que iluminan el logo con una secuencia visual automática.

## 🎯 Función Específica

- **Propósito**: Iluminar el logo del gateway en el stand de feria
- **Funcionalidad**: Solo decorativa/visual - sin funciones adicionales  
- **Operación**: Secuencia automática continua con colores corporativos
- **Instalación**: Dentro de la caja del gateway para efecto visual

## 🎨 Secuencia de Iluminación

El sistema ejecuta una secuencia predefinida que:
1. **Presenta cada color** en todo el logo (turquesa → azul marino → naranja)
2. **Simula "bajada"** del logo de arriba hacia abajo
3. **Combina colores** para formar el logo completo
4. **Efectos de flash** finales para llamar la atención
5. **Se repite continuamente** para mantener el impacto visual

## 🔧 Hardware Requerido

- **ESP8266 NodeMCU v2** (dentro de la caja del gateway)
- **3 tiras de LEDs NeoPixel** (10 LEDs por tira)
- **Fuente de alimentación 5V** para los LEDs
- **Conexiones**: D1, D2, D3 para las 3 secciones del logo

## �� Conexiones del Logo

```
ESP8266 Pin D1 (GPIO5)  →  LEDs sección SUPERIOR del logo (Turquesa)
ESP8266 Pin D2 (GPIO4)  →  LEDs sección CENTRAL del logo (Azul Marino)  
ESP8266 Pin D3 (GPIO0)  →  LEDs sección INFERIOR del logo (Naranja)

Alimentación:
5V externa  →  VCC de todas las tiras NeoPixel
GND común   →  GND ESP8266 + GND LEDs
```

## 🚀 Instalación

```bash
# Clonar y compilar
cd gateway-neopixel-esp8266-demo
pio run

# Subir al ESP8266
pio run --target upload
```

## ⚡ Funcionamiento

1. **Encendido automático**: El sistema inicia al alimentar el gateway
2. **Secuencia continua**: No requiere intervención manual
3. **Colores corporativos**: Usa los colores oficiales de la marca
4. **Efecto visual**: Llama la atención en el stand de feria

## 🎪 Para la Feria

- ✅ **Plug & Play**: Solo conectar y encender
- ✅ **Funcionamiento continuo**: Sin mantenimiento durante el evento
- ✅ **Impacto visual**: Logo iluminado llama la atención
- ✅ **Integrado**: Oculto dentro de la caja del gateway

---

**Desarrollado exclusivamente para iluminación decorativa del logo en ferias** 🎪✨
