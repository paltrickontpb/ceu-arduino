#include <avr/io.h>
#include <avr/interrupt.h>
//Not Required, but still written for elucidation

#define ADC1 0
#define ADC2 1

volatile int readFlag;
volatile int analogVal;
int channel = 0;

void setup(){
  ADMUX &= ~(1 << 5);
  ADMUX |= (1 << 6);
  ADMUX &= ~((1 << 3)|(1 << 2)|(1 << 1)|1); // Set to mux 0 ie. A0
  //ADMUX |= (1 << 3); // Channel 8 Selection (Internal Temparature)
  ADCSRA |= (1 << 7);
  ADCSRA |= (1 << 5);
  ADCSRB &= ~((1 << 2)|(1 << 1)|1);
  ADCSRA |= ((1 << 2)|(1 << 1)|1);
  ADCSRA |= (1 << 3);
  sei();
  readFlag = 0;
  ADCSRA |= (1 << 6);

  Serial.begin(9600);
}


void loop(){
  if (readFlag == 1){
    readFlag = 0;
    switch(channel){
      case 0:
        Serial.println("X : ");
        Serial.print(analogVal);
        channel += 1;
        ADMUX |= (1 << ADC1);
      break;
      case 1:
        Serial.println("Y : ");
        Serial.print(analogVal);
        channel += 1;
        ADMUX &= ~((1 << 3)|(1 << 2)|(1 << 1)|1);
        ADMUX |= (1 << ADC2);
      break;
      case 2:
        Serial.println("Z : ");
        Serial.print(analogVal);
        channel = 0;
        ADMUX &= ~((1 << 3)|(1 << 2)|(1 << 1)|1);
      break;
    }
  }
}

ISR(ADC_vect){
  readFlag = 1;
  analogVal = ADCL | (ADCH << 8);
}
