# invoke SourceDir generated makefile for main.pe430
main.pe430: .libraries,main.pe430
.libraries,main.pe430: package/cfg/main_pe430.xdl
	$(MAKE) -f C:\MSP430_LaunchPad\Workspace\ScienceFairGrace010214/src/makefile.libs

clean::
	$(MAKE) -f C:\MSP430_LaunchPad\Workspace\ScienceFairGrace010214/src/makefile.libs clean

