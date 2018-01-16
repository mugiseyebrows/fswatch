include_directories(../.. . ../../..
../../libfswatch/src/libfswatch/c++/windows/msys
../../libfswatch/src/libfswatch/c++/windows)

if (HAVE_CONFIG_H)
	add_definitions(-DHAVE_CONFIG_H)
	set(SOURCE_FILES
		../../libfswatch_config.h)
else()
  add_definitions(
  -DPACKAGE=fswatch
  -DPACKAGE_BUGREPORT=enrico.m.crisostomo@gmail.com
  -DPACKAGE_NAME=fswatch
  -DPACKAGE_STRING=fswatch 1.11.2
  -DPACKAGE_TARNAME=fswatch
  -DPACKAGE_URL=https://github.com/emcrisostomo/fswatch
  -DPACKAGE_VERSION=1.11.2
  -DVERSION=1.11.2)
endif()

set(SOURCE_FILES
        fswatch.cpp
        fswatch.hpp
        gettext.h)

if (WIN32)
  add_definitions(
      -DHAVE_WINDOWS=1
      -DHAVE_STRUCT_STAT_ST_MTIME=1
      -DHAVE_GETOPT_LONG=1)
endif(WIN32)

if (MSYS)
    set(SOURCE_FILES
        ${SOURCE_FILES}
            ../../libfswatch/src/libfswatch/c++/windows/msys/file-type.h
            ../../libfswatch/src/libfswatch/c++/windows/msys/realpath.cpp
            ../../libfswatch/src/libfswatch/c++/windows/msys/realpath.h)
    add_definitions(-DHAVE_MSYS)
endif(MSYS)

add_executable(fswatch ${SOURCE_FILES})
target_link_libraries(fswatch LINK_PUBLIC libfswatch)

if (MSYS)
    install(TARGETS fswatch DESTINATION "${CMAKE_ROOT}/../../bin" )
endif(MSYS)
