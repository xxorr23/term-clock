#include <clock.h>

/* Signal Handler for SIGINT */

void sigintHandler(int sig_num)
{
    /* Reset handler to catch SIGINT next time. */
    signal(SIGINT, sigintHandler);
    system("setterm -cursor on");
    exit(0);
}
