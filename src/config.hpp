#ifndef LO21_CONFIG_HPP
#define LO21_CONFIG_HPP

const int 	MAP_SIZE=16,
			TILE_SIZE=30,
			TIME_BETWEEN_WAVES=4,
			FREQUENCY=50;

namespace TOWER
{
	enum Type
	{
		WATERGUN,
		SLINGSHOT,
		PAINTBALL,
		PETANQUEPLAYER,
		NONE
	};
}


namespace ENEMY
{
	enum Type
	{
		ANT,
		BUG,
		WASP,
		MOSQUITO
	};
}


#endif // LO21_CONFIG_HPP
