//###############################################
//
// Author  : Gale
// Date    : 2011-4
// Email   : galemx@126.com
// Location: FuZhou FuJian China
//
#include "kkavr.h"
#include "delay.h"

//--------------------------------------
//##Motor drive signal 锟斤拷锟斤拷锟斤拷藕锟�
uchar Motor1, Motor2, Motor3, Motor4; //Motor signals 锟斤拷锟斤拷锟斤拷藕锟�
//###############################################
//
//   Motor drive limit
//   锟斤拷锟斤拷锟斤拷薹锟�
//
uchar MotorLimitValue(int v) {
	if (v > PPM_MAX)
		return PPM_MAX;
	if (v < 0)
		return 0;
	return v;
}

//###############################################
//
//   Motor signal output
//   锟斤拷锟斤拷锟斤拷锟脚猴拷
//
//-----Consist of two function: MotorControlBegin & MotorControlEnd
//-----  MotorControlEnd set all signal-pin to high, and ppm need
//-----  a 1000us delay, so I use this period to do something else,
//-----  when MotorControlEnd execute, it delay to 1000us exactly,
//-----  then output ppm signal
//-----锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷桑锟組otorControlBegin 锟斤拷 MotorControlEnd
//-----  MotorControlBegin 锟斤拷锟斤拷锟斤拷锟脚号斤拷锟斤拷锟竭ｏ拷锟斤拷锟斤拷PPM锟斤拷要1000us锟斤拷一锟斤拷
//-----  锟斤拷时锟斤拷锟斤拷锟斤拷锟斤拷锟角诧拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞比ワ拷傻锟斤拷锟斤拷锟斤拷椋拷锟組otorControlEnd
//-----  执锟叫碉拷时锟斤拷锟斤拷锟饺撅拷确锟斤拷时锟斤拷100us锟斤拷然锟斤拷锟斤拷锟斤拷锟絧pm锟脚猴拷
void MotorControlBegin(void) {
	//Reset softtimer
	TimerRst();

	//Rise all motor signal
	MOTOR1_H();
	MOTOR2_H();
	MOTOR3_H();
	MOTOR4_H();
}
//######
void MotorControlEnd(void) {
	uchar Cnt;

	//Wait until 1000us
	TimerTo(1000);
	TimerRst();

	//8us per cycle
	for (Cnt = 0; Cnt < 125; Cnt++) {
		if (Cnt > Motor1)
			MOTOR1_L();
		else
			MOTOR1_H();
		if (Cnt > Motor2)
			MOTOR2_L();
		else
			MOTOR2_H();
		if (Cnt > Motor3)
			MOTOR3_L();
		else
			MOTOR3_H();
		if (Cnt > Motor4)
			MOTOR4_L();
		else
			MOTOR4_H();

		//Patch cycle to 8us
		TimerTo(8);
		TimerRst();
	}

	MOTOR1_L();
	MOTOR2_L();
	MOTOR3_L();
	MOTOR4_L();
}
