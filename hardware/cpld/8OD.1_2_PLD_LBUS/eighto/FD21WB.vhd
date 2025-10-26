----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:07:55 10/04/2014 
-- Design Name: 
-- Module Name:    FD21 - Behavioral 
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

entity FD21 is
    Port ( AD : in  STD_LOGIC_VECTOR (15 downto 0);
			  A : in  STD_LOGIC_VECTOR (3 downto 0);
           BHE : in  STD_LOGIC;
           E : in  STD_LOGIC;
           Q : out  STD_LOGIC_VECTOR (19 downto 0);
           BHEQ : out  STD_LOGIC);
end FD21;

architecture Behavioral of FD21 is

begin

process(E, BHE, AD, A)
begin
	if (E='1') then 
		Q(15 downto 0) <= AD(15 downto 0);
		Q(19 downto 16) <= A(3 downto 0);
		BHEQ <= BHE;
   end if;
end process;

end Behavioral;

