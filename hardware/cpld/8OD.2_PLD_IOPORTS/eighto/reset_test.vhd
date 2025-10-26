-- Vhdl test bench created from schematic C:\Projects\8086\PLD\eighto\main.sch - Thu Aug 14 06:59:23 2014
--
-- Vhdl test bench created from schematic C:\Projects\8086\PLD\eighto\main.sch - Mon Aug 11 10:09:21 2014
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
ENTITY reset_test IS
END reset_test;
ARCHITECTURE behavioral OF reset_test IS 

COMPONENT main
   PORT( A19	:	IN	STD_LOGIC; 
          MIO	:	IN	STD_LOGIC; 
          ROMCS	:	OUT	STD_LOGIC; 
          RAMCS	:	OUT	STD_LOGIC; 
          UCSA	:	OUT	STD_LOGIC; 
          UCSB	:	OUT	STD_LOGIC; 
          UCSC	:	OUT	STD_LOGIC; 
          UCSD	:	OUT	STD_LOGIC; 
          PORTA	:	INOUT	STD_LOGIC_VECTOR (15 DOWNTO 0); 
		    PORTB	:	INOUT	STD_LOGIC_VECTOR (5 DOWNTO 0); 
			 PORTC	:	OUT	STD_LOGIC_VECTOR (15 DOWNTO 0); 
          PORTD	:	INOUT	STD_LOGIC_VECTOR (15 DOWNTO 0); 
          EXTWR	:	IN	STD_LOGIC; 
          EXTRD	:	IN	STD_LOGIC; 
          TXB	:	IN	STD_LOGIC; 
          TXC	:	IN	STD_LOGIC; 
          AQ	:	OUT	STD_LOGIC_VECTOR (15 DOWNTO 0); 
          AD	:	INOUT	STD_LOGIC_VECTOR (15 DOWNTO 0); 
          ALE	:	IN	STD_LOGIC; 
          SYSRESET	:	IN	STD_LOGIC; 
          BHE	:	IN	STD_LOGIC; 
          ULE	:	OUT	STD_LOGIC; 
          UHE	:	OUT	STD_LOGIC; 
          UDIR	:	OUT	STD_LOGIC; 
          EEWP	:	OUT	STD_LOGIC; 
			 EECS	:	OUT	STD_LOGIC; 
			 ADCS	:	OUT	STD_LOGIC; 
			 SCK	:	OUT	STD_LOGIC; 
			 MOSI	:	OUT	STD_LOGIC; 
          MISO	:	IN	STD_LOGIC; 
          CPUCLK	:	OUT	STD_LOGIC; 
			 IRQ1	:	IN	STD_LOGIC; 
          IRQ2	:	IN	STD_LOGIC; 
          IRQ4	:	IN	STD_LOGIC; 
          IRQ3	:	IN	STD_LOGIC; 
          NMI	:	OUT	STD_LOGIC; 
          MRST	:	OUT	STD_LOGIC; 
          TXD	:	IN	STD_LOGIC; 
          TXA	:	IN	STD_LOGIC; 
          SYSCLK	:	IN	STD_LOGIC; 
          CPU10	:	IN	STD_LOGIC; 
          TEST	:	OUT	STD_LOGIC);
   END COMPONENT;

   SIGNAL A19	:	STD_LOGIC;
   SIGNAL MIO	:	STD_LOGIC;
	SIGNAL EXTRD	:	STD_LOGIC;
   SIGNAL EXTWR	:	STD_LOGIC;
   SIGNAL AD	:	STD_LOGIC_VECTOR (15 DOWNTO 0);
	SIGNAL ALE	:	STD_LOGIC;
	SIGNAL AQ	:	STD_LOGIC_VECTOR (15 DOWNTO 0);
	
   SIGNAL ROMCS	:	STD_LOGIC;
   SIGNAL RAMCS	:	STD_LOGIC;
   SIGNAL UCSA	:	STD_LOGIC;
   SIGNAL UCSB	:	STD_LOGIC;
   SIGNAL UCSC	:	STD_LOGIC;
   SIGNAL UCSD	:	STD_LOGIC;
	
   SIGNAL PORTA	:	STD_LOGIC_VECTOR (15 DOWNTO 0);
   SIGNAL PORTB	:	STD_LOGIC_VECTOR (5 DOWNTO 0);
	SIGNAL PORTC	:	STD_LOGIC_VECTOR (15 DOWNTO 0);
   SIGNAL PORTD	:	STD_LOGIC_VECTOR (15 DOWNTO 0);

   SIGNAL TXA	:	STD_LOGIC;
   SIGNAL TXD	:	STD_LOGIC;
   SIGNAL TXB	:	STD_LOGIC;
   SIGNAL TXC	:	STD_LOGIC;

	SIGNAL SYSCLK	:	STD_LOGIC;
	SIGNAL CPU10	:	STD_LOGIC;
	SIGNAL CPUCLK	:	STD_LOGIC;

   SIGNAL BHE	:	STD_LOGIC;
   SIGNAL ULE	:	STD_LOGIC;
   SIGNAL UHE	:	STD_LOGIC;
   SIGNAL UDIR	:	STD_LOGIC;
   	
   SIGNAL EEWP : STD_LOGIC;
	SIGNAL EECS : STD_LOGIC;
	SIGNAL ADCS : STD_LOGIC;
	SIGNAL SCK : STD_LOGIC;
	SIGNAL MOSI : STD_LOGIC;
   SIGNAL MISO	:	STD_LOGIC;
  
	SIGNAL IRQ1	:	STD_LOGIC;
   SIGNAL IRQ2	:	STD_LOGIC;
   SIGNAL IRQ4	:	STD_LOGIC;
   SIGNAL IRQ3	:	STD_LOGIC;
   SIGNAL NMI	:	STD_LOGIC;
	
   SIGNAL MRST	:	STD_LOGIC;
   SIGNAL SYSRESET	:	STD_LOGIC;
	
   SIGNAL TEST	:	STD_LOGIC;

 
BEGIN

   UUT: main PORT MAP(
		A19 => A19, 
		MIO => MIO, 
		AD => AD, 
		AQ => AQ,
		ROMCS => ROMCS, 
		RAMCS => RAMCS, 
		UCSA => UCSA, 
		UCSB => UCSB, 
		UCSC => UCSC, 
		UCSD => UCSD, 
		PORTA => PORTA, 
		PORTB => PORTB, 
		PORTC => PORTC, 
		PORTD => PORTD, 
		EXTRD => EXTRD, 
		EXTWR => EXTWR, 
		TXA => TXA, 
		TXB => TXB, 
		TXD => TXD, 
		TXC => TXC, 
		ALE => ALE, 
		SYSRESET => SYSRESET, 
		BHE => BHE, 
		ULE => ULE, 
		UHE => UHE, 
		UDIR => UDIR, 
		EEWP => EEWP,
		EECS => EECS,
		ADCS => ADCS,
		SCK => SCK,
		MOSI => MOSI,
		MISO => MISO, 
		CPUCLK => CPUCLK, 
		IRQ1 => IRQ1, 
		IRQ2 => IRQ2, 
		IRQ4 => IRQ4, 
		IRQ3 => IRQ3, 
		NMI => NMI, 
		MRST => MRST, 
		SYSCLK => SYSCLK, 
		CPU10 => CPU10, 
		TEST => TEST
   );

-- *** Test Bench - User Defined Section ***
   tb : PROCESS
	
	procedure WriteWord (ADDR : in STD_LOGIC_VECTOR(15 downto 0);
							DATA : in STD_LOGIC_VECTOR(15 downto 0)) is
	begin
		AD <= transport (others => 'Z');
		SYSCLK <= transport '0';
		wait for 15ns;
		ALE <= transport '1';
		wait for 15ns;
		AD <= transport ADDR;
		wait for 20ns;
		SYSCLK <= transport '1';
		wait for 36ns;
		ALE <= transport '0';
		wait for 14ns;
		SYSCLK <= transport '0';
		wait for 18ns;
		EXTWR <= transport '0';
		wait for 10ns;
		AD <= transport DATA;
		wait for 18ns;
		SYSCLK <= transport '1';
		wait for 50ns;
		SYSCLK <= transport '0';
		wait for 50ns;
		SYSCLK <= transport '1';
		wait for 50ns;
		SYSCLK <= transport '0';
		wait for 25ns;
		EXTWR <= transport '1';
		AD <= transport (others => 'Z');
	end WriteWord;
	
	procedure ReadWord (ADDR : in STD_LOGIC_VECTOR(15 downto 0)) is
	begin
		AD <= transport (others => 'Z');
		SYSCLK <= transport '0';
		wait for 15ns;
		ALE <= transport '1';
		wait for 15ns;
		AD <= transport ADDR;
		wait for 20ns;
		SYSCLK <= transport '1';
		wait for 36ns;
		ALE <= transport '0';
		wait for 14ns;
		SYSCLK <= transport '0';
		wait for 18ns;
		AD <= transport (others => 'Z');
		wait for 10ns;
		EXTRD <= transport '0';
		wait for 18ns;
		SYSCLK <= transport '1';
		wait for 50ns;
		SYSCLK <= transport '0';
		wait for 50ns;
		SYSCLK <= transport '1';
		wait for 50ns;
		SYSCLK <= transport '0';
		wait for 25ns;
		EXTRD <= transport '1';
		AD <= transport (others => 'Z');
	end ReadWord;
	
   BEGIN
	
		ALE <= transport '0';
		MIO <= transport '0';
		A19 <= transport '0';
		BHE <= transport '0';
		
		TXA <= transport '0';
		TXB <= transport '0';
		TXC <= transport '0';
		TXD <= transport '0';
		
		IRQ1 <= transport '0';
		IRQ2 <= transport '0';
		IRQ3 <= transport '0';
		IRQ4 <= transport '0';
		
		CPU10 <= transport '1';
		SYSCLK <= transport '0';
		MISO <= transport '0';
		
		PORTA <= transport (others => '0');
		PORTB <= transport (others => 'Z');
		PORTD <= transport (others => 'Z');
	
		EXTWR <= transport '1';
		EXTRD <= transport '1';
		
		AD <= (others => 'Z');
		
		SYSRESET <= transport '0';
		wait for 100ns;
		SYSRESET <= transport '1';
		wait for 100ns;
		
		WriteWord(x"0002", x"1000");
		
		
		SYSRESET <= transport '0';
		wait for 100ns;
		SYSRESET <= transport '1';
		wait for 100ns;
		
		WAIT; -- will wait forever
		
   END PROCESS;
-- *** End Test Bench - User Defined Section ***

END;
