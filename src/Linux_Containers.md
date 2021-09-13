# Linux Containers

We will use lxd (LX Demon) and lxc (Linux Container) for creating and managing our Linux Containers

## Installation

On arch linux
```
sudo pacman -S lxc lxd
```

## Setup

### First of all we need to enable lxd and lxc service

On systemd
```
sudo systemctl enable lxd.service lxd.socket lxc.service
```

Enable the control groups PAM module by modifying `/etc/pam.d/system-login` to additionally contain the following line:
```
session    optional   pam_cgfs.so -c freezer,memory,name=systemd,unified
```

Secondly, modify `/etc/lxc/default.conf` to contain the following lines:
```
lxc.idmap = u 0 100000 65536
lxc.idmap = g 0 100000 65536
```

Finally, create both /etc/subuid and /etc/subgid to contain the mapping to the containerized uid/gid pairs for each user who shall be able to run the containers. The example below is simply for the root user (and systemd system unit):

Add folling to `/etc/subuid`
```
root:100000:65536
```

Add following to `/etc/subgid`
```
root:100000:65536
```

## GUI Setup


