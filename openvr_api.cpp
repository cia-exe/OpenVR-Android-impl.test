// openvr_api.cpp : Defines the exported functions for the DLL application.
//
#include <jni.h>
#include <stdio.h>
#include "Precomp.h"

#include <math.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/input.h>
#include "Matrices.h"


//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>

namespace vr
{
	namespace mobile
	{

		class VrSystem : public IVRSystem
		{

		protected:

			void Release()
			{
				SAFE_DELETE_PTR(m_pVRCompositor);
				SAFE_DELETE_PTR(m_pVRChaperone);
				SAFE_DELETE_PTR(m_pVROverlay);
				SAFE_DELETE_PTR(m_pVRRenderModels);
				SAFE_DELETE_PTR(m_pVRControlPanel);
				SAFE_DELETE_PTR(m_pVRTrackedCamera);
			}
		public:

			VrSystem() : m_pVRCompositor(0), m_pVRChaperone(0), m_pVROverlay(0), m_pVRRenderModels(0), m_pVRControlPanel(0), m_pVRTrackedCamera(0)
			{
				CHECKPOINT();

				int fd_kb; // /dev/input/event1
				int fd_gpad; //dev/input/event6


				fd_kb = open("/dev/input/event1", O_RDWR);
				if (fd_kb <= 0) {
					_TraceFormat("!!!! error open keyboard:%d\n", errno);
				}
				else
				{
					_TraceFormat("!!!! OK open keyboard:%d\n", errno);
				}

				fd_gpad = open("/dev/input/event6", O_RDWR);
				if (fd_gpad <= 0) {
					_TraceFormat("!!!! error open gamepad:%d\n", errno);
				}
				else
				{
					_TraceFormat("!!!! OK open Gamepad:%d\n", errno);
				}

				if(fd_kb) close(fd_kb);
				if (fd_gpad) close(fd_gpad);

			}


			virtual ~VrSystem()
			{
				CHECKPOINT();
				Release();
			}

			// ------------------------------------
			// Display Methods
			// ------------------------------------

			/** Size and position that the window needs to be on the VR display. */
			virtual void GetWindowBounds(int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight)
			{
				CHECKPOINT();
			}

			/** Suggested size for the intermediate render target that the distortion pulls from. */
			virtual void GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight)
			{
				CHECKPOINT();
				//*pnWidth = 1920/2;
				//*pnHeight = 1080;
				*pnWidth = 1920 / 2;
				*pnHeight = 1080 ;
			}

			/** Gets the viewport in the frame buffer to draw the output of the distortion into */
			virtual void GetEyeOutputViewport(Hmd_Eye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight)
			{
				CHECKPOINT();
			}

			/** The projection matrix for the specified eye */
			virtual HmdMatrix44_t GetProjectionMatrix(Hmd_Eye eEye, float fNearZ, float fFarZ, GraphicsAPIConvention eProjType)
			{
				CHECKPOINT();

				HmdMatrix44_t mat;
				memset(mat.m, 0.0f, sizeof(mat.m[0][0]) * 4 * 4);
				return mat;
			}

			/** The components necessary to build your own projection matrix in case your
			* application is doing something fancy like infinite Z */
			virtual void GetProjectionRaw(Hmd_Eye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom)
			{
				CHECKPOINT_C(eEye);

				const float fShift=0.2f;
				if (eEye == Eye_Left)
				{
					*pfLeft = -1.0f + fShift;
					*pfRight = 1.0f - fShift;
					*pfTop = -1.0f;
					*pfBottom = 1.0f;

				}
				else if (eEye == Eye_Right)
				{
					*pfLeft = -1.0f - fShift;
					*pfRight = 1.0f + fShift;
					*pfTop = -1.0f;
					*pfBottom = 1.0f;
				}
				else
					WARNPOINT();


			}

			/** Returns the result of the distortion function for the specified eye and input UVs. UVs go from 0,0 in
			* the upper left of that eye's viewport and 1,1 in the lower right of that eye's viewport. */
			virtual DistortionCoordinates_t ComputeDistortion(Hmd_Eye eEye, float fU, float fV)
			{
				CHECKPOINT();
				DistortionCoordinates_t r;
				return r;
			}

			/** Returns the transform from eye space to the head space. Eye space is the per-eye flavor of head
			* space that provides stereo disparity. Instead of Model * View * Projection the sequence is Model * View * Eye^-1 * Projection.
			* Normally View and Eye^-1 will be multiplied together and treated as View in your application.
			*/
			virtual HmdMatrix34_t GetEyeToHeadTransform(Hmd_Eye eEye)
			{
				CHECKPOINT_C(eEye);

				HmdMatrix34_t m;
				memset(m.m, 0.0f, sizeof(m.m[0][0]) * 3 * 4);
				m.m[0][0] = 1.0f;
				m.m[1][1] = 1.0f;
				m.m[2][2] = 1.0f;


				if (eEye == Eye_Left)
				{
					m.m[0][3] = -5.0f;
					//m.m[1][3] = 1.0f;
					//m.m[2][3] = 1.0f;
				}
				else if (eEye == Eye_Right)
				{
					m.m[0][3] = 5.0f;
					//m.m[1][3] = 1.0f;
					//m.m[2][3] = 1.0f;
				}
				else
					WARNPOINT();

				return m;
			}

			/** Returns the number of elapsed seconds since the last recorded vsync event. This
			*	will come from a vsync timer event in the timer if possible or from the application-reported
			*   time if that is not available. If no vsync times are available the function will
			*   return zero for vsync time and frame counter and return false from the method. */
			virtual bool GetTimeSinceLastVsync(float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter)
			{
				CHECKPOINT();
				return false;
			}

			/** [D3D9 Only]
			* Returns the adapter index that the user should pass into CreateDevice to set up D3D9 in such
			* a way that it can go full screen exclusive on the HMD. Returns -1 if there was an error.
			*/
			virtual int32_t GetD3D9AdapterIndex()
			{
				CHECKPOINT();
				return 0;
			}

			/** [D3D10/11 Only]
			* Returns the adapter index and output index that the user should pass into EnumAdapters and EnumOutputs
			* to create the device and swap chain in DX10 and DX11. If an error occurs both indices will be set to -1.
			*/
			virtual void GetDXGIOutputInfo(int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex)
			{
				CHECKPOINT();
			}

			/** [Windows Only]
			* Notifies the system that the VR output will appear in a particular window.
			*/
			virtual bool AttachToWindow(void *hWnd)
			{
				CHECKPOINT();
				return false;
			}

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
			virtual void GetDeviceToAbsoluteTrackingPose(TrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount)
			{
				CHECKPOINT();
			}

			/** Sets the zero pose for the seated tracker coordinate system to the current position and yaw of the HMD. After
			* ResetSeatedZeroPose all GetDeviceToAbsoluteTrackingPose calls that pass TrackingUniverseSeated as the origin
			* will be relative to this new zero pose. The new zero coordinate system will not change the fact that the Y axis
			* is up in the real world, so the next pose returned from GetDeviceToAbsoluteTrackingPose after a call to
			* ResetSeatedZeroPose may not be exactly an identity matrix. */
			virtual void ResetSeatedZeroPose() {
				CHECKPOINT();
			}

			/** Returns the transform from the seated zero pose to the standing absolute tracking system. This allows
			* applications to represent the seated origin to used or transform object positions from one coordinate
			* system to the other.
			*
			* The seated origin may or may not be inside the soft or hard bounds returned by IVRChaperone. Its position
			* depends on what the user has set in the chaperone calibration tool and previous calls to ResetSeatedZeroPose. */
			virtual HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose()
			{
				CHECKPOINT();

				HmdMatrix34_t r;
				return r;
			}

			/** Returns the transform from the tracking origin to the standing absolute tracking system. This allows
			* applications to convert from raw tracking space to the calibrated standing coordinate system. */
			virtual HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose()
			{
				CHECKPOINT();

				HmdMatrix34_t r;
				return r;
			}

			/** Get a sorted array of device indices of a given class of tracked devices (e.g. controllers).  Devices are sorted right to left
			* relative to the specified tracked device (default: hmd -- pass in -1 for absolute tracking space).  Returns the number of devices
			* in the list, or the size of the array needed if not large enough. */
			virtual uint32_t GetSortedTrackedDeviceIndicesOfClass(TrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex = k_unTrackedDeviceIndex_Hmd)
			{
				CHECKPOINT();
				return 0;
			}

			/** Returns the level of activity on the HMD. */
			virtual EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId)
			{
				CHECKPOINT();
			}

			/** Convenience utility to apply the specified transform to the specified pose.
			*   This properly transforms all pose components, including velocity and angular velocity
			*/
			virtual void ApplyTransform(TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t & trackedDevicePose, const HmdMatrix34_t & transform)
			{
				CHECKPOINT();
			}

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
			virtual TrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex)
			{
				CHECKPOINT();
				return TrackedDeviceClass_Invalid;
			}

			/** Returns true if there is a device connected in this slot. */
			virtual bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex)
			{
				_TraceFormat("****(%p) check %s, line: %d (%d)\n", this, __X_FUNCTION__, __LINE__, unDeviceIndex);

				if (k_unTrackedDeviceIndex_Hmd == unDeviceIndex)
				{
					return true;
				}

				return false;
			}

			/** Returns a bool property. If the device index is not valid or the property is not a bool type this function will return false. */
			virtual bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L)
			{
				CHECKPOINT();
				return false;
			}

			/** Returns a float property. If the device index is not valid or the property is not a float type this function will return 0. */
			virtual float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L)
			{
				CHECKPOINT();
				return 0.0f;
			}

			/** Returns an int property. If the device index is not valid or the property is not a int type this function will return 0. */
			virtual int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L)
			{
				CHECKPOINT();
				return 0;
			}

			/** Returns a uint64 property. If the device index is not valid or the property is not a uint64 type this function will return 0. */
			virtual uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L)
			{
				CHECKPOINT();
				return 0;
			}

			/** Returns a matrix property. If the device index is not valid or the property is not a matrix type, this function will return identity. */
			virtual HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError = 0L)
			{
				CHECKPOINT();
				HmdMatrix34_t m;
				return m;
			}

			/** Returns a string property. If the device index is not valid or the property is not a string type this function will
			* return 0. Otherwise it returns the length of the number of bytes necessary to hold this string including the trailing
			* null. Strings will generally fit in buffers of k_unTrackingStringSize characters. */
			virtual uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, TrackedPropertyError *pError = 0L)
			{
				CHECKPOINT();
				int x = snprintf(pchValue, unBufferSize, "<%d_%d>", unDeviceIndex, prop);
				if (pError) *pError = TrackedProp_Success;
				return x + 1;
			}

			/** returns a string that corresponds with the specified property error. The string will be the name
			* of the error enum value for all valid error codes */
			virtual const char *GetPropErrorNameFromEnum(TrackedPropertyError error)
			{
				_TraceFormat("****(%p) check %s, line: %d (0x%x)\n", this, __X_FUNCTION__, __LINE__, error);
				return "unknowb error...";
			}

			// ------------------------------------
			// Event methods
			// ------------------------------------

			/** Returns true and fills the event with the next event on the queue if there is one. If there are no events
			* this method returns false */
			virtual bool PollNextEvent(VREvent_t *pEvent)
			{
				CHECKPOINT();
				return false;
			}

			/** Returns true and fills the event with the next event on the queue if there is one. If there are no events
			* this method returns false. Fills in the pose of the associated tracked device in the provided pose struct.
			* This pose will always be older than the call to this function and should not be used to render the device. */
			virtual bool PollNextEventWithPose(TrackingUniverseOrigin eOrigin, vr::VREvent_t *pEvent, vr::TrackedDevicePose_t *pTrackedDevicePose)
			{
				CHECKPOINT();
				return false;
			}

			/** returns the name of an EVREvent enum value */
			virtual const char *GetEventTypeNameFromEnum(EVREventType eType)
			{
				_TraceFormat("****(%p) check %s, line: %d (0x%x)\n", this, __X_FUNCTION__, __LINE__, eType);
				return "unknown event...";
			}

			// ------------------------------------
			// Rendering helper methods
			// ------------------------------------

			/** Returns the stencil mesh information for the current HMD. If this HMD does not have a stencil mesh the vertex data and count will be
			* NULL and 0 respectively. This mesh is meant to be rendered into the stencil buffer (or into the depth buffer setting nearz) before rendering
			* each eye's view. The pixels covered by this mesh will never be seen by the user after the lens distortion is applied and based on visibility to the panels.
			* This will improve perf by letting the GPU early-reject pixels the user will never see before running the pixel shader.
			* NOTE: Render this mesh with backface culling disabled since the winding order of the vertices can be different per-HMD or per-eye.
			*/
			virtual HiddenAreaMesh_t GetHiddenAreaMesh(Hmd_Eye eEye)
			{
				CHECKPOINT();
				HiddenAreaMesh_t m;
				m.pVertexData = NULL;
				m.unTriangleCount = 0;
				return m;
			}


			// ------------------------------------
			// Controller methods
			// ------------------------------------

			/** Fills the supplied struct with the current state of the controller. Returns false if the controller index
			* is invalid. */
			virtual bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState)
			{
				CHECKPOINT();
				return false;
			}

			/** fills the supplied struct with the current state of the controller and the provided pose with the pose of
			* the controller when the controller state was updated most recently. Use this form if you need a precise controller
			* pose as input to your application when the user presses or releases a button. */
			virtual bool GetControllerStateWithPose(TrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, TrackedDevicePose_t *pTrackedDevicePose)
			{
				_TraceFormat("%s:%d (%d,%d)\n", __X_FUNCTION__, __LINE__,
					eOrigin, unControllerDeviceIndex);

				if (pTrackedDevicePose)
				{
					if (k_unTrackedDeviceIndex_Hmd == unControllerDeviceIndex)
					{
						pTrackedDevicePose->bDeviceIsConnected = true;
						pTrackedDevicePose->bPoseIsValid = true;
						pTrackedDevicePose->eTrackingResult = TrackingResult_Running_OK;

						{
							HmdMatrix34_t &m = pTrackedDevicePose->mDeviceToAbsoluteTracking;
							memset(m.m, 0.0f, sizeof(m.m[0][0]) * 3 * 4);
							m.m[0][0] = 1.0f;
							m.m[1][1] = 1.0f;
							m.m[2][2] = 1.0f;
						}
						{
							HmdVector3_t &v = pTrackedDevicePose->vAngularVelocity;
							v.v[0] = 0.0f; v.v[1] = 0.0f; v.v[2] = 0.0f;
						}
						{
							HmdVector3_t &v = pTrackedDevicePose->vVelocity;
							v.v[0] = 0.0f; v.v[1] = 0.0f; v.v[2] = 0.0f;
						}

					}
					else
					{
						pTrackedDevicePose->bDeviceIsConnected = false;
						pTrackedDevicePose->bPoseIsValid = false;
						pTrackedDevicePose->eTrackingResult = TrackingResult_Uninitialized;
					}
				}

				return true;
			}

			/** Trigger a single haptic pulse on a controller. After this call the application may not trigger another haptic pulse on this controller
			* and axis combination for 5ms. */
			virtual void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec)
			{
				CHECKPOINT();
			}

			/** returns the name of an EVRButtonId enum value */
			virtual const char *GetButtonIdNameFromEnum(EVRButtonId eButtonId)
			{
				_TraceFormat("****(%p) check %s, line: %d (0x%x)\n", this, __X_FUNCTION__, __LINE__, eButtonId);
				return "unknown Button...";
			}

			/** returns the name of an EVRControllerAxisType enum value */
			virtual const char *GetControllerAxisTypeNameFromEnum(EVRControllerAxisType eAxisType)
			{
				_TraceFormat("****(%p) check %s, line: %d (0x%x)\n", this, __X_FUNCTION__, __LINE__, eAxisType);
				return "unknown Axis...";
			}

			/** Tells OpenVR that this process wants exclusive access to controller button states and button events. Other apps will be notified that
			* they have lost input focus with a VREvent_InputFocusCaptured event. Returns false if input focus could not be captured for
			* some reason. */
			virtual bool CaptureInputFocus()
			{
				CHECKPOINT();
				return true;
			}

			/** Tells OpenVR that this process no longer wants exclusive access to button states and button events. Other apps will be notified
			* that input focus has been released with a VREvent_InputFocusReleased event. */
			virtual void ReleaseInputFocus()
			{
				CHECKPOINT();
			}

			/** Returns true if input focus is captured by another process. */
			virtual bool IsInputFocusCapturedByAnotherProcess()
			{
				CHECKPOINT();
				return false;
			}

			// ------------------------------------
			// Debug Methods
			// ------------------------------------

			/** Sends a request to the driver for the specified device and returns the response. The maximum response size is 32k,
			* but this method can be called with a smaller buffer. If the response exceeds the size of the buffer, it is truncated.
			* The size of the response including its terminating null is returned. */
			virtual uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize)
			{
				CHECKPOINT();
				return 0;
			}


			// ------------------------------------
			// Firmware methods
			// ------------------------------------

			/** Performs the actual firmware update if applicable.
			* The following events will be sent, if VRFirmwareError_None was returned: VREvent_FirmwareUpdateStarted, VREvent_FirmwareUpdateFinished
			* Use the properties Prop_Firmware_UpdateAvailable_Bool, Prop_Firmware_ManualUpdate_Bool, and Prop_Firmware_ManualUpdateURL_String
			* to figure our whether a firmware update is available, and to figure out whether its a manual update
			* Prop_Firmware_ManualUpdateURL_String should point to an URL describing the manual update process */
			virtual VRFirmwareError PerformFirmwareUpdate(TrackedDeviceIndex_t unDeviceIndex)
			{
				CHECKPOINT();
				return VRFirmwareError_Success;
			}


			// ------------------------------------
			// Display Mode methods
			// ------------------------------------

			/** Use to determine if the headset display is part of the desktop (i.e. extended) or hidden (i.e. direct mode). */
			virtual bool IsDisplayOnDesktop()
			{
				CHECKPOINT();
				return false;
			}

			/** Set the display visibility (true = extended, false = direct mode).  Return value of true indicates that the change was successful. */
			virtual bool SetDisplayVisibility(bool bIsVisibleOnDesktop)
			{
				CHECKPOINT();
				return true;
			}



			IVRCompositor *m_pVRCompositor;
			IVRChaperone *m_pVRChaperone;
			IVROverlay *m_pVROverlay;
			IVRRenderModels *m_pVRRenderModels;
			IVRControlPanel *m_pVRControlPanel;
			IVRTrackedCamera *m_pVRTrackedCamera;

		}; // VrSystem

		   //*********************************************









		   /** Allows the application to interact with the compositor */
		class VrCompositor : public IVRCompositor
		{
		public:

			VrCompositor()
			{
				CHECKPOINT();
			}

			virtual ~VrCompositor()
			{
				CHECKPOINT();
			}

			/** Returns the last error that occurred in the compositor */
			virtual uint32_t GetLastError(VR_OUT_STRING() char* pchBuffer, uint32_t unBufferSize)
			{
				CHECKPOINT();
				return 0;
			}


			/** Turns vsync on or off on the compositor window */
			virtual void SetVSync(bool bVSync)
			{
				CHECKPOINT();
			}


			/** Returns true if vsync is enabled in the compositor window */
			virtual bool GetVSync()
			{
				CHECKPOINT();
				return true;
			}


			/** Sets gamma for the compositor window */
			virtual void SetGamma(float fGamma)
			{
				CHECKPOINT();
			}


			/** Returns the gamma for the compositor window */
			virtual float GetGamma()
			{
				CHECKPOINT();
				return 1.0f;
			}


			/** Returns pose(s) to use to render scene (and optionally poses predicted two frames out for gameplay). */
			virtual VRCompositorError WaitGetPoses(VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
				VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount)
			{
				CHECKPOINT();
				return VRCompositorError_None;
			}


			/** Updated scene texture to display. If pBounds is NULL the entire texture will be used.
			*
			* OpenGL dirty state:
			*	glBindTexture
			*/
			virtual VRCompositorError Submit(Hmd_Eye eEye, GraphicsAPIConvention eTextureType, void* pTexture, const VRTextureBounds_t* pBounds, VRSubmitFlags_t nSubmitFlags = Submit_Default)
			{
				CHECKPOINT();
				return VRCompositorError_None;
			}

			/** Clears the frame that was sent with the last call to Submit. This will cause the
			* compositor to show the grid until Submit is called again. */
			virtual void ClearLastSubmittedFrame()
			{
				CHECKPOINT();
			}

			/** Returns true if timing data is filled it.  Sets oldest timing info if nFramesAgo is larger than the stored history.
			* Be sure to set timing.size = sizeof(Compositor_FrameTiming) on struct passed in before calling this function. */
			virtual bool GetFrameTiming(Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0)
			{
				CHECKPOINT();
				return true;
			}

			/** Fades the view on the HMD to the specified color. The fade will take fSeconds, and the color values are between
			* 0.0 and 1.0. This color is faded on top of the scene based on the alpha parameter. Removing the fade color instantly
			* would be FadeToColor( 0.0, 0.0, 0.0, 0.0, 0.0 ). */
			virtual void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false)
			{
				CHECKPOINT();
			}

			/** Fading the Grid in or out in fSeconds */
			virtual void FadeGrid(float fSeconds, bool bFadeIn)
			{
				CHECKPOINT();
			}

			/** Override the skybox used in the compositor (e.g. for during level loads when the app can't feed scene images fast enough). */
			virtual void SetSkyboxOverride(GraphicsAPIConvention eTextureType, void *pFront, void *pBack, void *pLeft, void *pRight, void *pTop, void *pBottom)
			{
				CHECKPOINT();
			}

			/** Resets compositor skybox back to defaults. */
			virtual void ClearSkyboxOverride()
			{
				CHECKPOINT();
			}

			/** Brings the compositor window to the front. This is useful for covering any other window that may be on the HMD
			* and is obscuring the compositor window. */
			virtual void CompositorBringToFront()
			{
				CHECKPOINT();
			}

			/** Pushes the compositor window to the back. This is useful for allowing other applications to draw directly to the HMD. */
			virtual void CompositorGoToBack()
			{
				CHECKPOINT();
			}

			/** Tells the compositor process to clean up and exit. You do not need to call this function at shutdown. Under normal
			* circumstances the compositor will manage its own life cycle based on what applications are running. */
			virtual void CompositorQuit()
			{
				CHECKPOINT();
			}

			/** Return whether the compositor is fullscreen */
			virtual bool IsFullscreen()
			{
				CHECKPOINT();
				return true;
			}

			/** Sets tracking space returned by WaitGetPoses */
			virtual void SetTrackingSpace(TrackingUniverseOrigin eOrigin)
			{
				CHECKPOINT();
			}

			/** Gets current tracking space returned by WaitGetPoses */
			virtual TrackingUniverseOrigin GetTrackingSpace()
			{
				CHECKPOINT();
				return TrackingUniverseSeated;
			}

			/** Returns the process ID of the process that is currently rendering the scene */
			virtual uint32_t GetCurrentSceneFocusProcess()
			{
				CHECKPOINT();
				return 0;
			}

			/** Returns true if the current process has the scene focus */
			virtual bool CanRenderScene()
			{
				CHECKPOINT();
				return true;
			}

			/** Creates a window on the primary monitor to display what is being shown in the headset. */
			virtual void ShowMirrorWindow()
			{
				CHECKPOINT();
			}

			/** Closes the mirrow window. */
			virtual void HideMirrorWindow()
			{
				CHECKPOINT();
			}

			/** Writes all images that the compositor knows about (including overlays) to a 'screenshots' folder in the SteamVR runtime root. */
			virtual void CompositorDumpImages()
			{
				CHECKPOINT();
			}

			/** Returns the time in seconds left in the current (as identified by FrameTiming's frameIndex) frame.
			* Due to "running start", this value may roll over to the next frame before ever reaching 0.0. */
			virtual float GetFrameTimeRemaining()
			{
				CHECKPOINT();
				return 0.1f;
			}

			/** Returns the process ID of the process that rendered the last frame (or 0 if the compositor itself rendered the frame.)
			* Returns 0 when fading out from an app and the app's process Id when fading into an app. */
			virtual uint32_t GetLastFrameRenderer()
			{
				CHECKPOINT();
				return 0;
			}


			/** Get the last set of poses returned by WaitGetPoses. */
			virtual VRCompositorError GetLastPoses(VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
				VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount)
			{
				_TraceFormat("*** %s:%d (%d,%d)\n", __X_FUNCTION__, __LINE__, unRenderPoseArrayCount, unGamePoseArrayCount);

				if (pGamePoseArray)
				{
					TrackedDevicePose_t*& p = pGamePoseArray;
					uint32_t c = unGamePoseArrayCount;

					for (int i = 0; i < c; i++)
					{
						p[i].bPoseIsValid = false;
						p[i].bDeviceIsConnected = false;
						p[i].eTrackingResult = TrackingResult_Uninitialized;
					}
				}

				if (pRenderPoseArray)
				{
					TrackedDevicePose_t*& p = pRenderPoseArray;
					uint32_t c = unRenderPoseArrayCount;

					{
						TrackedDevicePose_t& p0 = p[0]; //hmd

						p0.bDeviceIsConnected = true;
						p0.bPoseIsValid = true;
						p0.eTrackingResult = TrackingResult_Running_OK;

						{
							static float fAngle = 0.0f;
							fAngle += 3.141592654f / 60.0f;


							HmdMatrix34_t &m = p0.mDeviceToAbsoluteTracking;
							memset(m.m, 0.0f, sizeof(m.m[0][0]) * 3 * 4);
							m.m[0][0] = 1.0f;
							m.m[1][1] = 1.0f;
							m.m[2][2] = 1.0f;

							m.m[0][0] = cos(fAngle);
							m.m[0][1] = -sin(fAngle);

							m.m[1][0] = sin(fAngle);
							m.m[1][1] = cos(fAngle);
							

							m.m[0][3] = (rand()*2.0f)/ RAND_MAX;
							//m.m[1][3] = 1.0f;
							//m.m[2][3] = 1.0f;
						}
						{
							HmdVector3_t &v = p0.vAngularVelocity;
							v.v[0] = 0.0f; v.v[1] = 0.0f; v.v[2] = 0.0f;
						}
						{
							HmdVector3_t &v = p0.vVelocity;
							v.v[0] = 0.0f; v.v[1] = 0.0f; v.v[2] = 0.0f;
						}

					}


					for (int i = 1; i < c; i++)
					{
						p[i].bPoseIsValid = false;
						p[i].bDeviceIsConnected = false;
						p[i].eTrackingResult = TrackingResult_Uninitialized;
					}
				}




				return VRCompositorError_None;
			}

			/** Call immediately after presenting your app's window (i.e. companion window) to unblock the compositor.
			* This is an optional call, which only needs to be used if you can't instead call WaitGetPoses immediately after Present.
			* For example, if your engine's render and game loop are not on separate threads, or blocking the render thread until 3ms before the next vsync would
			* introduce a deadlock of some sort.  This function tells the compositor that you have finished all rendering after having Submitted buffers for both
			* eyes, and it is free to start its rendering work.  This should only be called from the same thread you are rendering on. */
			virtual void PostPresentHandoff()
			{
				CHECKPOINT();
			}
		};


		//*********************************************************************








		class VrOverlay : public IVROverlay
		{
		public:

			VrOverlay()
			{
				CHECKPOINT();
			}

			virtual ~VrOverlay()
			{
				CHECKPOINT();
			}

			// ---------------------------------------------
			// Overlay management methods
			// ---------------------------------------------

			/** Finds an existing overlay with the specified key. */
			virtual VROverlayError FindOverlay(const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Creates a new named overlay. All overlays start hidden and with default settings. */
			virtual VROverlayError CreateOverlay(const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pOverlayHandle)
			{
				CHECKPOINT();
				*pOverlayHandle = 0;
				return VROverlayError_None;
			}

			/** Destroys the specified overlay. When an application calls VR_Shutdown all overlays created by that app are
			* automatically destroyed. */
			virtual VROverlayError DestroyOverlay(VROverlayHandle_t ulOverlayHandle)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Specify which overlay to use the high quality render path.  This overlay will be composited in during the distortion pass which
			* results in it drawing on top of everything else, but also at a higher quality as it samples the source texture directly rather than
			* rasterizing into each eye's render texture first.  Because if this, only one of these is supported at any given time.  It is most useful
			* for overlays that are expected to take up most of the user's view (e.g. streaming video). */
			virtual VROverlayError SetHighQualityOverlay(VROverlayHandle_t ulOverlayHandle)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Returns the overlay handle of the current overlay being rendered using the single high quality overlay render path.
			* Otherwise it will return k_ulOverlayHandleInvalid. */
			virtual vr::VROverlayHandle_t GetHighQualityOverlay()
			{
				CHECKPOINT();
				return k_ulOverlayHandleInvalid;
			}

			/** Fills the provided buffer with the string key of the overlay. Returns the size of buffer required to store the key, including
			* the terminating null character. k_unVROverlayMaxKeyLength will be enough bytes to fit the string. */
			virtual uint32_t GetOverlayKey(VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, VROverlayError *pError = 0L)
			{
				CHECKPOINT();
				return 0;
			}

			/** Fills the provided buffer with the friendly name of the overlay. Returns the size of buffer required to store the key, including
			* the terminating null character. k_unVROverlayMaxNameLength will be enough bytes to fit the string. */
			virtual uint32_t GetOverlayName(VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, VROverlayError *pError = 0L)
			{
				CHECKPOINT();
				return 0;
			}

			/** Gets the raw image data from an overlay. Overlay image data is always returned as RGBA data, 4 bytes per pixel. If the buffer is not large enough, width and height
			* will be set and VROverlayError_ArrayTooSmall is returned. */
			virtual VROverlayError GetOverlayImageData(VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** returns a string that corresponds with the specified overlay error. The string will be the name
			* of the error enum value for all valid error codes */
			virtual const char *GetOverlayErrorNameFromEnum(VROverlayError error)
			{
				_TraceFormat("*** %s:%d (%d)\n", __X_FUNCTION__, __LINE__, error);
				return "GetOverlayErrorNameFromEnum";
			}


			// ---------------------------------------------
			// Overlay rendering methods
			// ---------------------------------------------

			/** Specify flag setting for a given overlay */
			virtual VROverlayError SetOverlayFlag(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets flag setting for a given overlay */
			virtual VROverlayError GetOverlayFlag(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets the color tint of the overlay quad. Use 0.0 to 1.0 per channel. */
			virtual VROverlayError SetOverlayColor(VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Gets the color tint of the overlay quad. */
			virtual VROverlayError GetOverlayColor(VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets the alpha of the overlay quad. Use 1.0 for 100 percent opacity to 0.0 for 0 percent opacity. */
			virtual VROverlayError SetOverlayAlpha(VROverlayHandle_t ulOverlayHandle, float fAlpha)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Gets the alpha of the overlay quad. By default overlays are rendering at 100 percent alpha (1.0). */
			virtual VROverlayError GetOverlayAlpha(VROverlayHandle_t ulOverlayHandle, float *pfAlpha)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets the gamma of the overlay quad. Use 2.2 when providing a texture in linear color space. */
			virtual VROverlayError SetOverlayGamma(VROverlayHandle_t ulOverlayHandle, float fGamma)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Gets the gamma of the overlay quad.  Be default overlays are rendered with 1.0 gamma. */
			virtual VROverlayError GetOverlayGamma(VROverlayHandle_t ulOverlayHandle, float *pfGamma)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets the width of the overlay quad in meters. By default overlays are rendered on a quad that is 1 meter across */
			virtual VROverlayError SetOverlayWidthInMeters(VROverlayHandle_t ulOverlayHandle, float fWidthInMeters)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Returns the width of the overlay quad in meters. By default overlays are rendered on a quad that is 1 meter across */
			virtual VROverlayError GetOverlayWidthInMeters(VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** For high-quality curved overlays only, sets the distance range in meters from the overlay used to automatically curve
			* the surface around the viewer.  Min is distance is when the surface will be most curved.  Max is when least curved. */
			virtual VROverlayError SetOverlayAutoCurveDistanceRangeInMeters(VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** For high-quality curved overlays only, gets the distance range in meters from the overlay used to automatically curve
			* the surface around the viewer.  Min is distance is when the surface will be most curved.  Max is when least curved. */
			virtual VROverlayError GetOverlayAutoCurveDistanceRangeInMeters(VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets the part of the texture to use for the overlay. UV Min is the upper left corner and UV Max is the lower right corner. */
			virtual VROverlayError SetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Gets the part of the texture to use for the overlay. UV Min is the upper left corner and UV Max is the lower right corner. */
			virtual VROverlayError GetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Returns the transform type of this overlay. */
			virtual VROverlayError GetOverlayTransformType(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets the transform to absolute tracking origin. */
			virtual VROverlayError SetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, TrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Gets the transform if it is absolute. Returns an error if the transform is some other type. */
			virtual VROverlayError GetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, TrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets the transform to relative to the transform of the specified tracked device. */
			virtual VROverlayError SetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Gets the transform if it is relative to a tracked device. Returns an error if the transform is some other type. */
			virtual VROverlayError GetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Shows the VR overlay.  For dashboard overlays, only the Dashboard Manager is allowed to call this. */
			virtual VROverlayError ShowOverlay(VROverlayHandle_t ulOverlayHandle)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Hides the VR overlay.  For dashboard overlays, only the Dashboard Manager is allowed to call this. */
			virtual VROverlayError HideOverlay(VROverlayHandle_t ulOverlayHandle)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Returns true if the overlay is visible. */
			virtual bool IsOverlayVisible(VROverlayHandle_t ulOverlayHandle)
			{
				CHECKPOINT();
			}


			// ---------------------------------------------
			// Overlay input methods
			// ---------------------------------------------

			/** Returns true and fills the event with the next event on the overlay's event queue, if there is one.
			* If there are no events this method returns false */
			virtual bool PollNextOverlayEvent(VROverlayHandle_t ulOverlayHandle, VREvent_t *pEvent)
			{
				CHECKPOINT();
				return false;
			}

			/** Returns the current input settings for the specified overlay. */
			virtual VROverlayError GetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets the input settings for the specified overlay. */
			virtual VROverlayError SetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Gets the mouse scaling factor that is used for mouse events. The actual texture may be a different size, but this is
			* typically the size of the underlying UI in pixels. */
			virtual VROverlayError GetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets the mouse scaling factor that is used for mouse events. The actual texture may be a different size, but this is
			* typically the size of the underlying UI in pixels. */
			virtual VROverlayError SetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Computes the overlay-space pixel coordinates of where the ray intersects the overlay with the
			* specified settings. Returns false if there is no intersection. */
			virtual bool ComputeOverlayIntersection(VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults)
			{
				CHECKPOINT();
			}

			/** Processes mouse input from the specified controller as though it were a mouse pointed at a compositor overlay with the
			* specified settings. The controller is treated like a laser pointer on the -z axis. The point where the laser pointer would
			* intersect with the overlay is the mouse position, the trigger is left mouse, and the track pad is right mouse.
			*
			* Return true if the controller is pointed at the overlay and an event was generated. */
			virtual bool HandleControllerOverlayInteractionAsMouse(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex)
			{
				CHECKPOINT();
			}

			/** Returns true if the specified overlay is the hover target. An overlay is the hover target when it is the last overlay "moused over"
			* by the virtual mouse pointer */
			virtual bool IsHoverTargetOverlay(VROverlayHandle_t ulOverlayHandle)
			{
				CHECKPOINT();
			}

			/** Returns the current Gamepad focus overlay */
			virtual vr::VROverlayHandle_t GetGamepadFocusOverlay()
			{
				CHECKPOINT();
			}

			/** Sets the current Gamepad focus overlay */
			virtual VROverlayError SetGamepadFocusOverlay(VROverlayHandle_t ulNewFocusOverlay)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Sets an overlay's neighbor. This will also set the neighbor of the "to" overlay
			* to point back to the "from" overlay. If an overlay's neighbor is set to invalid both
			* ends will be cleared */
			virtual VROverlayError SetOverlayNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Changes the Gamepad focus from one overlay to one of its neighbors. Returns VROverlayError_NoNeighbor if there is no
			* neighbor in that direction */
			virtual VROverlayError MoveGamepadFocusToNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

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
			virtual VROverlayError SetOverlayTexture(VROverlayHandle_t ulOverlayHandle, GraphicsAPIConvention eTextureType, void* pTexture)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Use this to tell the overlay system to release the texture set for this overlay. */
			virtual VROverlayError ClearOverlayTexture(VROverlayHandle_t ulOverlayHandle)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Separate interface for providing the data as a stream of bytes, but there is an upper bound on data
			* that can be sent. This function can only be called by the overlay's renderer process. */
			virtual VROverlayError SetOverlayRaw(VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Separate interface for providing the image through a filename: can be png or jpg, and should not be bigger than 1920x1080.
			* This function can only be called by the overlay's renderer process */
			virtual VROverlayError SetOverlayFromFile(VROverlayHandle_t ulOverlayHandle, const char *pchFilePath)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			// ----------------------------------------------
			// Dashboard Overlay Methods
			// ----------------------------------------------

			/** Creates a dashboard overlay and returns its handle */
			virtual VROverlayError CreateDashboardOverlay(const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Returns true if the dashboard is visible */
			virtual bool IsDashboardVisible()
			{
				CHECKPOINT();
			}

			/** returns true if the dashboard is visible and the specified overlay is the active system Overlay */
			virtual bool IsActiveDashboardOverlay(VROverlayHandle_t ulOverlayHandle)
			{
				CHECKPOINT();
			}

			/** Sets the dashboard overlay to only appear when the specified process ID has scene focus */
			virtual VROverlayError SetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Gets the process ID that this dashboard overlay requires to have scene focus */
			virtual VROverlayError GetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Shows the dashboard. */
			virtual void ShowDashboard(const char *pchOverlayToShow)
			{
				CHECKPOINT();
			}

			// ---------------------------------------------
			// Keyboard methods
			// ---------------------------------------------

			/** Show the virtual keyboard to accept input **/
			virtual VROverlayError ShowKeyboard(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			virtual VROverlayError ShowKeyboardForOverlay(VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue)
			{
				CHECKPOINT();
				return VROverlayError_None;
			}

			/** Get the text that was entered into the text input **/
			virtual uint32_t GetKeyboardText(VR_OUT_STRING() char *pchText, uint32_t cchText)
			{
				CHECKPOINT();
			}

			/** Hide the virtual keyboard **/
			virtual void HideKeyboard()
			{
				CHECKPOINT();
			}

		};


	}// namespace mobile




























/** called when lib is loaded */
	VR_INTERFACE jint JNI_OnLoad(JavaVM* aVm, void* aReserved)
	{
		LOGI("JNI_OnLoad() %s %s", __DATE__, __TIME__);

		//util::JVMUtil::SetJVM(aVm);

		//getWindow().takeSurface(null);

		return JNI_VERSION_1_6;
	}


	/** Returns the string version of an HMD error. This function may be called outside of VR_Init()/VR_Shutdown(). */
	VR_INTERFACE const char *VR_CALLTYPE VR_GetStringForHmdError(vr::HmdError error)
	{
		_TraceFormat("*** %s:%d (0x%x)\n", __X_FUNCTION__, __LINE__, error);
		return "check log by your self...";
	}



	using namespace mobile;

	static VrSystem *s_pVRSystem = 0;

	VR_INTERFACE IVRSystem *VR_CALLTYPE VR_Init(HmdError *peError, EVRApplicationType eApplicationType)
	{
		CHECKPOINT_C(s_pVRSystem);

		VR_Shutdown();
		s_pVRSystem = new VrSystem();
		*peError = HmdError_None;
		return s_pVRSystem;
	}

	/** unloads vrclient.dll. Any interface pointers from the interface are
	* invalid after this point */
	VR_INTERFACE void VR_CALLTYPE VR_Shutdown()
	{
		CHECKPOINT_C(s_pVRSystem);
		SAFE_DELETE_PTR(s_pVRSystem);
	}



	VR_INTERFACE void *VR_CALLTYPE VR_GetGenericInterface(const char *pchInterfaceVersion, vr::HmdError *peError)
	{
		_TraceFormat("(%p) %s:%d (%s)\n", s_pVRSystem, __X_FUNCTION__, __LINE__, pchInterfaceVersion);

		*peError = HmdError_Unknown;

		if (strstr(pchInterfaceVersion, "IVRSystem"))
		{
			IVRSystem *p = VRSystem();
			if (p) *peError = HmdError_None;
			return p;
		}
		else if (strstr(pchInterfaceVersion, "IVRCompositor"))
		{
			IVRCompositor *p = VRCompositor();
			if (p) *peError = HmdError_None;
			return p;
		}
		else if (strstr(pchInterfaceVersion, "IVROverlay"))
		{
			IVROverlay *p = VROverlay();
			if (p) *peError = HmdError_None;
			return p;
		}


		*peError = HmdError_Unknown;
		return NULL;
	}


	static bool EnvCheckFail()
	{
		if (!s_pVRSystem)
		{
			_TraceFormat("!!!!! need to call VR_Init() first!");
			return true;
		}
		else
			return false;
	}


	/** Returns the current IVRSystem pointer or NULL if VR_Init has not been called successfully */
	VR_INTERFACE vr::IVRSystem *VR_CALLTYPE VRSystem()
	{
		CHECKPOINT_C(s_pVRSystem);
		if (EnvCheckFail()) return NULL;
		return s_pVRSystem;
	}



	/** Returns the current IVRChaperone pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRChaperone *VR_CALLTYPE VRChaperone()
	{
		CHECKPOINT_C(s_pVRSystem);
		if (EnvCheckFail()) return NULL;
		return NULL;
	}

	/** Returns the current IVRCompositor pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRCompositor *VR_CALLTYPE VRCompositor()
	{
		CHECKPOINT_C(s_pVRSystem);
		if (EnvCheckFail()) return NULL;
		IVRCompositor*& p = s_pVRSystem->m_pVRCompositor;
		if (!p) p = new VrCompositor();
		return p;

	}

	/** Returns the current IVROverlay pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVROverlay *VR_CALLTYPE VROverlay()
	{
		CHECKPOINT_C(s_pVRSystem);
		if (EnvCheckFail()) return NULL;
		IVROverlay*& p = s_pVRSystem->m_pVROverlay;
		if (!p) p = new VrOverlay();
		return p;
	}

	/** Returns the current IVRRenderModels pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRRenderModels *VR_CALLTYPE VRRenderModels()
	{
		CHECKPOINT_C(s_pVRSystem);
		if (EnvCheckFail()) return NULL;
		return NULL;
	}

	/** Returns the current IVRControlPanel pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRControlPanel *VR_CALLTYPE VRControlPanel()
	{
		CHECKPOINT_C(s_pVRSystem);
		if (EnvCheckFail()) return NULL;
		return NULL;
	}

	/** Returns the current IVRTrackedCamera pointer or NULL the interface could not be found. */
	VR_INTERFACE vr::IVRTrackedCamera *VR_CALLTYPE VRTrackedCamera()
	{
		CHECKPOINT_C(s_pVRSystem);
		if (EnvCheckFail()) return NULL;
		return NULL;
	}




} // namespace vr
