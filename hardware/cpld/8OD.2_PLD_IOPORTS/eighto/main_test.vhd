-- Vhdl test bench created from schematic C:\Projects\8086\PLD\eighto\main.sch - Wed Aug 06 21:28:43 2014
--
-- Notes: 
-- 1) This testbench template has been automatically generated using types
-- std_logic and std_logic_vector for the ports of the unit under test.
-- Xilinx recommends that these types always be used for the top-level
-- I/O of a design in order to guarantee that the testbench will bind
-- correctly to the timing (post-route) simulation model.
-- 2) To use this template as your testbench, change the filename to any
-- name of your choice with the extension .vhd, and use the "Source->Add"
-- menu in Project Navigator to import the testbench. Then
-- edit the user defined section below, adding code to generate the 
-- stimulus for your design.
--
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
LIBRARY UNISIM;
USE UNISIM.Vcomponents.ALL;
ENTITY main_main_sch_tb IS
END main_main_sch_tb;
ARCHITECTURE behavioral OF main_main_sch_tb IS 

   COMPONENT main
   PORT( A19	:	IN	STD_LOGIC; 
          MIO	:	IN	STD_LOGIC; 
          ROMCS	:	OUT	STD_LOGIC; 
          RAMCS	:	OUT	STD_LOGIC; 
          UCSA	:	OUT	STD_LOGIC; 
          UCSB	:	OUT	STD_LOGIC; 
          UCSC	:	OUT	STD_LOGIC; 
          UCSD	:	OUT	STD_LOGIC; 
          AQ	:	OUT	STD_LOGIC_VECTOR (15 DOWNTO 0); 
          AD	:	INOUT	STD_LOGIC_VECTOR (15 DOWNTO 0); 
          PORTA	:	INOUT	STD_LOGIC_VECTOR (0 TO 15); 
          PORTD	:	OUT	STD_LOGIC_VECTOR (0 TO 5); 
          PORTE	:	INOUT	STD_LOGIC_VECTOR (0 TO 15); 
          EXTWR	:	IN	STD_LOGIC; 
          EXTRD	:	IN	STD_LOGIC; 
          PORTC	:	OUT	STD_LOGIC_VECTOR (15 DOWNTO 0); 
          PORTB	:	INOUT	STD_LOGIC_VECTOR (5 DOWNTO 0); 
          TXA	:	IN	STD_LOGIC; 
          TXD	:	IN	STD_LOGIC; 
          TXB	:	IN	STD_LOGIC; 
          TXC	:	IN	STD_LOGIC; 
          ALE	:	IN	STD_LOGIC; 
          SYSRESET	:	IN	STD_LOGIC);
   END COMPONENT;

   SIGNAL A19	:	STD_LOGIC;
   SIGNAL MIO	:	STD_LOGIC;
   SIGNAL ROMCS	:	STD_LOGIC;
   SIGNAL RAMCS	:	STD_LOGIC;
   SIGNAL UCSA	:	STD_LOGIC;
   SIGNAL UCSB	:	STD_LOGIC;
   SIGNAL UCSC	:	STD_LOGIC;
   SIGNAL UCSD	:	STD_LOGIC;
   SIGNAL AQ	:	STD_LOGIC_VECTOR (15 DOWNTO 0);
   SIGNAL AD	:	STD_LOGIC_VECTOR (15 DOWNTO 0);
   SIGNAL PORTA	:	STD_LOGIC_VECTOR (0 TO 15);
   SIGNAL PORTD	:	STD_LOGIC_VECTOR (0 TO 5);
   SIGNAL PORTE	:	STD_LOGIC_VECTOR (0 TO 15);
   SIGNAL EXTWR	:	STD_LOGIC;
   SIGNAL EXTRD	:	STD_LOGIC;
   SIGNAL PORTC	:	STD_LOGIC_VECTOR (15 DOWNTO 0);
   SIGNAL PORTB	:	STD_LOGIC_VECTOR (5 DOWNTO 0);
   SIGNAL TXA	:	STD_LOGIC;
   SIGNAL TXD	:	STD_LOGIC;
   SIGNAL TXB	:	STD_LOGIC;
   SIGNAL TXC	:	STD_LOGIC;
   SIGNAL ALE	:	STD_LOGIC;
   SIGNAL SYSRESET	:	STD_LOGIC;

BEGIN

   UUT: main PORT MAP(
		A19 => A19, 
		MIO => MIO, 
		ROMCS => ROMCS, 
		RAMCS => RAMCS, 
		UCSA => UCSA, 
		UCSB => UCSB, 
		UCSC => UCSC, 
		UCSD => UCSD, 
		AQ => AQ, 
		AD => AD, 
		PORTA => PORTA, 
		PORTD => PORTD, 
		PORTE => PORTE, 
		EXTWR => EXTWR, 
		EXTRD => EXTRD, 
		PORTC => PORTC, 
		PORTB => PORTB, 
		TXA => TXA, 
		TXD => TXD, 
		TXB => TXB, 
		TXC => TXC, 
		ALE => ALE, 
		SYSRESET => SYSRESET
   );

-- *** Test Bench - User Defined Section ***
   tb : PROCESS
   BEGIN
	
		ALE <= transport '0';
		MIO <= transport '0';
		A19 <= transport '0';
		
		TXA <= transport '0';
		TXB <= transport '0';
		TXC <= transport '0';
		TXD <= transport '0';
		
		PORTA <= "ZZZZZZZZZZZZZZZZ";
		PORTB <= "ZZZZZZ";
		PORTE <= "ZZZZZZZZZZZZZZZZ";
	
		EXTWR <= transport '1';
		EXTRD <= transport '1';
		
		SYSRESET <= transport '0';
		wait for 100ns;
		SYSRESET <= transport '1';
		
		
      wait for 100ns;
		
		--Select UARTA
		AD <= transport x"0020";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		
		--Select UARTB
		AD <= transport x"0028";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		
		--Select UARTC
		AD <= transport x"0030";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		
		--Select UARTD
		AD <= transport x"0038";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		
		-- Set PORTE Output
		AD <= transport x"0012";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport x"0000";
		wait for 100ns;
		EXTWR <= transport '0';
		wait for 100ns;
		EXTWR <= transport '1';
		
		-- Write to PORTC
		AD <= transport x"0008";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport x"3333";
		wait for 100ns;
		EXTWR <= transport '0';
		wait for 100ns;
		EXTWR <= transport '1';
		
		-- Write to PORTD
		AD <= transport x"000A";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport "0000000000111111";
		wait for 100ns;
		EXTWR <= transport '0';
		wait for 100ns;
		EXTWR <= transport '1';
		
		-- Write to PORTE
		AD <= transport x"000C";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport x"A521";
		wait for 100ns;
		EXTWR <= transport '0';
		wait for 100ns;
		EXTWR <= transport '1';
		
		-- Set PORTE Input
		AD <= transport x"0012";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport x"FFFF";
		wait for 100ns;
		EXTWR <= transport '0';
		wait for 100ns;
		EXTWR <= transport '1';
		wait for 100ns;
		
		PORTE <= transport x"a5a5";
		-- Read PORTE
		AD <= transport x"000C";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport "ZZZZZZZZZZZZZZZZ";
		wait for 100ns;
		EXTRD <= transport '0';
		wait for 100ns;
		EXTRD <= transport '1';
		
		-- Set PORTA Output
		AD <= transport x"000E";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport x"0000";
		wait for 100ns;
		EXTWR <= transport '0';
		wait for 100ns;
		EXTWR <= transport '1';
		wait for 100ns;

		-- Write PORTA
		AD <= transport x"0004";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport x"4534";
		wait for 100ns;
		EXTWR <= transport '0';
		wait for 100ns;
		EXTWR <= transport '1';
		
		-- Set PORTA Input
		AD <= transport x"000E";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport x"FFFF";
		wait for 100ns;
		EXTWR <= transport '0';
		wait for 100ns;
		EXTWR <= transport '1';
		wait for 100ns;
		
		PORTA <= transport x"FDFD";
		-- Read PORTA
		AD <= transport x"0004";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport "ZZZZZZZZZZZZZZZZ";
		wait for 100ns;
		EXTRD <= transport '0';
		wait for 100ns;
		EXTRD <= transport '1';
		
		PORTA <= transport x"FFFF";
		PORTB <= transport "110011";
		-- Read PORTB
		AD <= transport x"0006";
		wait for 100ns;
		ALE <= transport '1';
		wait for 100ns;
		ALE <= transport '0';
		wait for 100ns;
		AD <= transport "ZZZZZZZZZZZZZZZZ";
		wait for 100ns;
		EXTRD <= transport '0';
		wait for 100ns;
		EXTRD <= transport '1';
		
		WAIT;
   END PROCESS;
-- *** End Test Bench - User Defined Section ***

END;
