# Linker Script /Linker Understand
  - gcc -o main main.c
    - readelf -S main
  - gcc -nostartfiles -T link.ld -o main_custom main.c
    - readelf -S main_custom

  # sample Linker Scripting..
      MEMORY
      {
          FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K
          RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
      }
      
      SECTIONS
      {
          /* Set start address */
          . = ORIGIN(FLASH);
      
          /* Place .text in FLASH */
          .text : {
              KEEP(*(.isr_vector))   /* Vector table */
              *(.text*)              /* All code */
              *(.rodata*)            /* Read-only data */
              . = ALIGN(4);
              _etext = .;            /* Symbol marking end of .text */
          } > FLASH
      
          /* Place initialized data in RAM, but load from FLASH */
          .data : AT (ADDR(.text) + SIZEOF(.text)) {
              _sdata = .;            /* Start of .data in RAM */
              *(.data*)
              . = ALIGN(4);
              _edata = .;            /* End of .data in RAM */
          } > RAM
      
          /* Place uninitialized data (zeroed at startup) in RAM */
          .bss (NOLOAD) : {
              _sbss = .;
              *(.bss*)
              *(COMMON)
              . = ALIGN(4);
              _ebss = .;
          } > RAM
      
          /* End of RAM marker */
          _end = .;
      }
      
-------------------------------------------------------------------------------------------------------------
# [test] ../Cortex-A_M_Architecture/linuxKernal_driver/CHAR_DEVICE_DRIVER/gpio_driver  
   - echo 0 <pin-number> /dev/GPIO_koya  /* pin set low */
   - echo 1 <pin-number> /dev/GPIO_koya  /* pin set high */
