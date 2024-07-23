
#include "seafarertypes.h"
#include "seafarerctrl.h"




void hal_disable_cache()
{
    __asm__ __volatile__(
         "mrc p15,0,r0,c1,c0,0  \n\t"
         "orr r0,r0,%[tmpdata] \n\t"
         "mcr p15,0,r0,c1,c0,0 \n\t"
         : 
         :[tmpdata] "r" (0x1004)
         :"r0", "cc","memory"
    );    

}


u32_t cp15_read_c5()
{
    u32_t tmp;

    __asm__ __volatile__(
         "mrc p15,0,%[tmpreg],c5,c0,0  \n\t"
         : [tmpreg] "=r" (tmp)
         :
         : "cc","memory"
    );
    return tmp;
}

u32_t cp15_read_c6()
{
    u32_t tmp;

    __asm__ __volatile__(
         "mrc p15,0,%[tmpreg],c6,c0,0  \n\t"
         : [tmpreg] "=r" (tmp)
         :
         : "cc","memory"
    );
    return tmp;
}

u32_t hal_read_cp15regs(uint_t regnr)
{
    switch (regnr) {
    case CP15_C5R:
        return cp15_read_c5();
        break;
    case CP15_C6R:
        return cp15_read_c6();
        break;    
    default:
        break;
    }
    return 0;
}