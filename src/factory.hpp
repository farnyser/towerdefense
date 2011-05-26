#ifndef LO21_FACTORY_HPP
#define LO21_FACTORY_HPP

#include "tower.hpp"
#include "enemy.hpp"
#include "missile.hpp"

class Factory
{
private:
	Factory();
public:
	static Enemy* getEnemy(Enemy::Type type, lo21 *game, int size)
	{
		switch (type)
		{
			case Enemy::ANT:
				return new Ant(game, size);
			case Enemy::BUG:
				return new Bug(game, size);
			case Enemy::WASP:
				return new Wasp(game, size);
			case Enemy::MOSQUITO:
				return new Mosquito(game, size);
		}
		
		return NULL;
	}
	 
	static Tower* getTower(Tower::Type type, lo21 *game)
	{
		switch (type)
		{
			case Tower::SLINGSHOT:
				return new Slingshot(game);
			case Tower::PETANQUEPLAYER:
				return new PetanquePlayer(game);
			case Tower::WATERGUN:
				return new WaterGun(game);
			case Tower::PAINTBALL:
				return new PaintBall(game);
		}

		return NULL;
	}

	static Missile* getMissile(const Tower * const tw, const Enemy * const target, lo21 *game)
	{
		Tower::Attribute attr = tw->getAttribute();
		QPointF pos = tw->scenePos() + tw->getCenterPos();

		switch (attr.type)
		{
			default:
				return new AngryBird(game, pos, attr.bulletSpeed, attr.power, target);
		}

		return NULL;
	}
};

#endif /* end of include guard: LO21_FACTORY_HPP */
