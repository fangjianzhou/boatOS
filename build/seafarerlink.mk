
MAKEFLAGS =

include krnlbuidcmd.mh
include krnlobjs.mkh

.PHONY : all everything build_kernel
all: build_kernel

build_kernel:everything
#$(LDER_EXC_BIN)

everything :   
	$(LD) $(LDFLAGS) 
	$(OBJCOPY) $(OYFLAGS) $(KERNL_MK_ELFF_FILE) $(KERNL_MK_BINF_FILE)
	
#$(BOOT_EXC_ELF) $(BOOT_EXC_BIN)

$(BOOT_EXC_ELF): $(seafarer_LINK_OBJS)
	$(LD) $(LDFLAGS) -o $(BOOT_EXC_ELF)  $(seafarer_LINK_OBJS)
	@echo 'LD -[M] 正在构建...' $@
$(BOOT_EXC_BIN):
	
