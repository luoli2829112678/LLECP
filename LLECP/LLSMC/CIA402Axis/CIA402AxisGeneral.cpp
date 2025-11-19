#include"CIA402Axis.h"

int CIA402Axis::Axis_SetMotionPlanner(ST_InterParams stMotionPlanner)
{
    dSetPosition_s = stMotionPlanner.P;
    dSetVelocity_s = stMotionPlanner.V;
    dSetAcceleration_s = stMotionPlanner.A;
    dSetJerk_s = stMotionPlanner.J;
    dSetSnap_s = stMotionPlanner.S;
    switch (m_stMirrorPDO.ActualModesOfOperation)
    {
    case EN_ModesOfOperation::enModeCyclicSyncPosition:
        Axis_SetTargetPosition(stMotionPlanner.P);
        break;
    case EN_ModesOfOperation::enModeCyclicSyncVelocity:
        Axis_SetTargetVelocity(stMotionPlanner.V);
        break;
    default:
        printf("m_stMirrorPDO.ActualModesOfOperationError%d\n",m_stMirrorPDO.ActualModesOfOperation);
        break;
    }
}

int CIA402Axis::Axis_SetTargetPosition(double TargetPosition)
{
    //printf("CmdPosition:%f\n",TargetPosition);
    int32_t count = m_stAxisConfiguration.nEncodeDirection *  (TargetPosition * m_stAxisConfiguration.nEncodeRatio * m_stAxisConfiguration.dGearRatio) + 
                                    m_stAxisConfiguration.nEncodeHomePos;
    Axis_PDO_SetTargetPosition(count);  
    dSetPosition = TargetPosition;
    return AEC_SUCCESSED;   
}

int CIA402Axis::Axis_SetTargetTorque(double TargetTorque)
{
    int32_t count = TargetTorque * m_stAxisConfiguration.nTorqueDirection * m_stAxisConfiguration.dTorqueScales;
    Axis_PDO_SetTargetTorque(count);  
    return AEC_SUCCESSED;  
}

int CIA402Axis::Axis_SetTargetVelocity(double TargetVelocity)
{
    int32_t count = TargetVelocity * m_stAxisConfiguration.nTorqueDirection * m_stAxisConfiguration.dVelocityScale;
    Axis_PDO_SetTargetVelocity(count);  
    return AEC_SUCCESSED;  
}
