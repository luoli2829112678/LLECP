#include"SlaveBase.h"
#pragma pack(push, 1)
typedef struct _ST_NETX_TxPDO
{
	uint16_t StatusWord;
	int32_t ActualPos;
	uint32_t DigitalInputs;
	int16_t ActualCur;
	uint8_t ActModeOpration;

}ST_NETX_TxPDO;

typedef struct _ST_NETX_RxPDO
{
	uint16_t ControlWord;
	int32_t TargetPos;
	uint32_t DigitalInputs;
	int16_t TargetCur;
	uint8_t TargetModeOpration;
	//int16_t VelFF;
}ST_NETX_RxPDO;

class NETX_50_RE_ECS: public SlaveBase
{
private:
	ST_NETX_TxPDO* m_TxPDO;
	ST_NETX_RxPDO* m_RxPDO;
    /* data */
public:
    NETX_50_RE_ECS(/* args */);
    ~NETX_50_RE_ECS();
	int InitPDOmap(ec_slavet* ec_clave)override;
	int ConstructionCIA402Axis(CIA402Axis*& p_Axis)override;
	void Slave_RT()override;
};

