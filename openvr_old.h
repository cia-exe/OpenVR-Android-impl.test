#pragma once

// openvr.h
//========= Copyright Valve Corporation ============//
// Dynamically generated file. Do not modify this file directly.

#ifndef _OPENVR_API
#define _OPENVR_API

#include <stdint.h>
#include <jni.h>


// vrtypes.h
#ifndef _INCLUDE_VRTYPES_H
#define _INCLUDE_VRTYPES_H 

namespace vr
{

#if defined(__linux__) || defined(__APPLE__) 
	// The 32-bit version of gcc has the alignment requirement for uint64 and double set to
	// 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
	// The 64-bit version of gcc has the alignment requirement for these types set to
	// 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
	// The 64-bit structure packing has to match the 32-bit structure packing for each platform.
	#pragma pack( push, 4 )
#else
	#pragma pack( push, 8 )
#endif

// right-handed system
// +y is up
// +x is to the right
// -z is going away from you
// Distance unit is  meters
struct HmdMatrix34_t
{
	float m[3][4];
};

struct HmdMatrix44_t
{
	float m[4][4];
};

struct HmdVector3_t
{
	float v[3];
};

struct HmdVector4_t
{
	float v[4];
};

struct HmdVector3d_t
{
	double v[3];
};

struct HmdVector2_t
{
	float v[2];
};

struct HmdQuaternion_t
{
	double w, x, y, z;
};

struct HmdColor_t
{
	float r, g, b, a;
};

struct HmdQuad_t
{
	HmdVector3_t vCorners[ 4 ];
};

/** Used to return the post-distortion UVs for each color channel. 
* UVs range from 0 to 1 with 0,0 in the upper left corner of the 
* source render target. The 0,0 to 1,1 range covers a single eye. */
struct DistortionCoordinates_t
{
	float rfRed[2];
	float rfGreen[2];
	float rfBlue[2];
};

enum Hmd_Eye
{
	Eye_Left = 0,
	Eye_Right = 1
};

enum GraphicsAPIConvention
{
	API_DirectX = 0, // Normalized Z goes from 0 at the viewer to 1 at the far clip plane
	API_OpenGL = 1,  // Normalized Z goes from 1 at the viewer to -1 at the far clip plane
};

enum HmdTrackingResult
{
	TrackingResult_Uninitialized			= 1,

	TrackingResult_Calibrating_InProgress	= 100,
	TrackingResult_Calibrating_OutOfRange	= 101,

	TrackingResult_Running_OK				= 200,
	TrackingResult_Running_OutOfRange		= 201,
};

static const uint32_t k_unTrackingStringSize = 32;
static const uint32_t k_unMaxDriverDebugResponseSize = 32768;

/** Used to pass device IDs to API calls */
typedef uint32_t TrackedDeviceIndex_t;
static const uint32_t k_unTrackedDeviceIndex_Hmd = 0;
static const uint32_t k_unMaxTrackedDeviceCount = 16;
static const uint32_t k_unTrackedDeviceIndexInvalid = 0xFFFFFFFF;

/** Describes what kind of object is being tracked at a given ID */
enum TrackedDeviceClass
{
	TrackedDeviceClass_Invalid = 0,				// the ID was not valid.
	TrackedDeviceClass_HMD = 1,					// Head-Mounted Displays
	TrackedDeviceClass_Controller = 2,			// Tracked controllers
	TrackedDeviceClass_TrackingReference = 4,	// Camera and base stations that serve as tracking reference points

	TrackedDeviceClass_Other = 1000,
};


/** describes a single pose for a tracked object */
struct TrackedDevicePose_t
{
	HmdMatrix34_t mDeviceToAbsoluteTracking;
	HmdVector3_t vVelocity;				// velocity in tracker space in m/s
	HmdVector3_t vAngularVelocity;		// angular velocity in radians/s (?)
	HmdTrackingResult eTrackingResult;
	bool bPoseIsValid;

	// This indicates that there is a device connected for this spot in the pose array.
	// It could go from true to false if the user unplugs the device.
	bool bDeviceIsConnected;
};

/** Identifies which style of tracking origin the application wants to use
* for the poses it is requesting */
enum TrackingUniverseOrigin
{
	TrackingUniverseSeated = 0,		// Poses are provided relative to the seated zero pose
	TrackingUniverseStanding = 1,	// Poses are provided relative to the safe bounds configured by the user
	TrackingUniverseRawAndUncalibrated = 2,	// Poses are provided in the coordinate system defined by the driver. You probably don't want this one.
};


/** Each entry in this enum represents a property that can be retrieved about a
* tracked device. Many fields are only valid for one TrackedDeviceClass. */
enum TrackedDeviceProperty
{
	// general properties that apply to all device classes
	Prop_TrackingSystemName_String				= 1000,
	Prop_ModelNumber_String						= 1001,
	Prop_SerialNumber_String					= 1002,
	Prop_RenderModelName_String					= 1003,
	Prop_WillDriftInYaw_Bool					= 1004,
	Prop_ManufacturerName_String				= 1005,
	Prop_TrackingFirmwareVersion_String			= 1006,
	Prop_HardwareRevision_String				= 1007,
	Prop_AllWirelessDongleDescriptions_String	= 1008,
	Prop_ConnectedWirelessDongle_String			= 1009,
	Prop_DeviceIsWireless_Bool					= 1010,
	Prop_DeviceIsCharging_Bool					= 1011,
	Prop_DeviceBatteryPercentage_Float			= 1012, // 0 is empty, 1 is full
	Prop_StatusDisplayTransform_Matrix34		= 1013,
	Prop_Firmware_UpdateAvailable_Bool			= 1014,
	Prop_Firmware_ManualUpdate_Bool				= 1015,
	Prop_Firmware_ManualUpdateURL_String		= 1016,
	Prop_HardwareRevision_Uint64				= 1017,
	Prop_FirmwareVersion_Uint64					= 1018,
	Prop_FPGAVersion_Uint64						= 1019,
	Prop_VRCVersion_Uint64						= 1020,
	Prop_RadioVersion_Uint64					= 1021,
	Prop_DongleVersion_Uint64					= 1022,
	Prop_BlockServerShutdown_Bool				= 1023,

	// Properties that are unique to TrackedDeviceClass_HMD
	Prop_ReportsTimeSinceVSync_Bool				= 2000,
	Prop_SecondsFromVsyncToPhotons_Float		= 2001,
	Prop_DisplayFrequency_Float					= 2002,
	Prop_UserIpdMeters_Float					= 2003,
	Prop_CurrentUniverseId_Uint64				= 2004, 
	Prop_PreviousUniverseId_Uint64				= 2005, 
	Prop_DisplayFirmwareVersion_String			= 2006,
	Prop_IsOnDesktop_Bool						= 2007,
	Prop_DisplayMCType_Int32					= 2008,
	Prop_DisplayMCOffset_Float					= 2009,
	Prop_DisplayMCScale_Float					= 2010,
	Prop_VendorID_Int32                         = 2011,
	Prop_DisplayMCImageLeft_String              = 2012,
	Prop_DisplayMCImageRight_String             = 2013,
	Prop_DisplayGCBlackClamp_Float				= 2014,

	// Properties that are unique to TrackedDeviceClass_Controller
	Prop_AttachedDeviceId_String				= 3000,
	Prop_SupportedButtons_Uint64				= 3001,
	Prop_Axis0Type_Int32						= 3002, // Return value is of type EVRControllerAxisType
	Prop_Axis1Type_Int32						= 3003, // Return value is of type EVRControllerAxisType
	Prop_Axis2Type_Int32						= 3004, // Return value is of type EVRControllerAxisType
	Prop_Axis3Type_Int32						= 3005, // Return value is of type EVRControllerAxisType
	Prop_Axis4Type_Int32						= 3006, // Return value is of type EVRControllerAxisType

	// Properties that are unique to TrackedDeviceClass_TrackingReference
	Prop_FieldOfViewLeftDegrees_Float			= 4000,
	Prop_FieldOfViewRightDegrees_Float			= 4001,
	Prop_FieldOfViewTopDegrees_Float			= 4002,
	Prop_FieldOfViewBottomDegrees_Float			= 4003,
	Prop_TrackingRangeMinimumMeters_Float		= 4004,
	Prop_TrackingRangeMaximumMeters_Float		= 4005,

	// Camera calibration parameters
	Prop_TrackedCamera_IntrinsicsFX_Float		= 5000,
	Prop_TrackedCamera_IntrinsicsFY_Float		= 5001,
	Prop_TrackedCamera_IntrinsicsCX_Float		= 5002,
	Prop_TrackedCamera_IntrinsicsCY_Float		= 5003,
	Prop_TrackedCamera_IntrinsicsK1_Float		= 5004,
	Prop_TrackedCamera_IntrinsicsK2_Float		= 5005,
	Prop_TrackedCamera_IntrinsicsP1_Float		= 5006,
	Prop_TrackedCamera_IntrinsicsP2_Float		= 5007,
	Prop_TrackedCamera_IntrinsicsK3_Float		= 5008,
};

/** No string property will ever be longer than this length */
static const uint32_t k_unMaxPropertyStringSize = 32 * 1024;

/** Used to return errors that occur when reading properties. */
enum TrackedPropertyError
{
	TrackedProp_Success						= 0,
	TrackedProp_WrongDataType				= 1,
	TrackedProp_WrongDeviceClass			= 2,
	TrackedProp_BufferTooSmall				= 3,
	TrackedProp_UnknownProperty				= 4,
	TrackedProp_InvalidDevice				= 5,
	TrackedProp_CouldNotContactServer		= 6,
	TrackedProp_ValueNotProvidedByDevice	= 7,
	TrackedProp_StringExceedsMaximumLength	= 8,
};


/** a single vertex in a render model */
struct RenderModel_Vertex_t
{
	HmdVector3_t vPosition;		// position in meters in device space
	HmdVector3_t vNormal;		
	float rfTextureCoord[ 2 ];
};

/** A texture map for use on a render model */
struct RenderModel_TextureMap_t
{
	uint16_t unWidth, unHeight; // width and height of the texture map in pixels
	const uint8_t *rubTextureMapData;	// Map texture data. All textures are RGBA with 8 bits per channel per pixel. Data size is width * height * 4ub
};

/** Contains everything a game needs to render a single tracked or static object for the user. */
struct RenderModel_t
{
	uint64_t ulInternalHandle;					// Used internally by SteamVR
	const RenderModel_Vertex_t *rVertexData;			// Vertex data for the mesh
	uint32_t unVertexCount;						// Number of vertices in the vertex data
	const uint16_t *rIndexData;						// Indices into the vertex data for each triangle
	uint32_t unTriangleCount;					// Number of triangles in the mesh. Index count is 3 * TriangleCount
	RenderModel_TextureMap_t diffuseTexture;	// RGBA diffuse texture for the model
};


/** Allows the application to control what part of the provided texture will be used in the
* frame buffer. */
struct VRTextureBounds_t
{
	float uMin, vMin;
	float uMax, vMax;
};


/** Allows the applicaiton to control how scene textures are used by the compositor when calling Submit. */
enum VRSubmitFlags_t
{
	// Simple render path. App submits rendered left and right eye images with no lens distortion correction applied.
	Submit_Default = 0x00,

	// App submits final left and right eye images with lens distortion already applied (lens distortion makes the images appear
	// barrel distorted with chromatic aberration correction applied). The app would have used the data returned by
	// vr::IVRSystem::ComputeDistortion() to apply the correct distortion to the rendered images before calling Submit().
	Submit_LensDistortionAlreadyApplied = 0x01
};


/** Status of the overall system or tracked objects */
enum VRState_t
{
	VRState_Undefined = -1,
	VRState_Off = 0,
	VRState_Searching = 1,
	VRState_Searching_Alert = 2,
	VRState_Ready = 3,
	VRState_Ready_Alert = 4,
	VRState_NotReady = 5,
};

/** The types of events that could be posted (and what the parameters mean for each event type) */
enum EVREventType
{
	VREvent_None = 0,

	VREvent_TrackedDeviceActivated		= 100,
	VREvent_TrackedDeviceDeactivated	= 101,
	VREvent_TrackedDeviceUpdated		= 102,
	VREvent_TrackedDeviceUserInteractionStarted		= 103,
	VREvent_TrackedDeviceUserInteractionEnded	= 104,

	VREvent_ButtonPress					= 200, // data is controller
	VREvent_ButtonUnpress				= 201, // data is controller
	VREvent_ButtonTouch					= 202, // data is controller
	VREvent_ButtonUntouch				= 203, // data is controller

	VREvent_MouseMove					= 300, // data is mouse
	VREvent_MouseButtonDown				= 301, // data is mouse
	VREvent_MouseButtonUp				= 302, // data is mouse
	VREvent_FocusEnter					= 303, // data is overlay
	VREvent_FocusLeave					= 304, // data is overlay

	VREvent_InputFocusCaptured			= 400, // data is process
	VREvent_InputFocusReleased			= 401, // data is process
	VREvent_SceneFocusLost				= 402, // data is process
	VREvent_SceneFocusGained			= 403, // data is process
	VREvent_SceneApplicationChanged		= 404, // data is process - The App actually drawing the scene changed (usually to or from the compositor)
	VREvent_SceneFocusChanged			= 405, // data is process - New app got access to draw the scene

	VREvent_OverlayShown				= 500,
	VREvent_OverlayHidden				= 501,
	VREvent_DashboardActivated		= 502,
	VREvent_DashboardDeactivated	= 503,
	VREvent_DashboardThumbSelected	= 504, // Sent to the overlay manager - data is overlay
	VREvent_DashboardRequested		= 505, // Sent to the overlay manager - data is overlay
	VREvent_ResetDashboard			= 506, // Send to the overlay manager
	VREvent_RenderToast				= 507, // Send to the dashboard to render a toast - data is the notification ID
	VREvent_ImageLoaded				= 508, // Sent to overlays when a SetOverlayRaw or SetOverlayFromFile call finishes loading
	VREvent_ShowKeyboard			= 509, // Sent to keyboard renderer in the dashboard to invoke it

	VREvent_Notification_Show				= 600,
	VREvent_Notification_Dismissed			= 601,
	VREvent_Notification_BeginInteraction	= 602,

	VREvent_Quit						= 700, // data is process
	VREvent_ProcessQuit					= 701, // data is process

	VREvent_ChaperoneDataHasChanged		= 800,
	VREvent_ChaperoneUniverseHasChanged	= 801,
	VREvent_ChaperoneTempDataHasChanged = 802,

	VREvent_StatusUpdate				= 900,

	VREvent_MCImageUpdated				= 1000,

	VREvent_FirmwareUpdateStarted	= 1100,
	VREvent_FirmwareUpdateFinished	= 1101,

	VREvent_KeyboardClosed				= 1200,
	VREvent_KeyboardCharInput			= 1201,

	VREvent_ApplicationTransitionStarted	= 1300,
	VREvent_ApplicationTransitionAborted	= 1301,
	VREvent_ApplicationTransitionNewAppStarted = 1302,
};


/** Level of Hmd activity */
enum EDeviceActivityLevel
{
	k_EDeviceActivityLevel_Unknown = -1,
	k_EDeviceActivityLevel_Idle = 0,
	k_EDeviceActivityLevel_UserInteraction = 1,
	k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
};


/** VR controller button and axis IDs */
enum EVRButtonId
{
	k_EButton_System			= 0,
	k_EButton_ApplicationMenu	= 1,
	k_EButton_Grip				= 2,
	k_EButton_DPad_Left			= 3,
	k_EButton_DPad_Up			= 4,
	k_EButton_DPad_Right		= 5,
	k_EButton_DPad_Down			= 6,
	k_EButton_A					= 7,

	k_EButton_Axis0				= 32,
	k_EButton_Axis1				= 33,
	k_EButton_Axis2				= 34,
	k_EButton_Axis3				= 35,
	k_EButton_Axis4				= 36,

	// aliases for well known controllers
	k_EButton_SteamVR_Touchpad	= k_EButton_Axis0,
	k_EButton_SteamVR_Trigger	= k_EButton_Axis1,

	k_EButton_Dashboard_Back	= k_EButton_Grip,

	k_EButton_Max				= 64
};

inline uint64_t ButtonMaskFromId( EVRButtonId id ) { return 1ull << id; }

/** used for controller button events */
struct VREvent_Controller_t
{
	EVRButtonId button;
};


/** used for simulated mouse events in overlay space */
enum EVRMouseButton
{
	VRMouseButton_Left					= 0x0001,
	VRMouseButton_Right					= 0x0002,
	VRMouseButton_Middle				= 0x0004,
};


/** used for simulated mouse events in overlay space */
struct VREvent_Mouse_t
{
	float x, y;
	EVRMouseButton button;
};

/** notification related events. Details will still change at this point */
struct VREvent_Notification_t
{
	uint64_t ulUserValue;
	uint32_t notificationId;
};


/** Used for events about processes */
struct VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
};


/** Used for a few events about overlays */
struct VREvent_Overlay_t
{
	uint64_t overlayHandle;
};


/** Used for a few events about overlays */
struct VREvent_Status_t
{
	VRState_t statusState; 
};

/** Used for keyboard events **/
struct VREvent_Keyboard_t
{
	char cNewInput[12];	// Up to 11 bytes of new input
	uint32_t uFlags;	// Possible flags about the new input
};


/** Not actually used for any events. It is just used to reserve
* space in the union for future event types */
struct VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
};

/** If you change this you must manually update openvr_interop.cs.py */
typedef union
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_Status_t status;
	VREvent_Keyboard_t keyboard;
} VREvent_Data_t;

/** An event posted by the server to all running applications */
struct VREvent_t
{
	EVREventType eventType;
	TrackedDeviceIndex_t trackedDeviceIndex;
	VREvent_Data_t data;
	float eventAgeSeconds;
};


/** The mesh to draw into the stencil (or depth) buffer to perform 
* early stencil (or depth) kills of pixels that will never appear on the HMD.
* This mesh draws on all the pixels that will be hidden after distortion. 
*
* If the HMD does not provide a visible area mesh pVertexData will be
* NULL and unTriangleCount will be 0. */
struct HiddenAreaMesh_t
{
	const HmdVector2_t *pVertexData;
	uint32_t unTriangleCount;
};


/** Identifies what kind of axis is on the controller at index n. Read this type 
* with pVRSystem->Get( nControllerDeviceIndex, Prop_Axis0Type_Int32 + n );
*/
enum EVRControllerAxisType
{
	k_eControllerAxis_None = 0,
	k_eControllerAxis_TrackPad = 1,
	k_eControllerAxis_Joystick = 2,
	k_eControllerAxis_Trigger = 3, // Analog trigger data is in the X axis
};


/** contains information about one axis on the controller */
struct VRControllerAxis_t
{
	float x; // Ranges from -1.0 to 1.0 for joysticks and track pads. Ranges from 0.0 to 1.0 for triggers were 0 is fully released.
	float y; // Ranges from -1.0 to 1.0 for joysticks and track pads. Is always 0.0 for triggers.
};


/** the number of axes in the controller state */
static const uint32_t k_unControllerStateAxisCount = 5;


/** Holds all the state of a controller at one moment in time. */
struct VRControllerState001_t
{
	// If packet num matches that on your prior call, then the controller state hasn't been changed since 
	// your last call and there is no need to process it
	uint32_t unPacketNum;

	// bit flags for each of the buttons. Use ButtonMaskFromId to turn an ID into a mask
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;

	// Axis data for the controller's analog inputs
	VRControllerAxis_t rAxis[ k_unControllerStateAxisCount ];
};


typedef VRControllerState001_t VRControllerState_t;


/** determines how to provide output to the application of various event processing functions. */
enum EVRControllerEventOutputType
{
	ControllerEventOutput_OSEvents = 0,
	ControllerEventOutput_VREvents = 1,
};


/** Allows the application to customize how the overlay appears in the compositor */
struct Compositor_OverlaySettings
{
	uint32_t size; // sizeof(Compositor_OverlaySettings)
	bool curved, antialias;
	float scale, distance, alpha;
	float uOffset, vOffset, uScale, vScale;
	float gridDivs, gridWidth, gridScale;
	HmdMatrix44_t transform;
};

/** used to refer to a single VR overlay */
typedef uint64_t VROverlayHandle_t;

static const VROverlayHandle_t k_ulOverlayHandleInvalid = 0;

/** Errors that can occur around VR overlays */
enum VROverlayError
{
	VROverlayError_None					= 0,

	VROverlayError_UnknownOverlay		= 10,
	VROverlayError_InvalidHandle		= 11,
	VROverlayError_PermissionDenied		= 12,
	VROverlayError_OverlayLimitExceeded = 13, // No more overlays could be created because the maximum number already exist
	VROverlayError_WrongVisibilityType	= 14,
	VROverlayError_KeyTooLong			= 15,
	VROverlayError_NameTooLong			= 16,
	VROverlayError_KeyInUse				= 17,
	VROverlayError_WrongTransformType	= 18,
	VROverlayError_InvalidTrackedDevice = 19,
	VROverlayError_InvalidParameter		= 20,
	VROverlayError_ThumbnailCantBeDestroyed = 21,
	VROverlayError_ArrayTooSmall		= 22,
	VROverlayError_RequestFailed		= 23,
	VROverlayError_InvalidTexture		= 24,
	VROverlayError_UnableToLoadFile		= 25,
	VROVerlayError_KeyboardAlreadyInUse = 26,
};

/** enum values to pass in to VR_Init to identify whether the application will 
* draw a 3D scene. */
enum EVRApplicationType
{
	VRApplication_Other = 0,		// Some other kind of application that isn't covered by the other entries 
	VRApplication_Scene	= 1,		// Application will submit 3D frames 
	VRApplication_Overlay = 2,		// Application only interacts with overlays
};


/** error codes for firmware */
enum VRFirmwareError
{
	VRFirmwareError_None = 0,
	VRFirmwareError_Success = 1,
	VRFirmwareError_Fail = 2,
};


/** error codes returned by Vr_Init */

// Please add adequate error description to https://developer.valvesoftware.com/w/index.php?title=Category:SteamVRHelp
enum HmdError
{
	HmdError_None = 0,
	HmdError_Unknown = 1,

	HmdError_Init_InstallationNotFound	= 100,
	HmdError_Init_InstallationCorrupt	= 101,
	HmdError_Init_VRClientDLLNotFound	= 102,
	HmdError_Init_FileNotFound			= 103,
	HmdError_Init_FactoryNotFound		= 104,
	HmdError_Init_InterfaceNotFound		= 105,
	HmdError_Init_InvalidInterface		= 106,
	HmdError_Init_UserConfigDirectoryInvalid = 107,
	HmdError_Init_HmdNotFound			= 108,
	HmdError_Init_NotInitialized		= 109,
	HmdError_Init_PathRegistryNotFound	= 110,
	HmdError_Init_NoConfigPath			= 111,
	HmdError_Init_NoLogPath				= 112,
	HmdError_Init_PathRegistryNotWritable = 113,
	HmdError_Init_AppInfoInitFailed		= 114,
	HmdError_Init_Retry					= 115, // Used internally to cause retries to vrserver
	HmdError_Init_InitCanceledByUser	= 116, // The calling application should silently exit. The user canceled app startup
	HmdError_Init_AnotherAppLaunching	= 117, 
	HmdError_Init_SettingsInitFailed	= 118, 
	HmdError_Init_ShuttingDown			= 119,

	HmdError_Driver_Failed				= 200,
	HmdError_Driver_Unknown				= 201,
	HmdError_Driver_HmdUnknown			= 202,
	HmdError_Driver_NotLoaded			= 203,
	HmdError_Driver_RuntimeOutOfDate	= 204,
	HmdError_Driver_HmdInUse			= 205,
	HmdError_Driver_NotCalibrated		= 206,
	HmdError_Driver_CalibrationInvalid	= 207,
	HmdError_Driver_HmdDisplayNotFound  = 208,
	
	HmdError_IPC_ServerInitFailed		= 300,
	HmdError_IPC_ConnectFailed			= 301,
	HmdError_IPC_SharedStateInitFailed	= 302,
	HmdError_IPC_CompositorInitFailed	= 303,
	HmdError_IPC_MutexInitFailed		= 304,

	HmdError_VendorSpecific_UnableToConnectToOculusRuntime = 1000,

	HmdError_VendorSpecific_HmdFound_CantOpenDevice 			= 1101,
	HmdError_VendorSpecific_HmdFound_UnableToRequestConfigStart = 1102,
	HmdError_VendorSpecific_HmdFound_NoStoredConfig 			= 1103,
	HmdError_VendorSpecific_HmdFound_ConfigTooBig 				= 1104,
	HmdError_VendorSpecific_HmdFound_ConfigTooSmall 			= 1105,
	HmdError_VendorSpecific_HmdFound_UnableToInitZLib 			= 1106,
	HmdError_VendorSpecific_HmdFound_CantReadFirmwareVersion 	= 1107,
	HmdError_VendorSpecific_HmdFound_UnableToSendUserDataStart  = 1108,
	HmdError_VendorSpecific_HmdFound_UnableToGetUserDataStart   = 1109,
	HmdError_VendorSpecific_HmdFound_UnableToGetUserDataNext    = 1110,
	HmdError_VendorSpecific_HmdFound_UserDataAddressRange       = 1111,
	HmdError_VendorSpecific_HmdFound_UserDataError              = 1112,

	HmdError_Steam_SteamInstallationNotFound = 2000,

};

#pragma pack( pop )

// figure out how to import from the VR API dll
#if defined(_WIN32)

#ifdef VR_API_EXPORT
#define VR_INTERFACE extern "C" __declspec( dllexport )
#else
#define VR_INTERFACE extern "C" __declspec( dllimport )
#endif

#elif defined(GNUC) || defined(COMPILER_GCC) || defined(__APPLE__)

#ifdef VR_API_EXPORT
#define VR_INTERFACE extern "C" __attribute__((visibility("default")))
#else
#define VR_INTERFACE extern "C" 
#endif

#else
#define VR_INTERFACE extern "C" 
//#error "Unsupported Platform."
#endif


#if defined( _WIN32 )
#define VR_CALLTYPE __cdecl
#else
#define VR_CALLTYPE 
#endif

}

#endif // _INCLUDE_VRTYPES_H

// vrannotation.h
#ifdef __clang__
# define VR_CLANG_ATTR(ATTR) __attribute__((annotate( ATTR )))
#else
# define VR_CLANG_ATTR(ATTR)
#endif

#define VR_METHOD_DESC(DESC) VR_CLANG_ATTR( "desc:" #DESC ";" )
#define VR_IGNOREATTR() VR_CLANG_ATTR( "ignore" )
#define VR_OUT_STRUCT() VR_CLANG_ATTR( "out_struct: ;" )
#define VR_OUT_STRING() VR_CLANG_ATTR( "out_string: ;" )
#define VR_OUT_ARRAY_CALL(COUNTER,FUNCTION,PARAMS) VR_CLANG_ATTR( "out_array_call:" #COUNTER "," #FUNCTION "," #PARAMS ";" )
#define VR_OUT_ARRAY_COUNT(COUNTER) VR_CLANG_ATTR( "out_array_count:" #COUNTER ";" )
#define VR_ARRAY_COUNT(COUNTER) VR_CLANG_ATTR( "array_count:" #COUNTER ";" )
#define VR_ARRAY_COUNT_D(COUNTER, DESC) VR_CLANG_ATTR( "array_count:" #COUNTER ";desc:" #DESC )
#define VR_BUFFER_COUNT(COUNTER) VR_CLANG_ATTR( "buffer_count:" #COUNTER ";" )
#define VR_OUT_BUFFER_COUNT(COUNTER) VR_CLANG_ATTR( "out_buffer_count:" #COUNTER ";" )
#define VR_OUT_STRING_COUNT(COUNTER) VR_CLANG_ATTR( "out_string_count:" #COUNTER ";" )
// ivrsystem.h
namespace vr
{

class IVRSystem
{
public:


	// ------------------------------------
	// Display Methods
	// ------------------------------------

	/** Size and position that the window needs to be on the VR display. */
	virtual void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;

	/** Suggested size for the intermediate render target that the distortion pulls from. */
	virtual void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) = 0;

	/** Gets the viewport in the frame buffer to draw the output of the distortion into */
	virtual void GetEyeOutputViewport( Hmd_Eye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) = 0;
	
	/** The projection matrix for the specified eye */
	virtual HmdMatrix44_t GetProjectionMatrix( Hmd_Eye eEye, float fNearZ, float fFarZ, GraphicsAPIConvention eProjType ) = 0;

	/** The components necessary to build your own projection matrix in case your
	* application is doing something fancy like infinite Z */
	virtual void GetProjectionRaw( Hmd_Eye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) = 0;

	/** Returns the result of the distortion function for the specified eye and input UVs. UVs go from 0,0 in 
	* the upper left of that eye's viewport and 1,1 in the lower right of that eye's viewport. */
	virtual DistortionCoordinates_t ComputeDistortion( Hmd_Eye eEye, float fU, float fV ) = 0;

	/** Returns the transform from eye space to the head space. Eye space is the per-eye flavor of head
	* space that provides stereo disparity. Instead of Model * View * Projection the sequence is Model * View * Eye^-1 * Projection. 
	* Normally View and Eye^-1 will be multiplied together and treated as View in your application. 
	*/
	virtual HmdMatrix34_t GetEyeToHeadTransform( Hmd_Eye eEye ) = 0;

	/** Returns the number of elapsed seconds since the last recorded vsync event. This 
	*	will come from a vsync timer event in the timer if possible or from the application-reported
	*   time if that is not available. If no vsync times are available the function will 
	*   return zero for vsync time and frame counter and return false from the method. */
	virtual bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter ) = 0;

	/** [D3D9 Only]
	* Returns the adapter index that the user should pass into CreateDevice to set up D3D9 in such
	* a way that it can go full screen exclusive on the HMD. Returns -1 if there was an error.
	*/
	virtual int32_t GetD3D9AdapterIndex() = 0;

	/** [D3D10/11 Only]
	* Returns the adapter index and output index that the user should pass into EnumAdapters and EnumOutputs 
	* to create the device and swap chain in DX10 and DX11. If an error occurs both indices will be set to -1.
	*/
	virtual void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex ) = 0;

	/** [Windows Only]
	* Notifies the system that the VR output will appear in a particular window.
	*/
	virtual bool AttachToWindow( void *hWnd ) = 0;

	// ------------------------------------
	// Tracking Methods
	// ------------------------------------

	/** The pose that the tracker thinks that the HMD will be in at the specified number of seconds into the 
	* future. Pass 0 to get the state at the instant the method is called. Most of the time the application should
	* calculate the time until the photons will be emitted from the display and pass that time into the method.
	*
	* This is roughly analogous to the inverse of the view matrix in most applications, though 
	* many games will need to do some additional rotation or translation on top of the rotation
	* and translation provided by the head pose.
	*
	* For devices where bPoseIsValid is true the application can use the pose to position the device
	* in question. The provided array can be any size up to k_unMaxTrackedDeviceCount. 
	*
	* Seated experiences should call this method with TrackingUniverseSeated and receive poses relative
	* to the seated zero pose. Standing experiences should call this method with TrackingUniverseStanding 
	* and receive poses relative to the chaperone soft bounds. TrackingUniverseRawAndUncalibrated should 
	* probably not be used unless the application is the chaperone calibration tool itself, but will provide
	* poses relative to the hardware-specific coordinate system in the driver.
	*/
	virtual void GetDeviceToAbsoluteTrackingPose( TrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount ) = 0;

	/** Sets the zero pose for the seated tracker coordinate system to the current position and yaw of the HMD. After 
	* ResetSeatedZeroPose all GetDeviceToAbsoluteTrackingPose calls that pass TrackingUniverseSeated as the origin 
	* will be relative to this new zero pose. The new zero coordinate system will not change the fact that the Y axis 
	* is up in the real world, so the next pose returned from GetDeviceToAbsoluteTrackingPose after a call to 
	* ResetSeatedZeroPose may not be exactly an identity matrix. */
	virtual void ResetSeatedZeroPose() = 0;

	/** Returns the transform from the seated zero pose to the standing absolute tracking system. This allows 
	* applications to represent the seated origin to used or transform object positions from one coordinate
	* system to the other. 
	*
	* The seated origin may or may not be inside the soft or hard bounds returned by IVRChaperone. Its position 
	* depends on what the user has set in the chaperone calibration tool and previous calls to ResetSeatedZeroPose. */
	virtual HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() = 0;

	/** Returns the transform from the tracking origin to the standing absolute tracking system. This allows
	* applications to convert from raw tracking space to the calibrated standing coordinate system. */
	virtual HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() = 0;

	/** Get a sorted array of device indices of a given class of tracked devices (e.g. controllers).  Devices are sorted right to left
	* relative to the specified tracked device (default: hmd -- pass in -1 for absolute tracking space).  Returns the number of devices
	* in the list, or the size of the array needed if not large enough. */
	virtual uint32_t GetSortedTrackedDeviceIndicesOfClass( TrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex = k_unTrackedDeviceIndex_Hmd ) = 0;

	/** Returns the level of activity on the HMD. */
	virtual EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId ) = 0;

	// ------------------------------------
	// Property methods
	// ------------------------------------

	/** Returns the device class of a tracked device. If there has not been a device connected in this slot
	* since the application started this function will return TrackedDevice_Invalid. For previous detected
	* devices the function will return the previously observed device class. 
	*
	* To determine which devices exist on the system, just loop from 0 to k_unMaxTrackedDeviceCount and check
	* the device class. Every device with something other than TrackedDevice_Invalid is associated with an 
	* actual tracked device. */
	virtual TrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;

	/** Returns true if there is a device connected in this slot. */
	virtual bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;

	/** Returns a bool property. If the device index is not valid or the property is not a bool type this function will return false. */
	virtual bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L ) = 0;

	/** Returns a float property. If the device index is not valid or the property is not a float type this function will return 0. */
	virtual float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L ) = 0;

	/** Returns an int property. If the device index is not valid or the property is not a int type this function will return 0. */
	virtual int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L ) = 0;

	/** Returns a uint64 property. If the device index is not valid or the property is not a uint64 type this function will return 0. */
	virtual uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L ) = 0;

	/** Returns a matrix property. If the device index is not valid or the property is not a matrix type, this function will return identity. */
	virtual HmdMatrix34_t GetMatrix34TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L ) = 0;

	/** Returns a string property. If the device index is not valid or the property is not a float type this function will 
	* return 0. Otherwise it returns the length of the number of bytes necessary to hold this string including the trailing
	* null. Strings will generally fit in buffers of k_unTrackingStringSize characters. */
	virtual uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, TrackedPropertyError *pError = 0L ) = 0;

	/** returns a string that corresponds with the specified property error. The string will be the name 
	* of the error enum value for all valid error codes */
	virtual const char *GetPropErrorNameFromEnum( TrackedPropertyError error ) = 0;

	// ------------------------------------
	// Event methods
	// ------------------------------------

	/** Returns true and fills the event with the next event on the queue if there is one. If there are no events
	* this method returns false */
	virtual bool PollNextEvent( VREvent_t *pEvent ) = 0;

	/** Returns true and fills the event with the next event on the queue if there is one. If there are no events
	* this method returns false. Fills in the pose of the associated tracked device in the provided pose struct. 
	* This pose will always be older than the call to this function and should not be used to render the device. */
	virtual bool PollNextEventWithPose( TrackingUniverseOrigin eOrigin, vr::VREvent_t *pEvent, vr::TrackedDevicePose_t *pTrackedDevicePose ) = 0;

	/** returns the name of an EVREvent enum value */
	virtual const char *GetEventTypeNameFromEnum( EVREventType eType ) = 0;

	// ------------------------------------
	// Rendering helper methods
	// ------------------------------------

	/** Returns the stencil mesh information for the current HMD. If this HMD does not have a stencil mesh the vertex data and count will be
	* NULL and 0 respectively. This mesh is meant to be rendered into the stencil buffer (or into the depth buffer setting nearz) before rendering
	* each eye's view. The pixels covered by this mesh will never be seen by the user after the lens distortion is applied and based on visibility to the panels.
	* This will improve perf by letting the GPU early-reject pixels the user will never see before running the pixel shader.
	* NOTE: Render this mesh with backface culling disabled since the winding order of the vertices can be different per-HMD or per-eye.
	*/
	virtual HiddenAreaMesh_t GetHiddenAreaMesh( Hmd_Eye eEye ) = 0;


	// ------------------------------------
	// Controller methods
	// ------------------------------------

	/** Fills the supplied struct with the current state of the controller. Returns false if the controller index
	* is invalid. */
	virtual bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState ) = 0;

	/** fills the supplied struct with the current state of the controller and the provided pose with the pose of 
	* the controller when the controller state was updated most recently. Use this form if you need a precise controller
	* pose as input to your application when the user presses or releases a button. */
	virtual bool GetControllerStateWithPose( TrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, TrackedDevicePose_t *pTrackedDevicePose ) = 0;

	/** Trigger a single haptic pulse on a controller. After this call the application may not trigger another haptic pulse on this controller
	* and axis combination for 5ms. */
	virtual void TriggerHapticPulse( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec ) = 0;

	/** returns the name of an EVRButtonId enum value */
	virtual const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId ) = 0;

	/** returns the name of an EVRControllerAxisType enum value */
	virtual const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType ) = 0;

	/** Tells OpenVR that this process wants exclusive access to controller button states and button events. Other apps will be notified that 
	* they have lost input focus with a VREvent_InputFocusCaptured event. Returns false if input focus could not be captured for
	* some reason. */
	virtual bool CaptureInputFocus() = 0;

	/** Tells OpenVR that this process no longer wants exclusive access to button states and button events. Other apps will be notified 
	* that input focus has been released with a VREvent_InputFocusReleased event. */
	virtual void ReleaseInputFocus() = 0;

	/** Returns true if input focus is captured by another process. */
	virtual bool IsInputFocusCapturedByAnotherProcess() = 0;

	// ------------------------------------
	// Debug Methods
	// ------------------------------------

	/** Sends a request to the driver for the specified device and returns the response. The maximum response size is 32k,
	* but this method can be called with a smaller buffer. If the response exceeds the size of the buffer, it is truncated. 
	* The size of the response including its terminating null is returned. */
	virtual uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize ) = 0;


	// ------------------------------------
	// Firmware methods
	// ------------------------------------
	
	/** Performs the actual firmware update if applicable. 
	 * The following events will be sent, if VRFirmwareError_None was returned: VREvent_FirmwareUpdateStarted, VREvent_FirmwareUpdateFinished 
	 * Use the properties Prop_Firmware_UpdateAvailable_Bool, Prop_Firmware_ManualUpdate_Bool, and Prop_Firmware_ManualUpdateURL_String
	 * to figure our whether a firmware update is available, and to figure out whether its a manual update 
	 * Prop_Firmware_ManualUpdateURL_String should point to an URL describing the manual update process */
	virtual vr::VRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex ) = 0;


	// ------------------------------------
	// Display Mode methods
	// ------------------------------------

	/** Use to determine if the headset display is part of the desktop (i.e. extended) or hidden (i.e. direct mode). */
	virtual bool IsDisplayOnDesktop() = 0;

	/** Set the display visibility (true = extended, false = direct mode).  Return value of true indicates that the change was successful. */
	virtual bool SetDisplayVisibility( bool bIsVisibleOnDesktop ) = 0;

};

static const char * const IVRSystem_Version = "IVRSystem_006";

}

// ivrapplications.h
namespace vr
{

	/** Used for all errors reported by the IVRApplications interface */
	enum EVRApplicationError
	{
		VRApplicationError_None = 0,

		VRApplicationError_AppKeyAlreadyExists = 100,	// Only one application can use any given key
		VRApplicationError_NoManifest = 101,			// the running application does not have a manifest
		VRApplicationError_NoApplication = 102,			// No application is running
		VRApplicationError_InvalidIndex = 103,
		VRApplicationError_UnknownApplication = 104,	// the application could not be found
		VRApplicationError_IPCFailed = 105,				// An IPC failure caused the request to fail
		VRApplicationError_ApplicationAlreadyRunning = 106, 
		VRApplicationError_InvalidManifest = 107,
		VRApplicationError_InvalidApplication = 108,
		VRApplicationError_LaunchFailed = 109,			// the process didn't start
		VRApplicationError_ApplicationAlreadyStarting = 110, // the system was already starting the same application
		VRApplicationError_LaunchInProgress = 111,		// The system was already starting a different application
		VRApplicationError_OldApplicationQuitting = 112, 

		VRApplicationError_BufferTooSmall = 200,		// The provided buffer was too small to fit the requested data
		VRApplicationError_PropertyNotSet = 201,		// The requested property was not set
		VRApplicationError_UnknownProperty = 202,
	};

	/** The maximum length of an application key */
	static const uint32_t k_unMaxApplicationKeyLength = 128;

	/** these are the properties available on applications. */
	enum EVRApplicationProperty
	{
		VRApplicationProperty_Name_String				= 0,

		VRApplicationProperty_LaunchType_String			= 11,
		VRApplicationProperty_WorkingDirectory_String	= 12,
		VRApplicationProperty_BinaryPath_String			= 13,
		VRApplicationProperty_Arguments_String			= 14,
		VRApplicationProperty_URL_String				= 15,

		VRApplicationProperty_Description_String		= 50,
		VRApplicationProperty_NewsURL_String			= 51,
		VRApplicationProperty_ImagePath_String			= 52,
		VRApplicationProperty_Source_String				= 53,

		VRApplicationProperty_IsDashboardOverlay_Bool	= 60,
	};

	/** These are states the scene application startup process will go through. */
	enum EVRApplicationTransitionState
	{
		VRApplicationTransition_None = 0,

		VRApplicationTransition_OldAppQuitSent = 10,
		
		VRApplicationTransition_NewAppLaunched = 20,
	};


	class IVRApplications
	{
	public:

		// ---------------  Application management  --------------- //

		/** Adds an application manifest to the list to load when building the list of installed applications. 
		* Temporary manifests are not automatically loaded */
		virtual EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary = false ) = 0;

		/** Removes an application manifest from the list to load when building the list of installed applications. */
		virtual EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath ) = 0;

		/** Returns true if an application is installed */
		virtual bool IsApplicationInstalled( const char *pchAppKey ) = 0;

		/** Returns the number of applications available in the list */
		virtual uint32_t GetApplicationCount() = 0;

		/** Returns the key of the specified application. The index is at least 0 and is less than the return 
		* value of GetApplicationCount(). The buffer should be at least k_unMaxApplicationKeyLength in order to 
		* fit the key. */
		virtual EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;

		/** Returns the key of the application for the specified Process Id. The buffer should be at least 
		* k_unMaxApplicationKeyLength in order to fit the key. */
		virtual EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;

		/** Launches the application. The existing scene application will exit and then the new application will start.
		* This call is not valid for dashboard overlay applications. */
		virtual EVRApplicationError LaunchApplication( const char *pchAppKey ) = 0;

		/** Launches the dashboard overlay application if it is not already running. This call is only valid for 
		* dashboard overlay applications. */
		virtual EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey ) = 0;

		/** Identifies a running application. OpenVR can't always tell which process started in response
		* to a URL. This function allows a URL handler (or the process itself) to identify the app key 
		* for the now running application. Passing a process ID of 0 identifies the calling process. 
		* The application must be one that's known to the system via a call to AddApplicationManifest. */
		virtual EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey ) = 0;

		/** Returns the process ID for an application. Return 0 if the application was not found or is not running. */
		virtual uint32_t GetApplicationProcessId( const char *pchAppKey ) = 0;

		/** Returns a string for an applications error */
		virtual const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error ) = 0;

		// ---------------  Application properties  --------------- //

		/** Returns a value for an application property. The required buffer size to fit this value will be returned. */
		virtual uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError = nullptr ) = 0;

		/** Returns a value for an application property. The required buffer size to fit this value will be returned. */
		virtual bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError = nullptr ) = 0;

		/** Returns the application key for the home application. The buffer should be at least k_unMaxApplicationKeyLength bytes long. */
		virtual EVRApplicationError GetHomeApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;

		/** Sets the application key for the home application */
		virtual EVRApplicationError SetHomeApplication( const char *pchAppKey ) = 0;

		/** Sets the application auto-launch flag. This is only valid for applications which return true for VRApplicationProperty_IsDashboardOverlay_Bool. */
		virtual EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch ) = 0;

		/** Gets the application auto-launch flag. This is only valid for applications which return true for VRApplicationProperty_IsDashboardOverlay_Bool. */
		virtual bool GetApplicationAutoLaunch( const char *pchAppKey ) = 0;

		// ---------------  Transition methods --------------- //

		/** Returns the app key for the application that is starting up */
		virtual EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;

		/** Returns the application transition state */
		virtual EVRApplicationTransitionState GetTransitionState() = 0;

		/** Returns errors that would prevent the specified application from launching immediately. Calling this function will
		* cause the current scene application to quit, so only call it when you are actually about to launch something else.
		* What the caller should do about these failures depends on the failure:
		*   VRApplicationError_OldApplicationQuitting - An existing application has been told to quit. Wait for a VREvent_ProcessQuit
		*                                               and try again.
		*   VRApplicationError_ApplicationAlreadyStarting - This application is already starting. This is a permanent failure.
		*   VRApplicationError_LaunchInProgress	      - A different application is already starting. This is a permanent failure.
		*   VRApplicationError_None                   - Go ahead and launch. Everything is clear.
		*/
		virtual EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey ) = 0;

		/** Returns a string for an application transition state */
		virtual const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state ) = 0;


	};

	static const char * const IVRApplications_Version = "IVRApplications_001";

	/** Returns the current IVRApplications pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRApplications *VR_CALLTYPE VRApplications();

} // namespace vr
// ivrsettings.h
namespace vr
{
	enum EVRSettingsError
	{
		VRSettingsError_None = 0,
		VRSettingsError_IPCFailed = 1,
		VRSettingsError_WriteFailed = 2,
		VRSettingsError_ReadFailed = 3,
	};

	// The maximum length of a settings key
	static const uint32_t k_unMaxSettingsKeyLength = 128;

	class IVRSettings
	{
	public:
		virtual const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError ) = 0;

		virtual void Sync( EVRSettingsError *peError = nullptr ) = 0;

		virtual bool GetBool( const char *pchSection, const char *pchSettingsKey, bool bDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual float GetFloat( const char *pchSection, const char *pchSettingsKey, float flDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void GetString( const char *pchSection, const char *pchSettingsKey, char *pchValue, uint32_t unValueLen, const char *pchDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError = nullptr ) = 0;
	};

	//-----------------------------------------------------------------------------
	// steamvr keys

	static const char * const k_pch_SteamVR_Section = "steamvr";
	static const char * const k_pch_SteamVR_RequireHmd_String = "requireHmd";
	static const char * const k_pch_SteamVR_ForcedDriverKey_String = "forcedDriver";
	static const char * const k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
	static const char * const k_pch_SteamVR_EnableDistortion_Bool = "enableDistortion";
	static const char * const k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
	static const char * const k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
	static const char * const k_pch_SteamVR_SendSystemButtonToAllApps_Bool= "sendSystemButtonToAllApps";
	static const char * const k_pch_SteamVR_LogLevel_Int32 = "loglevel";
	static const char * const k_pch_SteamVR_IPD_Float = "ipd";
	static const char * const k_pch_SteamVR_Background_String = "background";

	//-----------------------------------------------------------------------------
	// lighthouse keys

	static const char * const k_pch_Lighthouse_Section = "driver_lighthouse";
	static const char * const k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
	static const char * const k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
	static const char * const k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";

	static const char * const k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
	static const char * const k_pch_Lighthouse_LighthouseName_String = "lighthousename";
	static const char * const k_pch_Lighthouse_MaxIncidenceAngleDegrees_Float = "maxincidenceangledegrees";
	static const char * const k_pch_Lighthouse_UseLighthouseDirect_Bool = "uselighthousedirect";
	static const char * const k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
	static const char * const k_pch_Lighthouse_OriginOffsetX_Float = "originoffsetx";
	static const char * const k_pch_Lighthouse_OriginOffsetY_Float = "originoffsety";
	static const char * const k_pch_Lighthouse_OriginOffsetZ_Float = "originoffsetz";
	static const char * const k_pch_Lighthouse_HeadingOffset_Float = "headingoffset";

	//-----------------------------------------------------------------------------
	// null keys

	static const char * const k_pch_Null_Section = "driver_null";
	static const char * const k_pch_Null_EnableNullDriver_Bool = "enable";
	static const char * const k_pch_Null_Id_String = "id";
	static const char * const k_pch_Null_SerialNumber_String = "serialNumber";
	static const char * const k_pch_Null_ModelNumber_String = "modelNumber";
	static const char * const k_pch_Null_WindowX_Int32 = "windowX";
	static const char * const k_pch_Null_WindowY_Int32 = "windowY";
	static const char * const k_pch_Null_WindowWidth_Int32 = "windowWidth";
	static const char * const k_pch_Null_WindowHeight_Int32 = "windowHeight";
	static const char * const k_pch_Null_RenderWidth_Int32 = "renderWidth";
	static const char * const k_pch_Null_RenderHeight_Int32 = "renderHeight";
	static const char * const k_pch_Null_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
	static const char * const k_pch_Null_DisplayFrequency_Float = "displayFrequency";

	//-----------------------------------------------------------------------------
	// notification keys
	static const char * const k_pch_Notifications_Section = "notifications";
	static const char * const k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";

	//-----------------------------------------------------------------------------
	// perf keys
	static const char * const k_pch_Perf_Section = "perfcheck";
	static const char * const k_pch_Perf_HeuristicActive_Bool = "heuristicActive";
	static const char * const k_pch_Perf_NotifyInHMD_Bool = "notifyInHMD";
	static const char * const k_pch_Perf_NotifyOnlyOnce_Bool = "notifyOnlyOnce";
	static const char * const k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
	static const char * const k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";

	//-----------------------------------------------------------------------------

	static const char * const IVRSettings_Version = "IVRSettings_001";

	/** Returns the current IVRSettings pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRSettings *VR_CALLTYPE VRSettings();

} // namespace vr
// ivrchaperone.h
namespace vr
{

#if defined(__linux__) || defined(__APPLE__) 
	// The 32-bit version of gcc has the alignment requirement for uint64 and double set to
	// 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
	// The 64-bit version of gcc has the alignment requirement for these types set to
	// 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
	// The 64-bit structure packing has to match the 32-bit structure packing for each platform.
	#pragma pack( push, 4 )
#else
	#pragma pack( push, 8 )
#endif

enum ChaperoneCalibrationState
{
	// OK!
	ChaperoneCalibrationState_OK = 1,									// Chaperone is fully calibrated and working correctly

	// Warnings
	ChaperoneCalibrationState_Warning = 100,
	ChaperoneCalibrationState_Warning_BaseStationMayHaveMoved = 101,	// A base station thinks that it might have moved
	ChaperoneCalibrationState_Warning_BaseStationRemoved = 102,			// There are less base stations than when calibrated
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,		// Seated bounds haven't been calibrated for the current tracking center

	// Errors
	ChaperoneCalibrationState_Error = 200,
	ChaperoneCalibrationState_Error_BaseStationUninitalized = 201,		// Tracking center hasn't be calibrated for at least one of the base stations
	ChaperoneCalibrationState_Error_BaseStationConflict = 202,			// Tracking center is calibrated, but base stations disagree on the tracking space
	ChaperoneCalibrationState_Error_SoftBoundsInvalid = 203,			// Soft bounds haven't been calibrated for the current tracking center
	ChaperoneCalibrationState_Error_HardBoundsInvalid = 204,			// Hard bounds haven't been calibrated for the current tracking center
};

/** SOFT BOUNDS ASSUMPTIONS
* Corners are in clockwise order.
* Tracking space center (0,0,0) is contained within the Soft Bounds.
* Angles of corners are between 25 and 155 degrees. 
* Quadrilateral formed is convex. 
* One side will run parallel to the X axis. 
* Height of every corner is 0Y (on the floor). */
struct ChaperoneSoftBoundsInfo_t
{
	HmdQuad_t quadCorners;
};

struct ChaperoneSeatedBoundsInfo_t
{
	HmdVector3_t vSeatedHeadPosition;
	HmdVector3_t vDeskEdgePositions[ 2 ];
};

/** HIGH LEVEL TRACKING SPACE ASSUMPTIONS:
* 0,0,0 is the preferred standing area center.
* 0Y is the floor height.
* -Z is the preferred forward facing direction. */
class IVRChaperone
{
public:

	/** Get the current state of Chaperone calibration. This state can change at any time during a session due to physical base station changes. */
	virtual ChaperoneCalibrationState GetCalibrationState() = 0;

	/** Returns the 4 corner positions of the Soft Bounds (also know as Safe Zone and Play Space). */
	virtual bool GetSoftBoundsInfo( ChaperoneSoftBoundsInfo_t *pInfo ) = 0;

	/** Returns the quads representing the Hard Bounds (static physical obstacles). */
	virtual bool GetHardBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) = 0;

	/** Returns the preferred seated position and front edge of their desk. */
	virtual bool GetSeatedBoundsInfo( ChaperoneSeatedBoundsInfo_t *pInfo ) = 0;

	/** Reload Chaperone data from the .vrchap file on disk. */
	virtual void ReloadInfo( void ) = 0;

	/** Optionally give the chaperone system a hit about the color and brightness in the scene **/
	virtual void SetSceneColor( HmdColor_t color ) = 0;

	/** Get the current chaperone bounds draw color and brightness **/
	virtual void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors ) = 0;
	
	/** Determine whether the bounds are showing right now **/
	virtual bool AreBoundsVisible() = 0;
	
	/** Force the bounds to show, mostly for utilities **/
	virtual void ForceBoundsVisible( bool bForce) = 0;
};

static const char * const IVRChaperone_Version = "IVRChaperone_002";

#pragma pack( pop )

}
// ivrcompositor.h
namespace vr
{

#if defined(__linux__) || defined(__APPLE__) 
	// The 32-bit version of gcc has the alignment requirement for uint64 and double set to
	// 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
	// The 64-bit version of gcc has the alignment requirement for these types set to
	// 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
	// The 64-bit structure packing has to match the 32-bit structure packing for each platform.
	#pragma pack( push, 4 )
#else
	#pragma pack( push, 8 )
#endif

/** Errors that can occur with the VR compositor */
enum VRCompositorError
{
	VRCompositorError_None						= 0,
	VRCompositorError_IncompatibleVersion		= 100,
	VRCompositorError_DoNotHaveFocus			= 101,
	VRCompositorError_InvalidTexture			= 102,
	VRCompositorError_IsNotSceneApplication		= 103,
};


/** Provides a single frame's timing information to the app */
struct Compositor_FrameTiming
{
	uint32_t size; // sizeof(Compositor_FrameTiming)
	double frameStart;
	float frameVSync; // seconds from frame start
	uint32_t droppedFrames;
	uint32_t frameIndex;
	vr::TrackedDevicePose_t pose;

	float prediction;

	float m_flFrameIntervalMs;
	float m_flSceneRenderCpuMs;
	float m_flSceneRenderGpuMs;
	float m_flCompositorRenderCpuMs;
	float m_flCompositorRenderGpuMs;
	float m_flPresentCallCpuMs;
	float m_flRunningStartMs;
};


#pragma pack( pop )


/** Allows the application to interact with the compositor */
class IVRCompositor
{
public:
	/** Returns the last error that occurred in the compositor */
	virtual uint32_t GetLastError( VR_OUT_STRING() char* pchBuffer, uint32_t unBufferSize ) = 0;

	/** Turns vsync on or off on the compositor window */
	virtual void SetVSync( bool bVSync ) = 0;

	/** Returns true if vsync is enabled in the compositor window */
	virtual bool GetVSync() = 0;

	/** Sets gamma for the compositor window */
	virtual void SetGamma( float fGamma ) = 0;

	/** Returns the gamma for the compositor window */
	virtual float GetGamma() = 0;

	/** Returns pose(s) to use to render scene (and optionally poses predicted two frames out for gameplay). */
	virtual VRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) = 0;

	/** Updated scene texture to display. If pBounds is NULL the entire texture will be used.
	*
	* OpenGL dirty state:
	*	glBindTexture
	*/
	virtual VRCompositorError Submit( Hmd_Eye eEye, GraphicsAPIConvention eTextureType, void* pTexture, const VRTextureBounds_t* pBounds, VRSubmitFlags_t nSubmitFlags = Submit_Default ) = 0;

	/** Clears the frame that was sent with the last call to Submit. This will cause the 
	* compositor to show the grid until Submit is called again. */
	virtual void ClearLastSubmittedFrame() = 0;

	/** Returns true if timing data is filled it.  Sets oldest timing info if nFramesAgo is larger than the stored history.
	* Be sure to set timing.size = sizeof(Compositor_FrameTiming) on struct passed in before calling this function. */
	virtual bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0 ) = 0;

	/** Fades the view on the HMD to the specified color. The fade will take fSeconds, and the color values are between 
	* 0.0 and 1.0. This color is faded on top of the scene based on the alpha parameter. Removing the fade color instantly 
	* would be FadeToColor( 0.0, 0.0, 0.0, 0.0, 0.0 ). */
	virtual void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false ) = 0;

	/** Fading the Grid in or out in fSeconds */
	virtual void FadeGrid( float fSeconds, bool bFadeIn ) = 0;

	/** Override the skybox used in the compositor (e.g. for during level loads when the app can't feed scene images fast enough). */
	virtual void SetSkyboxOverride( GraphicsAPIConvention eTextureType, void *pFront, void *pBack, void *pLeft, void *pRight, void *pTop, void *pBottom ) = 0;

	/** Resets compositor skybox back to defaults. */
	virtual void ClearSkyboxOverride() = 0;

	/** Brings the compositor window to the front. This is useful for covering any other window that may be on the HMD
	* and is obscuring the compositor window. */
	virtual void CompositorBringToFront() = 0;

	/** Pushes the compositor window to the back. This is useful for allowing other applications to draw directly to the HMD. */
	virtual void CompositorGoToBack() = 0;

	/** Tells the compositor process to clean up and exit. You do not need to call this function at shutdown. Under normal 
	* circumstances the compositor will manage its own life cycle based on what applications are running. */
	virtual void CompositorQuit() = 0;
	
	/** Return whether the compositor is fullscreen */
	virtual bool IsFullscreen() = 0;

	/** Sets tracking space returned by WaitGetPoses */
	virtual void SetTrackingSpace( TrackingUniverseOrigin eOrigin ) = 0;

	/** Gets current tracking space returned by WaitGetPoses */
	virtual TrackingUniverseOrigin GetTrackingSpace() = 0;

	/** Returns the process ID of the process that is currently rendering the scene */
	virtual uint32_t GetCurrentSceneFocusProcess() = 0;

	/** Returns true if the current process has the scene focus */
	virtual bool CanRenderScene() = 0;

	/** Creates a window on the primary monitor to display what is being shown in the headset. */
	virtual void ShowMirrorWindow() = 0;

	/** Closes the mirrow window. */
	virtual void HideMirrorWindow() = 0;

	/** Writes all images that the compositor knows about (including overlays) to a 'screenshots' folder in the SteamVR runtime root. */
	virtual void CompositorDumpImages() = 0;

	/** Returns the time in seconds left in the current (as identified by FrameTiming's frameIndex) frame.
	* Due to "running start", this value may roll over to the next frame before ever reaching 0.0. */
	virtual float GetFrameTimeRemaining() = 0;

	/** Returns the process ID of the process that rendered the last frame (or 0 if the compositor itself rendered the frame.)
	* Returns 0 when fading out from an app and the app's process Id when fading into an app. */
	virtual uint32_t GetLastFrameRenderer() = 0;
};

static const char * const IVRCompositor_Version = "IVRCompositor_008";

} // namespace vr


// ivrnotifications.h
namespace vr
{

#if defined(__linux__) || defined(__APPLE__) 
	// The 32-bit version of gcc has the alignment requirement for uint64 and double set to
	// 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
	// The 64-bit version of gcc has the alignment requirement for these types set to
	// 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
	// The 64-bit structure packing has to match the 32-bit structure packing for each platform.
	#pragma pack( push, 4 )
#else
	#pragma pack( push, 8 )
#endif

const char * const NotificationTypeFriendUpdate = "FriendUpdate";

// Used for passing graphic data
struct NotificationBitmap
{
	void *bytes;
	int32_t width;
	int32_t height;
	int32_t depth;
};

enum NotificationError_t
{
	k_ENotificationError_OK = 0,
	k_ENotificationError_Fail = 1,
	k_eNotificationError_InvalidParam = 2,
};

static const uint32_t k_unNotificationTypeMaxSize = 16;
static const uint32_t k_unNotificationTextMaxSize = 128;
static const uint32_t k_unNotificationCatagoryMaxSize = 32;

/** The types of events that could be posted (and what the parameters mean for each event type) */
/*enum NotificationEventType
{
	Notification_None = 0,

	Notification_Dismissed			= 101, // param1 = Device index
	Notification_BeginInteraction	= 102, // param1 = Device index
	Notification_Scroll				= 103, // param1 = Device index
	Notification_ClickOn			= 104, // param1 = Device index
	Notification_ClickOff			= 105, // param1 = Device index
};*/

/** An event posted by the server to all running applications */
/*struct NotificationEvent_t
{
	NotificationEventType eventType;
	int32_t x; // X coordinate in the notifications bitmap when the click happened
	int32_t y; // Y coordinate in the notifications bitmap when the click happened
	int32_t scroll_x; // X scrolling amount in the notifications bitmap coords
	int32_t scroll_y; // Y scrolling amount in the notifications bitmap coords
	uint32_t buttons; // Buttons pressed

	float eventAgeSeconds;
};*/

typedef uint32_t VRNotificationId;

// This struct will be used for the history list of notifications
struct NotificationItem
{
	VRNotificationId notificationId;
};



#pragma pack( pop )

/** Allows notification sources to interact with the VR system
	This current interface is not yet implemented. Do not use yet. */
class IVRNotifications
{
public:
	/** Returns the last error that occurred */
	virtual uint32_t GetErrorString( NotificationError_t error, VR_OUT_STRING() char* pchBuffer, uint32_t unBufferSize ) = 0;

	VR_METHOD_DESC( Create a new notification. )
	virtual NotificationError_t CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, const char *strType, const char *strText, const char *strCategory, const NotificationBitmap *photo, /* out */ vr::VRNotificationId *notificationId  ) = 0;

	VR_METHOD_DESC(Dismiss the notification)
	virtual NotificationError_t DismissNotification( vr::VRNotificationId notificationId ) = 0;

};

static const char * const IVRNotifications_Version = "IVRNotifications_001";

} // namespace vr


// ivroverlay.h
namespace vr
{

	/** The maximum length of an overlay key in bytes, counting the terminating null character. */
	static const uint32_t k_unVROverlayMaxKeyLength = 128;

	/** The maximum length of an overlay name in bytes, counting the terminating null character. */
	static const uint32_t k_unVROverlayMaxNameLength = 128;

	/** The maximum number of overlays that can exist in the system at one time. */
	static const uint32_t k_unMaxOverlayCount = 32;

	/** Types of input supported by VR Overlays */
	enum VROverlayInputMethod
	{
		VROverlayInputMethod_None		= 0, // No input events will be generated automatically for this overlay
		VROverlayInputMethod_Mouse		= 1, // Tracked controllers will get mouse events automatically
	};

	/** Allows the caller to figure out which overlay transform getter to call. */
	enum VROverlayTransformType
	{
		VROverlayTransform_Absolute					= 0,
		VROverlayTransform_TrackedDeviceRelative	= 1,
		VROverlayTransform_SystemOverlay			= 2,
	};

	/** Overlay control settings */
	enum VROverlayFlags
	{
		VROverlayFlags_None			= 0,

		// The following only take effect when rendered using the high quality render path (see SetHighQualityOverlay).
		VROverlayFlags_Curved		= 1,
		VROverlayFlags_RGSS4X		= 2,

		// Set this flag on a dashboard overlay to prevent a tab from showing up for that overlay
		VROverlayFlags_NoDashboardTab = 3,

	};

	struct VROverlayIntersectionParams_t
	{
		HmdVector3_t vSource;
		HmdVector3_t vDirection;
		TrackingUniverseOrigin eOrigin;
	};

	struct VROverlayIntersectionResults_t
	{
		HmdVector3_t vPoint;
		HmdVector3_t vNormal;
		HmdVector2_t vUVs;
		float fDistance;
	};

	// Input modes for the Big Picture gamepad text entry
	enum EGamepadTextInputMode
	{
		k_EGamepadTextInputModeNormal = 0,
		k_EGamepadTextInputModePassword = 1
	};


	// Controls number of allowed lines for the Big Picture gamepad text entry
	enum EGamepadTextInputLineMode
	{
		k_EGamepadTextInputLineModeSingleLine = 0,
		k_EGamepadTextInputLineModeMultipleLines = 1
	};

	class IVROverlay
	{
	public:

		// ---------------------------------------------
		// Overlay management methods
		// ---------------------------------------------

		/** Finds an existing overlay with the specified key. */
		virtual VROverlayError FindOverlay( const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle ) = 0;

		/** Creates a new named overlay. All overlays start hidden and with default settings. */
		virtual VROverlayError CreateOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pOverlayHandle ) = 0;

		/** Destroys the specified overlay. When an application calls VR_Shutdown all overlays created by that app are
		* automatically destroyed. */
		virtual VROverlayError DestroyOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Specify which overlay to use the high quality render path.  This overlay will be composited in during the distortion pass which
		* results in it drawing on top of everything else, but also at a higher quality as it samples the source texture directly rather than
		* rasterizing into each eye's render texture first.  Because if this, only one of these is supported at any given time.  It is most useful
		* for overlays that are expected to take up most of the user's view (e.g. streaming video). */
		virtual VROverlayError SetHighQualityOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Returns the overlay handle of the current overlay being rendered using the single high quality overlay render path.
		* Otherwise it will return k_ulOverlayHandleInvalid. */
		virtual vr::VROverlayHandle_t GetHighQualityOverlay() = 0;

		/** Fills the provided buffer with the string key of the overlay. Returns the size of buffer required to store the key, including
		* the terminating null character. k_unVROverlayMaxKeyLength will be enough bytes to fit the string. */
		virtual uint32_t GetOverlayKey( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, VROverlayError *pError = 0L ) = 0;

		/** Fills the provided buffer with the friendly name of the overlay. Returns the size of buffer required to store the key, including
		* the terminating null character. k_unVROverlayMaxNameLength will be enough bytes to fit the string. */
		virtual uint32_t GetOverlayName( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, VROverlayError *pError = 0L ) = 0;

		/** Gets the raw image data from an overlay. Overlay image data is always returned as RGBA data, 4 bytes per pixel. If the buffer is not large enough, width and height 
		* will be set and VROverlayError_ArrayTooSmall is returned. */
		virtual VROverlayError GetOverlayImageData( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight ) = 0;

		/** returns a string that corresponds with the specified overlay error. The string will be the name 
		* of the error enum value for all valid error codes */
		virtual const char *GetOverlayErrorNameFromEnum( VROverlayError error ) = 0;


		// ---------------------------------------------
		// Overlay rendering methods
		// ---------------------------------------------

		/** Specify flag setting for a given overlay */
		virtual VROverlayError SetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled ) = 0;

		/** Sets flag setting for a given overlay */
		virtual VROverlayError GetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled ) = 0;

		/** Sets the color tint of the overlay quad. Use 0.0 to 1.0 per channel. */
		virtual VROverlayError SetOverlayColor( VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue ) = 0;

		/** Gets the color tint of the overlay quad. */
		virtual VROverlayError GetOverlayColor( VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue ) = 0;

		/** Sets the alpha of the overlay quad. Use 1.0 for 100 percent opacity to 0.0 for 0 percent opacity. */
		virtual VROverlayError SetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float fAlpha ) = 0;

		/** Gets the alpha of the overlay quad. By default overlays are rendering at 100 percent alpha (1.0). */
		virtual VROverlayError GetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float *pfAlpha ) = 0;

		/** Sets the gamma of the overlay quad. Use 2.2 when providing a texture in linear color space. */
		virtual VROverlayError SetOverlayGamma( VROverlayHandle_t ulOverlayHandle, float fGamma ) = 0;

		/** Gets the gamma of the overlay quad.  Be default overlays are rendered with 1.0 gamma. */
		virtual VROverlayError GetOverlayGamma( VROverlayHandle_t ulOverlayHandle, float *pfGamma ) = 0;

		/** Sets the width of the overlay quad in meters. By default overlays are rendered on a quad that is 1 meter across */
		virtual VROverlayError SetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float fWidthInMeters ) = 0;

		/** Returns the width of the overlay quad in meters. By default overlays are rendered on a quad that is 1 meter across */
		virtual VROverlayError GetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters ) = 0;

		/** For high-quality curved overlays only, sets the distance range in meters from the overlay used to automatically curve
		* the surface around the viewer.  Min is distance is when the surface will be most curved.  Max is when least curved. */
		virtual VROverlayError SetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters ) = 0;

		/** For high-quality curved overlays only, gets the distance range in meters from the overlay used to automatically curve
		* the surface around the viewer.  Min is distance is when the surface will be most curved.  Max is when least curved. */
		virtual VROverlayError GetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters ) = 0;
		/** Sets the part of the texture to use for the overlay. UV Min is the upper left corner and UV Max is the lower right corner. */
		virtual VROverlayError SetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds ) = 0;

		/** Gets the part of the texture to use for the overlay. UV Min is the upper left corner and UV Max is the lower right corner. */
		virtual VROverlayError GetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds ) = 0;

		/** Returns the transform type of this overlay. */
		virtual VROverlayError GetOverlayTransformType( VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType ) = 0;

		/** Sets the transform to absolute tracking origin. */
		virtual VROverlayError SetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, TrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) = 0;

		/** Gets the transform if it is absolute. Returns an error if the transform is some other type. */
		virtual VROverlayError GetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, TrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) = 0;

		/** Sets the transform to relative to the transform of the specified tracked device. */
		virtual VROverlayError SetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) = 0;

		/** Gets the transform if it is relative to a tracked device. Returns an error if the transform is some other type. */
		virtual VROverlayError GetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) = 0;

		/** Shows the VR overlay.  For dashboard overlays, only the Dashboard Manager is allowed to call this. */
		virtual VROverlayError ShowOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Hides the VR overlay.  For dashboard overlays, only the Dashboard Manager is allowed to call this. */
		virtual VROverlayError HideOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Returns true if the overlay is visible. */
		virtual bool IsOverlayVisible( VROverlayHandle_t ulOverlayHandle ) = 0;


		// ---------------------------------------------
		// Overlay input methods
		// ---------------------------------------------

		/** Returns true and fills the event with the next event on the overlay's event queue, if there is one. 
		* If there are no events this method returns false */
		virtual bool PollNextOverlayEvent( VROverlayHandle_t ulOverlayHandle, VREvent_t *pEvent ) = 0;

		/** Returns the current input settings for the specified overlay. */
		virtual VROverlayError GetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod ) = 0;

		/** Sets the input settings for the specified overlay. */
		virtual VROverlayError SetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod ) = 0;

		/** Gets the mouse scaling factor that is used for mouse events. The actual texture may be a different size, but this is
		* typically the size of the underlying UI in pixels. */
		virtual VROverlayError GetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale ) = 0;

		/** Sets the mouse scaling factor that is used for mouse events. The actual texture may be a different size, but this is
		* typically the size of the underlying UI in pixels. */
		virtual VROverlayError SetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale ) = 0;

		/** Computes the overlay-space pixel coordinates of where the ray intersects the overlay with the
		* specified settings. Returns false if there is no intersection. */
		virtual bool ComputeOverlayIntersection( VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults ) = 0;

		/** Processes mouse input from the specified controller as though it were a mouse pointed at a compositor overlay with the
		* specified settings. The controller is treated like a laser pointer on the -z axis. The point where the laser pointer would
		* intersect with the overlay is the mouse position, the trigger is left mouse, and the track pad is right mouse. 
		*
		* Return true if the controller is pointed at the overlay and an event was generated. */
		virtual bool HandleControllerOverlayInteractionAsMouse( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex ) = 0;

		/** Returns true if the specified overlay has input focus. An overlay has input focus when it is the last overlay "moused over" 
		* by the virtual mouse pointer */
		virtual bool IsFocusOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		// ---------------------------------------------
		// Overlay texture methods
		// ---------------------------------------------

		/** Texture to draw for the overlay. IVRCompositor::SetGraphicsDevice must be called before 
		* this function. This function can only be called by the overlay's renderer process.
		*
		* If pBounds is NULL the entire texture will be used.
		*
		* OpenGL dirty state:
		*	glBindTexture
		*/
		virtual VROverlayError SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, GraphicsAPIConvention eTextureType, void* pTexture ) = 0;

		/** Use this to tell the overlay system to release the texture set for this overlay. */
		virtual VROverlayError ClearOverlayTexture( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Separate interface for providing the data as a stream of bytes, but there is an upper bound on data 
		* that can be sent. This function can only be called by the overlay's renderer process. */
		virtual VROverlayError SetOverlayRaw( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth ) = 0;

		/** Separate interface for providing the image through a filename: can be png or jpg, and should not be bigger than 1920x1080.
		* This function can only be called by the overlay's renderer process */
		virtual VROverlayError SetOverlayFromFile( VROverlayHandle_t ulOverlayHandle, const char *pchFilePath ) = 0;

		// ----------------------------------------------
		// Dashboard Overlay Methods
		// ----------------------------------------------

		/** Creates a dashboard overlay and returns its handle */
		virtual VROverlayError CreateDashboardOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle ) = 0;

		/** Returns true if the dashboard is visible */
		virtual bool IsDashboardVisible() = 0;

		/** returns true if the dashboard is visible and the specified overlay is the active system Overlay */
		virtual bool IsActiveDashboardOverlay( VROverlayHandle_t ulOverlayHandle ) = 0;

		/** Sets the dashboard overlay to only appear when the specified process ID has scene focus */
		virtual VROverlayError SetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId ) = 0;

		/** Gets the process ID that this dashboard overlay requires to have scene focus */
		virtual VROverlayError GetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId ) = 0;

		/** Shows the dashboard. */
		virtual void ShowDashboard( const char *pchOverlayToShow ) = 0;

		// ---------------------------------------------
		// Keyboard methods
		// ---------------------------------------------
		
		/** Show the virtual keyboard to accept input **/
		virtual VROverlayError ShowKeyboard( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode ) = 0;

		/** Get the text that was entered into the text input **/
		virtual uint32_t GetKeyboardText( VR_OUT_STRING() char *pchText, uint32_t cchText ) = 0;

		/** Hide the virtual keyboard **/
		virtual void HideKeyboard() = 0;
	};

	static const char * const IVROverlay_Version = "IVROverlay_005";

} // namespace vr
// ivrrendermodels.h
namespace vr
{

class IVRRenderModels
{
public:


	/** Loads and returns a render model for use in the application. pchRenderModelName should be a render model name
	* from the Prop_RenderModelName_String property or an absolute path name to a render model on disk. 
	*
	* The resulting render model is valid until VR_Shutdown() is called or until FreeRenderModel() is called. When the 
	* application is finished with the render model it should call FreeRenderModel() to free the memory associated
	* with the model.
	*
	* The method returns false if the model could not be loaded.
	*
	* The API expects that this function will be called at startup or when tracked devices are connected and disconnected.
	* If it is called every frame it will hurt performance.
	*/
	virtual bool LoadRenderModel( const char *pchRenderModelName, RenderModel_t *pRenderModel ) = 0;

	/** Frees a previously returned render model */
	virtual void FreeRenderModel( RenderModel_t *pRenderModel ) = 0;

	/** Use this to get the names of available render models.  Index does not correlate to a tracked device index, but
	* is only used for iterating over all available render models.  If the index is out of range, this function will return 0.
	* Otherwise, it will return the size of the buffer required for the name. */
	virtual uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen ) = 0;

	/** Returns the number of available render models. */
	virtual uint32_t GetRenderModelCount() = 0;


};

static const char * const IVRRenderModels_Version = "IVRRenderModels_001";

}

// ivrcontrolpanel.h
namespace vr
{

class IVRControlPanel
{
public:

	// ------------------------------------
	// Driver enumeration methods
	// ------------------------------------

	/** the number of active drivers */
	virtual uint32_t GetDriverCount() = 0;

	/** The ID of the specified driver as a UTF-8 string. Returns the length of the ID in bytes. If 
	* the buffer is not large enough to fit the ID an empty string will be returned. In general, 128 bytes
	* will be enough to fit any ID. */
	virtual uint32_t GetDriverId( uint32_t unDriverIndex, char *pchBuffer, uint32_t unBufferLen ) = 0;

	// ------------------------------------
	// Display Enumeration Methods
	// ------------------------------------

	/** the number of active displays on the specified driver */
	virtual uint32_t GetDriverDisplayCount( const char *pchDriverId ) = 0;

	/** The ID of the specified display in the specified driver as a UTF-8 string. Returns the 
	* length of the ID in bytes. If the buffer is not large enough to fit the ID an empty
	* string will be returned. In general, 128 bytes will be enough to fit any ID. */
	virtual uint32_t GetDriverDisplayId( const char *pchDriverId, uint32_t unDisplayIndex, char *pchBuffer, uint32_t unBufferLen ) = 0;

	// ------------------------------------
	// Display Detail Methods
	// ------------------------------------

	/** The model name of the specified driver in the specified driver as a UTF-8 string. Returns the 
	* length of the model name in bytes. If the buffer is not large enough to fit the model name an empty
	* string will be returned. In general, 128 bytes will be enough to fit any model name. Returns 0 if
	* the display or driver was not found. */
	virtual uint32_t GetDriverDisplayModelNumber( const char *pchDriverId, const char *pchDisplayId, char *pchBuffer, uint32_t unBufferLen ) = 0;

	/** The serial number of the specified driver in the specified driver as a UTF-8 string. Returns the 
	* length of the serial number in bytes. If the buffer is not large enough to fit the serial number an empty
	* string will be returned. In general, 128 bytes will be enough to fit any model name. Returns 0 if
	* the display or driver was not found. */
	virtual uint32_t GetDriverDisplaySerialNumber( const char *pchDriverId, const char *pchDisplayId, char *pchBuffer, uint32_t unBufferLen ) = 0;

	/** Returns the IVRSystem interface for the current display that matches the specified version number. 
	* This is usually unnecessary and the return value of VR_Init can be used without calling this method. */
	VR_IGNOREATTR()
	virtual class IVRSystem *GetCurrentDisplayInterface( const char *pchHmdInterfaceVersion ) = 0;

	// ------------------------------------
	// Shared Resource Methods
	// ------------------------------------

	/** Loads the specified resource into the provided buffer if large enough.
	* Returns the size in bytes of the buffer required to hold the specified resource. */
	virtual uint32_t LoadSharedResource( const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen ) = 0;

	// ------------------------------------
	// IPD Methods
	// ------------------------------------

	/** Gets the current IPD (Interpupillary Distance) in meters. */
	virtual float GetIPD() = 0;

	/** Sets the current IPD (Interpupillary Distance) in meters. */
	virtual void SetIPD( float fIPD ) = 0;

	// ------------------------------------
	// Compositor Methods
	// ------------------------------------

	/** Returns the IVRCompositor interface that matches the specified interface version.  This will only
	* return the compositor interface if it has already been initialized by the current process. */
	virtual class vr::IVRCompositor *GetCurrentCompositorInterface( const char *pchInterfaceVersion ) = 0;

	// ------------------------------------
	// Process control Methods
	// ------------------------------------

	/** Tells the specified OpenVR process to quit. If the process ID is 0, all processes will be told to quit,
	* ending with the process submitting the request. Returns false if the request could not be sent. */
	virtual bool QuitProcess( uint32_t pidProcessToQuit ) = 0;

	/** Starts a process and returns the PID or 0 if the process failed to start. */
	virtual uint32_t StartVRProcess( const char *pchExecutable, const char **pchArguments, uint32_t unArgumentCount, const char *pchWorkingDirectory) = 0;

	/** Sets the master process for OpenVR. When the master process exits VRServer will send quit messages to every other process
	* to start the shutdown process */
	virtual void SetMasterProcessToThis() = 0;


};

static const char * const IVRControlPanel_Version = "IVRControlPanel_001";

}// End

#endif // _OPENVR_API


namespace vr
{
	/** called when lib is loaded */
	VR_INTERFACE jint JNI_OnLoad(JavaVM* aVm, void* aReserved);

	/** Finds the active installation of the VR API and initializes it. The provided path must be absolute 
	* or relative to the current working directory. These are the local install versions of the equivalent
	* functions in steamvr.h and will work without a local Steam install.
	*
	* This path is to the "root" of the VR API install. That's the directory with 
	* the "drivers" directory and a platform (i.e. "win32") directory in it, not the directory with the DLL itself.
	*/
	VR_INTERFACE vr::IVRSystem *VR_CALLTYPE VR_Init( vr::HmdError *peError, vr::EVRApplicationType eApplicationType = vr::VRApplication_Scene );

	/** unloads vrclient.dll. Any interface pointers from the interface are 
	* invalid after this point */
	VR_INTERFACE void VR_CALLTYPE VR_Shutdown();

	/** Returns true if there is an HMD attached. This check is as lightweight as possible and
	* can be called outside of VR_Init/VR_Shutdown. It should be used when an application wants
	* to know if initializing VR is a possibility but isn't ready to take that step yet.
	*/
	VR_INTERFACE bool VR_CALLTYPE VR_IsHmdPresent();

	/** Returns true if the OpenVR runtime is installed. */
	VR_INTERFACE bool VR_CALLTYPE VR_IsRuntimeInstalled();

	/** Returns the string version of an HMD error. This function may be called outside of VR_Init()/VR_Shutdown(). */
	VR_INTERFACE const char *VR_CALLTYPE VR_GetStringForHmdError( vr::HmdError error );

	/** Returns the interface of the specified version. This method must be called after VR_Init. The
	* pointer returned is valid until VR_Shutdown is called.
	*/
	VR_INTERFACE void *VR_CALLTYPE VR_GetGenericInterface( const char *pchInterfaceVersion, vr::HmdError *peError );

	/** Returns the current IVRSystem pointer or NULL if VR_Init has not been called successfully */
	VR_INTERFACE vr::IVRSystem *VR_CALLTYPE VRSystem();

	/** Returns the current IVRChaperone pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRChaperone *VR_CALLTYPE VRChaperone();

	/** Returns the current IVRCompositor pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRCompositor *VR_CALLTYPE VRCompositor();

	/** Returns the current IVROverlay pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVROverlay *VR_CALLTYPE VROverlay();

	/** Returns the current IVRRenderModels pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRRenderModels *VR_CALLTYPE VRRenderModels();

	/** Returns the current IVRControlPanel pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRControlPanel *VR_CALLTYPE VRControlPanel();


	/** start to head tracking */
	VR_INTERFACE void VR_CALLTYPE Start(int width, int height, float xdpi, float ydpi);

	/** stop head tracking */
	VR_INTERFACE void VR_CALLTYPE Stop();

	/** get head pose */
	VR_INTERFACE void VR_CALLTYPE GetHeadPose(float* pose, float fps);

	/** get profile */
	VR_INTERFACE void VR_CALLTYPE GetProfile(float* profile);

	/** get view parameters */
	VR_INTERFACE void VR_CALLTYPE GetViewParameters(float* viewParams);

	/** apply distortion and render to screen */
	VR_INTERFACE void VR_CALLTYPE ApplyDistortionAndRender(int textureId);

}
