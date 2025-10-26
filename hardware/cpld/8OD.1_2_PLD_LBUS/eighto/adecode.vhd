----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:23:03 07/21/2014 
-- Design Name: 
-- Module Name:    adecode - Behavioral 
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

entity adecode is
    Port ( MIO : in STD_LOGIC;
			  A : in  STD_LOGIC_VECTOR (19 downto 0);
			  BHE : in STD_LOGIC;
			  DEN : in STD_LOGIC;
           ROMCS : out  STD_LOGIC;
           RAMCS : out  STD_LOGIC;
           UCSA : out  STD_LOGIC;
           UCSB : out  STD_LOGIC;
           UCSC : out  STD_LOGIC;
           UCSD : out  STD_LOGIC;
			  STATUS : out STD_LOGIC;
			  CFG : out STD_LOGIC;
           PORTA : out  STD_LOGIC;
           PORTB : out  STD_LOGIC;
           TRISA : out  STD_LOGIC;
           TRISB : out  STD_LOGIC;
			  MIDCS : out STD_LOGIC;
			  TIMER : out STD_LOGIC;
			  I2CCS : out STD_LOGIC;
			  UHE : out STD_LOGIC;
			  ULE : out STD_LOGIC;
			  LBUSCS : out STD_LOGIC;
			  LHE : out STD_LOGIC;
			  LLE : out STD_LOGIC);
end adecode;

architecture Behavioral of adecode is
signal UA : STD_LOGIC;
signal UB : STD_LOGIC;
signal UC : STD_LOGIC;
signal UD : STD_LOGIC;
signal I2C : STD_LOGIC;
signal MID : STD_LOGIC;
signal LBUS : STD_LOGIC;
begin
	
	ROMCS <= (MIO and A(19));
	RAMCS <= (MIO and (not A(19)));
	
   LBUS <= ((not MIO) and (A(7) or A(14) or A(15)));
	UA  <= ((not MIO) and (not LBUS) and (not A(6)) and (A(5)) and (not A(4)) and (not A(3)));
	UB  <= ((not MIO) and (not LBUS) and (not A(6)) and (A(5)) and (not A(4)) and (A(3)));
	UC  <= ((not MIO) and (not LBUS) and (not A(6)) and (A(5)) and (A(4)) and (not A(3)));
	UD  <= ((not MIO) and (not LBUS) and (not A(6)) and (A(5)) and (A(4)) and (A(3)));
	MID <= ((not MIO) and (not LBUS) and (A(6)) and (not A(5)) and (not A(4)));
   I2C <= ((not MIO) and (not LBUS) and (A(6)) and (not A(5)) and A(4));

	UCSA <= UA;
	UCSB <= UB;
	UCSC <= UC;
	UCSD <= UD;
	MIDCS <= MID;
	I2CCS <= I2C;
	LBUSCS <= LBUS;
	
	STATUS <= ((not MIO) and (not LBUS) and (not A(6)) and (not A(5)) and (not A(4)) and (not A(3)) and (not A(2)) and (not A(1)));
	CFG    <= ((not MIO) and (not LBUS) and (not A(6)) and (not A(5)) and (not A(4)) and (not A(3)) and (not A(2)) and (A(1)));
	
	PORTA <= ((not MIO) and (not LBUS) and (not A(6)) and (not A(5)) and (not A(4)) and (not A(3)) and (A(2)) and (not A(1)));
	PORTB <= ((not MIO) and (not LBUS) and (not A(6)) and (not A(5)) and (not A(4)) and (not A(3)) and (A(2)) and (A(1)));

	TRISA <= ((not MIO) and (not LBUS) and (not A(6)) and (not A(5)) and (not A(4)) and (A(3)) and (A(2)) and (not A(1)));
	TRISB <= ((not MIO) and (not LBUS) and (not A(6)) and (not A(5)) and (not A(4)) and (A(3)) and (A(2)) and (A(1)));

	TIMER <= ((not MIO) and (not LBUS) and (not A(6)) and (not A(5)) and (A(4)) and (A(3)) and (not A(2)) and (not A(1)));
	
	ULE <= ((UA or UB or UC or UD or MID or I2C) and (not A(0)) and (not BHE) and DEN);
	UHE <= ((UA or UB or UC or UD or MID or I2C) and A(0) and BHE and DEN);
	
	LLE <= (LBUS and (not A(0)) and (not BHE) and DEN);
	LHE <= (LBUS and A(0) and BHE and DEN);
	
end Behavioral;

