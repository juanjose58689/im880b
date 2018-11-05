#include "hcsr04.h"

bool HCread (int *buffer) { //*  buffer declara la variable tipo puntero de entero
    int i=0;
    RC4=true;               // Inicia pulso
    __delay_us(HC_DELAY_WAITING_TRIGGER); // Hace el pulso para que el sensor se active
    RC4=false;              // Termina pulso
    while(RC4 == false){
        i=i+1;
        __delay_us(10);
        if(i>100)
            return false;//permite saber si el sensor esta desconectado
    }
    i=0;
    while(RC4 == true){
        i=i+1;
        __delay_us(10);
    }
    *buffer=(unsigned int)(5*i/29);     //Conversion para medida en centimetro y  *buffer asigna al contenido de la direcciom
    return true;
}
