# Packages on Arch

## pacstrap

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

## Utils
- mtpfs	        : Reading and Writing from any MTP device
- ntfs-3g       : NTFS filesystem driver and utilities
- gvfs-mtp      : Virtual filesystem implementation for GIO (MTP backend; Android, media player)
- gvfs-gphoto2  : Virtual filesystem implementation for GIO (gphoto2 backend; PTP camera, MTP media player)
- nfs-utils     : Support programs for Network File Systems
- tlp           : Linux Advanced Power Management
- powertop      : A tool to diagnose issues with power consumption and power management
- python-pip    : The PyPA recommended tool for installing Python packages
- jre8-openjdk          : OpenJDK Java 8 full runtime environment
- jre8-openjdk-headless : OpenJDK Java 8 headless runtime environment
- wget          : Network utility to retrieve files from the Web
- gnome-keyring : Stores passwords and encryption keys

### Arch
```
# Filesystem Support
pacman -S mtpfs ntfs-3g gvfs-mtp gvfs-gphoto2

# Power Management
pacman -S tlp powertop

# Development
pacman -S python-pip jre8-openjdk jre8-openjdk-headless wget gnome-keyring
```


## xorg

- libx11        : X11 client-side library
- xorg-xinit    : X.Org initialisation program
- libxinerama   : X11 Xinerama extension library
- libxft        : FreeType-based font drawing library for X
- xorg-server   : Xorg X server
- xorg-xrandr   : Primitive command line interface to RandR extension
- xorg-xrdb     : X server resource database utility
- xorg-xinput   : Small commandline tool to configure devices
- xorg-xbacklight   : RandR-based backlight control application
- xf86-video-intel  : X.org Intel i810/i830/i915/945G/G965+ video drivers
- xclip             : Command line interface to the X11 clipboard

### Arch
```
pacman -S libx11 xorg-xinit libxinerama libxft xorg-server xorg-xrandr xorg-xrdb xorg-xinput xorg-xbacklight xclip

pacman -S xf86-video-intel

yay -S libxft-bgra-git
```

### Gentoo
```
emerge x11-libs/libX11 x11-base/xorg-server x11-libs/libXrandr x11-libs/libXinerama x11-libs/libXft x11-apps/xinit x11-apps/xrdb x11-apps/mesa-progs x11-apps/xrandr x11-misc/unclutter x11-misc/xclip
```

## Basic

- picom		: X compositor that may fix tearing issues
- unclutter	: A small program for hiding the mouse cursor
- os-prober	: Utility to detect other OSes on a set of drives
- man-db	: A utility for reading man pages
- bash-completion	: Programmable completion for the bash shell
- zsh-completions	: Additional completion definitions for Zsh
- zip,unzip,tar,bzip2,atool,unrar	: Compression utils

### Arch
```
pacman -S picom unclutter os-prober man-db bash-completion zsh-completions
pacman -S atool zip unzip tar bzip2 gzip lzip unrar
```

## Fonts

- noto-fonts        : Google Noto TTF fonts
- noto-fonts-cjk    : Google Noto CJK fonts
- ttf-joypixels     : Emoji as a Service (formerly EmojiOne)

### Arch
`pacman -S noto-fonts ttf-joypixels`

## Music

- alsa-utils    : Advanced Linux Sound Architecture - Utilities
- pulseaudio    : A featureful, general-purpose sound server
- pamixer       : Pulseaudio command-line mixer like amixer
- pulsemixer    : CLI and curses mixer for pulseaudio
- mpd           : Flexible, powerful, server-side application for playing music
- mpc           : Minimalist command line interface to MPD
- ncmpcpp       : terminal music player
- mpv           : video player

### Arch
```
pacman -S alsa-utils pulseaudio pamixer pulsemixer

pacman -S alsa-utils pipewire pipewire-alsa pipewire-pulse pulsemixer pamixer

pacman -S mpd mpc ncmpcpp mpv
```

## Shell

- dash      : POSIX compliant shell that aims to be as small as possible
- dashbinsh : redirects sh to dash (aur package)
- zsh       : advanced and programmable shell

## General

- fd        : find replacement in rust
- ripgrep   : grep replacement in rust
- fzf       : fuzzy finder
- htop      : system manager
- nitrogen  : wallpaper manager
- ranger    : Vim-like file fanager
- pcmanfm   : File manager
- neomutt   : email client
- dunst     : notification demon
- libnotify : notification client
- xarchiver : GTK+ frontend to command line archivers
- xterm     : default terminal for various program
- evince    : document viewer
- sxiv      : image viewer
- ueberzug  : image previewer
- maim      : Utility to take a screenshot using imlib2
- neovim    : text editor
- brave-bin : internet browser
- gparted   : A Partition Magic clone, frontend to GNU Parted

### Arch
```
pacman -S fd ripgrep fzf htop nitrogen ranger pcmanfm dunst libnotify xarchiver xterm evince sxiv ueberzug maim
yay -S neovim-nightly-bin brave-bin
```

## Nvidia

- nvidia-lts
- nvidia-utils
- nvidia-settings
- nvidia-prime
- optimus-manager (yay)

### Arch
```
# For linux lts kernel
pacman -S nvidia-lts nvidia-utils nvidia-settings nvidia-prime

# For latest linux kernel
pacman -S nvidia nvidia-utils nvidia-settings nvidia-prime
```

## Virtual Box

- virtualbox
- virtualbox-host-dkms (for lts and other kernels)
- virtualbox-host-modules-arch (for latest linux kernels)

### Arch
```
# For linux lts kernel
pacman -S virtualbox virtualbox-host-dkms linux-lts-headers

# For latest linux kernel
pacman -S virtualbox virtualbox-host-modules-arch linux-headers

# Add user into `vboxusers` group, here user is `rishav`
gpasswd -a rishav vboxusers

# load the `vboxdrv` module manually
modprobe vboxdrv
```

> Note: If you are on `linux` kernel then make sure you have `linux-headers` installed. Similarly if you are on `linux-lts` kernel then `linux-ltx-headers` should be installed.

## QEMU

- qemu : A generic and open source machine emulator and virtualizer
- vert-manager : Desktop user interface for managing virtual machines

```
pacman -S qemu virt-manager dnsmasq ebtables
```

## Fun

- figlet        :   A program for making large letters out of ordinary text
- cmatrix       :   A curses-based scrolling 'Matrix'-like screen
- neofetch      :   A CLI system information tool

### Arch
```
pacman -S figlet cmatrix neofetch
```

## Latex

- texlive-core  : TeX Live core distribution
- texlive-latexextra : Large collection of add-on packages for LaTeX
- texlive-science    : Typesetting for mathematics, natural and computer sciences
- texlive-publishers : LaTeX classes and packages for specific publishers
- texlive-formatsextra : Collection of extra TeX 'formats'
- pandoc        : Conversion between markup formats

## Development

- redis         : An in-memory database that persists on disk

```
pacman -S redis
```

- postgresql    : Sophisticated object-relational DBMS ([link](https://wiki.archlinux.org/title/PostgreSQL))

```
pacman -S postgresql
sudo -iu postgres       # login as postgres user
initdb --locale=en_US.UTF-8 -E UTF8 -D /var/lib/postgres/data

# start the service
systemctl enable --now postgresql.service
```

## Random

xdotools
tesseract - OCR
