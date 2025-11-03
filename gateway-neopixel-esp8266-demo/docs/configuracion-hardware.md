# Configuración de Hardware - Control NeoPixel ESP8266

## ✨ Software Universal - Dos Configuraciones de Hardware

Este proyecto usa **el mismo código** para dos configuraciones diferentes de hardware. No necesitas cambiar nada en el software, solo el cableado físico.

### 🔧 Opción 1: 3 Pines Separados
- **Conexión**: D1, D2, D3 independientes
- **LEDs por pin**: 10 LEDs cada uno
- **Total LEDs**: 30 LEDs (10 + 10 + 10)
- **Ventajas**: 
  - Control independiente de cada sección
  - Mejor rendimiento en paralelo
  - Ideal para prototipos y desarrollo

### 🔧 Opción 2: Pin Único  
- **Conexión**: Solo D1 con tira continua
- **LEDs en serie**: 30 LEDs consecutivos
- **Comportamiento**: Los LEDs 0-9, 10-19, 20-29 simulan las 3 secciones
- **Ventajas**:
  - Menos cables y conexiones
  - Instalación más simple
  - Ideal para montajes permanentes

## � Cambio de Configuración

**¡No hay que cambiar código!** Solo modifica el hardware:

1. **Programa una vez** el ESP8266
2. **Cambia solo el cableado** según tus necesidades
3. **El mismo software funciona** en ambos casos automáticamente

## 📋 Conexiones de Hardware

### Modo 3 Pines Separados
```
ESP8266 NodeMCU v2    →    NeoPixel LEDs
├── D1 (GPIO5)        →    Tira 1 (10 LEDs)
├── D2 (GPIO4)        →    Tira 2 (10 LEDs)  
├── D3 (GPIO0)        →    Tira 3 (10 LEDs)
├── 5V                →    VCC (todas las tiras)
└── GND               →    GND (todas las tiras)
```

### Modo Pin Único
```
ESP8266 NodeMCU v2    →    NeoPixel LEDs
├── D1 (GPIO5)        →    Data Pin (30 LEDs en serie)
├── 5V                →    VCC
└── GND               →    GND
```

## ⚙️ Funcionamiento Inteligente

### Cómo Funciona la Magia ✨

El software **siempre envía datos a D1, D2 y D3**, pero:

**Con 3 pines conectados**: 
- D1 → controla LEDs 0-9 de la primera tira
- D2 → controla LEDs 0-9 de la segunda tira  
- D3 → controla LEDs 0-9 de la tercera tira

**Con 1 pin conectado**:
- D1 → controla LEDs 0-29 de la tira continua
- D2 → envía datos al aire (sin LEDs conectados)
- D3 → envía datos al aire (sin LEDs conectados)

El resultado visual es **idéntico** porque ambas configuraciones producen 30 LEDs controlados en 3 secciones lógicas.

## 🔍 Monitoreo del Sistema

Al iniciar, el monitor serie mostrará:
```
=== PRESENTACIÓN SIMPLE DEL LOGO ===
Hardware: D1, D2, D3 configurados (conectar según necesidades)
```

## 🛠 Consejos de Instalación

### Para Modo 3 Pines:
- Usar cables cortos y de buena calidad
- Considerar resistencias de 470Ω en cada línea de datos
- Verificar que todas las tiras compartan GND común

### Para Pin Único:
- Usar tira de LEDs WS2812B de 30 LEDs consecutivos
- Cable de datos robusto para toda la longitud
- Considerar condensadores de filtrado (1000µF) cerca de la alimentación
- Resistencia de 470Ω entre D1 y el primer LED

## 🎯 Resultado

**El mismo software funciona perfecto en ambas configuraciones** - es como tener un controlador universal que se adapta automáticamente a tu hardware. ¡Programa una vez, usa en cualquier configuración!