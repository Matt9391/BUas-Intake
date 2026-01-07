#include "FishScene.h"
#include "Camera2D.h"
#include "Player.h"
#include "InteractableObject.h"
#include "resources.h"
#include "Randomize.h"
#include "Enemy.h"


namespace Tmpl8 {

	void FishScene::onEnter(Player& player, Camera2D& camera) {
		MapHandler::loadInteractableObject("2DInteractableObjectList.txt", 32);	
		
		int type = 6; //chest type

		for (int i = 0; i < 10; i++) {
			vec2 pos(
				Randomize::randomInt(3 * MapHandler::tileSize, 22 * MapHandler::tileSize),
				Randomize::randomInt(5 * MapHandler::tileSize, 33 * MapHandler::tileSize)
			);
			//vec2 pos(
			//	Randomize::randomInt(1 * MapHandler::tileSize, 24 * MapHandler::tileSize),
			//	Randomize::randomInt(1 * MapHandler::tileSize, 35 * MapHandler::tileSize)
			//	);
			vec2 size(46);

			MapHandler::createInteractableObject(type, pos, size, nullptr, &chestsSprite);

		}

		for (int i = 0; i < 10; i++) {
			vec2 pos(
				-5 * MapHandler::tileSize,
				Randomize::randomInt(5 * MapHandler::tileSize, 33 * MapHandler::tileSize)
			);

			vec2 size(128,46);
			vec2 endPos(
				26 * MapHandler::tileSize,
				Randomize::randomInt(pos.y - 5 * MapHandler::tileSize, pos.y + 5 * MapHandler::tileSize)
			);

			if (endPos.y >= 35 * MapHandler::tileSize) endPos.y = 34 * MapHandler::tileSize;
			if (endPos.y < 5 * MapHandler::tileSize) endPos.y = 5 * MapHandler::tileSize;

			float startOffset = Randomize::randomFloat(100, 1000);

			enemies.push_back(new Enemy(pos, size, endPos, startOffset, enemySprite));

		}

		
		camera.setWorldSize(MapHandler::tiles2D);
		
		player.setState(int(PlayerVisual::Fish));
		player.loadCollisionMaps(&MapHandler::maps2D);
		player.setPos({ 32,32 });
	}

	void FishScene::onExit() {
		MapHandler::objects.clear();
	}

	void FishScene::update(float dt, Camera2D& camera, Player& player) {

		player.update(dt);

		camera.follow(player.getPos());

		for (auto object : MapHandler::objects) {
			(*object).update(dt, player);

			if ((*object).intersectPlayer(player)) {
				if (player.isInteracting()) {
					(*object).interact(player);
				}

			}
		}

		for (auto e : enemies) {
			(*e).update(dt, player);

			if ((*e).intersectPlayer(player)) {
				(*e).attack(player);
			}
		}
	}

	void FishScene::draw(Surface* screen, Camera2D& camera, Player& player) {
		screen->Clear(0);

		for (int i = 0; i < MapHandler::tiles2D.y; i++) {
			for (int j = 0; j < MapHandler::tiles2D.x; j++) {
				for (int iMap = 0; iMap < MapHandler::maps2D.size(); iMap++) {
					int tx = MapHandler::maps2D[iMap][i][j * 4] - 'a';
					int ty = MapHandler::maps2D[iMap][i][j * 4 + 1] - 'a';
					//printf("%c e %c\n", tx + 'a', ty + 'a');
					int x = j * MapHandler::tileSize - int(camera.getPos().x);
					int y = i * MapHandler::tileSize - int(camera.getPos().y);
					//printf("%d e %d\n", x, y);

					MapHandler::drawTile(tx, ty, screen, &MapHandler::map2DTileset, x, y, 32);
				}

			}

		}

		//for (auto object : MapHandler::objects) {
		//	(*object).drawHitBox(screen, camera.getPos());
		//}
		//for (auto e : enemies) {
		//	(*e).drawHitBox(screen, camera.getPos());
		//}

		for (auto object : MapHandler::objects) {
			(*object).draw(screen, camera.getPos());

			if ((*object).intersectPlayer(player)) {
				(*object).showText(screen, camera.getPos());
			}
		}

		for (auto e : enemies) {
			(*e).draw(screen, camera.getPos());
		}

		player.draw(screen, camera.getPos());
	}

}