
#ifndef _KRLOBJNODE_T_H
#define _KRLOBJNODE_T_H

typedef struct s_OBJNODE
{
    spinlock_t  on_lock; //IO包自选
    list_h_t    on_list; //IO包链表
    sem_t       on_complesem; //IO包完成服务时用到的信号量
    uint_t      on_flgs; //IO包标志
    uint_t      on_stus; //IO包状态
    sint_t      on_opercode; //IO包操作码
    uint_t      on_objtype; //IO包类型
    void*       on_objadr; //对象指针
    uint_t      on_acsflgs; //访问标志
    uint_t      on_acsstus; //访问状态
    uint_t      on_currops; //不同的操作，其意义不同
    uint_t      on_len; //不同的操作，其意义不同
    uint_t      on_ioctrd; //控制码
    buf_t       on_buf; //缓冲区地址
    uint_t      on_bufcurops; //不同的操作，其意义不同
    size_t      on_bufsz; //缓冲区大小
    uint_t      on_count; //不同的操作，其意义不同
    void*       on_safedsc; //IO包安全描述符
    void*       on_fname; //文件路径名指针
    void*        on_finode; //文件对应的fimgrhd_t结构指针
    void*       on_extp; //扩展所用
}objnode_t;


#define OBJN_TY_DEV 1
#define OBJN_TY_FIL 2
#define OBJN_TY_NUL 0

#endif // KRLOBJNODE_T_H
