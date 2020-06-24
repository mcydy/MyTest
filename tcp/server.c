#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int disConnectWifiAp()
{
	// printf("disConnectWifiAp\n");
	
	// pid_t fpid ;
	// fpid = fork();
	// if (fpid == 0){
	 //       execl("/usr/bin/ffmpeg", "sudo" "ffmpeg");
	 //    }else{
	 //         // p->stream_pid = fpid;
	 //         // is_success = true;
	 //    }
	system("sudo ifdown wlan0");
	return 0;
}

int connectWifiBySsid(char *ssid, char *passwd)
{
	printf("%s---%s\n",ssid, passwd);
	// //编辑　wlan配置文件
	// "network={
 //    ssid=\"SchoolNetworkSSID\"
 //    psk=\"passwordSchool\"
	// }"

	char tmp[128];
	printf("start to modify ssid\n");
	sprintf(tmp,"sudo sed -i '10anetwork={ssid=\"%s\"psk=\"%s\"}' ./a.txt",ssid,passwd);
	printf("==%s\n",tmp);
	system(tmp);

	system("sudo idup wlan0")


	// sed -i '10aAdd Line Behind' passwd 

	// char tmp[128];
	// printf("start to modify ssid\n");
	// sprintf(tmp,"sudo sed -i 's/^ssid=.*$/ssid=%s/g' ./a.txt",ssid);
	// system(tmp);

	// char tmp1[128];
	// printf("start to modify psk\n");
	// sprintf(tmp,"sudo sed -i 's/^psk=.*$/psk=%s/g' ./a.txt",passwd);
	// system(tmp);

	//启动wifi


	return 0;	
}



int main(int argc, char *argv[])
{
	unsigned short port = 8000;
	if(argc > 1)
	{
		port = atoi(argv[1]);
	}
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("sockfd");
		exit(-1);
	}
	struct sockaddr_in my_addr;//本地信息
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;//设置地址族为IPv4
	my_addr.sin_port = htons(port);//设置地址的端口号信息
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY服务器可以接收任意地址

	int optval = -1; 
    socklen_t optlen = -1; 
    optval = 100;  
    optlen = sizeof(optval);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, optlen);
    struct timeval timeout = {20, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));


	int err_log = bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr));
	if(err_log != 0)
	{
		perror("binding");
		close(sockfd);
		exit(-1);
	}

	err_log = listen(sockfd, 10);
	if(err_log != 0)
	{
		perror("listen");
		close(sockfd);
		exit(-1);
	}
	printf("listen client %d\n",port);

	struct sockaddr_in client_addr;
	char cli_ip[INET_ADDRSTRLEN] = " ";
	socklen_t client_len = sizeof(client_addr);
	int connfd;
	connfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);//等待连接
	if(connfd < 0 )
	{
		perror("accept");
		return -1;
		//continue;
	}
	inet_ntop(AF_INET, &client_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);//转换并打印信息
	printf("********************************\n");
	while(1)
	{
		char recv_buf[2048] = " ";
		int revc_size = recv(connfd, recv_buf, sizeof(recv_buf), 0);//接收信息
		if(revc_size != 0)
		{
			printf("recv data:%s\n",recv_buf);
			//解析接收数据目前 目前报文格式   {ssid:neo,passwd:12345678}

			char des_ssid[32];
			char des_passwd[32];


			char *ssid_string = strstr(recv_buf, "ssid");
			if(ssid_string ==NULL)
	        {
	                printf("ssid_string is NULL\n");
	        }

			char *ssid_end = strstr(recv_buf, ",");
			if(ssid_end ==NULL)
	        {
	                printf("ssid_end is NULL\n");
	        }
			char *passwd_string = strstr(recv_buf, "passwd");
			if(passwd_string ==NULL)
	        {
	                printf("passwd_string is NULL\n");
	        }
			char *passwd_end = strstr(recv_buf, "}");
			if(passwd_end ==NULL)
	        {
	                printf("passwd_end is NULL\n");
	        }

	        if(ssid_string != NULL && ssid_end != NULL && passwd_string!= NULL && passwd_end != NULL)
	        {
		        printf("%s\n",ssid_string);
				memcpy(des_ssid, ssid_string+strlen("ssid:"), ssid_end-ssid_string-strlen("ssid:"));
				printf("size：%d ssid::::::::%s\n",ssid_end-ssid_string-strlen("ssid:"),des_ssid);

				memcpy(des_passwd, passwd_string+strlen("passwd:"), passwd_end-passwd_string-strlen("passwd:"));
				printf("siez: %d passwd:::::::::%s\n",passwd_end-passwd_string-strlen("passwd:"),des_passwd);
				send(connfd, "ok", 2, 0);//向客户端发送数据
				printf("ok\n");

				//1.关闭当前AP模式

				disConnectWifiAp();
				//2.连接新wifi

				connectWifiBySsid(des_ssid, des_passwd);
			}
		}
		
	}
	close(sockfd);//关闭监听套接字
	return 0;
}
