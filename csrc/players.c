#include "player_info.h"

player_info players[4];

int nplayers;
int current_player;

player_info rich4_players[12] = {
	{
		.name_ptr = 0x004665c4,
		.f4 = 0x00946126,
		.traffic_method = 0,
		.ndices = 1,
		.character = 0,
		.f20 = 1,
		.f22 = 3,
		.f23 = 2,
		.f24 = 60,
		.init_cash_ratio = 50,
		.f26 = 30,
	},
	{
		.name_ptr = 0x004665cd,
		.f4 = 0x00bdc3c6,
		.traffic_method = 0,
		.ndices = 1,
		.character = 1,
		.f20 = 1,
		.f22 = 3,
		.f23 = 1,
		.f24 = 100,
		.init_cash_ratio = 40,
		.f26 = 45,
	},
	{
		.name_ptr = 0x004665d6,
		.f4 = 0x0041323b,
		.traffic_method = 0,
		.ndices = 1,
		.character = 2,
		.f20 = 1,
		.f22 = 3,
		.f23 = 2,
		.f24 = 0,
		.init_cash_ratio = 70,
		.f26 = 0,
	},
	{
		.name_ptr = 0x004665df,
		.f4 = 0x00c626c3,
		.traffic_method = 0,
		.ndices = 1,
		.character = 3,
		.f20 = 0,
		.f22 = 3,
		.f23 = 2,
		.f24 = 100,
		.init_cash_ratio = 60,
		.f26 = 30,
	},
	{
		.name_ptr = 0x004665e8,
		.f4 = 0x00c5b830,
		.traffic_method = 0,
		.ndices = 1,
		.character = 4,
		.f20 = 1,
		.f22 = 3,
		.f23 = 1,
		.f24 = 50,
		.init_cash_ratio = 40,
		.f26 = 25,
	},
	{
		.name_ptr = 0x004665f1,
		.f4 = 0x00ed9d9d,
		.traffic_method = 0,
		.ndices = 1,
		.character = 5,
		.f20 = 0,
		.f22 = 3,
		.f23 = 1,
		.f24 = 75,
		.init_cash_ratio = 70,
		.f26 = 30,
	},
	{
		.name_ptr = 0x004665fa,
		.f4 = 0x0000f038,
		.traffic_method = 0,
		.ndices = 1,
		.character = 6,
		.f20 = 1,
		.f22 = 3,
		.f23 = 1,
		.f24 = 100,
		.init_cash_ratio = 50,
		.f26 = 20,
	},
	{
		.name_ptr = 0x00466603,
		.f4 = 0x00ffffa0,
		.traffic_method = 0,
		.ndices = 1,
		.character = 7,
		.f20 = 0,
		.f22 = 3,
		.f23 = 0,
		.f24 = 0,
		.init_cash_ratio = 40,
		.f26 = 35,
	},
	{
		.name_ptr = 0x0046660a,
		.f4 = 0x00e77c08,
		.traffic_method = 0,
		.ndices = 1,
		.character = 8,
		.f20 = 0,
		.f22 = 3,
		.f23 = 0,
		.f24 = 0,
		.init_cash_ratio = 60,
		.f26 = 20,
	},
	{
		.name_ptr = 0x00466611,
		.f4 = 0x00cc1a20,
		.traffic_method = 0,
		.ndices = 1,
		.character = 9,
		.f20 = 0,
		.f22 = 3,
		.f23 = 0,
		.f24 = 50,
		.init_cash_ratio = 50,
		.f26 = 0,
	},
	{
		.name_ptr = 0x0046661a,
		.f4 = 0x002017fe,
		.traffic_method = 0,
		.ndices = 1,
		.character = 10,
		.f20 = 1,
		.f22 = 3,
		.f23 = 1,
		.f24 = 30,
		.init_cash_ratio = 55,
		.f26 = 15,
	},
	{
		.name_ptr = 0x00466623,
		.f4 = 0x000ebdbd,
		.traffic_method = 0,
		.ndices = 1,
		.character = 11,
		.f20 = 0,
		.f22 = 3,
		.f23 = 2,
		.f24 = 80,
		.init_cash_ratio = 80,
		.f26 = 0,
	}
};
