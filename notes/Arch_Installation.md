# Create Bootable usb

`sudo dd bs=4 if=/mnt/Tools/linux/distros/archlinux-2021.02.01-x86_64.iso of=/dev/sdb conv=fdatasync status=progress`

# Verify the boot mode
To verify the boot mode, list the efivars directory:
` ls /sys/firmware/efi/efivars `

If the command shows the directory without error, then the system is booted in UEFI mode. If the directory does not exist, the system may be booted in BIOS (or CSM) mode. If the system did not boot in the mode you desired, refer to your motherboard's manual.


# Connect to the internet
`ip link`
WiFi - `iwctl`

    - device list
    - station device scan
    - station device get-networks
    - station device connect SSID
        SSID is name of your WiFi network (eg. 'Dark Demon')

## Alternate:
`iwctl --passphrase passphrase station device connect SSID`

## Test
`ping gnu.org`


# Update the system clock
`timedatectl set-ntp true`

# Partition the disks
When recognized by the live system, disks are assigned to a block device such as /dev/sda, /dev/nvme0n1 or /dev/mmcblk0. To identify these devices, use lsblk or fdisk.

`fdisk -l`
Results ending in rom, loop or airoot may be ignored.

The following partitions are required for a chosen device:

    - One partition for the root directory /.
    - For booting in UEFI mode: an EFI system partition.
    - If you want to create any stacked block devices for LVM, system encryption or RAID, do it now.

Example look UEFI with GPT

| Mount point           | Partition                 | Partition type        | Suggested size            |
| :-------------------- | :------------------------ | :-------------------  | :-----------------------  |
| /mnt/boot or /mnt/efi | /dev/efi_system_partition | EFI system partition  |	At least 260 MiB        |
| [SWAP]                | /dev/swap_partition       | Linux swap            | More than 512 MiB         |
| /mnt	                | /dev/root_partition       | Linux x86-64 root (/) | Remainder of the device   |

# Format the partitions
Once the partitions have been created, each newly created partition must be formatted with an appropriate file system. For example, to create an Ext4 file system on /dev/root_partition, run:

`mkfs.ext4 /dev/root_partition`

If you created a partition for swap, initialize it with mkswap:

`mkswap /dev/swap_partition`

Note: For stacked block devices replace /dev/*_partition with the appropriate block device path.

# Mount the file systems
Mount the root volume to /mnt. For example, if the root volume is /dev/root_partition:

`mount /dev/root_partition /mnt`
Create any remaining mount points (such as /mnt/efi) using mkdir and mount their corresponding volumes.

If you created a swap volume, enable it with swapon:

`swapon /dev/swap_partition`


# Installation

Update the system by `pacman -Syy`


## Select the mirrors (Optional)
- Install reflector by `pacman -S reflector`

- If you want you can backup default mirror list

`cp /etc/pacman.d/mirrorlist /etc/pacman.d/mirrorlist.bak`

- Getting good mirror list for your location

`reflector -c "IN" -f 12 -l 10 -n 12 --save /etc/pacman.d/mirrorlist`

# Install essential packages

`pacstrap /mnt base linux linux-firmware vim networkmanager grub efibootmgr git`

# Configure the system

## Fstab
Generate an fstab file (use -U to define by UUID):

`genfstab -U /mnt >> /mnt/etc/fstab`

## Chroot
Change root into the new system:

`arch-chroot /mnt`


## Set the time zone:

`ln -sf /usr/share/zoneinfo/Asia/Kolkata /etc/localtime`

- Run hwclock to generate /etc/adjtime:

`hwclock --systohc`

- Edit /etc/locale.gen and uncomment en_US.UTF-8 UTF-8 and other needed locales. Generate the locales by running:

`locale-gen`
- Create the locale.conf file, and set the LANG variable accordingly:

```
/etc/locale.conf
LANG=en_US.UTF-8
```
Network configuration
Create the hostname file:

`vim /etc/hostname`

`myhostname`


Add matching entries to hosts:

`vim /etc/hosts`

```
127.0.0.1	localhost
::1		localhost
127.0.1.1	myhostname.localdomain	myhostname
```

## Initramfs
Creating a new initramfs is usually not required, because mkinitcpio was run on installation of the kernel package with pacstrap.

For LVM, system encryption or RAID, modify mkinitcpio.conf(5) and recreate the initramfs image:

`mkinitcpio -P`

# Set users
- Create root password using `passwd`
- Create normal user

    `usradd -G wheel,audio,video rishav`


# Install Grub Bootloader
We already installed grub and efibootmgr which are necessary to install grub in efi boot filesystem

```
mkdir /boot/efi
mount /dev/sda1 /boot/efi
grub-install --target=x86_64-efi --bootloader-id=GRUB --efi-directory=/boot/efi
grub-mkconfig -o /boot/grub/grub.cfg
```
# Other impoetant things

- Depending on the processor, install the following package:

    -- amd-ucode for AMD processors

    -- intel-ucode for Intel processors.

    `pacman -S intel-ucode`
