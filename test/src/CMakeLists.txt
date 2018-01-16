include_directories(../.. .)

if (HAVE_CONFIG_H)
	add_definitions(-DHAVE_CONFIG_H)
	set(LIB_SOURCE_FILES
		../../libfswatch_config.h)
endif(HAVE_CONFIG_H)

set(SOURCE_FILES
        fswatch_test.c)

add_executable(fswatch_test ${SOURCE_FILES})
target_link_libraries(fswatch_test LINK_PUBLIC libfswatch)
