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

entity ioport_16_umux is
    Port ( reset : in  STD_LOGIC;
	        wr : in  STD_LOGIC;
			  rd : in  STD_LOGIC;
           portcs : in  STD_LOGIC;
           triscs : in  STD_LOGIC;
           d: in  STD_LOGIC_VECTOR (15 downto 0);
           ioin : out  STD_LOGIC_VECTOR (15 downto 0);
           ioport : inout  STD_LOGIC_VECTOR (15 downto 0);
			  utxa : in STD_LOGIC;
			  utxd : in STD_LOGIC;
			  urxa : out STD_LOGIC;
			  urxd : out STD_LOGIC;
			  pgmrxd : in STD_LOGIC;
			  uena : in STD_LOGIC;
			  uend : in STD_LOGIC;
			  portint : out STD_LOGIC;
			  extinta : out STD_LOGIC;
			  extintb : out STD_LOGIC);
end ioport_16_umux;

architecture Behavioral of ioport_16_umux is
signal changehold : STD_LOGIC_VECTOR(3 downto 0);
signal changed : STD_LOGIC_VECTOR(3 downto 0);
signal trishold : STD_LOGIC_VECTOR(15 downto 0);
signal dq : STD_LOGIC_VECTOR(15 downto 0);
signal triswr : STD_LOGIC;
signal portwr : STD_LOGIC;
signal changereset : STD_LOGIC;
begin

triswr <= (wr and triscs);
portwr <= (wr and portcs);
changereset <= (rd and portcs);
ioin(15 downto 0) <= ioport(15 downto 0);
urxa <= ioport(0) when uena = '1' else '1';
urxd <= ioport(15) when uend = '1' else pgmrxd;

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

process(changereset, reset)
begin
	if(reset = '1') then
		changehold <= (others => '0');
	elsif (rising_edge(changereset)) then 
		changehold <= ioport(11 downto 8);       
	end if;
end process;

process(changehold, ioport, trishold)
begin
	for i in 3 downto 0 loop
		changed(i) <= (trishold(i + 8) and (changehold(i) xor ioport(i + 8)));
	end loop;
end process;

portint <= (changed(3) or changed(2) or changed(1) or changed(0));
extinta <= ioport(2) and trishold(2);
extintb <= ioport(3) and trishold(3);

process (trishold, dq, uena, uend, utxa, utxd)
begin

	if (trishold(15) = '0') then
		ioport(15) <= dq(15);
	else
		ioport(15) <= 'Z';
	end if;

	if (trishold(14) = '0' and uend = '0') then
		ioport(14) <= dq(14);
	elsif (trishold(14) = '0' and uend = '1') then
		ioport(14) <= utxd;
	else
		ioport(14) <= 'Z';
	end if;
	
	for i in 13 downto 2 loop
		if (trishold(i) = '0') then
			ioport(i) <= dq(i);
		else
			ioport(i) <= 'Z';
		end if;
	end loop;
	
	if (trishold(1) = '0' and uena = '0') then
		ioport(1) <= dq(1);
	elsif (trishold(1) = '0' and uena = '1') then
		ioport(1) <= utxa;
	else
		ioport(1) <= 'Z';
	end if;
	
	if (trishold(0) = '0') then
		ioport(0) <= dq(0);
	else
		ioport(0) <= 'Z';
	end if;
	
end process;

end Behavioral;

