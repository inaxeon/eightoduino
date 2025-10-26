----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:19:31 08/05/2014 
-- Design Name: 
-- Module Name:    oport_6 - Behavioral 
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

entity spimaster is
    Port ( reset : in  STD_LOGIC;
			  wr : in  STD_LOGIC;
			  rd : in  STD_LOGIC;
           ctrlcs : in  STD_LOGIC;
			  wrcs : in  STD_LOGIC;
			  rdcs : in  STD_LOGIC;
           d : in  STD_LOGIC_VECTOR (15 downto 0);
			  eewp : out STD_LOGIC;
			  eecs : out STD_LOGIC;
			  adcs : out STD_LOGIC;
			  sck : out STD_LOGIC;
			  mosi : out STD_LOGIC;
			  miso : in STD_LOGIC;
			  miso_out : out STD_LOGIC);
end spimaster;

architecture Behavioral of spimaster is
signal portwr : STD_LOGIC;
signal spiclkhigh : STD_LOGIC;
begin

sck <= (rd and rdcs) or (wr and wrcs);
portwr <= (wr and ctrlcs);
miso_out <= miso;
mosi <= wrcs and d(7);

process(portwr, reset)
begin
	if(reset = '1') then
		eewp <= '0';
		eecs <= '0';
		adcs <= '0';
	elsif (rising_edge(portwr)) then 
		eewp <= d(2);
		eecs <= d(1);
		adcs <= d(0);
	end if;
end process;

end Behavioral;

