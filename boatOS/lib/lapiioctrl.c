
#include "seafarertypes.h"
#include "seafarerctrl.h"

sysstus_t api_ioctrl(hand_t fhand,buf_t buf,uint_t iocode,uint_t flgs)
{
    sysstus_t rets;
    API_ENTRY_PARE4(SNR_FS_IOCTRL,rets,fhand,buf,iocode,flgs);
    return rets;
}