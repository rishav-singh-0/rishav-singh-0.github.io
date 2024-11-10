# Introduction to Linux

## What is Operating System ?
An operating system (OS) is system software that manages computer hardware, software resources, and provides common services for computer programs.

## What is Kernel?
The kernel is a part of operating system which has complete control over everything in the system. It is the portion of the operating system code that is always resident in memory,[2] and facilitates interactions between hardware and software components.

## What is [Linux](https://www.kernel.org/linux.html)?
Linux is a clone of the operating system Unix, written from scratch by Linus Torvalds with assistance from a loosely-knit team of hackers across the Net. It aims towards [POSIX](http://get.posixcertified.ieee.org/) and Single UNIX Specification compliance.

## What is [GNU](http://www.gnu.org/)?
GNU is a Unix-like operating system. That means it is a collection of many programs: applications, libraries, developer tools, even games. The development of GNU, started in January 1984, is known as the GNU Project.
The name **"GNU"** is a recursive acronym for **"GNU's Not Unix."**

## What is Shell and Bash?
Shell is a program, which facilitates the interaction between the user and kernel. There are many shells available, like sh, bash, zsh, fish...etc

### Bash
Bash(Bourne-Again SHell) is an sh-compatible command language interpreter that executes commands read from the standard input or from a file.

## What are Process and Daemon?
### Process
A process refers to a program in execution; it’s a running instance of a program. It is made up of the program instruction, data read from files, other programs or input from a system user.

### Daemon
A Daemon is a service process that runs in the background and supervises the system or provides functionality to other processes.
The Daemon is for process wishing to detach themselves from the controlling terminal and run in the background. Most of the time, they are initialized at system startup and then wait in the background until their service is required.
- `syslogd` demon tracks the system information and saves it to log files

## What is Boot Loader or LILO?
LILO (Linux Loader) is a boot loader which loads any OS into main memory so that it can begin its operations. Now, many distributions use GRUB2 as the default boot loader.

# What are the advantage of Linux being open-source?
- Being open-source means its source code is available for everyone. Anyone can contribute, modify, enhance and distribute the code to anyone and for any purpose(under its open-source licence).
- Security is the other main advantage. By making the source available to anyone, security experts can help identify any main security flaws in the operating system. The advantage over operating systems such as Windows is that security flaws are caught before they become an issue for the public.
- Community support

## What are basic components of GNU/Linux OS?
### Kernel
### Shlls & GUI(System libraries)
### System Utilities

## How to check Memory stats and CPU stats?
- `free` command
  - `cat /prog/meminfo`
- `vmstat` command
  - `sar` command

## How to reduce or shrink the size of LVM partition?
Use `lvm`

## File Systems
- ext4, ntfs, btrfs ...

## Functionality of root user
### sudo & su

## What is CLI and GUI?
## What is Swap partition and size?
Swap space/partition is used when System running out of RAM(Random Access Memory) Memory. If the System RAM memory is full and then inactive pages in memory moved into swap space to run the program parallel without interrupting.
- if RAM < 2GB: double of RAM size
- if RAM < 4GB: anywhere around 4 to 6GB
- if RAM > 4GB: 20% of RAM

## How to access partitions under Linux?
- `lsblk` command
- `/dev/device`

## Device naming conventions
Like sda, vda, tty, video, fd, ttyS, lp 

## Permissions
- Read
- Write
- Execute

- `chmod` command
- `chown`

## Groups
- wheel

## Links
### Symbolic/Soft Links
- Source and Destination files will have diffrent inode numbers, permissions, and size
- Both files and directories
- Accross filesystems/partition

### Hard Links

## What is Virtual desktop?
A virtual desktop is a software emulation of a hardware device that runs on a physical or virtual machine at a remote location, hosted either on premises or in the cloud. Enable end users to access their unique desktop environments remotely over a network.

## What does nameless(empty) directory represent?
They serve as an attachment for all other directories, files, drives or devices. Eg. `/mnt`, `/media`.

## Environment Variables
An environment variable is a named object that contains data used by one or more applications. In simple terms, it is a variable with a name and a value. The value of an environmental variable can for example be the location of all executable files in the file system, the default editor that should be used, or the system locale settings.
- `env` command

## Redirection
Pass output of one operation as input to another operation in same command using `>`(greater-than) symbol.

## Searching
- `grep` command
- `find` command

## Terminating processes
- `kill` command

## Browsing within filesystem
- `cd` command
- `ls` command
- `du -sh /dir` to see directory size

## Process status
- `ps` command
- `ps aux`
  - S
  - Z
  - >

## nohup Command
Run a command immune to hangups, with output to a non-tty.
The process receiving the NOHUP signal will be terminated when you log out of the program, which was used to invoke it.

## Partial Backups
## Inode
- Contents of file will be stored in data blocks.
- Information/Metadata about that file will be stored in inode. eg file-size, permissions, owner, group, access time.
- Inode number points to inode table 

## nice Command

## Shadow passwords

## Facts
- Filename can be of maximum 255 characters
- Maximum path of 4096 characters
- Hidden files prifix with `.`(dot)
- Tab key
- Comments with `#` symbols
- Command chaining with `;` symbol

## References

- https://www.tecmint.com/linux-process-management/
