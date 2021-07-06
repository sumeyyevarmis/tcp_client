
#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	const char* message;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	// Winsock baþlatýlmasý
	printf("Winsock'u baslatma\n");
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAS baslatilamadi: %d\n", iResult);
		return 1;
	}

	printf("Baslatildi\n");

	// Socket oluþturma 
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("soket olusturulamadi\n");
		return 1;
	}
	printf("soket olustu\n");
	char ip[16];
	printf("IP adresinin giriniz: ");
	fgets(ip,16,stdin);
	int port;
	printf("Port numarasýný giiniz: ");
	scanf("%d",&port);
	struct sockaddr_in addr;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	// sunucuya baðlan
	if (connect(ConnectSocket, (sockaddr*)&addr, sizeof(addr)) < 0) {
		printf("Baglanilamadi\n");
		return 1;
	}
	printf("Baglandi\n");

	// veri göndermek için
	message = "Baglanti saglanmistir";
	if (send(ConnectSocket, message, strlen(message), 0) < 0) {
		printf("Gonderme basarisiz\n");
		return 1;
	}
	printf("Veri gonderildi\n");


	iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	recvbuf[iResult] = 0; 
	printf("%d:%s\n", iResult, recvbuf);
	
}