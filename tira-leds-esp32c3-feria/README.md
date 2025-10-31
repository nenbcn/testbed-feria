# Simulación Flujo de Agua - ESP32-C3

Este proyecto simula visualmente el flujo de agua en una tira de 144 LEDs NeoPixel para demostraciones en stand de feria. El ESP32-C3 recibe señales de pulsos que representan el caudal de agua y controla la velocidad de la animación LED correspondientemente.

## 🎯 Función Específica

- **Propósito**: Demostración visual del sistema de monitoreo de agua en el stand
- **Funcionalidad**: Simula flujo de agua con velocidad variable según caudal real
- **Operación**: **Más pulsos = flujo más rápido = LEDs más veloces**
- **Uso**: Demostración interactiva para explicar el funcionamiento del sistema

## 🌊 Simulación de Flujo

El sistema visualiza el caudal de agua mediante:
1. **"Gotas de agua"** representadas por grupos de LEDs azul turquesa
2. **Velocidad proporcional** al caudal real recibido por pulsos del caudalímetro
3. **Flujo continuo** que se mueve a lo largo de los 144 LEDs (simula tubería)
4. **Espaciado entre gotas** para simular el flujo natural del agua

### 📊 Relación Caudal-Velocidad Visual
```
🐌 Caudal BAJO  (1-5 Hz)   → Flujo lento (gotas cada 1.5 segundos)
🚶 Caudal MEDIO (10-50 Hz) → Flujo normal (gotas cada 500ms)
🏃 Caudal ALTO  (100+ Hz)  → Flujo rápido (gotas cada 40ms)
❌ Sin señal               → Sin flujo (LEDs apagados = no hay agua)
```

## 🔧 Hardware Requerido

- **Seeeduino XIAO ESP32-C3** (microcontrolador principal)
- **Tira de 144 LEDs NeoPixel** (representa la tubería del sistema)
- **Pin D3**: Salida de datos para controlar LEDs
- **Pin D6**: Entrada de pulsos del caudalímetro real
- **Fuente 5V externa** para alimentar los 144 LEDs

## 📐 Conexiones para el Stand

```
ESP32-C3 Pin D3  →  Data Input de la tira NeoPixel (simulación agua)
ESP32-C3 Pin D6  →  Señal de pulsos del caudalímetro real instalado
5V externa       →  VCC tira NeoPixel (144 LEDs requieren potencia)
GND común        →  GND ESP32-C3 + GND LEDs + GND sistema gateway
```

## ⚡ Funcionamiento en Tiempo Real

1. **Conexión al sistema real**: Los pulsos vienen directamente del caudalímetro
2. **Visualización inmediata**: Cambios de caudal se reflejan al instante
3. **Demostración interactiva**: Visitantes ven el efecto en tiempo real
4. **Educativo**: Facilita explicar cómo funciona el monitoreo de agua

## 🎪 Para Demostraciones en Feria

- ✅ **Impacto visual**: 144 LEDs azul turquesa muy llamativos
- ✅ **Respuesta inmediata**: Cambios visibles al instante
- ✅ **Educativo**: Ayuda a explicar el sistema de forma visual
- ✅ **Interactivo**: Visitantes pueden ver causa-efecto
- ✅ **Realista**: Colores y movimiento simulan agua real

## 🚀 Instalación

```bash
cd tira-leds-esp32c3-feria
pio run --target upload
pio device monitor  # Ver funcionamiento en tiempo real
```

---

**Simulación visual para demostrar el sistema de monitoreo de agua** 🌊🎪
