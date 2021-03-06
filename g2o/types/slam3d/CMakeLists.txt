ADD_LIBRARY(types_slam3d ${G2O_LIB_TYPE}
  isometry3d_gradients.cpp
  isometry3d_gradients.h
  se3_ops.hpp 
  se3_ops.h
  se3quat_gradients.cpp
  se3quat_gradients.h
  vertex_se3_quat.cpp
  vertex_se3_quat.h
  edge_se3_quat.cpp
  edge_se3_quat.h
  vertex_pointxyz.cpp
  vertex_pointxyz.h
  parameter_se3_offset.cpp
  parameter_se3_offset.h
  edge_se3_offset.cpp
  edge_se3_offset.h
  edge_se3_prior.cpp
  edge_se3_prior.h
  edge_se3_pointxyz.cpp
  edge_se3_pointxyz.h
  parameter_camera.cpp
  parameter_camera.h
  edge_se3_pointxyz_disparity.cpp
  edge_se3_pointxyz_disparity.h
  edge_se3_pointxyz_depth.cpp
  edge_se3_pointxyz_depth.h
  types_slam3d.cpp
  types_slam3d.h
  g2o_types_slam3d_api.h
)


SET_TARGET_PROPERTIES(types_slam3d PROPERTIES OUTPUT_NAME ${LIB_PREFIX}types_slam3d)

TARGET_LINK_LIBRARIES(types_slam3d ${OPENGL_gl_LIBRARY}  core)


INSTALL(TARGETS types_slam3d
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

ADD_EXECUTABLE(test_se3quat test_se3quat)
SET_TARGET_PROPERTIES(test_se3quat PROPERTIES OUTPUT_NAME test_se3quat${EXE_POSTFIX})

TARGET_LINK_LIBRARIES(test_se3quat types_slam3d)


FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

INSTALL(FILES ${headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/g2o/types/slam3d)


