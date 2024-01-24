SET PATH=E:\STM32\keil5\keil_v5\ARM\ARMCLANG\Bin;C:\Program Files (x86)\Common Files\Intel\Shared Libraries\redist\intel64_win\compiler;C:\Program Files (x86)\Common Files\Intel\Shared Libraries\redist\intel64\compiler;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\Program Files\Bandizip\;C:\Program Files (x86)\Windows Kits\10\Windows Performance Toolkit\;C:\Program Files\dotnet\;C:\Users\Lihao\AppData\Local\Microsoft\WindowsApps;E:\VS\Microsoft VS Code\bin
SET RVCT0INC=E:\STM32\keil5\keil_v5\ARM\ARMCLANG\include
SET RVCT0LIB=E:\STM32\keil5\keil_v5\ARM\ARMCLANG\lib
SET ARMCC0_ASMOPT=--diag_suppress=9931
SET ARMCC0_CCOPT=--diag_suppress=9931
SET ARMCC0_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F103ZE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Template
SET CPU_CLOCK=0x00B71B00
SET RVCT0INC=E:\STM32\keil5\keil_v5\ARM\ARMCLANG\include
SET RVCT0LIB=E:\STM32\keil5\keil_v5\ARM\ARMCLANG\lib
"E:\STM32\keil5\keil_v5\ARM\ARMCLANG\Bin\ArmAsm" --Via "..\..\output\startup_stm32f103xe._ia"
SET RVCT0INC=E:\STM32\keil5\keil_v5\ARM\ARMCLANG\include
SET RVCT0LIB=E:\STM32\keil5\keil_v5\ARM\ARMCLANG\lib
"E:\STM32\keil5\keil_v5\ARM\ARMCLANG\Bin\ArmCC" --Via "..\..\output\stm32f1xx_it.__i"
SET RVCT0INC=E:\STM32\keil5\keil_v5\ARM\ARMCLANG\include
SET RVCT0LIB=E:\STM32\keil5\keil_v5\ARM\ARMCLANG\lib
"E:\STM32\keil5\keil_v5\ARM\ARMCLANG\Bin\ArmLink" --Via "..\..\Output\atk_f103.lnp"
