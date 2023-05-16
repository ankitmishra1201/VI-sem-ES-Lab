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

;Reverse 10 32-bit numbers in memory

	MOV R0, #5
	LDR R1, =ARR
	LDR R2, =ARR
	LDR R3, [R2], #36
LOOP LDR R3, [R1]
	LDR R4, [R2]
	STR R4, [R1], #4
	STR R3, [R2], #-4
	SUBS R0, #1
	BNE LOOP

	AREA MY_DATA, DATA, READWRITE
ARR DCD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

	END