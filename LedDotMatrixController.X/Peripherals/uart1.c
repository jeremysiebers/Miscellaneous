/**
  Section: Included Files
 */
#include "uart1.h"
#include <xc.h>

/**
  Section: Macro Declarations
 */
#define EUSART1_TX_BUFFER_SIZE 20
#define EUSART1_RX_BUFFER_SIZE 20
#define FP 20000000
#define BAUDRATE 19200
#define BRGVAL 64//(unsigned char)((FP/BAUDRATE)/16)-1

/**
  Section: Global Variables
 */

static uint8_t eusart1TxHead = 0;
static uint8_t eusart1TxTail = 0;
static uint8_t eusart1TxBuffer[EUSART1_TX_BUFFER_SIZE];
volatile uint8_t eusart1TxBufferRemaining;

static uint8_t eusart1RxHead = 0;
static uint8_t eusart1RxTail = 0;
static uint8_t eusart1RxBuffer[EUSART1_RX_BUFFER_SIZE];
volatile uint8_t eusart1RxCount;

/**
  Section: EUSART1 APIs
 */

void EUSART1_Initialize(void) {
    // disable interrupts before changing states
    PIE1bits.RCIE = 0;
    PIE1bits.TXIE = 0;

    // Set the EUSART1 module to the options selected in the user interface.

    // ADDEN disabled; RX9 8-bit; RX9D 0x0; FERR no_error; CREN enabled; SPEN enabled; SREN disabled; OERR no_error; 
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9  = 0;
    RCSTAbits.SREN = 0;
    RCSTAbits.CREN = 1;
    RCSTAbits.FERR = 0;
    RCSTAbits.OERR = 0;
    RCSTAbits.RX9D = 0;
    
    // CSRC slave_mode; TRMT TSR_empty; TXEN enabled; BRGH hi_speed; SYNC asynchronous; SENDB sync_break_complete; TX9D 0x0; TX9 8-bit; 
    TXSTAbits.CSRC = 0;
    TXSTAbits.TX9  = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    TXSTAbits.TRMT = 0;            
    TXSTAbits.TX9D = 0;

    // Baud Rate = 19200; see datasheet
    SPBRG = BRGVAL;

    // initializing the driver state
    eusart1TxHead = 0;
    eusart1TxTail = 0;
    eusart1TxBufferRemaining = sizeof (eusart1TxBuffer);

    eusart1RxHead = 0;
    eusart1RxTail = 0;
    eusart1RxCount = 0;

    // enable receive interrupt
    PIE1bits.RCIE = 1;
}

/*
uint8_t EUSART1_Read(void) {
    uint8_t readValue = 0;

    if (0 == eusart1RxCount) {
        readValue = 0;
    }
    else
    {
        PIE1bits.RC1IE = 0;

        readValue = eusart1RxBuffer[eusart1RxTail++];
        if (sizeof (eusart1RxBuffer) <= eusart1RxTail) {
            eusart1RxTail = 0;
        }
        eusart1RxCount--;
        PIE1bits.RC1IE = 1;
    }
    return readValue;
}
*/

uint8_t EUSART1_Read(void) {
    uint8_t readValue = 0;

    while (0 == eusart1RxCount) {
    }

    PIE1bits.RCIE = 0;

    readValue = eusart1RxBuffer[eusart1RxTail++];
    if (sizeof (eusart1RxBuffer) <= eusart1RxTail) {
        eusart1RxTail = 0;
    }
    eusart1RxCount--;
    PIE1bits.RCIE = 1;

    return readValue;
}

void EUSART1_Write(uint8_t txData) {
    while (0 == eusart1TxBufferRemaining) {
    }

    if (0 == PIE1bits.TXIE) {
        TXREG = txData;
    } else {
        PIE1bits.TXIE = 0;
        eusart1TxBuffer[eusart1TxHead++] = txData;
        if (sizeof (eusart1TxBuffer) <= eusart1TxHead) {
            eusart1TxHead = 0;
        }
        eusart1TxBufferRemaining--;
    }
    PIE1bits.TXIE = 1;
}

void putch(char txData) {
    EUSART1_Write(txData);
}

void EUSART1_Transmit_ISR(void) {

    // add your EUSART1 interrupt custom code
    if (sizeof (eusart1TxBuffer) > eusart1TxBufferRemaining) {
        TXREG = eusart1TxBuffer[eusart1TxTail++];
        if (sizeof (eusart1TxBuffer) <= eusart1TxTail) {
            eusart1TxTail = 0;
        }
        eusart1TxBufferRemaining++;
    } else {
        PIE1bits.TXIE = 0;
    }
}

void EUSART1_Receive_ISR(void) {
    if (1 == RCSTAbits.OERR) {
        // EUSART1 error - restart

        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

    // buffer overruns are ignored
    eusart1RxBuffer[eusart1RxHead++] = RCREG;
    if (sizeof (eusart1RxBuffer) <= eusart1RxHead) {
        eusart1RxHead = 0;
    }
    eusart1RxCount++;
}
/**
  End of File
 */
