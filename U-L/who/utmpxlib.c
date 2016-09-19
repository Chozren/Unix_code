/* utmpxlib.c - functions to buffer reads from utmpx 
 *
 * functions are 
 *      utmpx_open(filename)    - open file 
 *          returns -1 on error
 *      utmpx_next()             -return pointer to next struct 
 *          returns NULL on eof
 *      utmpx_close             -close file 
 *
 * reads NRECS per read and then doles them out from the buffer 
 */

#include<stdio.h>
#include<unistd.h>
#include<utmpx.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>
#define NRECS 16
#define NULLUT ((struct utmpx *)NULL)
#define UTSIZE (sizeof(struct utmpx))

static char     utmpxbuf[NRECS * UTSIZE];       // storage
static int      num_recs;                       // num stored
static int      cur_rec;                        // next to go 
static int      fd_utmpx = -1;                  // read from 

int utmpx_open(char *filename)
{
    fd_utmpx = open(filename, O_RDONLY);        // open it
    cur_rec  = num_recs = 0;                    // no recs yet
    return fd_utmpx;                            //report
}

struct utmpx *utmpx_next()
{
    int utmpx_reload();
    struct utmpx *recp;
    if (fd_utmpx == -1)
        return NULLUT;
    if (cur_rec == num_recs && utmpx_reload() == 0)
        return NULLUT;
                                                //get address of record
    recp = (struct utmpx *) &utmpxbuf[cur_rec * UTSIZE];
    cur_rec++;
    return recp;
}
/*
 * read next bunch of records into buffer 
 */ 
int utmpx_reload()
{
    int amt_read;
    amt_read = read(fd_utmpx, utmpxbuf, NRECS * UTSIZE);
    num_recs = amt_read/UTSIZE;
    cur_rec = 0;
    return num_recs;
}


void utmpx_close()
{
    if (fd_utmpx != -1)
        close (fd_utmpx);
}
