#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
int main()
{
        // 创建套接字
        int lfd = socket(AF_INET,SOCK_STREAM,0) ;
        printf("创建套接字成功\n") ;
        struct sockaddr_in addr ;
        addr.sin_family = AF_INET ;
        addr.sin_port = htons(9999) ;
        inet_aton("192.168.73.129",&addr.sin_addr) ;
        // 绑定
        int r = bind(lfd,(struct sockaddr*)&addr,sizeof(addr)) ;
        if( -1 == r ) perror("bind") , exit(1) ;
        printf("bind成功\n") ;
        // 设置成被动套接字
        r = listen(lfd,SOMAXCONN) ;
        if( -1 == r ) perror("listen") , exit(1) ;
        printf("listen成功\n") ;
        // 等待客户端的连接
        // newfd:已连接描述符，已连接套接字
        int newfd = accept(lfd,NULL,NULL) ;
        printf("有客户连上来\n") ;
        while(1) {
               char buf[1024] ;
                r = read(newfd,buf,1024) ;
                if ( r == 0 )
                        break ;
                printf("buf = %s\n",buf) ;
                memset(buf,0x00,sizeof(buf)) ;
                //fflush(newfd) ;
                write(newfd,buf,r) ;
        }
        close(newfd) ;
        close(lfd) ;
}
