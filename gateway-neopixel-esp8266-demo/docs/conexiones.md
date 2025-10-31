# Diagrama de Conexiones - Control NeoPixel ESP8266

```
                    ESP8266 NodeMCU
                    ┌─────────────┐
                    │             │
                    │    D1(5)    ├─────┐
                    │             │     │
                    │    D2(4)    ├─────┼─────┐
                    │             │     │     │
                    │    D3(0)    ├─────┼─────┼─────┐
                    │             │     │     │     │
                    │    3V3      ├─────┼─────┼─────┼─────── VCC (Para pocos LEDs)
                    │             │     │     │     │
                    │    GND      ├─────┼─────┼─────┼─────── GND común
                    │             │     │     │     │
                    └─────────────┘     │     │     │
                                        │     │     │
    ┌───────────────────────────────────┘     │     │
    │                                         │     │
    │   Tira NeoPixel 1                       │     │
    │   ┌─────┬─────┬─────┬─────┐            │     │
    │   │ LED │ LED │ LED │ ... │            │     │
    │   │  1  │  2  │  3  │     │            │     │
    │   └─────┴─────┴─────┴─────┘            │     │
    │   Din                                   │     │
    │                                         │     │
    └─────────────────────────────────────────┘     │
                                                    │
        ┌───────────────────────────────────────────┘
        │
        │   Tira NeoPixel 2
        │   ┌─────┬─────┬─────┬─────┐
        │   │ LED │ LED │ LED │ ... │
        │   │  1  │  2  │  3  │     │
        │   └─────┴─────┴─────┴─────┘
        │   Din
        │
        └───────────────────────────────────────────┐
                                                    │
                                                    │
            ┌───────────────────────────────────────┘
            │
            │   Tira NeoPixel 3
            │   ┌─────┬─────┬─────┬─────┐
            │   │ LED │ LED │ LED │ ... │
            │   │  1  │  2  │  3  │     │
            │   └─────┴─────┴─────┴─────┘
            │   Din
            │
            └───────────────────────────────────────────


CONEXIONES DETALLADAS:
======================

ESP8266 Pin D1 (GPIO5)  →  Data Input Tira NeoPixel 1
ESP8266 Pin D2 (GPIO4)  →  Data Input Tira NeoPixel 2  
ESP8266 Pin D3 (GPIO0)  →  Data Input Tira NeoPixel 3

ALIMENTACIÓN:
=============

Opción 1 - Pocos LEDs (1-5 por tira):
ESP8266 3V3  →  VCC todas las tiras
ESP8266 GND  →  GND todas las tiras

Opción 2 - Muchos LEDs (recomendada):
Fuente externa 5V  →  VCC todas las tiras
Fuente externa GND →  GND todas las tiras + ESP8266 GND

COMPONENTES OPCIONALES:
=======================

- Resistencia 470Ω entre cada pin D1/D2/D3 y Din del NeoPixel
- Capacitor 1000µF entre VCC y GND de la fuente externa
- Fusible en la línea de alimentación principal

NOTAS IMPORTANTES:
==================

1. Para más de 15 LEDs total, usa fuente externa de 5V
2. Calcula 60mA por LED a máximo brillo
3. Conecta GND común entre ESP8266 y fuente externa
4. Los NeoPixels WS2812B funcionan con 3.3V de datos
5. Pin D3(GPIO0) se usa para boot - evita pull-down externo
```