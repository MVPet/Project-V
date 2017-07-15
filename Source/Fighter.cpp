#include "Fighter.h"
#include "Controls.h"
#include "Fight.h"
#include "Player.h"
#include "GameManager.h"
#include "ApplicationData.h"

#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace sf;

int Fighter::playerNumber = 0;

/************************
PUBLIC FUNCTIONS
************************/
Fighter::Fighter() {
	number = ++playerNumber;
}

Fighter::~Fighter() {
}

void Fighter::CheckInput(Controls* playerControls) {
	if (KOed || fightFinished)
		return;

	CheckDirectionalInput(playerControls);
	CheckActionInput(playerControls);
	CheckCommandLists(playerControls);

	if ("" == nextActionAnim)
		CheckMovementInput(playerControls);
	else {
		nextAnimToPlay = nextActionAnim;
		nextActionAnim = "";
		hitStopFrames = 0;
	}
}

void Fighter::CheckEnemyCollision(Fighter* enemy) {
	if (0 < hitStopFrames)
		return;

	if (!KOed && !enemy->KOed) CheckFighterCollision(enemy);
}

void Fighter::CheckBoundaryCollision() {
	if (0 < hitStopFrames)
		return;

	collidedWithEdges = (CheckStageBounds() || CheckCameraBounds());
}

void Fighter::Update(Fighter* enemy) {
	/*
	if (0 < quickRiseFrames) {
		std::cout << "QUICK RISE WINDOW OPEN" << std::endl;
		quickRiseFrames--;
	}
	*/
	if (!KOed) {
		onScreen = CheckOffScreen();

		if (isSupport && redMeter > healthMeter)
			healthMeter += 50;
	}

	if (0 < hitStopFrames)
		hitStopFrames--;

	if (0 < hitStopFrames) {
		return;
	}

	if (inAir)
		UpdateInAir();

	UpdatePosition();

	if (!KOed && !isSupport && !isAttacking && !inAir && !isBlocking && !beingThrown && ON_GROUND != animManager.GetCurrentAnimationName())
		UpdateScale(enemy->GetPosition().x);

	if (!KOed || (KOed && ON_GROUND != animManager.GetCurrentAnimationName())) {
		if ((!fightFinished || (fightFinished && justLanded)) && (justLanded || (animManager.IsCurrentAnimationDone() && (!inHardKnockdown && !inSoftKnockdown)))) {
			inputBuffer = ""; // Clear the input buffer
			justLanded = false;

			nextAnimToPlay = (inSoftKnockdown) ? BACK_ROLL : (inHardKnockdown) ? ON_GROUND : (inAir) ? FALLING : (isCrouching) ? CROUCH : (isSupport) ? SUPPORT_IDLE : IDLE;

			inHardKnockdown = false;
			inSoftKnockdown = false;
			if (ON_GROUND == animManager.GetCurrentAnimationName()) {
				nextAnimToPlay = GETUP;
			}

			if (isSupport) {
				if (disableGrav) {
					nextAnimToPlay = SUPPORT;
					disableGrav = false;
				}
				else if (!inAir || inSoftKnockdown || inHardKnockdown) {
					nextAnimToPlay = SUPPORT_END;
				}
			}

			if (CROSS_ASSAULT == animManager.GetCurrentAnimationName()) {
				isAssisting = false;
				isSupport = false;
				disableGrav = false;
				Fight::cameraLock = false;
				nextAnimToPlay = CROSS_ASSAULT_LANDING;
			}

			if (doingHyperSwap) {
				isAssisting = false;
				doingHyperSwap = false;
				Fight::p1HyperSwap = false;
				Fight::p2HyperSwap = false;
				Fight::cameraLock = false;
				nextAnimToPlay = hyperCommands.GetFoundCommand();
				specialMeter -= hyperCommands.GetFoundCommandMeterUsage();
			}

			if (KOed)
				player->StartDeathSwap();

			if (!KOed && ON_GROUND == animManager.GetCurrentAnimationName())
				nextAnimToPlay = GETUP;

		}

		if (!KOed && fightFinished && IDLE == animManager.GetCurrentAnimationName()) {
			nextAnimToPlay = (winner) ? WIN : LOSE;
		}
	}

	UpdateAnimations();

	UpdateCenter();

	UpdateProjectiles();

	if (++inputBufferTimer >= INPUT_BUFFER_FLUSH_INTERVAL)
		inputBuffer = "";
	frameCount++;
	supportCooldown--;
}

void Fighter::Draw(sf::RenderWindow* window) {
	//animManager.Draw(window, color);
	animManager.Draw(window, colorShader);
	//DrawBoxes(window);
	DrawProjectiles(window);
}

Vector2f Fighter::GetPosition() {
	return position;
}

void Fighter::SetPosition(sf::Vector2f newPosition) {
	position = newPosition;
	animManager.ReUpdateAnimationBoxes(position, xScale);
}

// Will be used by inherited classes for scripting functions 
// called by Animation for frame specific functions
bool Fighter::CallEnumFunction(int enumFunction) {
	switch (enumFunction) {
	case reset_to_idle:
		ResetToIdle();
		return true;
	case stop_x_movement:
		StopXMovement();
		return true;
	case stop_y_movement:
		StopYMovement();
		return true;
	case do_attack:
		DoAttack();
		return true;
	case do_hyper_attack:
		DoHyperAttack();
		return true;
	case do_jump:
		DoJump();
		return true;
	case do_super_jump:
		DoSuperJump();
		return true;
	case do_aerial_recovery:
		DoAerialRecovery();
		return true;
	case disable_gravity:
		DisableGravity();
		return true;
	case check_super_jump:
		CheckSuperJump();
		return true;
	case do_forward_dash:
		DoForwardDash();
		return true;
	case do_back_dash:
		DoBackDash();
		return true;
	case do_back_roll:
		DoBackRoll();
		return true;
	case reset_hit:
		ResetHit();
		return true;
	case do_support_enter:
		DoSupportEnter();
		return true;
	case do_support_exit:
		DoSupportExit();
		return true;
	case do_forward_throw:
		DoForwardThrow();
		return true;
	case do_back_throw:
		DoBackThrow();
		return true;
	case do_throw_damage:
		DoThrowDamage();
		return true;
	case check_for_snap_back_swap:
		CheckForSnapBackSpawn();
		return true;
	case start_end_countdown:
		StartEndCountdown();
		return true;
	case intro_done:
		IntroDone();
		return true;
	default:
		return false;
	}
}

/************************
PRIVATE FUNCTION
************************/
void Fighter::CheckMovementInput(Controls* playerControls) {

	float xAxis = playerControls->GetHorizontalAxis();
	float yAxis = playerControls->GetVerticalAxis();

	// FIX IT SO BACK IS LEFT ON 1 XSCALE AND RIGHT ON -1 SCALE

	if (-1 == xAxis)
		backHeld = true;
	else
		backHeld = false;

	if (1 == xAxis)
		forwardHeld = true;
	else
		forwardHeld = false;

	if (1 == yAxis)
		downHeld = true;
	else
		downHeld = false;

	if (-1 == yAxis)
		upHeld = true;
	else
		upHeld = false;

	if (isAttacking || isDashing || isHurt || isBlocking || beingThrown || (inAir && !isSuperJumping))
		return;

	if (!isCrouching) {
		if (backHeld)
			velocity.x = -maxSpeed;
		else if (forwardHeld)
			velocity.x = maxSpeed;

		if (!inAir) {
			if (forwardHeld)
				nextAnimToPlay = (1 == xScale) ? FORWARD_WALK : BACK_WALK;
			else if (backHeld)
				nextAnimToPlay = (1 == xScale) ? BACK_WALK : FORWARD_WALK;
			else
				nextAnimToPlay = IDLE;
		}
	}

	if (downHeld && !inAir) {
		isCrouching = true;
		nextAnimToPlay = CROUCH;
	}
	else
		isCrouching = false;
}

void Fighter::CheckActionInput(Controls* playerControls) {

	if (isHurt || isBlocking || beingThrown)
		return;

	if (!readyIntro) {
		if (playerControls->isActionPressed(Controls::Actions::Light)) {
			if (!lightHeld) {
				InsertIntoInputBuffer('l');
				/*if (0 < quickRiseFrames) {
					nextAnimToPlay = GETUP;
					velocity.x = 0.f;
				}*/
				//if ((!isAttacking && !disableActionUntilGrounded) || (canCombo && lastAttack < Light)) {
				if ((!isAttacking && !disableActionUntilGrounded)) {
					if (inAir)
						nextActionAnim = J_L;
					else if (downHeld)
						nextActionAnim = C_L;
					else
						nextActionAnim = L;

					lastAttack = Light;
					lightAttack = true;
					mediumAttack = false;
					heavyAttack = false;
					hiLoSwap = false;
				}
				else if (canCombo && hunterStyle && !hiLoSwap) {
					if (downHeld) {
						if (L == animManager.GetCurrentAnimationName()) {
							nextActionAnim = C_L;
							hiLoSwap = true;

							lastAttack = Light;
							lightAttack = true;
							mediumAttack = false;
							heavyAttack = false;
						}
					}
					else {
						if (C_L == animManager.GetCurrentAnimationName()) {
							nextActionAnim = L;
							hiLoSwap = true;

							lastAttack = Light;
							lightAttack = true;
							mediumAttack = false;
							heavyAttack = false;
						}
					}
				}
			}
			lightAttack = true;
			mediumAttack = false;
			heavyAttack = false;
			lightHeld = true;
		}
		else
			lightHeld = false;

		if (playerControls->isActionPressed(Controls::Actions::Medium)) {
			if (!mediumHeld) {
				InsertIntoInputBuffer('m');
				/*if (0 < quickRiseFrames) {
					nextAnimToPlay = GETUP;
					velocity.x = 0.f;
				}*/
				if ((!isAttacking && !disableActionUntilGrounded) || (canCombo && lastAttack < Medium)) {
					if (inAir)
						nextActionAnim = J_M;
					else if (downHeld)
						nextActionAnim = C_M;
					else
						nextActionAnim = M;

					lastAttack = Medium;
					mediumAttack = true;
					lightAttack = false;
					heavyAttack = false;
					hiLoSwap = false;
				}
				else if (canCombo && hunterStyle && Medium == lastAttack && !hiLoSwap) {
					if (downHeld) {
						if (M == animManager.GetCurrentAnimationName()) {
							nextActionAnim = C_M;
							hiLoSwap = true;

							lastAttack = Medium;
							mediumAttack = true;
							lightAttack = false;
							heavyAttack = false;
						}
					}
					else {
						if (C_M == animManager.GetCurrentAnimationName()) {
							nextActionAnim = M;
							hiLoSwap = true;

							lastAttack = Medium;
							mediumAttack = true;
							lightAttack = false;
							heavyAttack = false;
						}
					}
				}
			}
			mediumAttack = true;
			lightAttack = false;
			heavyAttack = false;
			mediumHeld = true;
		}
		else
			mediumHeld = false;

		if (playerControls->isActionPressed(Controls::Actions::Heavy)) {
			if (!heavyHeld) {
				InsertIntoInputBuffer('h');
				/*if (0 < quickRiseFrames) {
					nextAnimToPlay = GETUP;
					velocity.x = 0.f;
				}*/
				if ((!isAttacking && !disableActionUntilGrounded) || (canCombo && lastAttack < Heavy)) {

					if ((forwardHeld || backHeld) && CheckThrowRange()) {

						if (-1 == xScale) {
							if (backHeld)
								nextActionAnim = FORWARD_THROW;
							else if (forwardHeld)
								nextActionAnim = BACK_THROW;
						}
						else {
							if (forwardHeld)
								nextActionAnim = FORWARD_THROW;
							else if (backHeld)
								nextActionAnim = BACK_THROW;
						}

						commandFound = true;
						lastAttack = Throw;
						heavyAttack = true;
						lightAttack = false;
						mediumAttack = false;
						hiLoSwap = false;
					}
					else {
						if (inAir)
							nextActionAnim = J_H;
						else if (downHeld)
							nextActionAnim = C_H;
						else
							nextActionAnim = H;

						lastAttack = Heavy;
						heavyAttack = true;
						lightAttack = false;
						mediumAttack = false;
						hiLoSwap = false;
					}
				}
				else if (canCombo && hunterStyle && Heavy == lastAttack && !hiLoSwap) {
					if (downHeld) {
						if (H == animManager.GetCurrentAnimationName()) {
							nextActionAnim = C_H;
							hiLoSwap = true;

							lastAttack = Heavy;
							heavyAttack = true;
							lightAttack = false;
							mediumAttack = false;
						}
					}
					else {
						if (C_H == animManager.GetCurrentAnimationName()) {
							nextActionAnim = H;
							hiLoSwap = true;

							lastAttack = Heavy;
							heavyAttack = true;
							lightAttack = false;
							mediumAttack = false;
						}
					}
				}
			}
			heavyAttack = true;
			lightAttack = false;
			mediumAttack = false;
			heavyHeld = true;
		}
		else
			heavyHeld = false;

		if (playerControls->isActionPressed(Controls::Actions::Special)) {

			if (!specialHeld) {
				if ((!isAttacking && !disableActionUntilGrounded) || (canCombo && lastAttack <= Heavy)) {

					if (inAir)
						nextActionAnim = J_SP;
					else
						nextActionAnim = SP;

					lastAttack = Launch;
					//lightAttack = false;
					//mediumAttack = false;
					//heavyAttack = false;
				}
			}
			specialHeld = true;
		}
		else
			specialHeld = false;

		if (playerControls->isActionPressed(Controls::Actions::Support)) {
			if (!supportHeld) {
				InsertIntoInputBuffer('p');
			}
			supportHeld = true;
		}
		else
			supportHeld = false;

		// CHECKING FOR SWAPPING RELATED THINGS
		if (supportHeld) {
			supportHeldForFrames++;
			if ((!inAir && !isAttacking && !isBlocking && !isHurt) && FRAMES_TO_HOLD_FOR_SWAP < supportHeldForFrames) {
				player->DoCrossAssault(currentCenter, xScale);
				supportHeldForFrames = 0;
			}
		}
		else {
			if ((!inAir && !isAttacking && !isBlocking && !isHurt) && !isSupport && 0 < supportHeldForFrames && FRAMES_TO_HOLD_FOR_SWAP > supportHeldForFrames) {
				player->SummonSupport(currentCenter, xScale);
			}
			supportHeldForFrames = 0;
		}
	}

	/////////// MIGHT MOVE THIS TO MOVEMENT INPUT INSTEAD OF ACTION INPUT ///////////////////////////
	if (!isAttacking && !inAir && (playerControls->isActionPressed(Controls::Actions::Jump) || upHeld)) { // THIS'LL DO FOR NOW
		if (forwardHeld) {
			if (1 == xScale) {
				nextActionAnim = FORWARD_JUMP;
				jumpDirection = 1;
			}
			else if (-1 == xScale) {
				nextActionAnim = BACK_JUMP;
				jumpDirection = 1;
			}
		}
		else if (backHeld) {
			if (1 == xScale) {
				nextActionAnim = BACK_JUMP;
				jumpDirection = -1;
			}
			else if (-1 == xScale) {
				nextActionAnim = FORWARD_JUMP;
				jumpDirection = -1;
			}
		}
		else {
			nextActionAnim = JUMP;
			jumpDirection = 0;
		}
	}

	if (playerControls->isActionPressed(Controls::Actions::Pause)) {
		if (!pauseHeld) {
			pauseHeld = true;
			Fight::Pause(player->GetPlayerNumber(), commandListTexture);
		}
	}
	else
		pauseHeld = false;
}

void Fighter::CheckCommandLists(Controls* playerControls) {
	std::string inputCheck = "";
	commandFound = false;

	if (!doingHyperAttack) {
		if (!inAir) {
			if (!isAttacking)
				if (basicCommands.DoesCommandExist(inputBuffer))
					inputCheck = basicCommands.GetFoundCommand();
			if (lastAttack < Special) {
				if (specialCommands.DoesCommandExist(inputBuffer)) {
					inputCheck = specialCommands.GetFoundCommand();
					lastAttack = Special;
				}
			}

			if (hyperCommands.DoesCommandExist(inputBuffer, specialMeter)) {
				inputCheck = hyperCommands.GetFoundCommand();
				specialMeter -= hyperCommands.GetFoundCommandMeterUsage();
				lastAttack = Hyper;
			}
		}
		else {
			if (!isAttacking)
				if (airBasicCommands.DoesCommandExist(inputBuffer))
					inputCheck = airBasicCommands.GetFoundCommand();
			if (lastAttack < Special)
				if (airSpecialCommands.DoesCommandExist(inputBuffer)) {
					inputCheck = airSpecialCommands.GetFoundCommand();
					lastAttack = Special;
				}

			if (airHyperCommands.DoesCommandExist(inputBuffer, specialMeter)) {
				inputCheck = airHyperCommands.GetFoundCommand();
				specialMeter -= airHyperCommands.GetFoundCommandMeterUsage();
				lastAttack = Hyper;
			}
		}
	}
	else {
		if (player->GetSupport()->CheckForHyperInput(inputBuffer, specialMeter)) {
			player->HyperSwap();
		}
	}

	if ("" != inputCheck) {
		nextActionAnim = inputCheck;
		commandFound = true;
		inputBuffer = "";
	}
}

bool Fighter::CheckForHyperInput(std::string inputBuffer, int specialMeter) {
	return hyperCommands.DoesCommandExist(inputBuffer, specialMeter);
}

void Fighter::CheckDirectionalInput(Controls* playerControls) {

	float xAxis = playerControls->GetHorizontalAxis();
	float yAxis = playerControls->GetVerticalAxis();

	if (-1 == xAxis && 1 == yAxis) {
		if (!oneDirection) {
			InsertIntoInputBuffer((1 == xScale) ? '1' : '3');
			oneDirection = true;
			twoDirection = false;
			threeDirection = false;
			fourDirection = false;
			sixDirection = false;
			eightDirection = false;
		}
	}
	else if (1 == xAxis && 1 == yAxis) {
		if (!threeDirection) {
			InsertIntoInputBuffer((1 == xScale) ? '3' : '1');
			oneDirection = false;
			twoDirection = false;
			threeDirection = true;
			fourDirection = false;
			sixDirection = false;
			eightDirection = false;
		}
	}
	else if (1 == yAxis) {
		if (!twoDirection) {
			InsertIntoInputBuffer('2');
			/*if (0 < quickRiseFrames) {
				nextAnimToPlay = GETUP;
				velocity.x = 0.f;
			}*/
			oneDirection = false;
			twoDirection = true;
			threeDirection = false;
			fourDirection = false;
			sixDirection = false;
			eightDirection = false;
		}
	}
	else if (-1 == xAxis) {
		if (!fourDirection) {
			InsertIntoInputBuffer((1 == xScale) ? '4' : '6');
			oneDirection = false;
			twoDirection = false;
			threeDirection = false;
			fourDirection = true;
			sixDirection = false;
			eightDirection = false;
		}
	}
	else if (1 == xAxis) {
		if (!sixDirection) {
			InsertIntoInputBuffer((1 == xScale) ? '6' : '4');
			oneDirection = false;
			twoDirection = false;
			threeDirection = false;
			fourDirection = false;
			sixDirection = true;
			eightDirection = false;
		}
	}
	else if (-1 == yAxis) {
		if (!eightDirection) {
			InsertIntoInputBuffer('8');
			oneDirection = false;
			twoDirection = false;
			threeDirection = false;
			fourDirection = false;
			sixDirection = false;
			eightDirection = true;
		}
	}
	else {
		oneDirection = false;
		twoDirection = false;
		threeDirection = false;
		fourDirection = false;
		sixDirection = false;
		eightDirection = false;
	}
}

void Fighter::UpdateInAir() {
	float stageBottomBound = Fight::GetStage()->GetBottomBound();
	sf::IntRect fighterBoundBox = animManager.GetCurrentAnimation()->GetBoundBox();
	float fighterBottomBound = fighterBoundBox.top + fighterBoundBox.height;

	if (0 < velocity.y && fighterBottomBound > stageBottomBound) {
		inAir = false;
		disableActionUntilGrounded = false;
		justLanded = true;
		velocity.y = 0;
		if (isSupport) {
			velocity.x = 0;
		}
	}
	else if (!disableGrav && TERMINAL_VELOCITY > velocity.y)
		velocity.y += GRAVITY;

	if (disablePhysics) {
		velocity.y = 0;
	}
}

void Fighter::UpdatePosition() {
	position.x += (-555.f != newXVelocity) ? newXVelocity : velocity.x;
	position.y += velocity.y;

	newXVelocity = -555.f;
}

sf::Vector2f Fighter::CheckNextPosition() {
	return sf::Vector2f(position.x + (-555.f != newXVelocity) ? newXVelocity : velocity.x, position.y + velocity.y);
}

bool Fighter::CheckStageBounds() {

	sf::IntRect fighterBoundBox = animManager.GetCurrentAnimation()->GetBoundBox();
	float fighterBottomBound = fighterBoundBox.top + fighterBoundBox.height;
	float stageBottomBound = Fight::GetStage()->GetBottomBound();

	if (fighterBottomBound > stageBottomBound)
	{
		position.y -= fighterBottomBound - stageBottomBound;
	}

	//if ((isSupport || isAssisting) && (!onScreen || (onScreen && !supportDone))) {
	if (isSupport && disableGrav) {
		return false;
	}

	float stageLeftBound = Fight::GetStage()->GetLeftBound();
	float stageRightBound = Fight::GetStage()->GetRightBound();

	float fighterLeftBound = fighterBoundBox.left;
	float fighterRightBound = fighterBoundBox.left + fighterBoundBox.width;

	bool isCollision = false;

	if (FALLING == animManager.GetCurrentAnimationName() || IDLE == animManager.GetCurrentAnimationName()) {
		if (fighterLeftBound < stageLeftBound) {
			position.x += (stageLeftBound - fighterLeftBound) - 2;
		}
		else if (fighterRightBound > stageRightBound) {
			position.x -= (fighterRightBound - stageRightBound) - 2;
		}
	}

	// I get the feeling this doesn't work too well with fast velocities
	if (0 > velocity.x && fighterLeftBound < stageLeftBound) {
		velocity.x = 0;
		isCollision = true;
	}

	if (0 < velocity.x && fighterRightBound > stageRightBound) {
		velocity.x = 0;
		isCollision = true;
	}

	if (fighterLeftBound < stageLeftBound || fighterRightBound > stageRightBound) {
		isCollision = true;
	}

	return isCollision;
}

bool Fighter::CheckCameraBounds() {
	//if ((isSupport || isAssisting) && (!onScreen || (onScreen && !supportDone)))
	if (isSupport && disableGrav)
		return false;

	float cameraLeftBound = Fight::GetCamera().getCenter().x - Fight::GetCamera().getSize().x * 0.5f;
	float cameraRightBound = Fight::GetCamera().getCenter().x + Fight::GetCamera().getSize().x * 0.5f;

	sf::IntRect fighterBoundBox = animManager.GetCurrentAnimation()->GetBoundBox();
	float fighterLeftBound = fighterBoundBox.left;
	float fighterRightBound = fighterBoundBox.left + fighterBoundBox.width;
	float fighterBottomBound = fighterBoundBox.top + fighterBoundBox.height;

	bool isCollision = false;

	// I get the feeling this doesn't work too well with fast velocities
	if (0 > velocity.x && fighterLeftBound < cameraLeftBound) {
		velocity.x = 0;
		isCollision = true;
	}

	if (0 < velocity.x && fighterRightBound > cameraRightBound) {
		velocity.x = 0;
		isCollision = true;
	}

	if (fighterLeftBound < cameraLeftBound || fighterRightBound > cameraRightBound)
		isCollision = true;

	return isCollision;
}

void Fighter::Load() {
	healthMeter = maxHealth;
	redMeter = healthMeter;

	// Play default animation
	//animManager.Play((isSupport) ? SUPPORT_IDLE : IDLE, position, xScale);
	animManager.Play((isSupport) ? SUPPORT_IDLE : INTRO, position, xScale);

	if (!colorShader.loadFromFile("Shaders/ColorTest.frag", sf::Shader::Fragment))
		std::cout << "CANNOT LOAD COLOR SHADER" << std::endl;

	std::string filename = "Textures/Misc/HurtBoxTexture.png";
	if (!hurtBoxTexture.loadFromFile(filename))
		std::cout << "CANNOT LOAD HURT BOX TEXTURE" << std::endl;

	filename = "Textures/Misc/HitBoxTexture.png";
	if (!hitBoxTexture.loadFromFile(filename))
		std::cout << "CANNOT LOAD HIT BOX TEXTURE" << std::endl;

	filename = "Textures/Misc/BoundBoxTexture.png";
	if (!boundBoxTexture.loadFromFile(filename))
		std::cout << "CANNOT LOAD BOUND BOX TEXTURE" << std::endl;

	// Portraits
	filename = "Textures/Chars/" + name + "/Portraits/BattlePortrait.png";
	if (!battlePortraitTexture.loadFromFile(filename))
		std::cout << "CANNOT LOAD BOUND BOX TEXTURE" << std::endl;
	battlePortraitSprite.setTexture(battlePortraitTexture);
	battlePortraitSprite.setScale(0.75f, 0.75f);

	filename = "Textures/Chars/" + name + "/Portraits/AssistPortrait.png";
	if (!supportPortraitTexture.loadFromFile(filename))
		std::cout << "CANNOT LOAD BOUND BOX TEXTURE" << std::endl;
	supportPortraitSprite.setTexture(supportPortraitTexture);
	supportPortraitSprite.setScale(0.75f, 0.75f);

	filename = "Textures/Chars/" + name + "/Command_List.png";
	if (!commandListTexture.loadFromFile(filename))
		std::cout << "CANNOT LOAD COMMAND LIST TEXTURE" << std::endl;
}

void Fighter::UpdateAnimations() {
	if (fightFinished && isSupport)
		return;

	animManager.Play(nextAnimToPlay, position, xScale);
	nextActionAnim = "";
	nextAnimToPlay = "";
	animManager.Update(position, xScale, this);
}

void Fighter::UpdateScale(int xPosition) {
	if ((xPosition > position.x + 10))
		xScale = 1;
	else if ((xPosition < position.x - 10))
		xScale = -1;
}

void Fighter::UpdateProjectiles() {
	if (!spawnedProjectiles.empty()) {
		for (int i = 0; i < spawnedProjectiles.size(); i++) {
			spawnedProjectiles[i]->Update();

			if (spawnedProjectiles[i]->IsItTimeToDestroy()) {
				delete spawnedProjectiles[i];
				spawnedProjectiles.erase(spawnedProjectiles.begin() + i);
				i--;
			}
		}
	}
}

void Fighter::DrawProjectiles(sf::RenderWindow* window) {
	if (!spawnedProjectiles.empty())
		for (int i = 0; i < spawnedProjectiles.size(); i++)
			spawnedProjectiles[i]->Draw(window);
}

void Fighter::DrawBoxes(sf::RenderWindow* window) {
	float top;
	float left;
	float width;
	float height;

	int numOfHurtBoxes = animManager.GetCurrentAnimation()->GetHurtBoxes().size();
	sf::RectangleShape tempShape;
	for (int i = 0; i < numOfHurtBoxes; i++) {
		top = animManager.GetCurrentAnimation()->GetHurtBoxes()[i].top;
		left = animManager.GetCurrentAnimation()->GetHurtBoxes()[i].left;
		width = animManager.GetCurrentAnimation()->GetHurtBoxes()[i].width;
		height = animManager.GetCurrentAnimation()->GetHurtBoxes()[i].height;

		tempShape.setPosition(sf::Vector2f(left, top));
		tempShape.setSize(sf::Vector2f(width, height));
		tempShape.setTexture(&hurtBoxTexture);

		window->draw(tempShape);
	}

	top = animManager.GetCurrentAnimation()->GetBoundBox().top;
	left = animManager.GetCurrentAnimation()->GetBoundBox().left;
	width = animManager.GetCurrentAnimation()->GetBoundBox().width;
	height = animManager.GetCurrentAnimation()->GetBoundBox().height;

	sf::RectangleShape boundShape;
	boundShape.setPosition(sf::Vector2f(left, top));
	boundShape.setSize(sf::Vector2f(width, height));
	boundShape.setTexture(&boundBoxTexture);

	window->draw(boundShape);

	sf::RectangleShape hitShape;
	top = animManager.GetCurrentAnimation()->GetHitBox().top;
	left = animManager.GetCurrentAnimation()->GetHitBox().left;
	width = animManager.GetCurrentAnimation()->GetHitBox().width;
	height = animManager.GetCurrentAnimation()->GetHitBox().height;

	hitShape.setPosition(sf::Vector2f(left, top));
	hitShape.setSize(sf::Vector2f(width, height));
	hitShape.setTexture(&hitBoxTexture);

	window->draw(hitShape);
}

void Fighter::InsertIntoInputBuffer(char input) {
	inputBuffer += input;
	inputBufferTimer = 0; // Reset the time before we clear the buffer

	if (INPUT_BUFFER_MAX_LENGTH < inputBuffer.length())
		inputBuffer.erase(0, 1);

	//std::cout << "INSERTED | " << inputBuffer << std::endl;

	//std::cout << "added input: " << input << " | inputBuffer: " << inputBuffer << std::endl;
}

////////////////////// SCRIPTING FUNCTIONS ////////////////////////////////////

void Fighter::ResetToIdle() {
	/*if (isSupport && !inAir) {
		std::cout << "position: " << position.y << endl;
		animManager.Play(SUPPORT_END, position, xScale);
	}*/

	disableGrav = false;
	disablePhysics = false;
	SetCustomGravity(GRAVITY_CONST);
	player->SetDrawOrder(false);
	resetComboDamage = true;

	if (!isSupport) {
		Fight::ResetCombo(player->GetPlayerNumber());
		if (!inAir) Fight::LoseFocus();
		isAttacking = false;
		isDashing = false;
		isHurt = false;
		isBlocking = false;
		isSuperJumping = false;
		canCombo = false;
		inHardKnockdown = false;
		inSoftKnockdown = false;
		inScreenFly = false;
		enableHorizontalDampening = false;
		hasBeenHardKnockdowned = false;
		doingHyperAttack = false;
		player->canHyperSwap = true;
	}
}

void Fighter::Crouch() {
	isAttacking = false;
	StopXMovement();
}

void Fighter::StopXMovement() {
	velocity.x = 0;
}

void Fighter::StopYMovement() {
	velocity.y = 0;
}

void Fighter::DoAttack() {
	//hasHit = false;
	hasHitMain = false;
	hasHitSupport = false;
	isAttacking = true;
	canCombo = false;
	player->SetDrawOrder(true);

	if (downHeld)
		InsertIntoInputBuffer('2');
	if (forwardHeld)
		InsertIntoInputBuffer('6');
	if (backHeld)
		InsertIntoInputBuffer('4');
}

void Fighter::DoHyperAttack() {
	doingHyperAttack = true;
	lastAttack = Hyper;
	Fight::CreateHitSpark(currentCenter, -1, xScale);
}

void Fighter::DoForwardDash() {
	isDashing = true;
	inSoftKnockdown = false;
	velocity.x = 10.f * xScale;
}

void Fighter::DoBackRoll() {
	velocity.x = -3.f * xScale;
}

void Fighter::DoBackDash() {
	isDashing = true;
	inSoftKnockdown = false;
	velocity.x = -10.f * xScale;
}

void Fighter::DoJump() {
	inAir = true;
	isAttacking = false;
	velocity.x = 3.0f * jumpDirection;
	velocity.y = -11.f;
	inputBuffer = "";
}

void Fighter::DoSuperJump() {
	inAir = true;
	isSuperJumping = true;
	velocity.y = -15.f;

	hasHitMain = false;
	hasHitSupport = false;
	isAttacking = false;
	inputBuffer = "";
}

void Fighter::DoAerialRecovery() {
	isHurt = false;
	disableGrav = false;
	//velocity.x = -1.5f * xScale;
	//velocity.y = -10.f;
	Fight::ResetCombo(player->GetPlayerNumber());
}

void Fighter::DisableGravity() {
	disableGrav = true;
}

void Fighter::ResetHit() {
	hasHitMain = false;
	hasHitSupport = false;
}

void Fighter::CheckSuperJump() {
	if (hasHitMain && (specialHeld || upHeld)) {
		nextAnimToPlay = SUPER_JUMP;
	}
}

sf::Vector2f Fighter::GetVelocity() {
	return velocity;
}

void Fighter::SetNewVelocityX(float x) {
	velocity.x = x;
}

void Fighter::SetNewVelocityY(float y) {
	velocity.y = y;
}

void Fighter::CheckBoundBoxCollision(Fighter* enemy) {
	if (isSupport)
		return;

	// Check boudning box
	sf::IntRect enemyBoundBox = enemy->animManager.GetCurrentAnimation()->GetBoundBox();
	sf::IntRect ourBoundBox = animManager.GetCurrentAnimation()->GetBoundBox();

	// Check Bound Box
	if (ourBoundBox.intersects(enemyBoundBox)) {

		if (collidedWithEdges && !enemy->collidedWithEdges) {
			return;
		}

		if (inAir && !enemy->inAir) {
			if ((enemy->GetPosition().x - 15) > position.x) {
				position.x -= (enemy->collidedWithEdges) ? 20.f : 5.f;
			}
			else if ((enemy->GetPosition().x + 15) < position.x) {
				position.x += (enemy->collidedWithEdges) ? 20.f : 5.f;
			}
			else {
				if (-1 == enemy->xScale) { // TAKE CARE OF THIS AFTER THE BOXES HAVE BEEN FIXED TO SEE WHAT IS THE BEST WAY TO DO THIS
					position.x -= (enemy->collidedWithEdges) ? 20.f : 5.f;
				}
				else {
					position.x += (enemy->collidedWithEdges) ? 20.f : 5.f;
				}
			}
		}
		else {

			if (collidedWithEdges) {
				if ((!inAir && enemy->inAir) || (inAir && enemy->inAir)) {
					return;
				}
			}

			if (-1 == xScale) {
				float deltaBoxes = enemyBoundBox.left + enemyBoundBox.width - ourBoundBox.left;
				position.x += deltaBoxes * 0.5f;
				return;
			}
			else {
				float deltaBoxes = ourBoundBox.left + ourBoundBox.width - enemyBoundBox.left;
				position.x -= deltaBoxes * 0.5f;
				return;
			}
		}
	}
}

void Fighter::CheckHitBoxCollision(Fighter* enemy) {
	DamageInfo dInfo = animManager.GetCurrentAnimation()->GetDamageInfo();
	dInfo.knockback.x *= (enemy->position.x > position.x) ? 1 : -1;
	dInfo.additionalEffectKnockback.x *= (enemy->position.x > position.x) ? 1 : -1;
	//std::cout << MARCO << std::endl;
	// Check Hit Box
	/*
	sf::IntRect enemyHitBox = enemy->animManager.GetCurrentAnimation()->GetHitBox();
	sf::IntRect ourHitBox = animManager.GetCurrentAnimation()->GetHitBox();
	if (((!enemy->GetIsSupport() && !hasHitMain) || (enemy->GetIsSupport() && !hasHitSupport)) && ourHitBox.intersects(enemyHitBox)) {
		//hasHit = true;
		if (enemy->GetIsSupport())
			hasHitSupport = true;
		else
			hasHitMain = true;
		sf::Vector2f pointOfCollision;
		pointOfCollision.x = (position.x < enemy->GetPosition().x) ? enemyHitBox.left : enemyHitBox.left + enemyHitBox.width;
		pointOfCollision.y = ((ourHitBox.top + ourHitBox.height * 0.5f) + (enemyHitBox.top + enemyHitBox.height * 0.5f)) * 0.5f;

		if (enemy->TakeDamage(dInfo, pointOfCollision, comboNumber, this)) {
			CheckOnHit();
			animManager.GetCurrentAnimation()->AdvanceOneSprite();
			comboNumber++;
		}
		specialMeter += dInfo.meterGain;
		if (50000 < specialMeter)
			specialMeter = 50000;
		canCombo = true;
		hitStopFrames = dInfo.hitStop;
		if (inAir) velocity.y -= 1.f;
		return;
	}
	*/

	std::vector<sf::IntRect> enemyHurtBoxes = enemy->animManager.GetCurrentAnimation()->GetHurtBoxes();
	sf::IntRect ourHitBox = animManager.GetCurrentAnimation()->GetHitBox();
	for (int i = 0; i < enemyHurtBoxes.size(); i++) {
		if (((!enemy->GetIsSupport() && !hasHitMain) || (enemy->GetIsSupport() && !hasHitSupport)) && ourHitBox.intersects(enemyHurtBoxes[i])) {
			if (enemy->GetIsSupport())
				hasHitSupport = true;
			else
				hasHitMain = true;
			sf::Vector2f pointOfCollision;
			pointOfCollision.x = (position.x < enemy->GetPosition().x) ? enemyHurtBoxes[i].left : enemyHurtBoxes[i].left + enemyHurtBoxes[i].width;
			pointOfCollision.y = ((ourHitBox.top + (ourHitBox.height * 0.5f)) + (enemyHurtBoxes[i].top + (enemyHurtBoxes[i].height * 0.5f))) * 0.5f;
			if (enemy->TakeDamage(dInfo, pointOfCollision, comboNumber, this)) {
				CheckOnHit();
				animManager.GetCurrentAnimation()->AdvanceOneSprite();
				comboNumber++;
				hitStopFrames = dInfo.hitStop;
			}
			specialMeter += dInfo.meterGain;
			if (50000 < specialMeter)
				specialMeter = 50000;
			canCombo = true;
			if (inAir) velocity.y -= 1.f;
			return;
		}
	}
}

void Fighter::CheckFighterCollision(Fighter* enemy) {
	if (SUPPORT_END != enemy->animManager.GetCurrentAnimationName()) CheckBoundBoxCollision(enemy);
	CheckHitBoxCollision(enemy);

	if (!spawnedProjectiles.empty())
		for (int i = 0; i < spawnedProjectiles.size(); i++)
			spawnedProjectiles[i]->CheckEnemyCollision(this, enemy);
}

int Fighter::CalculateDamage(DamageInfo dInfo, int comboCount) {
	float min = (float)dInfo.damage * 0.1f;

	float scaledDamage = (dInfo.damage * pow(dInfo.damageScale, comboCount));

	return (min < scaledDamage) ? (int)scaledDamage : (int)min;
}

bool Fighter::TakeDamage(DamageInfo dInfo, sf::Vector2f pointOfCollision, int comboCount, Fighter* enemy) {

	if (!onScreen || KOed) {
		disablePhysics = false;
		disableGrav = false;
		return false;
	}

	if (!isPlayable) {
		nextAnimToPlay = SUPPORT_EXIT;
		Fight::CreateHitSpark(pointOfCollision, 0, xScale);
		assistCooldownMultiplyer = 2;
		inAir = false;
		return true;
	}

	if (isSupport) {
		supportDone = true;
		disableGrav = false;
	}

	player->SetDrawOrder(false);

	// BLOCKED
	if (!inHardKnockdown && (!isAttacking && !isHurt) && ((forwardHeld && -1 == xScale) || (backHeld && 1 == xScale)) && ((isCrouching && 0 == dInfo.highLowAttack) || (!isCrouching && 1 == dInfo.highLowAttack) || (2 == dInfo.highLowAttack))) {
		velocity.x = dInfo.knockback.x;
		nextAnimToPlay = (inAir) ? J_BLOCK : (downHeld) ? C_BLOCK : BLOCK;
		//animManager.GetAnimation(nextAnimToPlay)->SetFramesOfLastSprite(dInfo.blockStun); // EH KINDA EH
		animManager.GetAnimation(nextAnimToPlay)->SetFramesOfAnimation(dInfo.blockStun);
		hitStopFrames = dInfo.hitStop;
		if (isBlocking)
			animManager.Restart();
		isBlocking = true;
		enableHorizontalDampening = true;
		Fight::CreateHitSpark(pointOfCollision, HitSparkType::Guard, xScale);
		healthMeter -= CalculateDamage(dInfo, comboCount) * 0.25f;
		redMeter -= CalculateDamage(dInfo, comboCount) * 0.125f;
		AddSpecialMeter(dInfo.meterGain * 0.5f);
		if (0 >= redMeter)
			redMeter = 1;
		if (0 >= healthMeter)
			healthMeter = 1;
		if (collidedWithEdges && enemy) {
			enemy->PushAway(-velocity.x);
			velocity.x = 0;
		}
		return false;
	}
	// NOT BLOCKED
	else if (ON_GROUND != animManager.GetCurrentAnimationName() && GETUP != animManager.GetCurrentAnimationName() || AdditionalEffect::OTG == dInfo.additionalEffect)
	{
		switch (dInfo.additionalEffect)
		{
		case AdditionalEffect::Hard_KnockDown:
			velocity.x = dInfo.additionalEffectKnockback.x;
			velocity.y = dInfo.additionalEffectKnockback.y;
			inHardKnockdown = true;
			inSoftKnockdown = false;
			nextAnimToPlay = HARD_KNOCKDOWN;
			break;
		case AdditionalEffect::Knockdown:
			velocity.x = dInfo.additionalEffectKnockback.x;
			velocity.y = dInfo.additionalEffectKnockback.y;
			inSoftKnockdown = true;
			inHardKnockdown = false;
			nextAnimToPlay = HARD_KNOCKDOWN;
			break;
		case AdditionalEffect::Snap_Back:
			if (!isSupport) {
				velocity.x = -12.f * xScale;
				velocity.y = -10.f;
				isSupport = true;
				nextAnimToPlay = SNAP_BACK_HURT;
				supportDone = false;
				Fight::cameraLock = true;
			}
			break;
		case AdditionalEffect::Screen_Fly:
			if (inAir) {
				if (!isSupport) Fight::FocusOnPlayer(player->GetPlayerNumber());
				velocity.x = -12.f * xScale;
				velocity.y = 12.f;
				inHardKnockdown = true;
				inSoftKnockdown = false;
				inScreenFly = true;
				nextAnimToPlay = HARD_KNOCKDOWN;
				break;
			}
		default:
			velocity.x = dInfo.knockback.x;
			velocity.y = dInfo.knockback.y;
			inHardKnockdown = false;
			inSoftKnockdown = false;
			if (velocity.y < 0) inAir = true;
			nextAnimToPlay = (inAir) ? AIR_HURT : (isCrouching) ? CROUCH_HURT : HURT;
			break;
		}

		if (inAir && velocity.y == 0) velocity.y = -7.f;
		disablePhysics = (dInfo.ignoreAirShift);
		disableGrav = false;
		if (velocity.y < 0) inAir = true;
		if (!inAir && velocity.y > 0) velocity.y = 0;
		if (AIR_HURT == nextAnimToPlay)
			animManager.GetAnimation(nextAnimToPlay)->SetFramesAtSprite(0, dInfo.hitStun);
		else
			//animManager.GetAnimation(nextAnimToPlay)->SetFramesOfLastSprite(dInfo.hitStun - 6); // EH KINDS EH
			animManager.GetAnimation(nextAnimToPlay)->SetFramesOfAnimation(dInfo.hitStun - 6); // 6 frames is how long the HURT END anim is
		hitStopFrames = dInfo.hitStop;
		if (isHurt)
			animManager.Restart();
		isHurt = true;
		Fight::CreateHitSpark(pointOfCollision, dInfo.sparkType, xScale);
		AddSpecialMeter(dInfo.meterGain * 0.5f);
		healthMeter -= CalculateDamage(dInfo, comboCount);
		redMeter -= CalculateDamage(dInfo, comboCount) * 0.5f;
		if (0 > redMeter)
			redMeter = 0;
		if (0 >= healthMeter) {
			healthMeter = 0;
			Defeated();
		}

		if (!inAir && collidedWithEdges && enemy) {
			enemy->PushAway(-velocity.x);
			velocity.x = 0;
		}

		lastBaseDamage = dInfo.damage;
		lastModifiedDamage = CalculateDamage(dInfo, comboCount);
		lastComboDamage = (resetComboDamage) ? lastModifiedDamage : lastComboDamage + lastModifiedDamage;
		resetComboDamage = false;
		if (maxComboDamage < lastComboDamage) maxComboDamage = lastComboDamage;

		return true;
	}

	return false;
}

void Fighter::Defeated() {
	if (Fight::IsWinDisabled())
		return;

	KOed = true;
	redMeter = 0;
	velocity.x = -3.f * xScale;
	velocity.y = -7.f;
	inAir = true;
	disablePhysics = false;
	disableGrav = false;
	inHardKnockdown = true;
	inSoftKnockdown = false;
	nextAnimToPlay = HARD_KNOCKDOWN;
	ApplicationData::SetGameSpeed(0.5f, 30.f);
	if (player->GetMain()->KOed && (player->GetSupport()->KOed || !player->GetSupport()->GetIsPlayable()))
		Fight::ShowKOText();
}

void Fighter::PushAway(float xKnockback) {
	if (Special != lastAttack && Hyper != lastAttack) {
		velocity.x = xKnockback;
	}
}

void Fighter::ResetCombo() {
	comboNumber = 0;
}

AnimationManager Fighter::GetAnimationManager() {
	return animManager;
}

void Fighter::IncrementCombo() {
	comboNumber++;
}

void Fighter::AddSpecialMeter(int additionalMeter) {
	specialMeter += additionalMeter;
	if (50000 < specialMeter)
		specialMeter = 50000;
}

void Fighter::SetCanCombo(bool value) {
	canCombo = value;
}

void Fighter::CheckOnHit() {
}

float Fighter::GetPercentHealth() {
	return (float)healthMeter / (float)maxHealth;
}

float Fighter::GetPercentRedHealth() {
	return (float)redMeter / (float)maxHealth;
}

float Fighter::GetPercentOneSpecialbar() {
	return (float)(specialMeter % ONE_SPECIAL_BAR) / (float)ONE_SPECIAL_BAR;
}

void Fighter::UpdateCenter() {
	sf::Vector2f spriteOrigin = animManager.GetCurrentAnimation()->GetOrigin();

	currentCenter.y = (position.y + (center.y - spriteOrigin.y));// + center.y;
	currentCenter.x = position.x;
	/*
	if (0 < xScale)
		currentCenter.x = (position.x - spriteOrigin.x);// +center.x;
	else
		currentCenter.x = (position.x + spriteOrigin.x);// -center.x;
		*/
}

void Fighter::SetPlayer(Player* p) {
	player = p;
}

int Fighter::GetNumberOfSpecialBars() {
	return specialMeter / ONE_SPECIAL_BAR;
}

int Fighter::GetCombo() {
	return comboNumber;
}

void Fighter::SummonSupport(sf::Vector2f mainPosition, int mainXScale) {
	if (isAssisting || supportCooldown > 0 || KOed)
		return;

	hasHitSupport = false;
	hasHitMain = false;
	supportDone = false;

	supportEndPositionX = mainPosition.x;
	xScale = mainXScale;
	nextAnimToPlay = SUPPORT_ENTER;
	DoSupportEnter();
}

void Fighter::CrossAssault(sf::Vector2f mainPosition, int mainXScale) {
	hasHitSupport = false;
	hasHitMain = false;
	supportDone = false;

	supportEndPositionX = mainPosition.x;
	xScale = mainXScale;
	nextAnimToPlay = CROSS_ASSAULT;
	DoSupportEnter();
}

void Fighter::SetSupport(bool value) {
	isSupport = value;
}

bool Fighter::GetIsSupport() {
	return isSupport;
}

void Fighter::DoSupportEnter() {
	supportDone = false;
	inAir = true;

	if (1 == xScale) {
		position.x = (Fight::GetCamera().getCenter().x - Fight::GetCamera().getSize().x * 0.5f) - animManager.GetCurrentAnimation()->GetOrigin().x;
	}
	else {
		position.x = (Fight::GetCamera().getCenter().x + Fight::GetCamera().getSize().x * 0.5f) + animManager.GetCurrentAnimation()->GetOrigin().x;
	}

	position.y = (Fight::GetCamera().getCenter().y - Fight::GetCamera().getSize().y * 0.5f) - animManager.GetCurrentAnimation()->GetOrigin().y;

	velocity.x = ((supportEndPositionX - position.x)) / SUPPORT_FRAMES_OF_ENTRY;
	velocity.y = (((Fight::GetStage()->GetBottomBound() - animManager.GetCurrentAnimation()->GetOrigin().y) - position.y)) / SUPPORT_FRAMES_OF_ENTRY;

	isAssisting = true;
	disableGrav = true;

	animManager.ReUpdateAnimationBoxes(position, xScale);
}

void Fighter::DoSupportExit() {
	supportDone = false;

	if (!onScreen) {
		supportCooldown = (SUPPORT_COOLDOWN_FRAMES * assistCooldownMultiplyer);
		assistCooldownMultiplyer = 1;
		isAssisting = false;
		nextAnimToPlay = SUPPORT_IDLE;
	}

	if (!inAir) {
		inAir = true;
		disableGrav = true;
		velocity.y = -5.f;
		velocity.x = -11.f * xScale;
		xScale *= -1;
	}
}

bool Fighter::CheckOffScreen() {
	float camTop = Fight::GetCamera().getCenter().y - Fight::GetCamera().getSize().y * 0.5f;
	float boundBottom = animManager.GetCurrentAnimation()->GetBoundBox().top + animManager.GetCurrentAnimation()->GetBoundBox().height;

	if (1 == xScale) {
		float camRight = Fight::GetCamera().getCenter().x + Fight::GetCamera().getSize().x * 0.5f;
		float boundLeft = animManager.GetCurrentAnimation()->GetBoundBox().left;

		if (boundLeft > camRight)
			return false;
	}
	else {
		float camLeft = Fight::GetCamera().getCenter().x - Fight::GetCamera().getSize().x * 0.5f;
		float boundRight = animManager.GetCurrentAnimation()->GetBoundBox().left + animManager.GetCurrentAnimation()->GetBoundBox().width;

		if (boundRight < camLeft)
			return false;
	}

	return true;
}

void Fighter::SetMainEnemy(Fighter* mainEnemy) {
	enemyMain = mainEnemy;
}

bool Fighter::CheckThrowRange() {
	if (downHeld || isDashing)
		return false;

	std::string currentEnemyAnim = enemyMain->GetAnimationManager().GetCurrentAnimationName();

	if ((!inAir && !enemyMain->inAir) && (IDLE == currentEnemyAnim || FORWARD_WALK == currentEnemyAnim || BACK_WALK == currentEnemyAnim || FORWARD_DASH == currentEnemyAnim || BACK_DASH == currentEnemyAnim)) {
		sf::IntRect enemyBoundBox = enemyMain->GetAnimationManager().GetCurrentAnimation()->GetBoundBox();
		sf::IntRect ourBoundBox = animManager.GetCurrentAnimation()->GetBoundBox();

		if (1 == xScale) {
			if (15 > (enemyBoundBox.left - (ourBoundBox.left + ourBoundBox.width))) {
				return true;
			}
		}
		else {
			if (15 > (ourBoundBox.left - (enemyBoundBox.left + enemyBoundBox.width))) {
				return true;
			}
		}
	}
	return false;
}

void Fighter::BeThrown(std::string throwName, int newXScale) {
	beingThrown = true;
	xScale = newXScale;
	//animManager.Play(throwName, position, xScale);
	nextAnimToPlay = throwName;
}

void Fighter::DoForwardThrow() {

}

void Fighter::DoBackThrow() {

}

void Fighter::ReceiveThrowDamage(DamageInfo dInfo) {

	switch (dInfo.additionalEffect)
	{
	case AdditionalEffect::Hard_KnockDown:
		velocity.x = dInfo.additionalEffectKnockback.x;
		velocity.y = dInfo.additionalEffectKnockback.y;
		inHardKnockdown = true;
		inSoftKnockdown = false;
		break;
	case AdditionalEffect::Knockdown:
		velocity.x = dInfo.additionalEffectKnockback.x;
		velocity.y = dInfo.additionalEffectKnockback.y;
		inSoftKnockdown = true;
		inHardKnockdown = false;
		break;
	case AdditionalEffect::Screen_Fly:
		if (inAir) {
			velocity.x = dInfo.additionalEffectKnockback.x;
			velocity.y = dInfo.additionalEffectKnockback.y;
			inHardKnockdown = true;
			inSoftKnockdown = false;
			inScreenFly = true;
			break;
		}
	default:
		velocity.x = dInfo.knockback.x;
		velocity.y = dInfo.knockback.y;
		inHardKnockdown = false;
		inSoftKnockdown = false;
		break;
	}

	if (inAir && velocity.y == 0) velocity.y = -7.f;
	disablePhysics = (dInfo.ignoreAirShift);
	disableGrav = false;
	if (velocity.y != 0) inAir = true;
	nextAnimToPlay = (inHardKnockdown || inSoftKnockdown) ? HARD_KNOCKDOWN : (inAir) ? AIR_HURT : (isCrouching) ? CROUCH_HURT : HURT;
	if (AIR_HURT == nextAnimToPlay)
		animManager.GetAnimation(nextAnimToPlay)->SetFramesAtSprite(0, dInfo.hitStun);
	else
		animManager.GetAnimation(nextAnimToPlay)->SetFramesOfAnimation(dInfo.hitStun - 6);
	isHurt = true;
	healthMeter -= dInfo.damage;
	redMeter -= dInfo.damage * 0.5f;
	Fight::CreateHitSpark(currentCenter, dInfo.sparkType, xScale);
	if (0 > healthMeter)
		healthMeter = 0;
	if (0 > redMeter)
		redMeter = 0;

	beingThrown = false;
	return;
}

void Fighter::DoThrowDamage() {
	DamageInfo dInfo = animManager.GetCurrentAnimation()->GetDamageInfo();
	dInfo.knockback.x *= xScale;
	dInfo.additionalEffectKnockback.x *= xScale;
	enemyMain->ReceiveThrowDamage(dInfo);
}

bool Fighter::GetIsPlayable() {
	return isPlayable;
}
void Fighter::SetNextAnimToPlay(std::string nextAnim) {
	nextActionAnim = nextAnim;
}

void Fighter::CheckForSnapBackSpawn() {
	float camTop = Fight::GetCamera().getCenter().y - Fight::GetCamera().getSize().y * 0.5f;
	float boundBottom = animManager.GetCurrentAnimation()->GetBoundBox().top + animManager.GetCurrentAnimation()->GetBoundBox().height;

	if (-1 == xScale) {
		float camRight = Fight::GetCamera().getCenter().x + Fight::GetCamera().getSize().x * 0.5f;
		float boundLeft = animManager.GetCurrentAnimation()->GetBoundBox().left;

		if (boundLeft > camRight) {
			nextAnimToPlay = SUPPORT_IDLE;
			player->SnapBackSwap();
		}
	}
	else {
		float camLeft = Fight::GetCamera().getCenter().x - Fight::GetCamera().getSize().x * 0.5f;
		float boundRight = animManager.GetCurrentAnimation()->GetBoundBox().left + animManager.GetCurrentAnimation()->GetBoundBox().width;

		if (boundRight < camLeft) {
			nextAnimToPlay = SUPPORT_IDLE;
			player->SnapBackSwap();
		}
	}
}

void Fighter::HyperSwap(sf::Vector2f mainPosition, int mainXScale) {
	hasHitSupport = false;
	hasHitMain = false;
	supportDone = false;
	doingHyperSwap = true;
	supportEndPositionX = mainPosition.x;
	xScale = mainXScale;
	nextAnimToPlay = SUPPORT_ENTER;
	DoSupportEnter();
}

void Fighter::SetColor(int colorNum) {
}

void Fighter::SetCustomGravity(float newGrav) {
	GRAVITY = newGrav;
}

void Fighter::SetReadyIntro(bool rIntro) {
	readyIntro = rIntro;
}

bool Fighter::GetKOed() {
	return KOed;
}

void Fighter::FightIsOver(bool result) {
	fightFinished = true;
	winner = result;

	if (winner && !inAir) {
		velocity.x = 0;
		nextAnimToPlay = IDLE;
	}
}

void Fighter::StartEndCountdown() {
	Fight::StartEndCountdown();
}

sf::Sprite* Fighter::getBattlePortrait() {
	return &battlePortraitSprite;
}

sf::Sprite* Fighter::getSupportPortrait() {
	supportPortraitSprite.setColor((0 < supportCooldown) ? sf::Color::Black : sf::Color::White);
	return &supportPortraitSprite;
}

void Fighter::SetSoloFighter() {
	maxHealth *= 2;
	healthMeter = maxHealth;
	redMeter = healthMeter;
}

std::vector<Projectile*>* Fighter::GetSpawnedProjectiles() {
	return &spawnedProjectiles;
}

void Fighter::IntroDone() {
	Fight::PlayerIntroDone(player->GetPlayerNumber());
}

