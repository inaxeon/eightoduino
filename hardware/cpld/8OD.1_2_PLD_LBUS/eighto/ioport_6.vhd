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

entity ioport_6 is
    Port ( wr : in  STD_LOGIC;
           portcs : in  STD_LOGIC;
           triscs : in  STD_LOGIC;
           d: in  STD_LOGIC_VECTOR (15 downto 0);
           ioin : out  STD_LOGIC_VECTOR (5 downto 0);
           ioport : inout  STD_LOGIC_VECTOR (5 downto 0));
end ioport_6;

architecture Behavioral of ioport_6 is
signal trishold : std_logic_vector(5 downto 0);
begin

ioin(5 downto 0) <= ioport(5 DOWNTO 0);

process (triscs, wr, d)
begin
	if (wr = '1' and triscs = '1') then
		trishold <= d(5 downto 0);
	end if;
end process;

process (portcs, wr, d, trishold)
begin
	for i in 5 downto 0 loop
		if (wr = '1' and portcs = '1' and trishold(i) = '0') then
			ioport(i) <= d(i);
		else
			ioport(i) <= 'Z';
		end if;
	end loop;
end process;

end Behavioral;

