#include"CIA402Axis.h"
CIA402Axis::CIA402Axis(bool bVirtual) 
{ 
   m_bVirtual = bVirtual;
   m_enAxisMotionState = motionState_power_off;
   //map init
    m_st_map.pControlword             = &m_stPDO_Virtual.Controlword;
    m_st_map.pStatusWord              = &m_stPDO_Virtual.StatusWord;
    m_st_map.pErrorCode               = &m_stPDO_Virtual.ErrorCode;
    m_st_map.pTargetPosition          = &m_stPDO_Virtual.TargetPosition;
    m_st_map.pTargetVelocity          = &m_stPDO_Virtual.TargetVelocity;
    m_st_map.pTargetTorque            = &m_stPDO_Virtual.TargetTorque;
    m_st_map.pTargetModesOfOperation  = &m_stPDO_Virtual.TargetModesOfOperation;
    m_st_map.pActualPosition          = &m_stPDO_Virtual.ActualPosition;
    m_st_map.pActualVelocity          = &m_stPDO_Virtual.ActualVelocity;
    m_st_map.pActualTorque            = &m_stPDO_Virtual.ActualTorque;
    m_st_map.pActualModesOfOperation  = &m_stPDO_Virtual.ActualModesOfOperation;
    m_st_map.pDigitalInputs           = &m_stPDO_Virtual.DigitalInputs;
    m_st_map.pDigitalOutputs          = &m_stPDO_Virtual.DigitalOutputs;
}
CIA402Axis::~CIA402Axis(){}

int CIA402Axis::Axis_InitMap(ST_SMCInitMap st_map)
{
    m_st_map = st_map;
    //pdo镜像初始化防止飞车
    m_stMirrorPDO.Controlword = PDO_CONTROLWORD;
    m_stMirrorPDO.StatusWord = PDO_STATUSWORD;
    if(nullptr!=&PDO_ACTUALPOSITION)
    {
        m_stMirrorPDO.TargetPosition = PDO_ACTUALPOSITION;
        m_stMirrorPDO.ActualPosition = PDO_ACTUALPOSITION;
        PDO_TARGETPOSITION = PDO_ACTUALPOSITION;
    }
    if(nullptr!=&PDO_ACTUALTORQUE)
    {
        m_stMirrorPDO.TargetTorque = PDO_ACTUALTORQUE;
        m_stMirrorPDO.ActualTorque = PDO_ACTUALTORQUE;
    }
    if(nullptr!=&PDO_ACTVELOCITY)
    {
        m_stMirrorPDO.TargetVelocity = PDO_ACTVELOCITY;
        m_stMirrorPDO.ActualVelocity = PDO_ACTVELOCITY;
    }
    if(nullptr!=&PDO_ACTUALMODESOFOPERATION)
    {
        m_stMirrorPDO.TargetModesOfOperation = PDO_ACTUALMODESOFOPERATION;
        m_stMirrorPDO.ActualModesOfOperation = PDO_ACTUALMODESOFOPERATION;
    }
    return AEC_SUCCESSED;
}
int CIA402Axis::Axis_SetAxisID(uint16_t id)
{
    m_nAxisID = id;
    return AEC_SUCCESSED;
}
int CIA402Axis::Axis_SetAxisState(EN_AxisMotionState enAxisMotionState)
{
    m_enAxisMotionState = enAxisMotionState;
    return AEC_SUCCESSED;
}
int CIA402Axis::Axis_SetOverride(ST_Factor stFactor)
{
    m_stSoftMotionEX.m_stFactor = stFactor;
    return AEC_SUCCESSED;
}
EN_AxisMotionState CIA402Axis::Axis_ReadAxisState()
{
    return m_enAxisMotionState;
}

bool CIA402Axis::Axis_CheckError(int& nErrorID)
{
    bool res = Axis_PDOErrorCheck();
    nErrorID = m_nErrorCode;
    return(res);
}
bool CIA402Axis::Axis_CheckError()
{
    bool res = Axis_PDOErrorCheck();
    return res;
}

int CIA402Axis::Axis_ResetError()
{
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_SetInterFrame(ST_InterParams stInterParamsData)
{
    m_stInterParamsData = stInterParamsData;
    dSetVelocity_s = stInterParamsData.V;
    dSetAcceleration_s = stInterParamsData.A;
    dSetJerk_s = stInterParamsData.J;
    dSetSnap_s = stInterParamsData.S;
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_PushMotionUint(const ST_MotionUint STMotionUint)
{
    //立即中断当前运动，并开始新运动
    if(EN_BufferMode::enAborting == STMotionUint.BufferMode)
    {
        m_stSoftMotionEX.vMotionUint.clear();
    }
    //首点位下发清理缓存
    if(motionState_standstill == m_enAxisMotionState)
    {
        m_stSoftMotionEX.vMotionUint.clear();
    }
    if(enPositionPlanningMode != STMotionUint.PlanningMotionParam.PlanningMode)
    {
        m_stSoftMotionEX.vMotionUint.clear();
    }
    //缓存点位
    m_stSoftMotionEX.vMotionUint.push_back(STMotionUint);
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_GetMotionUint(ST_MotionUint& stMotionUint)
{
    int res = m_stSoftMotionEX.vMotionUint.size();
    if(0 == res)
    {
        return 0;
    }
    for(auto it = m_stSoftMotionEX.vMotionUint.begin();it<m_stSoftMotionEX.vMotionUint.end();it++)
    {
        stMotionUint = *it;
        if(it->bMotionDone)
        {
            continue;
        }
    }
    return AEC_SUCCESSED;
}


bool CIA402Axis::Axis_PDOErrorCheck()
{
    bool statuswordCheck = (m_stMirrorPDO.StatusWord & en_StatusWord_f) != 0;
    //errorCodeCheck
    return statuswordCheck;
}

void CIA402Axis::Axis_RT()
{
    Axis_PDOErrorCheck();
    AxisStatusCheck();
    PDOsynchronization();
    DataSynchronization();
    m_bCyclicSyncMotion = false;
    return;
}

void CIA402Axis::DataSynchronization()
{
    //PDO
    nCmdControlWord = m_stMirrorPDO.Controlword;
    nActStatusWord = m_stMirrorPDO.StatusWord;
    TargetPosition_PDO = m_stMirrorPDO.TargetPosition;
    nActualPosition_PDO = m_stMirrorPDO.ActualPosition;
    nCmdModeOpration = m_stMirrorPDO.TargetModesOfOperation;
    nActModeOpration = m_stMirrorPDO.ActualModesOfOperation;
    TargetTorque_PDO  = m_stMirrorPDO.TargetTorque;
    ActualTorque_PDO = m_stMirrorPDO.ActualTorque;
    TargetVelocity_PDO = m_stMirrorPDO.TargetVelocity;
    ActualVelocity_PDO =  m_stMirrorPDO.ActualVelocity;
    nAxisErrorID        = m_stMirrorPDO.ErrorCode;
    DigitalOutputs = m_stMirrorPDO.DigitalOutputs;
    DigitalInputs = m_stMirrorPDO.DigitalInputs;

    //运动数据
    dSetPosition = m_stAxisMotionData_now.dTarPos = m_stAxisConfiguration.nEncodeDirection * 
                        double(m_stMirrorPDO.TargetPosition - m_stAxisConfiguration.nEncodeHomePos) / 
                        double(m_stAxisConfiguration.nEncodeRatio * m_stAxisConfiguration.dGearRatio);
    dActPosition = m_stAxisMotionData_now.dTarPos = m_stAxisConfiguration.nEncodeDirection * 
                                        double(m_stMirrorPDO.ActualPosition - m_stAxisConfiguration.nEncodeHomePos) / 
                                        double(m_stAxisConfiguration.nEncodeRatio * m_stAxisConfiguration.dGearRatio);
    dSetTorque =   m_stAxisMotionData_now.dActCur = m_stMirrorPDO.TargetTorque / m_stAxisConfiguration.dTorqueScales * m_stAxisConfiguration.nTorqueDirection;    
    dActTorque =   m_stAxisMotionData_now.dActCur = m_stMirrorPDO.ActualTorque / m_stAxisConfiguration.dTorqueScales * m_stAxisConfiguration.nTorqueDirection;                  
    //状态
    nAxisErrorID = m_nErrorCode;
    bBusy     = m_bBusy;
    nAxisID   = m_nAxisID;
    enAxisMotionState = m_enAxisMotionState;
    //配置
    bVirtual = m_bVirtual;
    dGearRatio = m_stAxisConfiguration.dGearRatio;
    nEncodeRatio = m_stAxisConfiguration.nEncodeRatio;
    nEncodeDirection = m_stAxisConfiguration.nEncodeDirection;
    nEncodeHomePos = m_stAxisConfiguration.nEncodeHomePos;
    dTorqueScales = m_stAxisConfiguration.dTorqueScales;
    dVelocityScale = m_stAxisConfiguration.dVelocityScale;
    nTorqueDirection = m_stAxisConfiguration.nTorqueDirection;
    return;
}

void CIA402Axis::AxisStatusCheck()
{
    if(EN_AxisMotionState::motionState_synchronized_motion == m_enAxisMotionState)
    {
        if(m_bCyclicSyncMotion)
        {
            m_bCyclicSyncMotion = false;
        }
        else
        {
            m_nCyclicSyncMotionLosCount ++;
        }
        if(m_nCyclicSyncMotionLosCount>2)
        {
            Axis_SetAxisState(EN_AxisMotionState::motionState_standstill);
        }
    }
    else
    {
        m_nCyclicSyncMotionLosCount = 0;
    }
    return;
}