----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    22:02:37 08/11/2014 
-- Design Name: 
-- Module Name:    timer16 - Behavioral 
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

entity timer16 is
    Port ( reset : in  STD_LOGIC;
           wr : in  STD_LOGIC;
           timercs : in  STD_LOGIC;
           run : in  STD_LOGIC;
			  clk : in  STD_LOGIC;
           d : in  STD_LOGIC_VECTOR (15 downto 0);
           overflow : out  STD_LOGIC);
end timer16;

architecture Behavioral of timer16 is
signal count0 : STD_LOGIC_VECTOR (15 downto 0);
constant tc : STD_LOGIC_VECTOR (15 downto 0) := (others => '1');
signal tcclk : STD_LOGIC;
signal timerwr : STD_LOGIC;
begin

timerwr <= (wr and timercs);
tcclk <= ((clk and (not timercs)) or timerwr);

process (tcclk, reset) is   
begin
	if (reset='1') then
		count0 <= (others => '0');
	elsif (rising_edge (tcclk)) then
		if (timerwr = '1') then
			count0 <= d;
		elsif (run = '1') then
			count0 <= count0 + 1;
		end if;
	end if;
end process;

overflow <= '1' when count0 = tc else '0';

end Behavioral;

