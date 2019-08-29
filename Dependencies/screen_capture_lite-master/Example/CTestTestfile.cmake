# CMake generated Testfile for 
# Source directory: C:/Users/Edward/source/repos/EntropiaMinerLeague/Dependencies/screen_capture_lite-master/Example
# Build directory: C:/Users/Edward/source/repos/EntropiaMinerLeague/Dependencies/screen_capture_lite-master/Example
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(screen_capture_example "C:/Users/Edward/source/repos/EntropiaMinerLeague/Dependencies/screen_capture_lite-master/Example/Debug/screen_capture_example.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(screen_capture_example "C:/Users/Edward/source/repos/EntropiaMinerLeague/Dependencies/screen_capture_lite-master/Example/Release/screen_capture_example.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(screen_capture_example "C:/Users/Edward/source/repos/EntropiaMinerLeague/Dependencies/screen_capture_lite-master/Example/MinSizeRel/screen_capture_example.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(screen_capture_example "C:/Users/Edward/source/repos/EntropiaMinerLeague/Dependencies/screen_capture_lite-master/Example/RelWithDebInfo/screen_capture_example.exe")
else()
  add_test(screen_capture_example NOT_AVAILABLE)
endif()
