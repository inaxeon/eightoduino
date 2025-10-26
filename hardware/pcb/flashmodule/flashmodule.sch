EESchema Schematic File Version 2
LIBS:flashmodule-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:29f400
LIBS:m27c4002
LIBS:28f400
LIBS:flashmodule-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "8OD NOR flash module"
Date ""
Rev ""
Comp "Matthew Millman"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L M27C4002 U2
U 1 1 56347A02
P 7350 3300
F 0 "U2" H 7350 3350 60  0000 C CNN
F 1 "APA-640-T-A" V 7350 2800 60  0000 C CNN
F 2 "DIP40:DIP-40__600" H 7350 3300 60  0001 C CNN
F 3 "" H 7350 3300 60  0000 C CNN
	1    7350 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 56347E36
P 4550 4900
F 0 "#PWR3" H 4550 4650 50  0001 C CNN
F 1 "GND" H 4550 4750 50  0000 C CNN
F 2 "" H 4550 4900 60  0000 C CNN
F 3 "" H 4550 4900 60  0000 C CNN
	1    4550 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 4600 4550 4600
Wire Wire Line
	4450 4700 4550 4700
Connection ~ 4550 4700
$Comp
L GND #PWR5
U 1 1 56347E8F
P 8250 4650
F 0 "#PWR5" H 8250 4400 50  0001 C CNN
F 1 "GND" H 8250 4500 50  0000 C CNN
F 2 "" H 8250 4650 60  0000 C CNN
F 3 "" H 8250 4650 60  0000 C CNN
	1    8250 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 4350 8250 4350
Wire Wire Line
	8250 4350 8250 4650
Wire Wire Line
	8150 4450 8250 4450
Connection ~ 8250 4450
$Comp
L VCC #PWR4
U 1 1 56347EC9
P 8250 2250
F 0 "#PWR4" H 8250 2100 50  0001 C CNN
F 1 "VCC" H 8250 2400 50  0000 C CNN
F 2 "" H 8250 2250 60  0000 C CNN
F 3 "" H 8250 2250 60  0000 C CNN
	1    8250 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 2350 8250 2350
Wire Wire Line
	8250 2350 8250 2250
$Comp
L VCC #PWR2
U 1 1 56347F43
P 4550 2050
F 0 "#PWR2" H 4550 1900 50  0001 C CNN
F 1 "VCC" H 4550 2200 50  0000 C CNN
F 2 "" H 4550 2050 60  0000 C CNN
F 3 "" H 4550 2050 60  0000 C CNN
	1    4550 2050
	1    0    0    -1  
$EndComp
Entry Wire Line
	8400 2550 8500 2450
Wire Wire Line
	8150 2550 8400 2550
Entry Wire Line
	8400 2650 8500 2550
Entry Wire Line
	8400 2750 8500 2650
Entry Wire Line
	8400 2850 8500 2750
Entry Wire Line
	8400 2950 8500 2850
Entry Wire Line
	8400 3050 8500 2950
Entry Wire Line
	8400 3150 8500 3050
Entry Wire Line
	8400 3250 8500 3150
Entry Wire Line
	8400 3350 8500 3250
Entry Wire Line
	8400 3450 8500 3350
Entry Wire Line
	8400 3550 8500 3450
Entry Wire Line
	8400 3650 8500 3550
Entry Wire Line
	8400 3750 8500 3650
Entry Wire Line
	8400 3850 8500 3750
Entry Wire Line
	8400 3950 8500 3850
Entry Wire Line
	8400 4050 8500 3950
Wire Wire Line
	8150 2650 8400 2650
Wire Wire Line
	8400 2750 8150 2750
Wire Wire Line
	8150 2850 8400 2850
Wire Wire Line
	8150 2950 8400 2950
Wire Wire Line
	8400 3050 8150 3050
Wire Wire Line
	8150 3150 8400 3150
Wire Wire Line
	8150 3250 8400 3250
Wire Wire Line
	8400 3350 8150 3350
Wire Wire Line
	8150 3450 8400 3450
Wire Wire Line
	8150 3550 8400 3550
Wire Wire Line
	8150 3650 8400 3650
Wire Wire Line
	8150 3750 8400 3750
Wire Wire Line
	8150 3850 8400 3850
Wire Wire Line
	8150 3950 8400 3950
Wire Wire Line
	8150 4050 8400 4050
Text Label 8200 2550 0    60   ~ 0
D0
Text Label 8200 2650 0    60   ~ 0
D1
Text Label 8200 2750 0    60   ~ 0
D2
Text Label 8200 2850 0    60   ~ 0
D3
Text Label 8200 2950 0    60   ~ 0
D4
Text Label 8200 3050 0    60   ~ 0
D5
Text Label 8200 3150 0    60   ~ 0
D6
Text Label 8200 3250 0    60   ~ 0
D7
Text Label 8200 3350 0    60   ~ 0
D8
Text Label 8200 3450 0    60   ~ 0
D9
Text Label 8200 3550 0    60   ~ 0
D10
Text Label 8200 3650 0    60   ~ 0
D11
Text Label 8200 3750 0    60   ~ 0
D12
Text Label 8200 3850 0    60   ~ 0
D13
Text Label 8200 3950 0    60   ~ 0
D14
Text Label 8200 4050 0    60   ~ 0
D15
Wire Bus Line
	8500 1600 8500 3950
Entry Wire Line
	4700 2500 4800 2400
Wire Wire Line
	4450 2500 4700 2500
Entry Wire Line
	4700 2600 4800 2500
Entry Wire Line
	4700 2700 4800 2600
Entry Wire Line
	4700 2800 4800 2700
Entry Wire Line
	4700 2900 4800 2800
Entry Wire Line
	4700 3000 4800 2900
Entry Wire Line
	4700 3100 4800 3000
Entry Wire Line
	4700 3200 4800 3100
Entry Wire Line
	4700 3300 4800 3200
Entry Wire Line
	4700 3400 4800 3300
Entry Wire Line
	4700 3500 4800 3400
Entry Wire Line
	4700 3600 4800 3500
Entry Wire Line
	4700 3700 4800 3600
Entry Wire Line
	4700 3800 4800 3700
Entry Wire Line
	4700 3900 4800 3800
Entry Wire Line
	4700 4000 4800 3900
Wire Wire Line
	4450 2600 4700 2600
Wire Wire Line
	4700 2700 4450 2700
Wire Wire Line
	4450 2800 4700 2800
Wire Wire Line
	4450 2900 4700 2900
Wire Wire Line
	4700 3000 4450 3000
Wire Wire Line
	4450 3100 4700 3100
Wire Wire Line
	4450 3200 4700 3200
Wire Wire Line
	4700 3300 4450 3300
Wire Wire Line
	4450 3400 4700 3400
Wire Wire Line
	4450 3500 4700 3500
Wire Wire Line
	4450 3600 4700 3600
Wire Wire Line
	4450 3700 4700 3700
Wire Wire Line
	4450 3800 4700 3800
Wire Wire Line
	4450 3900 4700 3900
Wire Wire Line
	4450 4000 4700 4000
Text Label 4500 2500 0    60   ~ 0
D0
Text Label 4500 2600 0    60   ~ 0
D1
Text Label 4500 2700 0    60   ~ 0
D2
Text Label 4500 2800 0    60   ~ 0
D3
Text Label 4500 2900 0    60   ~ 0
D4
Text Label 4500 3000 0    60   ~ 0
D5
Text Label 4500 3100 0    60   ~ 0
D6
Text Label 4500 3200 0    60   ~ 0
D7
Text Label 4500 3300 0    60   ~ 0
D8
Text Label 4500 3400 0    60   ~ 0
D9
Text Label 4500 3500 0    60   ~ 0
D10
Text Label 4500 3600 0    60   ~ 0
D11
Text Label 4500 3700 0    60   ~ 0
D12
Text Label 4500 3800 0    60   ~ 0
D13
Text Label 4500 3900 0    60   ~ 0
D14
Text Label 4500 4000 0    60   ~ 0
D15
Wire Bus Line
	4800 1600 4800 3900
Wire Bus Line
	8500 1600 4800 1600
Entry Wire Line
	2800 2200 2700 2100
Wire Wire Line
	3050 2200 2800 2200
Entry Wire Line
	2800 2300 2700 2200
Entry Wire Line
	2800 2400 2700 2300
Entry Wire Line
	2800 2500 2700 2400
Entry Wire Line
	2800 2600 2700 2500
Entry Wire Line
	2800 2700 2700 2600
Entry Wire Line
	2800 2800 2700 2700
Entry Wire Line
	2800 2900 2700 2800
Entry Wire Line
	2800 3000 2700 2900
Entry Wire Line
	2800 3100 2700 3000
Entry Wire Line
	2800 3200 2700 3100
Entry Wire Line
	2800 3300 2700 3200
Entry Wire Line
	2800 3400 2700 3300
Entry Wire Line
	2800 3500 2700 3400
Entry Wire Line
	2800 3600 2700 3500
Entry Wire Line
	2800 3700 2700 3600
Wire Wire Line
	3050 2300 2800 2300
Wire Wire Line
	2800 2400 3050 2400
Wire Wire Line
	3050 2500 2800 2500
Wire Wire Line
	3050 2600 2800 2600
Wire Wire Line
	2800 2700 3050 2700
Wire Wire Line
	3050 2800 2800 2800
Wire Wire Line
	3050 2900 2800 2900
Wire Wire Line
	2800 3000 3050 3000
Wire Wire Line
	3050 3100 2800 3100
Wire Wire Line
	3050 3200 2800 3200
Wire Wire Line
	3050 3300 2800 3300
Wire Wire Line
	3050 3400 2800 3400
Wire Wire Line
	3050 3500 2800 3500
Wire Wire Line
	3050 3600 2800 3600
Wire Wire Line
	3050 3700 2800 3700
Text Label 3000 2200 2    60   ~ 0
A0
Text Label 3000 2300 2    60   ~ 0
A1
Text Label 3000 2400 2    60   ~ 0
A2
Text Label 3000 2500 2    60   ~ 0
A3
Text Label 3000 2600 2    60   ~ 0
A4
Text Label 3000 2700 2    60   ~ 0
A5
Text Label 3000 2800 2    60   ~ 0
A6
Text Label 3000 2900 2    60   ~ 0
A7
Text Label 3000 3000 2    60   ~ 0
A8
Text Label 3000 3100 2    60   ~ 0
A9
Text Label 3000 3200 2    60   ~ 0
A10
Text Label 3000 3300 2    60   ~ 0
A11
Text Label 3000 3400 2    60   ~ 0
A12
Text Label 3000 3500 2    60   ~ 0
A13
Text Label 3000 3600 2    60   ~ 0
A14
Text Label 3000 3700 2    60   ~ 0
A15
Entry Wire Line
	2700 3700 2800 3800
Entry Wire Line
	2700 3800 2800 3900
Wire Wire Line
	2800 3800 3050 3800
Wire Wire Line
	2800 3900 3050 3900
Text Label 3000 3800 2    60   ~ 0
A16
Text Label 3000 3900 2    60   ~ 0
A17
Entry Wire Line
	6300 2350 6200 2250
Wire Wire Line
	6550 2350 6300 2350
Entry Wire Line
	6300 2450 6200 2350
Entry Wire Line
	6300 2550 6200 2450
Entry Wire Line
	6300 2650 6200 2550
Entry Wire Line
	6300 2750 6200 2650
Entry Wire Line
	6300 2850 6200 2750
Entry Wire Line
	6300 2950 6200 2850
Entry Wire Line
	6300 3050 6200 2950
Entry Wire Line
	6300 3150 6200 3050
Entry Wire Line
	6300 3250 6200 3150
Entry Wire Line
	6300 3350 6200 3250
Entry Wire Line
	6300 3450 6200 3350
Entry Wire Line
	6300 3550 6200 3450
Entry Wire Line
	6300 3650 6200 3550
Entry Wire Line
	6300 3750 6200 3650
Entry Wire Line
	6300 3850 6200 3750
Wire Wire Line
	6550 2450 6300 2450
Wire Wire Line
	6300 2550 6550 2550
Wire Wire Line
	6550 2650 6300 2650
Wire Wire Line
	6550 2750 6300 2750
Wire Wire Line
	6300 2850 6550 2850
Wire Wire Line
	6550 2950 6300 2950
Wire Wire Line
	6550 3050 6300 3050
Wire Wire Line
	6300 3150 6550 3150
Wire Wire Line
	6550 3250 6300 3250
Wire Wire Line
	6550 3350 6300 3350
Wire Wire Line
	6550 3450 6300 3450
Wire Wire Line
	6550 3550 6300 3550
Wire Wire Line
	6550 3650 6300 3650
Wire Wire Line
	6550 3750 6300 3750
Wire Wire Line
	6550 3850 6300 3850
Text Label 6500 2350 2    60   ~ 0
A0
Text Label 6500 2450 2    60   ~ 0
A1
Text Label 6500 2550 2    60   ~ 0
A2
Text Label 6500 2650 2    60   ~ 0
A3
Text Label 6500 2750 2    60   ~ 0
A4
Text Label 6500 2850 2    60   ~ 0
A5
Text Label 6500 2950 2    60   ~ 0
A6
Text Label 6500 3050 2    60   ~ 0
A7
Text Label 6500 3150 2    60   ~ 0
A8
Text Label 6500 3250 2    60   ~ 0
A9
Text Label 6500 3350 2    60   ~ 0
A10
Text Label 6500 3450 2    60   ~ 0
A11
Text Label 6500 3550 2    60   ~ 0
A12
Text Label 6500 3650 2    60   ~ 0
A13
Text Label 6500 3750 2    60   ~ 0
A14
Text Label 6500 3850 2    60   ~ 0
A15
Entry Wire Line
	6200 3850 6300 3950
Entry Wire Line
	6200 3950 6300 4050
Wire Wire Line
	6300 3950 6550 3950
Wire Wire Line
	6300 4050 6550 4050
Text Label 6500 3950 2    60   ~ 0
A16
Text Label 6500 4050 2    60   ~ 0
A17
Wire Bus Line
	6200 3950 6200 1450
Wire Bus Line
	6200 1450 2700 1450
Wire Wire Line
	6550 4350 6200 4350
Text Label 6500 4350 2    60   ~ 0
~CS
Text Label 6500 5250 2    60   ~ 0
~WR
Wire Wire Line
	6550 4450 6200 4450
Text Label 6500 4450 2    60   ~ 0
~RD
Wire Wire Line
	3050 4600 2700 4600
Text Label 3000 4500 2    60   ~ 0
~CS
Wire Wire Line
	3050 4500 2700 4500
Text Label 3000 4700 2    60   ~ 0
~WR
Wire Wire Line
	3050 4700 2700 4700
Text Label 3000 4600 2    60   ~ 0
~RD
Wire Wire Line
	2400 4200 3050 4200
Wire Wire Line
	2400 4200 2400 3900
$Comp
L VCC #PWR1
U 1 1 5634900B
P 2400 3900
F 0 "#PWR1" H 2400 3750 50  0001 C CNN
F 1 "VCC" H 2400 4050 50  0000 C CNN
F 2 "" H 2400 3900 60  0000 C CNN
F 3 "" H 2400 3900 60  0000 C CNN
	1    2400 3900
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 56349190
P 9400 3200
F 0 "C1" H 9425 3300 50  0000 L CNN
F 1 "0.1" H 9425 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 9438 3050 30  0001 C CNN
F 3 "" H 9400 3200 60  0000 C CNN
	1    9400 3200
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR6
U 1 1 563491F7
P 9400 2900
F 0 "#PWR6" H 9400 2750 50  0001 C CNN
F 1 "VCC" H 9400 3050 50  0000 C CNN
F 2 "" H 9400 2900 60  0000 C CNN
F 3 "" H 9400 2900 60  0000 C CNN
	1    9400 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 5634921D
P 9400 3500
F 0 "#PWR7" H 9400 3250 50  0001 C CNN
F 1 "GND" H 9400 3350 50  0000 C CNN
F 2 "" H 9400 3500 60  0000 C CNN
F 3 "" H 9400 3500 60  0000 C CNN
	1    9400 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3500 9400 3350
Wire Wire Line
	9400 3050 9400 2900
$Comp
L 28F400 U1
U 1 1 56367DE3
P 3750 3350
F 0 "U1" H 3750 3250 60  0000 C CNN
F 1 "E28F400CVT" H 3750 3500 60  0000 C CNN
F 2 "TSOP48:TSOP48" H 3750 3350 60  0001 C CNN
F 3 "" H 3750 3350 60  0000 C CNN
	1    3750 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2200 4450 2200
Wire Bus Line
	2700 1450 2700 3800
Wire Wire Line
	4550 4600 4550 4900
$Comp
L CONN_01X03 P1
U 1 1 563854A7
P 6900 5150
F 0 "P1" H 6900 5350 50  0000 C CNN
F 1 "CONN_01X03" V 7000 5150 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03" H 6900 5150 60  0001 C CNN
F 3 "" H 6900 5150 60  0000 C CNN
	1    6900 5150
	1    0    0    1   
$EndComp
$Comp
L CONN_01X03 P2
U 1 1 56385500
P 7800 5150
F 0 "P2" H 7800 5350 50  0000 C CNN
F 1 "CONN_01X03" V 7900 5150 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03" H 7800 5150 60  0001 C CNN
F 3 "" H 7800 5150 60  0000 C CNN
	1    7800 5150
	-1   0    0    1   
$EndComp
Wire Wire Line
	6700 5250 6200 5250
Wire Wire Line
	4800 4400 4450 4400
Wire Wire Line
	4800 4200 4450 4200
Wire Wire Line
	8500 5250 8000 5250
Wire Wire Line
	8500 5050 8000 5050
Wire Wire Line
	6700 5150 6200 5150
Wire Wire Line
	4550 2200 4550 2050
Wire Wire Line
	4450 2300 4700 2300
Text Label 4500 2300 0    60   ~ 0
VPP
Text Label 4500 4200 0    60   ~ 0
~RESET
Text Label 8200 5250 0    60   ~ 0
~RESET
Text Label 8200 5050 0    60   ~ 0
~WP
Text Label 4500 4400 0    60   ~ 0
~WP
Text Label 6500 5150 2    60   ~ 0
VPP
$EndSCHEMATC
