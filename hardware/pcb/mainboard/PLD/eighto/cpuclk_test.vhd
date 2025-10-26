--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   09:49:20 08/12/2014
-- Design Name:   
-- Module Name:   C:/Projects/8086/PLD/eighto/cpuclk_test.vhd
-- Project Name:  eighto
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: cpuclock
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY cpuclk_test IS
END cpuclk_test;
 
ARCHITECTURE behavior OF cpuclk_test IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT cpuclock
    PORT(
         clkin : IN  std_logic;
         clkout : OUT  std_logic;
         reset : IN  std_logic;
         cpud2 : IN  std_logic;
         cpureset : OUT  std_logic;
         cpuready : OUT  std_logic;
         timerclk : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal clkin : std_logic := '0';
   signal reset : std_logic := '0';
   signal cpud2 : std_logic := '0';

 	--Outputs
   signal clkout : std_logic;
   signal cpureset : std_logic;
   signal cpuready : std_logic;
   signal timerclk : std_logic;

   -- Clock period definitions
   constant clkin_period : time := 10 ns;
   constant clkout_period : time := 10 ns;
   constant timerclk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: cpuclock PORT MAP (
          clkin => clkin,
          clkout => clkout,
          reset => reset,
          cpud2 => cpud2,
          cpureset => cpureset,
          cpuready => cpuready,
          timerclk => timerclk
        );

   -- Clock process definitions
   clkin_process :process
   begin
		clkin <= '0';
		wait for clkin_period/2;
		clkin <= '1';
		wait for clkin_period/2;
   end process;
 
	
 
   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clkin_period*100;

      reset <= transport '1';
		wait for 100ns;
		reset <= transport '0';

      wait;
   end process;

END;
