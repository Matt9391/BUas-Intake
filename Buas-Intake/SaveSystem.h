#include <utility>
#include <string>
#include <unordered_map>

#pragma once
namespace Tmpl8 {

	class Player;
	class SaveSystem
	{
	public:
		//load and reset and save game saves
		void loadGameSaves(std::unordered_map<long long, bool>& achievements);
		void resetGameSaves(std::unordered_map<long long, bool>& achievements);
		void saveGame(Player& player, std::unordered_map<long long, bool>& achievements);
		//get saved data from game saves
		double getDataSave(const std::string& key);
		std::unordered_map<std::string, double> getGameSaves();
	private:
		//get map from string
		std::pair<std::string, std::string> getMap(const std::string& str);

		//game saves dictionary
		std::unordered_map<std::string, double> gameSaves;

	};


}

