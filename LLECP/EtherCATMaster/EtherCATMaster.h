#ifndef ETHERCATMASTER_H
#define ETHERCATMASTER_H
#include<vector>
#include<string>
#include"SOEM/soem/soem.h"
#include <stdint.h>
#include<stdio.h>
#include"EtherCATDef.h"
#include <thread>

#define SLAVEID 2
#define EC_TIMEOUTMON 500

static const int NSEC_PER_SECOND = 1e+9;
static const int NSEC_PER_USECOND = 1e+3;

class EtherCATMaster
{
protected:
    ecx_contextt m_ctx;
    
    
    uint8_t m_nMasterIndex;
    //ethercat master param
    bool m_bIsConfigDc;
    int m_nShitTime = 0;
    float m_fCycle = 1.0;
    bool m_bIsSimulation;
    std::string m_sNetWork = "enp2s0";

    //EtherCAT thread
    std::thread thEtherCAT_RT, thEtherCAT_RT_Check;
    /* data */
    uint8_t m_nSlaveNum;

    std::vector<std::string> m_vSlaveInfo;
    ec_slavet m_MasterInfo;




    int expectedWKC;
    int m_nWkc;

    //PDO

    int m_nRxPDOSize;//slave recv
    int m_nTxPDOSize;//slave send
    uint8_t  m_PDOmap[MAX_PDO_SIZE];
    ec_groupt*  m_p_ECTgroup;
    uint8 m_currentgroup = 0;
    uint16 m_wkc = 0;
    uint16 m_expectedWKC = 0;
    boolean m_bInOP = true;


    //SLAVE
    std::vector<SlaveBase*> m_v_slave;
public:
    EtherCATMaster(uint8_t nMasterIndex);
    ~EtherCATMaster();
    int SetNetworkPort(std::string networkport);
    int StartMaster();
    int CloseMaster();
    void Test();
    uint8_t writeSDO_SHORT(int slave_no, uint16_t index, uint8_t subidx, short value);
    uint8_t writeSDO_INT(int slave_no, uint16_t index, uint8_t subidx, int value);
    uint8_t writeSDO_LONG(int slave_no, uint16_t index, uint8_t subidx, long value);
    uint8_t writeSDO_UCHAR(int slave_no, uint16_t index, uint8_t subidx,unsigned char value);
    uint8_t writeSDO_USHORT(int slave_no, uint16_t index, uint8_t subidx,unsigned short value);
    uint8_t writeSDO_UINT(int slave_no, uint16_t index, uint8_t subidx,unsigned int value);
    uint8_t writeSDO_ULONG(int slave_no, uint16_t index, uint8_t subidx,unsigned long value);

    // char readSDO_CHAR(int slave_no, uint16_t index, uint8_t subidx);
    short readSDO_SHORT(int slave_no, uint16_t index, uint8_t subidx);
    int readSDO_INT(int slave_no, uint16_t index, uint8_t subidx, int *Value);
    long readSDO_LONG(int slave_no, uint16_t index, uint8_t subidx);
    unsigned char readSDO_UCHAR(int slave_no, uint16_t index, uint8_t subidx);
    unsigned short readSDO_USHORT(int slave_no, uint16_t index, uint8_t subidx);
    unsigned int readSDO_UINT(int slave_no, uint16_t index, uint8_t subidx);
    unsigned long readSDO_ULONG(int slave_no, uint16_t index, uint8_t subidx);

    
protected:
    //Thread
    int CreateRT_Thread(std::thread* th,void (EtherCATMaster::*func)());
    void EtherCAT_RT();
    void EtherCAT_RT_Check();
    int InitRT_Thread();
    bool m_bEtherCAT_RT;
    bool m_bEtherCAT_RT_Check;
    //SOEM
    int ScanSlave();
    int InitSlave();
public:
    //Axis
    int ConstructionCIA402AxisVec(std::vector<CIA402Axis*>* v_Axis);
};
#endif // ETHERCATMASTER_H