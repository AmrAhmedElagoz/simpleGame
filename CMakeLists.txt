cmake_minimum_required(VERSION 3.17)
project(simpleGame)
set(CMAKE_CXX_STANDARD 20)

option(BUILD_EXTERNALS "Build SFML and ImGui from submodules" ON)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

if(BUILD_EXTERNALS)
    message(STATUS "Building SFML and ImGui-SFML from submodules.")

    # Build SFML
    add_subdirectory(extern/SFML)

    # ImGui location
    set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui)

    # Tell ImGui-SFML not to look for SFML via find_package
    set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
    add_subdirectory(extern/imgui-sfml)

    # Libraries from submodules
    set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
    set(IMGUI_SFML_LIB ImGui-SFML::ImGui-SFML)

    set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
    )

else()
    message(STATUS "Using prebuilt SFML and ImGui-SFML.")

    # Helper to pick shared over static automatically
    function(add_sfml_imported name)
        set(lib_base ${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML/build/lib/lib${name})
        if(EXISTS ${lib_base}-s.a)
            # static
            add_library(${name} STATIC IMPORTED)
            set_target_properties(${name} PROPERTIES
                IMPORTED_LOCATION ${lib_base}-s.a
                INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML/include
            )
        elseif(EXISTS ${lib_base}.so)
            # shared
            add_library(${name} SHARED IMPORTED)
            set_target_properties(${name} PROPERTIES
                IMPORTED_LOCATION ${lib_base}.so
                INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML/include
            )
        else()
            message(FATAL_ERROR "SFML library for ${name} not found in ${lib_base}(-s.a|.so)")
        endif()
    endfunction()

    # Prebuilt SFML libs
    add_sfml_imported(sfml-system)
    add_sfml_imported(sfml-window)
    add_sfml_imported(sfml-graphics)
    add_sfml_imported(sfml-audio)
    add_sfml_imported(sfml-network)

    set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

    # Prebuilt ImGui-SFML
    set(IMGUI_SFML_BASE ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui-sfml/build/libImGui-SFML)
    if(EXISTS ${IMGUI_SFML_BASE}.so)
        add_library(ImGui-SFML::ImGui-SFML SHARED IMPORTED)
        set_target_properties(ImGui-SFML::ImGui-SFML PROPERTIES
            IMPORTED_LOCATION ${IMGUI_SFML_BASE}.so
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui-sfml
        )
    elseif(EXISTS ${IMGUI_SFML_BASE}.a)
        add_library(ImGui-SFML::ImGui-SFML STATIC IMPORTED)
        set_target_properties(ImGui-SFML::ImGui-SFML PROPERTIES
            IMPORTED_LOCATION ${IMGUI_SFML_BASE}.a
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui-sfml
        )
    else()
        message(FATAL_ERROR "Prebuilt ImGui-SFML not found at ${IMGUI_SFML_BASE}.so or .a")
    endif()

    set(IMGUI_SFML_LIB ImGui-SFML::ImGui-SFML)

    set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui/backends
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML/include
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui-sfml
    )

endif()

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SFML_LIBS}
    ${IMGUI_SFML_LIB}
)

# Extra system libs when using prebuilt
if(NOT BUILD_EXTERNALS)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        pthread
        dl
        X11
        Xrandr
        udev
        freetype
        GL
    )
endif()
