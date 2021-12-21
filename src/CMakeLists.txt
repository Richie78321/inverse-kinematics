file(GLOB SOURCE_FILES *.cpp)

add_library(InverseKinematics ${SOURCE_FILES})

target_link_libraries(InverseKinematics linalg)
target_include_directories(InverseKinematics PUBLIC ../include/src)