--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : ioport.vhf
-- /___/   /\     Timestamp : 08/04/2014 11:44:03
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family xc9500 -flat -suppress -vhdl C:/Projects/8086/PLD/eighto/ioport.vhf -w C:/Projects/8086/PLD/eighto/ioport.sch
--Design Name: ioport
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

entity IBUF16_MXILINX_ioport is
   port ( I : in    std_logic_vector (15 downto 0); 
          O : out   std_logic_vector (15 downto 0));
end IBUF16_MXILINX_ioport;

architecture BEHAVIORAL of IBUF16_MXILINX_ioport is
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

entity OBUFE_MXILINX_ioport is
   port ( E : in    std_logic; 
          I : in    std_logic; 
          O : out   std_logic);
end OBUFE_MXILINX_ioport;

architecture BEHAVIORAL of OBUFE_MXILINX_ioport is
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

entity LD16_MXILINX_ioport is
   port ( D : in    std_logic_vector (15 downto 0); 
          G : in    std_logic; 
          Q : out   std_logic_vector (15 downto 0));
end LD16_MXILINX_ioport;

architecture BEHAVIORAL of LD16_MXILINX_ioport is
   attribute BOX_TYPE   : string ;
   component LD
      generic( INIT : bit :=  '0');
      port ( D : in    std_logic; 
             G : in    std_logic; 
             Q : out   std_logic);
   end component;
   attribute BOX_TYPE of LD : component is "BLACK_BOX";
   
begin
   Q0 : LD
      port map (D=>D(0),
                G=>G,
                Q=>Q(0));
   
   Q1 : LD
      port map (D=>D(1),
                G=>G,
                Q=>Q(1));
   
   Q2 : LD
      port map (D=>D(2),
                G=>G,
                Q=>Q(2));
   
   Q3 : LD
      port map (D=>D(3),
                G=>G,
                Q=>Q(3));
   
   Q4 : LD
      port map (D=>D(4),
                G=>G,
                Q=>Q(4));
   
   Q5 : LD
      port map (D=>D(5),
                G=>G,
                Q=>Q(5));
   
   Q6 : LD
      port map (D=>D(6),
                G=>G,
                Q=>Q(6));
   
   Q7 : LD
      port map (D=>D(7),
                G=>G,
                Q=>Q(7));
   
   Q8 : LD
      port map (D=>D(8),
                G=>G,
                Q=>Q(8));
   
   Q9 : LD
      port map (D=>D(9),
                G=>G,
                Q=>Q(9));
   
   Q10 : LD
      port map (D=>D(10),
                G=>G,
                Q=>Q(10));
   
   Q11 : LD
      port map (D=>D(11),
                G=>G,
                Q=>Q(11));
   
   Q12 : LD
      port map (D=>D(12),
                G=>G,
                Q=>Q(12));
   
   Q13 : LD
      port map (D=>D(13),
                G=>G,
                Q=>Q(13));
   
   Q14 : LD
      port map (D=>D(14),
                G=>G,
                Q=>Q(14));
   
   Q15 : LD
      port map (D=>D(15),
                G=>G,
                Q=>Q(15));
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity ioport is
   port ( D      : in    std_logic_vector (15 downto 0); 
          PORTCS : in    std_logic; 
          TRISCS : in    std_logic; 
          WR     : in    std_logic; 
          IOIN   : out   std_logic_vector (15 downto 0); 
          IOPORT : inout std_logic_vector (0 to 15));
end ioport;

architecture BEHAVIORAL of ioport is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal PORTAQ   : std_logic_vector (15 downto 0);
   signal TRISAQ   : std_logic_vector (15 downto 0);
   signal XLXN_171 : std_logic;
   signal XLXN_173 : std_logic;
   component OBUFE_MXILINX_ioport
      port ( E : in    std_logic; 
             I : in    std_logic; 
             O : out   std_logic);
   end component;
   
   component LD16_MXILINX_ioport
      port ( D : in    std_logic_vector (15 downto 0); 
             G : in    std_logic; 
             Q : out   std_logic_vector (15 downto 0));
   end component;
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component IBUF16_MXILINX_ioport
      port ( I : in    std_logic_vector (15 downto 0); 
             O : out   std_logic_vector (15 downto 0));
   end component;
   
   attribute HU_SET of XLXI_3 : label is "XLXI_3_17";
   attribute HU_SET of XLXI_4 : label is "XLXI_4_16";
   attribute HU_SET of XLXI_5 : label is "XLXI_5_15";
   attribute HU_SET of XLXI_6 : label is "XLXI_6_14";
   attribute HU_SET of XLXI_7 : label is "XLXI_7_13";
   attribute HU_SET of XLXI_8 : label is "XLXI_8_12";
   attribute HU_SET of XLXI_9 : label is "XLXI_9_11";
   attribute HU_SET of XLXI_10 : label is "XLXI_10_10";
   attribute HU_SET of XLXI_11 : label is "XLXI_11_9";
   attribute HU_SET of XLXI_12 : label is "XLXI_12_8";
   attribute HU_SET of XLXI_13 : label is "XLXI_13_7";
   attribute HU_SET of XLXI_15 : label is "XLXI_15_6";
   attribute HU_SET of XLXI_16 : label is "XLXI_16_5";
   attribute HU_SET of XLXI_17 : label is "XLXI_17_4";
   attribute HU_SET of XLXI_18 : label is "XLXI_18_3";
   attribute HU_SET of XLXI_40 : label is "XLXI_40_1";
   attribute HU_SET of XLXI_41 : label is "XLXI_41_0";
   attribute HU_SET of XLXI_194 : label is "XLXI_194_2";
   attribute HU_SET of XLXI_240 : label is "XLXI_240_18";
begin
   XLXI_3 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(14),
                I=>PORTAQ(14),
                O=>IOPORT(14));
   
   XLXI_4 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(13),
                I=>PORTAQ(13),
                O=>IOPORT(13));
   
   XLXI_5 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(12),
                I=>PORTAQ(12),
                O=>IOPORT(12));
   
   XLXI_6 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(11),
                I=>PORTAQ(11),
                O=>IOPORT(11));
   
   XLXI_7 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(10),
                I=>PORTAQ(10),
                O=>IOPORT(10));
   
   XLXI_8 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(9),
                I=>PORTAQ(9),
                O=>IOPORT(9));
   
   XLXI_9 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(8),
                I=>PORTAQ(8),
                O=>IOPORT(8));
   
   XLXI_10 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(7),
                I=>PORTAQ(7),
                O=>IOPORT(7));
   
   XLXI_11 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(6),
                I=>PORTAQ(6),
                O=>IOPORT(6));
   
   XLXI_12 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(5),
                I=>PORTAQ(5),
                O=>IOPORT(5));
   
   XLXI_13 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(4),
                I=>PORTAQ(4),
                O=>IOPORT(4));
   
   XLXI_15 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(3),
                I=>PORTAQ(3),
                O=>IOPORT(3));
   
   XLXI_16 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(2),
                I=>PORTAQ(2),
                O=>IOPORT(2));
   
   XLXI_17 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(1),
                I=>PORTAQ(1),
                O=>IOPORT(1));
   
   XLXI_18 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(0),
                I=>PORTAQ(0),
                O=>IOPORT(0));
   
   XLXI_40 : LD16_MXILINX_ioport
      port map (D(15 downto 0)=>D(15 downto 0),
                G=>XLXN_173,
                Q(15 downto 0)=>TRISAQ(15 downto 0));
   
   XLXI_41 : LD16_MXILINX_ioport
      port map (D(15 downto 0)=>D(15 downto 0),
                G=>XLXN_171,
                Q(15 downto 0)=>PORTAQ(15 downto 0));
   
   XLXI_194 : OBUFE_MXILINX_ioport
      port map (E=>TRISAQ(15),
                I=>PORTAQ(15),
                O=>IOPORT(15));
   
   XLXI_239 : AND2
      port map (I0=>PORTCS,
                I1=>WR,
                O=>XLXN_171);
   
   XLXI_240 : IBUF16_MXILINX_ioport
      port map (I(15 downto 0)=>IOPORT(0 to 15),
                O(15 downto 0)=>IOIN(15 downto 0));
   
   XLXI_241 : AND2
      port map (I0=>WR,
                I1=>TRISCS,
                O=>XLXN_173);
   
end BEHAVIORAL;


