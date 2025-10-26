----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:48:39 09/04/2014 
-- Design Name: 
-- Module Name:    biu - Behavioral 
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

entity biu is
    Port ( sync : in STD_LOGIC;
			  clk : in STD_LOGIC;
			  rdin : in  STD_LOGIC;
           wrin : in  STD_LOGIC;
			  rd_nosync : out STD_LOGIC;
			  wr_nosync : out STD_LOGIC;
           rd_sync : out STD_LOGIC;
           wr_sync : out STD_LOGIC;
			  rdy : out STD_LOGIC;
			  irdy : in STD_LOGIC);
end biu;

architecture Behavioral of biu is
signal wrhold : STD_LOGIC;
signal rdhold : STD_LOGIC;
signal wrhigh : STD_LOGIC;
signal rdhigh : STD_LOGIC;
begin

wrhigh <= (clk and wrin);
rdhigh <= (clk and rdin);

process(irdy)
begin
	if (rising_edge(clk)) then
		rdy <= irdy;
	end if;
end process;

process(wrhigh, sync)
begin
	if (sync = '1') then
		wrhold <= '0';
	elsif (rising_edge(wrhigh)) then
		wrhold <= not wrhold;
	end if;
end process;

process(rdhigh, sync)
begin
	if (sync = '1') then
		rdhold <= '0';
	elsif (rising_edge(rdhigh)) then
		rdhold <= not rdhold;
	end if;
end process;

wr_sync <= wrhold;
rd_sync <= rdhold;
rd_nosync <= rdin;
wr_nosync <= wrin;

end Behavioral;

