all: clear make 

make: clear
	@cd src;make;cd ..

clear:
	@rm kernel.bin bochsout.txt > /dev/null 2>&1 | true
