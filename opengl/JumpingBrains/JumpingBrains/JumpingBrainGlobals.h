// Patrick Bunetic
// Changes indicated with [PB]

///////////////////////////////////////////////////////
// JumpingBrainGlobals.h - Global Constant Definitions //
///////////////////////////////////////////////////////

#ifndef JUMPING_BRAIN_GLOBALS_H

const float PI = 3.1415926535f;

// Window Position/Resizing Constants
const int   INIT_WINDOW_POSITION[2] = { 50, 50 };
const float ASPECT_RATIO            = 1.0f;
const int   INIT_WINDOW_SIZE[2]     = { 900, int(900/ASPECT_RATIO) };
const float FRUSTUM_FIELD_OF_VIEW   = 35.0f;
const float FRUSTUM_NEAR_PLANE      = 0.1f;
const float FRUSTUM_FAR_PLANE       = 200.0f; // [PB] changed
const float BACKGROUND_COLOR[3]     = {0.3f, 0.4f, 0.8f};

// Lighting Constants
const float LIGHT_0_POSITION[]    = { 0.0f, 3.0f, 0.0f, 0.0f};
const float LIGHT_1_POSITION[]    = { 0.0f, -50.0f, 50.0f, 0.0f};
const float LIGHT_AMBIENT[]       = { 0.8f, 0.8f, 0.8f, 1.0f};
const float LIGHT_DIFFUSE[]       = { 0.9f, 0.9f, 0.9f, 1.0f};
const float LIGHT_SPECULAR[]      = { 1.0f, 1.0f, 1.0f, 1.0f};
const float LIGHT_MODEL_AMBIENT[] = { 0.7f, 0.7f, 0.7f, 1.0f};

// Viewer Positioning Constants
const float VIEWER_DISTANCE         = 60.0f; // [PB] changed
const float INITIAL_VIEWER_AZIMUTH = PI / 2.0f;// 0.0f;
const float INITIAL_VIEWER_ALTITUDE = 3*(PI / 2.0f)/4; // [PB] changed
const float VIEWER_ANGLE_INCREMENT  = PI / 60.0f;

// [PB]
// Disk Constants
const double DISK_RADIUS		= 24;
const int DISK_SLICES			= 64;
const int DISK_LOOPS			= 8;
const float DISK_COLOR[3]		= { 0.7f, 0.7f, 0.0f };
const float DISK_POSITION[3]	= { 0.0f, 0.0f, 0.0f };

// [PB]
// Jumping Brain Jump Constants
const float JUMP_MIN = 0.0f;
const float JUMP_HEIGHT = 9.0f;
const float JUMP_INCREMENT = 0.3f;
const float JUMP_DISTANCE_INCREMENT = 0.1f;
const float ROTATION_VELOCITY_FACTOR = 1.0f;

// [PB] Jumping Brain Color Constants
const float COLOR_RED[3] = { 1.0f, 0.0f, 0.0f };
const float COLOR_GREEN[3] = { 0.0f, 1.0f, 0.0f };
const float COLOR_BLUE[3] = { 0.0f, 0.0f, 1.0f };
const float COLOR_YELLOW[3] = { 1.0f, 1.0f, 0.0f };
const float COLOR_MAGENTA[3] = { 1.0f, 0.0f, 1.0f };
const float COLOR_CYAN[3] = { 0.0f, 1.0f, 1.0f };
const float COLOR_WHITE[3] = { 1.0f, 1.0f, 1.0f };

// [PB]
// 'Texture' Spheres Constants
const float BUMP_RADIUS = 1.0f; // initially was set to '0.5' which looked close to the version in the specs.
								// using '1.0' makes it look more brain-like, though	

// [PB] Jumping Brain Rotation/Position Constants
// These are arrays, so BRAIN_ROTATION[i] refers to the rotation of 'brains[i]'
//    where 'brains' is the array of JumpingBrain in main (an so on, for the other arrays).
const int BRAIN_ROTATION[7]		= { 0, 50, 100, 150, 200, 250, 300 };
const float BRAIN_X_POSITION[7] = { 13.0f, 12.0f, -4.0f, 7.0f, -5.0f, 1.0f, 18.0f };
const float BRAIN_Z_POSITION[7] = { -9.0f, 12.0f, -10.0f, 3.0f, 20.0f, 4.0f, -12.0f };

const float BRAIN_SCALE_FACTOR = 1.0f;

// Jumping Brain Constants
const float JUMPINGBRAIN_RESCALE          = 4.0f;
const float MIN_VEL_SCALE_FACTOR          = 2.0f; // [PB] changed
const float MAX_VEL_SCALE_FACTOR          = 4.0f;
const float VEL_SCALE_FACTOR_INCREMENT    = 2.0f; // [PB] changed
const float JUMPINGBRAIN_RADIUS_SIZE      = 0.24f;
const float JUMPINGBRAIN_COLOR[3]         = {0.3f, 0.6f, 0.3f};
const float JUMPINGBRAIN_POSITION[]       = { 0.0f, 0.0f, 0.0f };

const float BODY_SPHERE_RADIUS       = 10.0f/JUMPINGBRAIN_RESCALE;
const float BODY_SPHERE_SCALE[]      = {0.6f, 0.8f, 1.0f};
const float BODY_SPHERE_COLOR[]      = {1.0f, 1.0f, 1.0f};
const float BODY_CYLINDER_RADIUS     = 2.25f/JUMPINGBRAIN_RESCALE;
const float BODY_CYLINDER_LENGTH     = 7.0f/JUMPINGBRAIN_RESCALE;
const float BODY_CYLINDER_COLOR[]    = {1.0f, 1.0f, 1.0f};
const float BODY_MIN_PITCH           = 90.0f;
const float BODY_MAX_PITCH           = 90.0f;
const float BODY_PITCH_INCREMENT     = 0.0f;

const float SHOULDERS_SPHERE_RADIUS    = 0.3f/JUMPINGBRAIN_RESCALE;
const float SHOULDERS_SPHERE_CENTER[]  = { 0.0f/JUMPINGBRAIN_RESCALE, 5.0f/JUMPINGBRAIN_RESCALE, 7.0f/JUMPINGBRAIN_RESCALE };
const float SHOULDERS_SPHERE_SCALE[]   = {1.0f, 1.0f, 1.0f};
const float SHOULDERS_SPHERE_COLOR[]   = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float SHOULDERS_CYLINDER_RADIUS  = 0.2f/JUMPINGBRAIN_RESCALE;
const float SHOULDERS_CYLINDER_LENGTH  = 8.5f/JUMPINGBRAIN_RESCALE;
const float SHOULDERS_CYLINDER_COLOR[] = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
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
const float HUMERUS_SPHERE_COLOR[]   = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float HUMERUS_CYLINDER_RADIUS  = 0.3f/JUMPINGBRAIN_RESCALE;
const float HUMERUS_CYLINDER_LENGTH  = 2.0f/JUMPINGBRAIN_RESCALE;
const float HUMERUS_CYLINDER_COLOR[] = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float HUMERUS_MIN_PITCH        = -15.0f;
const float HUMERUS_MAX_PITCH        = 15.0f;
const float HUMERUS_PITCH_INCREMENT  = 1.0f;

const float FOREARM_SPHERE_RADIUS    = 1.5f/JUMPINGBRAIN_RESCALE;
const float FOREARM_SPHERE_SCALE[]   = {0.4f, 1.0f, 0.4f};
const float FOREARM_SPHERE_COLOR[]   = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float FOREARM_CYLINDER_RADIUS  = 0.3f/JUMPINGBRAIN_RESCALE;
const float FOREARM_CYLINDER_LENGTH  = 1.5f/JUMPINGBRAIN_RESCALE;
const float FOREARM_CYLINDER_COLOR[] = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float FOREARM_MIN_PITCH        = 0.0f;
const float FOREARM_MAX_PITCH        = 90.0f;
const float FOREARM_PITCH_INCREMENT  = 3.0f;

const float HAND_SPHERE_RADIUS    = 1.0f/JUMPINGBRAIN_RESCALE;
const float HAND_SPHERE_SCALE[]   = {1.0f, 1.0f, 0.25f};
const float HAND_SPHERE_COLOR[]   = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float HAND_CYLINDER_RADIUS  = 0.0f/JUMPINGBRAIN_RESCALE;
const float HAND_CYLINDER_LENGTH  = 1.0f/JUMPINGBRAIN_RESCALE;
const float HAND_CYLINDER_COLOR[] = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float HAND_MIN_PITCH        = -30.0f;
const float HAND_MAX_PITCH        = 0.0f;
const float HAND_PITCH_INCREMENT  = 1.0f;

const float PELVIS_SPHERE_RADIUS    = 0.3f/JUMPINGBRAIN_RESCALE;
const float PELVIS_SPHERE_CENTER[]  = { 0.0f/JUMPINGBRAIN_RESCALE, 6.0f/JUMPINGBRAIN_RESCALE, 0.0f/JUMPINGBRAIN_RESCALE };
const float PELVIS_SPHERE_SCALE[]   = {1.0f, 1.0f, 1.0f};
const float PELVIS_SPHERE_COLOR[]   = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float PELVIS_CYLINDER_RADIUS  = 0.2f/JUMPINGBRAIN_RESCALE;
const float PELVIS_CYLINDER_LENGTH  = 12.0f/JUMPINGBRAIN_RESCALE;
const float PELVIS_CYLINDER_COLOR[] = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
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
const float THIGH_SPHERE_COLOR[]   = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float THIGH_CYLINDER_RADIUS  = 0.25f/JUMPINGBRAIN_RESCALE;
const float THIGH_CYLINDER_LENGTH  = 3.0f/JUMPINGBRAIN_RESCALE;
const float THIGH_CYLINDER_COLOR[] = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float THIGH_MIN_PITCH        = -90.0f;
const float THIGH_MAX_PITCH        = 90.0f;
const float THIGH_PITCH_INCREMENT  = 6.0f;

const float SHIN_SPHERE_RADIUS    = 4.0f/JUMPINGBRAIN_RESCALE;
const float SHIN_SPHERE_SCALE[]   = {0.35f, 1.0f, 0.35f};
const float SHIN_SPHERE_COLOR[]   = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float SHIN_CYLINDER_RADIUS  = 0.25f/JUMPINGBRAIN_RESCALE;
const float SHIN_CYLINDER_LENGTH  = 4.0f/JUMPINGBRAIN_RESCALE;
const float SHIN_CYLINDER_COLOR[] = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float SHIN_MIN_PITCH        = 0.0f;
const float SHIN_MAX_PITCH        = 150.0f;
const float SHIN_PITCH_INCREMENT  = 5.0f;

const float FOOT_SPHERE_RADIUS    = 2.0f/JUMPINGBRAIN_RESCALE;
const float FOOT_SPHERE_SCALE[]   = {0.4f, 1.0f, 0.25f};
const float FOOT_SPHERE_COLOR[]   = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float FOOT_CYLINDER_RADIUS  = 0.25f/JUMPINGBRAIN_RESCALE;
const float FOOT_CYLINDER_LENGTH  = 2.0f/JUMPINGBRAIN_RESCALE;
const float FOOT_CYLINDER_COLOR[] = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float FOOT_MIN_PITCH        = -150.0f;
const float FOOT_MAX_PITCH        = 0.0f;
const float FOOT_PITCH_INCREMENT  = 5.0f;

const float TOE_SPHERE_RADIUS    = 1.0f/JUMPINGBRAIN_RESCALE;
const float TOE_SPHERE_SCALE[]   = {1.0f, 1.0f, 0.25f};
const float TOE_SPHERE_COLOR[]   = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float TOE_CYLINDER_RADIUS  = 0.0f/JUMPINGBRAIN_RESCALE;
const float TOE_CYLINDER_LENGTH  = 1.0f/JUMPINGBRAIN_RESCALE;
const float TOE_CYLINDER_COLOR[] = {JUMPINGBRAIN_COLOR[0], JUMPINGBRAIN_COLOR[1], JUMPINGBRAIN_COLOR[2]};
const float TOE_MIN_PITCH        = 0.0f;
const float TOE_MAX_PITCH        = 30.0f;
const float TOE_PITCH_INCREMENT  = 1.0f;

// Material Properties Constants
const float AMBIENT_COEFF  = -1.0f;    // Minimal ambient reflectance.
const float DIFFUSE_COEFF  =  1.0f;    // Maximal diffuse reflectance.
const float SPECULAR_COEFF =  1.0f;    // Maximal specular reflectance.
const float SPECULAR_EXPON = 20.0f;    // Low level of shininess (scale: 0-128).

#define JUMPING_BRAIN_GLOBALS_H
#endif