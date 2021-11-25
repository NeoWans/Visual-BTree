cmake_minimum_required(VERSION 3.5)
project(Visual-BTree VERSION 0.1 LANGUAGES CXX)
list(APPEND CMAKE_PREFIX_PATH "/opt/Qt5.12.11/5.12.11/gcc_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -fpermissive")
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
include_directories(inc)
add_library(btree SHARED src/BNode.cc src/BTree.cc)
set(PROJECT_SOURCES
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(Visual-BTree
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
  )
# Define target properties for Android with Qt 6 as:
#  set_property(TARGET Visual-BTree APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#         ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(Visual-BTree SHARED
      ${PROJECT_SOURCES}
    )
# Define properties for Android with Qt 5 after find_package() calls as:
#  set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(Visual-BTree
      ${PROJECT_SOURCES}
    )
  endif()
endif()
target_link_libraries(Visual-BTree PRIVATE Qt${QT_VERSION_MAJOR}::Widgets btree gvc cgraph cdt)
set_target_properties(Visual-BTree PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(Visual-BTree)
endif()
