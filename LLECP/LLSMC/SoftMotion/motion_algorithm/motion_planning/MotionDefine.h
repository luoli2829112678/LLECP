#pragma once
#include<stdio.h>
#include <stdint.h>  
#include<vector>
#include <algorithm> 
#include <iostream>
#include <fstream>
#include<math.h>
#define Zero 1e-9
#define MAX_PATH_NUM_ALLOWED 100000
#define ITERATIVESTEPS 0.00001


#define ERROR_CALCULATION_01 1
#define ERROR_CALCULATION_02 2
#define ERROR_CALCULATION_03 3
#define ERROR_DISPLACEMENT_TOO_SMALL 4
#define ERROR_INVALID_PARAMETERS 5
#define The_displacement_is_too_small_to_plan 6
#define Invalid_input_parameter 7
#define Error_in_calculating_the_acceleration_for_the_single_deceleration_segment 8
#define Error_in_calculating_the_acceleration_for_the_single_aeceleration_segment 9
#define Error_in_calculating_acceleration_in_the_aeceleration_section 10
#define Error_in_calculating_acceleration_in_the_deceleration_section 11
#define Planning_error 12
#define Denominator_is_zero 1111

//规划模式
enum EN_PlanningMode
{
    //0
    enPlanningModeNull = 0,//无模式
    enPositionPlanningMode = 1,//位置模式
    enVelocityPlanningMode = 2,//速度模式
    enAccelerationPlanningMode = 3, //加速度模式

    enStopPlanningMode = 99 //停止模式
};


struct ST_PlanParams {
	double q0=0;      // 起始位置
	double q1=0;      // 目标位置  
	double v0=0;      // 起始速度
	double v1=0;      // 结束速度
	double a0=0;      // 起始加速度
	double a1=0;      // 结束加速度
	double V_max=0;    // 最大速度
	double A_amax=0;    // 最大加速度
	double A_dmax=0;    // 最大加速度
	double J_max=0;    // 最大加加速度
	double S_max=0;    // 最大跳度
	EN_PlanningMode enPlanmode;      //运动模式

	// 相等运算符：逐个成员比较
	bool operator==(const ST_PlanParams& other) const
	{
		return 
			//初始位置改变不视为运动参数发生了变化
			//q0 == other.q0 &&
			fabs(q1 - other.q1) < ITERATIVESTEPS &&
			fabs(v0 - other.v0) < ITERATIVESTEPS &&
			fabs(v1 - other.v1) < ITERATIVESTEPS &&
			fabs(V_max - other.V_max) < ITERATIVESTEPS &&
			fabs(A_amax - other.A_amax) < ITERATIVESTEPS &&
			fabs(A_dmax - other.A_dmax) < ITERATIVESTEPS &&
			fabs(J_max - other.J_max) < ITERATIVESTEPS &&
			fabs(S_max - other.S_max) < ITERATIVESTEPS;
	}

	bool operator!=(const ST_PlanParams& other) const
	{
		return 
			fabs(q1 - other.q1) > ITERATIVESTEPS ||
			fabs(v0 - other.v0) > ITERATIVESTEPS ||
			fabs(v1 - other.v1) > ITERATIVESTEPS ||
			fabs(V_max - other.V_max) > ITERATIVESTEPS ||
			fabs(A_amax - other.A_amax) > ITERATIVESTEPS ||
			fabs(A_dmax - other.A_dmax) > ITERATIVESTEPS ||
			fabs(J_max - other.J_max) > ITERATIVESTEPS ||
			fabs(S_max - other.S_max) > ITERATIVESTEPS;
	}

};

struct ST_PlanData {

	double Ta=0;      // 加速时间
	double Tv=0;      // 匀速时间
	double Td=0;      // 减速时间
	double Tsa=0;
	double Tsd=0;
	double Tja=0;
	double Tjd=0;
	double T=0;       // 总时间

	double A_amax=0;
	double A_dmax=0;
	double J_amax=0;
	double J_dmax=0;
	int direction=1;
};
struct ST_InterParams {
	double P=0; // 位置
	double V=0; // 速度 
	double A=0; // 加速度
	double J=0; // 加加速度
	double S=0; // 跳度
};