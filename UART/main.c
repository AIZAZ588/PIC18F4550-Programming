/* * File: main.c * Author: aizaz * * Created on September 10, 2023, 8:31 AM */ void UART_INIT(unsigned long); void eusart_tx_data(char); char eusart_rx_data(void); void eusart_tx_str(char* ptr); #include #define _XTAL_FREQ 4000000 void main(void) { UART_INIT(9600); //char serial_data = 0; eusart_tx_str(" Welcome AIzaz!\r\n"); eusart_tx_str(" Please Enter 1 for ON \r\n 0 for OFF \r\n"); eusart_tx_str(" Enter choice : "); unsigned char choice =0; while(1) { choice = eusart_rx_data(); if (choice == '1' ) { eusart_tx_str(" LED ON! \r\n"); LATDbits.LATD0 =1; eusart_tx_str(" Enter choice : "); } else if (choice == '0') { eusart_tx_str(" LED OFF!\r\n"); LATDbits.LATD0 =0; eusart_tx_str(" Enter choice : "); } else { eusart_tx_str(" Wrong choice! \r\n"); eusart_tx_str(" Enter choice : "); } } return; } void UART_INIT(unsigned long async_baud_rate) { TRISCbits.RC6 =0; //RX TRISCbits.RC7 =1; //TX TRISDbits.RD0 =0; //LED SPBRG = (unsigned char) ((_XTAL_FREQ/4)/async_baud_rate -1); //Set baud rate TXSTAbits.BRGH =1; //high baud rate select bit TXSTAbits.SYNC =0; // Async TXSTAbits.TXEN =1; TXSTAbits.TX9 =0; //Select 8bit Transmission RCSTAbits.SPEN =1; //Serial Port Enable RCSTAbits.CREN =1; //Enable Continuous Receive RCSTAbits.RX9 =0; //8bit reception BAUDCONbits.BRG16 =1; } void eusart_tx_data(char c8_data) { while (!TXIF ); //waiting until TXIF gets low TXREG = c8_data; } char eusart_rx_data(void) { while(!RCIF); return RCREG; } void eusart_tx_str(char* ptr) { while(*ptr != 0) { eusart_tx_data(*ptr++); } }