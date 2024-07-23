
#include "seafarertypes.h"
#include "seafarerctrl.h"
void init_krlmm()
{
    init_krlpagempol();

    return; 
}

adr_t krlnew(size_t mmsize)
{
    if(mmsize==MALCSZ_MIN||mmsize>MALCSZ_MAX)
    {
        return NULL;
    }
    return kmempool_new(mmsize);
}

bool_t krldelete(adr_t fradr,size_t frsz)
{
    if(fradr==NULL||frsz==MALCSZ_MIN||frsz>MALCSZ_MAX)
    {
        return FALSE;
    }
    return  kmempool_delete(fradr,frsz);
}

