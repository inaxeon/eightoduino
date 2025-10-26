
-- 8OD LCD Halfshield CPLD
-- by Matthew Millman

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity halfshield is
    Port (
			  AD : inout STD_LOGIC_VECTOR (7 downto 0);
			  A : in  STD_LOGIC_VECTOR (15 downto 8);
			  RDn : in  STD_LOGIC;
			  WRn : in  STD_LOGIC;
			  ALE : in  STD_LOGIC;
			  DTR : in  STD_LOGIC;
			  RSTn : in  STD_LOGIC;
			  CLK : in  STD_LOGIC;
			  IRDY : out  STD_LOGIC;
           LCD_E1 : out  STD_LOGIC;
			  LCD_E2 : out  STD_LOGIC;
			  LCD_RS : out  STD_LOGIC;
			  LCD_RW : out  STD_LOGIC;
			  LCD_BL : out  STD_LOGIC;
			  SP1 : out  STD_LOGIC);
end halfshield;

architecture Behavioral of halfshield is
signal AQ : std_logic_vector(7 downto 0);
signal RD : std_logic;
signal WR : std_logic;
signal BL : std_logic;
signal BLCS : std_logic;
signal LCD1CS : std_logic;
signal LCD2CS : std_logic;
signal RST : std_logic;
signal AST : std_logic;
signal COUNT0 : STD_LOGIC_VECTOR (1 downto 0);
signal RDYLOCK : std_logic;
signal TMRUN : std_logic;

-- IRDY is asserted for 2 cycles of PCLK, which by the time 8OD's main CPLD has finished
-- re-synchronising the RDY signal, will stretch the bus access from 190nS to around 250nS
-- when the 8086 is clocked at 10MHz. Enough to meet the HD44780's 230nS minumum @ 5V VCC
constant IRDY_TC : STD_LOGIC_VECTOR (1 downto 0) := "10";
signal IRDYOVERFLOW : std_logic;
begin
	
	RD <= (not RDn);
	WR <= (not WRn);
	RST <= (not RSTn);
	
	process(ALE, AD)
		begin
		if (ALE = '1') then 
			AQ <= AD;
		end if;
	end process;
	
	-- Intel to Motorola bus conversion
	LCD_RW <= (not DTR);
	LCD_RS <= AQ(0);
	
	LCD1CS <= (not AQ(2)) and (not AQ(1));
	LCD2CS <= (not AQ(2)) and (AQ(1));
	BLCS <= AQ(2) and (not AQ(1) and (not AQ(0)));
	
	LCD_E1 <= ((WR or RD) and LCD1CS);
	LCD_E2 <= ((WR or RD) and LCD2CS);
	
	-- Backlight register (write)
	process(BLCS, WR, AD)
	begin
		if (BLCS = '1' and WR = '1') then
			BL <= AD(0);
		end if;
	end process;

	LCD_BL <= BL;
	
	-- Backlight register (read)
	process (BLCS, RD, BL)
	begin
		if (BLCS = '1' and RD = '1') then
			AD(7 downto 1) <= "0000000";
			AD(0) <= BL;
		else
			AD(7 downto 0) <= "ZZZZZZZZ";
		end if;
	end process;
	
	-- IRDY Generator
	process (CLK, AST, ALE, IRDYOVERFLOW)
	begin
		if (ALE = '1' or IRDYOVERFLOW = '1') then
			TMRUN <= '0';
		elsif (rising_edge(CLK)) then
			if (AST = '1' and RDYLOCK = '0') then
				TMRUN <= '1';
			end if;
		end if;
	end process;

	process (CLK, ALE)
	begin
		if (ALE = '1') then
			RDYLOCK <= '0';
		elsif (rising_edge(CLK)) then
			if (TMRUN = '1') then
				RDYLOCK <= '1';
			end if;
		end if;
	end process;

	process (CLK, AST) is  
	begin
		if (ALE = '1') then
			COUNT0 <= (others => '0');
		elsif (rising_edge (CLK)) then
			if (TMRUN = '1') then
				COUNT0 <= std_logic_vector(unsigned(COUNT0) + 1);
			end if;
		end if;
	end process;

	AST <= (RD or WR);
	IRDYOVERFLOW <= '1' when COUNT0 = IRDY_TC else '0';
	IRDY <= not TMRUN;
	
end Behavioral;

