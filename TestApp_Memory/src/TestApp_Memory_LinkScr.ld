/*******************************************************************/
/*                                                                 */
/* This file is automatically generated by linker script generator.*/
/*                                                                 */
/* Version: Xilinx EDK 10.1.03 EDK_K_SP3.6                                */
/*                                                                 */
/* Copyright (c) 2004 Xilinx, Inc.  All rights reserved.           */
/*                                                                 */
/* Description : PowerPC405 Linker Script                          */
/*                                                                 */
/*******************************************************************/

_STACK_SIZE = DEFINED(_STACK_SIZE) ? _STACK_SIZE : 0x40000;
_HEAP_SIZE = DEFINED(_HEAP_SIZE) ? _HEAP_SIZE : 0x40000;

/* Define Memories in the system */

MEMORY
{
   SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR : ORIGIN = 0x00000000, LENGTH = 0x04000000
   xps_bram_if_cntlr_1 : ORIGIN = 0xFFFE0000, LENGTH = 0x0001FFEC
}

/* Specify the default entry point to the program */

ENTRY(_start)
/* STARTUP(boot.o) */

/* Define the sections, and where they are mapped in memory */

SECTIONS
{
.vectors : {
   __vectors_start = .;
   *(.vectors)
   __vectors_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.text : {
   *(.text)
   *(.text.*)
   *(.gnu.linkonce.t.*)
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.init : {
   KEEP (*(.init))
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.fini : {
   KEEP (*(.fini))
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.rodata : {
   __rodata_start = .;
   *(.rodata)
   *(.rodata.*)
   *(.gnu.linkonce.r.*)
   __rodata_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.rodata1 : {
   __rodata1_start = .;
   *(.rodata1)
   *(.rodata1.*)
   __rodata1_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.sdata2 : {
   __sdata2_start = .;
   *(.sdata2)
   *(.sdata2.*)
   *(.gnu.linkonce.s2.*)
   __sdata2_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.sbss2 : {
   __sbss2_start = .;
   *(.sbss2)
   *(.sbss2.*)
   *(.gnu.linkonce.sb2.*)
   __sbss2_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.data : {
   __data_start = .;
   *(.data)
   *(.data.*)
   *(.gnu.linkonce.d.*)
   __data_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.data1 : {
   __data1_start = .;
   *(.data1)
   *(.data1.*)
   __data1_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.got : {
   *(.got)
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.got1 : {
   *(.got1)
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.got2 : {
   *(.got2)
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.ctors : {
   __CTOR_LIST__ = .;
   ___CTORS_LIST___ = .;
   KEEP (*crtbegin.o(.ctors))
   KEEP (*(EXCLUDE_FILE(*crtend.o) .ctors))
   KEEP (*(SORT(.ctors.*)))
   KEEP (*(.ctors))
   __CTOR_END__ = .;
   ___CTORS_END___ = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.dtors : {
   __DTOR_LIST__ = .;
   ___DTORS_LIST___ = .;
   KEEP (*crtbegin.o(.dtors))
   KEEP (*(EXCLUDE_FILE(*crtend.o) .dtors))
   KEEP (*(SORT(.dtors.*)))
   KEEP (*(.dtors))
   __DTOR_END__ = .;
   ___DTORS_END___ = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.fixup : {
   __fixup_start = .;
   *(.fixup)
   __fixup_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.eh_frame : {
   *(.eh_frame)
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.jcr : {
   *(.jcr)
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.gcc_except_table : {
   *(.gcc_except_table)
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.sdata : {
   __sdata_start = .;
   *(.sdata)
   *(.sdata.*)
   *(.gnu.linkonce.s.*)
   __sdata_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.sbss : {
   __sbss_start = .;
   *(.sbss)
   *(.sbss.*)
   *(.gnu.linkonce.sb.*)
   __sbss_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.tdata : {
   __tdata_start = .;
   *(.tdata)
   *(.tdata.*)
   *(.gnu.linkonce.td.*)
   __tdata_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.tbss : {
   __tbss_start = .;
   *(.tbss)
   *(.tbss.*)
   *(.gnu.linkonce.tb.*)
   __tbss_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.bss : {
   __bss_start = .;
   *(.bss)
   *(.bss.*)
   *(.gnu.linkonce.b.*)
   *(COMMON)
   . = ALIGN(4);
   __bss_end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

/* Generate Stack and Heap Sections */

.stack : {
   _stack_end = .;
   . += _STACK_SIZE;
   . = ALIGN(16);
   __stack = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

.heap : {
   . = ALIGN(16);
   _heap_start = .;
   . += _HEAP_SIZE;
   . = ALIGN(16);
   _heap_end = .;
   _end = .;
} > SDR_SDRAM_CUSTOM_C_MPMC_BASEADDR

}

