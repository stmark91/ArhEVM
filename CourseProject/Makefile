all:
	rm -f ./bin/s*
	make -C print
	make -C scan
	make -C simpleComputer
	make -C consoleSC
	make -C readKey
	make -C bc
	make -C cpu
	make -C asm
	make -C basic
	make -C main

restruct:
	make clean
	make restruct -C print
	make restruct -C scan
	make restruct -C simpleComputer
	make restruct -C consoleSC
	make restruct -C readKey
	make restruct -C bc
	make restruct -C cpu
	make restruct -C asm
	make restruct -C basic
	make restruct -C main

clean:
	make clean -C print
	make clean -C scan
	make clean -C simpleComputer
	make clean -C consoleSC
	make clean -C readKey
	make clean -C bc
	make clean -C cpu
	make clean -C asm
	make clean -C basic
	make clean -C main
	rm -f ./lib/*.a
