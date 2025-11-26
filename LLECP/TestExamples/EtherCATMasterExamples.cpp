#include"../EtherCATMaster/EtherCATMaster.h"
#include <unistd.h>
int main()
{
    EtherCATMaster* pMaster = new EtherCATMaster(0);  
    pMaster->StartMaster();
    sleep(1000);
    return 0;
}