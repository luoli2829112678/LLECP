
#include"EtherCATMaster.h"

uint8_t EtherCATMaster::writeSDO_SHORT(int slave_no, uint16_t index, uint8_t subidx, short value)
{
  int ret;
  ret = ecx_SDOwrite(&m_ctx,slave_no, index, subidx, FALSE, sizeof(value), &value, 700000);
  return ret;
}
uint8_t EtherCATMaster::writeSDO_INT(int slave_no, uint16_t index, uint8_t subidx, int value)
{
  int ret;
  ret = ecx_SDOwrite(&m_ctx,slave_no, index, subidx, FALSE, sizeof(value), &value, 700000);
  return ret;
}
uint8_t EtherCATMaster::writeSDO_LONG(int slave_no, uint16_t index, uint8_t subidx, long value)
{
  int ret;
  ret = ecx_SDOwrite(&m_ctx,slave_no, index, subidx, FALSE, sizeof(value), &value, 700000);
  return ret;
}
uint8_t EtherCATMaster::writeSDO_UCHAR(int slave_no, uint16_t index, uint8_t subidx,unsigned char value)
{
  int ret;
  ret = ecx_SDOwrite(&m_ctx,slave_no, index, subidx, FALSE, sizeof(value), &value, 700000);
  return ret;
}
uint8_t EtherCATMaster::writeSDO_USHORT(int slave_no, uint16_t index, uint8_t subidx,unsigned short value)
{
  int ret;
  ret = ecx_SDOwrite(&m_ctx,slave_no, index, subidx, FALSE, sizeof(value), &value, 700000);
  return ret;
}
uint8_t EtherCATMaster::writeSDO_UINT(int slave_no, uint16_t index, uint8_t subidx,unsigned int value)
{
  int ret;
  ret = ecx_SDOwrite(&m_ctx,slave_no, index, subidx, FALSE, sizeof(value), &value, 700000);
  return ret;
}
uint8_t EtherCATMaster::writeSDO_ULONG(int slave_no, uint16_t index, uint8_t subidx,unsigned long value)
{
  int ret;
  ret = ecx_SDOwrite(&m_ctx,slave_no, index, subidx, FALSE, sizeof(value), &value, 700000);
  return ret;
}

// char EtherCATMaster::readSDO_CHAR(int slave_no, uint16_t index, uint8_t subidx)
// {
//     int ret, l;
//     char val;
//     l = sizeof(val);
//     ret = ecx_SDOread(&m_ctx,slave_no, index, subidx, FALSE, &l, &val, 700000);
//     if ( ret <= 0 ) { // ret = Workcounter from last slave response
//         fprintf(stderr, "Failed to read from ret:%d, slave_no:%d, index:0x%04x, subidx:0x%02x\n", ret, slave_no, index, subidx);
//     }
//     return val;
// }
short EtherCATMaster::readSDO_SHORT(int slave_no, uint16_t index, uint8_t subidx)
{
    int ret, l;
    short val;
    l = sizeof(val);
    ret = ecx_SDOread(&m_ctx,slave_no, index, subidx, FALSE, &l, &val, 700000);
    return val;
}
int EtherCATMaster::readSDO_INT(int slave_no, uint16_t index, uint8_t subidx, int *Value)
{
  int ret, l;
  int val;
  l = sizeof(val);
  ret = ecx_SDOread(&m_ctx,slave_no, index, subidx, FALSE, &l, Value, 700000);
  return ret;
}
long EtherCATMaster::readSDO_LONG(int slave_no, uint16_t index, uint8_t subidx)
{
    int ret, l;
    long val;
    l = sizeof(val);
    ret = ecx_SDOread(&m_ctx,slave_no, index, subidx, FALSE, &l, &val, 700000);
    return val;
}
unsigned char EtherCATMaster::readSDO_UCHAR(int slave_no, uint16_t index, uint8_t subidx)
{
    int ret, l;
    unsigned char val;
    l = sizeof(val);
    ret = ecx_SDOread(&m_ctx,slave_no, index, subidx, FALSE, &l, &val, 700000);
    return val;
}
unsigned short EtherCATMaster::readSDO_USHORT(int slave_no, uint16_t index, uint8_t subidx)
{
    int ret, l;
    unsigned short val;
    l = sizeof(val);
    ret = ecx_SDOread(&m_ctx,slave_no, index, subidx, FALSE, &l, &val, 700000);
    return val;
}
unsigned int EtherCATMaster::readSDO_UINT(int slave_no, uint16_t index, uint8_t subidx)
{
    int ret, l;
    unsigned int val;
    l = sizeof(val);
    ret = ecx_SDOread(&m_ctx,slave_no, index, subidx, FALSE, &l, &val, 700000);
    return val;
}
unsigned long EtherCATMaster::readSDO_ULONG(int slave_no, uint16_t index, uint8_t subidx)
{
    int ret, l;
    unsigned long val;
    l = sizeof(val);
    ret = ecx_SDOread(&m_ctx,slave_no, index, subidx, FALSE, &l, &val, 700000);
    return val;
}
