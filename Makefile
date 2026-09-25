BOARD_PORT ?= /dev/ttyUSB0
FQBN = esp32:esp32:esp32

.PHONY: logs
logs:
	arduino-cli monitor -p $(BOARD_PORT) --config 115200

.PHONY: logs-raw
logs-raw:
	stty -F $(BOARD_PORT) 115200 raw -echo 2>/dev/null; timeout 8 cat $(BOARD_PORT) 2>&1

.PHONY: build
build: 
	arduino-cli compile --fqbn $(FQBN) ./src 2>&1 | tail -15

.PHONY: upload
upload:
	arduino-cli upload -p $(BOARD_PORT) --fqbn $(FQBN) ./src 2>&1 | tail -5

.PHONY: deploy
deploy: build upload

