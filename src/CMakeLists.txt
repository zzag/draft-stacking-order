set(lib_SRCS
    StackingOrder.cc
    Toplevel.cc
)

add_library(stackingorder SHARED ${lib_SRCS})
target_link_libraries(stackingorder Qt5::Core Qt5::Gui)
