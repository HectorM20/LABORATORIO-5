//***********************************************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Héctor Martínez - 22369
// Proyecto: LAB 5
// Hardware: ATmega328p
//***********************************************************************************************

#include <avr/io.h>
#include <util/delay.h>

#define SERVO_MIN_POS 1999 // 0 grados
#define SERVO_MAX_POS 3999 // 180 grados


uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);


{

	while (1){
		ADCSRA |= (1<<ADSC); // Iniciar la conversión de ADC
		while (ADCSRA & (1<<ADSC));
		uint16_t pot_val = ADC; // Leer el resultado del ADC
		uint16_t servo_pos = map(pot_val, 0, 1023, SERVO_MIN_POS, SERVO_MAX_POS); //asigna posición
		OCR2A = servo_pos;
		_delay_ms(100); // Retraso para que el servo alcance la posición
	}
}

int main(void)
{
	initPWM2FastA(no_invertido, 1024)

	while (1){
		ADCSRA |= (1<<ADSC); // Iniciar la conversión de ADC
		while (ADCSRA & (1<<ADSC)); 
		uint16_t pot_val = ADC; // Leer el resultado del ADC
		uint16_t servo_pos = map(pot_val, 0, 1023, SERVO_MIN_POS, SERVO_MAX_POS); //asigna posición
		OCR1A = servo_pos;
		_delay_ms(100); // Retraso para que el servo alcance la posición
	}
}

{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
// Función para inicializar ADC
void ADC_init() {
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
// Habilitar ADC
	ADCSRA |= (1 << ADEN);

// Establece el voltaje de referencia en AVCC
	ADMUX |= (1 << REFS0);
}

// Función para leer el valor ADC
uint16_t ADC_read(uint8_t adc_canal) {
//Selecciona el canal ADC
	ADMUX = (ADMUX & 0xF0) | (adc_canal & 0x0F);
	
// Iniciar la conversión ADC
	ADCSRA |= (1 << ADSC);
	
// Espera a que se complete la conversión
	while (ADCSRA & (1 << ADSC));
	
// Devuelve el resultado del ADC
	return ADC;
}

// Función para inicializar PWM
void PWM_init() {
	// Definir PB2 como salida
	DDRB |= (1 << DDRB2);
	
// Establece el modo no inversor para PWM
	TCCR1A |= (1 << COM1A1);

// Establece el modo PWM rápido, 8 bits
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	
// Establece el preescalador en 64
	TCCR1B |= (1 << CS11) | (1 << CS10);
}

// Función para ajustar el ciclo de trabajo de PWM según el valor de ADC
void adjustPWM(uint16_t adc_value) {
// Escala el valor de ADC para que coincida con el rango de PWM (0-255)
	uint8_t duty_cycle = adc_value >> 2; // Desplazamiento a la derecha de 2 bits para convertir el valor ADC de 10 bits a 8 bits
	
// Establecer el ciclo de trabajo PWM
	OCR1A = duty_cycle;
}

int main() {
// Inicializar PWM
	ADC_init();
	PWM_init();
	uint16_t adc_value;
	
	// Main loop
	while (1) {
// Leer el valor ADC del potenciómetro conectado al canal 0 del ADC (pin A0)
		adc_value = ADC_read(0);
		
//Ajusta el ciclo de trabajo de PWM según el valor de ADC
		adjustPWM(adc_value);
		
		_delay_ms(10);
	}
	return 0;
}


