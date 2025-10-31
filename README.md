# Testbed Feria - Sistema Completo para Demostraciones

Este repositorio contiene **todo el software y documentación** necesarios para el testbed de demostración en ferias/eventos. Incluye proyectos ESP8266/ESP32-C3 con LEDs NeoPixel y una versión especial del gateway con funcionalidades mejoradas para demostraciones interactivas.

## 📁 Proyectos Incluidos

### 🎯 gateway-neopixel-esp8266-demo
- **Hardware**: ESP8266 NodeMCU v2
- **Función**: **Iluminación del logo del Gateway para feria**
- **Características**: Secuencia automática para iluminar el logo de la caja del gateway
- **LEDs**: 3 tiras x 10 LEDs con colores corporativos (turquesa, azul marino, naranja)
- **Uso**: Únicamente decorativo/visual para stand de feria

### 🌆 tira-leds-esp32c3-feria  
- **Hardware**: Seeeduino XIAO ESP32-C3
- **Función**: **Simulación visual de flujo de agua en stand**
- **Características**: Simula flujo de agua con velocidad variable según señal de entrada
- **LEDs**: 144 LEDs - flujo más rápido = mayor caudal de agua
- **Uso**: Demostración visual del funcionamiento del sistema de agua

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

| Componente | Microcontrolador | LEDs/Función | Alimentación |
|------------|------------------|--------------|--------------|
| **Gateway Testbed** | ESP32 (especial) | Status LEDs + MQTT 200ms + Válvula | 12V externa |
| Gateway Demo | ESP8266 NodeMCU v2 | 3 tiras x 10 LEDs (logo) | 5V externa |
| Tira SmartCity | ESP32-C3 XIAO | 1 tira x 144 LEDs (flujo) | 5V externa |
| Control Lavadora | ESP8266 NodeMCU v2 | Variable (estados) | 3.3V/5V |

## 🔧 Configuración

Cada proyecto incluye:
- `platformio.ini` configurado
- Diagramas de conexión en `/docs`
- Tests unitarios básicos
- README específico

## 🏭 Gateway Especial para Testbed

### Versión Mejorada del Gateway
Este testbed incluye una **versión especial del gateway** con las siguientes mejoras para demostraciones:

#### ⚡ Responsividad Mejorada
- **MQTT cada 200ms**: Mensajes más frecuentes para respuesta visual inmediata
- **Tiempo real**: Los cambios se ven instantáneamente en la simulación LED
- **Interactividad**: Ideal para demostraciones con público en vivo

#### 🔧 Control de Válvula Anti-Fugas
- **Detección automática de fugas**: Monitoring continuo del sistema
- **Accionamiento de relé**: Cierre automático de válvula en caso de emergencia
- **Seguridad**: Protección del sistema durante las demostraciones
- **Indicación visual**: LEDs muestran el estado de la válvula

#### 📋 Diferencias con Gateway de Producción
```
Gateway Producción  →  MQTT cada 1000ms, sin control válvula
Gateway Testbed     →  MQTT cada 200ms + control válvula anti-fugas
```

### 🔀 Versiones del Gateway
- **Producción**: Disponible en branches del repositorio principal del gateway
- **Testbed**: Versión especial incluida en este repositorio
- **Documentación**: Todas las versiones documentadas aquí

## 📦 Contenido Completo del Testbed

Este repositorio es **autosuficiente** e incluye:
- ✅ **Todo el software** necesario para la demostración
- ✅ **Documentación completa** de instalación y uso
- ✅ **Diagramas de conexión** de todos los componentes
- ✅ **Configuraciones optimizadas** para ferias
- ✅ **Versión especial del gateway** con mejoras para demos
- ✅ **Tests y validaciones** para funcionamiento confiable

## 🚀 Setup Completo del Testbed

1. **Hardware**: Montar según diagramas incluidos
2. **Gateway**: Usar la versión especial incluida (200ms + válvula)
3. **LEDs**: Configurar los 3 proyectos de iluminación
4. **Conexiones**: Seguir documentación específica de cada componente
5. **Pruebas**: Ejecutar tests incluidos antes del evento

---

**Sistema completo y autosuficiente para demostraciones técnicas** 🎪✨  
*Incluye versiones especiales optimizadas para ferias*
