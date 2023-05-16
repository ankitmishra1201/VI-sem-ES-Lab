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

	MOV R0, N
	MLA R1, R0, R0, R0
	LSR R1, #1
	LDR R2, =ARR
	STR R1, [R2]

N EQU 3
	AREA MY_DATA, DATA, READWRITE
ARR DCD 0

	END