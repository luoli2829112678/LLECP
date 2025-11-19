#include"CIA402Axis.h"

int CIA402Axis::Axis_SetGearRatio(double GearRatio)
{
    m_stAxisConfiguration.dGearRatio = GearRatio;
    this->dGearRatio = GearRatio;
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_SetEncodeRatio(uint32_t EncodeRatio)
{
    m_stAxisConfiguration.nEncodeRatio = EncodeRatio;
    nEncodeRatio = EncodeRatio;
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_SetEncodeDirection(int EncodeDirection)
{
    m_stAxisConfiguration.nEncodeDirection = EncodeDirection;
    nEncodeDirection = EncodeDirection;
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_SetEncodeHomePos(int32_t EncodeHomePos)
{
    m_stAxisConfiguration.nEncodeHomePos = EncodeHomePos;
    nEncodeHomePos = EncodeHomePos;
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_SetTorqueScales(double TorqueScales)
{
    m_stAxisConfiguration.dTorqueScales = TorqueScales;
    dTorqueScales = TorqueScales;
    return AEC_SUCCESSED;
}
int CIA402Axis::Axis_SetVelocityScale(double VelocityScale)
{
    m_stAxisConfiguration.dVelocityScale = VelocityScale;
    dVelocityScale = VelocityScale;
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_SetTorqueDirection(int TorqueDirection)
{
    m_stAxisConfiguration.nTorqueDirection = TorqueDirection;
    nTorqueDirection = TorqueDirection;
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_SetSWLimit(double Positive,double Negative)
{
    m_stAxisConfiguration.dPositive = Positive;
    m_stAxisConfiguration.dNegative = Negative;
    dPositive = Positive;
    dNegative = Negative;
    return AEC_SUCCESSED;
}
int CIA402Axis::Axis_SetControlCycle(double dControlCycle)
{
    m_dControlCycle = dControlCycle;
    return AEC_SUCCESSED;
}

int CIA402Axis::Axis_SetDriveErrorCode(int ErrorCode)
{
    m_nErrorCode = ErrorCode;
    return AEC_SUCCESSED;
}