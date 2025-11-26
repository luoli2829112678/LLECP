#include"NETX_50_RE_ECS.h"


NETX_50_RE_ECS::NETX_50_RE_ECS(/* args */)
{
    m_SlaveType = enAxis;
    m_eep_man = 37940;
    m_eep_id = 27;
}

NETX_50_RE_ECS::~NETX_50_RE_ECS()
{
}

int NETX_50_RE_ECS::InitPDOmap(ec_slavet* ec_clave)
{
    if (ec_clave == nullptr)
    {
        return -1;
    }
    m_TxPDO = (ST_NETX_TxPDO*)ec_clave->inputs;
    m_RxPDO = (ST_NETX_RxPDO*)ec_clave->outputs;
    m_RxPDO->TargetPos = m_TxPDO->ActualPos;
    m_RxPDO->TargetModeOpration = m_TxPDO->ActModeOpration;
    m_RxPDO->TargetCur = m_TxPDO->ActualCur;
    return 0;
}

void NETX_50_RE_ECS::Slave_RT()
{
    //printf("ActPOS:%d\n",m_TxPDO->ActualPos);
    return;
}

int NETX_50_RE_ECS::ConstructionCIA402Axis(CIA402Axis*& p_Axis)
{
    p_Axis = new CIA402Axis(false);
    ST_SMCInitMap st_map;
    //映射PDO
    st_map.pControlword = &m_RxPDO->ControlWord;
    st_map.pTargetModesOfOperation = &m_RxPDO->TargetModeOpration;
    st_map.pTargetPosition = &m_RxPDO->TargetPos;

    st_map.pStatusWord = &m_TxPDO->StatusWord;
    st_map.pActualModesOfOperation = &m_TxPDO->ActModeOpration;
    st_map.pActualPosition = &m_TxPDO->ActualPos;
    p_Axis->Axis_InitMap(st_map);
    return 0;
}