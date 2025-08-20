#!/bin/bash
clear

# Banner
cat << "EOF"

           █████╗ ██████╗  ██████╗██╗  ██╗    ██╗     ██╗███╗   ██╗██╗   ██╗██╗  ██╗    ██╗███╗   ██╗███████╗████████╗ █████╗ ██╗     ██╗      █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
          ██╔══██╗██╔══██╗██╔════╝██║  ██║    ██║     ██║████╗  ██║██║   ██║╚██╗██╔╝    ██║████╗  ██║██╔════╝╚══██╔══╝██╔══██╗██║     ██║     ██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
          ███████║██████╔╝██║     ███████║    ██║     ██║██╔██╗ ██║██║   ██║ ╚███╔╝     ██║██╔██╗ ██║███████╗   ██║   ███████║██║     ██║     ███████║   ██║   ██║██║   ██║██╔██╗ ██║
          ██╔══██║██╔══██╗██║     ██╔══██║    ██║     ██║██║╚██╗██║██║   ██║ ██╔██╗     ██║██║╚██╗██║╚════██║   ██║   ██╔══██║██║     ██║     ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
          ██║  ██║██║  ██║╚██████╗██║  ██║    ███████╗██║██║ ╚████║╚██████╔╝██╔╝ ██╗    ██║██║ ╚████║███████║   ██║   ██║  ██║███████╗███████╗██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
          ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝    ╚══════╝╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝    ╚═╝╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝

EOF

echo -e "\n[ INFO ] Launching iwctl to check wireless devices...\n"
iwctl

echo -e "\n[ INFO ] Setting timezone to Asia/Kolkata...\n"
timedatectl set-timezone Asia/Kolkata

echo -e "\n[ INFO ] Updating /etc/pacman.conf settings...\n"
sed -i 's/^\s*ParallelDownloads\s*=\s*[0-9]\+/ParallelDownloads = 16/' /etc/pacman.conf
sed -i '/^\s*#\[multilib\]/, /^\s*#Include = \/etc\/pacman.d\/mirrorlist/ s/^#//' /etc/pacman.conf

echo -e "\n[ INFO ] Updating mirrorlist for India...\n"
reflector --country India --threads 16 --latest 16 --protocol http,https --age 12 --save /etc/pacman.d/mirrorlist

echo -e "\n[ INFO ] Updating system packages...\n"
pacman -Syyu --noconfirm

echo -e "\n[ INFO ] Listing disks...\n"
lsblk

read -p "[ ? ] Enter disk name (e.g., nvme0n1 or sda) : " disk

echo -e "\n[ INFO ] Wiping disk /dev/$disk ...\n"
nvme format /dev/"$disk" --force

echo -e "\n[ INFO ] Creating partitions on /dev/$disk ...\n"
parted -s /dev/"$disk" \
    mklabel gpt \
    mkpart ESP fat32 1MiB 513MiB \
    set 1 esp on \
    mkpart Linux ext4 513MiB 100%

echo -e "\n[ INFO ] Formatting partitions...\n"
mkfs.fat -F 32 /dev/"$disk"p1
mkfs.ext4 /dev/"$disk"p2

echo -e "\n[ INFO ] Mounting partitions...\n"
mount /dev/"$disk"p2 /mnt
mount --mkdir /dev/"$disk"p1 /mnt/boot

echo -e "\n[ INFO ] Installing base system...\n"
pacstrap -K /mnt base

echo -e "\n[ INFO ] Updating mirrorlist inside chroot...\n"
reflector --country India --threads 16 --latest 16 --protocol http,https --age 12 --save /mnt/etc/pacman.d/mirrorlist

echo -e "\n[ INFO ] Generating fstab...\n"
genfstab -U /mnt >> /mnt/etc/fstab

arch-chroot /mnt
