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

#include "xsi.h"

struct XSI_INFO xsi_info;

char *IEEE_P_2592010699;
char *STD_STANDARD;
char *IEEE_P_3499444699;
char *IEEE_P_3620187407;
char *IEEE_P_1242562249;
char *UNISIM_P_0947159679;
char *IEEE_P_2717149903;
char *STD_TEXTIO;


int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    ieee_p_2592010699_init();
    ieee_p_1242562249_init();
    unisim_p_0947159679_init();
    ieee_p_3499444699_init();
    ieee_p_3620187407_init();
    work_a_2311894725_3212880686_init();
    work_a_1315651414_3212880686_init();
    work_a_3660251246_3212880686_init();
    work_a_3839246751_3212880686_init();
    work_a_3078712824_3212880686_init();
    work_a_3616980496_3212880686_init();
    work_a_3004498275_3212880686_init();
    work_a_2060963391_3212880686_init();
    work_a_2372741284_3212880686_init();
    unisim_a_3055263662_1392679692_init();
    std_textio_init();
    ieee_p_2717149903_init();
    unisim_a_1525108159_2393828108_init();
    work_a_1601170373_3212880686_init();
    unisim_a_3341709158_0094846637_init();
    work_a_0690644276_3212880686_init();
    work_a_0070216396_3212880686_init();
    unisim_a_2661327437_0605893366_init();
    unisim_a_2952178788_1492584465_init();
    work_a_3584125769_3212880686_init();
    unisim_a_1717296735_4086321779_init();
    work_a_2232473996_3212880686_init();
    work_a_1382780561_3212880686_init();
    unisim_a_2472025866_3046367013_init();
    work_a_1774854872_3212880686_init();
    work_a_2226623189_3212880686_init();


    xsi_register_tops("work_a_2226623189_3212880686");

    IEEE_P_2592010699 = xsi_get_engine_memory("ieee_p_2592010699");
    xsi_register_ieee_std_logic_1164(IEEE_P_2592010699);
    STD_STANDARD = xsi_get_engine_memory("std_standard");
    IEEE_P_3499444699 = xsi_get_engine_memory("ieee_p_3499444699");
    IEEE_P_3620187407 = xsi_get_engine_memory("ieee_p_3620187407");
    IEEE_P_1242562249 = xsi_get_engine_memory("ieee_p_1242562249");
    UNISIM_P_0947159679 = xsi_get_engine_memory("unisim_p_0947159679");
    IEEE_P_2717149903 = xsi_get_engine_memory("ieee_p_2717149903");
    STD_TEXTIO = xsi_get_engine_memory("std_textio");

    return xsi_run_simulation(argc, argv);

}
