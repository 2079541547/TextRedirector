cmake_minimum_required(VERSION 3.22.1)

project("terrariatextredirector")


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -flto")


set(DOBBY_LIB ${CMAKE_CURRENT_SOURCE_DIR}/DependencyLibrary/Dobby/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a)


set(BNM_INCLUDE_DIRS
        DependencyLibrary/BNM/include
        DependencyLibrary/BNM/external/include
        DependencyLibrary/BNM/external
        DependencyLibrary/BNM/external/utf8
        DependencyLibrary/BNM/src/private
)

add_library(
        BNM
        STATIC
        DependencyLibrary/BNM/src/Class.cpp
        DependencyLibrary/BNM/src/ClassesManagement.cpp
        DependencyLibrary/BNM/src/Coroutine.cpp
        DependencyLibrary/BNM/src/Defaults.cpp
        DependencyLibrary/BNM/src/Delegates.cpp
        DependencyLibrary/BNM/src/EventBase.cpp
        DependencyLibrary/BNM/src/Exceptions.cpp
        DependencyLibrary/BNM/src/FieldBase.cpp
        DependencyLibrary/BNM/src/Hooks.cpp
        DependencyLibrary/BNM/src/Image.cpp
        DependencyLibrary/BNM/src/Internals.cpp
        DependencyLibrary/BNM/src/Loading.cpp
        DependencyLibrary/BNM/src/MethodBase.cpp
        DependencyLibrary/BNM/src/MonoStructures.cpp
        DependencyLibrary/BNM/src/PropertyBase.cpp
        DependencyLibrary/BNM/src/UnityStructures.cpp
        DependencyLibrary/BNM/src/Utils.cpp
)

target_include_directories(
        BNM
        PUBLIC
        ${BNM_INCLUDE_DIRS}
        DependencyLibrary/Dobby
)

target_link_libraries(
        BNM
        PUBLIC
        log
        ${DOBBY_LIB}
)


set(SRC_CPP
        native-lib.cpp
        Src/log.cpp
        Src/initialize.cpp
        Src/tool/export.cpp
        Src/tool/redirect.cpp
)


add_library(${CMAKE_PROJECT_NAME} SHARED
        ${SRC_CPP}
)

target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC
        Includes
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        BNM
        log)