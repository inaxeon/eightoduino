
-- VHDL Instantiation Created from source file ioport_16_umux.vhd -- 10:15:48 09/05/2014
--
-- Notes: 
-- 1) This instantiation template has been automatically generated using types
-- std_logic and std_logic_vector for the ports of the instantiated module
-- 2) To use this template to instantiate this entity, cut-and-paste and then edit

	COMPONENT ioport_16_umux
	PORT(
		reset : IN std_logic;
		wr : IN std_logic;
		rd : IN std_logic;
		portcs : IN std_logic;
		triscs : IN std_logic;
		d : IN std_logic_vector(15 downto 0);
		utxa : IN std_logic;
		utxd : IN std_logic;
		uena : IN std_logic;
		uend : IN std_logic;
		clrportint : IN std_logic;    
		ioport : INOUT std_logic_vector(15 downto 0);      
		ioin : OUT std_logic_vector(15 downto 0);
		portint : OUT std_logic
		);
	END COMPONENT;

	Inst_ioport_16_umux: ioport_16_umux PORT MAP(
		reset => ,
		wr => ,
		rd => ,
		portcs => ,
		triscs => ,
		d => ,
		ioin => ,
		ioport => ,
		utxa => ,
		utxd => ,
		uena => ,
		uend => ,
		portint => ,
		clrportint => 
	);


