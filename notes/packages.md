# Packages on Arch

# pacstrap

- base
- linux-lts
- linux-lts-headers
- base-devel
- btrfs
- btrfs-progs
- vim
- networkmanager
- grub
- efibootmgr
- intel-ucode

# xorg

- libx11
- xorg-xinit
- libxinerama
- libxft
- xorg-server
- xorg-xrandr
- xorg-xrdb
- xorg-xinput
- xorg-xbacklight
- xf86-video-intel
- xclip

## Basic

- picom
- unclutter
- os-prober
- man-db
- bash-completion

## Fonts

- noto-fonts        :   google noto fonts
- noto-fonts-cjk    :   google noto fonts full
- tty-joypixels     :   emoji fonts

## Music

- alsa-utils:   alsa utilities
- pulse-audio
- pamixer   :   manage volume through commandline
- pulsemixer:   semi gtk way for volume output and input
- mpd       :   music player demon
- mpc       :   manage music form commandline
- ncmpcpp   :   terminal music player
- mpv       :   video player

## shell

- dash      :   POSIX compliant shell that aims to be as small as possible
- dashbinsh :   redirects sh to dash (aur package)
- zsh       :   advanced and programmable shell

## General

- fd        :   find replacement in rust
- ripgrep   :   grep replacement in rust
- fzf       :   fuzzy finder
- htop      :   system manager
- nitrogen  :   wallpaper manager
- ranger    :   file manager
- neomutt   :   email client
- dnust     :   notification demon
- libnotify :   notification client
- xarchiver :   GTK+ frontend to command line archivers
- xterm     :   default terminal for various program
- evience   :   document viewer

### yay

- neovim    :   text editor
- brave-bin :   internet browser

## Nvidia

- nvidia-lts
- nvidia-utils
- nvidia-settings
- nvidia-prime
- optimus-manager (yay)

## Virtual Box

- virtualbox
- virtualbox-host-dkms (for lts and other kernels)
- virtualbox-host-modules-arch (for latest linux kernels)

Note: If you are on `linux` kernel then make sure you have `linux-headers` installed. Similarly if you are on `linux-lts kernel` then `linux-ltx-headers` should be installed.

## Fun

- figlet        :   write words with style
- cmatrix       :   terminal animation
- neofetch  :   stylish system info
