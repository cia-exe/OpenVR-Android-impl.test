copy ..\libs\armeabi\libopenvr_api.so "D:\Workspace\VR\work\OpenVr_SDK_Implemant\unity_prj\New Unity Project\Assets\Plugins\Android\libs\armeabi"
copy ..\libs\armeabi-v7a\libopenvr_api.so "D:\Workspace\VR\work\OpenVr_SDK_Implemant\unity_prj\New Unity Project\Assets\Plugins\Android\libs\armeabi-v7a"
adb push ..\libs\armeabi\libopenvr_api.so /data/data/com.test.openvr/lib/libopenvr_api.so
