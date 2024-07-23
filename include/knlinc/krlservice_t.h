
#ifndef KRLSERVICE_T_H
#define KRLSERVICE_T_H

#define SNR_MM_ALLOC 0x1
#define SNR_MM_FREE 0x2
#define SNR_TD_EXEL 0x3
#define SNR_TD_EXIT 0x4
#define SNR_TD_HAND 0x5
#define SNR_TD_RSTATS 0x6
#define SNR_TD_SSTATS 0x7
#define SNR_FS_OPEN 0x8
#define SNR_FS_CLOSE 0x9
#define SNR_FS_READ 0xa
#define SNR_FS_WRITE 0xb
#define SNR_FS_IOCTRL 0xc
#define SNR_FS_LSEEK 0xd
#define SNR_TIME 0xe

#define SWINR_MAX 0xf

#define SYSSTUSERR (-1)
#define SYSSTUSOK (0)
#define FILE_TY_MASK 0xf
#define FILE_TY_FILE 0
#define FILE_TY_DEV 1
#define RWO_FLG_MASK 0xff
#define RWO_FLG_BITS 0x4
#define RW_FLG 0x3
#define RO_FLG 0x1
#define WO_FLG 0x2
#define NF_FLG 0x4



typedef struct s_STKPARAME
{
    reg_t rvs0;//因为stmfd sp!,{r1,lr}代码会让SP寄存器自增，所以这里有4B的空间
    reg_t rvs1;
    reg_t parmv1;
    reg_t parmv2; 
    reg_t parmv3; 
    reg_t parmv4; 
    reg_t parmv5; 
    reg_t parmv6; 
    reg_t parmv7;     
}stkparame_t;

typedef sysstus_t (*syscall_t)(uint_t swinr,stkparame_t* stkparm);

KRL_DEFGLOB_VARIABLE(syscall_t,osscalltab)[SWINR_MAX]={
NULL,krlsvetabl_mallocblk,
krlsvetabl_mfreeblk,krlsvetabl_exel_thread,
krlsvetabl_exit_thread,
krlsvetabl_retn_threadhand,
krlsvetabl_retn_threadstats,
krlsvetabl_set_threadstats,
krlsvetabl_open,krlsvetabl_close,
krlsvetabl_read,krlsvetabl_write,
krlsvetabl_ioctrl,krlsvetabl_lseek,
krlsvetabl_time};

#endif // KRLSERVICE_T_H
