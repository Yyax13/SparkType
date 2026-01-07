BOARD_FQBN 	:= digistump:avr:digispark-tiny
PORT       	:= /dev/hidraw0
BUILD_DIR  	:= build
LIB_DIR    	:= $(CURDIR)/vendor/arduino-libraries
SKETCH     	:= .

all: compile

compile:
	arduino-cli compile \
	--fqbn $(BOARD_FQBN) \
	--libraries $(LIB_DIR) \
	--output-dir $(BUILD_DIR) \
	$(SKETCH)

upload:
	arduino-cli upload \
	--fqbn $(BOARD_FQBN) \
	--port $(PORT) \
	$(SKETCH)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean compile

.PHONY: all compile upload clean rebuild
