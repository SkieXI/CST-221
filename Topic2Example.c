#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>


struct
{
    int currentlocation;
    int baselocaiton;
    int buffer[256];
}

struct mybuffer buf1;


    mybuffer* pbuf1;
    pbuf1->baselocaiton;
    
    buf1.baselocaiton =10;
}

int main(int argc, char *argv([])
{
    pid_t pid;
    int listenfd = 0, connnfd = 0
    struct sockaddr_in serv_addr;
    
    char senduff[1025];
    time_t ticks;
    
    pid = fork();
    
    if(pid ==1)
    {
        fprint(stderr, "can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(senduff, '0', sizeof(senduff));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (pid ==0)
    {
        serv_addr.sin_port = htons(5001);
    }
    else
    {
        serv_addr.sin_port = htons(5000);
    }
    
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    listen(listenfd, 1) ;
    
    while(1)
    {
        connfd = accenpt(listenfd, (struct sockaddr*)NULL, NULL);
        
        ticks = time(NULL);
        
        if(pid ==0)
        {
            snprintf(sendbuff, sizeof(sendBuff), "CSR #2 connected.";
        }
        else
        {
            snprintf(sentbuff, sizeof(sendbuff), "CSR #1 connected.";
        }
        
        write(connfd, sendBuff, strlen(sendbuff));
        
        close(connfd);
        sleep(1);
    }

}
