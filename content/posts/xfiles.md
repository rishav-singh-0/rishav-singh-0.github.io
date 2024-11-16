## .xinitrc
The ~/.xinitrc file is a shell script read by xinit and by its front-end
startx. It is mainly used to execute desktop environments, window managers and
other programs when starting the X server (e.g., starting daemons and setting
environment variables).

## .xprofiles
An xprofile file, ~/.xprofile and /etc/xprofile, allows you to execute commands
at the beginning of the X user session - before the window manager is started.

## .Xresources
Xresources is a user-level configuration dotfile, typically located at
~/.Xresources. It can be used to set X resources, which are configuration
parameters for X client applications. (xrdb ~/.Xresources)

## .profile
Runs on each login
