# lisgd

Lisgd (libinput **synthetic** gesture daemon) lets you bind gestures based on
libinput touch events to run specific commands to execute. For example,
dragging left to right with one finger could execute a particular command
like launching a terminal. Directional L-R, R-L, U-D, and D-U gestures and
diagnol LD-RU, RD-LU, UR-DL, UL-DR gestures are supported with 1 through 
n fingers.

Unlike other libinput gesture daemons, lisgd uses touch events to
recognize **synthetic swipe gestures** rather than using the *libinput*'s
gesture events. The advantage of this is that the synthetic gestures
you define via lisgd can be used on touchscreens, which normal libinput
gestures don't support.

This program was built for use on the [Pinephone](https://www.pine64.org/pinephone/);
however it could be used in general for any device that supports touch events,
like laptop touchscreens or similar. You may want to adjust the threshold
depending on the device you're using.

## All credits to the original author/authors.
I was strugging to get a consitent screen rotation/gesture system on my SurfaceBook 2 
running sway. While this is primarily for sway it can be used elsewhere in wayland. 
With the help of Grok, the lisgd binary now follows screen rotation so there is no 
need to kill/restart the process on every rotation/transformation of the screen. 
For my surfacebook 2, the /dev/input/eventXX changes every wake/sleep so I put a 
simple udev rule to map the current eventXX for the Virtual IPTSD device 
to /dev/input/touchscreen. The lisgd code now polls for changes to the inode which 
happens regularly after a sleep/wake cycle. Use iio-sway for rotation.
I have included my config.h so if you don't have a /dev/input/touchscreen put your 
device path.

## Configuration
Configuration can be done in two ways:

1. Through a suckless style `config.h`; see the `config.def.h`
2. Through commandline flags which override the default config.h values

### Suckless-style config.h based configuration
Copy the example `config.def.h` configuration to `config.h`.

### Commandline flags based configuration
Flags:

- **-d [devicenodepath]**: Defines the dev filesystem device to monitor
  - Example: `lisgd -d /dev/input/input1`
- **-g [nfingers,gesture,command]**: Allows you to bind a gesture wherein 
  nfingers is an integer, gesture is one of {LR,RL,DU,UD,DLUR,URDL,ULDR,DLUR},
  and command is the shell command to be executed. The -g option can be used
  multiple times to bind multiple gestures.
  - Single Gesture Example: `lisgd -g "1,LR,notify-send swiped lr"`
  - Multiple Gestures Example: `lisgd -g "1,LR,notify-send swiped lr" -g "1,RL,noitfy-send swiped rl"`
- **-m [timeoutms]**: Number of milliseconds gestures must be performed within 
    to be registered. After the timeoutms value; the gesture won't be registered.
  - Example: `lisgd -m 1200`
- **-o [orientation]**: Number of 90-degree rotations to translate gestures by. 
  Can be set to 0-3. For example using 1; a L-R gesture would become a U-D 
  gesture. Meant to be used for screen-rotation.
  - Example `lisgd -o 1`
- **-r [degrees]**: Number of degrees offset each 45-degree interval may still 
  be recognized within. Maximum value is 45. Default value is 15. E.g. U-D 
  is a 180 degree gesture but with 15 degrees of leniency will be recognized 
  between 165-195 degrees.
  - Example: `lisgd -r 20`
- **-t [threshold_units]**: Threshold in libinput units (pixels) after which a 
  gesture registers. Defaults to 300.
  - Example: `lisgd -t 400`
- **-v**: Verbose mode, useful for debugging
  - Example: `lisgd -v`
