#!/bin/sh
 
echo ""
echo "Compiling ..."
/home/ken/Working/android-ndk-r10e/ndk-build NDK_PROJECT_PATH=. NDK_APPLICATION_MK=Application.mk  APP_BUILD_SCRIPT=Android.mk
mv libs/armeabi/libopenvr_api.so ..

echo ""
echo "Cleaning up / removing build folders..."  #optional..
rm -rf libs
rm -rf obj
rm -rf org

echo ""
echo "Done!"
