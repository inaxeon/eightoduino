----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:47:56 08/08/2014 
-- Design Name: 
-- Module Name:    clockreset - Behavioral 
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity cpuclock is
    Port ( clkin : in  STD_LOGIC;
			  cpu10 : in  STD_LOGIC;
			  timerclk : out STD_LOGIC;
			  cpuclk : out STD_LOGIC;
			  clkd2 : out STD_LOGIC;
			  pclk : out STD_LOGIC);
end cpuclock;

architecture Behavioral of cpuclock is
signal tclk : STD_LOGIC_VECTOR (5 downto 0);
signal thirdclk : STD_LOGIC_VECTOR (1 downto 0);
signal thirdclkout : STD_LOGIC;
signal inclkd2 : STD_LOGIC;
signal inclkd4 : STD_LOGIC;
signal masterclk : STD_LOGIC;
begin

process (clkin) is   
begin
	if (rising_edge (clkin)) then
		inclkd2 <=  not inclkd2;
	end if;
end process;

process (inclkd2) is   
begin
	if (rising_edge (inclkd2)) then
		inclkd4 <=  not inclkd4;
	end if;
end process;

masterclk <= inclkd2 when cpu10 = '0' else clkin;
clkd2 <= inclkd4 when cpu10 = '0' else inclkd2;
pclk <= masterclk;

process (masterclk) is   
begin
	if (rising_edge (masterclk)) then
		if (thirdclk = 2) then
			thirdclk <= (others => '0');
		else
			thirdclk <= thirdclk + 1;
		end if;
	end if;
end process;

thirdclkout <= thirdclk(0);
cpuclk <= thirdclkout;

process (thirdclkout) is   
begin
	if (rising_edge (thirdclkout)) then
		tclk <= tclk + 1;
	end if;
end process;

timerclk <= tclk(5);

end Behavioral;

