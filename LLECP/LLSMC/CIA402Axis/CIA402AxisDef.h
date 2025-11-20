#pragma once
#include"../SoftMotion/motion_algorithm/motion_planning/MotionDefine.h"
#include <vector>
#include <stdint.h> 
#include <string.h>
#include<time.h>
#include <cstdlib>
#include <cstdio>
#include <math.h>



struct ST_CIA402_PDO
{
    uint16_t   Controlword;
    int32_t    TargetPosition;
    int32_t    TargetVelocity;
    int16_t    TargetTorque;
    uint8_t    TargetModesOfOperation;
    uint32_t   DigitalOutputs;
    uint32_t   TouchProbeFunction;
    uint32_t   AddVelocityValue;
    uint32_t   AddTorqueValue;

    uint16_t   StatusWord;
    int32_t    ActualPosition;
    int32_t    ActualVelocity;
    int16_t    ActualTorque;
    uint8_t    ActualModesOfOperation;
    uint32_t   TouchProbeStatus;
    uint32_t   DigitalInputs;
    uint16_t   ErrorCode;
};

//该映射遵照CanOpen402协议
struct ST_SMCInitMap
{
    uint16_t*   pControlword;
    uint16_t*   pStatusWord;
    uint16_t*   pErrorCode;
    int32_t*    pTargetPosition;
    int32_t*    pTargetVelocity;
    int16_t*    pTargetTorque;
    uint8_t*    pTargetModesOfOperation;
    int32_t*    pActualPosition;
    int32_t*    pActualVelocity;
    int16_t*    pActualTorque;
    uint8_t*    pActualModesOfOperation;
    uint32_t*   pDigitalInputs;
    uint32_t*   pDigitalOutputs;  
    
    uint32_t*   pTouchProbeFunction;
    uint32_t*   pAddVelocityValue;
    uint32_t*   pAddTorqueValue;
    uint32_t*   pTouchProbeStatus;
    ST_SMCInitMap()
    {
        pStatusWord = nullptr;
        pErrorCode = nullptr;
        pTargetPosition = nullptr;
        pTargetVelocity = nullptr;
        pTargetTorque = nullptr;
        pTargetModesOfOperation = nullptr;
        pActualPosition = nullptr;
        pActualVelocity = nullptr;
        pActualTorque = nullptr;
        pActualModesOfOperation = nullptr;
        pDigitalInputs = nullptr;
        pDigitalOutputs = nullptr;
        pTouchProbeFunction = nullptr;
        pAddVelocityValue = nullptr;
        pAddTorqueValue = nullptr;
        pTouchProbeStatus = nullptr;
    }
};

typedef enum
{
    en_ControlWord_Init                     = 0, 
    en_ControlWord_so                       = 1 << 0,  
    en_ControlWord_ev                       = 1 << 1,
    en_ControlWord_qs                       = 1 << 2,
    en_ControlWord_eo                       = 1 << 3,
    en_ControlWord_oms0                     = 1 << 4,
    en_ControlWord_oms1                     = 1 << 5,
    en_ControlWord_oms2                     = 1 << 6,
    en_ControlWord_fr                       = 1 << 7,
    en_ControlWord_h                        = 1 << 8,
    en_ControlWord_oms3                     = 1 << 9,
    en_ControlWord_r                        = 1 << 10,
    en_ControlWord_ms1                      = 1 << 11,
    en_ControlWord_ms2                      = 1 << 12,
    en_ControlWord_ms3                      = 1 << 13,
    en_ControlWord_ms4                      = 1 << 14,
    en_ControlWord_ms5                      = 1 << 15,

} EN_SMC_ControlWord;

typedef enum// : EC_T_USHORT
{
	en_StatusWord_rtso                      = 1 << 0,
	en_StatusWord_so                        = 1 << 1,
	en_StatusWord_oe                        = 1 << 2,
	en_StatusWord_f                         = 1 << 3,
	en_StatusWord_ve                        = 1 << 4,
	en_StatusWord_qs                        = 1 << 5,
	en_StatusWord_sod                       = 1 << 6,
	en_StatusWord_w                         = 1 << 7,
	en_StatusWord_ms                        = 1 << 8,
	en_StatusWord_rm                        = 1 << 9,
	en_StatusWord_tr                        = 1 << 10,
	en_StatusWord_ila                       = 1 << 11,
	en_StatusWord_oms1                      = 1 << 12,
	en_StatusWord_oms2                      = 1 << 13,
	en_StatusWord_ms1                       = 1 << 14,
	en_StatusWord_ms2                       = 1 << 15,
} EN_SMC_StatusWord;




// 运动方向
enum EN_Direction
{
    enPositive = 1,   // 正方向
    enNegative = -1,   // 负方向
    //enCurrent  = 2    // 保持当前方向（有些厂商支持）
};

//运动模式
enum EN_MoveType
{
    enMoveTypeNull,
    enAbsoluteMotion,
    enRelativMotion,
};

// 缓冲模式
enum EN_BufferMode
{
    enAborting = 0,   // 立即中断当前运动，执行新指令
    enBuffered = 1,   // 缓冲，等前一运动完成后再执行
    enBlendingLow = 2, // 融合过渡，低优先级平滑衔接
    enBlendingHigh = 3 // 融合过渡，高优先级平滑衔接
};

struct ST_PlanningMotionParam
{
    double pos;
    double vel;
    double acc;
    double dec;
    double jerk;
    EN_PlanningMode PlanningMode;
    EN_Direction  Direction;
    // == 运算符重载
    bool operator==(const ST_PlanningMotionParam& other) const
    {
        auto eq = [](double a, double b) { return std::fabs(a - b) < 1e-9; };

        return eq(pos,  other.pos)  &&
               eq(vel,  other.vel)  &&
               eq(acc,  other.acc)  &&
               eq(dec,  other.dec)  &&
               eq(jerk, other.jerk) &&
               (PlanningMode == other.PlanningMode) &&
               (Direction    == other.Direction);
    }
    bool operator!=(const ST_PlanningMotionParam& other) const
    {
        return !(*this == other);
    }
};

struct ST_MotionUint
{
    ST_PlanningMotionParam  PlanningMotionParam;
    EN_BufferMode BufferMode;
    EN_MoveType MoveType;
    void* fbID;//功能块指针
    //回调函数
    std::function<void(bool, bool, bool, bool, int)> fCallback;
    bool bMotion;
    bool bMotionDone;
    void SetFBStauts(bool bBusy,bool bDone,bool bCommandAborted,bool bError,int nErrorID)
    {
        bMotionDone = bDone;
        bMotion = bBusy;
        if (fCallback) 
            fCallback(bBusy,bDone,bCommandAborted,bError,nErrorID);
        return;
    }
};

struct ST_Factor
{
    double dVelFactor;
    double dAccFactor;
    double dJerkFactor;
    ST_Factor()
    {
        dVelFactor = 1;
        dAccFactor = 1;
        dJerkFactor = 1;
    }
    // == 运算符重载
    bool operator==(const ST_Factor& other) const
    {
        auto eq = [](double a, double b) { return std::fabs(a - b) < 1e-9; };

        return eq(dVelFactor,  other.dVelFactor)  &&
               eq(dAccFactor,  other.dAccFactor)  &&
               eq(dJerkFactor,  other.dJerkFactor);
    }
    bool operator!=(const ST_Factor& other) const
    {
        return !(*this == other);
    }
};

struct ST_SoftMotionData
{
    //待运动点位
    std::vector<ST_MotionUint>vMotionUint;
    //运动参数
    ST_PlanningMotionParam stSoftMotionMotionParam;
    //运动时间帧
    double dMotionTime;
    //减速比 
    ST_Factor m_stFactor;
    //重新规划标志
    bool bReplan;
};


struct ST_SMCAxisConfiguration
{
    double dGearRatio;
    uint32_t nEncodeRatio;
    int nEncodeDirection;
    int nEncodeHomePos;
    double dTorqueScales;
    double dVelocityScale;
    int nTorqueDirection;
    double dPositive;
    double dNegative;
    ST_SMCAxisConfiguration()
    {
        dGearRatio = 1;
        nEncodeRatio = 131072;
        nEncodeDirection = 1;
        nEncodeHomePos = 0;
        dTorqueScales = 1;
        nTorqueDirection = 1;
        dNegative = 0;
        dPositive = 0;
    }
};


enum EN_ModesOfOperation
{
    enModeManufacturerSpecificMin = -128,// 厂商自定义模式起始值

    enModeNoModeAssigned = 0,            // 无模式变化/未指定模式
    enModeProfilePosition = 1,           // 位置模式
    enModeVelocity = 2,                  // 速度模式
    enModeProfileVelocity = 3,           // 简单速度模式
    enModeProfileTorque = 4,             // 扭矩模式
    enModeReserved5 = 5,                 // 保留
    enModeHoming = 6,                    // 回零模式
    enModeInterpolatedPosition = 7,      // 插值位置模式
    enModeCyclicSyncPosition = 8,        // 同步位置模式（周期）
    enModeCyclicSyncVelocity = 9,        // 同步速度模式（周期）
    enModeCyclicSyncTorque = 10,         // 同步扭矩模式（周期）

    enModeManufacturerSpecificMax = 127  // 厂商自定义最大值
    // 11 到 127 保留
};

//OpenPLC标准
enum EN_AxisMotionState
{
    motionState_power_off           = 0,  // Disabled
    motionState_errorstop           = 1,  // Error Stop
    motionState_stopping            = 2,  // Stopping
    motionState_standstill          = 3,  // Standstill
    motionState_discrete_motion     = 4,  // 单步运动
    motionState_continuous_motion   = 5,  // 连续运动
    motionState_synchronized_motion = 6,  // 同步运动
    motionState_homing              = 7   // 回零
};


struct ST_SMCAxisMotionData
{
    int32_t nTarPosCount;
    int32_t nActPosCount;
    int32_t nTarCurCount;
    int32_t nActCurCount;
    double dTarPos;
    double dTarVel;
    //double dTarAcc;
    double dActPos;
    double dActVel;
   // double dActAcc;
    double dTarCur;
    double dActCur;
    //************************** */
    double dTarVel_c;
    double dTarAcc_c;
    double dTarJerk_c;
    double dActVel_c;
    double dActAcc_c;
    double dActJerk_c;
    EN_ModesOfOperation snTarMOO;
    EN_ModesOfOperation snActMOO;
    ST_SMCAxisMotionData()
    {
        dTarVel = 0;
        //dTarAcc = 0;
        dActVel = 0;
        //dActAcc = 0;
        dTarVel_c = 0;
        dTarAcc_c = 0;
        dActVel_c = 0;
        dActAcc_c = 0;
        dActJerk_c = 0;
        dActJerk_c = 0;
        dTarCur = 0;
        dActCur = 0;
    }
};

class SMCTimer 
{
public:
    bool bInit_IN;
    long nInit_PT = 0;  // 以微秒为单位
    struct timespec nInit_ET = {0, 0};

	bool bLast_CLK = false;
public:
	// 定时器
    bool Ton(bool IN, int PT, int& ET) 
    {
        if (!IN)
        {
            ET = 0;
            bInit_IN = false;
            nInit_PT = 0;
            nInit_ET = {0, 0};
            return false;
        }
        // 检测上升沿
        if (IN && !bInit_IN)
        {
            nInit_PT = PT;
            clock_gettime(CLOCK_MONOTONIC, &nInit_ET);
        }
        if (IN)
        {
            bInit_IN = IN;
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            // 计算经过的时间（微秒）
            long elapsed = (now.tv_sec - nInit_ET.tv_sec) * 1000000 + 
                           (now.tv_nsec - nInit_ET.tv_nsec) / 1000;
            ET = elapsed;
            return ET > nInit_PT;
        }
        return false;
    }

	bool Ton(bool IN, int PT) 
    {
		int ET = 0;
        if (!IN)
        {
            bInit_IN = false;
            nInit_PT = 0;
            nInit_ET = {0, 0};
            return false;
        }
        // 检测上升沿
        if (IN && !bInit_IN)
        {
            nInit_PT = PT;
            clock_gettime(CLOCK_MONOTONIC, &nInit_ET);
        }
        if (IN)
        {
            bInit_IN = IN;
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            // 计算经过的时间（微秒）
            long elapsed = (now.tv_sec - nInit_ET.tv_sec) * 1000000 + 
                           (now.tv_nsec - nInit_ET.tv_nsec) / 1000;
            ET = elapsed;
            return ET > nInit_PT;
        }
        return false;
    }
	// 上升沿检测
	bool R_TRIG(bool CLK)
	{
		if (CLK && !bLast_CLK)
		{
			bLast_CLK = CLK;
			return true;
		}
		else
		{
			bLast_CLK = CLK;
			return false;
		}
	}
	// 下降沿检测
    bool F_TRIG(bool CLK)
    {
        if (!CLK && bLast_CLK) // 从 true 变为 false
        {
            bLast_CLK = CLK;
            return true;
        }
        else
        {
            bLast_CLK = CLK;
            return false;
        }
    }
};

