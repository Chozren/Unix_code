/* who2.c - who is buffered reads
 *  - surpresses empty records
 *  - formats time nicely
 *  - buffered input (using utmplib)
 */ 

#include<stdio.h>
#include<sys/types.h>
#include<utmpx.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>

int main ()
{
    int utmpx_open(char *);
    void utmpx_close();
    void show_info(struct utmpx *);
    struct utmpx *utbufp,
                 *utmpx_next();

    if (utmpx_open(UTMPX_FILE) == -1) {
        perror(UTMPX_FILE);
        exit(1);
    }

    while ((utbufp = utmpx_next()) != ((struct utmpx *)NULL))
        show_info (utbufp);
    utmpx_close();
    return 0;
}

void show_info(struct utmpx *utbufp)
{

    void show_time();

   // if (utbufp->ut_type != USER_PROCESS)
     //   return;
    printf("%-8.8s", utbufp->ut_user);     /* the logname*/
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);     /* the tty */ 
    printf(" ");
    printf("%d", utbufp->ut_pid);
    show_time();
# ifdef SHOWHOST
    if (utbufp->ut_host[0] != '\0')
        printf("(%s)", utbufp->ut_host);        /* the host */ 
# endif
    printf("\n");
} 

/* showtime */
void show_time()
{   
    char buf[100];
    time_t t;
    time(&t);
    struct tm *tim = localtime(&t);
        
    strftime(buf, 100, " %b %e  %R", tim);  /* login time */ 
    printf("%s", buf);     
    printf(" ");
}
