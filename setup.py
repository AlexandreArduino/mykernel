import os

os.mkdir("../myos")
os.system("unzip bootloader.zip")
os.system("cp -r bootloader/ ../myos/")
os.system("rm -Rf bootloader/")
os.system("mv build.mk ../myos/Makefile")
os.chdir("../")
os.system("mv mykernel/ myos/")
os.system("mv myos/mykernel/ myos/kernel/")