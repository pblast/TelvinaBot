
/***************************************************************************//**
 *   @file   botTelegram.c
 *   @brief  Este archivo contiene las funciones principales que se utilizarn
 *           para el control de la API de telegram
 *   @author PBL
*******************************************************************************/

/******************************************************************************/
/*                                 INCLUDES                                   */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

#include "main.h"
#include "botTelegram.h"



/******************************************************************************/
/*                          VARIABLES DE MÓDULO                               */
/******************************************************************************/
    struct string s;
    struct chat chatIn;
    long lastMSG = 0;

/******************************************************************************/
/*                                FUNCIONES                                   */
/******************************************************************************/

/**
 * Función para inicializar la cadena en la que se guardarán los datos recibidos
 * @param s Estructura que contiene el puntero de inicio de la cadena y su
 *          longitud
 */
    void init_string (struct string *s) {
        s->len = 0;
        s->ptr = malloc (s->len + 1);
        if (s->ptr == NULL) {
            exit (EXIT_FAILURE);
        }
        s->ptr[0] = '\0';
    }


size_t writefunc (void *ptr, size_t size, size_t nmemb, struct string *s){
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc (s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        exit (EXIT_FAILURE);
    }
    memcpy (s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}

/**
 * Función para hacer una peticin GETME a la API
 * @return  Devuelve un 0 si todo ha ido bien o un entero positivo en caso contrario
 */
    int getMSG (int cmd){
        char strURL[100];
        CURL *curl;
        CURLcode res;

        init_string (&s);

        curl_global_init (CURL_GLOBAL_DEFAULT);

        curl = curl_easy_init ();
        if (! curl) {
            return 1;
        }

        /* Fijamos en las opciones de curl la dirección a la que acceder */
        switch (cmd) {
        case 0:
            sprintf (strURL, "%s%s%s", BOTURL, TelBot.token, GETMEURL);
            break;
        case 1:
            sprintf (strURL, "%s%s%s", BOTURL, TelBot.token, GETUPDATESURL);
            if (lastMSG != 0) {
                sprintf (strURL, "%s?offset=%ld", strURL, lastMSG);
            }
            break;
        default:
            return 1;
            break;
        }

        curl_easy_setopt (curl, CURLOPT_URL, strURL);
        /* but in that case we also tell libcurl to follow redirection */
        curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt (curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform (curl);

        /* Check for errors */
        if (res != CURLE_OK) {
            return 1;
        }

        if (! parseMSG (&s)) {
            sendMSG (chatIn.cid, "bur");
        }
        /* always cleanup */
        curl_easy_cleanup (curl);

        return 0;
    }


/**
 * Función para enviar un mensaje a través del bot
 * @param  chat_id Identificador del usuario al que se quiere enviar el mensaje
 * @param  texto   Texto que se quiere enviar al usuario indicado
 * @return         Devuelve un 0 si todo ha ido bien y un entero positivo en caso
 *                 de haberse producido algún error
 */
    int sendMSG (long chat_id, char* texto){
        char strURL[1000];
        CURL *curl;
        CURLcode res;

        init_string (&s);

        curl_global_init (CURL_GLOBAL_DEFAULT);

        curl = curl_easy_init ();

        if (! curl) {
            return 1;
        }

        sprintf (strURL, "%s%s%s", BOTURL, TelBot.token, SENDMSGURL);
        sprintf (strURL, "%s?chat_id=%ld&text=%s", strURL, chat_id, texto);

        curl_easy_setopt (curl, CURLOPT_URL, strURL);

        /* but in that case we also tell libcurl to follow redirection */
        curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt (curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform (curl);

        /* Check for errors */
        if (res != CURLE_OK) {
            return 1;
        }

        /* always cleanup */
        curl_easy_cleanup (curl);

        return 0;
    }


/**
 * Función para extraer los datos de un nuevo mensaje recibido. Los datos son
 * almacenados en una estructura de tipo chat.
 * @param  s Cadena de texto que contiene los datos del mensaje recibido en
 *           formato de texto plano
 * @return   Devuelve un 0 si todo ha ido bien y un entero positivo en caso
 *           de producirse un error
 */
    int parseMSG (struct string *s){
        char* inicio = 0;
        char* straux1 = NULL;
        char* straux2 = NULL;
        int len;

        // fprintf (stdout, "MSG(0):  %s  \n-----------------\n", s->ptr);
        /* Se parsea el ID de la actualización */
        inicio = strstr (s->ptr, "update_id\":");

        if (inicio == NULL) {
            return 1;
        }

        // fprintf(stdout,"INICIO: %d\n",inicio);
        straux1 = inicio + strlen ("update_id\":");
        straux2 = strstr (straux1, ",");
        len = straux2 - straux1;
        *(straux1 + len) = 0;
        inicio = straux1 + len + 1;
        chatIn.update_id = atol (straux1);
        lastMSG = chatIn.update_id + 1;
        // fprintf (stdout, "update_id: %s\n", straux1);
        // fprintf (stdout, "update_id: %s\n", straux1);

        /* Se parsea el ID del mensaje recibido */
        inicio = strstr (inicio, "message_id\":");
        straux1 = inicio + strlen ("message_id\":");
        straux2 = strstr (straux1, ",");
        len = straux2 - straux1;
        *(straux1 + len) = 0;
        inicio = straux1 + len + 1;
        chatIn.msg_id = atol (straux1);
        // fprintf (stdout, "message_id: %s\n", straux1);
        // fprintf (stdout, "message_id: %s\n", straux1);

        /* Se parsea el ID del remitente */
        inicio = strstr (inicio, "\"from\":{\"id\":");
        straux1 = inicio + strlen ("\"from\":{\"id\":");
        straux2 = strstr (straux1, ",");
        len = straux2 - straux1;
        *(straux1 + len) = 0;
        inicio = straux1 + len + 1;
        chatIn.cid = atol (straux1);
        // fprintf (stdout, "id: %s\n", straux1);
        // fprintf (stdout, "id: %s\n", straux1);

        /* Se parsea el nombre del remitente */
        inicio = strstr (inicio, "first_name\":\"");
        straux1 = inicio + strlen ("first_name\":\"");
        straux2 = strstr (straux1, "\"");
        len = straux2 - straux1;
        *(straux1 + len) = 0;
        inicio = straux1 + len + 1;
        chatIn.nome = straux1;
        // fprintf (stdout, "nome:  %s\n", straux1);
        // fprintf (stdout, "nome:  %s\n", straux1);

        /* Se parsea el apellido del remitente */
        inicio = strstr (inicio, "last_name\":\"");
        straux1 = inicio + strlen ("last_name\":\"");
        straux2 = strstr (straux1, "\"");
        len = straux2 - straux1;
        *(straux1 + len) = 0;
        inicio = straux1 + len + 1;
        chatIn.nome = straux1;
        // fprintf (stdout, "apelliu:  %s\n", straux1);
        // fprintf (stdout, "apelliu:  %s\n", straux1);


        /* Se parsea la fecha del mensaje */
        inicio = strstr (inicio, "date\":");
        straux1 = inicio + strlen ("date\":");
        straux2 = strstr (straux1, ",");
        len = straux2 - straux1;
        *(straux1 + len) = 0;
        inicio = straux1 + len + 1;
        chatIn.fecha = atol (straux1);
        // fprintf (stdout, "fecha: %s\n", straux1);
        // fprintf (stdout, "fecha: %s\n", straux1);

        /* Se parsea el texto del mensaje */
        inicio = strstr (inicio, "text\":\"");
        if (inicio != NULL) {
            straux1 = inicio + strlen ("text\":\"");
            straux2 = strstr (straux1, "\"");
            len = straux2 - straux1;
            *(straux1 + len) = 0;
            inicio = straux1 + len + 1;
            chatIn.nome = straux1;
        }
        // fprintf (stdout, "texto:  %s\n", straux1);
        // fprintf (stdout, "texto:  %s\n", straux1);

        // // straux1=straux2+1;
        // fprintf(stdout, "MSG:  %s  \n\nxxxxxxxxxxxxx\n\n", inicio);
        // fprintf (stdout, "MSG:  %s  \n\nxxxxxxxxxxxxx\n\n", inicio);
        return 0;
    }
/******************************* End of file***********************************/
