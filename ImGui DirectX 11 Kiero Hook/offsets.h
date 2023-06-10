#pragma once
#define MAX_TELEPORTS 16

// Maximum number of entities to consider.
#define MAX_ENTITIES 64

// Notes:
// Entity types 1 and 7 are players and enemies
// Player x-position in shooting range is -1038 at bottom of stairs.
// Player x-position in shooting range is -1025 at top of stairs.
// Player z-position in shooting range is 4.99 at top of stairs.
// Player z-position in shooting range is 0.68 at step.
// Player z-position in shooting range is -0.14 at bottom.

// Core offsets.
#define OFF_INDEXMODULE 0x45D2230
#define OFF_RLCLIENT 0x468EB28
#define OFF_VIEWMATRIX 0x0468EB28 + 0xB28
#define OFF_CONTROLLER 0x3E42DA8

// Camera offsets.
#define OFF_CAMERA_POS 0x78
#define OFF_CAMERA_YAW 0xc0
#define OFF_CAMERA_PITCH 0xc4

// Crosshair offsets.
#define OFF_CROSSHAIR_POS 0x31EC
#define OFF_CROSSHAIR_YAW 0x336C
#define OFF_CROSSHAIR_PITCH 0x3348

// Entity offsets.
#define OFF_ENTITY_CROSSHAIR 0x630
#define OFF_ENTITY_POS 0x80
#define OFF_ENTITY_ROT_X 0x48
#define OFF_ENTITY_ROT_Z 0x40

// Warp offset.
#define OFF_WARP_POS 0x70

#define LENGTH_CROSSHAIR 6
#define WIDTH_CROSSHAIR 2
#define COLOR_CROSSHAIR COLOR_GREEN