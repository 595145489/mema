file(GLOB base_SRC "*.cc")
add_library(mema_base_lib ${base_SRC})

target_include_directories(mema_base_lib PUBLIC ${PROJECT_SOURCE_DIR}/mema) 
target_link_libraries(mema_base_lib PUBLIC gflags::gflags)

find_package(Threads)
target_link_libraries(mema_base_lib PUBLIC -lpthread )
file(GLOB HEADSLIB "*.h")

install(FILES ${HEADSLIB} DESTINATION ${PROJECT_SOURCE_DIR}/bin/include/base)
install(TARGETS mema_base_lib DESTINATION ${PROJECT_SOURCE_DIR}/bin/lib/base)
