#pragma once

#include <SFML\Graphics.hpp>

class Fighter;
class Controls;

class Player {
public:
	//Player(int playerNum, Fighter* fighter1, Fighter* fighter2);
	Player(int playerNum, std::string fighter1, std::string fighter2);
	~Player();

	void UpdateEvent(sf::Event event);
	//void Update(Fighter* enemy);
	void CheckInput();
	void CheckEnemyCollision(Fighter* enemy);
	void CheckBoundaryCollision();
	void Update(Fighter* enemy);
	//void Draw(sf::RenderWindow* window);
	void DrawMain(sf::RenderWindow* window);
	void DrawSupport(sf::RenderWindow* window);
	void SetColors(int mainColor, int supportColor);

	bool CheckFightersHealth();
	float GetTotalRemainingHealth();
	void SetDrawOrder(bool onTopLayer);
	bool GetDrawFirst();
	void FightIsOver(int winnerNumber);

	Controls* GetControls();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f newPosition);
	void SetReadyIntro(bool readyIntro);
	Fighter* GetMain();
	Fighter* GetSupport();

	int GetCurrentCombo();
	void ResetCombo();

	int GetPlayerNumber();
	void SetMainEnemy(Fighter* mainEnemy);
	void SummonSupport(sf::Vector2f mainPosition, int mainXScale);
	void DoCrossAssault(sf::Vector2f mainPosition, int mainXScale);
	void SnapBackSwap();
	void HyperSwap();
	void StartDeathSwap();
	void DeathSwap();

	bool canHyperSwap = true;

private:
	Controls* playerControls;
	int playerNumber;
	Fighter* main;
	Fighter* support;

	int timeUntilDeathSwap;
	bool drawFirst = false;
};