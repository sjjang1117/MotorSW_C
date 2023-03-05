#include "MMCFunc.h"
#include <stdio.h>

unity_GUI unityGUI;

void MMCFunc::InitDest(bool btn_InitDest)
{
	if (btn_InitDest)
	{
		long addr = 0xD8000000;
		if (mmc_initx(1, NULL))
		{
			printf("MMC board init failed\n");
		}
		set_amp_enable(0, TRUE);
		set_position(0, 0.0);
	}
	else
	{
		v_move_stop(0); // jog 정지 후 연결 해제
		set_amp_enable(0, FALSE);
	}
}

void MMCFunc::RunStop(bool btn_RunStop, double vel)
{
	if (btn_RunStop)
	{
		v_move(0, vel, 15);
		printf("Run\n");
	}
	else
	{
		v_move_stop(0);
		printf("Stop\n");
	}
}

void MMCFunc::ZeroPos()
{	
		set_position(0, 0.0);
		printf("ZeroPos\n");
}

