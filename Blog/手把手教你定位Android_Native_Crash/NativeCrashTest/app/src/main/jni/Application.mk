APP_PLATFORM := android-29

# 设置支持的 CPU 架构平台
APP_ABI := \
    armeabi x86

# 设置 C++ 支持库, see: https://developer.android.google.cn/ndk/guides/cpp-support
# 因为 ndk 弃用了 gcc，转而使用了 clang, 所以目前 c++_static 是最好的选择
APP_STL := c++_static