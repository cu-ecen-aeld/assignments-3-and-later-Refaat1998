#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char* argv[])
{


FILE *fptr = NULL;

openlog ("writerprog", LOG_CONS | LOG_PID | LOG_NDELAY | LOG_PERROR, LOG_USER);

if (argc <= 2)
{
   syslog(LOG_ERR, "Invalid number of arguments");
   exit(1);
}

fptr = fopen(argv[1], "w");


if (fptr == NULL)
{
   printf("Error opening/creating a file\n");
   syslog(LOG_ERR, "Error opening a file");
   exit(1);
}



fprintf(fptr, "%s",argv[2]);
syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
fclose(fptr);





//syslog (LOG_MAKEPRI(LOG_USER, LOG_WARNING), "Program started by User %d", getuid ());
//syslog (LOG_INFO, "A tree falls in a forest");



closelog ();


}
