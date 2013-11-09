INCLUDE(CollectSrcs)
PROJECT(cpp-protobuf)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES($ENV{GCC_PLUGIN_INCLUDE})
INCLUDE_DIRECTORIES($ENV{LOCAL_INCLUDE})
INCLUDE_DIRECTORIES(common entry generator meta parser)
LINK_DIRECTORIES($ENV{LOCAL_LIB})

ADD_SUBDIRECTORY(entry)
ADD_SUBDIRECTORY(common)
ADD_SUBDIRECTORY(parser)
ADD_SUBDIRECTORY(meta)
ADD_SUBDIRECTORY(generator)

SET(cpp_protobuf_SUBDIRS common entry generator parser meta)
GET_SRCS(cpp_protobuf_SRClISTS cpp_protobuf_SUBDIRS)

ADD_LIBRARY(cpp-protobuf SHARED ${cpp_protobuf_SRClISTS})
TARGET_LINK_LIBRARIES(cpp-protobuf boost_date_time)
TARGET_LINK_LIBRARIES(cpp-protobuf boost_system)
TARGET_LINK_LIBRARIES(cpp-protobuf boost_filesystem)
TARGET_LINK_LIBRARIES(cpp-protobuf pthread)
INSTALL(TARGETS cpp-protobuf 
    LIBRARY DESTINATION bin
    RUNTIME DESTINATION  bin)
