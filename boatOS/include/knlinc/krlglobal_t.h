
#ifndef _KRLGLOBAL_T_H
#define _KRLGLOBAL_T_H
#define KRL_DEFGLOB_VARIABLE(vartype,varname) \
KEXTERN  __attribute__((section(".data"))) vartype varname
#endif // KRLGLOBAL_T_H
