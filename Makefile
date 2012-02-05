all: clear make iso

make: clear
	cd src;make;cd ..

clear:
	@rm iso.iso kernel.bin bochsout.txt| true
