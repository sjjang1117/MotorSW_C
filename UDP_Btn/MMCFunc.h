#pragma once
#include "MMCWHP301.h"

typedef struct
{
	double cmdVelValue; // ��� �ӵ� ��

	bool btn_InitDest; // ��, ��	
	bool btn_RunStop; // ��, ��
	bool btn_ZeroPos; // home

	bool btn_VelUp; // �ӵ� ����
	bool btn_VelDown; // �ӵ� ����

} unity_GUI;

class MMCFunc
{
public:
	void InitDest(bool btn_InitDest);
	void RunStop(bool btn_RunStop, double vel);
	void ZeroPos();
public:
};

