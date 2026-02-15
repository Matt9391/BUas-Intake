#include "SaveSystem.h"
#include "../Gameplay/Player.h"
#include "../DataTypes/Fish.h"
#include "../InteractableObjects/IncomeMultiplier.h"
#include "../InteractableObjects/StaminaShop.h"
#include <iostream>
#include <fstream>

namespace Tmpl8 {
	std::unordered_map<std::string, double> SaveSystem::getGameSaves() {
		return this->gameSaves;
	}

	void SaveSystem::saveGame(Player& player, std::unordered_map<long long, bool>& achievements) {
		//update game data into game saves dictionary
		gameSaves["coins"] = double(player.getCoins());

		//clean fish counts
		gameSaves["fish_common"] = 0;
		gameSaves["fish_rare"] = 0;
		gameSaves["fish_epic"] = 0;
		gameSaves["fish_legendary"] = 0;

		//set fish counts
		for (auto& fish : player.getFishes()) {
			if (fish.rarity == FishRarity::COMMON)
				gameSaves["fish_common"] += 1;
			if (fish.rarity == FishRarity::RARE)
				gameSaves["fish_rare"] += 1;
			if (fish.rarity == FishRarity::EPIC)
				gameSaves["fish_epic"] += 1;
			if (fish.rarity == FishRarity::LEGENDARY)
				gameSaves["fish_legendary"] += 1;
		}

		//clean chest counts
		gameSaves["chest0"] = 0;
		gameSaves["chest1"] = 0;
		gameSaves["chest2"] = 0;
		gameSaves["chest3"] = 0;

		//set chest counts
		for (auto& chest : player.getChests()) {
			if (chest.type == 0)
				gameSaves["chest0"] += 1;
			if (chest.type == 1)
				gameSaves["chest1"] += 1;
			if (chest.type == 2)
				gameSaves["chest2"] += 1;
			if (chest.type == 3)
				gameSaves["chest3"] += 1;
		}

		gameSaves["incomeMultiplier"] = player.getMultiplier();
		gameSaves["incomeMultiplierPrice"] = IncomeMultiplier::getPrice();
		gameSaves["stamina"] = player.getStamina();
		gameSaves["staminaPrice"] = StaminaShop::getPrice();

		//check last achievement achieved
		long long coinsAchieved = 0;
		for (auto& pair : achievements) {
			if (pair.second)
				coinsAchieved = pair.first;
		}

		gameSaves["lastAchievement"] = double(coinsAchieved);

		//write game saves to file
		std::ofstream outFile("./assets/gameSaves/gameSave.txt");

		for (auto& pair : gameSaves) {
			outFile << pair.first << ":" << pair.second << "\n";
		}


		outFile.close();
	}

	double SaveSystem::getDataSave(const std::string& key) {
		return gameSaves[key];
	}

	void SaveSystem::resetGameSaves(std::unordered_map<long long, bool>& achievements) {
		//load default game saves from file
		std::ifstream objFile("./assets/gameSaves/defaultGameSave.txt");
		std::string line;
		std::unordered_map<std::string, double> defaultGameSaves;
		//coins
		//fish common - rare - epic - legendary -> chest 0-1-2-3 -> stamina
		//income multiplier price - income multiplier - stamina price
		while (std::getline(objFile, line)) {
			std::pair<std::string, std::string> data = getMap(line);
			defaultGameSaves[data.first] = std::stod(data.second);
		}

		objFile.close();

		//overwrite current game saves with default ones
		this->gameSaves = defaultGameSaves;

		//reset achievements
		for (auto& pair : achievements) {
			pair.second = false;
		}
	}

	void SaveSystem::loadGameSaves(std::unordered_map<long long, bool>& achievements) {
		std::ifstream objFile("./assets/gameSaves/gameSave.txt");
		std::string line;

		//coins
		//fish common - rare - epic - legendary -> chest 0-1-2-3 -> stamina
		//income multiplier price - income multiplier - stamina price

		//load game saves from reading file
		while (std::getline(objFile, line)) {
			std::pair<std::string, std::string> data = getMap(line);
			gameSaves[data.first] = std::stod(data.second);
		}

		//set achievements based on last achievement saved
		for (auto& pair : achievements) {
			if (gameSaves["lastAchievement"] >= pair.first) {
				pair.second = true;
			}
		}

		objFile.close();

	}

	//key:value dictionary parser
	std::pair<std::string, std::string> SaveSystem::getMap(const std::string& str) {
		std::string key = "";
		bool keyDone = false;
		std::string value = "";

		//split string into key and value based on ':'
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != ':' && !keyDone) {
				key += str[i];
			}
			else if (str[i] == ':') {
				keyDone = true;
			}
			else if (keyDone) {
				value += str[i];
			}

		}

		return { key,value };
	}
}