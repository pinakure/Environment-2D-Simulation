;TurboFX - This module implements fast routines, mainly intended to FX and post processing.

[SECTION .text]

%ifdef WIN32

%macro FUNC 1
[GLOBAL _%1]
_%1:
%endmacro

%else

%macro FUNC 1
[GLOBAL %1]
%1:
%endmacro

%endif

FUNC GetCycles
	rdtsc
	ret
;ret always returns control. return value is stored in EAX

[SECTION .bss]
;define byte (list), terminado en 0 si se usan strings
; db "hello", 0, 45, 23, 0

;	align 16

; Array resb 1
