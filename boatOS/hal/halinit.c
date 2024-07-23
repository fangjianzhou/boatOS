
#include "seafarertypes.h"
#include "seafarerctrl.h"
LKHEAD_T void init_hal()
{
    init_paltform();
    init_haluart();
    init_halmach();
    init_halmm();
    init_halintupt();
    //print_mach(&osmach);
    //print_mmapdsc(&osmach);
    //for(;;);
    //test_blkmm();
    return;
}
