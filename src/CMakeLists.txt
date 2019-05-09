set(lib_SRCS
    client.cpp
    group.cpp
    stacking_order.cpp
    toplevel.cpp
)

add_library(stackingorder SHARED ${lib_SRCS})
target_link_libraries(stackingorder
    Qt5::Core
    Qt5::Gui

    KF5::WindowSystem
)
