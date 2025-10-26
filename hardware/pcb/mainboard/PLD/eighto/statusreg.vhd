----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    20:27:20 08/05/2014 
-- Design Name: 
-- Module Name:    configreg - Behavioral 
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

entity configreg is
    Port ( wr : in  STD_LOGIC;
           configcs : in  STD_LOGIC;
           d : in  STD_LOGIC_VECTOR (15 downto 0);
           rst : out  STD_LOGIC;
           tmrun : out  STD_LOGIC;
           uena : out  STD_LOGIC;
           uenb : out  STD_LOGIC;
           uenc : out  STD_LOGIC;
           uend : out  STD_LOGIC;
           uinta : out  STD_LOGIC;
           uintb : out  STD_LOGIC;
           uintc : out  STD_LOGIC;
           uintd : out  STD_LOGIC;
           tmint : out  STD_LOGIC;
           gie : out  STD_LOGIC);
end configreg;

architecture Behavioral of configreg is

begin

process(wr, configreg, d)
begin
  if (wr = '1' and configcs = '1') then
      rst <= d(11);
		tmrun <= d(10);
		uena <= d(9);
		uenb <= d(8);
		uenc <= d(7);
		uend <= d(6);
		uinta <= d(5);
		uintb <= d(4);
		uintc <= d(3);
		uintd <= d(2);
		tmint <= d(1);
		gie <= d(0);
  end if;
end process;


end Behavioral;

