----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:24:56 08/05/2014 
-- Design Name: 
-- Module Name:    ioport_16 - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity lbus is
    Port ( pclk : in STD_LOGIC;
	        cpuclk : in STD_LOGIC;
			  ale : in STD_LOGIC;
	        reset : in STD_LOGIC;
	        wr : in STD_LOGIC;
	        rd : in STD_LOGIC;
			  mio : in STD_LOGIC;
			  a : in STD_LOGIC_VECTOR (19 downto 0);
			  dtr : in STD_LOGIC;
			  den : in STD_LOGIC;
			  lle : in STD_LOGIC;
           lbuscs : in  STD_LOGIC;
           d : in  STD_LOGIC_VECTOR (15 downto 0);
			  ioin : out  STD_LOGIC_VECTOR (7 downto 0);
			  lbus_mio : out STD_LOGIC;
			  lbus_dtr : out STD_LOGIC;
			  lbus_den : out STD_LOGIC;
			  lbus_rd : out STD_LOGIC;
			  lbus_wr : out STD_LOGIC;
			  lbus_rst : out STD_LOGIC;
			  lbus_ale : out STD_LOGIC;
           lbus_ad : inout  STD_LOGIC_VECTOR (7 downto 0);
			  lbus_a : out  STD_LOGIC_VECTOR (19 downto 8));
end lbus;

architecture Behavioral of lbus is
signal eightbitdmx : std_logic_vector(7 downto 0);
signal dirholdp1 : STD_LOGIC;
signal dirholdp2 : STD_LOGIC;
signal lfall : STD_LOGIC;
begin

lbus_wr <= (lbuscs and wr);
lbus_rd <= (lbuscs and rd);
lbus_a <= a(19 downto 8);
lbus_dtr <= dtr;
lbus_den <= (lbuscs and den);
ioin <= lbus_ad;
lbus_rst <= reset;
lbus_ale <= ale and (not cpuclk);
lbus_mio <= mio;


lfall <= mio or ale;

process (lfall, rd, wr)
begin
	if (rd = '1' or wr = '1') then
		dirholdp1 <= '0';
	elsif (falling_edge(lfall)) then
		dirholdp1 <= not dirholdp1;
	end if;
end process;

process (dirholdp1, pclk)
begin
	if (rising_edge(pclk)) then
		dirholdp2 <= dirholdp1;
	end if;
end process;

process(dirholdp1, dirholdp2, d)
begin
	if (dirholdp1 = '1' or dirholdp2 = '1' or lle = '1') then
		eightbitdmx <= d(7 downto 0);
	else
		eightbitdmx <= d(15 downto 8);
	end if;
end process;

process(dirholdp1, dirholdp2, eightbitdmx)
begin
   if ((dirholdp1 = '1' and dirholdp2 = '1') or (dtr = '1' and den = '1' and mio = '0')) then
		lbus_ad <= eightbitdmx;
	else
		lbus_ad <= "ZZZZZZZZ";
	end if;
end process;

end Behavioral;

