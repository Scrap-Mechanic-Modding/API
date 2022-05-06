add_library(PacketParser SHARED
	common.hpp
	Utils.hpp
	Utils.cpp
	VMT.hpp
	ByteStream.hpp
	ByteStream.cpp
	Packets/Packet.hpp
	Packets/GenericPacket.hpp
	Packets/GenericPacket.cpp
	Packets/C2S_ChatPacket.hpp
	Packets/C2S_ChatPacket.cpp
	CompressionHelper.hpp
	CompressionHelper.cpp
	PacketParser.hpp
	PacketParser.cpp
	hook.hpp
	hook.cpp
	dll_main.cpp
)

target_link_libraries(PacketParser steam_api64)
target_link_libraries(PacketParser lz4)

target_link_directories(PacketParser PRIVATE "${CMAKE_SOURCE_DIR}/lib")
target_include_directories(PacketParser PRIVATE "${CMAKE_SOURCE_DIR}/include")

set_property(TARGET PacketParser PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")