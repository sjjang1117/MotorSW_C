#pragma once
#include "MMCWHP301.h"

typedef struct
{
	double cmdVelValue; // 명령 속도 값

	bool btn_InitDest; // 켜, 꺼	
	bool btn_RunStop; // 가, 서
	bool btn_ZeroPos; // home

	bool btn_VelUp; // 속도 증가
	bool btn_VelDown; // 속도 감소

} unity_GUI;

class MMCFunc
{
public:
	void InitDest(bool btn_InitDest);
	void RunStop(bool btn_RunStop, double vel);
	void ZeroPos();
public:
};

