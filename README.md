# Hardware Abstraction Layer

## Overview
ARM hardware abstraction layer


## Build
Environment setup for QCA4020 dev board SDK
```shell
$ export BOARD_VARIANT = cdb && export RTOS = threadx && expor t CHIPSET_VARIANT = qca4020

$ export PATH=$PATH:$HOME/Downloads/gcc-arm-none-eabi-6-2017-q2-update/bin

$ export TOOLLIBPATH=$HOME/Downloads/gcc-arm-none-eabi-6-2017-q2-update/lib/gcc/arm-none-eabi/6.2.1/thumb/v7e-m/

$ export NEWLIBPATH=$HOME/Downloads/gcc-arm-none-eabi-6-2017-q2-update/arm-none-eabi/lib/thumb/v7e-m/

```


## Overview
`Lastlock` is a device capable of manipulating door lock from a mobile phone through Bluetooth.
Some use cases of a lock:
* `Appartments renting`. Access to apartments can be given automaticaly for a specific time window after 
rental payment have been processed
* Logging/monitoring of a door access. Installed accelerometer can notify in case of
penetration attempt.
The lock can be installed inside, without any traces from outside, though providing extra level of protection. 

User authentification is made by public key cryptography. Keys having tree structure.
User can monitor and disable/enable children keys.
Advanced shared access to resource can be achieved by using multiple root keys
and rules for their activation. Scripting API for automation.


## Roadmap
### v0.1.0 
1. Bluetooth communication.
Broadcast BLE endpoint, send/receive test data packet.

2. PWM motor control.
Driver for motor control.

3. Test setup.
Run unit-test and demo on a host machine(QEMU emulator)

### v0.2.0
1. Operationg mode switching (Normal, Sleep, DeepSleep)
Create driver for utilizing operating modes of aplication logic CPI

2. Demo loop power consumption 
Measure power consumption of demo loop: `Wake Up -> BLE communication -> Open -> Lock -> Deep sleep`

### v0.3.0
1. Multikey 
