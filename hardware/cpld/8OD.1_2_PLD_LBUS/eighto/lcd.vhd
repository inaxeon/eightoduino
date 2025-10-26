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

entity lcd is
    Port ( wr : in  STD_LOGIC;
	        rd : in STD_LOGIC;
			  a : in STD_LOGIC_VECTOR (19 downto 0);
			  dtr : in STD_LOGIC;
			  den : in STD_LOGIC;
			  lle : in STD_LOGIC;
           lcdcs : in  STD_LOGIC;
           d : in  STD_LOGIC_VECTOR (15 downto 0);
			  ioin : out  STD_LOGIC_VECTOR (7 downto 0);
			  lcd_rs : out STD_LOGIC;
			  lcd_rw : out STD_LOGIC;
			  lcd_e1 : out STD_LOGIC;
			  lcd_e2 : out STD_LOGIC;
           lcd_d : inout  STD_LOGIC_VECTOR (7 downto 0));
end lcd;

architecture Behavioral of lcd is
signal eightbitdmx : std_logic_vector(7 downto 0);
begin

lcd_rs <= A(0);
lcd_rw <= (not dtr);

lcd_e1 <= (lcdcs and (wr or rd) and (not A(1)));
lcd_e2 <= (lcdcs and (wr or rd) and (A(1)));

ioin <= lcd_d;

process(lle, d)
begin
	if (lle = '1') then
		eightbitdmx <= d(7 downto 0);
	else
		eightbitdmx <= d(15 downto 8);
	end if;
end process;

process(dtr, lcdcs, eightbitdmx)
begin
	if (dtr = '1' and lcdcs = '1') then
		lcd_d <= eightbitdmx;
	else
		lcd_d <= "ZZZZZZZZ";
	end if;
end process;

end Behavioral;

