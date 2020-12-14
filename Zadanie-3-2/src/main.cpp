#include <Arduino.h>
#include <stdint.h>

#define FOSC 16000000
#define BAUD 9600
#define MY_UBRR (FOSC / 16 / BAUD-1)
#define USE_UART_RX_IRQ 0
char ReceivedChar;
char Message[] = "Hello";
char *pMessage = Message; 
void setup(){
  UBRR0H = (MY_UBRR >> 8);
  UBRR0L = MY_UBRR;
  UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
  UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);

 while (*pMessage){
  while ( !(UCSR0A & (1<<UDRE0)) );
  UDR0 = *pMessage;
  pMessage++;
  }
  #if (USE_UART_RX_IRQ == 1)
  UCSR0B |= (1<<RXCIE0);
  #endif
}

void loop(){
  #if (USE_UART_RX_IRQ == 0)
  while (! (UCSR0A & (1<<RXC0)))
  ;
  ReceivedChar = UDR0; 
  while (!(UCSR0A & (1<< UDRE0)))
  ;
  UDR0 = ReceivedChar; 
  #endif
}
#if (USE_UART_RX_IRQ ==1)
ISR (USART_RX_vect){
  ReceivedChar = UDR0;
  UDR0 = ReceivedChar;
}
#endif