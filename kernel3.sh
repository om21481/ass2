#!/bin/bash
mkdir new_kernel3

cd new_kernel3

uname -mrs

wget --no-check-certificate https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.19.9.tar.xz

unxz -v linux-5.19.9.tar.xz
tar xvf linux-5.19.9.tar

cd linux-5.19.9

make mrproper

wget --no-check-certificate https://raw.githubusercontent.com/om21481/linux-kernel/main/config-rev-9-gold

mv config-rev-9-gold .config

make
make modules
make modules_install

cp -v arch/x86/boot/bzImage /boot/vmlinuz-linux_hocus_pocus3

ls /usr/lib/modules

mkinitcpio -k 5.19.9 -g /boot/initramfs-linux_hocus_pocus3.img

grub-mkconfig -o /boot/grub/grub.cfg
reboot

cd ..

cd ..

rm -r new_kernel3