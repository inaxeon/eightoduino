--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : main.vhf
-- /___/   /\     Timestamp : 01/13/2017 13:45:23
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family xc9500 -flat -suppress -vhdl N:/Electronics/eightoduino_v3/8OD.1_2_PLD_LBUS/eighto/main.vhf -w N:/Electronics/eightoduino_v3/8OD.1_2_PLD_LBUS/eighto/main.sch
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
   port ( A         : in    std_logic_vector (19 downto 16); 
          ALE       : in    std_logic; 
          BHE       : in    std_logic; 
          CPU10     : in    std_logic; 
          DEN       : in    std_logic; 
          DTR       : in    std_logic; 
          EXTRD     : in    std_logic; 
          EXTWR     : in    std_logic; 
          IRQ1      : in    std_logic; 
          IRQ2      : in    std_logic; 
          IRQ3      : in    std_logic; 
          IRQ4      : in    std_logic; 
          LBUS_IRDY : in    std_logic; 
          MIO       : in    std_logic; 
          PGMRXD    : in    std_logic; 
          RESET     : in    std_logic; 
          SYSCLK    : in    std_logic; 
          TXA       : in    std_logic; 
          TXB       : in    std_logic; 
          TXC       : in    std_logic; 
          TXD       : in    std_logic; 
          AQ        : out   std_logic_vector (18 downto 0); 
          BHEQ      : out   std_logic; 
          CPUCLK    : out   std_logic; 
          EEWP      : out   std_logic; 
          I2CCS     : out   std_logic; 
          LBUS_A    : out   std_logic_vector (19 downto 8); 
          LBUS_ALE  : out   std_logic; 
          LBUS_CLK  : out   std_logic; 
          LBUS_DEN  : out   std_logic; 
          LBUS_DTR  : out   std_logic; 
          LBUS_MIO  : out   std_logic; 
          LBUS_RD   : out   std_logic; 
          LBUS_RST  : out   std_logic; 
          LBUS_WR   : out   std_logic; 
          MIDCLK    : out   std_logic; 
          MIDCS     : out   std_logic; 
          MRST      : out   std_logic; 
          NMI       : out   std_logic; 
          RAMCS     : out   std_logic; 
          RDY       : out   std_logic; 
          ROMCS     : out   std_logic; 
          RXA       : out   std_logic; 
          RXB       : out   std_logic; 
          RXC       : out   std_logic; 
          RXD       : out   std_logic; 
          UCSA      : out   std_logic; 
          UCSB      : out   std_logic; 
          UCSC      : out   std_logic; 
          UCSD      : out   std_logic; 
          UHE       : out   std_logic; 
          ULE       : out   std_logic; 
          WDI       : out   std_logic; 
          AD_E      : inout std_logic_vector (15 downto 0); 
          LBUS_AD   : inout std_logic_vector (7 downto 0); 
          PORTA     : inout std_logic_vector (15 downto 0); 
          PORTB     : inout std_logic_vector (5 downto 0));
end main;

architecture BEHAVIORAL of main is
   attribute BOX_TYPE   : string ;
   attribute HU_SET     : string ;
   attribute SLEW       : string ;
   signal AD            : std_logic_vector (15 downto 0);
   signal AL            : std_logic_vector (19 downto 0);
   signal CONFIG_CS     : std_logic;
   signal DENA          : std_logic;
   signal EIGHTBIT_IOIN : std_logic_vector (7 downto 0);
   signal EXTA_INT      : std_logic;
   signal EXTB_INT      : std_logic;
   signal LBUS_CS       : std_logic;
   signal LHE           : std_logic;
   signal LLE           : std_logic;
   signal PCLK          : std_logic;
   signal PORTA_CS      : std_logic;
   signal PORTA_INT     : std_logic;
   signal PORTA_IOIN    : std_logic_vector (15 downto 0);
   signal PORTB_CS      : std_logic;
   signal PORTB_IOIN    : std_logic_vector (5 downto 0);
   signal RD_NOSYNC     : std_logic;
   signal RD_SYNC       : std_logic;
   signal STATUS_CS     : std_logic;
   signal STATUS_IOIN   : std_logic_vector (7 downto 0);
   signal TIMER_CLK     : std_logic;
   signal TIMER_CS      : std_logic;
   signal TIMER_INT     : std_logic;
   signal TIMER_RUN     : std_logic;
   signal TRISA_CS      : std_logic;
   signal TRISB_CS      : std_logic;
   signal UARTA_ENABLE  : std_logic;
   signal UARTB_ENABLE  : std_logic;
   signal UARTC_ENABLE  : std_logic;
   signal UARTD_ENABLE  : std_logic;
   signal WR_NOSYNC     : std_logic;
   signal WR_SYNC       : std_logic;
   signal XLXN_19       : std_logic;
   signal XLXN_20       : std_logic;
   signal XLXN_21       : std_logic;
   signal XLXN_22       : std_logic;
   signal XLXN_23       : std_logic;
   signal XLXN_24       : std_logic;
   signal XLXN_444      : std_logic;
   signal XLXN_451      : std_logic;
   signal XLXN_469      : std_logic;
   signal XLXN_2395     : std_logic;
   signal XLXN_2401     : std_logic;
   signal XLXN_2464     : std_logic;
   signal XLXN_2860     : std_logic;
   signal XLXN_2861     : std_logic;
   signal XLXN_2862     : std_logic;
   signal XLXN_2863     : std_logic;
   signal XLXN_2864     : std_logic;
   signal XLXN_2865     : std_logic;
   signal XLXN_2866     : std_logic;
   signal XLXN_2867     : std_logic;
   signal XLXN_2872     : std_logic;
   signal XLXN_3045     : std_logic;
   signal XLXN_3146     : std_logic;
   signal XLXN_3213     : std_logic_vector (15 downto 0);
   signal XLXN_3225     : std_logic;
   signal XLXN_3226     : std_logic;
   signal XLXN_3237     : std_logic;
   signal XLXN_3239     : std_logic;
   signal XLXN_3248     : std_logic;
   signal XLXN_3275     : std_logic;
   signal XLXN_3285     : std_logic;
   signal XLXN_3286     : std_logic;
   signal XLXN_3288     : std_logic;
   signal XLXN_3289     : std_logic;
   signal XLXN_3297     : std_logic;
   signal XLXN_3298     : std_logic;
   signal CPUCLK_DUMMY  : std_logic;
   signal BHEQ_DUMMY    : std_logic;
   component FD21
      port ( BHE  : in    std_logic; 
             AD   : in    std_logic_vector (15 downto 0); 
             A    : in    std_logic_vector (3 downto 0); 
             BHEQ : out   std_logic; 
             Q    : out   std_logic_vector (19 downto 0); 
             E    : in    std_logic);
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
   
   component portread
      port ( portaen    : in    std_logic; 
             portben    : in    std_logic; 
             statusen   : in    std_logic; 
             porta      : in    std_logic_vector (15 downto 0); 
             portb      : in    std_logic_vector (5 downto 0); 
             status     : in    std_logic_vector (7 downto 0); 
             eightbit   : in    std_logic_vector (7 downto 0); 
             eightbiten : in    std_logic; 
             lle        : in    std_logic; 
             portout    : out   std_logic_vector (15 downto 0));
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
             DEN    : in    std_logic; 
             A      : in    std_logic_vector (19 downto 0); 
             ROMCS  : out   std_logic; 
             RAMCS  : out   std_logic; 
             UCSA   : out   std_logic; 
             UCSB   : out   std_logic; 
             UCSC   : out   std_logic; 
             UCSD   : out   std_logic; 
             STATUS : out   std_logic; 
             CFG    : out   std_logic; 
             MIDCS  : out   std_logic; 
             TIMER  : out   std_logic; 
             UHE    : out   std_logic; 
             ULE    : out   std_logic; 
             LHE    : out   std_logic; 
             LLE    : out   std_logic; 
             LBUSCS : out   std_logic; 
             I2CCS  : out   std_logic; 
             PORTA  : out   std_logic; 
             PORTB  : out   std_logic; 
             TRISA  : out   std_logic; 
             TRISB  : out   std_logic);
   end component;
   
   component IBUF16_MXILINX_main
      port ( I : in    std_logic_vector (15 downto 0); 
             O : out   std_logic_vector (15 downto 0));
   end component;
   
   component biu
      port ( sync      : in    std_logic; 
             clk       : in    std_logic; 
             rdin      : in    std_logic; 
             wrin      : in    std_logic; 
             irdy      : in    std_logic; 
             rd_nosync : out   std_logic; 
             wr_nosync : out   std_logic; 
             rd_sync   : out   std_logic; 
             wr_sync   : out   std_logic; 
             rdy       : out   std_logic);
   end component;
   
   component OR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR3 : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component OBUF
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute SLEW of OBUF : component is "SLOW";
   attribute BOX_TYPE of OBUF : component is "BLACK_BOX";
   
   component asplit
      port ( al  : in    std_logic_vector (19 downto 0); 
             aq  : out   std_logic_vector (18 downto 0); 
             a19 : out   std_logic);
   end component;
   
   component cpuclock
      port ( clkin    : in    std_logic; 
             cpu10    : in    std_logic; 
             timerclk : out   std_logic; 
             cpuclk   : out   std_logic; 
             clkd2    : out   std_logic; 
             pclk     : out   std_logic);
   end component;
   
   component lbus
      port ( cpuclk   : in    std_logic; 
             ale      : in    std_logic; 
             reset    : in    std_logic; 
             wr       : in    std_logic; 
             rd       : in    std_logic; 
             mio      : in    std_logic; 
             dtr      : in    std_logic; 
             den      : in    std_logic; 
             lle      : in    std_logic; 
             lbuscs   : in    std_logic; 
             a        : in    std_logic_vector (19 downto 0); 
             d        : in    std_logic_vector (15 downto 0); 
             ioin     : out   std_logic_vector (7 downto 0); 
             pclk     : in    std_logic; 
             lbus_ad  : inout std_logic_vector (7 downto 0); 
             lbus_mio : out   std_logic; 
             lbus_dtr : out   std_logic; 
             lbus_den : out   std_logic; 
             lbus_rd  : out   std_logic; 
             lbus_wr  : out   std_logic; 
             lbus_rst : out   std_logic; 
             lbus_ale : out   std_logic; 
             lbus_a   : out   std_logic_vector (19 downto 8));
   end component;
   
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
   attribute HU_SET of XLXI_246 : label is "XLXI_246_17";
   attribute HU_SET of XLXI_271 : label is "XLXI_271_16";
   attribute HU_SET of XLXI_335 : label is "XLXI_335_18";
begin
   BHEQ <= BHEQ_DUMMY;
   CPUCLK <= CPUCLK_DUMMY;
   addrdemux : FD21
      port map (A(3 downto 0)=>A(19 downto 16),
                AD(15 downto 0)=>AD(15 downto 0),
                BHE=>BHE,
                E=>ALE,
                BHEQ=>BHEQ_DUMMY,
                Q(19 downto 0)=>AL(19 downto 0));
   
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
                rst=>XLXN_3298,
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
   
   portreader : portread
      port map (eightbit(7 downto 0)=>EIGHTBIT_IOIN(7 downto 0),
                eightbiten=>LBUS_CS,
                lle=>LLE,
                porta(15 downto 0)=>PORTA_IOIN(15 downto 0),
                portaen=>PORTA_CS,
                portb(5 downto 0)=>PORTB_IOIN(5 downto 0),
                portben=>PORTB_CS,
                status(7 downto 0)=>STATUS_IOIN(7 downto 0),
                statusen=>STATUS_CS,
                portout(15 downto 0)=>XLXN_3213(15 downto 0));
   
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
      port map (E=>XLXN_3226,
                I(15 downto 0)=>XLXN_3213(15 downto 0),
                O(15 downto 0)=>AD_E(15 downto 0));
   
   XLXI_260 : AND2
      port map (I0=>RD_NOSYNC,
                I1=>XLXN_3225,
                O=>XLXN_3237);
   
   XLXI_263 : INV
      port map (I=>XLXN_451,
                O=>UHE);
   
   XLXI_264 : INV
      port map (I=>XLXN_3146,
                O=>ULE);
   
   XLXI_271 : OBUFE_MXILINX_main
      port map (E=>XLXN_3298,
                I=>XLXN_469,
                O=>MRST);
   
   XLXI_306 : INV
      port map (I=>EXTWR,
                O=>XLXN_2395);
   
   XLXI_314 : INV
      port map (I=>BHEQ_DUMMY,
                O=>XLXN_444);
   
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
      port map (A(19 downto 0)=>AL(19 downto 0),
                BHE=>XLXN_444,
                DEN=>DENA,
                MIO=>MIO,
                CFG=>CONFIG_CS,
                I2CCS=>XLXN_3285,
                LBUSCS=>LBUS_CS,
                LHE=>LHE,
                LLE=>LLE,
                MIDCS=>XLXN_2464,
                PORTA=>PORTA_CS,
                PORTB=>PORTB_CS,
                RAMCS=>XLXN_20,
                ROMCS=>XLXN_19,
                STATUS=>STATUS_CS,
                TIMER=>TIMER_CS,
                TRISA=>TRISA_CS,
                TRISB=>TRISB_CS,
                UCSA=>XLXN_21,
                UCSB=>XLXN_22,
                UCSC=>XLXN_23,
                UCSD=>XLXN_24,
                UHE=>XLXN_451,
                ULE=>XLXN_3146);
   
   XLXI_330 : INV
      port map (I=>DEN,
                O=>DENA);
   
   XLXI_335 : IBUF16_MXILINX_main
      port map (I(15 downto 0)=>AD_E(15 downto 0),
                O(15 downto 0)=>AD(15 downto 0));
   
   XLXI_357 : biu
      port map (clk=>CPUCLK_DUMMY,
                irdy=>LBUS_IRDY,
                rdin=>XLXN_2401,
                sync=>ALE,
                wrin=>XLXN_2395,
                rdy=>RDY,
                rd_nosync=>RD_NOSYNC,
                rd_sync=>RD_SYNC,
                wr_nosync=>WR_NOSYNC,
                wr_sync=>WR_SYNC);
   
   XLXI_360 : OR3
      port map (I0=>PORTA_CS,
                I1=>PORTB_CS,
                I2=>STATUS_CS,
                O=>XLXN_3225);
   
   XLXI_361 : OR2
      port map (I0=>XLXN_3275,
                I1=>XLXN_3237,
                O=>XLXN_3226);
   
   XLXI_366 : AND2
      port map (I0=>XLXN_3239,
                I1=>XLXN_3248,
                O=>XLXN_3275);
   
   XLXI_367 : INV
      port map (I=>DTR,
                O=>XLXN_3239);
   
   XLXI_370 : OR2
      port map (I0=>LHE,
                I1=>LLE,
                O=>XLXN_3248);
   
   XLXI_371 : INV
      port map (I=>XLXN_3285,
                O=>I2CCS);
   
   XLXI_373 : INV
      port map (I=>XLXN_3286,
                O=>LBUS_RD);
   
   XLXI_374 : INV
      port map (I=>XLXN_3288,
                O=>LBUS_WR);
   
   XLXI_375 : INV
      port map (I=>XLXN_3289,
                O=>LBUS_DEN);
   
   XLXI_376 : INV
      port map (I=>XLXN_3297,
                O=>LBUS_RST);
   
   XLXI_381 : OBUF
      port map (I=>ALE,
                O=>WDI);
   
   XLXI_384 : asplit
      port map (al(19 downto 0)=>AL(19 downto 0),
                aq(18 downto 0)=>AQ(18 downto 0),
                a19=>open);
   
   XLXI_386 : cpuclock
      port map (clkin=>SYSCLK,
                cpu10=>CPU10,
                clkd2=>MIDCLK,
                cpuclk=>CPUCLK_DUMMY,
                pclk=>PCLK,
                timerclk=>TIMER_CLK);
   
   XLXI_388 : OBUF
      port map (I=>PCLK,
                O=>LBUS_CLK);
   
   XLXI_389 : lbus
      port map (a(19 downto 0)=>AL(19 downto 0),
                ale=>ALE,
                cpuclk=>CPUCLK_DUMMY,
                d(15 downto 0)=>AD(15 downto 0),
                den=>DENA,
                dtr=>DTR,
                lbuscs=>LBUS_CS,
                lle=>LLE,
                mio=>MIO,
                pclk=>PCLK,
                rd=>RD_NOSYNC,
                reset=>RESET,
                wr=>WR_NOSYNC,
                ioin(7 downto 0)=>EIGHTBIT_IOIN(7 downto 0),
                lbus_a(19 downto 8)=>LBUS_A(19 downto 8),
                lbus_ale=>LBUS_ALE,
                lbus_den=>XLXN_3289,
                lbus_dtr=>LBUS_DTR,
                lbus_mio=>LBUS_MIO,
                lbus_rd=>XLXN_3286,
                lbus_rst=>XLXN_3297,
                lbus_wr=>XLXN_3288,
                lbus_ad(7 downto 0)=>LBUS_AD(7 downto 0));
   
   XLXI_390 : GND
      port map (G=>XLXN_469);
   
end BEHAVIORAL;


