/*****************************************************************//**
 *   @file   daemon.c
 *   @brief  Archivo que recoge las funciones necesarias para la creacin de un demonio que se ejecute en segundo plano
 *   @author PBL
*********************************************************************/

/********************************************************************/
/*                           INCLUDES                               */
/********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include  <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



/********************************************************************/
/*                           FUNCIONES                              */
/********************************************************************/

int startDaemon (void){
    pid_t id_process = 0;
    pid_t sid = 0;

    /* Se crea el proceso hijo y se comprueba si ha habido algun fallo en la cración. De haberlo se sale devolviendo error */
    id_process = fork ();

    if (id_process < 0) {
        printf ("fork failed!\n");
        return 1;
    }

    umask (0);

    sid = setsid ();

    if (sid < 0) {
        exit (EXIT_FAILURE);
    }
    if ((chdir ("/")) < 0) {
        exit (EXIT_FAILURE);
    }

    close (STDIN_FILENO);
    close (STDOUT_FILENO);
    close (STDERR_FILENO);
    return 0;
}


/************************** End of file******************************/
