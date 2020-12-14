#include <Arduino.h>
#define ADC_RESOLUTION_DEFAULT (5.0f / 1024.0f)

uint16_t digital;
float Voltage;

uint16_t ADCsingleREAD(uint8_t adcToUse){
uint16_t ADCval;

ADMUX = adcToUse;
ADMUX |= (1 << REFS0);
ADMUX &= ~(1 << ADLAR);
ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
ADCSRA |= (1 << ADEN);
ADCSRA |= (1 << ADSC);
while (ADCSRA & (1 << ADSC))
  ;
ADCval = ADCL;
ADCval = (ADCH << 8 ) + ADCval;

return ADCval; 
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  digital = ADCsingleREAD(0);
  Voltage = ADC_RESOLUTION_DEFAULT * digital;
  Serial.print("A0 = 102");
  Serial.print(digital);
  Serial.print(" \t V(0) = 0,5");
  Serial.print(Voltage);
  Serial.println(" [V]");
  delay(1000);
}