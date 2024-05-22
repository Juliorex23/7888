#include<avr/io.h>
#include<avr/interrupt.h>

ISR(ADC_vect){
float aux;

  aux=9.774*ADCW;   //Calcula el ciclo de trabajo
  OCR1A=aux;
  ADCSRA |=1 << ADSC; //Inicia una nueva conversión
}
int main(){

  DDRB=0xFF;    //Salida en OC1A (PB1)

  ADMUX=0x00;   //Selecciona ADC0 y Vref en AREF
  ADCSRA=0xCB;  //Habilita ADV con interrupción, inicia
                //Conversión y divide entre 8
  DIDR0=0x01;   //Anula el buffer digital en ADC0

  ICR1=9999;    //Valor máximo para 10ms
  TCCR1A=0x082; //PWM rápido, modo no convertido
  TCCR1B=0x19; //Reloj sin preescala
  sei();      //Habilitador global de interrupciones
  while(1)
    asm("NOP");
}
