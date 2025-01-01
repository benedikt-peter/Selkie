add_executable(SelkieServer src/main.cpp
        src/network/ENetServer.h
        src/network/MsgPackSerializer.h)

target_link_libraries(SelkieServer PRIVATE EnTT::EnTT spdlog::spdlog enet_static msgpack-cxx) # boost_program_options