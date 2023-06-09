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

	LDR R0, =SRC1
	LDR R0, [R0]
	LDR R1, =SRC2
	LDR R1, [R1]
	MOV R2, #1
MOD0 MUL R3, R2, R0
MOD1 CMP R3, R1
	SUBHI R3, R3, R1
	BLS LCM
	B MOD1
LCM CMP R3, #0
	BEQ EXIT
	ADD R2, #1
	BNE MOD0
EXIT MUL R3, R2, R0
	LDR R4, =ARR
	STR R3, [R4]

SRC1 DCD 0xF
SRC2 DCD 0x19
	AREA MY_DATA, DATA, READWRITE
ARR DCD 0

	END