this repo contains some  experimental stuff for (Symbian 9 Kernel) , ekern.lib, ldd ... etc

** EKernCtl:
this is an LDD (logical device driver) which has a function to reboot the device via Kern::Restart(mode)

** Clients  for EKernCtl.ldd :

1) - KRestartModule ,  an mshell module that can be used to restart the kernel

2) - krestart, a native symbian program without gui.


** Resource:

https://github.com/zorn-v/ROMPatcher


https://github.com/d3ru/FShell
