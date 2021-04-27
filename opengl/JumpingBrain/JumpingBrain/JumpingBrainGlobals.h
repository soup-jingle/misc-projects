// PATRICK BUNETIC
// Things I added/changed indicated by "[PB]" comment
//     This does not include the sphere radii, cylinder lengths/radii,
//     sphere scaling factors, or changes to min/max pitch since it is
//     a given that all those values for each joint should change.
// NOTE: All joint spheres are shrunk along x- and z-axes (scale factor < 1.0).
//     This makes them all long along the y-axis. All joints are thought of as
//	   upright in this way, so all translations are performed on the y-axis exclusively.
////////////////////////////////////////////////////////
// JumpingBrainGlobals.h - Global Constant Definitions //
////////////////////////////////////////////////////////
#ifndef JUMPING_BRAIN_GLOBALS_H

const float PI = 3.1415926535f;

// Window Position/Resizing Constants
const int   INIT_WINDOW_POSITION[2] = { 50, 50 };
const float ASPECT_RATIO            = 1.0f;
const int   INIT_WINDOW_SIZE[2]     = { 900, int(900/ASPECT_RATIO) };
const float FRUSTUM_FIELD_OF_VIEW   = 35.0f;
const float FRUSTUM_NEAR_PLANE      = 0.1f;
const float FRUSTUM_FAR_PLANE       = 100.0f;
const float BACKGROUND_COLOR[3]     = {0.3f, 0.7f, 0.8f}; // [PB] changed to light blue

// Lighting Constants
const float LIGHT_0_POSITION[]    = { 0.0f, 3.0f, 0.0f, 0.0f};
const float LIGHT_1_POSITION[]    = { 0.0f, -50.0f, 50.0f, 0.0f};
const float LIGHT_AMBIENT[]       = { 0.8f, 0.8f, 0.8f, 1.0f};
const float LIGHT_DIFFUSE[]       = { 0.9f, 0.9f, 0.9f, 1.0f};
const float LIGHT_SPECULAR[]      = { 1.0f, 1.0f, 1.0f, 1.0f};
const float LIGHT_MODEL_AMBIENT[] = { 0.7f, 0.7f, 0.7f, 1.0f};

// Viewer Positioning Constants
const float VIEWER_DISTANCE         = 5.0f;
const float INITIAL_VIEWER_AZIMUTH = PI / 2.0f;
const float INITIAL_VIEWER_ALTITUDE = PI / 2.0f;
const float VIEWER_ANGLE_INCREMENT  = PI / 60.0f;

// Jumping Brain Constants
const float MIN_VEL_SCALE_FACTOR = 0.0f;
const float MAX_VEL_SCALE_FACTOR = 4.0f;
const float VEL_SCALE_FACTOR_INCREMENT = 0.25f;
const float JUMPER_RESCALE =10.0f;
const float ANIM_VEL_SCALE_FACTOR = 4.0f;
const float JUMPER_RADIUS_SIZE = 0.24f;
const float JUMPER_COLOR[3] = { 0.0f, 0.7f, 0.5f }; // Changed to a green [PB]
const float JUMPER_BRAIN_COLOR[3] = { 0.9f, 0.7f, 0.8f }; // Brain is pinkish grey [PB]

const float TORSO_AND_HEAD_SPHERE_RADIUS = 8.0f / JUMPER_RESCALE;
const float TORSO_AND_HEAD_ABOVE_SPHERE_RADIUS = 2.75f / JUMPER_RESCALE;
const float TORSO_AND_HEAD_SPHERE_CENTER[] = { 0.0f / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE }; // elbow
const float TORSO_AND_HEAD_SPHERE_COLOR[] = { JUMPER_BRAIN_COLOR[0], JUMPER_BRAIN_COLOR[1], JUMPER_BRAIN_COLOR[2] };
const float TORSO_AND_HEAD_CYLINDER_RADIUS = 0.0f / JUMPER_RESCALE; // No need for cylinder visibility [PB]
const float TORSO_AND_HEAD_CYLINDER_LENGTH = 4.7f / JUMPER_RESCALE; 
const float TORSO_AND_HEAD_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float TORSO_AND_HEAD_PITCH = 0.0f;
const float TORSO_AND_HEAD_MIN_PITCH = 0.0f;
const float TORSO_AND_HEAD_MAX_PITCH = 0.0f;
const float TORSO_AND_HEAD_PITCH_INCREMENT = 0.0f;
const float TORSO_AND_HEAD_SPHERE_SCALE_X = 0.8f;
const float TORSO_AND_HEAD_SPHERE_SCALE_Y = 0.7f;
const float TORSO_AND_HEAD_SPHERE_SCALE_Z = 1.0f;

const float SHOULDERS_SPHERE_RADIUS = 3.25f / JUMPER_RESCALE;
const float SHOULDERS_SPHERE_CENTER[] = { 0.0f / JUMPER_RESCALE, 3.5f / JUMPER_RESCALE, 6.0f / JUMPER_RESCALE };
const float SHOULDERS_SPHERE_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float SHOULDERS_CYLINDER_RADIUS = 0.25f / JUMPER_RESCALE;
const float SHOULDERS_CYLINDER_LENGTH = 8.5f / JUMPER_RESCALE;
const float SHOULDERS_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float SHOULDERS_ROLL = 0.0f;
const float SHOULDERS_MIN_ROLL = -7.5f;
const float SHOULDERS_MAX_ROLL = 7.5f;
const float SHOULDERS_ROLL_INCREMENT = -0.5f;
const float SHOULDERS_YAW = 0.0f;
const float SHOULDERS_MIN_YAW = -7.5f;
const float SHOULDERS_MAX_YAW = 7.5f;
const float SHOULDERS_YAW_INCREMENT = -0.5f;
const float SHOULDERS_Y_TRANSFORM = -1.0f;
const float SHOULDERS_Z_TRANSFORM = 5.0f;
const float SHOULDERS_SPHERE_SCALE_X = 1.0f;
const float SHOULDERS_SPHERE_SCALE_Y = 1.0f;
const float SHOULDERS_SPHERE_SCALE_Z = 1.0f;

const float HUMERUS_SPHERE_RADIUS = 1.8f / JUMPER_RESCALE;
const float HUMERUS_SPHERE_CENTER[] = { 0.0f / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE };
const float HUMERUS_SPHERE_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float HUMERUS_CYLINDER_RADIUS = 0.25f / JUMPER_RESCALE;
const float HUMERUS_CYLINDER_LENGTH = 1.7f / JUMPER_RESCALE;
const float HUMERUS_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float HUMERUS_PITCH = 0.0f;
const float HUMERUS_MIN_PITCH = -10.0f;
const float HUMERUS_MAX_PITCH = 10.0f;
const float HUMERUS_PITCH_INCREMENT = 1.0f;
const float HUMERUS_SPHERE_SCALE_X = 0.5f;
const float HUMERUS_SPHERE_SCALE_Y = 1.0f;
const float HUMERUS_SPHERE_SCALE_Z = 0.5f;

const float FOREARM_SPHERE_RADIUS = 1.7f / JUMPER_RESCALE;
const float FOREARM_SPHERE_CENTER[] = { 0.0f / JUMPER_RESCALE, -HUMERUS_CYLINDER_LENGTH / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE };
const float FOREARM_SPHERE_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float FOREARM_CYLINDER_RADIUS = 0.25f / JUMPER_RESCALE;
const float FOREARM_CYLINDER_LENGTH = 1.6f / JUMPER_RESCALE;
const float FOREARM_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float FOREARM_PITCH = 0.0f;
const float FOREARM_MIN_PITCH = -10.0f;
const float FOREARM_MAX_PITCH = 90.0f;
const float FOREARM_PITCH_INCREMENT = 5.0f;
const float FOREARM_SPHERE_SCALE_X = 0.32f;
const float FOREARM_SPHERE_SCALE_Y = 1.0f;
const float FOREARM_SPHERE_SCALE_Z = 0.32f;

const float HAND_SPHERE_RADIUS = 1.0f / JUMPER_RESCALE;
const float HAND_SPHERE_CENTER[] = { 0.0f / JUMPER_RESCALE, 0.4f / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE };
const float HAND_SPHERE_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float HAND_CYLINDER_RADIUS = 0.25f / JUMPER_RESCALE;
const float HAND_CYLINDER_LENGTH = 0.0f / JUMPER_RESCALE;
const float HAND_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float HAND_PITCH = 0.0f;
const float HAND_MIN_PITCH = -30.0f;
const float HAND_MAX_PITCH = 0.0f;
const float HAND_PITCH_INCREMENT = 1.5f;
const float HAND_SPHERE_SCALE_X = 1.0f;
const float HAND_SPHERE_SCALE_Y = 1.0f;
const float HAND_SPHERE_SCALE_Z = 0.1f;

const float HIPS_SPHERE_RADIUS = 1.75f / JUMPER_RESCALE;
const float HIPS_SPHERE_CENTER[] = { 0.0f / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE, -5.0f / JUMPER_RESCALE };
const float HIPS_SPHERE_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float HIPS_CYLINDER_RADIUS = 0.25f / JUMPER_RESCALE;
const float HIPS_CYLINDER_LENGTH = 9.7f / JUMPER_RESCALE;
const float HIPS_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float HIPS_ROLL = 0.0f;
const float HIPS_MIN_ROLL = -7.5f;
const float HIPS_MAX_ROLL = 7.5f;
const float HIPS_ROLL_INCREMENT = 0.5f;
const float HIPS_YAW = 0.0f;
const float HIPS_MIN_YAW = -7.5f;
const float HIPS_MAX_YAW = 7.5f;
const float HIPS_YAW_INCREMENT = 0.5f;
const float HIPS_Y_TRANSFORM = -3.0f;
const float HIPS_Z_TRANSFORM = -5.0f;
const float HIPS_SPHERE_SCALE_X = 1.0f;
const float HIPS_SPHERE_SCALE_Y = 1.0f;
const float HIPS_SPHERE_SCALE_Z = 1.0f;

const float THIGH_SPHERE_RADIUS = 3.0f / JUMPER_RESCALE;
const float THIGH_SPHERE_CENTER[] = { 0.0f / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE };
const float THIGH_SPHERE_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float THIGH_CYLINDER_RADIUS = 0.25f / JUMPER_RESCALE;
const float THIGH_CYLINDER_LENGTH = 2.7f / JUMPER_RESCALE;
const float THIGH_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float THIGH_PITCH = 0.0f;
const float THIGH_MIN_PITCH = -90.0f;
const float THIGH_MAX_PITCH = 90.0f;
const float THIGH_PITCH_INCREMENT = -9.0f;
const float THIGH_SPHERE_SCALE_X = 0.5f;
const float THIGH_SPHERE_SCALE_Y = 1.0f;
const float THIGH_SPHERE_SCALE_Z = 0.5f;
const float THIGH_OFFSET = 0.75f; // Testing purposes. Was not actually used [PB]

const float SHIN_SPHERE_RADIUS = 3.5f / JUMPER_RESCALE;
const float SHIN_SPHERE_CENTER[] = { 0.0f / JUMPER_RESCALE, THIGH_CYLINDER_LENGTH / JUMPER_RESCALE, 0.0 / JUMPER_RESCALE };
const float SHIN_SPHERE_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float SHIN_CYLINDER_RADIUS = 0.25f / JUMPER_RESCALE;
const float SHIN_CYLINDER_LENGTH = 3.5f / JUMPER_RESCALE;
const float SHIN_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float SHIN_PITCH = 0.0f;
const float SHIN_MIN_PITCH = 0.0f;
const float SHIN_MAX_PITCH = 135.0f;
const float SHIN_PITCH_INCREMENT = 6.75f;
const float SHIN_SPHERE_SCALE_X = 0.35f;
const float SHIN_SPHERE_SCALE_Y = 1.0f;
const float SHIN_SPHERE_SCALE_Z = 0.35f;

const float HEEL_SPHERE_RADIUS = 2.0f / JUMPER_RESCALE;
const float HEEL_SPHERE_CENTER[] = { 0.0f, -SHIN_CYLINDER_LENGTH / JUMPER_RESCALE, 0.0f };
const float HEEL_SPHERE_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float HEEL_CYLINDER_RADIUS = 0.25f / JUMPER_RESCALE;
const float HEEL_CYLINDER_LENGTH = 2.0f / JUMPER_RESCALE;
const float HEEL_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float HEEL_PITCH = -90.0f;
const float HEEL_MIN_PITCH = 45.0f;
const float HEEL_MAX_PITCH = 185.0f;
const float HEEL_PITCH_INCREMENT = 7.0f;
const float HEEL_SPHERE_SCALE_X = 0.45f;
const float HEEL_SPHERE_SCALE_Y = 1.0f;
const float HEEL_SPHERE_SCALE_Z = 0.2f;

const float TOE_SPHERE_RADIUS = 1.5f / JUMPER_RESCALE;
const float TOE_SPHERE_CENTER[] = { 0.0f / JUMPER_RESCALE, 0.0f / JUMPER_RESCALE, HEEL_CYLINDER_LENGTH / JUMPER_RESCALE };
const float TOE_SPHERE_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float TOE_CYLINDER_RADIUS = 0.25f / JUMPER_RESCALE;
const float TOE_CYLINDER_LENGTH = 0.0f / JUMPER_RESCALE;
const float TOE_CYLINDER_COLOR[] = { JUMPER_COLOR[0], JUMPER_COLOR[1], JUMPER_COLOR[2] };
const float TOE_PITCH = 0.0f;
const float TOE_MIN_PITCH = 0.0f;
const float TOE_MAX_PITCH = 30.0f;
const float TOE_PITCH_INCREMENT = 1.5f;
const float TOE_SPHERE_SCALE_X = 1.0f;
const float TOE_SPHERE_SCALE_Y = 1.0f;
const float TOE_SPHERE_SCALE_Z = 0.1f;

const float CHARACTER_ELEVATION = HIPS_SPHERE_RADIUS + THIGH_CYLINDER_LENGTH +
SHIN_CYLINDER_LENGTH + HEEL_SPHERE_RADIUS;

// Material Properties Constants
const float AMBIENT_COEFF  = -1.0f;    // Minimal ambient reflectance.
const float DIFFUSE_COEFF  =  1.0f;    // Maximal diffuse reflectance.
const float SPECULAR_COEFF =  1.0f;    // Maximal specular reflectance.
const float SPECULAR_EXPON =  20.0f;    // Low level of shininess (scale: 0-128).

#define JUMPING_BRAIN_GLOBALS_H
#endif