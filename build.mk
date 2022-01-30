all: clean
	cd kernel && make && cd ../bootloader && make && cd ../ && clear && qemu-system-x86_64 -machine q35 -m 60M -smp 1 -cpu qemu64 -serial stdio -no-reboot build/myos.iso
details_boot:
	qemu-system-x86_64 -machine q35 -m 60M -d int -smp 1 -cpu qemu64 -serial stdio -no-reboot -no-shutdown build/myos.iso
clean:
	rm -Rf build/
	mkdir build/
	clear && echo "CLEAN"
