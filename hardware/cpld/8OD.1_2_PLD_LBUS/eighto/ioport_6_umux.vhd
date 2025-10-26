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

entity ioport_6_umux is
    Port ( reset : in  STD_LOGIC;
			  wr : in  STD_LOGIC;
           portcs : in  STD_LOGIC;
           triscs : in  STD_LOGIC;
           d: in  STD_LOGIC_VECTOR (15 downto 0);
           ioin : out  STD_LOGIC_VECTOR (5 downto 0);
           ioport : inout  STD_LOGIC_VECTOR (5 downto 0);
			  utxb : in STD_LOGIC;
			  utxc : in STD_LOGIC;
			  urxb : out STD_LOGIC;
			  urxc : out STD_LOGIC;
			  uenb : in STD_LOGIC;
			  uenc : in STD_LOGIC);
end ioport_6_umux;

architecture Behavioral of ioport_6_umux is
signal trishold : std_logic_vector(5 downto 0);
signal dq : std_logic_vector(5 downto 0);
signal triswr : STD_LOGIC;
signal portwr : STD_LOGIC;
begin

triswr <= (wr and triscs);
portwr <= (wr and portcs);
ioin(5 downto 0) <= ioport(5 downto 0);
urxc <= ioport(1) when uenc = '1' else '1';
urxb <= ioport(3) when uenb = '1' else '1';

process(triswr, reset)
begin
	if(reset = '1') then
		trishold <= (others => '1');
	elsif (rising_edge(triswr)) then 
		trishold <= d(5 downto 0);
	end if;
end process;

process(portwr, reset)
begin
	if(reset = '1') then
		dq <= (others => '0');
	elsif (rising_edge(portwr)) then 
		dq <= d(5 downto 0);
	end if;
end process;

process (trishold, dq, uenb, uenc, utxb, utxc)
begin
	for i in 5 downto 3 loop
		if (trishold(i) = '0') then
			ioport(i) <= dq(i);
		else
			ioport(i) <= 'Z';
		end if;
	end loop;
	
	if (trishold(2) = '0' and uenb = '0') then
		ioport(2) <= dq(2);
	elsif (trishold(2) = '0' and uenb = '1') then
		ioport(2) <= utxb;
	else
		ioport(2) <= 'Z';
	end if;
	
	if (trishold(1) = '0') then
		ioport(1) <= dq(1);
	else
		ioport(1) <= 'Z';
	end if;
	
	if (trishold(0) = '0' and uenc = '0') then
		ioport(0) <= dq(0);
	elsif (trishold(0) = '0' and uenc = '1') then
		ioport(0) <= utxc;
	else
		ioport(0) <= 'Z';
	end if;
	
end process;

end Behavioral;

