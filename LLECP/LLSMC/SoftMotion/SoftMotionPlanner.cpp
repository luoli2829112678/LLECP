#include"SoftMotion.h"
void SoftMotion::SoftMotionPlanner_RT()
{
    for(size_t i = 0;i<m_v_Axis.size();i++)
    {
        AxisMotionPlanner(m_v_Axis[i]);
    }
    return;
}

int SoftMotion::AxisMotionPlanner(CIA402Axis* pAxis)
{
    //状态校验
    if((pAxis->Axis_ReadAxisState()!=EN_AxisMotionState::motionState_standstill)
            &&(pAxis->Axis_ReadAxisState()!=EN_AxisMotionState::motionState_discrete_motion)
            &&(pAxis->Axis_ReadAxisState()!=EN_AxisMotionState::motionState_continuous_motion)
            &&(pAxis->Axis_ReadAxisState()!=EN_AxisMotionState::motionState_synchronized_motion))
            {
                pAxis->m_stSoftMotionEX.vMotionUint.clear();
                return AEC_SUCCESSED;
            }
    double T;
    if(pAxis->m_stSoftMotionEX.vMotionUint.size() == 0)
    {
        return AEC_SUCCESSED;
    }
    auto itMotionData = pAxis->m_stSoftMotionEX.vMotionUint.begin();
    while(itMotionData->bMotionDone)
    {
        itMotionData ++;
        //所有点位运动完成
        if(pAxis->m_stSoftMotionEX.vMotionUint.end() == itMotionData)
        {
            //切换状态
            pAxis->Axis_SetAxisState(EN_AxisMotionState::motionState_standstill);
            return AEC_SUCCESSED;
        }
    }
    pAxis->Axis_SetAxisState(EN_AxisMotionState::motionState_discrete_motion);
    //当前迭代器内是正在运动的点位
    ST_PlanningMotionParam stMotionParam = itMotionData->PlanningMotionParam;
    //正在运行当前点位
    if((pAxis->m_stSoftMotionEX.stSoftMotionMotionParam == stMotionParam)&&(!pAxis->m_stSoftMotionEX.bReplan))
    {
        //通用规划
        switch (stMotionParam.PlanningMode)
        {
        case EN_PlanningMode::enPositionPlanningMode:
        case EN_PlanningMode::enVelocityPlanningMode:
                //得到当前帧的运动参数
                FifteenSeg_Inter(m_vSoftMotionPlanParams[pAxis->nAxisID].stActParam,m_vSoftMotionPlanParams[pAxis->nAxisID].trackData,
                                pAxis->m_stSoftMotionEX.dMotionTime,m_vSoftMotionPlanParams[pAxis->nAxisID].stInterData);
            break;
        case EN_PlanningMode::enStopPlanningMode:
                stopmotion(stMotionParam.pos,stMotionParam.vel,pAxis->dSetAcceleration_s,stMotionParam.dec,stMotionParam.jerk,pAxis->m_stSoftMotionEX.dMotionTime,T,m_vSoftMotionPlanParams[pAxis->nAxisID].stInterData);
                printf("T:%F------Time:%f--------AxisPos:%f---vel:%f\n",T,pAxis->m_stSoftMotionEX.dMotionTime,m_vSoftMotionPlanParams[pAxis->nAxisID].stInterData.P,
                   m_vSoftMotionPlanParams[pAxis->nAxisID].stInterData.V);
                break;     
        default:
            break;
        }
        //开始运动 
        pAxis->Axis_SetMotionPlanner(m_vSoftMotionPlanParams[pAxis->nAxisID].stInterData);
        //时间帧加
        pAxis->m_stSoftMotionEX.dMotionTime += m_dSoftMotionCycle;
    }
    else//新点位
    {
        pAxis->m_stSoftMotionEX.bReplan = false;
        ST_PlanningMotionParam stMotionParam_Run = stMotionParam;
        ST_PlanParams stsetParam;
        switch (stMotionParam_Run.PlanningMode)
        {
        case EN_PlanningMode::enPositionPlanningMode:
        case EN_PlanningMode::enVelocityPlanningMode:
            //绝对运动做偏移
            if(enRelativMotion == itMotionData->MoveType)
            {
                stMotionParam_Run.pos = pAxis->dActPosition + stMotionParam_Run.pos;
            }
            pAxis->m_stSoftMotionEX.stSoftMotionMotionParam = stMotionParam;
            pAxis->m_stSoftMotionEX.dMotionTime = 0;
            stsetParam.q0 = pAxis->dActPosition;
            stsetParam.q1 = stMotionParam_Run.pos;
            stsetParam.v0 = pAxis->dSetVelocity_s;
            stsetParam.v1 = 0;
            stsetParam.a0 = 0;
            stsetParam.a1 = 0;
            stsetParam.V_max = stMotionParam_Run.vel *  pAxis->m_stSoftMotionEX.m_stFactor.dVelFactor;
            stsetParam.A_amax = stMotionParam_Run.acc *  pAxis->m_stSoftMotionEX.m_stFactor.dAccFactor;
            stsetParam.A_dmax = stMotionParam_Run.dec *  pAxis->m_stSoftMotionEX.m_stFactor.dJerkFactor;
            stsetParam.J_max = stMotionParam_Run.jerk;
            stsetParam.S_max = MaxSnap;
            stsetParam.enPlanmode = stMotionParam_Run.PlanningMode;
            FifteenSeg_plan(stsetParam,m_vSoftMotionPlanParams[pAxis->nAxisID].stActParam,m_vSoftMotionPlanParams[pAxis->nAxisID].trackData);
            //得到当前帧的运动参数
            FifteenSeg_Inter(m_vSoftMotionPlanParams[pAxis->nAxisID].stActParam,m_vSoftMotionPlanParams[pAxis->nAxisID].trackData,
                            pAxis->m_stSoftMotionEX.dMotionTime,m_vSoftMotionPlanParams[pAxis->nAxisID].stInterData);
            break;
        case EN_PlanningMode::enStopPlanningMode:
            stMotionParam.pos = pAxis->dActPosition;
            stMotionParam.vel = pAxis->dSetVelocity_s;
            pAxis->m_stSoftMotionEX.stSoftMotionMotionParam = stMotionParam;
            pAxis->m_stSoftMotionEX.dMotionTime = 0;
            printf("startStoppos:%f\n",pAxis->dActPosition);
            stopmotion(pAxis->dActPosition,
                pAxis->dSetVelocity_s,
                pAxis->dSetAcceleration_s,
                stMotionParam.dec,
                stMotionParam.jerk,
                pAxis->m_stSoftMotionEX.dMotionTime,
                T,
                m_vSoftMotionPlanParams[pAxis->nAxisID].stInterData);
                m_vSoftMotionPlanParams[pAxis->nAxisID].stActParam,m_vSoftMotionPlanParams[pAxis->nAxisID].trackData.T = T;
            break;
        default:
            break;
        }
        //开始运动 
        pAxis->Axis_SetMotionPlanner(m_vSoftMotionPlanParams[pAxis->nAxisID].stInterData);
        //时间帧加
        pAxis->m_stSoftMotionEX.dMotionTime += m_dSoftMotionCycle;
    }





    //运动完成检测
    if((enPositionPlanningMode == itMotionData->PlanningMotionParam.PlanningMode)||(enStopPlanningMode == itMotionData->PlanningMotionParam.PlanningMode))
    {
        if(pAxis->m_stSoftMotionEX.dMotionTime > m_vSoftMotionPlanParams[pAxis->nAxisID].trackData.T)
        {
            itMotionData->bMotionDone = true;
        }
    }
    return AEC_SUCCESSED;
}