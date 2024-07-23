
#include "seafarertypes.h"
#include "seafarerctrl.h"

void init_krl()
{
    init_krlmm();
	init_krldevice();
    init_krldriver();
	init_krlsched();
    
    init_ktime();
    init_task();
    init_krlcpuidle();
    hal_sysdie("seafarer RUN!!");
    return;
}
