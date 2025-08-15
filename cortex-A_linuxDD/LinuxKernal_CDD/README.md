CDD = character device driver
------------------------------------------------------------------------
# [ Virtual Bus Address ] [ actual physical adress]
  not allow linux kernal to directly write to physical address (like: bare metal microcontrol low level driver we are writing.)
  - [x] Interatcing With Physical Base Address via Kernal/User Space ?
   
```mermaid
graph BT;
    Kernal-space --> ioreamp;
    User-space --> mmap;
    Kernal-space  --> System-Calls
    System-Calls  --> User-space
    ioreamp -.-> virtual-Base-Address
    mmap -.-> virtual-Base-Address
    virtual-Base-Address --> Interact_with_Physical_address
style Kernal-space fill:#f00,stroke:#ff0,stroke-width:2px, color:#fff
style User-space fill:#0f0,stroke:#ff0,stroke-width:2px, color:#000
style virtual-Base-Address fill:#ff0,stroke:#ff0,stroke-width:2px, color:#000
```
