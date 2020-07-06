cmake_minimum_required(VERSION 3.10.2)
project(main)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS graphics window system)
add_executable(game test.cpp)
target_link_libraries(myapp sfml-graphics sfml-audio)

if (NOT SFML_FIND_COMPONENTS)
    message(FATAL_ERROR "find_package(SFML) called with no component")
endif()

set(FIND_SFML_PATHS
    "${CMAKE_CURRENT_LIST_DIR}/../.."
    ${SFML_ROOT}
    $ENV{SFML_ROOT}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt)

find_path(SFML_DOC_DIR SFML.tag
          PATH_SUFFIXES SFML/doc share/doc/SFML
          PATHS ${FIND_SFML_PATHS})


# Update requested components (eg. request window component if graphics component was requested)
set(FIND_SFML_SYSTEM_DEPENDENCIES "")
set(FIND_SFML_MAIN_DEPENDENCIES "")
set(FIND_SFML_AUDIO_DEPENDENCIES system)
set(FIND_SFML_NETWORK_DEPENDENCIES system)
set(FIND_SFML_WINDOW_DEPENDENCIES system)
set(FIND_SFML_GRAPHICS_DEPENDENCIES window system)
set(FIND_SFML_ADDITIONAL_COMPONENTS "")
foreach(component ${SFML_FIND_COMPONENTS})
    string(TOUPPER "${component}" UPPER_COMPONENT)
    list(APPEND FIND_SFML_ADDITIONAL_COMPONENTS ${FIND_SFML_${UPPER_COMPONENT}_DEPENDENCIES})
endforeach()
list(APPEND SFML_FIND_COMPONENTS ${FIND_SFML_ADDITIONAL_COMPONENTS})
list(REMOVE_DUPLICATES SFML_FIND_COMPONENTS)

# Choose which target definitions must be imported
if (SFML_STATIC_LIBRARIES)
	set(SFML_IS_FRAMEWORK_INSTALL "@SFML_BUILD_FRAMEWORKS@")
    if (SFML_IS_FRAMEWORK_INSTALL)
        message(WARNING "Static frameworks are not supported by SFML. Clear SFML_DIR cache entry, \
and either change SFML_STATIC_LIBRARIES or CMAKE_FIND_FRAMEWORK before calling find_package(SFML)")
    endif()
    set(config_name "Static")
else()
    set(config_name "Shared")
endif()
set(targets_config_file "${CMAKE_CURRENT_LIST_DIR}/SFML${config_name}Targets.cmake")

# Generate imported targets for SFML and its dependencies
if (EXISTS "${targets_config_file}")
    # Set SFML_FOUND to TRUE by default, may be overwritten by one of the includes below
    set(SFML_FOUND TRUE)
    include("${targets_config_file}")
    include("${CMAKE_CURRENT_LIST_DIR}/SFMLConfigDependencies.cmake")

    if (SFML_FOUND)
        foreach (component ${SFML_FIND_COMPONENTS})
            string(TOUPPER "${component}" UPPER_COMPONENT)
            if (TARGET sfml-${component})
                set(SFML_${UPPER_COMPONENT}_FOUND TRUE)
            else()
                set(FIND_SFML_ERROR "Found SFML but requested component '${component}' is missing in the config defined in ${SFML_DIR}.")
                set(SFML_${UPPER_COMPONENT}_FOUND FALSE)
                set(SFML_FOUND FALSE)
            endif()
        endforeach()
    endif()
else()
    set(FIND_SFML_ERROR "Requested SFML configuration (${config_name}) was not found")
    set(SFML_FOUND FALSE)
endif()

if (NOT SFML_FOUND)
    if(SFML_FIND_REQUIRED)
        # fatal error
        message(FATAL_ERROR "${FIND_SFML_ERROR}")
    elseif(NOT SFML_FIND_QUIETLY)
        # error but continue
        message(STATUS "${FIND_SFML_ERROR}")
    endif()
endif()

if (SFML_FOUND AND NOT SFML_FIND_QUIETLY)
    message(STATUS "Found SFML @VERSION_MAJOR@.@VERSION_MINOR@.@VERSION_PATCH@ in ${CMAKE_CURRENT_LIST_DIR}")
endif()