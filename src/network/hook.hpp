#pragma once

#include "../common.hpp"
#include "PacketParser.hpp"
#include "../utility/Utils.hpp"
#include "../utility/VMT.hpp"
#include "hook.hpp"

#include <memory>
#include <cstdint>


int hookNetworkingFuncs(uintptr_t baseAddress);