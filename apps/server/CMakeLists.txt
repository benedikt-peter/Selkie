add_executable(SelkieServer src/main.cpp
        src/network/enetserver.h
        src/network/msgpackserializer.h
        src/network/enetserver.cpp
        src/network/serializer.h
        src/network/eventsbuffer.h
        src/network/events.h
        src/network/message.h
)

target_link_libraries(SelkieServer PRIVATE EnTT::EnTT boost_core spdlog::spdlog enet_static msgpack-cxx) # boost_program_options

set_property(TARGET SelkieServer PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)