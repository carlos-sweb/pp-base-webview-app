cmake_minimum_required(VERSION 3.16)
project(base LANGUAGES C)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(WEBKIT REQUIRED IMPORTED_TARGET webkitgtk-6.0)
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)
set(RESOURCE_XML ${CMAKE_CURRENT_SOURCE_DIR}/src/base-gresource.xml)
set(GENERATED_RESOURCE_C ${CMAKE_CURRENT_SOURCE_DIR}/src/base-gresource.c)
add_custom_command(
  OUTPUT ${GENERATED_RESOURCE_C}
  COMMAND ${GLIB_COMPILE_RESOURCES} 
    --target=${GENERATED_RESOURCE_C}
    --generate-source 
    --sourcedir=${CMAKE_CURRENT_SOURCE_DIR}/www 
    ${RESOURCE_XML}
  DEPENDS ${RESOURCE_XML}  
  VERBATIM 
)
add_executable(${PROJECT_NAME} src/main.c ${GENERATED_RESOURCE_C})
target_link_libraries(${PROJECT_NAME} 
    PkgConfig::GTK
    PkgConfig::WEBKIT
)
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)