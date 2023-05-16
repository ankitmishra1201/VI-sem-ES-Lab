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

;WAALP to add two 128-bit numbers stored in code segment and store the result in data segment

	MOV R0, #0
	MSR xPSR, R0
	MOV R0, #4
	LDR R1, =SRC1
	LDR R2, =SRC2
	LDR R3, =DST
LOOP LDR R4, [R1], #4
	LDR R5, [R2], #4
	ADCS R6, R5, R4
	STR R6, [R3], #4
	SUB R0, #1
	TEQ R0, #0
	BNE LOOP
	ADC R6, #0
	STR R6, [R3]
STOP B STOP
	
SRC1 DCD 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
SRC2 DCD 0x2, 0, 0, 0

	AREA MY_DATA, DATA, READWRITE
DST DCD 0, 0, 0, 0, 0

	END