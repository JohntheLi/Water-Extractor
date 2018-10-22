#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/grace_2_20_01_12/packages;C:/ti/ccsv5/ccs_base/msp430/msp430ware_1_40_01_44/packages;C:/ti/ccsv5/ccs_base;C:/MSP430_LaunchPad/Workspace/ScienceFairGrace010214/.config
override XDCROOT = C:/ti/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/grace_2_20_01_12/packages;C:/ti/ccsv5/ccs_base/msp430/msp430ware_1_40_01_44/packages;C:/ti/ccsv5/ccs_base;C:/MSP430_LaunchPad/Workspace/ScienceFairGrace010214/.config;C:/ti/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif
