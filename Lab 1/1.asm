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

;WAALP to transfer a block of 10 32-bit numbers from 1 memory to another, when source and destination blocks are overlapping and non-overlapping.

	MOV R0, #10
	LDR R1, =ARR+36
	LDR R2, =ARR+(36+(N*4))
LOOP LDR R3, [R1], #-4
	STR R3, [R2], #-4
	SUBS R0, #1
	BNE LOOP
STOP B STOP
N EQU 1

	AREA MY_DATA, DATA, READWRITE
ARR DCD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

	END