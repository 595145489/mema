add_subdirectory(thirdparty/gflags)
add_subdirectory(base)

file(GLOB base_SRC "*.cc")
file(GLOB thread_SRC "thread/*.cc")
file(GLOB poller_SRC "poller/*.cc")
file(GLOB socketopt_SRC "socketopt/*.cc")
file(GLOB writerbatch_SRC "writerbatch/*.cc")

add_library(mema_base ${base_SRC} ${thread_SRC} ${poller_SRC} ${socketopt_SRC} ${writerbatch_SRC})

target_include_directories(mema_base PUBLIC ${PROJECT_SOURCE_DIR}/mema) 
target_link_libraries(mema_base PUBLIC mema_base_lib)
target_link_libraries(mema_base PUBLIC gflags::gflags)

file(GLOB HEADS "*.h")
file(GLOB thread_HEADS "thread/*.h")
file(GLOB poller_HEADS "poller/*.h")
file(GLOB socketopt_HEADS "socketopt/*.h")
file(GLOB writerbatch_HEADS"writerbatch/*.h")

install(FILES ${HEADS} ${thread_HEADS} ${poller_HEADS} ${socketopt_HEADS} ${writerbatch_HEADS} DESTINATION ${PROJECT_SOURCE_DIR}/bin/include)
install(TARGETS mema_base DESTINATION ${PROJECT_SOURCE_DIR}/bin/lib)

if(MEMA_BUILD_TESTS)
    add_subdirectory(tests)
endif()
