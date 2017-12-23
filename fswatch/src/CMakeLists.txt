include_directories(../.. . ../../..)
add_definitions(-DHAVE_CONFIG_H)
set(SOURCE_FILES
        fswatch.cpp
        fswatch.hpp
        gettext.h
        ../../libfswatch_config.h)

if (MSYS)
    set(SOURCE_FILES
        ${SOURCE_FILES}
            ../../libfswatch/src/libfswatch/c++/windows/msys/file-type.h
            ../../libfswatch/src/libfswatch/c++/windows/msys/libfswatch_config.h
            ../../libfswatch/src/libfswatch/c++/windows/msys/realpath.cpp
            ../../libfswatch/src/libfswatch/c++/windows/msys/realpath.h)
    add_definitions(-DHAVE_MSYS)
endif(MSYS)

add_executable(fswatch ${SOURCE_FILES})
target_link_libraries(fswatch LINK_PUBLIC libfswatch)

if (MSYS)
    install(TARGETS fswatch DESTINATION "${CMAKE_ROOT}/../../bin" )
endif(MSYS)
