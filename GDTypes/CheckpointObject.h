#pragma once
#include "PlayerCheckpoint.h"
namespace GT {
	class CheckpointObject{
	public:
		char pad_0000[240]; //0x0000
		PlayerCheckpoint* playerCheckpoint; //0x00F0
		PlayerCheckpoint* player2Checkpoint; //0x00F4
	}; //Size: 0x00F8
}
