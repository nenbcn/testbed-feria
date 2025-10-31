/*
 * Test básico para el proyecto NeoPixel ESP8266
 * Este archivo contiene pruebas unitarias simples
 */

#include <Arduino.h>
#include <unity.h>

// Función para probar la inicialización básica
void test_basic_initialization() {
    // Test que siempre pasa para verificar que el framework funciona
    TEST_ASSERT_EQUAL(true, true);
}

// Test para verificar que los pines están definidos correctamente
void test_pin_definitions() {
    TEST_ASSERT_EQUAL(D1, 5);  // D1 = GPIO5
    TEST_ASSERT_EQUAL(D2, 4);  // D2 = GPIO4  
    TEST_ASSERT_EQUAL(D3, 0);  // D3 = GPIO0
}

// Test para verificar configuraciones básicas
void test_configuration_values() {
    const int NUM_LEDS = 10;
    const int BRIGHTNESS = 50;
    
    TEST_ASSERT_GREATER_THAN(0, NUM_LEDS);
    TEST_ASSERT_LESS_OR_EQUAL(255, BRIGHTNESS);
    TEST_ASSERT_GREATER_OR_EQUAL(0, BRIGHTNESS);
}

void setup() {
    delay(2000); // Espera para que se inicialice el puerto serie
    
    UNITY_BEGIN();
    
    RUN_TEST(test_basic_initialization);
    RUN_TEST(test_pin_definitions);
    RUN_TEST(test_configuration_values);
    
    UNITY_END();
}

void loop() {
    // Los tests se ejecutan una sola vez en setup()
}