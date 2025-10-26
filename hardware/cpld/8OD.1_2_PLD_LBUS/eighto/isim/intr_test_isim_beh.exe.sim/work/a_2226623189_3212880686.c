/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "//S8FS01/Matt/Electronics/eightoduino/PLD/eighto/intr_test.vhd";



void work_a_2226623189_3212880686_sub_2361317755_3145898073(char *t0, char *t1, char *t2, char *t3)
{
    char t5[40];
    char t6[16];
    char t11[16];
    char *t7;
    char *t8;
    int t9;
    unsigned int t10;
    char *t12;
    int t13;
    unsigned char t14;
    char *t15;
    char *t16;
    unsigned char t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    unsigned int t30;
    int64 t31;

LAB0:    t7 = (t6 + 0U);
    t8 = (t7 + 0U);
    *((int *)t8) = 15;
    t8 = (t7 + 4U);
    *((int *)t8) = 0;
    t8 = (t7 + 8U);
    *((int *)t8) = -1;
    t9 = (0 - 15);
    t10 = (t9 * -1);
    t10 = (t10 + 1);
    t8 = (t7 + 12U);
    *((unsigned int *)t8) = t10;
    t8 = (t11 + 0U);
    t12 = (t8 + 0U);
    *((int *)t12) = 15;
    t12 = (t8 + 4U);
    *((int *)t12) = 0;
    t12 = (t8 + 8U);
    *((int *)t12) = -1;
    t13 = (0 - 15);
    t10 = (t13 * -1);
    t10 = (t10 + 1);
    t12 = (t8 + 12U);
    *((unsigned int *)t12) = t10;
    t12 = (t5 + 4U);
    t14 = (t2 != 0);
    if (t14 == 1)
        goto LAB3;

LAB2:    t15 = (t5 + 12U);
    *((char **)t15) = t6;
    t16 = (t5 + 20U);
    t17 = (t3 != 0);
    if (t17 == 1)
        goto LAB5;

LAB4:    t18 = (t5 + 28U);
    *((char **)t18) = t11;
    t19 = (t0 + 15496U);
    t20 = (t19 + 12U);
    t10 = *((unsigned int *)t20);
    t10 = (t10 * 1U);
    t21 = xsi_get_transient_memory(t10);
    memset(t21, 0, t10);
    t22 = t21;
    memset(t22, (unsigned char)4, t10);
    t23 = (t0 + 10480);
    t24 = (t23 + 56U);
    t25 = *((char **)t24);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    t28 = (t0 + 15496U);
    t29 = (t28 + 12U);
    t30 = *((unsigned int *)t29);
    t30 = (t30 * 1U);
    memcpy(t27, t21, t30);
    xsi_driver_first_trans_fast(t23);
    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB9:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB10;

LAB11:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB7:
LAB8:
LAB6:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB15:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB16;

LAB17:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB13:
LAB14:
LAB12:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (15 * 1000LL);
    xsi_process_wait(t1, t31);

LAB21:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB22;

LAB23:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB19:
LAB20:
LAB18:    t7 = (t0 + 10480);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    t22 = (t0 + 15496U);
    t23 = (t22 + 12U);
    t10 = *((unsigned int *)t23);
    t10 = (t10 * 1U);
    memcpy(t21, t2, t10);
    xsi_driver_first_trans_fast(t7);
    t31 = (15 * 1000LL);
    xsi_process_wait(t1, t31);

LAB27:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB28;

LAB29:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB25:
LAB26:
LAB24:    t7 = (t0 + 9136);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (20 * 1000LL);
    xsi_process_wait(t1, t31);

LAB33:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB34;

LAB35:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB31:
LAB32:
LAB30:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB39:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB40;

LAB41:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB37:
LAB38:
LAB36:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB45:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB46;

LAB47:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB43:
LAB44:
LAB42:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (36 * 1000LL);
    xsi_process_wait(t1, t31);

LAB51:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB52;

LAB53:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB49:
LAB50:
LAB48:    t7 = (t0 + 9136);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (14 * 1000LL);
    xsi_process_wait(t1, t31);

LAB57:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB58;

LAB59:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB55:
LAB56:
LAB54:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB63:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB64;

LAB65:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB61:
LAB62:
LAB60:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB69:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB70;

LAB71:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB67:
LAB68:
LAB66:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (18 * 1000LL);
    xsi_process_wait(t1, t31);

LAB75:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB76;

LAB77:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB73:
LAB74:
LAB72:    t7 = (t0 + 10352);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (10 * 1000LL);
    xsi_process_wait(t1, t31);

LAB81:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB82;

LAB83:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB79:
LAB80:
LAB78:    t7 = (t0 + 10480);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    t22 = (t0 + 15496U);
    t23 = (t22 + 12U);
    t10 = *((unsigned int *)t23);
    t10 = (t10 * 1U);
    memcpy(t21, t3, t10);
    xsi_driver_first_trans_fast(t7);
    t31 = (18 * 1000LL);
    xsi_process_wait(t1, t31);

LAB87:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB88;

LAB89:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB85:
LAB86:
LAB84:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB93:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB94;

LAB95:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB91:
LAB92:
LAB90:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB99:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB100;

LAB101:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB97:
LAB98:
LAB96:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (50 * 1000LL);
    xsi_process_wait(t1, t31);

LAB105:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB106;

LAB107:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB103:
LAB104:
LAB102:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB111:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB112;

LAB113:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB109:
LAB110:
LAB108:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB117:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB118;

LAB119:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB115:
LAB116:
LAB114:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (50 * 1000LL);
    xsi_process_wait(t1, t31);

LAB123:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB124;

LAB125:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB121:
LAB122:
LAB120:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB129:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB130;

LAB131:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB127:
LAB128:
LAB126:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB135:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB136;

LAB137:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB133:
LAB134:
LAB132:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (50 * 1000LL);
    xsi_process_wait(t1, t31);

LAB141:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB142;

LAB143:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB139:
LAB140:
LAB138:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB147:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB148;

LAB149:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB145:
LAB146:
LAB144:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)2;
    xsi_driver_first_trans_fast(t7);
    t31 = (12 * 1000LL);
    xsi_process_wait(t1, t31);

LAB153:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB154;

LAB155:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB151:
LAB152:
LAB150:    t7 = (t0 + 10032);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t31 = (25 * 1000LL);
    xsi_process_wait(t1, t31);

LAB159:    t7 = (t1 + 88U);
    t8 = *((char **)t7);
    t19 = (t8 + 2480U);
    *((unsigned int *)t19) = 1U;
    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 0U);
    getcontext(t22);
    t23 = (t1 + 88U);
    t24 = *((char **)t23);
    t25 = (t24 + 2480U);
    t10 = *((unsigned int *)t25);
    if (t10 == 1)
        goto LAB160;

LAB161:    t26 = (t1 + 88U);
    t27 = *((char **)t26);
    t28 = (t27 + 2480U);
    *((unsigned int *)t28) = 3U;

LAB157:
LAB158:
LAB156:    t7 = (t0 + 10352);
    t8 = (t7 + 56U);
    t19 = *((char **)t8);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    t7 = (t0 + 15496U);
    t8 = (t7 + 12U);
    t10 = *((unsigned int *)t8);
    t10 = (t10 * 1U);
    t19 = xsi_get_transient_memory(t10);
    memset(t19, 0, t10);
    t20 = t19;
    memset(t20, (unsigned char)4, t10);
    t21 = (t0 + 10480);
    t22 = (t21 + 56U);
    t23 = *((char **)t22);
    t24 = (t23 + 56U);
    t25 = *((char **)t24);
    t26 = (t0 + 15496U);
    t27 = (t26 + 12U);
    t30 = *((unsigned int *)t27);
    t30 = (t30 * 1U);
    memcpy(t25, t19, t30);
    xsi_driver_first_trans_fast(t21);

LAB1:    return;
LAB3:    *((char **)t12) = t2;
    goto LAB2;

LAB5:    *((char **)t16) = t3;
    goto LAB4;

LAB10:    xsi_saveStackAndSuspend(t1);
    goto LAB11;

LAB16:    xsi_saveStackAndSuspend(t1);
    goto LAB17;

LAB22:    xsi_saveStackAndSuspend(t1);
    goto LAB23;

LAB28:    xsi_saveStackAndSuspend(t1);
    goto LAB29;

LAB34:    xsi_saveStackAndSuspend(t1);
    goto LAB35;

LAB40:    xsi_saveStackAndSuspend(t1);
    goto LAB41;

LAB46:    xsi_saveStackAndSuspend(t1);
    goto LAB47;

LAB52:    xsi_saveStackAndSuspend(t1);
    goto LAB53;

LAB58:    xsi_saveStackAndSuspend(t1);
    goto LAB59;

LAB64:    xsi_saveStackAndSuspend(t1);
    goto LAB65;

LAB70:    xsi_saveStackAndSuspend(t1);
    goto LAB71;

LAB76:    xsi_saveStackAndSuspend(t1);
    goto LAB77;

LAB82:    xsi_saveStackAndSuspend(t1);
    goto LAB83;

LAB88:    xsi_saveStackAndSuspend(t1);
    goto LAB89;

LAB94:    xsi_saveStackAndSuspend(t1);
    goto LAB95;

LAB100:    xsi_saveStackAndSuspend(t1);
    goto LAB101;

LAB106:    xsi_saveStackAndSuspend(t1);
    goto LAB107;

LAB112:    xsi_saveStackAndSuspend(t1);
    goto LAB113;

LAB118:    xsi_saveStackAndSuspend(t1);
    goto LAB119;

LAB124:    xsi_saveStackAndSuspend(t1);
    goto LAB125;

LAB130:    xsi_saveStackAndSuspend(t1);
    goto LAB131;

LAB136:    xsi_saveStackAndSuspend(t1);
    goto LAB137;

LAB142:    xsi_saveStackAndSuspend(t1);
    goto LAB143;

LAB148:    xsi_saveStackAndSuspend(t1);
    goto LAB149;

LAB154:    xsi_saveStackAndSuspend(t1);
    goto LAB155;

LAB160:    xsi_saveStackAndSuspend(t1);
    goto LAB161;

}

void work_a_2226623189_3212880686_sub_196525925_3145898073(char *t0, char *t1, char *t2)
{
    char t4[24];
    char t5[16];
    char *t6;
    char *t7;
    int t8;
    unsigned int t9;
    unsigned char t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    unsigned int t23;
    int64 t24;

LAB0:    t6 = (t5 + 0U);
    t7 = (t6 + 0U);
    *((int *)t7) = 15;
    t7 = (t6 + 4U);
    *((int *)t7) = 0;
    t7 = (t6 + 8U);
    *((int *)t7) = -1;
    t8 = (0 - 15);
    t9 = (t8 * -1);
    t9 = (t9 + 1);
    t7 = (t6 + 12U);
    *((unsigned int *)t7) = t9;
    t7 = (t4 + 4U);
    t10 = (t2 != 0);
    if (t10 == 1)
        goto LAB3;

LAB2:    t11 = (t4 + 12U);
    *((char **)t11) = t5;
    t12 = (t0 + 15496U);
    t13 = (t12 + 12U);
    t9 = *((unsigned int *)t13);
    t9 = (t9 * 1U);
    t14 = xsi_get_transient_memory(t9);
    memset(t14, 0, t9);
    t15 = t14;
    memset(t15, (unsigned char)4, t9);
    t16 = (t0 + 10480);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    t21 = (t0 + 15496U);
    t22 = (t21 + 12U);
    t23 = *((unsigned int *)t22);
    t23 = (t23 * 1U);
    memcpy(t20, t14, t23);
    xsi_driver_first_trans_fast(t16);
    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB7:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB8;

LAB9:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB5:
LAB6:
LAB4:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB13:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB14;

LAB15:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB11:
LAB12:
LAB10:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (15 * 1000LL);
    xsi_process_wait(t1, t24);

LAB19:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB20;

LAB21:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB17:
LAB18:
LAB16:    t6 = (t0 + 10480);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    t16 = (t0 + 15496U);
    t17 = (t16 + 12U);
    t9 = *((unsigned int *)t17);
    t9 = (t9 * 1U);
    memcpy(t15, t2, t9);
    xsi_driver_first_trans_fast(t6);
    t24 = (15 * 1000LL);
    xsi_process_wait(t1, t24);

LAB25:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB26;

LAB27:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB23:
LAB24:
LAB22:    t6 = (t0 + 9136);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (20 * 1000LL);
    xsi_process_wait(t1, t24);

LAB31:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB32;

LAB33:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB29:
LAB30:
LAB28:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB37:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB38;

LAB39:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB35:
LAB36:
LAB34:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB43:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB44;

LAB45:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB41:
LAB42:
LAB40:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (36 * 1000LL);
    xsi_process_wait(t1, t24);

LAB49:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB50;

LAB51:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB47:
LAB48:
LAB46:    t6 = (t0 + 9136);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (14 * 1000LL);
    xsi_process_wait(t1, t24);

LAB55:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB56;

LAB57:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB53:
LAB54:
LAB52:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB61:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB62;

LAB63:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB59:
LAB60:
LAB58:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB67:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB68;

LAB69:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB65:
LAB66:
LAB64:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (18 * 1000LL);
    xsi_process_wait(t1, t24);

LAB73:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB74;

LAB75:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB71:
LAB72:
LAB70:    t6 = (t0 + 15496U);
    t12 = (t6 + 12U);
    t9 = *((unsigned int *)t12);
    t9 = (t9 * 1U);
    t13 = xsi_get_transient_memory(t9);
    memset(t13, 0, t9);
    t14 = t13;
    memset(t14, (unsigned char)4, t9);
    t15 = (t0 + 10480);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    t20 = (t0 + 15496U);
    t21 = (t20 + 12U);
    t23 = *((unsigned int *)t21);
    t23 = (t23 * 1U);
    memcpy(t19, t13, t23);
    xsi_driver_first_trans_fast(t15);
    t24 = (10 * 1000LL);
    xsi_process_wait(t1, t24);

LAB79:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB80;

LAB81:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB77:
LAB78:
LAB76:    t6 = (t0 + 10416);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (18 * 1000LL);
    xsi_process_wait(t1, t24);

LAB85:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB86;

LAB87:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB83:
LAB84:
LAB82:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB91:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB92;

LAB93:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB89:
LAB90:
LAB88:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB97:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB98;

LAB99:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB95:
LAB96:
LAB94:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (50 * 1000LL);
    xsi_process_wait(t1, t24);

LAB103:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB104;

LAB105:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB101:
LAB102:
LAB100:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB109:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB110;

LAB111:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB107:
LAB108:
LAB106:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB115:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB116;

LAB117:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB113:
LAB114:
LAB112:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (50 * 1000LL);
    xsi_process_wait(t1, t24);

LAB121:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB122;

LAB123:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB119:
LAB120:
LAB118:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB127:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB128;

LAB129:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB125:
LAB126:
LAB124:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB133:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB134;

LAB135:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB131:
LAB132:
LAB130:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (50 * 1000LL);
    xsi_process_wait(t1, t24);

LAB139:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB140;

LAB141:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB137:
LAB138:
LAB136:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB145:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB146;

LAB147:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB143:
LAB144:
LAB142:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)2;
    xsi_driver_first_trans_fast(t6);
    t24 = (12 * 1000LL);
    xsi_process_wait(t1, t24);

LAB151:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB152;

LAB153:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB149:
LAB150:
LAB148:    t6 = (t0 + 10032);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t24 = (25 * 1000LL);
    xsi_process_wait(t1, t24);

LAB157:    t6 = (t1 + 88U);
    t12 = *((char **)t6);
    t13 = (t12 + 2480U);
    *((unsigned int *)t13) = 1U;
    t14 = (t1 + 88U);
    t15 = *((char **)t14);
    t16 = (t15 + 0U);
    getcontext(t16);
    t17 = (t1 + 88U);
    t18 = *((char **)t17);
    t19 = (t18 + 2480U);
    t9 = *((unsigned int *)t19);
    if (t9 == 1)
        goto LAB158;

LAB159:    t20 = (t1 + 88U);
    t21 = *((char **)t20);
    t22 = (t21 + 2480U);
    *((unsigned int *)t22) = 3U;

LAB155:
LAB156:
LAB154:    t6 = (t0 + 10416);
    t12 = (t6 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    t6 = (t0 + 15496U);
    t12 = (t6 + 12U);
    t9 = *((unsigned int *)t12);
    t9 = (t9 * 1U);
    t13 = xsi_get_transient_memory(t9);
    memset(t13, 0, t9);
    t14 = t13;
    memset(t14, (unsigned char)4, t9);
    t15 = (t0 + 10480);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    t20 = (t0 + 15496U);
    t21 = (t20 + 12U);
    t23 = *((unsigned int *)t21);
    t23 = (t23 * 1U);
    memcpy(t19, t13, t23);
    xsi_driver_first_trans_fast(t15);

LAB1:    return;
LAB3:    *((char **)t7) = t2;
    goto LAB2;

LAB8:    xsi_saveStackAndSuspend(t1);
    goto LAB9;

LAB14:    xsi_saveStackAndSuspend(t1);
    goto LAB15;

LAB20:    xsi_saveStackAndSuspend(t1);
    goto LAB21;

LAB26:    xsi_saveStackAndSuspend(t1);
    goto LAB27;

LAB32:    xsi_saveStackAndSuspend(t1);
    goto LAB33;

LAB38:    xsi_saveStackAndSuspend(t1);
    goto LAB39;

LAB44:    xsi_saveStackAndSuspend(t1);
    goto LAB45;

LAB50:    xsi_saveStackAndSuspend(t1);
    goto LAB51;

LAB56:    xsi_saveStackAndSuspend(t1);
    goto LAB57;

LAB62:    xsi_saveStackAndSuspend(t1);
    goto LAB63;

LAB68:    xsi_saveStackAndSuspend(t1);
    goto LAB69;

LAB74:    xsi_saveStackAndSuspend(t1);
    goto LAB75;

LAB80:    xsi_saveStackAndSuspend(t1);
    goto LAB81;

LAB86:    xsi_saveStackAndSuspend(t1);
    goto LAB87;

LAB92:    xsi_saveStackAndSuspend(t1);
    goto LAB93;

LAB98:    xsi_saveStackAndSuspend(t1);
    goto LAB99;

LAB104:    xsi_saveStackAndSuspend(t1);
    goto LAB105;

LAB110:    xsi_saveStackAndSuspend(t1);
    goto LAB111;

LAB116:    xsi_saveStackAndSuspend(t1);
    goto LAB117;

LAB122:    xsi_saveStackAndSuspend(t1);
    goto LAB123;

LAB128:    xsi_saveStackAndSuspend(t1);
    goto LAB129;

LAB134:    xsi_saveStackAndSuspend(t1);
    goto LAB135;

LAB140:    xsi_saveStackAndSuspend(t1);
    goto LAB141;

LAB146:    xsi_saveStackAndSuspend(t1);
    goto LAB147;

LAB152:    xsi_saveStackAndSuspend(t1);
    goto LAB153;

LAB158:    xsi_saveStackAndSuspend(t1);
    goto LAB159;

}

static void work_a_2226623189_3212880686_p_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    int64 t9;

LAB0:    t1 = (t0 + 8752U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(283, ng0);
    t2 = (t0 + 9136);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(284, ng0);
    t2 = (t0 + 9200);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(285, ng0);
    t2 = (t0 + 15729);
    t4 = (t0 + 9264);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 4U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(286, ng0);
    t2 = (t0 + 15733);
    t4 = (t0 + 9328);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 20U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(287, ng0);
    t2 = (t0 + 9392);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(289, ng0);
    t2 = (t0 + 9456);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(290, ng0);
    t2 = (t0 + 9520);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(291, ng0);
    t2 = (t0 + 9584);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(292, ng0);
    t2 = (t0 + 9648);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(294, ng0);
    t2 = (t0 + 9712);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(295, ng0);
    t2 = (t0 + 9776);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(296, ng0);
    t2 = (t0 + 9840);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(297, ng0);
    t2 = (t0 + 9904);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(299, ng0);
    t2 = (t0 + 9968);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(300, ng0);
    t2 = (t0 + 10032);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(301, ng0);
    t2 = (t0 + 10096);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)4;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(303, ng0);
    t2 = xsi_get_transient_memory(16U);
    memset(t2, 0, 16U);
    t3 = t2;
    memset(t3, (unsigned char)2, 16U);
    t4 = (t0 + 10160);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(304, ng0);
    t2 = xsi_get_transient_memory(6U);
    memset(t2, 0, 6U);
    t3 = t2;
    memset(t3, (unsigned char)4, 6U);
    t4 = (t0 + 10224);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 6U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(305, ng0);
    t2 = xsi_get_transient_memory(16U);
    memset(t2, 0, 16U);
    t3 = t2;
    memset(t3, (unsigned char)4, 16U);
    t4 = (t0 + 10288);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(307, ng0);
    t2 = (t0 + 10352);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(308, ng0);
    t2 = (t0 + 10416);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(310, ng0);
    t2 = xsi_get_transient_memory(16U);
    memset(t2, 0, 16U);
    t3 = t2;
    memset(t3, (unsigned char)2, 16U);
    t4 = (t0 + 10480);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(312, ng0);
    t2 = (t0 + 10544);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(313, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB6:    *((char **)t1) = &&LAB7;

LAB1:    return;
LAB4:    xsi_set_current_line(314, ng0);
    t2 = (t0 + 10544);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(315, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB10:    *((char **)t1) = &&LAB11;
    goto LAB1;

LAB5:    goto LAB4;

LAB7:    goto LAB5;

LAB8:    xsi_set_current_line(317, ng0);
    t2 = xsi_get_transient_memory(16U);
    memset(t2, 0, 16U);
    t3 = t2;
    memset(t3, (unsigned char)2, 16U);
    t4 = (t0 + 10160);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(319, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 15753);
    t5 = (t0 + 15769);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(322, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 15785);
    t5 = (t0 + 15801);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(324, ng0);
    t2 = (t0 + 15817);
    t4 = (t0 + 10160);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(325, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB14:    *((char **)t1) = &&LAB15;
    goto LAB1;

LAB9:    goto LAB8;

LAB11:    goto LAB9;

LAB12:    xsi_set_current_line(331, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 15833);
    t5 = (t0 + 15849);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(332, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 15865);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(335, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 15881);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(338, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 15897);
    t5 = (t0 + 15913);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(340, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 15929);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(343, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 15945);
    t5 = (t0 + 15961);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(345, ng0);
    t2 = (t0 + 15977);
    t4 = (t0 + 10160);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(346, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB18:    *((char **)t1) = &&LAB19;
    goto LAB1;

LAB13:    goto LAB12;

LAB15:    goto LAB13;

LAB16:    xsi_set_current_line(349, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 15993);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(350, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16009);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(352, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16025);
    t5 = (t0 + 16041);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(353, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16057);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(355, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16073);
    t5 = (t0 + 16089);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(357, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16105);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(360, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16121);
    t5 = (t0 + 16137);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(362, ng0);
    t2 = (t0 + 9712);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(364, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB22:    *((char **)t1) = &&LAB23;
    goto LAB1;

LAB17:    goto LAB16;

LAB19:    goto LAB17;

LAB20:    xsi_set_current_line(367, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16153);
    t5 = (t0 + 16169);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(368, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16185);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(370, ng0);
    t2 = (t0 + 9712);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(373, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16201);
    t5 = (t0 + 16217);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(375, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB26:    *((char **)t1) = &&LAB27;
    goto LAB1;

LAB21:    goto LAB20;

LAB23:    goto LAB21;

LAB24:    xsi_set_current_line(378, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16233);
    t5 = (t0 + 16249);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(380, ng0);
    t2 = (t0 + 9776);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(382, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB30:    *((char **)t1) = &&LAB31;
    goto LAB1;

LAB25:    goto LAB24;

LAB27:    goto LAB25;

LAB28:    xsi_set_current_line(385, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16265);
    t5 = (t0 + 16281);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(386, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16297);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(388, ng0);
    t2 = (t0 + 9776);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(391, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16313);
    t5 = (t0 + 16329);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(393, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB34:    *((char **)t1) = &&LAB35;
    goto LAB1;

LAB29:    goto LAB28;

LAB31:    goto LAB29;

LAB32:    xsi_set_current_line(396, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16345);
    t5 = (t0 + 16361);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(398, ng0);
    t2 = (t0 + 9840);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(400, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB38:    *((char **)t1) = &&LAB39;
    goto LAB1;

LAB33:    goto LAB32;

LAB35:    goto LAB33;

LAB36:    xsi_set_current_line(403, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16377);
    t5 = (t0 + 16393);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(404, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16409);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(406, ng0);
    t2 = (t0 + 9840);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(409, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16425);
    t5 = (t0 + 16441);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(411, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB42:    *((char **)t1) = &&LAB43;
    goto LAB1;

LAB37:    goto LAB36;

LAB39:    goto LAB37;

LAB40:    xsi_set_current_line(414, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16457);
    t5 = (t0 + 16473);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(416, ng0);
    t2 = (t0 + 9904);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(418, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB46:    *((char **)t1) = &&LAB47;
    goto LAB1;

LAB41:    goto LAB40;

LAB43:    goto LAB41;

LAB44:    xsi_set_current_line(421, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16489);
    t5 = (t0 + 16505);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(422, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16521);
    work_a_2226623189_3212880686_sub_196525925_3145898073(t0, t2, t3);
    xsi_set_current_line(424, ng0);
    t2 = (t0 + 9904);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(427, ng0);
    t2 = (t0 + 8560);
    t3 = (t0 + 16537);
    t5 = (t0 + 16553);
    work_a_2226623189_3212880686_sub_2361317755_3145898073(t0, t2, t3, t5);
    xsi_set_current_line(429, ng0);
    t9 = (100 * 1000LL);
    t2 = (t0 + 8560);
    xsi_process_wait(t2, t9);

LAB50:    *((char **)t1) = &&LAB51;
    goto LAB1;

LAB45:    goto LAB44;

LAB47:    goto LAB45;

LAB48:    xsi_set_current_line(431, ng0);

LAB54:    *((char **)t1) = &&LAB55;
    goto LAB1;

LAB49:    goto LAB48;

LAB51:    goto LAB49;

LAB52:    goto LAB2;

LAB53:    goto LAB52;

LAB55:    goto LAB53;

}


extern void work_a_2226623189_3212880686_init()
{
	static char *pe[] = {(void *)work_a_2226623189_3212880686_p_0};
	static char *se[] = {(void *)work_a_2226623189_3212880686_sub_2361317755_3145898073,(void *)work_a_2226623189_3212880686_sub_196525925_3145898073};
	xsi_register_didat("work_a_2226623189_3212880686", "isim/intr_test_isim_beh.exe.sim/work/a_2226623189_3212880686.didat");
	xsi_register_executes(pe);
	xsi_register_subprogram_executes(se);
}
