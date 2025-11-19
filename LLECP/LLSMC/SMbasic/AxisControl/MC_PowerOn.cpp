#include"MC_PowerOn.h"
MC_PowerOn::MC_PowerOn(/* args */)
{
    m_bExecute =false;
    m_bBusy = false;
    m_bDone = false;
    m_bError = false;
    m_nErrorID = false;
}

MC_PowerOn::~MC_PowerOn()
{
}

void MC_PowerOn::operator()(CIA402Axis* axis)
{
    this->Execute();
}
void MC_PowerOn::operator()(CIA402Axis* axis,bool bExecute,bool &bBusy,bool &bDone, bool &bError,int &nErrorID)
{
    if((bExecute && m_bExecute)&&(axis != m_pCIA402Axis))
    {
        m_pCIA402Axis->Axis_SetAxisState(EN_AxisMotionState::motionState_errorstop);
        m_fsPowerOn = ReadyPowerOn;
        m_bBusy = false;
        m_bError = true;
        m_bDone = false;
        m_nErrorID = SMEC_ABNORMAL_AXIS_CHANGE;
    }
    m_pCIA402Axis = axis;
    m_bExecute = bExecute;
    this->Execute();
    m_bBusy = m_bBusy;
    bDone = m_bDone;
    bError = m_bError;
    nErrorID = m_nErrorID;
}

void MC_PowerOn::Execute()
{
    if(nullptr == m_pCIA402Axis)
    {
        m_bError = true;
        m_nErrorID = SMEC_INVALID_AXIS;
        return;
    }
    uint16_t nControlWord = 0;
    uint16_t nStatusWord = 0;
    int32_t nActPos;
    m_pCIA402Axis->Axis_PDO_ReadStatusWord(nStatusWord);
    m_pCIA402Axis->Axis_PDO_ReadControlword(nControlWord);
    m_bBusy = false;
    m_bError = false;
    m_bDone = false;
    m_nErrorID = SMEC_SUCCESSED;
    if(!m_bExecute)
    {
       m_Timer.R_TRIG(m_bExecute);
       m_fsPowerOn = ReadyPowerOn;
       return;
    }
    //检测使能中报错
    uint16_t unStatuBit;
    if(m_pCIA402Axis->Axis_CheckError())
    {
        m_fsPowerOn = PowerOnError;
        //反馈错误状态
        m_bError = true;
        m_Timer.Ton(false, SMC_TIME_OUT);
        m_pCIA402Axis->Axis_CheckError();
    } 
    //位置对齐
    if(ReadyPowerOn != m_fsPowerOn)
    {
        m_pCIA402Axis->Axis_PDO_ReadActualPosition(nActPos);
        m_pCIA402Axis->Axis_PDO_SetTargetPosition(nActPos);
    }
    //printf("POWRTON:%d\n",static_cast<int>(m_fsPowerOn));
    switch (m_fsPowerOn)
    {
        case ReadyPowerOn:
            if(m_Timer.R_TRIG(m_bExecute))
            {
                m_pCIA402Axis->Axis_PDO_ReadActualPosition(nActPos);
                m_pCIA402Axis->Axis_PDO_SetTargetPosition(nActPos);
                //检测轴是否为去使能状态（错误或运动等状态禁用）
                if(motionState_power_off != m_pCIA402Axis->Axis_ReadAxisState())
                {
                    //此状态不允许使能，也不切状态机，功能块置为error
                    m_fsPowerOn = PowerOnError;
                    //切换到错误状态
                    m_bError = true;
                    m_Timer.Ton(false, SMC_TIME_OUT);
                    break;
                }
                //切换到位置模式
                m_pCIA402Axis->Axis_PDO_SetModesOfOperation(EN_ModesOfOperation ::enModeCyclicSyncPosition);
                //虚拟轴直接使能完成
                if(m_pCIA402Axis->bVirtual)
                {
                    //反馈完成状态
                    m_bDone = true;
                    //同步状态机
                    m_pCIA402Axis->Axis_SetAxisState(EN_AxisMotionState::motionState_standstill);
                    m_fsPowerOn = PowerOnFinish;
                    m_Timer.Ton(false, SMC_TIME_OUT);
                    break;
                }
                //初始化控制字
                m_pCIA402Axis->Axis_PDO_SetControlword(en_ControlWord_Init);
                m_fsPowerOn = StartPowerOn;
                m_bBusy = true;
                m_Timer.Ton(false, SMC_TIME_OUT);
                break;
            }
            break;
        case StartPowerOn:
            m_pCIA402Axis->Axis_PDO_SetControlword(nControlWord | en_ControlWord_ev | en_ControlWord_qs);
            m_fsPowerOn = PowerOning_0x06;
            m_bBusy = true;
            break;
        case PowerOning_0x06:
            m_bBusy = true;
            unStatuBit = en_StatusWord_qs | en_StatusWord_rtso;
            if ((nStatusWord & unStatuBit) == unStatuBit)
            {
                m_pCIA402Axis->Axis_PDO_SetControlword(nControlWord | en_ControlWord_ev | en_ControlWord_qs | en_ControlWord_so);
                m_fsPowerOn = PowerOning_0x07;
                break;
            }
            //超时检测
            if(m_Timer.Ton(true, SMC_TIME_OUT))
            {
                m_fsPowerOn = PowerOnError;
                m_pCIA402Axis->Axis_SetAxisState(EN_AxisMotionState::motionState_errorstop);
                m_bError = true;
                m_bBusy = false;
                m_nErrorID = SMEC_TIMEOUT;
                m_Timer.Ton(false, SMC_TIME_OUT);
                break;
            }
            break;
        case PowerOning_0x07:
            m_bBusy = true;
            unStatuBit = en_StatusWord_qs | en_StatusWord_rtso | en_StatusWord_so;
            if ((nStatusWord & unStatuBit) == unStatuBit)
            {
                m_pCIA402Axis->Axis_PDO_SetControlword(nControlWord | en_ControlWord_ev | en_ControlWord_qs | en_ControlWord_so | en_ControlWord_eo);
                m_fsPowerOn = PowerOning_0x0F;
                break;
            }
            //超时检测
            if(m_Timer.Ton(true, SMC_TIME_OUT))
            {
                m_fsPowerOn = PowerOnError;
                m_pCIA402Axis->Axis_SetAxisState(EN_AxisMotionState::motionState_errorstop);
                m_bError = true;
                m_bBusy = false;
                m_nErrorID = SMEC_TIMEOUT;
                m_Timer.Ton(false, SMC_TIME_OUT);
                break;
            }
            break;
        case PowerOning_0x0F:
            m_bBusy = true;
            unStatuBit = en_StatusWord_qs | en_StatusWord_rtso | en_StatusWord_so | en_StatusWord_oe;
            if ((nStatusWord & unStatuBit) == unStatuBit)
            {
                //就绪
                m_bDone = true;
                m_fsPowerOn = PowerOnFinish;
                // 切换轴状态到准备就绪状态
                m_pCIA402Axis->Axis_SetAxisState(EN_AxisMotionState::motionState_standstill);
                break;
            }
            //超时检测
            if(m_Timer.Ton(true, SMC_TIME_OUT))
            {
                m_fsPowerOn = PowerOnError;
                m_pCIA402Axis->Axis_SetAxisState(EN_AxisMotionState::motionState_errorstop);
                m_bError = true;
                m_bBusy = false;
                m_nErrorID = SMEC_TIMEOUT;
                m_Timer.Ton(false, SMC_TIME_OUT);
                break;
            }
            break;
        case PowerOnFinish:
            if(m_Timer.F_TRIG(m_bExecute))
            {
                m_fsPowerOn = ReadyPowerOn;
                break;
            }
            m_bDone = true;
            break;
        case PowerOnError:
            if(m_Timer.F_TRIG(m_bExecute))
            {
                m_fsPowerOn = ReadyPowerOn;
                break;
            }
            m_bError = true;
            break;
        default:
            m_fsPowerOn = PowerOnError;
            break;
    }
}