//------------------------------------------------------------------------------
//
//	File:		SerialDevice.cpp
//	Abstract:	Serial Device Abstraction
//	Version:	0.1
//	Date:		18.05.2016
//	Disclaimer:	This example code is provided by IMST GmbH on an "AS IS" basis
//				without any warranties.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//  Include Files
//------------------------------------------------------------------------------
#include "SerialDevice.h"

#include <xc.h>

//------------------------------------------------------------------------------
//  Section RAM
//------------------------------------------------------------------------------

// Todo : add your own platform specific variables here

//------------------------------------------------------------------------------
//  Section Code
//------------------------------------------------------------------------------

/**
 * Open
 * @brief: open serial device
 * 
 * Configura e Inicia el modulo/puerto serie.
 */
bool
SerialDevice_Open(UINT8         comNumber,
                  int           dataBits,
                  UINT8         parity)
{
    //UART, Ajustes comunes a Rx y Tx. Inicializado de acuerdo a datasheet 16F2550
    //Se prueba con 8(interno) y 7.3728(externo) MHz
    ////1: (En reset,SPBRG=0). Usar BRG16=1 y BRGH=1. Velocidades despues de PLL (si lo hay)
    SPBRG=16;   //Fosc=8 MHz (ejm,interno)
    //SPBRG=15;   //Fosc=7.3728 MHz (externo)
    SYNC=false; //2. Modo Asincrono
    BRG16=true;
    BRGH=true;
    SPEN=true; //2. Habilita Puerto Serie
    //TRANSMISOR
    TXEN=true; //6,Tx. Habilita transmisor
    //RECEPTOR
    CREN=true;  //6,Rx. Habilita receptor
    RCIE=true;  //7,Rx. Interrupcion por recepcion habilitada
    return SerialSentIsOpen();
}

/*
 * Simple check for the status of Tx module
 */
bool SerialSentIsOpen(void)
{
    return (bool)(SPEN && TXEN);
}

/**
 * Close
 * @brief: close serial device
 */
bool
SerialDevice_Close()
{
    SPEN=false; //2. Habilita Puerto Serie
    TXEN=false; //6,Tx. Habilita transmisor
    CREN=false;  //6,Rx. Habilita receptor
    return true;
}

/**
 * SendData
 * @brief: send data
 */
int
SerialDevice_SendData(UINT8* txBuffer, UINT8 txLength)
{
    for (UINT8 i=0;i<txLength;i++) {
        if (!SerialDevice_SendByte(txBuffer[i])) {
            //Escapes the error
            return false;
        }
    }
    return true;
}

/**
 * SendByte
 * @brief: send single byte
 */
int
SerialDevice_SendByte(UINT8 txByte)
{
    if (SerialSentIsOpen()) {
        while (!TRMT);  //Wait for a pending transmision, due to TSR busy
        TXREG=txByte;
        while (!TXIF);  //Wait while TXREG value are transferred to TSR
        return true;
    }
    return false;
}

/**
 * ReadData
 * @brief: read data
 */
int
SerialDevice_ReadData(UINT8* rxBuffer, int rxBufferSize)
{
    // Todo : add your own platform specific code here
    return -1;
}
//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
