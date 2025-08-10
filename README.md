# Linker Script /Linker Understand
  - gcc -o main main.c
    - readelf -S main
  - gcc -nostartfiles -T link.ld -o main_custom main.c
    - readelf -S main_custom   
