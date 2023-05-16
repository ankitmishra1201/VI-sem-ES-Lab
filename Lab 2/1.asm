	AREA RESET, DATA, READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10000100
	DCD Reset_Handler
	
	ALIGN
	
	AREA MY_CODE, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler

;WAALP to add 10 32-bit numbers stored in code segment and store result in data segment

	MOV R0, #0
	MSR xPSR, R0
	MOV R0, #5
	LDR R1, =SRC
	LDR R2, =DST
LOOP LDR R3, [R1], #4
	LDR R4, [R1], #4
	ADDS R5, R4, R3
	ADC R7, #0
	ADDS R6, R5
	ADC R7, #0
	SUBS R0, #1
	BNE LOOP
	STR R6, [R2], #4
	STR R7, [R2]
STOP B STOP
SRC DCD 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF

	AREA MY_DATA, DATA, READWRITE
DST DCD 0, 0

	END