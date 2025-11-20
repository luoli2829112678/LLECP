#pragma once
#include<vector>
#include <cmath>
#include"../CIA402Axis/CIA402Axis.h"
#include"SMbasicErrorCode.h"
#include"motion_algorithm/motion_planning/motion_planning.h"
#define MaxSnap 20000000

struct SoftMotionPlanParams;


class SoftMotion
{
protected:
    std::vector<CIA402Axis*>m_v_Axis;
    uint16_t nAxisCount;
    double m_dSoftMotionCycle;
    std::vector<SoftMotionPlanParams> m_vSoftMotionPlanParams;
protected:
    void AxisRealTime();
    void SoftMotionPlanner_RT();
    int AxisMotionPlanner(CIA402Axis* pAxis);
public:
    SoftMotion(std::vector<CIA402Axis*> v_Axis);
    ~SoftMotion();
    void SoftMotionRun();
    int SetSoftMotionCycle(double dCycle);
};


struct SoftMotionPlanParams
{
    //规划参数
    ST_PlanParams stActParam;
    ST_PlanData trackData;

    //当前运动帧参数
    ST_InterParams stInterData;
};