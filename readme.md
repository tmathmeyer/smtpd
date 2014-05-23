# Synaptic Multi-Touch Parsing Daemon
#### a lightweight daemon for managing multi touch on a synaptic trackpad including support for 3-5 finger swipes in four directions each as well as 3-5 finger tapps

#####SMTPD is not a finished product by any means. While I can be reasonably certain that this wont break anything, you can't take my word for it. 

###TODO:
- daemonisation -> its a bit silly, but this is not yet in deamon form. expect it soon (a week?)
- read from synclient directly, instead of having it piped into stdin
- trackpad size discovery -> right now it needs to be entered manually
- gesture detection -> being able to discern things like swiping in a circle
- detecting dependance on forked synaptic driver (someday i would like to incorperate this into my own fork of that, but I'm going to wait for wayland)

###INSTALATION:
######this is only tested on arch linux. attempt at your own risk
- install the forked version of xf86-synaptics: xf86-input-synaptics-xswipe-git (availible in the aur and github)
- clone this repo
- edit the src/config.h file. defines in the form [ACTION]_[#] "/run/this/script" is an action:
	- each command is executed by system() with no root privelages, so make sure you use either things in your path or give the full path to the script/executable
- edit the heuristics information at the top of the file, some of the information must be obtained from running `~$ synclient`
	- trackpad_width -> this is equal to ABS(trackpad_left - trackpad_right) / 100 (these can be found in the output of synclient)
	- trackpad_height -> this is ABS(trackpad_bottom - trackpad_top) /100 (also from synclient output)
	- trackpad_scale_factor -> this is hueristics, tweak it until you like it. (will be editable throgh a CLI in the future)
	- trackpad_min_duration -> this is the cutof in ms between what is considered a tap and a swipe. tweak this to your liking (will also be in the CLI)
- run `make`
- run `synclient -m 10 | ./smtpd`
- ignore the debug info
