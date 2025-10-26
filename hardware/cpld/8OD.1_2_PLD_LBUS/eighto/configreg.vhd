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
    Port ( reset : in  STD_LOGIC;
			  wr : in  STD_LOGIC;
           configcs : in  STD_LOGIC;
           d : in  STD_LOGIC_VECTOR (15 downto 0);
			  eewp : out  STD_LOGIC;
           rst : out  STD_LOGIC;
           tmrun : out  STD_LOGIC;
           uena : out  STD_LOGIC;
           uenb : out  STD_LOGIC;
           uenc : out  STD_LOGIC;
           uend : out  STD_LOGIC;
			  extinta : out  STD_LOGIC;
			  extintb : out  STD_LOGIC;
           uinta : out  STD_LOGIC;
           uintb : out  STD_LOGIC;
           uintc : out  STD_LOGIC;
           uintd : out  STD_LOGIC;
           tmint : out  STD_LOGIC;
			  portainten : out STD_LOGIC;
           gie : out  STD_LOGIC);
end configreg;

architecture Behavioral of configreg is
signal configwr : STD_LOGIC;
begin

configwr <= (wr and configcs);

process(configwr, reset)
begin
	if(reset = '1') then
		rst <= '0';
	elsif (rising_edge(configwr)) then 
		rst <= d(15);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		tmrun <= '0';
	elsif (rising_edge(configwr)) then 
		tmrun <= d(14);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		uend <= '0';
	elsif (rising_edge(configwr)) then 
		uend <= d(13);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		uenc <= '0';
	elsif (rising_edge(configwr)) then 
		uenc <= d(12);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		uenb <= '0';
	elsif (rising_edge(configwr)) then 
		uenb <= d(11);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		uena <= '0';
	elsif (rising_edge(configwr)) then 
		uena <= d(10);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		eewp <= '0';
	elsif (rising_edge(configwr)) then 
		eewp <= d(9);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		extintb <= '0';
	elsif (rising_edge(configwr)) then 
		extintb <= d(8);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		extinta <= '0';
	elsif (rising_edge(configwr)) then 
		extinta <= d(7);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		uintd <= '0';
	elsif (rising_edge(configwr)) then 
		uintd <= d(6);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		uintc <= '0';
	elsif (rising_edge(configwr)) then 
		uintc <= d(5);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		uintb <= '0';
	elsif (rising_edge(configwr)) then 
		uintb <= d(4);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		uinta <= '0';
	elsif (rising_edge(configwr)) then 
		uinta <= d(3);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		portainten <= '0';
	elsif (rising_edge(configwr)) then 
		portainten <= d(2);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		tmint <= '0';
	elsif (rising_edge(configwr)) then 
		tmint <= d(1);       
	end if;
end process;

process(configwr, reset)
begin
	if(reset = '1') then
		gie <= '0';
	elsif (rising_edge(configwr)) then 
		gie <= d(0);       
	end if;
end process;

end Behavioral;

