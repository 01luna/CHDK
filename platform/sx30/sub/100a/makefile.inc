#PLATFORMID=0x3210
PLATFORMID=12816

PLATFORMOS=dryos

ROMBASEADDR=0xFF810000
MAXRAMADDR=0x07FFFFFF

# Set up size variables for EXMEM
EXMEM_HEAP_SKIP=0x2F7600	#(0x48000000-0x47D08A00) from sub_FF890270 = size of video buffers in EXMEM area
EXMEM_BUFFER_SIZE=0x400000	# Amount of EXMEM memory to allocate for CHDK = 4MB

ifdef OPT_CHDK_IN_EXMEM
MEMISOSTART=0x79089e0		# MAXRAMADDR+1 - EXMEM_HEAP_SKIP - EXMEM_BUFFER_SIZE - 32 (exmem allocates 64 bytes extra, 32 before and 32 after block allocated)
else
MEMISOSTART=0x18122C
endif

NEED_ENCODED_DISKBOOT=5

KEYSYS=d4b

PLATFORMOSVER=45
