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



static void unisim_a_3341709158_0094846637_p_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    unsigned char t4;
    unsigned char t5;
    unsigned char t6;
    unsigned char t7;
    char *t9;
    unsigned char t11;
    unsigned int t12;
    char *t13;
    char *t14;
    char *t15;
    char *t17;
    unsigned char t19;
    unsigned int t20;
    char *t21;
    char *t22;
    char *t23;
    char *t25;
    unsigned char t27;
    unsigned int t28;
    char *t29;
    char *t30;
    char *t31;
    char *t32;

LAB0:    t1 = (t0 + 3184U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1768U);
    t3 = *((char **)t2);
    t4 = *((unsigned char *)t3);
    t5 = (t4 == (unsigned char)1);
    if (t5 != 0)
        goto LAB4;

LAB6:
LAB5:
LAB38:    *((char **)t1) = &&LAB39;

LAB1:    return;
LAB4:    t2 = (t0 + 6004);
    t9 = (t0 + 6013);
    t11 = 1;
    if (9U == 3U)
        goto LAB16;

LAB17:    t11 = 0;

LAB18:    if (t11 == 1)
        goto LAB13;

LAB14:    t15 = (t0 + 6016);
    t17 = (t0 + 6025);
    t19 = 1;
    if (9U == 6U)
        goto LAB22;

LAB23:    t19 = 0;

LAB24:    t7 = t19;

LAB15:    if (t7 == 1)
        goto LAB10;

LAB11:    t23 = (t0 + 6031);
    t25 = (t0 + 6040);
    t27 = 1;
    if (9U == 9U)
        goto LAB28;

LAB29:    t27 = 0;

LAB30:    t6 = t27;

LAB12:    if (t6 != 0)
        goto LAB7;

LAB9:    if ((unsigned char)0 == 0)
        goto LAB34;

LAB35:
LAB8:    goto LAB5;

LAB7:    t31 = (t0 + 1768U);
    t32 = *((char **)t31);
    t31 = (t32 + 0);
    *((unsigned char *)t31) = (unsigned char)0;
    goto LAB8;

LAB10:    t6 = (unsigned char)1;
    goto LAB12;

LAB13:    t7 = (unsigned char)1;
    goto LAB15;

LAB16:    t12 = 0;

LAB19:    if (t12 < 9U)
        goto LAB20;
    else
        goto LAB18;

LAB20:    t13 = (t2 + t12);
    t14 = (t9 + t12);
    if (*((unsigned char *)t13) != *((unsigned char *)t14))
        goto LAB17;

LAB21:    t12 = (t12 + 1);
    goto LAB19;

LAB22:    t20 = 0;

LAB25:    if (t20 < 9U)
        goto LAB26;
    else
        goto LAB24;

LAB26:    t21 = (t15 + t20);
    t22 = (t17 + t20);
    if (*((unsigned char *)t21) != *((unsigned char *)t22))
        goto LAB23;

LAB27:    t20 = (t20 + 1);
    goto LAB25;

LAB28:    t28 = 0;

LAB31:    if (t28 < 9U)
        goto LAB32;
    else
        goto LAB30;

LAB32:    t29 = (t23 + t28);
    t30 = (t25 + t28);
    if (*((unsigned char *)t29) != *((unsigned char *)t30))
        goto LAB29;

LAB33:    t28 = (t28 + 1);
    goto LAB31;

LAB34:    t2 = (t0 + 6049);
    xsi_report(t2, 87U, (unsigned char)3);
    goto LAB35;

LAB36:    goto LAB2;

LAB37:    goto LAB36;

LAB39:    goto LAB37;

}

static void unisim_a_3341709158_0094846637_p_1(char *t0)
{
    unsigned char t1;
    char *t2;
    char *t3;
    unsigned char t4;
    unsigned char t5;
    char *t6;
    unsigned char t7;
    unsigned char t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    unsigned char t13;
    unsigned char t14;
    unsigned char t15;
    unsigned char t16;
    unsigned char t17;
    char *t18;
    char *t19;

LAB0:    t2 = (t0 + 1352U);
    t3 = *((char **)t2);
    t4 = *((unsigned char *)t3);
    t5 = (t4 == (unsigned char)3);
    if (t5 == 1)
        goto LAB5;

LAB6:    t2 = (t0 + 1352U);
    t6 = *((char **)t2);
    t7 = *((unsigned char *)t6);
    t8 = (t7 == (unsigned char)7);
    t1 = t8;

LAB7:    if (t1 != 0)
        goto LAB2;

LAB4:    t2 = (t0 + 1352U);
    t3 = *((char **)t2);
    t4 = *((unsigned char *)t3);
    t5 = (t4 == (unsigned char)2);
    if (t5 == 1)
        goto LAB10;

LAB11:    t2 = (t0 + 1352U);
    t6 = *((char **)t2);
    t7 = *((unsigned char *)t6);
    t8 = (t7 == (unsigned char)6);
    t1 = t8;

LAB12:    if (t1 != 0)
        goto LAB8;

LAB9:    t2 = (t0 + 1352U);
    t3 = *((char **)t2);
    t1 = *((unsigned char *)t3);
    t4 = (t1 == (unsigned char)0);
    if (t4 != 0)
        goto LAB26;

LAB27:    t2 = (t0 + 3832);
    t3 = (t2 + 56U);
    t6 = *((char **)t3);
    t9 = (t6 + 56U);
    t10 = *((char **)t9);
    *((unsigned char *)t10) = (unsigned char)1;
    xsi_driver_first_trans_fast_port(t2);

LAB3:    t2 = (t0 + 3752);
    *((int *)t2) = 1;

LAB1:    return;
LAB2:    t2 = (t0 + 3832);
    t9 = (t2 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = (unsigned char)4;
    xsi_driver_first_trans_fast_port(t2);
    goto LAB3;

LAB5:    t1 = (unsigned char)1;
    goto LAB7;

LAB8:    t2 = (t0 + 1192U);
    t9 = *((char **)t2);
    t14 = *((unsigned char *)t9);
    t15 = (t14 == (unsigned char)3);
    if (t15 == 1)
        goto LAB16;

LAB17:    t2 = (t0 + 1192U);
    t10 = *((char **)t2);
    t16 = *((unsigned char *)t10);
    t17 = (t16 == (unsigned char)7);
    t13 = t17;

LAB18:    if (t13 != 0)
        goto LAB13;

LAB15:    t2 = (t0 + 1192U);
    t3 = *((char **)t2);
    t4 = *((unsigned char *)t3);
    t5 = (t4 == (unsigned char)2);
    if (t5 == 1)
        goto LAB21;

LAB22:    t2 = (t0 + 1192U);
    t6 = *((char **)t2);
    t7 = *((unsigned char *)t6);
    t8 = (t7 == (unsigned char)6);
    t1 = t8;

LAB23:    if (t1 != 0)
        goto LAB19;

LAB20:    t2 = (t0 + 1192U);
    t3 = *((char **)t2);
    t1 = *((unsigned char *)t3);
    t4 = (t1 == (unsigned char)0);
    if (t4 != 0)
        goto LAB24;

LAB25:    t2 = (t0 + 3832);
    t3 = (t2 + 56U);
    t6 = *((char **)t3);
    t9 = (t6 + 56U);
    t10 = *((char **)t9);
    *((unsigned char *)t10) = (unsigned char)1;
    xsi_driver_first_trans_fast_port(t2);

LAB14:    goto LAB3;

LAB10:    t1 = (unsigned char)1;
    goto LAB12;

LAB13:    t2 = (t0 + 3832);
    t11 = (t2 + 56U);
    t12 = *((char **)t11);
    t18 = (t12 + 56U);
    t19 = *((char **)t18);
    *((unsigned char *)t19) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t2);
    goto LAB14;

LAB16:    t13 = (unsigned char)1;
    goto LAB18;

LAB19:    t2 = (t0 + 3832);
    t9 = (t2 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t2);
    goto LAB14;

LAB21:    t1 = (unsigned char)1;
    goto LAB23;

LAB24:    t2 = (t0 + 3832);
    t6 = (t2 + 56U);
    t9 = *((char **)t6);
    t10 = (t9 + 56U);
    t11 = *((char **)t10);
    *((unsigned char *)t11) = (unsigned char)0;
    xsi_driver_first_trans_fast_port(t2);
    goto LAB14;

LAB26:    t2 = (t0 + 3832);
    t6 = (t2 + 56U);
    t9 = *((char **)t6);
    t10 = (t9 + 56U);
    t11 = *((char **)t10);
    *((unsigned char *)t11) = (unsigned char)0;
    xsi_driver_first_trans_fast_port(t2);
    goto LAB3;

}


extern void unisim_a_3341709158_0094846637_init()
{
	static char *pe[] = {(void *)unisim_a_3341709158_0094846637_p_0,(void *)unisim_a_3341709158_0094846637_p_1};
	xsi_register_didat("unisim_a_3341709158_0094846637", "isim/intr_test_isim_beh.exe.sim/unisim/a_3341709158_0094846637.didat");
	xsi_register_executes(pe);
}
