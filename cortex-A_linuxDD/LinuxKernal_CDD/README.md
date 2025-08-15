CDD = character device driver
------------------------------------------------------------------------
# [ Virtual Bus Address ] [ actual physical adress]
  not allow linux kernal to directly write to physical address (like: bare metal microcontrol low level driver we are writing.)
  - Kernal space API : "ioremap" ➜ virtual Base address ➜ give link with Base Address(actual physical address )
  - User space API   : "mmap"    ➜ virtual Base address ➜ give link with Base Address(actual physical address )
