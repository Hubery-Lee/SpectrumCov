#----------------------------------------------------------------------------
# Qt setup
# instruct cmake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)   # saves having to use QT5_WRAP_CPP
set(CMAKE_AUTORCC ON)   # saves having to use QT5_ADD_RESOURCES
set(CMAKE_AUTOUIC ON)   # saves having to use QT5_WRAP_UI

find_package(Qt5 COMPONENTS Core REQUIRED) # Core stuff
find_package(Qt5 COMPONENTS Gui REQUIRED) # Gui for openGL integration
# find_package(Qt5 COMPONENTS NetWork REQUIRED) # for network 
# find_package(Qt5 COMPONENTS Concurrent REQUIRED) # for threading
# find_package(Qt5 COMPONENTS Gamepad)  # controller support
# find_package(Qt5 COMPONENTS OpenGLExtensions REQUIRED)  #for openGL
# find_package(Qt5OpenGL)
# find_package(Qt5 COMPONENTS Multimedia REQUIRED) # multimedia capabilities
# find_package(Qt5 COMPONENTS MultimediaWidgets REQUIRED) # 
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# copy form auto generation
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
#----------------------------------------------------------------------------
# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
# find_package(ROOT REQUIRED)
find_package(ROOT REQUIRED COMPONENTS Core Cling RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics Gui MathCore Thread)
#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    )
# find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# # setup include directory for this project
# include_directories(.)
#----------------------------------------------------------------------------
# 需要设置的文件
# file(GLOB Dict_headers ${PROJECT_SOURCE_DIR}/example2b.h) #dictionary headerfiles
# file(GLOB Dict_sources ${PROJECT_SOURCE_DIR}/example2b.cxx) #dictionary sourcefiles
# file(GLOB LinkDeffs ${PROJECT_SOURCE_DIR}/ex2bLinkDef.h) #linkdeffiles
# #----------------------------------------------------------------------------
# # 生成ROOT检索预编译文件
# ROOT_GENERATE_DICTIONARY(myDict ${Dict_headers} LINKDEF ${LinkDeffs})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cxx)
file(GLOB headers ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB forms ${PROJECT_SOURCE_DIR}/src/*.ui)
file(GLOB resources ${PROJECT_SOURCE_DIR}/src/images.qrc)
file(GLOB rc_icons ${PROJECT_SOURCE_DIR}/src/winapp.ico)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Qt libraries
# 
# add_executable(${PROJECT_NAME} ${sources} ${headers} ${forms} ${resources} ${rc_icons} appicon.rc)  #for windows
add_executable(${PROJECT_NAME} ${sources} ${headers} ${forms} ${resources} ${rc_icons})

target_link_libraries( ${PROJECT_NAME} PRIVATE ${ROOT_LIBRARIES}   Qt${QT_VERSION_MAJOR}::Widgets)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS ${PROJECT_NAME}  DESTINATION bin)
# install(TARGETS LIHUI DESTINATION lib)
