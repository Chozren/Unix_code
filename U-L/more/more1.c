/*
 * read and print 24 lines then pause for a few special commands
 */ 
#include<stdio.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more();

int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc == 1)
        do_more(stdin);
    else
        while (--agrc)
            if ((fp = fopen(* ++argv, "r")) != NULL)
            {
                do_more(fp);
                fclose(fp);
            }
            else
                exit(1);
    return 0;
}
void do_more(FILE *fp)
/*
 * read PAGELEN lines, then call see_more() for further instructions
*/ 
{
    char    line[LINELEN];
    int     num_of_lines = 0;
    int     reply;

    int see_more();

    while (fgets(line, LINELEN, fp)) {
        if (num_of_lines == PAGELEN) {  
            reply == see_more();
            if (reply == 0)
                break;
            num_of_lines -= reply;    
        }

    }

} 

