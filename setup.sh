mkdir ../myos
unzip bootloader.zip
cp -r bootloader/ ../myos/
rm -Rf bootloader/
unzip modules.zip
cp -r modules/ ../myos/
rm -Rf modules/
mv build.mk ../myos/Makefile
mv ../mykernel/ ../myos/
mv ../myos/mykernel/ ../myos/kernel/