#ifndef CIA402AXISDEF_H   // 如果还没定义这个宏
#define CIA402AXISDEF_H   // 定义宏，防止重复包含
#include"CIA402AxisDef.h"
#include"AxisErrorCode.h"
#include"AxisFriendList.h"
#define PDO_CONTROLWORD  *(m_st_map.pControlword)
#define PDO_STATUSWORD  *(m_st_map.pStatusWord)
#define PDO_TARGETPOSITION  *(m_st_map.pTargetPosition)
#define PDO_ACTUALPOSITION  *(m_st_map.pActualPosition)
#define PDO_TARGETTORQUE  *(m_st_map.pTargetTorque)
#define PDO_ACTUALTORQUE  *(m_st_map.pActualTorque)
#define PDO_TARGETVELOCITY *(m_st_map.pTargetVelocity)
#define PDO_ACTVELOCITY  *(m_st_map.pActualVelocity)
#define PDO_TARGETMODESOFOPERATION  *(m_st_map.pTargetModesOfOperation)
#define PDO_ACTUALMODESOFOPERATION  *(m_st_map.pActualModesOfOperation)
#define PDO_ERRORCODE  *(m_st_map.pErrorCode)
#define PDO_DIGITALOUTPUTS *(m_st_map.pDigitalOutputs) 
#define PDO_DIGITALINPUTS *(m_st_map.pDigitalInputs)
class SoftMotion;

class CIA402Axis 
{
    FRIEND_CLASSES
    friend SoftMotion;
protected:
    //connfig
    bool m_bVirtual;
    bool m_bBusy;
    uint32_t m_nAxisID;
    int m_nErrorCode;
    ST_CIA402_PDO m_stPDO_Virtual;
    //pdo同步
    ST_CIA402_PDO m_stMirrorPDO;
    ST_SMCInitMap m_st_map;
    ST_SMCAxisConfiguration m_stAxisConfiguration;
    bool m_bCyclicSyncMotion;
    int16_t m_nCyclicSyncMotionLosCount;
    double m_dControlCycle;//ms

    //Data
    ST_SMCAxisMotionData m_stAxisMotionData_now;
    ST_SMCAxisMotionData m_stAxisMotionData_old[5];

    //state
    EN_AxisMotionState m_enAxisMotionState;//sm
    //SoftMotion交换数据
    ST_SoftMotionData m_stSoftMotionEX;
    //插补帧
    ST_InterParams  m_stInterParamsData;
    

public:
    //external data
    //axis data
    int nCmdControlWord;      // 控制字（主站发往从站）
    int nActStatusWord;       // 状态字（从站反馈主站）

    // --- 目标运动参数 ---
    double dSetPosition;      // 目标位置（工程单位）
    int    TargetPosition_PDO;// 目标位置（PDO映射整数值）
    double dSetVelocity;      // 目标速度
    int    TargetVelocity_PDO;// 目标位置（PDO映射整数值）
    double dSetTorque;      // 目标力矩
    int    TargetTorque_PDO;// 目标力矩（PDO映射整数值）


    // --- 实际运动参数 ---
    double dActPosition;      // 实际位置（工程单位）
    int    nActualPosition_PDO;// 实际位置（PDO映射整数值）
    double dActVelocity;      // 实际速度
    int    ActualVelocity_PDO;// 实际位置（PDO映射整数值）
    double dActTorque;      // 实际力矩
    int    ActualTorque_PDO;// 实际力矩（PDO映射整数值）

    int DigitalOutputs;
    int DigitalInputs;


    // --- 补偿或控制器内部计算值 ---
    double dSetVelocity_c;    // 修正后速度（补偿）
    double dSetAcceleration_c;// 修正后加速度
    double dSetJerk_c;        // 修正后加加速度

    // --- 实际补偿参数 ---
    double dActVelocity_c;      // 实际补偿后速度
    double dActAcceleration_c;  // 实际补偿后加速度
    double dActJerk_c;          // 实际补偿后跃度


    double dSetPosition_s;    // SoftMotion速度
    double dSetVelocity_s;    // SoftMotion速度
    double dSetAcceleration_s;// SoftMotion加速度
    double dSetJerk_s;        // SoftMotion加加速度
    double dSetSnap_s; 

    // 模式与错误信息（Mode / Error）
    int nCmdModeOpration;    // 当前指令的操作模式（例如 Profile Position、Cyclic Synchronous Position 等）
    int nActModeOpration;    // 从站反馈的操作模式
    int nAxisErrorID;        // 轴错误代码（Fault ID）
    bool bBusy;
    
    //state
    bool bVirtual;    
    uint32_t nAxisID;
    EN_AxisMotionState enAxisMotionState;
    
    //config
    double dGearRatio;
    uint32_t nEncodeRatio;
    int nEncodeDirection;
    int nEncodeHomePos;
    double dTorqueScales;
    double dVelocityScale;
    int nTorqueDirection;
    double dPositive;
    double dNegative;
public:
    CIA402Axis(bool bVirtual);
    ~CIA402Axis();
    int Axis_InitMap(ST_SMCInitMap st_map);
    int Axis_SetAxisID(uint16_t id);
protected:
    int Axis_SetAxisState(EN_AxisMotionState enAxisMotionState);
    int Axis_SetOverride(ST_Factor stFactor);
    EN_AxisMotionState Axis_ReadAxisState();
    bool Axis_CheckError(int& nErrorID);
    bool Axis_CheckError();
    int Axis_ResetError();
    int Axis_SetInterFrame(ST_InterParams stInterParamsData);

    void Axis_SetCyclicSyncMotion();

    //PDO镜像直接控制pdo

    void PDOsynchronization();
    void AxisStatusCheck();
    // ===== 写入（RxPDO） =====
    int PDO_SetControlword(uint16_t Controlword);
    int PDO_SetTargetPosition(int32_t TargetPosition);
    int PDO_SetTargetVelocity(int32_t TargetVelocity);
    int PDO_SetTargetTorque(int16_t TargetTorque);
    int PDO_SetModesOfOperation(uint8_t mode);
    int PDO_SetDigitalOutputs(uint32_t DigitalOutputs);

    // ===== 读取（TxPDO） =====
    int PDO_ReadStatusWord(uint16_t& StatusWord);
    int PDO_ReadErrorCode(uint16_t& ErrorCode);
    int PDO_ReadActualPosition(int32_t& ActualPosition);
    int PDO_ReadActualVelocity(int32_t& ActualVelocity);
    int PDO_ReadActualTorque(int16_t& ActualTorque);
    int PDO_ReadModesOfOperation(uint8_t& mode);
    int PDO_ReadDigitalInputs(uint32_t& inputs);
    int PDO_ReadDigitalOutputs(uint32_t& outputs);

    // ===== 读回目标值缓存或虚拟轴调试 =====
    int PDO_ReadControlword(uint16_t& Controlword);
    int PDO_ReadTargetPosition(int32_t& TargetPosition);
    int PDO_ReadTargetVelocity(int32_t& TargetVelocity);
    int PDO_ReadTargetTorque(int16_t& TargetTorque);
    int PDO_ReadTargetModesOfOperation(uint8_t& mode);



    //MC功能块控制
    int Axis_PDO_SetControlword(uint16_t Controlword);
    int Axis_PDO_SetTargetPosition(int32_t TargetPosition);
    int Axis_PDO_SetTargetVelocity(int32_t TargetVelocity);
    int Axis_PDO_SetTargetTorque(int16_t TargetTorque);
    int Axis_PDO_SetModesOfOperation(EN_ModesOfOperation mode);
    int Axis_PDO_SetDigitalOutputs(uint32_t DigitalOutputs);
    int Axis_PDO_ReadStatusWord(uint16_t& StatusWord);
    int Axis_PDO_ReadErrorCode(uint16_t& ErrorCode);
    int Axis_PDO_ReadActualPosition(int32_t& ActualPosition);
    int Axis_PDO_ReadActualVelocity(int32_t& ActualVelocity);
    int Axis_PDO_ReadActualTorque(int16_t& ActualTorque);
    int Axis_PDO_ReadModesOfOperation(EN_ModesOfOperation& mode);
    int Axis_PDO_ReadDigitalInputs(uint32_t& inputs);
    int Axis_PDO_ReadDigitalOutputs(uint32_t& outputs);
    int Axis_PDO_ReadControlword(uint16_t& Controlword);
    int Axis_PDO_ReadTargetPosition(int32_t& TargetPosition);
    int Axis_PDO_ReadTargetVelocity(int32_t& TargetVelocity);
    int Axis_PDO_ReadTargetTorque(int16_t& TargetTorque);
    int Axis_PDO_ReadTargetModesOfOperation(uint8_t& mode);



    int Axis_PushMotionUint(const ST_MotionUint STMotionUint);
    int Axis_GetMotionUint(ST_MotionUint& stMotionUint);

public:
    //Config
    //设置减速比，调用即时生效*******减速比定义：在设置的编码器分辨率下一个编码器分辨率周期下的运动距离*****对于HR机器人应该是360/101
    int Axis_SetGearRatio(double dGearRatio);
    //设置编码器分辨率，调用即时生效
    int Axis_SetEncodeRatio(uint32_t nEncodeRatio);
    //设置编码器方向实时生效
    int Axis_SetEncodeDirection(int nEncodeDirection);
    //设置编码器原点，实时生效
    int Axis_SetEncodeHomePos(int32_t nEncodeHomePos);
    //设置电流常数，实时生效
    int Axis_SetTorqueScales(double dTorqueScales);
    //设置速度常数
    int Axis_SetVelocityScale(double dVelocityScale);
    //设置电流方向，实时生效
    int Axis_SetTorqueDirection(int nTorqueDirection);
    //设置硬件边界
    int Axis_SetSWLimit(double dPositive,double dNegative);
    //设置控制周期(ms)
    int Axis_SetControlCycle(double dControlCycle);
    //驱动赋错误码
    int Axis_SetDriveErrorCode(int ErrorCode);



protected:
    int Axis_SetMotionPlanner(ST_InterParams stMotionPlanner);
    int Axis_SetTargetPosition(double TargetPosition);
    int Axis_SetTargetVelocity(double TargetVelocity);
    int Axis_SetTargetTorque(double TargetTorque);
//CIA402AxisGeneral
protected:
    //轴的实时函数
    void Axis_RT();
    bool Axis_PDOErrorCheck();
    void DataSynchronization();
};


#endif