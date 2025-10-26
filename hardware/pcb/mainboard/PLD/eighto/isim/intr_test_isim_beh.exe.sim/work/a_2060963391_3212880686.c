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
static const char *ng0 = "//S8FS01/Matt/Electronics/eightoduino/PLD/eighto/portread.vhd";



static void work_a_2060963391_3212880686_p_0(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    unsigned char t14;
    unsigned char t15;
    unsigned char t16;
    unsigned char t17;
    unsigned char t18;
    unsigned char t19;
    char *t20;
    char *t21;
    unsigned char t22;
    unsigned char t23;
    unsigned char t24;
    int t25;
    unsigned char t26;
    char *t27;

LAB0:    xsi_set_current_line(52, ng0);
    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB2;

LAB4:    xsi_set_current_line(55, ng0);
    t1 = (t0 + 1032U);
    t2 = *((char **)t1);
    t6 = (15 - 15);
    t7 = (t6 * 1U);
    t8 = (0 + t7);
    t1 = (t2 + t8);
    t5 = (t0 + 4192);
    t9 = (t5 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    memcpy(t12, t1, 10U);
    xsi_driver_first_trans_delta(t5, 0U, 10U, 0LL);

LAB3:    xsi_set_current_line(58, ng0);
    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t14 = *((unsigned char *)t2);
    t15 = (t14 == (unsigned char)3);
    if (t15 == 1)
        goto LAB11;

LAB12:    t4 = (unsigned char)0;

LAB13:    if (t4 == 1)
        goto LAB8;

LAB9:    t3 = (unsigned char)0;

LAB10:    if (t3 != 0)
        goto LAB5;

LAB7:    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t14 = *((unsigned char *)t2);
    t15 = (t14 == (unsigned char)2);
    if (t15 == 1)
        goto LAB19;

LAB20:    t4 = (unsigned char)0;

LAB21:    if (t4 == 1)
        goto LAB16;

LAB17:    t3 = (unsigned char)0;

LAB18:    if (t3 != 0)
        goto LAB14;

LAB15:    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t14 = *((unsigned char *)t2);
    t15 = (t14 == (unsigned char)2);
    if (t15 == 1)
        goto LAB27;

LAB28:    t4 = (unsigned char)0;

LAB29:    if (t4 == 1)
        goto LAB24;

LAB25:    t3 = (unsigned char)0;

LAB26:    if (t3 != 0)
        goto LAB22;

LAB23:    xsi_set_current_line(65, ng0);
    t1 = (t0 + 1032U);
    t2 = *((char **)t1);
    t6 = (15 - 5);
    t7 = (t6 * 1U);
    t8 = (0 + t7);
    t1 = (t2 + t8);
    t5 = (t0 + 4192);
    t9 = (t5 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    memcpy(t12, t1, 5U);
    xsi_driver_first_trans_delta(t5, 10U, 5U, 0LL);

LAB6:    xsi_set_current_line(68, ng0);
    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t15 = *((unsigned char *)t2);
    t16 = (t15 == (unsigned char)3);
    if (t16 == 1)
        goto LAB39;

LAB40:    t14 = (unsigned char)0;

LAB41:    if (t14 == 1)
        goto LAB36;

LAB37:    t4 = (unsigned char)0;

LAB38:    if (t4 == 1)
        goto LAB33;

LAB34:    t3 = (unsigned char)0;

LAB35:    if (t3 != 0)
        goto LAB30;

LAB32:    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t15 = *((unsigned char *)t2);
    t16 = (t15 == (unsigned char)2);
    if (t16 == 1)
        goto LAB50;

LAB51:    t14 = (unsigned char)0;

LAB52:    if (t14 == 1)
        goto LAB47;

LAB48:    t4 = (unsigned char)0;

LAB49:    if (t4 == 1)
        goto LAB44;

LAB45:    t3 = (unsigned char)0;

LAB46:    if (t3 != 0)
        goto LAB42;

LAB43:    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t15 = *((unsigned char *)t2);
    t16 = (t15 == (unsigned char)2);
    if (t16 == 1)
        goto LAB61;

LAB62:    t14 = (unsigned char)0;

LAB63:    if (t14 == 1)
        goto LAB58;

LAB59:    t4 = (unsigned char)0;

LAB60:    if (t4 == 1)
        goto LAB55;

LAB56:    t3 = (unsigned char)0;

LAB57:    if (t3 != 0)
        goto LAB53;

LAB54:    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t15 = *((unsigned char *)t2);
    t16 = (t15 == (unsigned char)2);
    if (t16 == 1)
        goto LAB72;

LAB73:    t14 = (unsigned char)0;

LAB74:    if (t14 == 1)
        goto LAB69;

LAB70:    t4 = (unsigned char)0;

LAB71:    if (t4 == 1)
        goto LAB66;

LAB67:    t3 = (unsigned char)0;

LAB68:    if (t3 != 0)
        goto LAB64;

LAB65:    xsi_set_current_line(77, ng0);
    t1 = (t0 + 1032U);
    t2 = *((char **)t1);
    t25 = (0 - 15);
    t6 = (t25 * -1);
    t7 = (1U * t6);
    t8 = (0 + t7);
    t1 = (t2 + t8);
    t3 = *((unsigned char *)t1);
    t5 = (t0 + 4192);
    t9 = (t5 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = t3;
    xsi_driver_first_trans_delta(t5, 15U, 1, 0LL);

LAB31:    t1 = (t0 + 4112);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(53, ng0);
    t1 = (t0 + 1352U);
    t5 = *((char **)t1);
    t6 = (15 - 15);
    t7 = (t6 * 1U);
    t8 = (0 + t7);
    t1 = (t5 + t8);
    t9 = (t0 + 4192);
    t10 = (t9 + 56U);
    t11 = *((char **)t10);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    memcpy(t13, t1, 10U);
    xsi_driver_first_trans_delta(t9, 0U, 10U, 0LL);
    goto LAB3;

LAB5:    xsi_set_current_line(59, ng0);
    t1 = (t0 + 1352U);
    t10 = *((char **)t1);
    t6 = (15 - 5);
    t7 = (t6 * 1U);
    t8 = (0 + t7);
    t1 = (t10 + t8);
    t11 = (t0 + 4192);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    t20 = (t13 + 56U);
    t21 = *((char **)t20);
    memcpy(t21, t1, 5U);
    xsi_driver_first_trans_delta(t11, 10U, 5U, 0LL);
    goto LAB6;

LAB8:    t1 = (t0 + 2472U);
    t9 = *((char **)t1);
    t18 = *((unsigned char *)t9);
    t19 = (t18 == (unsigned char)2);
    t3 = t19;
    goto LAB10;

LAB11:    t1 = (t0 + 2152U);
    t5 = *((char **)t1);
    t16 = *((unsigned char *)t5);
    t17 = (t16 == (unsigned char)2);
    t4 = t17;
    goto LAB13;

LAB14:    xsi_set_current_line(61, ng0);
    t1 = (t0 + 1192U);
    t10 = *((char **)t1);
    t6 = (5 - 5);
    t7 = (t6 * 1U);
    t8 = (0 + t7);
    t1 = (t10 + t8);
    t11 = (t0 + 4192);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    t20 = (t13 + 56U);
    t21 = *((char **)t20);
    memcpy(t21, t1, 5U);
    xsi_driver_first_trans_delta(t11, 10U, 5U, 0LL);
    goto LAB6;

LAB16:    t1 = (t0 + 2472U);
    t9 = *((char **)t1);
    t18 = *((unsigned char *)t9);
    t19 = (t18 == (unsigned char)2);
    t3 = t19;
    goto LAB18;

LAB19:    t1 = (t0 + 2152U);
    t5 = *((char **)t1);
    t16 = *((unsigned char *)t5);
    t17 = (t16 == (unsigned char)3);
    t4 = t17;
    goto LAB21;

LAB22:    xsi_set_current_line(63, ng0);
    t1 = (t0 + 1512U);
    t10 = *((char **)t1);
    t6 = (5 - 5);
    t7 = (t6 * 1U);
    t8 = (0 + t7);
    t1 = (t10 + t8);
    t11 = (t0 + 4192);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    t20 = (t13 + 56U);
    t21 = *((char **)t20);
    memcpy(t21, t1, 5U);
    xsi_driver_first_trans_delta(t11, 10U, 5U, 0LL);
    goto LAB6;

LAB24:    t1 = (t0 + 2472U);
    t9 = *((char **)t1);
    t18 = *((unsigned char *)t9);
    t19 = (t18 == (unsigned char)3);
    t3 = t19;
    goto LAB26;

LAB27:    t1 = (t0 + 2152U);
    t5 = *((char **)t1);
    t16 = *((unsigned char *)t5);
    t17 = (t16 == (unsigned char)2);
    t4 = t17;
    goto LAB29;

LAB30:    xsi_set_current_line(69, ng0);
    t1 = (t0 + 1352U);
    t11 = *((char **)t1);
    t25 = (0 - 15);
    t6 = (t25 * -1);
    t7 = (1U * t6);
    t8 = (0 + t7);
    t1 = (t11 + t8);
    t26 = *((unsigned char *)t1);
    t12 = (t0 + 4192);
    t13 = (t12 + 56U);
    t20 = *((char **)t13);
    t21 = (t20 + 56U);
    t27 = *((char **)t21);
    *((unsigned char *)t27) = t26;
    xsi_driver_first_trans_delta(t12, 15U, 1, 0LL);
    goto LAB31;

LAB33:    t1 = (t0 + 2632U);
    t10 = *((char **)t1);
    t23 = *((unsigned char *)t10);
    t24 = (t23 == (unsigned char)2);
    t3 = t24;
    goto LAB35;

LAB36:    t1 = (t0 + 2472U);
    t9 = *((char **)t1);
    t19 = *((unsigned char *)t9);
    t22 = (t19 == (unsigned char)2);
    t4 = t22;
    goto LAB38;

LAB39:    t1 = (t0 + 2152U);
    t5 = *((char **)t1);
    t17 = *((unsigned char *)t5);
    t18 = (t17 == (unsigned char)2);
    t14 = t18;
    goto LAB41;

LAB42:    xsi_set_current_line(71, ng0);
    t1 = (t0 + 1192U);
    t11 = *((char **)t1);
    t25 = (0 - 5);
    t6 = (t25 * -1);
    t7 = (1U * t6);
    t8 = (0 + t7);
    t1 = (t11 + t8);
    t26 = *((unsigned char *)t1);
    t12 = (t0 + 4192);
    t13 = (t12 + 56U);
    t20 = *((char **)t13);
    t21 = (t20 + 56U);
    t27 = *((char **)t21);
    *((unsigned char *)t27) = t26;
    xsi_driver_first_trans_delta(t12, 15U, 1, 0LL);
    goto LAB31;

LAB44:    t1 = (t0 + 2632U);
    t10 = *((char **)t1);
    t23 = *((unsigned char *)t10);
    t24 = (t23 == (unsigned char)2);
    t3 = t24;
    goto LAB46;

LAB47:    t1 = (t0 + 2472U);
    t9 = *((char **)t1);
    t19 = *((unsigned char *)t9);
    t22 = (t19 == (unsigned char)2);
    t4 = t22;
    goto LAB49;

LAB50:    t1 = (t0 + 2152U);
    t5 = *((char **)t1);
    t17 = *((unsigned char *)t5);
    t18 = (t17 == (unsigned char)3);
    t14 = t18;
    goto LAB52;

LAB53:    xsi_set_current_line(73, ng0);
    t1 = (t0 + 1512U);
    t11 = *((char **)t1);
    t25 = (0 - 5);
    t6 = (t25 * -1);
    t7 = (1U * t6);
    t8 = (0 + t7);
    t1 = (t11 + t8);
    t26 = *((unsigned char *)t1);
    t12 = (t0 + 4192);
    t13 = (t12 + 56U);
    t20 = *((char **)t13);
    t21 = (t20 + 56U);
    t27 = *((char **)t21);
    *((unsigned char *)t27) = t26;
    xsi_driver_first_trans_delta(t12, 15U, 1, 0LL);
    goto LAB31;

LAB55:    t1 = (t0 + 2632U);
    t10 = *((char **)t1);
    t23 = *((unsigned char *)t10);
    t24 = (t23 == (unsigned char)2);
    t3 = t24;
    goto LAB57;

LAB58:    t1 = (t0 + 2472U);
    t9 = *((char **)t1);
    t19 = *((unsigned char *)t9);
    t22 = (t19 == (unsigned char)3);
    t4 = t22;
    goto LAB60;

LAB61:    t1 = (t0 + 2152U);
    t5 = *((char **)t1);
    t17 = *((unsigned char *)t5);
    t18 = (t17 == (unsigned char)2);
    t14 = t18;
    goto LAB63;

LAB64:    xsi_set_current_line(75, ng0);
    t1 = (t0 + 1672U);
    t11 = *((char **)t1);
    t26 = *((unsigned char *)t11);
    t1 = (t0 + 4192);
    t12 = (t1 + 56U);
    t13 = *((char **)t12);
    t20 = (t13 + 56U);
    t21 = *((char **)t20);
    *((unsigned char *)t21) = t26;
    xsi_driver_first_trans_delta(t1, 15U, 1, 0LL);
    goto LAB31;

LAB66:    t1 = (t0 + 2632U);
    t10 = *((char **)t1);
    t23 = *((unsigned char *)t10);
    t24 = (t23 == (unsigned char)3);
    t3 = t24;
    goto LAB68;

LAB69:    t1 = (t0 + 2472U);
    t9 = *((char **)t1);
    t19 = *((unsigned char *)t9);
    t22 = (t19 == (unsigned char)2);
    t4 = t22;
    goto LAB71;

LAB72:    t1 = (t0 + 2152U);
    t5 = *((char **)t1);
    t17 = *((unsigned char *)t5);
    t18 = (t17 == (unsigned char)2);
    t14 = t18;
    goto LAB74;

}


extern void work_a_2060963391_3212880686_init()
{
	static char *pe[] = {(void *)work_a_2060963391_3212880686_p_0};
	xsi_register_didat("work_a_2060963391_3212880686", "isim/intr_test_isim_beh.exe.sim/work/a_2060963391_3212880686.didat");
	xsi_register_executes(pe);
}
