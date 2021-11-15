###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = STM32F103C6
COMPILER = "Keil for ARM"
TARGET = Debug
SHELL = C:\WINDOWS\system32\cmd.exe

## Tools general options
ASMFLAGS=--cpu=cortex-m3 --thumb -g
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -IC:/Keil_v5/ARM/CMSIS/Include -g
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/Debug/main.o: TOOL=CC
#        G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/main.c
#     G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/Debug/system_stm32f1xx.o: TOOL=CC
#        G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/system_stm32f1xx.c
#     G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/Debug/startup_stm32f103.o: TOOL=ASM
#        G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/startup_stm32f103.s
#     G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/Debug/delay.o: TOOL=CC
#        G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/delay.c
#     G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/Debug/lcd.o: TOOL=CC
#        G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/lcd.c
#     G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/Debug/rlc.o: TOOL=CC
#        G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/rlc.c
#     G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/Debug/rc.o: TOOL=CC
#        G:/Mi unidad/Ing Computacion/Facultad/Cuarto año/Taller de proyecto I/Practica/TP3/Proteusdef/Cap_Ind/STM32F103C6/rc.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o system_stm32f1xx.o startup_stm32f103.o delay.o lcd.o rlc.o rc.o 
	$(LD)  $(LDFLAGS)  "main.o" "system_stm32f1xx.o" "startup_stm32f103.o" "delay.o" "lcd.o" "rlc.o" "rc.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

system_stm32f1xx.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "system_stm32f1xx.o"

startup_stm32f103.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "startup_stm32f103.o"

delay.o:	../delay.c 
	$(CC) $(CCFLAGS)  "../delay.c" -c -o "delay.o"

lcd.o:	../lcd.c 
	$(CC) $(CCFLAGS)  "../lcd.c" -c -o "lcd.o"

rlc.o:	../rlc.c 
	$(CC) $(CCFLAGS)  "../rlc.c" -c -o "rlc.o"

rc.o:	../rc.c 
	$(CC) $(CCFLAGS)  "../rc.c" -c -o "rc.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf system_stm32f1xx.o
	rm -rf startup_stm32f103.o
	rm -rf delay.o
	rm -rf lcd.o
	rm -rf rlc.o
	rm -rf rc.o
