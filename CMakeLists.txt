cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(template)

option(WITH_GEANT4_UIVIS "Build project with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(template main.cc ${sources} ${headers})
target_link_libraries(template ${Geant4_LIBRARIES})

set(TEMPLATE_SCRIPTS
        init_vis.mac
        vis.mac
        run.mac
        loop_1_run.mac
        loop_2_run.mac
        gps_gun_vis.mac
        gps_gun.mac
        test.stl
        )

foreach(_script ${TEMPLATE_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


install(TARGETS template DESTINATION bin)


