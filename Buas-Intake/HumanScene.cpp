#include "HumanScene.h"
#include "Camera2D.h"
#include "Player.h"
#include "InteractableObject.h"
#include "resources.h"

namespace Tmpl8 {

	void HumanScene::onEnter(Player& player, Camera2D& camera) {
		MapHandler::loadInteractableObject("tdwInteractableObjectList.txt", 32, &fishingAreaSprites);
		camera.setWorldSize(MapHandler::tilesTdw);

		player.setPos(vec2(MapHandler::tileSize * 15,MapHandler::tileSize * 5));
		player.setState(int(PlayerVisual::Human));
		player.loadCollisionMaps(&MapHandler::mapsTdw);
	}

	void HumanScene::onExit() {
		MapHandler::objects.clear();
	}

	void HumanScene::update(float dt, Camera2D& camera, Player& player) {

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
	}

	void HumanScene::draw(Surface* screen, Camera2D& camera, Player& player) {
		screen->Clear(0);

		for (int i = 0; i < MapHandler::tilesTdw.y; i++) {
			for (int j = 0; j < MapHandler::tilesTdw.x; j++) {
				for (int iMap = 0; iMap < MapHandler::mapsTdw.size(); iMap++) {
					int tx = MapHandler::mapsTdw[iMap][i][j * 4] - 'a';
					int ty = MapHandler::mapsTdw[iMap][i][j * 4 + 1] - 'a';
					//printf("%c e %c\n", tx + 'a', ty + 'a');
					int x = j * MapHandler::tileSize - int(camera.getPos().x);
					int y = i * MapHandler::tileSize - int(camera.getPos().y);
					//printf("%d e %d\n", x, y);

					MapHandler::drawTile(tx, ty, screen, &MapHandler::mapTdwTileset, x, y, 32);
				}

			}

		}

		for (auto object : MapHandler::objects) {
			(*object).drawHitBox(screen, camera.getPos());
		}

		for (auto object : MapHandler::objects) {
			(*object).draw(screen, camera.getPos());

			if ((*object).intersectPlayer(player)) {
				//printf("TIPO: %d\n", (*object).type);
				(*object).showText(screen, camera.getPos());
			}
		}

		player.draw(screen, camera.getPos());
	}

}