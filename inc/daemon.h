/***************************************************************************//**
 *   @file   daemon.h
 *   @brief  Archivo que recoge las estructuras, definiciones y prototipos
 *           necesarios para la creación de un demonio y conseguir que el
 *           programa se ejecute en segundo plano
 *   @author PBL
*******************************************************************************/

#ifndef DAEMON_H
#define DAEMON_H


//******************************************************************************/
/*                                  DEFINES                                   */
/******************************************************************************/


/******************************************************************************/
/*                                  PROTOTIPOS                                */
/******************************************************************************/

    int startDaemon(void);
    int stopDaemon(void);


#endif
/******************************* End of file***********************************/
