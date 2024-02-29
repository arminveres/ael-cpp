.PHONY: lib comp_cmds

lib:
	cmake -B build \
		-DAEL_USE_PICO_SDK=true \
		-DAEL_BOARD=pico_w
	cmake --build build --parallel

comp_cmds: lib
	ln -sf build/compile_commands.json compile_commands.json
