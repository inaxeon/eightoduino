--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : main.vhf
-- /___/   /\     Timestamp : 09/30/2015 14:02:39
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family xc9500 -flat -suppress -vhdl N:/Electronics/eightoduino/PLD/eighto/main.vhf -w N:/Electronics/eightoduino/PLD/eighto/main.sch
--Design Name: main
--Device: xc9500
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesized and simulated, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity OBUFE_MXILINX_main is
   port ( E : in    std_logic; 
          I : in    std_logic; 
          O : out   std_logic);
end OBUFE_MXILINX_main;

architecture BEHAVIORAL of OBUFE_MXILINX_main is
   attribute BOX_TYPE   : string ;
   signal T : std_logic;
   component OBUFT
      port ( I : in    std_logic; 
             T : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of OBUFT : component is "BLACK_BOX";
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
begin
   I_36_10 : OBUFT
      port map (I=>I,
                T=>T,
                O=>O);
   
   I_36_12 : INV
      port map (I=>E,
                O=>T);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity IBUF16_MXILINX_main is
   port ( I : in    std_logic_vector (15 downto 0); 
          O : out   std_logic_vector (15 downto 0));
end IBUF16_MXILINX_main;

architecture BEHAVIORAL of IBUF16_MXILINX_main is
   attribute BOX_TYPE   : string ;
   component IBUF
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of IBUF : component is "BLACK_BOX";
   
begin
   I_36_30 : IBUF
      port map (I=>I(8),
                O=>O(8));
   
   I_36_31 : IBUF
      port map (I=>I(9),
                O=>O(9));
   
   I_36_32 : IBUF
      port map (I=>I(10),
                O=>O(10));
   
   I_36_33 : IBUF
      port map (I=>I(11),
                O=>O(11));
   
   I_36_34 : IBUF
      port map (I=>I(15),
                O=>O(15));
   
   I_36_35 : IBUF
      port map (I=>I(14),
                O=>O(14));
   
   I_36_36 : IBUF
      port map (I=>I(13),
                O=>O(13));
   
   I_36_37 : IBUF
      port map (I=>I(12),
                O=>O(12));
   
   I_36_38 : IBUF
      port map (I=>I(4),
                O=>O(4));
   
   I_36_39 : IBUF
      port map (I=>I(5),
                O=>O(5));
   
   I_36_40 : IBUF
      port map (I=>I(6),
                O=>O(6));
   
   I_36_41 : IBUF
      port map (I=>I(7),
                O=>O(7));
   
   I_36_42 : IBUF
      port map (I=>I(3),
                O=>O(3));
   
   I_36_43 : IBUF
      port map (I=>I(2),
                O=>O(2));
   
   I_36_44 : IBUF
      port map (I=>I(1),
                O=>O(1));
   
   I_36_45 : IBUF
      port map (I=>I(0),
                O=>O(0));
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity OBUFE16_MXILINX_main is
   port ( E : in    std_logic; 
          I : in    std_logic_vector (15 downto 0); 
          O : out   std_logic_vector (15 downto 0));
end OBUFE16_MXILINX_main;

architecture BEHAVIORAL of OBUFE16_MXILINX_main is
   attribute HU_SET     : string ;
   component OBUFE_MXILINX_main
      port ( E : in    std_logic; 
             I : in    std_logic; 
             O : out   std_logic);
   end component;
   
   attribute HU_SET of I_36_30 : label is "I_36_30_12";
   attribute HU_SET of I_36_31 : label is "I_36_31_11";
   attribute HU_SET of I_36_32 : label is "I_36_32_10";
   attribute HU_SET of I_36_33 : label is "I_36_33_9";
   attribute HU_SET of I_36_34 : label is "I_36_34_13";
   attribute HU_SET of I_36_35 : label is "I_36_35_14";
   attribute HU_SET of I_36_36 : label is "I_36_36_15";
   attribute HU_SET of I_36_37 : label is "I_36_37_8";
   attribute HU_SET of I_36_38 : label is "I_36_38_4";
   attribute HU_SET of I_36_39 : label is "I_36_39_7";
   attribute HU_SET of I_36_40 : label is "I_36_40_3";
   attribute HU_SET of I_36_41 : label is "I_36_41_2";
   attribute HU_SET of I_36_42 : label is "I_36_42_1";
   attribute HU_SET of I_36_43 : label is "I_36_43_0";
   attribute HU_SET of I_36_44 : label is "I_36_44_5";
   attribute HU_SET of I_36_45 : label is "I_36_45_6";
begin
   I_36_30 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(8),
                O=>O(8));
   
   I_36_31 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(9),
                O=>O(9));
   
   I_36_32 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(10),
                O=>O(10));
   
   I_36_33 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(11),
                O=>O(11));
   
   I_36_34 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(15),
                O=>O(15));
   
   I_36_35 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(14),
                O=>O(14));
   
   I_36_36 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(13),
                O=>O(13));
   
   I_36_37 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(12),
                O=>O(12));
   
   I_36_38 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(6),
                O=>O(6));
   
   I_36_39 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(7),
                O=>O(7));
   
   I_36_40 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(0),
                O=>O(0));
   
   I_36_41 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(1),
                O=>O(1));
   
   I_36_42 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(2),
                O=>O(2));
   
   I_36_43 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(3),
                O=>O(3));
   
   I_36_44 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(4),
                O=>O(4));
   
   I_36_45 : OBUFE_MXILINX_main
      port map (E=>E,
                I=>I(5),
                O=>O(5));
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity main is
   port ( A      : in    std_logic_vector (19 downto 16); 
          ALE    : in    std_logic; 
          BHE    : in    std_logic; 
          CPU10  : in    std_logic; 
          DEN    : in    std_logic; 
          EXTRD  : in    std_logic; 
          EXTWR  : in    std_logic; 
          IRQ1   : in    std_logic; 
          IRQ2   : in    std_logic; 
          IRQ3   : in    std_logic; 
          IRQ4   : in    std_logic; 
          MIO    : in    std_logic; 
          PGMRXD : in    std_logic; 
          RESET  : in    std_logic; 
          SYSCLK : in    std_logic; 
          TXA    : in    std_logic; 
          TXB    : in    std_logic; 
          TXC    : in    std_logic; 
          TXD    : in    std_logic; 
          AQ     : out   std_logic_vector (19 downto 0); 
          BHEQ   : out   std_logic; 
          CPUCLK : out   std_logic; 
          EEWP   : out   std_logic; 
          MIDCLK : out   std_logic; 
          MIDCS  : out   std_logic; 
          MRST   : out   std_logic; 
          NMI    : out   std_logic; 
          PORTD  : out   std_logic_vector (15 downto 0); 
          RAMCS  : out   std_logic; 
          ROMCS  : out   std_logic; 
          RXA    : out   std_logic; 
          RXB    : out   std_logic; 
          RXC    : out   std_logic; 
          RXD    : out   std_logic; 
          UCSA   : out   std_logic; 
          UCSB   : out   std_logic; 
          UCSC   : out   std_logic; 
          UCSD   : out   std_logic; 
          UHE    : out   std_logic; 
          ULE    : out   std_logic; 
          WDI    : out   std_logic; 
          AD_E   : inout std_logic_vector (15 downto 0); 
          PORTA  : inout std_logic_vector (15 downto 0); 
          PORTB  : inout std_logic_vector (5 downto 0); 
          PORTC  : inout std_logic_vector (15 downto 0));
end main;

architecture BEHAVIORAL of main is
   attribute BOX_TYPE   : string ;
   attribute HU_SET     : string ;
   attribute SLEW       : string ;
   signal AD           : std_logic_vector (15 downto 0);
   signal CONFIG_CS    : std_logic;
   signal EXTA_INT     : std_logic;
   signal EXTB_INT     : std_logic;
   signal PORTA_CS     : std_logic;
   signal PORTA_INT    : std_logic;
   signal PORTA_IOIN   : std_logic_vector (15 downto 0);
   signal PORTB_CS     : std_logic;
   signal PORTB_IOIN   : std_logic_vector (5 downto 0);
   signal PORTC_CS     : std_logic;
   signal PORTC_IOIN   : std_logic_vector (15 downto 0);
   signal PORTD_CS     : std_logic;
   signal RD_NOSYNC    : std_logic;
   signal RD_SYNC      : std_logic;
   signal STATUS_CS    : std_logic;
   signal STATUS_IOIN  : std_logic_vector (7 downto 0);
   signal TIMER_CLK    : std_logic;
   signal TIMER_CS     : std_logic;
   signal TIMER_INT    : std_logic;
   signal TIMER_RUN    : std_logic;
   signal TRISA_CS     : std_logic;
   signal TRISB_CS     : std_logic;
   signal TRISC_CS     : std_logic;
   signal UARTA_ENABLE : std_logic;
   signal UARTB_ENABLE : std_logic;
   signal UARTC_ENABLE : std_logic;
   signal UARTD_ENABLE : std_logic;
   signal WR_SYNC      : std_logic;
   signal XLXN_19      : std_logic;
   signal XLXN_20      : std_logic;
   signal XLXN_21      : std_logic;
   signal XLXN_22      : std_logic;
   signal XLXN_23      : std_logic;
   signal XLXN_24      : std_logic;
   signal XLXN_255     : std_logic_vector (15 downto 0);
   signal XLXN_444     : std_logic;
   signal XLXN_451     : std_logic;
   signal XLXN_452     : std_logic;
   signal XLXN_469     : std_logic;
   signal XLXN_720     : std_logic;
   signal XLXN_2395    : std_logic;
   signal XLXN_2401    : std_logic;
   signal XLXN_2461    : std_logic;
   signal XLXN_2464    : std_logic;
   signal XLXN_2860    : std_logic;
   signal XLXN_2861    : std_logic;
   signal XLXN_2862    : std_logic;
   signal XLXN_2863    : std_logic;
   signal XLXN_2864    : std_logic;
   signal XLXN_2865    : std_logic;
   signal XLXN_2866    : std_logic;
   signal XLXN_2867    : std_logic;
   signal XLXN_2872    : std_logic;
   signal XLXN_3045    : std_logic;
   signal XLXN_3053    : std_logic;
   signal XLXN_3125    : std_logic;
   signal CPUCLK_DUMMY : std_logic;
   signal AQ_DUMMY     : std_logic_vector (19 downto 0);
   signal BHEQ_DUMMY   : std_logic;
   component FD21
      port ( BHE  : in    std_logic; 
             AD   : in    std_logic_vector (15 downto 0); 
             A    : in    std_logic_vector (3 downto 0); 
             BHEQ : out   std_logic; 
             Q    : out   std_logic_vector (19 downto 0); 
             E    : in    std_logic);
   end component;
   
   component biu
      port ( clk       : in    std_logic; 
             rdin      : in    std_logic; 
             wrin      : in    std_logic; 
             rd_nosync : out   std_logic; 
             rd_sync   : out   std_logic; 
             wr_sync   : out   std_logic; 
             sync      : in    std_logic);
   end component;
   
   component cpuclock
      port ( clkin    : in    std_logic; 
             cpu10    : in    std_logic; 
             timerclk : out   std_logic; 
             cpuclk   : out   std_logic; 
             clkd2    : out   std_logic);
   end component;
   
   component configreg
      port ( reset      : in    std_logic; 
             wr         : in    std_logic; 
             configcs   : in    std_logic; 
             eewp       : out   std_logic; 
             rst        : out   std_logic; 
             tmrun      : out   std_logic; 
             uena       : out   std_logic; 
             uenb       : out   std_logic; 
             uenc       : out   std_logic; 
             uend       : out   std_logic; 
             uinta      : out   std_logic; 
             uintb      : out   std_logic; 
             uintc      : out   std_logic; 
             uintd      : out   std_logic; 
             tmint      : out   std_logic; 
             portainten : out   std_logic; 
             extinta    : out   std_logic; 
             extintb    : out   std_logic; 
             gie        : out   std_logic; 
             d          : in    std_logic_vector (15 downto 0));
   end component;
   
   component intc
      port ( reset      : in    std_logic; 
             wr         : in    std_logic; 
             statusen   : in    std_logic; 
             uena       : in    std_logic; 
             uenb       : in    std_logic; 
             uenc       : in    std_logic; 
             uend       : in    std_logic; 
             tmen       : in    std_logic; 
             portainten : in    std_logic; 
             extintaen  : in    std_logic; 
             extintben  : in    std_logic; 
             gie        : in    std_logic; 
             uinta      : in    std_logic; 
             uintb      : in    std_logic; 
             uintc      : in    std_logic; 
             uintd      : in    std_logic; 
             tmint      : in    std_logic; 
             portaint   : in    std_logic; 
             extinta    : in    std_logic; 
             extintb    : in    std_logic; 
             d          : in    std_logic_vector (15 downto 0); 
             irq        : out   std_logic; 
             status     : out   std_logic_vector (7 downto 0));
   end component;
   
   component ioport_6_umux
      port ( reset  : in    std_logic; 
             wr     : in    std_logic; 
             portcs : in    std_logic; 
             triscs : in    std_logic; 
             utxb   : in    std_logic; 
             utxc   : in    std_logic; 
             uenb   : in    std_logic; 
             uenc   : in    std_logic; 
             d      : in    std_logic_vector (15 downto 0); 
             ioport : inout std_logic_vector (5 downto 0); 
             urxb   : out   std_logic; 
             urxc   : out   std_logic; 
             ioin   : out   std_logic_vector (5 downto 0));
   end component;
   
   component ioport_16
      port ( ioport : inout std_logic_vector (15 downto 0); 
             wr     : in    std_logic; 
             portcs : in    std_logic; 
             triscs : in    std_logic; 
             d      : in    std_logic_vector (15 downto 0); 
             ioin   : out   std_logic_vector (15 downto 0); 
             reset  : in    std_logic);
   end component;
   
   component oport_16
      port ( oport  : out   std_logic_vector (15 downto 0); 
             wr     : in    std_logic; 
             portcs : in    std_logic; 
             d      : in    std_logic_vector (15 downto 0); 
             reset  : in    std_logic);
   end component;
   
   component portread
      port ( portaen  : in    std_logic; 
             portben  : in    std_logic; 
             portcen  : in    std_logic; 
             statusen : in    std_logic; 
             porta    : in    std_logic_vector (15 downto 0); 
             portb    : in    std_logic_vector (5 downto 0); 
             portc    : in    std_logic_vector (15 downto 0); 
             status   : in    std_logic_vector (7 downto 0); 
             portout  : out   std_logic_vector (15 downto 0));
   end component;
   
   component timer16
      port ( reset    : in    std_logic; 
             wr       : in    std_logic; 
             timercs  : in    std_logic; 
             run      : in    std_logic; 
             overflow : out   std_logic; 
             clk      : in    std_logic; 
             d        : in    std_logic_vector (15 downto 0));
   end component;
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
   component OBUFE16_MXILINX_main
      port ( E : in    std_logic; 
             I : in    std_logic_vector (15 downto 0); 
             O : out   std_logic_vector (15 downto 0));
   end component;
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component OBUFE_MXILINX_main
      port ( E : in    std_logic; 
             I : in    std_logic; 
             O : out   std_logic);
   end component;
   
   component OBUF
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute SLEW of OBUF : component is "SLOW";
   attribute BOX_TYPE of OBUF : component is "BLACK_BOX";
   
   component OR4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR4 : component is "BLACK_BOX";
   
   component ioport_16_umux
      port ( reset   : in    std_logic; 
             wr      : in    std_logic; 
             rd      : in    std_logic; 
             portcs  : in    std_logic; 
             triscs  : in    std_logic; 
             d       : in    std_logic_vector (15 downto 0); 
             ioport  : inout std_logic_vector (15 downto 0); 
             ioin    : out   std_logic_vector (15 downto 0); 
             extinta : out   std_logic; 
             extintb : out   std_logic; 
             portint : out   std_logic; 
             utxa    : in    std_logic; 
             utxd    : in    std_logic; 
             uena    : in    std_logic; 
             uend    : in    std_logic; 
             urxa    : out   std_logic; 
             urxd    : out   std_logic; 
             pgmrxd  : in    std_logic);
   end component;
   
   component adecode
      port ( MIO    : in    std_logic; 
             BHE    : in    std_logic; 
             ROMCS  : out   std_logic; 
             RAMCS  : out   std_logic; 
             UCSA   : out   std_logic; 
             UCSB   : out   std_logic; 
             UCSC   : out   std_logic; 
             UCSD   : out   std_logic; 
             STATUS : out   std_logic; 
             CFG    : out   std_logic; 
             PORTA  : out   std_logic; 
             PORTB  : out   std_logic; 
             PORTC  : out   std_logic; 
             PORTD  : out   std_logic; 
             TRISA  : out   std_logic; 
             TRISB  : out   std_logic; 
             TRISC  : out   std_logic; 
             MIDCS  : out   std_logic; 
             TIMER  : out   std_logic; 
             DEN    : in    std_logic; 
             UHE    : out   std_logic; 
             ULE    : out   std_logic; 
             A      : in    std_logic_vector (19 downto 0));
   end component;
   
   component IBUF16_MXILINX_main
      port ( I : in    std_logic_vector (15 downto 0); 
             O : out   std_logic_vector (15 downto 0));
   end component;
   
   attribute HU_SET of XLXI_246 : label is "XLXI_246_16";
   attribute HU_SET of XLXI_271 : label is "XLXI_271_18";
   attribute HU_SET of XLXI_335 : label is "XLXI_335_17";
begin
   AQ(19 downto 0) <= AQ_DUMMY(19 downto 0);
   BHEQ <= BHEQ_DUMMY;
   CPUCLK <= CPUCLK_DUMMY;
   addrdemux : FD21
      port map (A(3 downto 0)=>A(19 downto 16),
                AD(15 downto 0)=>AD(15 downto 0),
                BHE=>BHE,
                E=>ALE,
                BHEQ=>BHEQ_DUMMY,
                Q(19 downto 0)=>AQ_DUMMY(19 downto 0));
   
   businterface : biu
      port map (clk=>CPUCLK_DUMMY,
                rdin=>XLXN_2401,
                sync=>ALE,
                wrin=>XLXN_2395,
                rd_nosync=>RD_NOSYNC,
                rd_sync=>RD_SYNC,
                wr_sync=>WR_SYNC);
   
   clockgen : cpuclock
      port map (clkin=>SYSCLK,
                cpu10=>CPU10,
                clkd2=>MIDCLK,
                cpuclk=>CPUCLK_DUMMY,
                timerclk=>TIMER_CLK);
   
   config : configreg
      port map (configcs=>CONFIG_CS,
                d(15 downto 0)=>AD(15 downto 0),
                reset=>RESET,
                wr=>WR_SYNC,
                eewp=>EEWP,
                extinta=>XLXN_2862,
                extintb=>XLXN_2861,
                gie=>XLXN_2860,
                portainten=>XLXN_2863,
                rst=>XLXN_720,
                tmint=>XLXN_2864,
                tmrun=>TIMER_RUN,
                uena=>UARTA_ENABLE,
                uenb=>UARTB_ENABLE,
                uenc=>UARTC_ENABLE,
                uend=>UARTD_ENABLE,
                uinta=>XLXN_2872,
                uintb=>XLXN_2867,
                uintc=>XLXN_2866,
                uintd=>XLXN_2865);
   
   intr : intc
      port map (d(15 downto 0)=>AD(15 downto 0),
                extinta=>EXTA_INT,
                extintaen=>XLXN_2862,
                extintb=>EXTB_INT,
                extintben=>XLXN_2861,
                gie=>XLXN_2860,
                portaint=>PORTA_INT,
                portainten=>XLXN_2863,
                reset=>RESET,
                statusen=>STATUS_CS,
                tmen=>XLXN_2864,
                tmint=>TIMER_INT,
                uena=>XLXN_2872,
                uenb=>XLXN_2867,
                uenc=>XLXN_2866,
                uend=>XLXN_2865,
                uinta=>IRQ1,
                uintb=>IRQ2,
                uintc=>IRQ3,
                uintd=>IRQ4,
                wr=>WR_SYNC,
                irq=>NMI,
                status(7 downto 0)=>STATUS_IOIN(7 downto 0));
   
   ioportb : ioport_6_umux
      port map (d(15 downto 0)=>AD(15 downto 0),
                portcs=>PORTB_CS,
                reset=>RESET,
                triscs=>TRISB_CS,
                uenb=>UARTB_ENABLE,
                uenc=>UARTC_ENABLE,
                utxb=>TXB,
                utxc=>TXC,
                wr=>WR_SYNC,
                ioin(5 downto 0)=>PORTB_IOIN(5 downto 0),
                urxb=>RXB,
                urxc=>RXC,
                ioport(5 downto 0)=>PORTB(5 downto 0));
   
   ioportc : ioport_16
      port map (d(15 downto 0)=>AD(15 downto 0),
                portcs=>PORTC_CS,
                reset=>RESET,
                triscs=>TRISC_CS,
                wr=>WR_SYNC,
                ioin(15 downto 0)=>PORTC_IOIN(15 downto 0),
                ioport(15 downto 0)=>PORTC(15 downto 0));
   
   oportd : oport_16
      port map (d(15 downto 0)=>AD(15 downto 0),
                portcs=>PORTD_CS,
                reset=>RESET,
                wr=>WR_SYNC,
                oport(15 downto 0)=>PORTD(15 downto 0));
   
   portreader : portread
      port map (porta(15 downto 0)=>PORTA_IOIN(15 downto 0),
                portaen=>PORTA_CS,
                portb(5 downto 0)=>PORTB_IOIN(5 downto 0),
                portben=>PORTB_CS,
                portc(15 downto 0)=>PORTC_IOIN(15 downto 0),
                portcen=>PORTC_CS,
                status(7 downto 0)=>STATUS_IOIN(7 downto 0),
                statusen=>STATUS_CS,
                portout(15 downto 0)=>XLXN_255(15 downto 0));
   
   timer0 : timer16
      port map (clk=>TIMER_CLK,
                d(15 downto 0)=>AD(15 downto 0),
                reset=>RESET,
                run=>TIMER_RUN,
                timercs=>TIMER_CS,
                wr=>WR_SYNC,
                overflow=>TIMER_INT);
   
   XLXI_6 : INV
      port map (I=>XLXN_19,
                O=>ROMCS);
   
   XLXI_7 : INV
      port map (I=>XLXN_20,
                O=>RAMCS);
   
   XLXI_8 : INV
      port map (I=>XLXN_21,
                O=>UCSA);
   
   XLXI_9 : INV
      port map (I=>XLXN_22,
                O=>UCSB);
   
   XLXI_10 : INV
      port map (I=>XLXN_23,
                O=>UCSC);
   
   XLXI_11 : INV
      port map (I=>XLXN_24,
                O=>UCSD);
   
   XLXI_13 : INV
      port map (I=>EXTRD,
                O=>XLXN_2401);
   
   XLXI_246 : OBUFE16_MXILINX_main
      port map (E=>XLXN_3125,
                I(15 downto 0)=>XLXN_255(15 downto 0),
                O(15 downto 0)=>AD_E(15 downto 0));
   
   XLXI_260 : AND2
      port map (I0=>RD_NOSYNC,
                I1=>XLXN_2461,
                O=>XLXN_3125);
   
   XLXI_263 : INV
      port map (I=>XLXN_451,
                O=>UHE);
   
   XLXI_264 : INV
      port map (I=>XLXN_452,
                O=>ULE);
   
   XLXI_270 : INV
      port map (I=>XLXN_720,
                O=>XLXN_469);
   
   XLXI_271 : OBUFE_MXILINX_main
      port map (E=>XLXN_720,
                I=>XLXN_469,
                O=>MRST);
   
   XLXI_304 : OBUF
      port map (I=>ALE,
                O=>WDI);
   
   XLXI_306 : INV
      port map (I=>EXTWR,
                O=>XLXN_2395);
   
   XLXI_314 : INV
      port map (I=>BHEQ_DUMMY,
                O=>XLXN_444);
   
   XLXI_324 : OR4
      port map (I0=>PORTA_CS,
                I1=>PORTB_CS,
                I2=>PORTC_CS,
                I3=>STATUS_CS,
                O=>XLXN_2461);
   
   XLXI_325 : INV
      port map (I=>XLXN_2464,
                O=>MIDCS);
   
   XLXI_327 : ioport_16_umux
      port map (d(15 downto 0)=>AD(15 downto 0),
                pgmrxd=>PGMRXD,
                portcs=>PORTA_CS,
                rd=>RD_SYNC,
                reset=>RESET,
                triscs=>TRISA_CS,
                uena=>UARTA_ENABLE,
                uend=>UARTD_ENABLE,
                utxa=>TXA,
                utxd=>TXD,
                wr=>WR_SYNC,
                extinta=>XLXN_3045,
                extintb=>EXTB_INT,
                ioin(15 downto 0)=>PORTA_IOIN(15 downto 0),
                portint=>PORTA_INT,
                urxa=>RXA,
                urxd=>RXD,
                ioport(15 downto 0)=>PORTA(15 downto 0));
   
   XLXI_328 : INV
      port map (I=>XLXN_3045,
                O=>EXTA_INT);
   
   XLXI_329 : adecode
      port map (A(19 downto 0)=>AQ_DUMMY(19 downto 0),
                BHE=>XLXN_444,
                DEN=>XLXN_3053,
                MIO=>MIO,
                CFG=>CONFIG_CS,
                MIDCS=>XLXN_2464,
                PORTA=>PORTA_CS,
                PORTB=>PORTB_CS,
                PORTC=>PORTC_CS,
                PORTD=>PORTD_CS,
                RAMCS=>XLXN_20,
                ROMCS=>XLXN_19,
                STATUS=>STATUS_CS,
                TIMER=>TIMER_CS,
                TRISA=>TRISA_CS,
                TRISB=>TRISB_CS,
                TRISC=>TRISC_CS,
                UCSA=>XLXN_21,
                UCSB=>XLXN_22,
                UCSC=>XLXN_23,
                UCSD=>XLXN_24,
                UHE=>XLXN_451,
                ULE=>XLXN_452);
   
   XLXI_330 : INV
      port map (I=>DEN,
                O=>XLXN_3053);
   
   XLXI_335 : IBUF16_MXILINX_main
      port map (I(15 downto 0)=>AD_E(15 downto 0),
                O(15 downto 0)=>AD(15 downto 0));
   
end BEHAVIORAL;


