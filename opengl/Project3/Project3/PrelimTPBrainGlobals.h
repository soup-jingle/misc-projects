// Patrick Bunetic
// Changes indicated by "[PB]" comment
// added constants pertaining to grass amount/size and concentric circles on which grass patches are made
//////////////////////////////////////////////////////////
// PrelimTPBrainGlobals.h - Global Constant Definitions //
//////////////////////////////////////////////////////////

#ifndef PRELIM_TP_BRAIN_GLOBALS_H

const float PI                      = 3.1415926535f;
const float PI_OVER_180             = 0.0174532925f;           // One degree (in radians).

// Window Position/Resizing Constants
const int   INIT_WINDOW_POSITION[2] = { 50, 50 };
const float ASPECT_RATIO            = 1.5f;
const int   INIT_WINDOW_SIZE[2]     = { 1000, int(1000/ASPECT_RATIO) };
const float FRUSTUM_FIELD_OF_VIEW   = 35.0f;
const float FRUSTUM_NEAR_PLANE      = 0.1f;
const float FRUSTUM_FAR_PLANE       = 100.0f;
const float BACKGROUND_COLOR[3]     = {0.3f, 0.4f, 0.8f};

// Viewer Constants
const float ORIG_VIEWER_AZIMUTH     = 0.0f;                    // Azimuth angle (spherical coordinates).
const float AZIMUTH_INCREMENT       = 3 * PI_OVER_180;         // Left-right arrow-driven azimuth change.
const float ORIG_VIEWER_ELEVATION   = 15 * PI_OVER_180;        // Elevation angle (spherical coordinates).
const float ELEVATION_INCREMENT     = 3 * PI_OVER_180;         // Up-down arrow-driven elevation change.
const float MIN_ELEVATION           = 3 * PI_OVER_180;         // Lower bound on elevation angle.
const float MAX_ELEVATION           = 87 * PI_OVER_180;        // Upper bound on elevation angle.
const float VIEWER_DISTANCE         = 9.0f;	                   // Distance from center of disk

// Lighting Constants
const float LIGHT_0_POSITION[]    = { 0.0f, 3.0f, 0.0f, 0.0f};
const float LIGHT_1_POSITION[]    = { 0.0f, -50.0f, 50.0f, 0.0f};
const float LIGHT_AMBIENT[]       = { 0.8f, 0.8f, 0.8f, 1.0f};
const float LIGHT_DIFFUSE[]       = { 0.9f, 0.9f, 0.9f, 1.0f};
const float LIGHT_SPECULAR[]      = { 1.0f, 1.0f, 1.0f, 1.0f};
const float LIGHT_MODEL_AMBIENT[] = { 0.7f, 0.7f, 0.7f, 1.0f};

// Disk Constants
const int DISK_NUMBER_SLICES     = 72;
const int DISK_NUMBER_LOOPS      = 12;
const float DISK_RADIUS          = 6.0f;
const float DISK_POSITION[3]     = { 0.0f, -0.3f, -6.0f };
const float DISK_COLOR[3]        = { 0.3f, 0.3f, 0.0f };

// Jumping Brain Constants
const int   NBR_JUMPING_BRAINS            = 7;
const float JUMPINGBRAIN_RESCALE          = 10.0f;
const float MIN_VEL_SCALE_FACTOR          = 0.0f;
const float MAX_VEL_SCALE_FACTOR          = 4.0f;
const float VEL_SCALE_FACTOR_INCREMENT    = 0.25f;
const float JUMPINGBRAIN_RADIUS_SIZE      = 0.24f;
const float JUMPINGBRAIN_MIN_HEIGHT		  = -0.25f; // [PB] make constant for all brains
const float JUMPINGBRAIN_COLOR[NBR_JUMPING_BRAINS][3]   = { {0.9f, 0.9f, 0.9f}, {0.9f, 0.3f, 0.3f}, {0.3f, 0.9f, 0.3f},
                                                            {0.3f, 0.3f, 0.9f}, {0.9f, 0.9f, 0.3f}, {0.9f, 0.3f, 0.9f}, {0.3f, 0.9f, 0.9f} };
const float INIT_JUMPINGBRAIN_POSITION[NBR_JUMPING_BRAINS][3] = { { 0.0f, JUMPINGBRAIN_MIN_HEIGHT, -6.0f },
																	{ 0.0f, JUMPINGBRAIN_MIN_HEIGHT, -3.0f }, 
																	{ 2.5f, JUMPINGBRAIN_MIN_HEIGHT, -4.5f }, 
																	{ 2.5f, JUMPINGBRAIN_MIN_HEIGHT, -7.5f }, 
																	{ 0.0f, JUMPINGBRAIN_MIN_HEIGHT, -9.0f }, 
																	{ -2.5f, JUMPINGBRAIN_MIN_HEIGHT, -7.5f }, 
																	{ -2.5f, JUMPINGBRAIN_MIN_HEIGHT, -4.5f } };
const float INIT_JUMPINGBRAIN_ORIENTATION[NBR_JUMPING_BRAINS] = { 0.0f, 45.0f, 180.0f, 225.0f, 90.0f, 270.0f, 135.0f };
const float ORIENTATION_INCREMENT         = 5.0f;
const float JUMPINGBRAIN_SCALE_FACTOR     = 0.3f;
const float JUMPINGBRAIN_PITCH            = 12.0f;
const float JUMPINGBRAIN_ALTITUDE_INC     = 0.03f;
const float JUMPINGBRAIN_PLANAR_INC       = 0.03f;

const float BODY_SPHERE_RADIUS       = 10.0f/JUMPINGBRAIN_RESCALE;
const float BODY_SPHERE_SCALE[]      = {0.6f, 0.8f, 1.0f};
const float BODY_CYLINDER_RADIUS     = 2.25f/JUMPINGBRAIN_RESCALE;
const float BODY_CYLINDER_LENGTH     = 7.0f/JUMPINGBRAIN_RESCALE;
const float BODY_MIN_PITCH           = 90.0f;
const float BODY_MAX_PITCH           = 90.0f;
const float BODY_PITCH_INCREMENT     = 0.0f;

const float SHOULDERS_SPHERE_RADIUS    = 0.3f/JUMPINGBRAIN_RESCALE;
const float SHOULDERS_SPHERE_CENTER[]  = { 0.0f/JUMPINGBRAIN_RESCALE, 5.0f/JUMPINGBRAIN_RESCALE, 7.0f/JUMPINGBRAIN_RESCALE };
const float SHOULDERS_SPHERE_SCALE[]   = {1.0f, 1.0f, 1.0f};
const float SHOULDERS_CYLINDER_RADIUS  = 0.2f/JUMPINGBRAIN_RESCALE;
const float SHOULDERS_CYLINDER_LENGTH  = 8.5f/JUMPINGBRAIN_RESCALE;
const float SHOULDERS_ROLL             = 0.0f;
const float SHOULDERS_MIN_ROLL         = 0.0f;
const float SHOULDERS_MAX_ROLL         = 0.0f;
const float SHOULDERS_ROLL_INCREMENT   = 0.0f;
const float SHOULDERS_YAW              = 0.0f;
const float SHOULDERS_MIN_YAW          = 0.0f;
const float SHOULDERS_MAX_YAW          = 0.0f;
const float SHOULDERS_YAW_INCREMENT    = 0.0f;

const float HUMERUS_SPHERE_RADIUS    = 2.0f/JUMPINGBRAIN_RESCALE;
const float HUMERUS_SPHERE_SCALE[]   = {0.5f, 1.0f, 0.5f};
const float HUMERUS_CYLINDER_RADIUS  = 0.3f/JUMPINGBRAIN_RESCALE;
const float HUMERUS_CYLINDER_LENGTH  = 2.0f/JUMPINGBRAIN_RESCALE;
const float HUMERUS_MIN_PITCH        = -15.0f;
const float HUMERUS_MAX_PITCH        = 15.0f;
const float HUMERUS_PITCH_INCREMENT  = 1.0f;

const float FOREARM_SPHERE_RADIUS    = 1.5f/JUMPINGBRAIN_RESCALE;
const float FOREARM_SPHERE_SCALE[]   = {0.4f, 1.0f, 0.4f};
const float FOREARM_CYLINDER_RADIUS  = 0.3f/JUMPINGBRAIN_RESCALE;
const float FOREARM_CYLINDER_LENGTH  = 1.5f/JUMPINGBRAIN_RESCALE;
const float FOREARM_MIN_PITCH        = 0.0f;
const float FOREARM_MAX_PITCH        = 90.0f;
const float FOREARM_PITCH_INCREMENT  = 3.0f;

const float HAND_SPHERE_RADIUS    = 1.0f/JUMPINGBRAIN_RESCALE;
const float HAND_SPHERE_SCALE[]   = {1.0f, 1.0f, 0.25f};
const float HAND_CYLINDER_RADIUS  = 0.0f/JUMPINGBRAIN_RESCALE;
const float HAND_CYLINDER_LENGTH  = 1.0f/JUMPINGBRAIN_RESCALE;
const float HAND_MIN_PITCH        = -30.0f;
const float HAND_MAX_PITCH        = 0.0f;
const float HAND_PITCH_INCREMENT  = 1.0f;

const float PELVIS_SPHERE_RADIUS    = 0.3f/JUMPINGBRAIN_RESCALE;
const float PELVIS_SPHERE_CENTER[]  = { 0.0f/JUMPINGBRAIN_RESCALE, 6.0f/JUMPINGBRAIN_RESCALE, 0.0f/JUMPINGBRAIN_RESCALE };
const float PELVIS_SPHERE_SCALE[]   = {1.0f, 1.0f, 1.0f};
const float PELVIS_CYLINDER_RADIUS  = 0.2f/JUMPINGBRAIN_RESCALE;
const float PELVIS_CYLINDER_LENGTH  = 12.0f/JUMPINGBRAIN_RESCALE;
const float PELVIS_ROLL             = 0.0f;
const float PELVIS_MIN_ROLL         = 0.0f;
const float PELVIS_MAX_ROLL         = 0.0f;
const float PELVIS_ROLL_INCREMENT   = 0.0f;
const float PELVIS_YAW              = 0.0f;
const float PELVIS_MIN_YAW          = 0.0f;
const float PELVIS_MAX_YAW          = 0.0f;
const float PELVIS_YAW_INCREMENT    = 0.0f;

const float THIGH_SPHERE_RADIUS    = 3.0f/JUMPINGBRAIN_RESCALE;
const float THIGH_SPHERE_SCALE[]   = {0.65f, 1.0f, 0.65f};
const float THIGH_CYLINDER_RADIUS  = 0.25f/JUMPINGBRAIN_RESCALE;
const float THIGH_CYLINDER_LENGTH  = 3.0f/JUMPINGBRAIN_RESCALE;
const float THIGH_MIN_PITCH        = -90.0f;
const float THIGH_MAX_PITCH        = 90.0f;
const float THIGH_PITCH_INCREMENT  = 6.0f;

const float SHIN_SPHERE_RADIUS    = 4.0f/JUMPINGBRAIN_RESCALE;
const float SHIN_SPHERE_SCALE[]   = {0.35f, 1.0f, 0.35f};
const float SHIN_CYLINDER_RADIUS  = 0.25f/JUMPINGBRAIN_RESCALE;
const float SHIN_CYLINDER_LENGTH  = 4.0f/JUMPINGBRAIN_RESCALE;
const float SHIN_MIN_PITCH        = 0.0f;
const float SHIN_MAX_PITCH        = 150.0f;
const float SHIN_PITCH_INCREMENT  = 5.0f;

const float HEEL_SPHERE_RADIUS    = 2.0f/JUMPINGBRAIN_RESCALE;
const float HEEL_SPHERE_SCALE[]   = {0.4f, 1.0f, 0.25f};
const float HEEL_CYLINDER_RADIUS  = 0.25f/JUMPINGBRAIN_RESCALE;
const float HEEL_CYLINDER_LENGTH  = 2.0f/JUMPINGBRAIN_RESCALE;
const float HEEL_MIN_PITCH        = -150.0f;
const float HEEL_MAX_PITCH        = 0.0f;
const float HEEL_PITCH_INCREMENT  = 5.0f;

const float TOE_SPHERE_RADIUS    = 1.0f/JUMPINGBRAIN_RESCALE;
const float TOE_SPHERE_SCALE[]   = {1.0f, 1.0f, 0.25f};
const float TOE_CYLINDER_RADIUS  = 0.0f/JUMPINGBRAIN_RESCALE;
const float TOE_CYLINDER_LENGTH  = 1.0f/JUMPINGBRAIN_RESCALE;
const float TOE_MIN_PITCH        = 0.0f;
const float TOE_MAX_PITCH        = 30.0f;
const float TOE_PITCH_INCREMENT  = 1.0f;

// Material Properties Constants
const float AMBIENT_COEFF  = -1.0f;    // Minimal ambient reflectance.
const float DIFFUSE_COEFF  =  1.0f;    // Maximal diffuse reflectance.
const float SPECULAR_COEFF =  1.0f;    // Maximal specular reflectance.
const float SPECULAR_EXPON = 20.0f;    // Low level of shininess (scale: 0-128).

// Texture-Based Constants
const int   MAX_FILENAME_LENGTH = 20; 
const char  DISK_TEXTURE_FILENAME[MAX_FILENAME_LENGTH] = { "JumpingBrain.bmp" };
// [PB] array of brain textures
const char BRAIN_TEXTURE_FILENAME[NBR_JUMPING_BRAINS][MAX_FILENAME_LENGTH] =
{ "WhiteBrain.bmp", "RedBrain.bmp", "GreenBrain.bmp", "BlueBrain.bmp", "YellowBrain.bmp", "MagentaBrain.bmp", "CyanBrain.bmp" };

// Raindrop-Based Constants
const int   NUMBER_RAINDROPS = 2000;
const float DROP_WIDTH       = 0.5f;
const float DROP_COLOR[]     = { 0.20f, 0.30f, 0.50f };
const float MIN_DROP_DELTA[] = { -0.05f, -0.30f, -0.05f };
const float MAX_DROP_DELTA[] = { 0.05f, -0.10f, 0.05f };

// [PB] Grass constants
/* Feel free to change these three values if there are performance issues */
const int NUMBER_BLADES = 2100;
const int BLADES_PER_PATCH = 25; // arbitrary number
const int NUM_SEG = 10; // Number of line segments per blade. This number may be anywhere from 1 to 10.
					    // 10 Gives it a little downward curl at its end

const float GRASS_WIDTH = 1.0f;
const float GRASS_HEIGHT = 0.81f;
const float COEFFICIENT = 6;	// arbitrary number; makes grass grow more up than sideways
const float FACTOR = 0.04f; // this is tied closely to the coefficient, 1/10 the square root of height/coefficient
							//     (1/10 because the max number of segments is 10)
const float GRASS_HEIGHT_CORRECTION = DISK_POSITION[1];
const float GRASS_Z_CORRECTION = DISK_POSITION[2];

const float GRASS_COLOR[] = { 0.1f, 0.5f, 0.3f };
const float PATCH_DISTANCE = 1.3f;	// The concentric circles on which patches lie have circumference C
									// N = floor(C / PATCH_DISTANCE) : number of patches
									// (360 / N) : how many degrees apart each patch is
const int NUM_CONC_CIRC = 7.0f;
const float PATCH_RADIUS = 6.0f / NUM_CONC_CIRC; // radius of concentric circles on which patches of grass lie
const float INNER_RADIUS = PATCH_DISTANCE / (NUM_CONC_CIRC * 2);

#define PRELIM_TP_BRAIN_GLOBALS_H
#endif