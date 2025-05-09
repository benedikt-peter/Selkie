add_library(SelkieProtocol
        include/message.h
        include/messagequeue.h
        include/msgpackserializer.h
        include/serializer.h
)

target_include_directories(SelkieProtocol PUBLIC include)

target_link_libraries(SelkieProtocol spdlog::spdlog enet_static msgpack-cxx)

set_property(TARGET SelkieProtocol PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)