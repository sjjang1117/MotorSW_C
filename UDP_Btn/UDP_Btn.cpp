// UDP_Btn.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winSock2.h>
#include <windows.h>
#pragma comment (lib,"ws2_32.lib")
#include "MMCWHP301.h"
#include "MMCFunc.h"

#define BUFFER_SIZE 1024
#define Pi 3.14

int HostToIoPort = 11112;
int ReturnValue;
int TimeO = 1000;
unity_GUI HostToIO;
MMCFunc mmcFunc;

typedef struct
{
	double cmdVel;
	double cmdPos;

	double actVel;
	double actPos;

	int cmdRPM;
}SendActValue;

SendActValue IOtoHOST ;

int main()
{

	bool btn_InitDest_B = false; // 켜, 꺼 이전값
	bool btn_RunStop_B = false; // 가, 서 이전값
	bool btn_ZeroPos_B = false; // home 이전값

	bool btn_VelUp_B = false; // 속도 증가 이전값
	bool btn_VelDown_B = false; // 속도 감소 이전값



	WSADATA wsa;// 소켓 통신 관련 변수 선언
	SOCKET HostSocket;

	SOCKADDR_IN HostAddress;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)// Window socket 초기화
	{
		printf("Err");
		return -1;
	}

	HostSocket = socket(AF_INET, SOCK_DGRAM, 0);// 호스트 소켓 생성 UDP로
	if (HostSocket == INVALID_SOCKET) return -1;

	setsockopt(HostSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&TimeO, sizeof(TimeO));
	//setsockopt(HostSocket, SOL_SOCKET, SO_RCVBUF, (char*)&HostToIO, sizeof(HostToIO));

	//소켓 주소 초기화
	HostAddress.sin_family = AF_INET; // IPv4 주소체계 사용
	HostAddress.sin_port = htons((unsigned short)HostToIoPort); // data를 받을 포트번호
	HostAddress.sin_addr.s_addr = htonl(INADDR_ANY);


	//bind 과정
	if (bind(HostSocket, (SOCKADDR*)&HostAddress, sizeof(HostAddress)) == SOCKET_ERROR)
	{
		printf("[UDP]\t호스트 소켓 바인드 에러\n");
		return -1;
	}

	SOCKADDR_IN IOAddress;
	int addrlen = sizeof(IOAddress);


	/*------------------------루프문 시작------------------------*/
	while (true)
	{
		//수신한 바이트 수
		ReturnValue = recvfrom(HostSocket, (char*)&HostToIO, sizeof(HostToIO), 0, (SOCKADDR*)&(IOAddress), &addrlen);

		// MMC 켜기, 끄기
		if (btn_InitDest_B != HostToIO.btn_InitDest)
			mmcFunc.InitDest(HostToIO.btn_InitDest);
		
		btn_InitDest_B = HostToIO.btn_InitDest; // 이전 값에 현재 값 넣기


		// 조그 가기, 멈추기
		if (btn_RunStop_B != HostToIO.btn_RunStop && HostToIO.btn_InitDest)
			mmcFunc.RunStop(HostToIO.btn_RunStop, HostToIO.cmdVelValue);

		btn_RunStop_B = HostToIO.btn_RunStop; // 이전 값에 현재 값 넣기
		

		//조그 포지션 : 0 (ZeroPos)
		if (btn_ZeroPos_B != HostToIO.btn_ZeroPos && HostToIO.btn_InitDest)
			mmcFunc.ZeroPos();

		btn_ZeroPos_B = HostToIO.btn_ZeroPos; // 이전 값에 현재 값 넣기


		// 속도 증가
		if (btn_VelUp_B != HostToIO.btn_VelUp)
			printf("속도 증가\n");

		btn_VelUp_B = HostToIO.btn_VelUp; // 이전 값에 현재 값 넣기


		// 속도 감소
		if (btn_VelDown_B != HostToIO.btn_VelDown)
			printf("속도 감소\n");

		btn_VelDown_B = HostToIO.btn_VelDown; // 이전 값에 현재 값 넣기 */


		IOtoHOST.actVel++;
		IOtoHOST.actPos++;

		printf("%lf %d %d\n", IOtoHOST.actPos, HostToIO.btn_InitDest, HostToIO.cmdACCValue);
		

		//IOtoHOST.actVel = get_velocity(0) * 0.01862; // 실제 속도값 획득
		//get_position(0, &IOtoHOST.actPos); // 실제 포지션값 획득
		//IOtoHOST.actPos = IOtoHOST.actPos / 131072 * 0.001355852;
		//IOtoHost.actPos = IOtoHOST.actPos / 131072 * PI; // 각도
		//IOtoHOST.actPos = IOtoHOST.actPos / 131072 * 60; // RPM
		
		// 데이터 보내기
		sendto(HostSocket, (char*)&IOtoHOST, sizeof(IOtoHOST), 0, (SOCKADDR*)&(IOAddress), sizeof(IOAddress));

	}


	// close socket
	closesocket(HostSocket);

	WSACleanup();// 윈속 종료
}
