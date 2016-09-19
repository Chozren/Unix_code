#include<stdio.h>
#include<utmpx.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define SHOWHOST            /*include remote machine on output */ 

int main()
{
    struct utmpx current_record;     /*read info into here */ 
    int         utmpfd;             /* read from this descriptor */ 
    int         reclen = sizeof (current_record);

    void show_info(struct utmpx *);

    if ((utmpfd = open (UTMPX_FILE, O_RDONLY)) == -1) {
        perror(UTMPX_FILE);          /* UTMPX_FILE is in utmpx_file.h */ 
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen)
        show_info (&current_record);
    close(utmpfd);
    return 0;
}
/* show_info()
 * displays contents of the utmp struct inhuman readable form
 * *note* these sizes shoul not be hardwired
 */ 
void show_info(struct utmpx *utbufp)
{

    void show_time();

   // if (utbufp->ut_type != USER_PROCESS)
     //   return;
    printf("%-8.8s", utbufp->ut_user);     /* the logname*/
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);     /* the tty */ 
    printf(" ");
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
