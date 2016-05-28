/***************************************************************************//**
 *   @file   config.c
 *   @brief  Este archivo contiene las funciones necesarias para configurar el
 *           funcionamiento del bot. Tanto en su arranque como en la interacción
 *           con los usuarios. Esta configuración se basará en la carga de un
 *           fichero que definirá las caracteristicas del bot. En el se
 *           contendrá el TOKEN, el ID del usuario administrador y de los demas
 *           usuarios que tienene permiso de uso del bot, así como sus
 *           preferencias de uso.
 *   @author PBL
*******************************************************************************/

/******************************************************************************/
/*                                  INCLUDES                                  */
/******************************************************************************/
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "config.h"
    #include "botTelegram.h"
    #include "main.h"

/******************************************************************************/
/*                                  FUNCIONES                                 */
/******************************************************************************/

    /**
     * Función para leer los datos guardados en el archivo de configuración del
     * bot y poder así inicializar el bot. Los datos que se leeen son el token,
     * el id del administrador y los ids de los usuarios con acceso. Estos
     * parámetros se guardan en una estructura
     * @return  Devuelve un 0 si todo ha ido bien y un entero positivo en caso
     *          contrario.
     */
    int CargaConfig(const char* archivo){
        FILE *configFile;
        char linea[50];

        /* TODO: Se debe acabar la carga de los parámetros de configuración.
        Faltaría la lista de usuarios permitidos */
        configFile=fopen(archivo,"r");

        if(configFile==NULL)
            return 1;

        while(fscanf(configFile,"%s",linea)!=EOF){
            if(!strcmp(linea,"[TOKEN]")){
                fscanf(configFile,"%s",linea);
                memcpy(TelBot.token,linea,strlen(linea));

                fprintf(stdout, "TOKEN: %s\n", TelBot.token);
            }
            if(!strcmp(linea,"[ADMIN_ID]")){
                fscanf(configFile,"%s",linea);
                TelBot.adminId=atol(linea);

                fprintf(stdout, "ADMIN_ID: %ld\n", TelBot.adminId);
            }

        }

        fprintf(stdout, "Se ha leido todo el archivo\n");

        return 0;
    }


/******************************* End of file***********************************/
