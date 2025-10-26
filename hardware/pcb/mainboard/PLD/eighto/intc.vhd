----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:39:25 08/08/2014 
-- Design Name: 
-- Module Name:    intc - Behavioral 
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

entity intc is
    Port ( reset : in STD_LOGIC;
			  wr : in STD_LOGIC;
			  statusen : in STD_LOGIC;
			  uena : in STD_LOGIC;
           uenb : in STD_LOGIC;
           uenc : in STD_LOGIC;
           uend : in STD_LOGIC;
           tmen : in STD_LOGIC;
			  portainten : in STD_LOGIC;
			  extintaen : in STD_LOGIC;
			  extintben : in STD_LOGIC;
           gie : in STD_LOGIC;
           uinta : in STD_LOGIC;
           uintb : in STD_LOGIC;
           uintc : in STD_LOGIC;
           uintd : in STD_LOGIC;
           tmint : in STD_LOGIC;
			  portaint : in STD_LOGIC;
			  extinta : in STD_LOGIC;
			  extintb : in STD_LOGIC;
			  d : in STD_LOGIC_VECTOR (15 downto 0);
           status : out  STD_LOGIC_VECTOR (7 downto 0);
			  irq : out STD_LOGIC);
end intc;

architecture Behavioral of intc is
signal statuswr : STD_LOGIC;
signal timerflag : STD_LOGIC;
signal portaflag : STD_LOGIC;
signal extflaga : STD_LOGIC;
signal extflagb : STD_LOGIC;
begin

	statuswr <= (wr and statusen);
	
	process(reset, statuswr, tmint, d)
	
	begin
		if(reset = '1') then
			timerflag <= '0';
		elsif (tmint = '1') then
			timerflag <= '1';
		elsif (rising_edge(statuswr)) then
			if (d(0) = '0') then
				timerflag <= '0';
			end if;
		end if;
	end process;
	
	process(reset, statuswr, portaint, d)
	begin
		if (reset = '1') then
			portaflag <= '0';
		elsif (portaint = '1') then
			portaflag <= '1';
		elsif (rising_edge(statuswr)) then
			if (d(1) = '0') then
				portaflag <= '0';
			end if;
		end if;
	end process;
	
	process(reset, statuswr, extinta, d)
	begin
		if (reset = '1') then
			extflaga <= '0';
		elsif (extinta = '1') then
			extflaga <= '1';
		elsif (rising_edge(statuswr)) then
			if (d(6) = '0') then
				extflaga <= '0';
			end if;
		end if;
	end process;
	
	process(reset, statuswr, extintb, d)
	begin
		if (reset = '1') then
			extflagb <= '0';
		elsif (extintb = '1') then
			extflagb <= '1';
		elsif (rising_edge(statuswr)) then
			if (d(7) = '0') then
				extflagb <= '0';
			end if;
		end if;
	end process;
	
	status(0) <= timerflag;
	status(1) <= portaflag;
	
	status(2) <= uinta;
	status(3) <= uintb;
	status(4) <= uintc;
	status(5) <= uintd;
	
	status(6) <= extflaga;
	status(7) <= extflagb;
	
	irq <= (gie and ((uena and uinta) or (uenb and uintb) or (uenc and uintc) or (uend and uintd) or (tmen and timerflag)
		or (portainten and portaflag) or (extflaga and extintaen) or (extflagb and extintben)));

end Behavioral;

