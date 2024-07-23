
#include "seafarertypes.h"
#include "seafarerctrl.h"
sysstus_t api_lseek(hand_t fhand,uint_t lofset,uint_t flgs)
{
    sysstus_t rets;
    API_ENTRY_PARE3(SNR_FS_LSEEK,rets,fhand,lofset,flgs);
    return rets;
}