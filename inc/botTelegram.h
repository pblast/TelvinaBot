/***************************************************************************//**
 *   @file   botTelegram.h
 *   @brief  Archivo que contiene los prototipos, variables y estructuras
 *           necesarias para el envo y recepcin de mensajes de un bot de telegram
 *   @author PBL
*******************************************************************************/

#ifndef BOTELEGRAM_H
#define BOTELEGRAM_H


/******************************************************************************/
/*                                  DEFINES                                   */
/******************************************************************************/

#define BOTURL          "https://api.telegram.org/bot"
#define GETMEURL        "/getMe"
#define GETUPDATESURL   "/getUpdates"
#define SENDMSGURL      "/sendMessage"


/******************************************************************************/
/*                                ESTRUCTURAS                                 */
/******************************************************************************/

    struct string {
        char *ptr;
        size_t len;
    };

    struct chat{
        long update_id;
        long msg_id;
        long cid;
        long fecha;
        char* nome;
        char* apelliu;
        char* texto;
    };


/******************************************************************************/
/*                            VARIABLES GLOBALES                              */
/******************************************************************************/

    extern struct string s;


/******************************************************************************/
/*                                PROTOTIPOS                                  */
/******************************************************************************/

    void init_string (struct string *s);
    size_t writefunc (void *ptr, size_t size, size_t nmemb, struct string *s);
    int getMSG (int cmd);
    int sendMSG(long chat_id,char* texto);
    int parseMSG(struct string *s);


#endif
/******************************* End of file***********************************/
