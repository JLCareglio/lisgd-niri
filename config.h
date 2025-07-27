/*
  distancethreshold: Minimum cutoff for a gestures to take effect
  degreesleniency: Offset degrees within which gesture is recognized (max=45)
  timeoutms: Maximum duration for a gesture to take place in miliseconds
  orientation: Number of 90 degree turns to shift gestures by
  verbose: 1=enabled, 0=disabled; helpful for debugging
  device: Path to the /dev/ filesystem device events should be read from
  gestures: Array of gestures; binds num of fingers / gesturetypes to commands
            Supported gestures: SwipeLR, SwipeRL, SwipeDU, SwipeUD,
                                SwipeDLUR, SwipeURDL, SwipeDRUL, SwipeULDRfd
*/

unsigned int distancethreshold = 125;
unsigned int distancethreshold_pressed = 60;
unsigned int degreesleniency = 15;
unsigned int timeoutms = 800;
unsigned int orientation = 0;
unsigned int verbose = 0;
double edgesizeleft = 50.0;
double edgesizetop = 50.0;
double edgesizeright = 50.0;
double edgesizebottom = 50.0;
double edgessizescaling = 1.0;
char *device = "/dev/input/touchscreen";

//Gestures can also be specified interactively from the command line using -g
Gesture gestures[] = {
	/* nfingers, gesturetype, edge, distance, mode, command */
	{1, SwipeRL,   EdgeRight, DistanceAny, ActModeReleased, "swaymsg workspace next"},
	{1, SwipeLR,   EdgeLeft, DistanceAny, ActModeReleased, "swaymsg workspace prev"},
	{1, SwipeUD,   EdgeTop, DistanceAny, ActModeReleased, "nwggrid -client"},
	{1, SwipeDU,   EdgeBottom, DistanceAny, ActModeReleased, "pkill -SIGRTMIN -f wvkbd-mobintl"},
	{2, SwipeUD,   EdgeAny, DistanceAny, ActModeReleased, "sway-interactive-screenshot -s focused-output"},
	{3, SwipeLR,   EdgeAny, DistanceAny, ActModeReleased, "swaymsg layout tabbed"},
	{3, SwipeRL,   EdgeAny, DistanceAny, ActModeReleased, "swaymsg layout toggle split"},
	{4, SwipeUD,   EdgeAny, DistanceAny, ActModeReleased, "swaymsg kill"},
};
