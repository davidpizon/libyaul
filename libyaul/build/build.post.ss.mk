include $(YAUL_INSTALL_ROOT)/share/ip.bin.mk

OUTPUT_FILES= $(SH_PROGRAM).ss
CLEAN_OUTPUT_FILES?= $(OUTPUT_FILES) $(SH_BUILD_PATH)/CART-IP.BIN $(SH_BUILD_PATH)/CART-IP.BIN.map

include $(YAUL_INSTALL_ROOT)/share/build.post.bin.mk

$(SH_PROGRAM).ss: $(SH_BUILD_PATH)/$(SH_PROGRAM).bin $(SH_BUILD_PATH)/CART-IP.BIN
	@printf -- "$(V_BEGIN_YELLOW)$@$(V_END)\n"
	$(ECHO)cat $(SH_BUILD_PATH)/CART-IP.BIN $(SH_BUILD_PATH)/$(SH_PROGRAM).bin > $@

$(SH_BUILD_PATH)/CART-IP.BIN: $(YAUL_INSTALL_ROOT)/share/yaul/ip/ip.sx $(SH_BUILD_PATH)/$(SH_PROGRAM).bin
	$(ECHO)$(YAUL_INSTALL_ROOT)/share/wrap-error $(YAUL_INSTALL_ROOT)/bin/make-ip \
	    "$(SH_BUILD_PATH)/$(SH_PROGRAM).bin" \
		"$(IP_VERSION)" \
		$(IP_RELEASE_DATE) \
		"$(IP_AREAS)" \
		"$(IP_PERIPHERALS)" \
		'"$(IP_TITLE)"' \
		$(IP_MASTER_STACK_ADDR) \
		$(IP_SLAVE_STACK_ADDR) \
		$(IP_1ST_READ_ADDR) \
	    -1 && mv -f $(SH_BUILD_PATH)/IP.BIN $(SH_BUILD_PATH)/CART-IP.BIN