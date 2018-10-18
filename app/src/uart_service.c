#include "uart_service.h"
#include "sapi.h"

void printElevatorStatus() {
	char* miTexto = "hola\n\r";
	uartWriteString( UART_USB, miTexto );
}
