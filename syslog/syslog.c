#include<stdio.h>
#include<syslog.h>
#include<unistd.h>

int main(){
    int pid = getpid();
    printf("PID= %d", pid);
    setlogmask(LOG_UPTO(LOG_NOTICE));
    openlog("syslog_example", LOG_CONS | LOG_PID | LOG_NDELAY , LOG_LOCAL1);

    syslog(LOG_NOTICE, "Program started by %d", getuid());
    syslog(LOG_INFO, "This is info");
    closelog();
}