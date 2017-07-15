#pragma once

#include <SFML\Graphics.hpp>

#include "AnimationManager.h"
#include "CommandList.h"
#include "Projectile.h"
#include "FighterStrings.h"
#include "AnimationStrings.h"

class Controls;
class Player;

using namespace std;

using AdditionalEffect = DamageInfo::AdditionalEffect;
using DamageScale = DamageInfo::DamageScale;
using HitSparkType = DamageInfo::HitSparkType;

class Fighter {
public:
	Fighter();
	~Fighter();

	void SetPlayer(Player* p);

	virtual void Load();
	virtual void SetColor(int colorNum);
	virtual void CheckInput(Controls* playerControls);
	virtual void CheckEnemyCollision(Fighter* enemy);
	virtual void CheckBoundaryCollision();
	virtual void Update(Fighter* enemy);
	//virtual void SupportUpdate(Fighter* enemy);
	virtual void Draw(sf::RenderWindow* window);
	virtual bool TakeDamage(DamageInfo dInfo, sf::Vector2f pointOfCollision, int comboCount, Fighter* enemy = nullptr);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f newPosition);
	void SetSoloFighter();

	sf::Vector2f GetVelocity();
	void SetNewVelocityX(float x);
	void SetNewVelocityY(float y);
	void SetReadyIntro(bool rIntro);

	AnimationManager GetAnimationManager();

	void PushAway(float xKnockback);
	void IncrementCombo();
	void AddSpecialMeter(int additionalMeter);
	void SetCanCombo(bool value);
	void FightIsOver(bool result);

	void SetNextAnimToPlay(std::string nextAnim);

	virtual void SummonSupport(sf::Vector2f mainPosition, int mainXScale);
	virtual void CrossAssault(sf::Vector2f mainPosition, int mainXScale);
	virtual void HyperSwap(sf::Vector2f mainPosition, int mainXScale);
	void SetSupport(bool value);
	bool GetIsSupport();
	virtual void DoSupportEnter();
	virtual void DoSupportExit();
	virtual bool CheckOffScreen();
	bool GetIsPlayable();
	bool GetKOed();
	bool CheckForHyperInput(std::string inputBuffer, int specialMeter);

	virtual bool CallEnumFunction(int functionEnum);

	void ResetToIdle();
	void Crouch();
	void StopXMovement();
	void StopYMovement();
	void ResetCombo();
	void SetCustomGravity(float newGrav);

	float GetPercentHealth();
	float GetPercentRedHealth();
	float GetPercentOneSpecialbar();
	int GetNumberOfSpecialBars();
	int GetCombo();
	std::vector<Projectile*>* GetSpawnedProjectiles();

	void BeThrown(std::string throwName, int newXScale);
	void ReceiveThrowDamage(DamageInfo dInfo);

	void SetMainEnemy(Fighter* mainEnemy);

	sf::Sprite* getBattlePortrait();
	sf::Sprite* getSupportPortrait();

	sf::Color color;
	bool isAssisting = false;
	bool inAir = false;
	bool isSupport = false;
	bool supportDone = true;
	bool onScreen = false;
	int xScale = 1;
	bool doingHyperAttack = false;
	bool doingHyperSwap = false;
	bool isAttacking = false;
	bool disableGrav = false;
	bool disablePhysics = false;
	bool pauseHeld = true;

	int healthMeter;
	bool isPlayable;
	int redMeter = 0;
	int specialMeter = 0;

protected:
	enum MoveTeirs { None, Light, Medium, Heavy, Command, Special, Hyper, Launch, Throw };

	enum FrameFunctions 
	{
		reset_to_idle, stop_x_movement, stop_y_movement, crouch, do_attack, do_jump, do_forward_jump, do_back_jump, do_back_roll, do_super_jump, check_super_jump, do_forward_dash, do_back_dash, do_aerial_recovery, disable_gravity,
		reset_hit, do_hyper_attack, do_snap_back, do_support_enter, do_support_exit, do_forward_throw, do_back_throw, do_throw_damage, check_for_snap_back_swap,
		start_end_countdown, intro_done,
		last, // Reserved for the "inherited" enums
	};
	const int SUPPORT_FRAMES_OF_ENTRY = 20;

	virtual void CheckMovementInput(Controls* playerControls);
	void CheckDirectionalInput(Controls* playerControls);
	virtual void CheckActionInput(Controls* playerControls);
	void CheckCommandLists(Controls* playerControls);
	void UpdatePosition();
	bool CheckStageBounds();
	bool CheckCameraBounds();
	void CheckFighterCollision(Fighter* enemy);
	void CheckBoundBoxCollision(Fighter* enemy);
	void CheckHitBoxCollision(Fighter* enemy);
	sf::Vector2f CheckNextPosition();
	virtual void UpdateAnimations();
	virtual void UpdateInAir();
	void UpdateScale(int xPosition);
	void UpdateProjectiles();
	void UpdateCenter();
	void DrawProjectiles(sf::RenderWindow* window);
	virtual void DrawBoxes(sf::RenderWindow* window);

	void InsertIntoInputBuffer(char input);

	void DoAttack();
	void DoHyperAttack();
	void DoJump();
	void DoSuperJump();
	void CheckSuperJump();
	void DoAerialRecovery();
	void DisableGravity();
	void DoForwardDash();
	void DoBackRoll();
	void DoBackDash();
	void ResetHit();
	void CheckForSnapBackSpawn();
	void StartEndCountdown();
	void IntroDone();

	virtual void DoForwardThrow();
	virtual void DoBackThrow();
	virtual void DoThrowDamage();

	bool CheckThrowRange();

	virtual void CheckOnHit();

	int maxHealth;
	float maxSpeed;
	int jumpDirection = 0;
	bool isSuperJumping = false;
	bool isCrouching = false;
	bool isDashing = false;
	bool disableActionUntilGrounded = false;
	bool isBlocking = false;
	bool isHurt = false;
	bool justLanded = false;
	bool collidedWithEdges = false;
	bool canCombo = false;
	bool inSoftKnockdown = false;
	int quickRiseFrames = 0;
	bool inHardKnockdown = false;
	bool inScreenFly = false;
	int lastAttack = None;
	std::string nextActionAnim = "";
	string nextAnimToPlay = "";
	std::string name;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f currentCenter;
	sf::Vector2f center;
	//int xScale;
	AnimationManager animManager;

	CommandList basicCommands;
	CommandList airBasicCommands;
	CommandList commandNormals;
	CommandList specialCommands;
	CommandList airSpecialCommands;
	CommandList hyperCommands;
	CommandList airHyperCommands;

	bool forwardHeld = false;
	bool backHeld = false;
	bool downHeld = false;
	bool upHeld = false;
	bool lightHeld = false;
	bool mediumHeld = false;
	bool heavyHeld = false;
	bool specialHeld = false;
	bool supportHeld = false;
	int supportHeldForFrames = 0;
	const int FRAMES_TO_HOLD_FOR_SWAP = 60;

	bool commandFound = false;
	bool fourDirection = false;
	bool oneDirection = false;
	bool twoDirection = false;
	bool threeDirection = false;
	bool sixDirection = false;
	bool eightDirection = false;

	bool lightAttack = false;
	bool mediumAttack = false;
	bool heavyAttack = false;
	//bool hasHit = false;
	bool hasHitMain = false;
	bool hasHitSupport = false;
	bool hasBeenHardKnockdowned = false;

	//std::vector<int> inputBuffer;
	std::string inputBuffer = "";
	int inputBufferTimer = 0;

	std::vector<Projectile*> spawnedProjectiles;

	int comboNumber = 0;
	bool enableHorizontalDampening = false;

	const float GRAVITY_CONST = 0.5f;
	float GRAVITY = GRAVITY_CONST;
	const int ONE_SPECIAL_BAR = 10000;
	const int THREE_SPECIAL_BARS = 30000;

	Player* player;

	//bool isSupport = false;
	float supportEndPositionX;
	//bool isAssisting = false;
	int supportCooldown = 0;

	Fighter* enemyMain;

	bool beingThrown = false;
	bool winner = false;
	bool fightFinished = false;

	sf::Shader colorShader;

	sf::Texture battlePortraitTexture;
	sf::Sprite battlePortraitSprite;
	sf::Texture supportPortraitTexture;
	sf::Sprite supportPortraitSprite;

	sf::Texture commandListTexture;

	int assistCooldownMultiplyer = 1;

	bool hunterStyle = false;
	bool hiLoSwap = false;

	int lastBaseDamage = 0;
	int lastModifiedDamage = 0;
	int lastComboDamage = 0;
	int maxComboDamage = 0;
	bool resetComboDamage = true;

private:
	void Defeated();
	int CalculateDamage(DamageInfo dInfo, int comboCount);

	sf::Texture hurtBoxTexture;
	sf::Texture hitBoxTexture;
	sf::Texture boundBoxTexture;

	const float TERMINAL_VELOCITY = 10.f;

	const int	INPUT_BUFFER_FLUSH_INTERVAL = 15; // Number of frames before the buffer is flushed
	const int	INPUT_BUFFER_MAX_LENGTH = 11;
	const int	SUPPORT_COOLDOWN_FRAMES = 60;

	int hitStopFrames = 0;
	int frameCount = 0;
	static int playerNumber;
	int number;
	bool readyIntro = true;
	bool KOed = false;

	float newXVelocity = -555.f;
};