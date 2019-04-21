#include "uart_service.h"

#define BASE_ASCII_NUMBERS 48

void printOpeningStatus(uint16_t time) {
	char text[23] = "\r\nAbriendo puerta. XXX%";
	text[19] = time/100 		+ BASE_ASCII_NUMBERS; // obtener 1 digito y convertir
	text[20] = (time/10) % 10 	+ BASE_ASCII_NUMBERS; // obtener 2 digito y convertir
	text[21] = time%10 			+ BASE_ASCII_NUMBERS; // obtener 3 digito y convertir

	uartWriteString( UART_USB, text );
}

void printClosingStatus(uint16_t time) {
	char text[23] = "Cerrando puerta. XXX% \n\r";
	text[19] = time/100 		+ BASE_ASCII_NUMBERS; // obtener 1 digito y convertir
	text[20] = (time/10) % 10 	+ BASE_ASCII_NUMBERS; // obtener 2 digito y convertir
	text[21] = time%10 			+ BASE_ASCII_NUMBERS; // obtener 3 digito y convertir

	uartWriteString( UART_USB, text );
}
