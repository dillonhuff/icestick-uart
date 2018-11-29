# In case of burn error do:
# sudo kextunload -b com.FTDI.driver.FTDIUSBSerialDriver

PROJ = blinky
BUILD = ./build
DEVICE = 1k
FOOTPRINT = tq144

FILES = top.v

all:
	make clean
	mkdir $(BUILD)
	yosys -p "synth_ice40 -top top -blif $(BUILD)/$(PROJ).blif" $(FILES)
	#arachne-pnr -d $(subst hx,,$(subst lp,,$(DEVICE))) -o $(BUILD)/$(PROJ).asc -p $(BUILD)/$(PROJ).blif
	arachne-pnr -d $(DEVICE) -P $(FOOTPRINT) -o $(BUILD)/$(PROJ).asc -p pinmap.pcf $(BUILD)/$(PROJ).blif
	icepack $(BUILD)/$(PROJ).asc $(BUILD)/$(PROJ).bin


burn:
	~/CppWorkspace/icestorm/iceprog/iceprog  $(BUILD)/$(PROJ).bin

clean:
	rm -rf $(BUILD)
