#include "FishScene.h"
#include "Camera2D.h"
#include "Player.h"
#include "InteractableObject.h"

namespace Tmpl8 {

	void FishScene::onEnter() {

	}

	void FishScene::onExit() {}

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
	}

	void FishScene::draw(Surface* screen, Camera2D& camera, Player& player) {
		screen->Clear(0);

		for (int i = 0; i < MapHandler::tiles2D.y; i++) {
			for (int j = 0; j < MapHandler::tiles2D.x; j++) {
				for (int iMap = 0; iMap < MapHandler::maps2D.size() - 1; iMap++) {
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

		//for (auto object : MapHandler::objects) {
		//	(*object).draw(screen, camera.getPos());

		//	if ((*object).intersectPlayer(player)) {
		//		(*object).showText(screen, camera.getPos());
		//	}
		//}

		player.draw(screen, camera.getPos());
	}

}