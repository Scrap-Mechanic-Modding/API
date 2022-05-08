add_library(API SHARED
	common.hpp
	utility/ByteStream.hpp
	utility/ByteStream.cpp
	utility/ProgramHeader.hpp
	utility/ProgramHeader.cpp
	utility/Utils.hpp
	utility/Utils.cpp
	utility/VMT.hpp
	utility/ProgramHeader.hpp
	utility/ProgramHeader.cpp
	utility/InstanceManager.hpp
	utility/InstanceManager.cpp
	network/Packets/Packet.hpp
	network/Packets/GenericPacket.hpp
	network/Packets/GenericPacket.cpp
	network/Packets/C2S_ChatPacket.hpp
	network/Packets/C2S_ChatPacket.cpp
	network/CompressionHelper.hpp
	network/CompressionHelper.cpp
	network/PacketParser.hpp
	network/PacketParser.cpp
	network/hook.hpp
	network/hook.cpp
	dll_main.cpp
)

target_link_libraries(API steam_api64)
target_link_libraries(API lz4)

target_link_directories(API PRIVATE "${CMAKE_SOURCE_DIR}/lib")
target_include_directories(API PRIVATE "${CMAKE_SOURCE_DIR}/include")

set_property(TARGET API PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")