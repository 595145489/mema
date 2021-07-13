add_executable(FirstOneTest FirstOneTest.cc)
target_link_libraries(FirstOneTest PRIVATE  mema_base)

add_executable(TestBaseSocket TestBaseSocket.cc)
target_link_libraries(TestBaseSocket PRIVATE  mema_base)

add_executable(LogTest LogTest.cc)
target_link_libraries(LogTest PRIVATE mema_base)

add_executable(TestThreadPool TestThreadPool.cc)
target_link_libraries(TestThreadPool PRIVATE mema_base)

add_executable(Client TestThreadPool1.cc)
target_link_libraries(Client PRIVATE mema_base)
