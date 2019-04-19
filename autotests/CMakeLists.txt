set(testStackingOrder_SRCS StackingOrderTest.cc)
add_executable(testStackingOrder ${testStackingOrder_SRCS})
target_link_libraries(testStackingOrder Qt5::Test stackingorder)
add_test(NAME testStackingOrder COMMAND testStackingOrder)
