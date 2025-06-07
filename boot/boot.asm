 [bits 32]

 section .multiboot2
 align 8
     dd 0xe85250d6              ; Multiboot2 magic number
     dd 0                       ; Architecture (0 = i386)
     dd multiboot_end - multiboot_header
     dd -(0xe85250d6 + 0 + (multiboot_end - multiboot_header)) ; checksum = -(magic + arch + length)

 multiboot_header:
     ; End tag (required)
     align 8
     dw 0                       ; type = 0 (end tag)
     dw 0                       ; flags
     dd 8                       ; size = 8
 multiboot_end:

 section .text
 global _start
 extern kernel_main
 extern _stack_top

 ; 64-bit Global Descriptor Table
 gdt64:
     dq 0                            ; Null segment
     dq 0x00af9a000000ffff           ; 0x08: 64-bit Code Segment
     dq 0x00af92000000ffff           ; 0x10: 64-bit Data Segment

 gdt64_ptr:
     dw gdt64_end - gdt64 - 1        ; GDT size (limit)
     dd gdt64                        ; GDT base address
 gdt64_end:

 _start:
     cli                             ; Disable interrupts
     lgdt [gdt64_ptr]                ; Load GDT

     ; Enable PAE (Physical Address Extension)
     mov eax, cr4
     or eax, 1 << 5                  ; Set bit 5 (PAE)
     mov cr4, eax

     ; Enable Long Mode via EFER MSR
     mov ecx, 0xC0000080             ; IA32_EFER MSR
     rdmsr
     or eax, 1 << 8                  ; Set LME (Long Mode Enable)
     wrmsr

     ; Load PML4 into CR3
     mov eax, page_table_l4
     mov cr3, eax

     ; Enable Paging (CR0.PG = 1 and CR0.PE = 1)
     mov eax, cr0
     or eax, 0x80000001              ; Set PG and PE
     mov cr0, eax

     ; Far jump to 64-bit code segment (0x08)
     jmp 0x08:long_mode_entry

 [bits 64]
 long_mode_entry:
     mov rsp, _stack_top             ; Set stack pointer
     call kernel_main                ; Call C kernel entry

 .hang:
     hlt
     jmp .hang

 section .rodata
 align 4096
 page_table_l4:
     dq page_table_pdpt + 0x03       ; PML4 -> PDPT (Present + RW)

 align 4096
 page_table_pdpt:
     dq page_table_pd + 0x03         ; PDPT -> PD (Present + RW)

 align 4096
 page_table_pd:
     dq 0x0000000000000000 + 0x83    ; PD -> 2MB page (Present + RW + PS)
     times 511 dq 0                  ; Fill rest of PD entries with 0