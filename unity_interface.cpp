#include "Precomp.h"



//opengl
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


//*************************************************************
// sop
//
// 1. copy class VRNativeEntrypoints { ...} from openvr_api.cs
// e.g
// [DllImportAttribute("openvr_api", EntryPoint = "VR_IVRSystem_GetWindowBounds")]
// internal static extern void VR_IVRSystem_GetWindowBounds(IntPtr instancePtr, ref int pnX, ref int pnY, ref uint pnWidth, ref uint pnHeight);
// ...

// 2. use PSPad	
// replace by regular expressions
// "\[Dll.*\Z" ==> ""
// "ref\s(\w+)\s" ==> "$1* "
// "System.Text.StringBuilder" ==> "/* System.Text.StringBuilder */ void*"

// simple replace
// "internal static extern" ==> "VR_INTERFACE"


using namespace vr;

VR_INTERFACE void VR_IVRSystem_GetWindowBounds(IntPtr instancePtr, int* pnX, int* pnY, uint* pnWidth, uint* pnHeight) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSystem_GetRecommendedRenderTargetSize(IntPtr instancePtr, uint* pnWidth, uint* pnHeight)
{ 
	IVRSystem* p = static_cast<IVRSystem*>(instancePtr);
	return p->GetRecommendedRenderTargetSize(pnWidth, pnHeight);
}

VR_INTERFACE void VR_IVRSystem_GetEyeOutputViewport(IntPtr instancePtr, Hmd_Eye eEye, uint* pnX, uint* pnY, uint* pnWidth, uint* pnHeight) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE HmdMatrix44_t VR_IVRSystem_GetProjectionMatrix(IntPtr instancePtr, Hmd_Eye eEye, float fNearZ, float fFarZ, GraphicsAPIConvention eProjType) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSystem_GetProjectionRaw(IntPtr instancePtr, Hmd_Eye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom)
{
	IVRSystem* p = static_cast<IVRSystem*>(instancePtr);
	return p->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom);
}

VR_INTERFACE DistortionCoordinates_t VR_IVRSystem_ComputeDistortion(IntPtr instancePtr, Hmd_Eye eEye, float fU, float fV) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE HmdMatrix34_t VR_IVRSystem_GetEyeToHeadTransform(IntPtr instancePtr, Hmd_Eye eEye)
{
	IVRSystem* p = static_cast<IVRSystem*>(instancePtr);
	return p->GetEyeToHeadTransform(eEye);
}

VR_INTERFACE bool VR_IVRSystem_GetTimeSinceLastVsync(IntPtr instancePtr, float* pfSecondsSinceLastVsync, ulong* pulFrameCounter) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE int VR_IVRSystem_GetD3D9AdapterIndex(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSystem_GetDXGIOutputInfo(IntPtr instancePtr, int* pnAdapterIndex, int* pnAdapterOutputIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRSystem_AttachToWindow(IntPtr instancePtr, IntPtr hWnd) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSystem_GetDeviceToAbsoluteTrackingPose(IntPtr instancePtr, TrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, /* [In, Out] */ TrackedDevicePose_t* pTrackedDevicePoseArray, uint unTrackedDevicePoseArrayCount) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSystem_ResetSeatedZeroPose(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE HmdMatrix34_t VR_IVRSystem_GetSeatedZeroPoseToStandingAbsoluteTrackingPose(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE HmdMatrix34_t VR_IVRSystem_GetRawZeroPoseToStandingAbsoluteTrackingPose(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRSystem_GetSortedTrackedDeviceIndicesOfClass(IntPtr instancePtr, TrackedDeviceClass eTrackedDeviceClass, /* [In, Out] */ uint* punTrackedDeviceIndexArray, uint unTrackedDeviceIndexArrayCount, uint unRelativeToTrackedDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRSystem_GetTrackedDeviceActivityLevel(IntPtr instancePtr, uint unDeviceId) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSystem_ApplyTransform(IntPtr instancePtr, TrackedDevicePose_t* pOutputPose, IntPtr trackedDevicePose, IntPtr transform) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE TrackedDeviceClass VR_IVRSystem_GetTrackedDeviceClass(IntPtr instancePtr, uint unDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRSystem_IsTrackedDeviceConnected(IntPtr instancePtr, uint unDeviceIndex)
{
	IVRSystem* p = static_cast<IVRSystem*>(instancePtr);
	return p->IsTrackedDeviceConnected(unDeviceIndex);
}

VR_INTERFACE bool VR_IVRSystem_GetBoolTrackedDeviceProperty(IntPtr instancePtr, uint unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError* pError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE float VR_IVRSystem_GetFloatTrackedDeviceProperty(IntPtr instancePtr, uint unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError* pError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE int VR_IVRSystem_GetInt32TrackedDeviceProperty(IntPtr instancePtr, uint unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError* pError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE ulong VR_IVRSystem_GetUint64TrackedDeviceProperty(IntPtr instancePtr, uint unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError* pError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE HmdMatrix34_t VR_IVRSystem_GetMatrix34TrackedDeviceProperty(IntPtr instancePtr, uint unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError* pError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRSystem_GetStringTrackedDeviceProperty(IntPtr instancePtr, uint unDeviceIndex, TrackedDeviceProperty prop, /* System.Text.StringBuilder */ char* pchValue, uint unBufferSize, TrackedPropertyError* pError)
{	
	IVRSystem* p = static_cast<IVRSystem*>(instancePtr);
	return p->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError);
}

VR_INTERFACE IntPtr VR_IVRSystem_GetPropErrorNameFromEnum(IntPtr instancePtr, TrackedPropertyError error) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRSystem_PollNextEvent(IntPtr instancePtr, VREvent_t* pEvent) 
{
	IVRSystem* p = static_cast<IVRSystem*>(instancePtr);
	return p->PollNextEvent(pEvent);
}

VR_INTERFACE bool VR_IVRSystem_PollNextEventWithPose(IntPtr instancePtr, TrackingUniverseOrigin eOrigin, VREvent_t* pEvent, TrackedDevicePose_t* pTrackedDevicePose)
{
	IVRSystem* p = static_cast<IVRSystem*>(instancePtr);	
	return p->PollNextEventWithPose(eOrigin, pEvent, pTrackedDevicePose);
}

VR_INTERFACE IntPtr VR_IVRSystem_GetEventTypeNameFromEnum(IntPtr instancePtr, uint eType) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE HiddenAreaMesh_t VR_IVRSystem_GetHiddenAreaMesh(IntPtr instancePtr, Hmd_Eye eEye)
{
	IVRSystem* p = static_cast<IVRSystem*>(instancePtr);
	return p->GetHiddenAreaMesh(eEye);
}

VR_INTERFACE bool VR_IVRSystem_GetControllerState(IntPtr instancePtr, uint unControllerDeviceIndex, VRControllerState_t* pControllerState) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRSystem_GetControllerStateWithPose(IntPtr instancePtr, TrackingUniverseOrigin eOrigin, uint unControllerDeviceIndex, VRControllerState_t* pControllerState, TrackedDevicePose_t* pTrackedDevicePose)
{
	IVRSystem* p = static_cast<IVRSystem*>(instancePtr);	
	return p->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, pTrackedDevicePose);
}

VR_INTERFACE void VR_IVRSystem_TriggerHapticPulse(IntPtr instancePtr, uint unControllerDeviceIndex, uint unAxisId, char usDurationMicroSec) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE IntPtr VR_IVRSystem_GetButtonIdNameFromEnum(IntPtr instancePtr, uint eButtonId) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE IntPtr VR_IVRSystem_GetControllerAxisTypeNameFromEnum(IntPtr instancePtr, uint eAxisType) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRSystem_CaptureInputFocus(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSystem_ReleaseInputFocus(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRSystem_IsInputFocusCapturedByAnotherProcess(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRSystem_DriverDebugRequest(IntPtr instancePtr, uint unDeviceIndex, string pchRequest, string pchResponseBuffer, uint unResponseBufferSize) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VRFirmwareError VR_IVRSystem_PerformFirmwareUpdate(IntPtr instancePtr, uint unDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRSystem_IsDisplayOnDesktop(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRSystem_SetDisplayVisibility(IntPtr instancePtr, bool bIsVisibleOnDesktop) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_AddApplicationManifest(IntPtr instancePtr, string pchApplicationManifestFullPath, bool bTemporary) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_RemoveApplicationManifest(IntPtr instancePtr, string pchApplicationManifestFullPath) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRApplications_IsApplicationInstalled(IntPtr instancePtr, string pchAppKey) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_GetApplicationCount(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_GetApplicationKeyByIndex(IntPtr instancePtr, uint unApplicationIndex, string pchAppKeyBuffer, uint unAppKeyBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_GetApplicationKeyByProcessId(IntPtr instancePtr, uint unProcessId, string pchAppKeyBuffer, uint unAppKeyBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_LaunchApplication(IntPtr instancePtr, string pchAppKey) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_LaunchDashboardOverlay(IntPtr instancePtr, string pchAppKey) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_IdentifyApplication(IntPtr instancePtr, uint unProcessId, string pchAppKey) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_GetApplicationProcessId(IntPtr instancePtr, string pchAppKey) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE IntPtr VR_IVRApplications_GetApplicationsErrorNameFromEnum(IntPtr instancePtr, uint error) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_GetApplicationPropertyString(IntPtr instancePtr, string pchAppKey, uint eProperty, string pchPropertyValueBuffer, uint unPropertyValueBufferLen, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRApplications_GetApplicationPropertyBool(IntPtr instancePtr, string pchAppKey, uint eProperty, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_GetHomeApplication(IntPtr instancePtr, string pchAppKeyBuffer, uint unAppKeyBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_SetHomeApplication(IntPtr instancePtr, string pchAppKey) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_SetApplicationAutoLaunch(IntPtr instancePtr, string pchAppKey, bool bAutoLaunch) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRApplications_GetApplicationAutoLaunch(IntPtr instancePtr, string pchAppKey) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_GetStartingApplication(IntPtr instancePtr, string pchAppKeyBuffer, uint unAppKeyBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_GetTransitionState(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRApplications_PerformApplicationPrelaunchCheck(IntPtr instancePtr, string pchAppKey) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE IntPtr VR_IVRApplications_GetApplicationsTransitionStateNameFromEnum(IntPtr instancePtr, uint state) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE ChaperoneCalibrationState VR_IVRChaperone_GetCalibrationState(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperone_GetPlayAreaSize(IntPtr instancePtr, float* pSizeX, float* pSizeZ) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperone_GetPlayAreaRect(IntPtr instancePtr, HmdQuad_t* rect) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperone_ReloadInfo(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperone_SetSceneColor(IntPtr instancePtr, HmdColor_t color) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperone_GetBoundsColor(IntPtr instancePtr, HmdColor_t* pOutputColorArray, int nNumOutputColors) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperone_AreBoundsVisible(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperone_ForceBoundsVisible(IntPtr instancePtr, bool bForce) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRCompositor_GetLastError(IntPtr instancePtr, /* System.Text.StringBuilder */ char* pchBuffer, uint unBufferSize)
{
	IVRCompositor* p = static_cast<IVRCompositor*>(instancePtr);
	return p->GetLastError(pchBuffer, unBufferSize);
}

VR_INTERFACE void VR_IVRCompositor_SetVSync(IntPtr instancePtr, bool bVSync) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRCompositor_GetVSync(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_SetGamma(IntPtr instancePtr, float fGamma) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE float VR_IVRCompositor_GetGamma(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VRCompositorError VR_IVRCompositor_WaitGetPoses(IntPtr instancePtr, /* [In, Out] */ TrackedDevicePose_t* pRenderPoseArray, uint unRenderPoseArrayCount, /* [In, Out] */ TrackedDevicePose_t* pGamePoseArray, uint unGamePoseArrayCount) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VRCompositorError VR_IVRCompositor_Submit(IntPtr instancePtr, Hmd_Eye eEye, GraphicsAPIConvention eTextureType, IntPtr pTexture, VRTextureBounds_t* pBounds, VRSubmitFlags_t nSubmitFlags) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_ClearLastSubmittedFrame(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRCompositor_GetFrameTiming(IntPtr instancePtr, Compositor_FrameTiming* pTiming, uint unFramesAgo) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_FadeToColor(IntPtr instancePtr, float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_FadeGrid(IntPtr instancePtr, float fSeconds, bool bFadeIn) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_SetSkyboxOverride(IntPtr instancePtr, GraphicsAPIConvention eTextureType, IntPtr pFront, IntPtr pBack, IntPtr pLeft, IntPtr pRight, IntPtr pTop, IntPtr pBottom) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_ClearSkyboxOverride(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_CompositorBringToFront(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_CompositorGoToBack(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_CompositorQuit(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRCompositor_IsFullscreen(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_SetTrackingSpace(IntPtr instancePtr, TrackingUniverseOrigin eOrigin) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE TrackingUniverseOrigin VR_IVRCompositor_GetTrackingSpace(IntPtr instancePtr) 
{
	IVRCompositor* p = static_cast<IVRCompositor*>(instancePtr);
	return p->GetTrackingSpace();
}

VR_INTERFACE uint VR_IVRCompositor_GetCurrentSceneFocusProcess(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRCompositor_CanRenderScene(IntPtr instancePtr)
{
	IVRCompositor* p = static_cast<IVRCompositor*>(instancePtr);
	return p->CanRenderScene();
}

VR_INTERFACE void VR_IVRCompositor_ShowMirrorWindow(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_HideMirrorWindow(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRCompositor_CompositorDumpImages(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE float VR_IVRCompositor_GetFrameTimeRemaining(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRCompositor_GetLastFrameRenderer(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VRCompositorError VR_IVRCompositor_GetLastPoses(IntPtr instancePtr, /* [In, Out] */ TrackedDevicePose_t* pRenderPoseArray, uint unRenderPoseArrayCount, /* [In, Out] */ TrackedDevicePose_t* pGamePoseArray, uint unGamePoseArrayCount)
{
	IVRCompositor* p = static_cast<IVRCompositor*>(instancePtr);
	return p->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
}

VR_INTERFACE void VR_IVRCompositor_PostPresentHandoff(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_FindOverlay(IntPtr instancePtr, string pchOverlayKey, ulong* pOverlayHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_CreateOverlay(IntPtr instancePtr, string pchOverlayKey, string pchOverlayFriendlyName, ulong* pOverlayHandle)
{
	IVROverlay* p = static_cast<IVROverlay*>(instancePtr);
	return p->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, (VROverlayHandle_t*)pOverlayHandle);
}

VR_INTERFACE VROverlayError VR_IVROverlay_DestroyOverlay(IntPtr instancePtr, ulong ulOverlayHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetHighQualityOverlay(IntPtr instancePtr, ulong ulOverlayHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE ulong VR_IVROverlay_GetHighQualityOverlay(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVROverlay_GetOverlayKey(IntPtr instancePtr, ulong ulOverlayHandle, /* System.Text.StringBuilder */ void* pchValue, uint unBufferSize, VROverlayError* pError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVROverlay_GetOverlayName(IntPtr instancePtr, ulong ulOverlayHandle, /* System.Text.StringBuilder */ void* pchValue, uint unBufferSize, VROverlayError* pError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayImageData(IntPtr instancePtr, ulong ulOverlayHandle, IntPtr pvBuffer, uint unBufferSize, uint* punWidth, uint* punHeight) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE IntPtr VR_IVROverlay_GetOverlayErrorNameFromEnum(IntPtr instancePtr, VROverlayError error)
{	
	IVROverlay* p = static_cast<IVROverlay*>(instancePtr);
	return (IntPtr)p->GetOverlayErrorNameFromEnum(error);
}

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayFlag(IntPtr instancePtr, ulong ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayFlag(IntPtr instancePtr, ulong ulOverlayHandle, VROverlayFlags eOverlayFlag, bool* pbEnabled) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayColor(IntPtr instancePtr, ulong ulOverlayHandle, float fRed, float fGreen, float fBlue) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayColor(IntPtr instancePtr, ulong ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayAlpha(IntPtr instancePtr, ulong ulOverlayHandle, float fAlpha) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayAlpha(IntPtr instancePtr, ulong ulOverlayHandle, float* pfAlpha) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayGamma(IntPtr instancePtr, ulong ulOverlayHandle, float fGamma) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayGamma(IntPtr instancePtr, ulong ulOverlayHandle, float* pfGamma) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayWidthInMeters(IntPtr instancePtr, ulong ulOverlayHandle, float fWidthInMeters) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayWidthInMeters(IntPtr instancePtr, ulong ulOverlayHandle, float* pfWidthInMeters) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayAutoCurveDistanceRangeInMeters(IntPtr instancePtr, ulong ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayAutoCurveDistanceRangeInMeters(IntPtr instancePtr, ulong ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayTextureBounds(IntPtr instancePtr, ulong ulOverlayHandle, VRTextureBounds_t* pOverlayTextureBounds) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayTextureBounds(IntPtr instancePtr, ulong ulOverlayHandle, VRTextureBounds_t* pOverlayTextureBounds) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayTransformType(IntPtr instancePtr, ulong ulOverlayHandle, VROverlayTransformType* peTransformType) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayTransformAbsolute(IntPtr instancePtr, ulong ulOverlayHandle, TrackingUniverseOrigin eTrackingOrigin, HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayTransformAbsolute(IntPtr instancePtr, ulong ulOverlayHandle, TrackingUniverseOrigin* peTrackingOrigin, HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayTransformTrackedDeviceRelative(IntPtr instancePtr, ulong ulOverlayHandle, uint unTrackedDevice, HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayTransformTrackedDeviceRelative(IntPtr instancePtr, ulong ulOverlayHandle, uint* punTrackedDevice, HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_ShowOverlay(IntPtr instancePtr, ulong ulOverlayHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_HideOverlay(IntPtr instancePtr, ulong ulOverlayHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVROverlay_IsOverlayVisible(IntPtr instancePtr, ulong ulOverlayHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVROverlay_PollNextOverlayEvent(IntPtr instancePtr, ulong ulOverlayHandle, VREvent_t* pEvent) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayInputMethod(IntPtr instancePtr, ulong ulOverlayHandle, VROverlayInputMethod* peInputMethod) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayInputMethod(IntPtr instancePtr, ulong ulOverlayHandle, VROverlayInputMethod eInputMethod) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetOverlayMouseScale(IntPtr instancePtr, ulong ulOverlayHandle, HmdVector2_t* pvecMouseScale) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayMouseScale(IntPtr instancePtr, ulong ulOverlayHandle, HmdVector2_t* pvecMouseScale) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVROverlay_ComputeOverlayIntersection(IntPtr instancePtr, ulong ulOverlayHandle, VROverlayIntersectionParams_t* pParams, VROverlayIntersectionResults_t* pResults) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVROverlay_HandleControllerOverlayInteractionAsMouse(IntPtr instancePtr, ulong ulOverlayHandle, uint unControllerDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVROverlay_IsHoverTargetOverlay(IntPtr instancePtr, ulong ulOverlayHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE ulong VR_IVROverlay_GetGamepadFocusOverlay(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetGamepadFocusOverlay(IntPtr instancePtr, ulong ulNewFocusOverlay) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayNeighbor(IntPtr instancePtr, uint eDirection, ulong ulFrom, ulong ulTo) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_MoveGamepadFocusToNeighbor(IntPtr instancePtr, uint eDirection, ulong ulFrom) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayTexture(IntPtr instancePtr, ulong ulOverlayHandle, GraphicsAPIConvention eTextureType, IntPtr pTexture) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_ClearOverlayTexture(IntPtr instancePtr, ulong ulOverlayHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayRaw(IntPtr instancePtr, ulong ulOverlayHandle, IntPtr pvBuffer, uint unWidth, uint unHeight, uint unDepth) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetOverlayFromFile(IntPtr instancePtr, ulong ulOverlayHandle, string pchFilePath) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_CreateDashboardOverlay(IntPtr instancePtr, string pchOverlayKey, string pchOverlayFriendlyName, ulong* pMainHandle, ulong* pThumbnailHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVROverlay_IsDashboardVisible(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVROverlay_IsActiveDashboardOverlay(IntPtr instancePtr, ulong ulOverlayHandle) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_SetDashboardOverlaySceneProcess(IntPtr instancePtr, ulong ulOverlayHandle, uint unProcessId) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_GetDashboardOverlaySceneProcess(IntPtr instancePtr, ulong ulOverlayHandle, uint* punProcessId) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVROverlay_ShowDashboard(IntPtr instancePtr, string pchOverlayToShow) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_ShowKeyboard(IntPtr instancePtr, int eInputMode, int eLineInputMode, string pchDescription, uint unCharMax, string pchExistingText, bool bUseMinimalMode, ulong uUserValue) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE VROverlayError VR_IVROverlay_ShowKeyboardForOverlay(IntPtr instancePtr, ulong ulOverlayHandle, int eInputMode, int eLineInputMode, string pchDescription, uint unCharMax, string pchExistingText, bool bUseMinimalMode, ulong uUserValue) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVROverlay_GetKeyboardText(IntPtr instancePtr, /* System.Text.StringBuilder */ void* pchText, uint cchText) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVROverlay_HideKeyboard(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRRenderModels_LoadRenderModel(IntPtr instancePtr, string pchRenderModelName, RenderModel_t* pRenderModel) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRRenderModels_FreeRenderModel(IntPtr instancePtr, RenderModel_t* pRenderModel) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRRenderModels_GetRenderModelName(IntPtr instancePtr, uint unRenderModelIndex, /* System.Text.StringBuilder */ void* pchRenderModelName, uint unRenderModelNameLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRRenderModels_GetRenderModelCount(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRRenderModels_GetComponentCount(IntPtr instancePtr, string pchRenderModelName) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRRenderModels_GetComponentName(IntPtr instancePtr, string pchRenderModelName, uint unComponentIndex, /* System.Text.StringBuilder */ void* pchComponentName, uint unComponentNameLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE ulong VR_IVRRenderModels_GetComponentButtonMask(IntPtr instancePtr, string pchRenderModelName, string pchComponentName) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRRenderModels_GetComponentRenderModelName(IntPtr instancePtr, string pchRenderModelName, string pchComponentName, /* System.Text.StringBuilder */ void* pchComponentRenderModelName, uint unComponentRenderModelNameLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRRenderModels_GetComponentState(IntPtr instancePtr, string pchRenderModelName, string pchComponentName, VRControllerState_t controllerState, ComponentState_t* pComponentState) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRControlPanel_GetDriverCount(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRControlPanel_GetDriverId(IntPtr instancePtr, uint unDriverIndex, string pchBuffer, uint unBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRControlPanel_GetDriverDisplayCount(IntPtr instancePtr, string pchDriverId) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRControlPanel_GetDriverDisplayId(IntPtr instancePtr, string pchDriverId, uint unDisplayIndex, string pchBuffer, uint unBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRControlPanel_GetDriverDisplayModelNumber(IntPtr instancePtr, string pchDriverId, string pchDisplayId, string pchBuffer, uint unBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRControlPanel_GetDriverDisplaySerialNumber(IntPtr instancePtr, string pchDriverId, string pchDisplayId, string pchBuffer, uint unBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRControlPanel_LoadSharedResource(IntPtr instancePtr, string pchResourceName, string pchBuffer, uint unBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE float VR_IVRControlPanel_GetIPD(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRControlPanel_SetIPD(IntPtr instancePtr, float fIPD) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE IntPtr VR_IVRControlPanel_GetCurrentCompositorInterface(IntPtr instancePtr, string pchInterfaceVersion) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRControlPanel_QuitProcess(IntPtr instancePtr, uint pidProcessToQuit) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRControlPanel_StartVRProcess(IntPtr instancePtr, string pchExecutable, string pchArguments, uint unArgumentCount, string pchWorkingDirectory) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRControlPanel_SetMasterProcessToThis(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRNotifications_GetErrorString(IntPtr instancePtr, NotificationError_t error, /* System.Text.StringBuilder */ void* pchBuffer, uint unBufferSize) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE NotificationError_t VR_IVRNotifications_CreateNotification(IntPtr instancePtr, ulong ulOverlayHandle, ulong ulUserValue, string strType, string strText, string strCategory, NotificationBitmap* photo, uint* notificationId) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE NotificationError_t VR_IVRNotifications_DismissNotification(IntPtr instancePtr, uint notificationId) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE IntPtr VR_IVRSettings_GetSettingsErrorNameFromEnum(IntPtr instancePtr, uint eError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSettings_Sync(IntPtr instancePtr, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRSettings_GetBool(IntPtr instancePtr, string pchSection, string pchSettingsKey, bool bDefaultValue, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSettings_SetBool(IntPtr instancePtr, string pchSection, string pchSettingsKey, bool bValue, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE int VR_IVRSettings_GetInt32(IntPtr instancePtr, string pchSection, string pchSettingsKey, int nDefaultValue, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSettings_SetInt32(IntPtr instancePtr, string pchSection, string pchSettingsKey, int nValue, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE float VR_IVRSettings_GetFloat(IntPtr instancePtr, string pchSection, string pchSettingsKey, float flDefaultValue, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSettings_SetFloat(IntPtr instancePtr, string pchSection, string pchSettingsKey, float flValue, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSettings_GetString(IntPtr instancePtr, string pchSection, string pchSettingsKey, string pchValue, uint unValueLen, string pchDefaultValue, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRSettings_SetString(IntPtr instancePtr, string pchSection, string pchSettingsKey, string pchValue, uint* peError) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_HasCamera(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_GetCameraFirmwareDescription(IntPtr instancePtr, uint nDeviceIndex, string pBuffer, uint nBufferLen) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_GetCameraFrameDimensions(IntPtr instancePtr, uint nDeviceIndex, uint nVideoStreamFormat, uint* pWidth, uint* pHeight) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_SetCameraVideoStreamFormat(IntPtr instancePtr, uint nDeviceIndex, uint nVideoStreamFormat) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE uint VR_IVRTrackedCamera_GetCameraVideoStreamFormat(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_EnableCameraForStreaming(IntPtr instancePtr, uint nDeviceIndex, bool bEnable) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_StartVideoStream(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_StopVideoStream(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_IsVideoStreamActive(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE float VR_IVRTrackedCamera_GetVideoStreamElapsedTime(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE IntPtr VR_IVRTrackedCamera_GetVideoStreamFrame(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_ReleaseVideoStreamFrame(IntPtr instancePtr, uint nDeviceIndex, CameraVideoStreamFrame_t* pFrameImage) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_SetAutoExposure(IntPtr instancePtr, uint nDeviceIndex, bool bEnable) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_SupportsPauseResume(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_PauseVideoStream(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_ResumeVideoStream(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRTrackedCamera_IsVideoStreamPaused(IntPtr instancePtr, uint nDeviceIndex) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperoneSetup_CommitWorkingCopy(IntPtr instancePtr, uint configFile) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperoneSetup_RevertWorkingCopy(IntPtr instancePtr) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperoneSetup_GetWorkingPlayAreaSize(IntPtr instancePtr, float* pSizeX, float* pSizeZ) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperoneSetup_GetWorkingPlayAreaRect(IntPtr instancePtr, HmdQuad_t* rect) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperoneSetup_GetWorkingCollisionBoundsInfo(IntPtr instancePtr, /* [In, Out] */ HmdQuad_t* pQuadsBuffer, uint* punQuadsCount) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperoneSetup_GetLiveCollisionBoundsInfo(IntPtr instancePtr, /* [In, Out] */ HmdQuad_t* pQuadsBuffer, uint* punQuadsCount) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperoneSetup_GetWorkingSeatedZeroPoseToRawTrackingPose(IntPtr instancePtr, HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE bool VR_IVRChaperoneSetup_GetWorkingStandingZeroPoseToRawTrackingPose(IntPtr instancePtr, HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperoneSetup_SetWorkingPlayAreaSize(IntPtr instancePtr, float sizeX, float sizeZ) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperoneSetup_SetWorkingCollisionBoundsInfo(IntPtr instancePtr, /* [In, Out] */ HmdQuad_t* pQuadsBuffer, uint unQuadsCount) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperoneSetup_SetWorkingSeatedZeroPoseToRawTrackingPose(IntPtr instancePtr, IntPtr matSeatedZeroPoseToRawTrackingPose) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperoneSetup_SetWorkingStandingZeroPoseToRawTrackingPose(IntPtr instancePtr, IntPtr matStandingZeroPoseToRawTrackingPose) { CHECKPOINT_C(instancePtr); }

VR_INTERFACE void VR_IVRChaperoneSetup_ReloadFromDisk(IntPtr instancePtr, uint configFile) { CHECKPOINT_C(instancePtr); }


//***************************************************************************

static void OnRenderEvent(int eventID)
{	
	//copy from openvr_api.cs ; public class Unity{...}
	const int k_nRenderEventID_WaitGetPoses = 201510020;
	const int k_nRenderEventID_SubmitL = 201510021;
	const int k_nRenderEventID_SubmitR = 201510022;
	const int k_nRenderEventID_Flush = 201510023;
	const int k_nRenderEventID_PostPresentHandoff = 201510024;

	const char* str;

	switch (eventID)
	{
	case k_nRenderEventID_WaitGetPoses:
		str = "k_nRenderEventID_WaitGetPoses";
		break;

	case k_nRenderEventID_SubmitL:
		str = "k_nRenderEventID_SubmitL";
		{
			//glClearColor(0.0,0.0,1.0,0.0);			
			//glClear(GL_COLOR_BUFFER_BIT);
		}
		break;

	case k_nRenderEventID_SubmitR:
		str = "k_nRenderEventID_SubmitR";
		{
			//glClearColor(1.0, 0.0, 0.0, 0.0);
			//glClear(GL_COLOR_BUFFER_BIT);
		}
		break;

	case k_nRenderEventID_Flush:
		str = "k_nRenderEventID_Flush";
		break;

	case k_nRenderEventID_PostPresentHandoff:
		str = "k_nRenderEventID_PostPresentHandoff"; 
		break;


	default:
		str = "unknown";
		break;
	}


//
	GLint drawFboId = 0, readFboId = 0;
		GLint texId0 = 0, texId1 = 0, texId2 = 0, texId3 = 0;
		//glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
		//glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);
		

		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &drawFboId);
		glGetIntegerv(GL_COLOR_ATTACHMENT0, &texId0);
		//glGetIntegerv(GL_COLOR_ATTACHMENT1, &texId1);
		//glGetIntegerv(GL_COLOR_ATTACHMENT2, &texId2);
		//glGetIntegerv(GL_COLOR_ATTACHMENT3, &texId3);

		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &texId1);
//		


	_TraceFormat("%s:%d (%d : fbo=%d, tex=%d,tex=%d,tex=%d,tex=%d) %s", __X_FUNCTION__, __LINE__, eventID,drawFboId,texId0, texId1, texId2, texId3, str);
}

//VR_INTERFACE IntPtr UnityHooks_GetRenderEventFunc()
extern "C" UnityRenderingEvent UnityHooks_GetRenderEventFunc()
{
	//CHECKPOINT_C(0);
	return OnRenderEvent;
}

VR_INTERFACE void UnityHooks_SetSubmitParams(VRTextureBounds_t boundsL, VRTextureBounds_t boundsR, VRSubmitFlags_t nSubmitFlags)
{
	_TraceFormat("%s:%d L(%3.2f,%3.2f,%3.2f,%3.2f), R(%3.2f,%3.2f,%3.2f,%3.2f), flag=%d", __X_FUNCTION__, __LINE__,
		boundsL.uMin, boundsL.vMin, boundsL.uMax, boundsL.vMax,
		boundsR.uMin, boundsR.vMin, boundsR.uMax, boundsR.vMax,
		nSubmitFlags);	
}

VR_INTERFACE void UnityHooks_EventWriteString(string sEvent)
{
	//CHECKPOINT_C(0);
	_TraceFormat("%s:%d -- %s", __X_FUNCTION__, __LINE__, sEvent);
}


