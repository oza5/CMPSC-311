//OSMAN ALI OZA5@PSU.EDU
//977810411

#include <stdio.h>
#include "csapp.h"
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 16777216 
#define MAX_OBJECT_SIZE 8388608 
#define PORT_SIZE 9999      //PROXY PORT SIZE SET TO RANDOM BIG VALUE

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";


void doit(int connfd);
void parse_uri(char *uri,char *hostname,char *path,int *port);

int main(int argc,char **argv)          /*CODE EXTRACTED FROM TINY.C*/
{    					
    int listenfd,connfd;		   //INSTANTIATE INTEGERS FOR FILE DESCRIPTORS 	
    socklen_t  clientlen;                 // INSTANTIATE SOCKET FOR CLIENT ADDRESS
    char hostname[MAXLINE],port[MAXLINE];
    struct sockaddr_storage clientaddr;
    
    /* Check command line args */
    if(argc != 2){                                    //IF "./PROXY" DOESNT HAVE AN ARGUMENT RETURN A ERROR SHOWING ITS
        fprintf(stderr,"usage :%s <port> \n",argv[0]);
        exit(1);
    }
                                                        
    Signal(SIGPIPE, SIG_IGN);                         //IGNORE THE SIGPIPE SIGNAL            
    listenfd = Open_listenfd(argv[1]);                //PROXY OPENS A LISTEN DESCRIPTOR ON PORT = ARGUMENT
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //ACCEPTS CONNECTION FROM CLIENTS ON THIS PORT AND CREATES A CONNECTION 
	Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, 
                    port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
	doit(connfd);                                             //MAIN FUNCTION OF PROXY
	Close(connfd);                                            //CLOSE PROXY AFTER SERVICING OF CLIENT IS DONE
    }
    return 0;
}


void doit(int connfd)    /*MAIN PROXY CONNECTION THAT HANDLES ALL REQUESTS/SERVICES*/
{   int a,b,c_1,c_2,c_3;
    char buf2[MAXLINE],
    req[MAXLINE],
    info_hdr[MAXLINE],
    main_serv[MAXLINE];
    int main_serverfd;//INTEGER FOR SERVER FILE DESCRIPTOR
    char port_store[PORT_SIZE];
    char buf[MAXLINE],method[MAXLINE],uri[MAXLINE],version[MAXLINE];
    char server_hdr [MAXLINE];
    char hostname[MAXLINE],path[MAXLINE];
    int port = 80; //DEFAULT PORT NUMBER

    rio_t client_rio; //ROBUST I/O INSTANTIATIONS FOR CLIENT AND SERVER
    rio_t server_rio;

    Rio_readinitb(&client_rio,connfd); //READ REQUEST FROM CLIENTFD
    Rio_readlineb(&client_rio,buf,MAXLINE); 
    sscanf(buf,"%s %s %s",method,uri,version); 

    if(strcasecmp(method,"GET")){//CHECK IF REQUEST TYPE IS GET
        printf("\nProxy does not implement the method");
        return;
    }
    /*CALL TO PARSE CLIENT RECEIVED URI AND EXTRACT HOSTNAME, PATH,PORT*/ 
    parse_uri(uri,hostname,path,&port);

    
   
    
    /*START BUILDING HEADER WITH MAKING REQUEST PATH*/
    sprintf(req,"GET %s HTTP/1.0\r\n",path);
    /*get other request header for client rio and change it */
    
    while(Rio_readlineb(&client_rio,buf2,MAXLINE)!=0) /*EXTRACT REQUEST HEADER FOR CLIENT, TO MODIFY IT*/
    { 
	a = strcmp(buf2,"\r\n"); //CHECK FOR END OF LINE IN REQUEST HEADER
        if(!a)
	{ 
	    break;
	}
        b = strncasecmp(buf2,"Host: %s\r\n",strlen("Host: %s\r\n")); //EXTRACT THE HOST INFORMATION
        if(!b)
        {
            strcpy(main_serv,buf2);
            continue;
        }
        c_1 = strncasecmp(buf2,"Connection",10); //BUILD UP ADDITIONAL REQUEST HEADERS FROM CLIENT REQUEST BUFFER
	c_2 = strncasecmp(buf2,"Proxy-Connection",16);
	c_3 = strncasecmp(buf2,"User-Agent",10);
        
	if(!(c_1||c_2)){
		if(!(c_2||c_3))
		{
		  strcat(info_hdr,buf2);    //CHECK FOR ADDITIONAL HEADER-INFO
		}
    	}
    }

    if(strlen(main_serv)==0)
    {
        sprintf(main_serv,"Host: %s\r\n",hostname); //GETS THE HOSTNAME
    }
    sprintf(server_hdr,"%s%s%s%s%s%s%s",req,main_serv, //FINALLY COMPILES THE HEADER WITH ALL NECESSARY AND ADDITIONAL HEADERS AND INFORMATION ABOUT CONNECTION
	"Connection: close\r\n",
	"Proxy-Connection: close\r\n",
	user_agent_hdr,
	info_hdr,
	"\r\n");

   
    
    sprintf(port_store,"%d",port);
    main_serverfd = Open_clientfd(hostname,port_store); //OPEN UP A CONNECTION PORT TO THE END SERVER
    if(main_serverfd<0){
        printf("connection failed\n"); //CHECKS FOR ANY ERRORS OR FALIURES IN CONNECTION
        return;
    }

    Rio_readinitb(&server_rio,main_serverfd); //SEND HTTP INFORMATION TO ENDSERVER TO BEGIN SERVICING PART OF REQUEST PROCESS
    
    Rio_writen(main_serverfd,server_hdr,strlen(server_hdr));

   
    int bytes_read =0; // AMOUNT OF INFO READ BY PROXY FROM MAIN SERVER
    while((bytes_read=Rio_readlineb(&server_rio,buf,MAXLINE)) > 0) //READ ALL INFO FROM MAIN SERVER SEND TO THE CLIENT
    {
        Rio_writen(connfd,buf,bytes_read); //ONCE READ FROM SERVER START FORWARDING THIS INFORMATION TO CLIENT
    }
    Close(main_serverfd); //CLOSE PROXY-SERVER CONNECTION ONCE PROCESS IS DONE
}


/*PARSE URI FUNCTION THAT ENABLES US TO EXTRACT HOST,PORT AND PATH FROM THE REQUEST HEADER GENERATED BY DOIT FUNCTION*/
void parse_uri(char *uri,char *host,char *path,int *port)
{   
    int i = 0;
    char *val_toFill = '\0'; 
    char *ptr_uri_start;
    char buf[MAXLINE]; 
    char *start;
    
    memset(buf, atoi(&val_toFill), MAXLINE); //FILL MEMORY WITH VAL_TO_FILL(SIZE) 
    strcpy(buf, uri);

    memset(host, atoi(&val_toFill), MAXLINE); //MEMORY FOR HOST
    ptr_uri_start = strstr(buf, "http://");   //LOOK FOR START POSITION OF "HTTP://"
    start = ptr_uri_start;
    memset(path, atoi(&val_toFill), MAXLINE); //MEMEORY FOR PATH
    
    if(start == NULL) 
	{
        return; /*IF HTTP IS NOT PRESENT JUST RETURNS URI*/
        }
    else
	{ 
        start += 7; //GET TO THE START OF HOST 
	}
    int i_update =0;
    int loop_uri = 1; //LOOP VARIANT TO ITERATE THROUGH REQUEST FOR PARSING AND BREAKING
    while(loop_uri) 
	{
	char flag = start[i];
        if(flag == ':')
	{
            loop_uri = 0;
	}
	else if (flag == '/') //FIND THE HOST PART OF THE URI
	{
	    loop_uri = 0;
        }
	else{
            host[i] = flag;   
	    i_update += 1;
	    i+=1;
	    loop_uri = 1;
	    }
        }
    host[i_update] = '\0';
    if(start[i_update] == ':')//GET TO THE PORT PART OF URI
	{
	i_update +=1;
        sscanf(&start[i_update], "%d%s", port, path); //SAVE PORT
	}
    else
	{
        sscanf(&start[i_update], "%s", path); //SAVE PATH
	}
    return;

}

