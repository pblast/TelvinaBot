/*****************************************************************//**
 *   @file   lang.h
 *   @brief  Este archivo añade soporte al multilenguage. En el se recogen todas las cadenas que se mostrarán tanto por pantalla como por el bot en función del lenguaje seleccionado.
 *   @author PBL
*********************************************************************/

#ifndef LANG_H
#define LANG_H

#ifdef _LANG_AS
    #define INTROTERM "PROGRAMA DE TELVINA"
    #define ERRCONEXTERM " Nun se pue conectar con Telvina\n"
    #define OKCONEXTERM "Pudo crease la coexión con Telvina\n"
#elif _LANG_ES
    #define INTROTERM "PROGRAMA DE TELVINA"
    #define ERRCONEXTERM "No se puede conectar con Telvina\n"
    #define OKCONEXTERM "Se ha podido establecer la conexión con Telvina\n"
#endif
/********************************************************************/
/*                            DEFINES                               */
/********************************************************************/


/********************************************************************/
/*                          PROTOTIPOS                              */
/********************************************************************/

#endif
/************************** End of file******************************/
