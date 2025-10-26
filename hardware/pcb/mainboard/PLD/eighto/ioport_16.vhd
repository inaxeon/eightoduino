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

entity ioport_16 is
    Port ( reset : in  STD_LOGIC;
			  wr : in  STD_LOGIC;
           portcs : in  STD_LOGIC;
           triscs : in  STD_LOGIC;
           d: in  STD_LOGIC_VECTOR (15 downto 0);
           ioin : out  STD_LOGIC_VECTOR (15 downto 0);
           ioport : inout  STD_LOGIC_VECTOR (15 downto 0));
end ioport_16;

architecture Behavioral of ioport_16 is
signal trishold : std_logic_vector(15 downto 0);
signal dq : std_logic_vector(15 downto 0);
signal triswr : STD_LOGIC;
signal portwr : STD_LOGIC;
begin

triswr <= (wr and triscs);
portwr <= (wr and portcs);

ioin(15 downto 0) <= ioport(15 downto 0);

process(triswr, reset)
begin
	if(reset = '1') then
		trishold <= (others => '1');
	elsif (rising_edge(triswr)) then 
		trishold <= d;
	end if;
end process;

process(portwr, reset)
begin
	if(reset = '1') then
		dq <= (others => '0');
	elsif (rising_edge(portwr)) then 
		dq <= d;       
	end if;
end process;

process (trishold, dq)
begin
	for i in 15 downto 0 loop
		if (trishold(i) = '0') then
			ioport(i) <= dq(i);
		else
			ioport(i) <= 'Z';
		end if;
	end loop;
end process;

end Behavioral;

