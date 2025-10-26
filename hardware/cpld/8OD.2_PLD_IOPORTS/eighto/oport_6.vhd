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

entity oport_6 is
    Port ( reset : in  STD_LOGIC;
			  wr : in  STD_LOGIC;
           portcs : in  STD_LOGIC;
           d : in  STD_LOGIC_VECTOR (15 downto 0);
           oport : out  STD_LOGIC_VECTOR (5 downto 0));
end oport_6;

architecture Behavioral of oport_6 is
signal portwr : STD_LOGIC;
begin

portwr <= (wr and portcs);

process(portwr, reset)
begin
	if(reset = '1') then
		oport <= (others => '0');
	elsif (rising_edge(portwr)) then 
		oport <= d(5 downto 0);       
	end if;
end process;

end Behavioral;

