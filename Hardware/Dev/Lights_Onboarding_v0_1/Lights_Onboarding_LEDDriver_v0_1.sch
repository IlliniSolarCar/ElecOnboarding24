EESchema Schematic File Version 4
LIBS:Lights_Onboarding_v0_1-cache
EELAYER 26 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 2 7
Title "Led Driver Sheet"
Date ""
Rev "0.1"
Comp "Illini Solar Car"
Comment1 "Designed By: Jonathan Mullen"
Comment2 "Fa 19 Onboard Project"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ICs:BCR421UW6Q U2
U 1 1 5D39FB9B
P 6100 3400
AR Path="/5D39FB23/5D39FB9B" Ref="U2"  Part="1" 
AR Path="/5D3A07F2/5D39FB9B" Ref="U3"  Part="1" 
AR Path="/5D3A080A/5D39FB9B" Ref="U4"  Part="1" 
AR Path="/5D3A080E/5D39FB9B" Ref="U5"  Part="1" 
AR Path="/5D3B99D2/5D39FB9B" Ref="U6"  Part="1" 
AR Path="/5D3B9D8B/5D39FB9B" Ref="U7"  Part="1" 
F 0 "U?" H 6100 3515 50  0000 C CNN
F 1 "BCR421UW6Q" H 6100 3424 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6_Handsoldering" H 6000 3300 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/BCR421UW6Q.pdf" H 6100 3400 50  0001 C CNN
F 4 "BCR421UW6Q" H 6200 3500 50  0001 C CNN "MPN"
	1    6100 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3550 5200 3550
$Comp
L power:GND #PWR07
U 1 1 5D3A0052
P 6100 4300
AR Path="/5D39FB23/5D3A0052" Ref="#PWR07"  Part="1" 
AR Path="/5D3A07F2/5D3A0052" Ref="#PWR09"  Part="1" 
AR Path="/5D3A080A/5D3A0052" Ref="#PWR011"  Part="1" 
AR Path="/5D3A080E/5D3A0052" Ref="#PWR013"  Part="1" 
AR Path="/5D3B99D2/5D3A0052" Ref="#PWR014"  Part="1" 
AR Path="/5D3B9D8B/5D3A0052" Ref="#PWR016"  Part="1" 
F 0 "#PWR?" H 6100 4050 50  0001 C CNN
F 1 "GND" H 6105 4127 50  0000 C CNN
F 2 "" H 6100 4300 50  0001 C CNN
F 3 "" H 6100 4300 50  0001 C CNN
	1    6100 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 4300 6100 4150
$Comp
L device:R_US R8
U 1 1 5D3A031D
P 5600 3900
AR Path="/5D39FB23/5D3A031D" Ref="R8"  Part="1" 
AR Path="/5D3A07F2/5D3A031D" Ref="R9"  Part="1" 
AR Path="/5D3A080A/5D3A031D" Ref="R10"  Part="1" 
AR Path="/5D3A080E/5D3A031D" Ref="R11"  Part="1" 
AR Path="/5D3B99D2/5D3A031D" Ref="R3"  Part="1" 
AR Path="/5D3B9D8B/5D3A031D" Ref="R4"  Part="1" 
F 0 "R?" H 5668 3946 50  0000 L CNN
F 1 "2.1" H 5668 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5640 3890 50  0001 C CNN
F 3 "~" H 5600 3900 50  0001 C CNN
F 4 "RES SMD 2.1 OHM 1% 1/4W 1206 " H 5600 3900 50  0001 C CNN "MPN"
	1    5600 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3700 5600 3700
Wire Wire Line
	5600 3700 5600 3750
Wire Wire Line
	5600 4050 5600 4150
Wire Wire Line
	5600 4150 6100 4150
Connection ~ 6100 4150
Wire Wire Line
	6100 4150 6100 4050
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5D3A0455
P 7350 3600
AR Path="/5D39FB23/5D3A0455" Ref="J4"  Part="1" 
AR Path="/5D3A07F2/5D3A0455" Ref="J5"  Part="1" 
AR Path="/5D3A080A/5D3A0455" Ref="J6"  Part="1" 
AR Path="/5D3A080E/5D3A0455" Ref="J7"  Part="1" 
AR Path="/5D3B99D2/5D3A0455" Ref="J9"  Part="1" 
AR Path="/5D3B9D8B/5D3A0455" Ref="J10"  Part="1" 
F 0 "J?" H 7450 3500 50  0000 L CNN
F 1 "Conn_01x02" H 7450 3600 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 7350 3600 50  0001 C CNN
F 3 "~" H 7350 3600 50  0001 C CNN
F 4 "22232021" H 7350 3600 50  0001 C CNN "MPN"
	1    7350 3600
	1    0    0    1   
$EndComp
$Comp
L power:+12V #PWR06
U 1 1 5D3A05C1
P 6900 3300
AR Path="/5D39FB23/5D3A05C1" Ref="#PWR06"  Part="1" 
AR Path="/5D3A07F2/5D3A05C1" Ref="#PWR08"  Part="1" 
AR Path="/5D3A080A/5D3A05C1" Ref="#PWR010"  Part="1" 
AR Path="/5D3A080E/5D3A05C1" Ref="#PWR012"  Part="1" 
AR Path="/5D3B99D2/5D3A05C1" Ref="#PWR05"  Part="1" 
AR Path="/5D3B9D8B/5D3A05C1" Ref="#PWR015"  Part="1" 
F 0 "#PWR?" H 6900 3150 50  0001 C CNN
F 1 "+12V" H 6915 3473 50  0000 C CNN
F 2 "" H 6900 3300 50  0001 C CNN
F 3 "" H 6900 3300 50  0001 C CNN
	1    6900 3300
	1    0    0    -1  
$EndComp
Text HLabel 5200 3550 0    50   Input ~ 0
LEDEnable
Text Notes 5050 2800 0    50   ~ 0
LED Driver rated up to 350 ma depending on EN voltage. \nAt 3.3V about 200 mA. At 5V about 275mA 
Wire Wire Line
	7150 3500 6900 3500
Wire Wire Line
	6900 3500 6900 3300
Text Label 6800 3600 0    50   ~ 0
LED_OUT
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D482F09
P 6600 3500
AR Path="/5D39FB23/5D482F09" Ref="#FLG01"  Part="1" 
AR Path="/5D3A07F2/5D482F09" Ref="#FLG02"  Part="1" 
AR Path="/5D3A080A/5D482F09" Ref="#FLG03"  Part="1" 
AR Path="/5D3A080E/5D482F09" Ref="#FLG04"  Part="1" 
AR Path="/5D3B99D2/5D482F09" Ref="#FLG05"  Part="1" 
AR Path="/5D3B9D8B/5D482F09" Ref="#FLG06"  Part="1" 
F 0 "#FLG?" H 6600 3575 50  0001 C CNN
F 1 "PWR_FLAG" H 6600 3674 50  0000 C CNN
F 2 "" H 6600 3500 50  0001 C CNN
F 3 "~" H 6600 3500 50  0001 C CNN
	1    6600 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 3600 6600 3600
Wire Wire Line
	6600 3500 6600 3600
Connection ~ 6600 3600
Wire Wire Line
	6600 3600 7150 3600
$EndSCHEMATC
