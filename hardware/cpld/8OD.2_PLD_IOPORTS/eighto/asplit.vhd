----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:41:21 11/09/2015 
-- Design Name: 
-- Module Name:    asplit - Behavioral 
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

entity asplit is
    Port ( al : in  STD_LOGIC_VECTOR (19 downto 0);
           aq : out  STD_LOGIC_VECTOR (18 downto 0);
           a19 : out  STD_LOGIC);
end asplit;

architecture Behavioral of asplit is

begin
aq <= al(18 downto 0);
a19 <= al(19);
end Behavioral;

