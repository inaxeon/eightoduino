----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:04:32 08/04/2014 
-- Design Name: 
-- Module Name:    portread - Behavioral 
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

entity portread is
    Port ( porta : in  STD_LOGIC_VECTOR (15 downto 0);
           portb : in  STD_LOGIC_VECTOR (5 downto 0);
           eightbit : in  STD_LOGIC_VECTOR (7 downto 0);
			  status : in  STD_LOGIC_VECTOR (7 downto 0);
           portout : out  STD_LOGIC_VECTOR (15 downto 0);
           portaen : in  STD_LOGIC;
           portben : in  STD_LOGIC;
           eightbiten : in  STD_LOGIC;
			  lle : in  STD_LOGIC;
			  statusen : in  STD_LOGIC);
end portread;

architecture Behavioral of portread is
signal eightbitdmx : STD_LOGIC_VECTOR (15 downto 0);
begin

process (portaen, portben, eightbiten, porta, portb, eightbit, statusen, eightbiten, lle, status)
begin

	if (lle = '1') then
		eightbitdmx(7 downto 0) <= eightbit;
		eightbitdmx(15 downto 8) <= porta(7 downto 0);
	else
	   eightbitdmx(7 downto 0) <= porta(7 downto 0);
		eightbitdmx(15 downto 8) <= eightbit;
   end if;

	if (eightbiten = '1') then
		portout(15 downto 8) <= eightbitdmx(15 downto 8);
	else
		portout(15 downto 8) <= porta(15 downto 8);
	end if;
	
	if (eightbiten = '1' and statusen = '0') then
		portout(7 downto 6) <= eightbitdmx(7 downto 6);
	elsif (eightbiten = '0' and statusen = '1') then
		portout(7 downto 6) <= status(7 downto 6);
	else
		portout(7 downto 6) <= porta(7 downto 6);
	end if;
	
	if (eightbiten = '1' and portben = '0' and statusen = '0') then
		portout(5 downto 1) <= eightbitdmx(5 downto 1);
	elsif (eightbiten = '0' and portben = '1' and statusen = '0') then
		portout(5 downto 1) <= portb(5 downto 1);
	elsif (eightbiten = '0' and eightbiten = '0' and statusen = '1') then
		portout(5 downto 1) <= status(5 downto 1);
	else
		portout(5 downto 1) <= porta(5 downto 1);
	end if;
	
	if (eightbiten = '1' and portben = '0' and statusen = '0') then
		portout(0) <= eightbitdmx(0);
	elsif (eightbiten = '0' and portben = '1' and statusen = '0') then
		portout(0) <= portb(0);
	elsif (eightbiten = '0' and portben = '0' and statusen = '1') then
		portout(0) <= status(0);
	else
		portout(0) <= porta(0);
	end if;
	
end process;

end Behavioral;

