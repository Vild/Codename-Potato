all: clear make 

make: clear
	@cd src;make;cd ..

clean:
	@cd src;make clean;cd ..;rm kernel.bin bochsout.txt > /dev/null 2>&1 | true
