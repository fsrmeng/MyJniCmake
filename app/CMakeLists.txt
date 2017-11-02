# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
#设置构建本地库所需的最小CMake版本
cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#添加自己写的C/C++源文件
add_library( # Sets the name of the library.
             zhangpan

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/zhangpan.c)

add_library( # Sets the name of the library.
             file_encryption

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/file_encryption.c)

add_library( # Sets the name of the library.
             file_patch

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/file_patch.c)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

#依赖NDK中的库
find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

#将目标库与NDK中的库进行连接
target_link_libraries( # Specifies the target library.
                       zhangpan

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
target_link_libraries( # Specifies the target library.
                       file_encryption

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
target_link_libraries( # Specifies the target library.
                       file_patch

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )