mkdir ../myos
unzip bootloader.zip
cp -r bootloader/ ../myos/
rm -Rf bootloader/
mv build.mk ../myos/Makefile
mv ../mykernel/ ../myos/
mv myos/mykernel/ myos/kernel/