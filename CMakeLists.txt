project(MediaCenterComponents)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${KDE4_INCLUDES}
    libs/
)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

add_subdirectory(browsingbackends)
add_subdirectory(mediaelements)
add_subdirectory(libs)
add_subdirectory(shells)

message("*** QtMultimediaKit (included in Qt-Mobility) is required at runtime to play multimedia.")
message("*** You can download it from http://get.qt.nokia.com/qt/add-ons/qt-mobility-opensource-src-1.2.0.zip .")

