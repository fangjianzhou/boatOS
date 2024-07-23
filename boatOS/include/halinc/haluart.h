
#ifndef _HALUART_H
#define _HALUART_H



void hal_uart0_putc(char_t c);

void init_haluart();
drvstus_t hal_uart_write(uint_t uart,void* buf,uint_t len);
drvstus_t hal_uart_read(uint_t uart,void* buf,uint_t* retlen);
drvstus_t hal_uart_ioctrl(uint_t uart,uint_t ctrlcode,void* ctrdata);
drvstus_t uart_send_char(uint_t uart,char_t ch);
drvstus_t uart_receive_char(uint_t uart,char_t* retch);

void init_uart0();
#endif // HALUART_H
