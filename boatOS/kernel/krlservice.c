
#include "seafarertypes.h"
#include "seafarerctrl.h"
sysstus_t krlservice(uint_t swinr,void* sframe)
{
    return osscalltab[swinr](swinr,(stkparame_t*)sframe);
}