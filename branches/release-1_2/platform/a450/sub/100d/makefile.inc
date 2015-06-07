#3155
PLATFORMID=12629

PLATFORMOS=vxworks

MEMBASEADDR=0x1900
RESTARTSTART=0x50000
MEMISOSTART=0x95730
ROMBASEADDR=0xffc00000
MAXRAMADDR=0xffffff


PLFLAGS=-DMEMBASEADDR=$(MEMBASEADDR) -DMEMISOSTART=$(MEMISOSTART) -DMEMISOSIZE=$(MEMISOSIZE)
PLFLAGS+=-DRESTARTSTART=$(RESTARTSTART)