
#include "seafarertypes.h"
#include "seafarerctrl.h"



hand_t api_open(void* file,uint_t flgs,uint_t stus)
{
    hand_t rethand;
    API_ENTRY_PARE3(SNR_FS_OPEN,rethand,file,flgs,stus);
    return rethand;
}