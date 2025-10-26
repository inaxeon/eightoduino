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
static const char *ng0 = "//S8FS01/Matt/Electronics/eightoduino/PLD/eighto/ioport_16.vhd";
extern char *IEEE_P_2592010699;

unsigned char ieee_p_2592010699_sub_1605435078_503743352(char *, unsigned char , unsigned char );
unsigned char ieee_p_2592010699_sub_1744673427_503743352(char *, char *, unsigned int , unsigned int );


static void work_a_3616980496_3212880686_p_0(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    unsigned char t5;
    unsigned char t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;

LAB0:    xsi_set_current_line(49, ng0);

LAB3:    t1 = (t0 + 1192U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 1512U);
    t4 = *((char **)t1);
    t5 = *((unsigned char *)t4);
    t6 = ieee_p_2592010699_sub_1605435078_503743352(IEEE_P_2592010699, t3, t5);
    t1 = (t0 + 5512);
    t7 = (t1 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    *((unsigned char *)t10) = t6;
    xsi_driver_first_trans_fast(t1);

LAB2:    t11 = (t0 + 5352);
    *((int *)t11) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_3616980496_3212880686_p_1(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    unsigned char t5;
    unsigned char t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;

LAB0:    xsi_set_current_line(50, ng0);

LAB3:    t1 = (t0 + 1192U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 1352U);
    t4 = *((char **)t1);
    t5 = *((unsigned char *)t4);
    t6 = ieee_p_2592010699_sub_1605435078_503743352(IEEE_P_2592010699, t3, t5);
    t1 = (t0 + 5576);
    t7 = (t1 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    *((unsigned char *)t10) = t6;
    xsi_driver_first_trans_fast(t1);

LAB2:    t11 = (t0 + 5368);
    *((int *)t11) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_3616980496_3212880686_p_2(char *t0)
{
    char *t1;
    char *t2;
    unsigned int t3;
    unsigned int t4;
    unsigned int t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;

LAB0:    xsi_set_current_line(52, ng0);

LAB3:    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = (15 - 15);
    t4 = (t3 * 1U);
    t5 = (0 + t4);
    t1 = (t2 + t5);
    t6 = (t0 + 5640);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 16U);
    xsi_driver_first_trans_delta(t6, 0U, 16U, 0LL);

LAB2:    t11 = (t0 + 5384);
    *((int *)t11) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_3616980496_3212880686_p_3(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;

LAB0:    xsi_set_current_line(56, ng0);
    t1 = (t0 + 1032U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 2432U);
    t3 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 5400);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(57, ng0);
    t1 = xsi_get_transient_memory(16U);
    memset(t1, 0, 16U);
    t5 = t1;
    memset(t5, (unsigned char)3, 16U);
    t6 = (t0 + 5704);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 16U);
    xsi_driver_first_trans_fast(t6);
    goto LAB3;

LAB5:    xsi_set_current_line(59, ng0);
    t2 = (t0 + 1672U);
    t5 = *((char **)t2);
    t2 = (t0 + 5704);
    t6 = (t2 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t5, 16U);
    xsi_driver_first_trans_fast(t2);
    goto LAB3;

}

static void work_a_3616980496_3212880686_p_4(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;

LAB0:    xsi_set_current_line(65, ng0);
    t1 = (t0 + 1032U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 2592U);
    t3 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 5416);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(66, ng0);
    t1 = xsi_get_transient_memory(16U);
    memset(t1, 0, 16U);
    t5 = t1;
    memset(t5, (unsigned char)2, 16U);
    t6 = (t0 + 5768);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 16U);
    xsi_driver_first_trans_fast(t6);
    goto LAB3;

LAB5:    xsi_set_current_line(68, ng0);
    t2 = (t0 + 1672U);
    t5 = *((char **)t2);
    t2 = (t0 + 5768);
    t6 = (t2 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t5, 16U);
    xsi_driver_first_trans_fast(t2);
    goto LAB3;

}

static void work_a_3616980496_3212880686_p_5(char *t0)
{
    char *t1;
    char *t2;
    int t3;
    int t4;
    char *t5;
    char *t6;
    int t7;
    int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned char t13;
    unsigned char t14;
    char *t15;
    char *t16;
    int t17;
    int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    unsigned char t23;
    char *t24;
    int t25;
    int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;
    char *t34;

LAB0:    xsi_set_current_line(74, ng0);
    t1 = (t0 + 8558);
    *((int *)t1) = 15;
    t2 = (t0 + 8562);
    *((int *)t2) = 0;
    t3 = 15;
    t4 = 0;

LAB2:    if (t3 >= t4)
        goto LAB3;

LAB5:    t1 = (t0 + 5432);
    *((int *)t1) = 1;

LAB1:    return;
LAB3:    xsi_set_current_line(75, ng0);
    t5 = (t0 + 2152U);
    t6 = *((char **)t5);
    t5 = (t0 + 8558);
    t7 = *((int *)t5);
    t8 = (t7 - 15);
    t9 = (t8 * -1);
    xsi_vhdl_check_range_of_index(15, 0, -1, *((int *)t5));
    t10 = (1U * t9);
    t11 = (0 + t10);
    t12 = (t6 + t11);
    t13 = *((unsigned char *)t12);
    t14 = (t13 == (unsigned char)2);
    if (t14 != 0)
        goto LAB6;

LAB8:    xsi_set_current_line(78, ng0);
    t1 = (t0 + 8558);
    t7 = *((int *)t1);
    t8 = (t7 - 15);
    t9 = (t8 * -1);
    t10 = (1 * t9);
    t11 = (0U + t10);
    t2 = (t0 + 5832);
    t5 = (t2 + 56U);
    t6 = *((char **)t5);
    t12 = (t6 + 56U);
    t15 = *((char **)t12);
    *((unsigned char *)t15) = (unsigned char)4;
    xsi_driver_first_trans_delta(t2, t11, 1, 0LL);

LAB7:
LAB4:    t1 = (t0 + 8558);
    t3 = *((int *)t1);
    t2 = (t0 + 8562);
    t4 = *((int *)t2);
    if (t3 == t4)
        goto LAB5;

LAB9:    t7 = (t3 + -1);
    t3 = t7;
    t5 = (t0 + 8558);
    *((int *)t5) = t3;
    goto LAB2;

LAB6:    xsi_set_current_line(76, ng0);
    t15 = (t0 + 2312U);
    t16 = *((char **)t15);
    t15 = (t0 + 8558);
    t17 = *((int *)t15);
    t18 = (t17 - 15);
    t19 = (t18 * -1);
    xsi_vhdl_check_range_of_index(15, 0, -1, *((int *)t15));
    t20 = (1U * t19);
    t21 = (0 + t20);
    t22 = (t16 + t21);
    t23 = *((unsigned char *)t22);
    t24 = (t0 + 8558);
    t25 = *((int *)t24);
    t26 = (t25 - 15);
    t27 = (t26 * -1);
    t28 = (1 * t27);
    t29 = (0U + t28);
    t30 = (t0 + 5832);
    t31 = (t30 + 56U);
    t32 = *((char **)t31);
    t33 = (t32 + 56U);
    t34 = *((char **)t33);
    *((unsigned char *)t34) = t23;
    xsi_driver_first_trans_delta(t30, t29, 1, 0LL);
    goto LAB7;

}


extern void work_a_3616980496_3212880686_init()
{
	static char *pe[] = {(void *)work_a_3616980496_3212880686_p_0,(void *)work_a_3616980496_3212880686_p_1,(void *)work_a_3616980496_3212880686_p_2,(void *)work_a_3616980496_3212880686_p_3,(void *)work_a_3616980496_3212880686_p_4,(void *)work_a_3616980496_3212880686_p_5};
	xsi_register_didat("work_a_3616980496_3212880686", "isim/intr_test_isim_beh.exe.sim/work/a_3616980496_3212880686.didat");
	xsi_register_executes(pe);
}
