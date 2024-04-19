

#ifndef PWM2_H_
#define PWM2_H_

#include <stdint.h>
#include <avr/io.h>

#define invertido 1
#define no_invertido 0



//Funcion para configurar PWM2 modo Fast canal A 
void initPWM2FastA(uint8_t inverted, uint16_t prescaler){
	DDRB |= (1<<PB1); // Configurar PB1 como salida
	ADMUX |= (1<<REFS0) | (1<<MUX0); // Establece el voltaje de referencia en AVCC y selecciona ADC1 como entrada
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // Habilita ADC y establece el prescaler en 64

	TCCR1A |= (1<<COM1A1) | (1<<WGM11); // PWM rápido, modo no inversor
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10); // Fast PWM, prescaler = 1024
	ICR1=39999;  //Período PWM de 20 ms
	
	
}

void updateDutyCycleA(uint8_t duty){
	OCR2A = duty;
}






#endif /* PWM2_H_ */