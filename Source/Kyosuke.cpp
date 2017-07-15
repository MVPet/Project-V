#include "Kyosuke.h"
#include "Controls.h"
#include <iostream>

Kyosuke::Kyosuke() {
}

Kyosuke::~Kyosuke() {
}

void Kyosuke::Load() {
	name = KYOSUKE;
	std::string charPath = "Textures/Chars/" + name + "/";
	isPlayable = true;
	center = sf::Vector2f(174, 210);
	maxHealth = 1200000;
	maxSpeed = 3.f;

	Animation* temp;
	DamageInfo* dInfo;
	std::vector<sf::IntRect> hurtBoxes;
	int* framesPerSprite;

	// IDLE
	temp = new Animation(charPath, IDLE, 15, true);
	temp->AddFrameFunction(0, reset_to_idle);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(157, 169, 50, 102));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 168, 62, 41));
	hurtBoxes.push_back(sf::IntRect(144, 208, 70, 63));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(IDLE, temp);

	// WIN
	temp = new Animation(charPath, WIN, 9, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(8, start_end_countdown);
	temp->AddBoundBox(0, sf::IntRect(157, 169, 50, 102));
	animManager.AddAnimation(WIN, temp);

	// LOSE
	temp = new Animation(charPath, LOSE, 6, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(5, start_end_countdown);
	temp->AddBoundBox(0, sf::IntRect(157, 169, 50, 102));
	animManager.AddAnimation(LOSE, temp);

	// INTRO
	temp = new Animation(charPath, INTRO, 4, false, IDLE);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(3, intro_done);
	framesPerSprite = new int[5]{ 45, 5, 5, 5, };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddBoundBox(0, sf::IntRect(157, 169, 50, 102));
	animManager.AddAnimation(INTRO, temp);

	// HURT
	temp = new Animation(charPath, HURT, 4, false, HURT_END);
	temp->AddBoundBox(0, sf::IntRect(155, 168, 50, 101));
	temp->AddBoundBox(1, sf::IntRect(149, 168, 50, 101));
	temp->AddBoundBox(2, sf::IntRect(143, 168, 50, 101));
	temp->AddBoundBox(3, sf::IntRect(124, 168, 50, 101));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 164, 58, 46));
	hurtBoxes.push_back(sf::IntRect(140, 207, 75, 62));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(142, 164, 71, 46));
	hurtBoxes.push_back(sf::IntRect(140, 207, 75, 62));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(129, 164, 73, 46));
	hurtBoxes.push_back(sf::IntRect(140, 207, 75, 62));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(120, 164, 58, 106));
	hurtBoxes.push_back(sf::IntRect(174, 228, 37, 42));
	temp->AddHurtBoxes(3, hurtBoxes);
	animManager.AddAnimation(HURT, temp);

	// HURT END
	temp = new Animation(charPath, HURT_END, 3, false);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[3]{ 2,2,2 };
	temp->AddBoundBox(0, sf::IntRect(140, 174, 50, 97));
	temp->AddBoundBox(1, sf::IntRect(146, 172, 50, 97));
	temp->AddBoundBox(2, sf::IntRect(152, 174, 50, 97));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(128, 172, 74, 45));
	hurtBoxes.push_back(sf::IntRect(136, 217, 75, 53));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(142, 169, 70, 41));
	hurtBoxes.push_back(sf::IntRect(140, 210, 72, 60));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 169, 66, 45));
	hurtBoxes.push_back(sf::IntRect(142, 214, 70, 56));
	temp->AddHurtBoxes(2, hurtBoxes);
	animManager.AddAnimation(HURT_END, temp);

	// AIR HURT
	temp = new Animation(charPath, AIR_HURT, 2, false, AERIAL_RECOVERY);
	temp->AddBoundBox(0, sf::IntRect(161, 169, 50, 93));
	temp->AddBoundBox(1, sf::IntRect(151, 177, 50, 50));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 162, 63, 102));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(141, 173, 84, 61));
	temp->AddHurtBoxes(1, hurtBoxes);
	animManager.AddAnimation(AIR_HURT, temp);

	// AERIAL RECOVERY
	temp = new Animation(charPath, AERIAL_RECOVERY, 5, false);
	temp->SetFramesOfAnimation(12);
	temp->AddFrameFunction(0, do_aerial_recovery);
	temp->AddBoundBox(0, sf::IntRect(153, 177, 50, 50));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(126, 177, 123, 34));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(140, 168, 107, 50));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(149, 161, 50, 64));
	hurtBoxes.push_back(sf::IntRect(169, 130, 45, 34));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(136, 134, 28, 61));
	hurtBoxes.push_back(sf::IntRect(150, 171, 58, 50));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(117, 175, 87, 43));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(AERIAL_RECOVERY, temp);

	// CROUCH HURT
	temp = new Animation(charPath, CROUCH_HURT, 4, false, CROUCH_HURT_END);
	temp->AddBoundBox(0, sf::IntRect(155, 198, 50, 74));
	temp->AddBoundBox(2, sf::IntRect(139, 198, 50, 74));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 198, 61, 74));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(134, 198, 72, 74));
	temp->AddHurtBoxes(2, hurtBoxes);
	animManager.AddAnimation(CROUCH_HURT, temp);

	// CROUCH HURT END
	temp = new Animation(charPath, CROUCH_HURT_END, 3, false);
	temp->AddBoundBox(0, sf::IntRect(134, 205, 53, 70));
	temp->AddBoundBox(1, sf::IntRect(150, 205, 53, 70));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(132, 204, 75, 71));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(146, 204, 67, 71));
	temp->AddHurtBoxes(1, hurtBoxes);
	animManager.AddAnimation(CROUCH_HURT_END, temp);

	// HARD KNOCKDOWN
	temp = new Animation(charPath, HARD_KNOCKDOWN, 3, false);
	temp->AddBoundBox(0, sf::IntRect(160, 182, 50, 76));
	temp->AddBoundBox(1, sf::IntRect(149, 184, 76, 43));
	temp->AddBoundBox(2, sf::IntRect(147, 171, 57, 54));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(133, 169, 67, 40));
	hurtBoxes.push_back(sf::IntRect(174, 204, 56, 64));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(133, 157, 49, 58));
	hurtBoxes.push_back(sf::IntRect(172, 185, 75, 64));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(133, 178, 52, 65));
	hurtBoxes.push_back(sf::IntRect(180, 162, 56, 36));
	temp->AddHurtBoxes(2, hurtBoxes);
	animManager.AddAnimation(HARD_KNOCKDOWN, temp);

	// ON GROUND
	temp = new Animation(charPath, ON_GROUND, 6, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(133, 215, 62, 56));
	temp->AddBoundBox(1, sf::IntRect(133, 228, 72, 43));
	temp->AddBoundBox(3, sf::IntRect(133, 237, 72, 34));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(130, 203, 75, 69));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(108, 228, 125, 41));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(108, 237, 131, 36));
	temp->AddHurtBoxes(3, hurtBoxes);
	animManager.AddAnimation(ON_GROUND, temp);

	// GET UP
	temp = new Animation(charPath, GETUP, 5, false, IDLE);
	temp->SetFramesOfAnimation(15);
	temp->AddBoundBox(0, sf::IntRect(147, 236, 60, 35));
	temp->AddBoundBox(2, sf::IntRect(157, 225, 48, 46));
	temp->AddBoundBox(3, sf::IntRect(157, 203, 48, 68));
	temp->AddBoundBox(4, sf::IntRect(152, 178, 50, 93));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(134, 236, 93, 46));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(134, 211, 69, 72));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(147, 199, 69, 72));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 188, 51, 83));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(147, 168, 61, 104));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(GETUP, temp);

	// BACK ROLL
	temp = new Animation(charPath, BACK_ROLL, 4, false, IDLE);
	temp->SetFramesOfAnimation(18);
	temp->AddFrameFunction(0, do_back_roll);
	temp->AddBoundBox(0, sf::IntRect(156, 173, 50, 98));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 170, 50, 50));
	hurtBoxes.push_back(sf::IntRect(130, 213, 61, 58));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 170, 69, 50));
	hurtBoxes.push_back(sf::IntRect(130, 213, 61, 58));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(170, 185, 50, 50));
	hurtBoxes.push_back(sf::IntRect(130, 213, 61, 58));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(131, 195, 84, 76));
	temp->AddHurtBoxes(3, hurtBoxes);
	animManager.AddAnimation(BACK_ROLL, temp);

	// FORWARD_WALK
	temp = new Animation(charPath, FORWARD_WALK, 6, true);
	temp->AddBoundBox(0, sf::IntRect(157, 168, 42, 104));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 166, 52, 106));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(FORWARD_WALK, temp);

	// BACK_WALK
	temp = new Animation(charPath, BACK_WALK, 6, true);
	temp->AddBoundBox(0, sf::IntRect(150, 167, 50, 104));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 167, 71, 33));
	hurtBoxes.push_back(sf::IntRect(150, 164, 50, 107));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 167, 71, 33));
	hurtBoxes.push_back(sf::IntRect(158, 164, 37, 107));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 167, 71, 33));
	hurtBoxes.push_back(sf::IntRect(150, 164, 41, 107));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 167, 71, 33));
	hurtBoxes.push_back(sf::IntRect(150, 164, 38, 107));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 167, 71, 33));
	hurtBoxes.push_back(sf::IntRect(150, 164, 46, 107));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(BACK_WALK, temp);

	// FORWARD DASH
	temp = new Animation(charPath, FORWARD_DASH, 4, false);
	temp->AddFrameFunction(0, do_forward_dash);
	temp->AddBoundBox(0, sf::IntRect(151, 172, 50, 99));
	temp->AddBoundBox(2, sf::IntRect(170, 172, 50, 99));
	temp->AddBoundBox(3, sf::IntRect(160, 172, 50, 99));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 171, 50, 67));
	hurtBoxes.push_back(sf::IntRect(134, 236, 84, 35));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 171, 49, 67));
	hurtBoxes.push_back(sf::IntRect(123, 236, 110, 35));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(170, 171, 50, 99));
	hurtBoxes.push_back(sf::IntRect(134, 233, 37, 30));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 171, 61, 100));
	temp->AddHurtBoxes(3, hurtBoxes);
	animManager.AddAnimation(FORWARD_DASH, temp);
	basicCommands.AddCommand("66", FORWARD_DASH);

	// BACK DASH
	temp = new Animation(charPath, BACK_DASH, 5, false);
	temp->AddFrameFunction(0, do_back_dash);
	temp->AddFrameFunction(3, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(149, 176, 53, 93));
	temp->AddBoundBox(3, sf::IntRect(146, 176, 53, 93));
	temp->AddBoundBox(4, sf::IntRect(154, 176, 53, 93));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 171, 67, 98));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(139, 171, 67, 42));
	hurtBoxes.push_back(sf::IntRect(139, 213, 78, 42));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 171, 67, 98));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 171, 55, 98));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 171, 67, 98));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(BACK_DASH, temp);
	basicCommands.AddCommand("44", BACK_DASH);

	// JUMP
	temp = new Animation(charPath, JUMP, 10, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(1, do_jump);
	temp->AddBoundBox(0, sf::IntRect(155, 157, 31, 97));
	temp->AddBoundBox(3, sf::IntRect(161, 157, 31, 68));
	temp->AddBoundBox(4, sf::IntRect(170, 157, 31, 68));
	temp->AddBoundBox(8, sf::IntRect(161, 157, 31, 68));
	temp->AddBoundBox(9, sf::IntRect(155, 157, 31, 97));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 40, 124));
	hurtBoxes.push_back(sf::IntRect(129, 175, 80, 40));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 40, 115));
	hurtBoxes.push_back(sf::IntRect(129, 175, 80, 40));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 149, 38, 101));
	hurtBoxes.push_back(sf::IntRect(187, 185, 32, 21));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 161, 45, 70));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 149, 38, 101));
	hurtBoxes.push_back(sf::IntRect(187, 168, 32, 21));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 59, 27));
	hurtBoxes.push_back(sf::IntRect(150, 175, 43, 89));
	temp->AddHurtBoxes(9, hurtBoxes);
	animManager.AddAnimation(JUMP, temp);

	// FORWARD JUMP
	temp = new Animation(charPath, JUMP, 10, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(1, do_jump);
	temp->AddBoundBox(0, sf::IntRect(155, 157, 31, 97));
	temp->AddBoundBox(3, sf::IntRect(161, 157, 31, 68));
	temp->AddBoundBox(4, sf::IntRect(170, 157, 31, 68));
	temp->AddBoundBox(8, sf::IntRect(161, 157, 31, 68));
	temp->AddBoundBox(9, sf::IntRect(155, 157, 31, 97));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 40, 124));
	hurtBoxes.push_back(sf::IntRect(129, 175, 80, 40));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 40, 115));
	hurtBoxes.push_back(sf::IntRect(129, 175, 80, 40));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 149, 38, 101));
	hurtBoxes.push_back(sf::IntRect(187, 185, 32, 21));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 161, 45, 70));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 149, 38, 101));
	hurtBoxes.push_back(sf::IntRect(187, 168, 32, 21));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 59, 27));
	hurtBoxes.push_back(sf::IntRect(150, 175, 43, 89));
	temp->AddHurtBoxes(9, hurtBoxes);
	animManager.AddAnimation(FORWARD_JUMP, temp);

	// BACKWARD JUMP
	temp = new Animation(charPath, JUMP, 10, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(1, do_jump);
	temp->AddBoundBox(0, sf::IntRect(155, 157, 31, 97));
	temp->AddBoundBox(3, sf::IntRect(161, 157, 31, 68));
	temp->AddBoundBox(4, sf::IntRect(170, 157, 31, 68));
	temp->AddBoundBox(8, sf::IntRect(161, 157, 31, 68));
	temp->AddBoundBox(9, sf::IntRect(155, 157, 31, 97));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 40, 124));
	hurtBoxes.push_back(sf::IntRect(129, 175, 80, 40));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 40, 115));
	hurtBoxes.push_back(sf::IntRect(129, 175, 80, 40));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 149, 38, 101));
	hurtBoxes.push_back(sf::IntRect(187, 185, 32, 21));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 161, 45, 70));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 149, 38, 101));
	hurtBoxes.push_back(sf::IntRect(187, 168, 32, 21));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 59, 27));
	hurtBoxes.push_back(sf::IntRect(150, 175, 43, 89));
	temp->AddHurtBoxes(9, hurtBoxes);
	animManager.AddAnimation(BACK_JUMP, temp);

	// SUPER_JUMP
	temp = new Animation(charPath, JUMP, 10, false);
	temp->AddFrameFunction(0, do_super_jump);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(155, 157, 31, 97));
	temp->AddBoundBox(3, sf::IntRect(163, 157, 27, 72));
	temp->AddBoundBox(4, sf::IntRect(167, 170, 34, 45));
	temp->AddBoundBox(7, sf::IntRect(166, 170, 37, 45));
	temp->AddBoundBox(8, sf::IntRect(160, 158, 33, 72));
	temp->AddBoundBox(9, sf::IntRect(159, 157, 29, 90));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 40, 124));
	hurtBoxes.push_back(sf::IntRect(129, 175, 80, 40));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 40, 115));
	hurtBoxes.push_back(sf::IntRect(129, 175, 80, 40));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 149, 38, 101));
	hurtBoxes.push_back(sf::IntRect(187, 185, 32, 21));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 161, 45, 70));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 149, 38, 101));
	hurtBoxes.push_back(sf::IntRect(187, 168, 32, 21));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 149, 59, 27));
	hurtBoxes.push_back(sf::IntRect(150, 175, 43, 89));
	temp->AddHurtBoxes(9, hurtBoxes);
	animManager.AddAnimation(SUPER_JUMP, temp);
	basicCommands.AddCommand("28", SUPER_JUMP);

	// FALLING
	temp = new Animation(charPath, FALLING, 1, true);
	temp->AddFrameFunction(0, reset_to_idle);
	temp->AddBoundBox(0, sf::IntRect(150, 149, 50, 97));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(149, 141, 56, 126));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(FALLING, temp);

	// CROUCH
	temp = new Animation(charPath, CROUCH, 1, true);
	temp->AddFrameFunction(0, reset_to_idle);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(157, 200, 50, 70));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 199, 60, 71));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(CROUCH, temp);

	// Blocking
	temp = new Animation(charPath, BLOCK, 2, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(147, 171, 50, 100));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(148, 169, 59, 52));
	hurtBoxes.push_back(sf::IntRect(144, 221, 65, 50));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(148, 169, 53, 52));
	hurtBoxes.push_back(sf::IntRect(144, 221, 65, 50));
	temp->AddHurtBoxes(1, hurtBoxes);
	animManager.AddAnimation(BLOCK, temp);

	// C.Block
	temp = new Animation(charPath, C_BLOCK, 2, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(155, 198, 50, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 199, 59, 74));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(C_BLOCK, temp);

	// J.Block
	temp = new Animation(charPath, J_BLOCK, 2, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(157, 156, 45, 82));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 100));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 155, 50, 100));
	temp->AddHurtBoxes(1, hurtBoxes);
	animManager.AddAnimation(J_BLOCK, temp);

	// FORWARD THROW
	temp = new Animation(charPath, FORWARD_THROW, 8, false);
	temp->SetFramesAtSprite(0, 10);
	temp->AddDamageInfo(new DamageInfo(50000, 400, 13, 0, 0, 0, sf::Vector2f(0, 0), DamageScale::HeavyScale, HitSparkType::Heavy, false, AdditionalEffect::Hard_KnockDown, sf::Vector2f(4.f, -7.f)));
	temp->AddFrameFunction(0, do_forward_throw);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(5, do_throw_damage);
	temp->AddBoundBox(0, sf::IntRect(162, 166, 41, 105));
	animManager.AddAnimation(FORWARD_THROW, temp);

	// BACK THROW
	temp = new Animation(charPath, BACK_THROW, 15, false);
	temp->SetFramesAtSprite(0, 10);
	temp->AddDamageInfo(new DamageInfo(50000, 400, 13, 0, 0, 0, sf::Vector2f(0, 0), DamageScale::HeavyScale, HitSparkType::Nothing, false, AdditionalEffect::Hard_KnockDown, sf::Vector2f(-7.f, -10.f)));
	temp->AddFrameFunction(0, do_back_throw);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(8, do_throw_damage);
	temp->AddBoundBox(0, sf::IntRect(164, 170, 50, 101));
	animManager.AddAnimation(BACK_THROW, temp);

	// L
	temp = new Animation(charPath, L, 5, false);
	temp->AddDamageInfo(new DamageInfo(50000, 400, 13, 11, 6, 1, sf::Vector2f(1.5f, 0.f), DamageScale::LightScale, HitSparkType::Light));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[5]{ 5, 3, 3, 3, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(1, sf::IntRect(191, 174, 64, 28));
	temp->AddHitBox(2, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 172, 45, 100));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 163, 41, 71));
	hurtBoxes.push_back(sf::IntRect(142, 232, 77, 40));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 163, 47, 71));
	hurtBoxes.push_back(sf::IntRect(142, 232, 77, 40));
	hurtBoxes.push_back(sf::IntRect(198, 176, 54, 23));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 163, 47, 71));
	hurtBoxes.push_back(sf::IntRect(142, 232, 77, 40));
	hurtBoxes.push_back(sf::IntRect(198, 176, 41, 23));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 163, 47, 71));
	hurtBoxes.push_back(sf::IntRect(142, 232, 76, 40));
	hurtBoxes.push_back(sf::IntRect(198, 176, 29, 23));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 163, 47, 71));
	hurtBoxes.push_back(sf::IntRect(142, 232, 76, 40));
	hurtBoxes.push_back(sf::IntRect(198, 171, 19, 24));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(L, temp);

	// c.L
	temp = new Animation(charPath, C_L, 6, false);
	temp->AddDamageInfo(new DamageInfo(45000, 360, 14, 12, 6, 0, sf::Vector2f(1.5f, 0.f), DamageScale::LightScale, HitSparkType::Light));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[6]{ 5, 2, 4, 3, 2, 2 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(1, sf::IntRect(174, 241, 72, 31));
	temp->AddHitBox(2, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(152, 201, 50, 73));
	temp->AddBoundBox(4, sf::IntRect(155, 201, 50, 73));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(149, 201, 55, 73));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 201, 36, 73));
	hurtBoxes.push_back(sf::IntRect(180, 236, 65, 36));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 201, 36, 73));
	hurtBoxes.push_back(sf::IntRect(180, 226, 43, 48));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 201, 55, 73));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 201, 55, 73));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(C_L, temp);

	// j.L
	temp = new Animation(charPath, J_L, 5, false);
	temp->AddDamageInfo(new DamageInfo(55000, 440, 14, 12, 6, 1, sf::Vector2f(0.5f, 0.f), DamageScale::LightScale, HitSparkType::Light));
	temp->AddFrameFunction(0, do_attack);
	framesPerSprite = new int[5]{ 3, 3, 13, 3, 2 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(167, 185, 50, 38));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(160, 159, 50, 77));
	temp->AddBoundBox(2, sf::IntRect(137, 159, 50, 77));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 158, 56, 79));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(132, 155, 47, 96));
	hurtBoxes.push_back(sf::IntRect(176, 190, 39, 29));
	temp->AddHurtBoxes(2, hurtBoxes);
	animManager.AddAnimation(J_L, temp);

	// M
	temp = new Animation(charPath, M, 7, false);
	temp->AddDamageInfo(new DamageInfo(75000, 600, 18, 16, 8, 1, sf::Vector2f(1.5f, 0.f), DamageScale::MediumScale, HitSparkType::Medium));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[7]{ 3, 5, 3, 5, 5, 5, 6 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(209, 183, 58, 40));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(167, 170, 37, 102));
	temp->AddBoundBox(2, sf::IntRect(173, 170, 37, 102));
	temp->AddBoundBox(3, sf::IntRect(179, 170, 37, 102));
	temp->AddBoundBox(4, sf::IntRect(176, 170, 37, 102));
	temp->AddBoundBox(5, sf::IntRect(167, 170, 37, 102));
	temp->AddBoundBox(6, sf::IntRect(163, 170, 37, 102));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(164, 162, 45, 76));
	hurtBoxes.push_back(sf::IntRect(147, 223, 78, 49));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(169, 162, 45, 76));
	hurtBoxes.push_back(sf::IntRect(147, 223, 78, 49));
	hurtBoxes.push_back(sf::IntRect(211, 187, 50, 28));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(181, 162, 48, 110));
	hurtBoxes.push_back(sf::IntRect(147, 223, 38, 49));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(177, 162, 48, 110));
	hurtBoxes.push_back(sf::IntRect(147, 223, 33, 49));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(164, 164, 45, 61));
	hurtBoxes.push_back(sf::IntRect(147, 223, 78, 49));
	hurtBoxes.push_back(sf::IntRect(205, 184, 27, 17));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 162, 45, 64));
	hurtBoxes.push_back(sf::IntRect(143, 223, 78, 49));
	hurtBoxes.push_back(sf::IntRect(198, 177, 29, 23));
	temp->AddHurtBoxes(6, hurtBoxes);
	animManager.AddAnimation(M, temp);

	// c.M
	temp = new Animation(charPath, C_M, 9, false);
	temp->AddDamageInfo(new DamageInfo(68000, 544, 18, 16, 8, 0, sf::Vector2f(1.5f, 0.f), DamageScale::MediumScale, HitSparkType::Medium));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_c_m);
	temp->AddFrameFunction(3, stop_x_movement);
	framesPerSprite = new int[9]{ 5, 3, 3, 4, 3, 3, 3, 3, 3 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(218, 231, 66, 42));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(172, 195, 55, 79));
	temp->AddBoundBox(7, sf::IntRect(157, 195, 55, 79));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(180, 192, 70, 26));
	hurtBoxes.push_back(sf::IntRect(156, 217, 72, 57));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(180, 192, 55, 26));
	hurtBoxes.push_back(sf::IntRect(174, 217, 53, 62));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(173, 205, 54, 68));
	hurtBoxes.push_back(sf::IntRect(224, 236, 58, 36));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(173, 205, 54, 68));
	hurtBoxes.push_back(sf::IntRect(224, 236, 45, 36));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(170, 192, 58, 85));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 192, 52, 81));
	temp->AddHurtBoxes(7, hurtBoxes);
	animManager.AddAnimation(C_M, temp);

	// j.M
	temp = new Animation(charPath, J_M, 7, false);
	temp->AddDamageInfo(new DamageInfo(6000, 480, 18, 16, 6, 1, sf::Vector2f(0.5f, 0.f), DamageScale::MediumScale, HitSparkType::Medium));
	temp->AddFrameFunction(0, do_attack);
	framesPerSprite = new int[7]{ 5, 4, 5, 4, 4, 4, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(205, 173, 50, 29));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(151, 150, 42, 89));
	temp->AddBoundBox(1, sf::IntRect(159, 150, 42, 89));
	temp->AddBoundBox(2, sf::IntRect(157, 150, 42, 89));
	temp->AddBoundBox(4, sf::IntRect(160, 150, 42, 89));
	temp->AddBoundBox(5, sf::IntRect(157, 150, 42, 89));
	temp->AddBoundBox(6, sf::IntRect(158, 150, 42, 89));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(147, 141, 50, 103));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 148, 50, 95));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 155, 50, 68));
	hurtBoxes.push_back(sf::IntRect(203, 174, 50, 25));
	hurtBoxes.push_back(sf::IntRect(134, 216, 23, 39));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 155, 50, 75));
	hurtBoxes.push_back(sf::IntRect(203, 170, 47, 15));
	hurtBoxes.push_back(sf::IntRect(135, 214, 23, 39));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(163, 141, 50, 76));
	hurtBoxes.push_back(sf::IntRect(130, 212, 39, 41));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 147, 57, 79));
	hurtBoxes.push_back(sf::IntRect(130, 219, 28, 31));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 148, 63, 89));
	hurtBoxes.push_back(sf::IntRect(137, 224, 18, 31));
	temp->AddHurtBoxes(6, hurtBoxes);
	animManager.AddAnimation(J_M, temp);

	// H
	temp = new Animation(charPath, H, 9, false);
	temp->AddDamageInfo(new DamageInfo(90000, 760, 17, 19, 10, 1, sf::Vector2f(1.5f, 0.f), DamageScale::HeavyScale, HitSparkType::Heavy));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_h);
	temp->AddFrameFunction(3, stop_x_movement);
	framesPerSprite = new int[9]{ 4, 3, 3, 3, 5, 4, 4, 4, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(3, sf::IntRect(208, 168, 63, 33));
	temp->AddHitBox(4, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(148, 167, 47, 104));
	temp->AddBoundBox(1, sf::IntRect(155, 167, 47, 104));
	temp->AddBoundBox(2, sf::IntRect(164, 167, 47, 104));
	temp->AddBoundBox(4, sf::IntRect(176, 167, 47, 104));
	temp->AddBoundBox(5, sf::IntRect(173, 167, 47, 104));
	temp->AddBoundBox(6, sf::IntRect(170, 167, 47, 104));
	temp->AddBoundBox(7, sf::IntRect(161, 167, 47, 104));
	temp->AddBoundBox(8, sf::IntRect(157, 167, 47, 104));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(146, 165, 50, 105));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 165, 50, 105));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(163, 165, 50, 72));
	hurtBoxes.push_back(sf::IntRect(148, 225, 79, 50));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(146, 168, 121, 30));
	hurtBoxes.push_back(sf::IntRect(148, 197, 83, 74));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 168, 112, 30));
	hurtBoxes.push_back(sf::IntRect(148, 197, 83, 74));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 168, 105, 30));
	hurtBoxes.push_back(sf::IntRect(148, 197, 83, 74));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(169, 165, 50, 105));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(163, 165, 43, 105));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 165, 50, 105));
	temp->AddHurtBoxes(8, hurtBoxes);
	animManager.AddAnimation(H, temp);

	// c.H
	temp = new Animation(charPath, C_H, 12, false);
	temp->AddDamageInfo(new DamageInfo(80000, 640, 26, 22, 10, 0, sf::Vector2f(1.5f, 0.f), DamageScale::HeavyScale, HitSparkType::Heavy, false, AdditionalEffect::Hard_KnockDown, sf::Vector2f(0.f, -5.f)));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[12]{ 3, 3, 2, 2, 3, 4, 4, 4, 4, 4, 3, 3 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(4, sf::IntRect(233, 222, 74, 50));
	temp->AddHitBox(5, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(155, 211, 50, 59));
	temp->AddBoundBox(2, sf::IntRect(176, 211, 50, 59));
	temp->AddBoundBox(3, sf::IntRect(193, 198, 50, 73));
	temp->AddBoundBox(4, sf::IntRect(205, 211, 50, 59));
	temp->AddBoundBox(6, sf::IntRect(168, 211, 50, 59));
	temp->AddBoundBox(7, sf::IntRect(155, 211, 50, 59));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 206, 58, 64));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 186, 58, 84));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 182, 83, 89));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(188, 196, 58, 75));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(197, 206, 58, 64));
	hurtBoxes.push_back(sf::IntRect(250, 240, 50, 31));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 206, 71, 64));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 206, 58, 64));
	hurtBoxes.push_back(sf::IntRect(114, 232, 39, 50));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 206, 58, 64));
	hurtBoxes.push_back(sf::IntRect(116, 244, 39, 28));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 206, 58, 64));
	temp->AddHurtBoxes(9, hurtBoxes);
	animManager.AddAnimation(C_H, temp);

	// j.H
	temp = new Animation(charPath, J_H, 7, false);
	temp->AddDamageInfo(new DamageInfo(90000, 720, 26, 24, 6, 1, sf::Vector2f(1.f, 0.f), DamageScale::HeavyScale, HitSparkType::Heavy));
	temp->AddFrameFunction(0, do_attack);
	framesPerSprite = new int[7]{ 3, 3, 3, 4, 8, 8, 7 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(3, sf::IntRect(169, 188, 56, 80));
	temp->AddHitBox(4, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(162, 157, 46, 90));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 152, 55, 94));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 157, 55, 78));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 152, 55, 86));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(130, 148, 74, 75));
	hurtBoxes.push_back(sf::IntRect(181, 196, 39, 66));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(142, 148, 74, 63));
	hurtBoxes.push_back(sf::IntRect(181, 209, 31, 46));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(143, 152, 71, 87));
	temp->AddHurtBoxes(6, hurtBoxes);
	animManager.AddAnimation(J_H, temp);

	// Sp
	temp = new Animation(charPath, SP, 11, false);
	temp->AddDamageInfo(new DamageInfo(100000, 800, 22, 21, 10, 1, sf::Vector2f(1.f, -14.f), DamageScale::SpecialScale, HitSparkType::Heavy));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(4, check_super_jump);
	framesPerSprite = new int[11]{ 3, 3, 3, 2, 3, 5, 4, 4, 3, 3, 3 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(3, sf::IntRect(175, 133, 55, 139));
	temp->AddHitBox(5, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(143, 207, 50, 64));
	temp->AddBoundBox(3, sf::IntRect(143, 176, 50, 95));
	temp->AddBoundBox(7, sf::IntRect(143, 197, 50, 75));
	temp->AddBoundBox(8, sf::IntRect(151, 188, 50, 85));
	temp->AddBoundBox(9, sf::IntRect(153, 188, 50, 85));
	temp->AddBoundBox(10, sf::IntRect(153, 188, 50, 84));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(119, 210, 69, 68));
	hurtBoxes.push_back(sf::IntRect(186, 239, 29, 36));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(119, 210, 81, 68));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(119, 189, 85, 88));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(136, 169, 69, 102));
	hurtBoxes.push_back(sf::IntRect(200, 139, 25, 34));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(136, 169, 69, 102));
	hurtBoxes.push_back(sf::IntRect(200, 151, 25, 34));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(136, 169, 56, 102));
	hurtBoxes.push_back(sf::IntRect(192, 170, 25, 44));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(119, 199, 86, 73));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(141, 177, 69, 96));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(147, 177, 61, 96));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(148, 167, 57, 105));
	temp->AddHurtBoxes(10, hurtBoxes);
	animManager.AddAnimation(SP, temp);

	// j.Sp
	temp = new Animation(charPath, J_SP, 8, false);
	temp->AddDamageInfo(new DamageInfo(95000, 760, 39, 37, 10, 1, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::Screen_Fly)); //, sf::Vector2f(2.f, 10.f)));
	temp->AddFrameFunction(0, do_attack);
	framesPerSprite = new int[8]{ 3, 3, 3, 8, 5, 5, 4, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(3, sf::IntRect(158, 149, 44, 93));
	temp->AddHitBox(4, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(149, 155, 44, 93));
	temp->AddBoundBox(2, sf::IntRect(155, 155, 44, 93));
	temp->AddBoundBox(4, sf::IntRect(162, 155, 44, 93));
	temp->AddBoundBox(5, sf::IntRect(158, 155, 44, 93));
	temp->AddBoundBox(6, sf::IntRect(157, 155, 44, 93));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(146, 154, 50, 93));
	hurtBoxes.push_back(sf::IntRect(135, 226, 13, 30));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(140, 148, 62, 99));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 140, 46, 108));
	hurtBoxes.push_back(sf::IntRect(195, 146, 33, 16));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 140, 40, 108));
	hurtBoxes.push_back(sf::IntRect(195, 142, 37, 42));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 140, 43, 108));
	hurtBoxes.push_back(sf::IntRect(195, 196, 48, 36));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 154, 55, 93));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 154, 50, 98));
	temp->AddHurtBoxes(7, hurtBoxes);
	animManager.AddAnimation(J_SP, temp);

	// SPECIALS
	// CROSS CUTTER
	temp = new Animation(charPath, CROSS_CUTTER, 9, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(3, spawn_cross_cutter);
	framesPerSprite = new int[9]{ 4, 3, 3, 6, 6, 6, 6, 6, 5 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddBoundBox(0, sf::IntRect(168, 171, 39, 99));
	temp->AddBoundBox(2, sf::IntRect(179, 164, 39, 106));
	temp->AddBoundBox(3, sf::IntRect(189, 197, 45, 73));
	temp->AddBoundBox(6, sf::IntRect(176, 189, 45, 81));
	temp->AddBoundBox(7, sf::IntRect(176, 171, 39, 99));
	temp->AddBoundBox(8, sf::IntRect(168, 171, 39, 99));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(170, 171, 42, 50));
	hurtBoxes.push_back(sf::IntRect(147, 220, 68, 50));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 144, 42, 76));
	hurtBoxes.push_back(sf::IntRect(152, 205, 68, 68));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(181, 151, 33, 69));
	hurtBoxes.push_back(sf::IntRect(159, 212, 68, 58));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(187, 195, 52, 75));
	hurtBoxes.push_back(sf::IntRect(141, 230, 49, 40));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(170, 186, 59, 84));
	hurtBoxes.push_back(sf::IntRect(138, 240, 34, 33));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(175, 171, 42, 50));
	hurtBoxes.push_back(sf::IntRect(147, 220, 74, 50));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(167, 168, 48, 53));
	hurtBoxes.push_back(sf::IntRect(147, 220, 68, 50));
	temp->AddHurtBoxes(8, hurtBoxes);
	animManager.AddAnimation(CROSS_CUTTER, temp);
	specialCommands.AddCommand("236l", CROSS_CUTTER);
	specialCommands.AddCommand("236m", CROSS_CUTTER);
	specialCommands.AddCommand("236h", CROSS_CUTTER);

	// SHADOW WAVE
	temp = new Animation(charPath, SHADOW_WAVE, 9, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(2, spawn_shadow_wave);
	temp->AddBoundBox(0, sf::IntRect(152, 157, 35, 81));
	temp->AddBoundBox(1, sf::IntRect(152, 157, 35, 91));
	temp->AddBoundBox(2, sf::IntRect(159, 157, 35, 91));
	temp->AddBoundBox(3, sf::IntRect(165, 157, 35, 81));
	temp->AddBoundBox(4, sf::IntRect(157, 157, 42, 81));
	temp->AddBoundBox(8, sf::IntRect(157, 172, 42, 76));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(147, 150, 45, 101));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(137, 147, 57, 62));
	hurtBoxes.push_back(sf::IntRect(135, 207, 42, 53));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(144, 139, 54, 120));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 150, 50, 77));
	hurtBoxes.push_back(sf::IntRect(203, 167, 44, 13));
	hurtBoxes.push_back(sf::IntRect(134, 220, 41, 26));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 150, 57, 87));
	hurtBoxes.push_back(sf::IntRect(126, 220, 32, 33));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 152, 60, 87));
	hurtBoxes.push_back(sf::IntRect(126, 220, 32, 33));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 166, 47, 81));
	hurtBoxes.push_back(sf::IntRect(133, 227, 24, 33));
	hurtBoxes.push_back(sf::IntRect(176, 168, 46, 29));
	temp->AddHurtBoxes(8, hurtBoxes);
	animManager.AddAnimation(SHADOW_WAVE, temp);
	airSpecialCommands.AddCommand("236l", SHADOW_WAVE);
	airSpecialCommands.AddCommand("236m", SHADOW_WAVE);
	airSpecialCommands.AddCommand("236h", SHADOW_WAVE);

	// LIGHTNING UPPER
	temp = new Animation(charPath, LIGHTNING_UPPER, 11, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(4, spawn_lightning_upper);
	framesPerSprite = new int[11]{ 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddBoundBox(0, sf::IntRect(158, 180, 45, 91));
	temp->AddBoundBox(1, sf::IntRect(165, 180, 45, 91));
	temp->AddBoundBox(3, sf::IntRect(170, 180, 45, 91));
	temp->AddBoundBox(4, sf::IntRect(170, 157, 45, 114));
	temp->AddBoundBox(8, sf::IntRect(158, 180, 45, 91));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 174, 71, 28));
	hurtBoxes.push_back(sf::IntRect(141, 202, 73, 69));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(182, 179, 48, 25));
	hurtBoxes.push_back(sf::IntRect(147, 202, 73, 69));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(167, 165, 48, 38));
	hurtBoxes.push_back(sf::IntRect(145, 202, 73, 69));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 155, 65, 116));
	hurtBoxes.push_back(sf::IntRect(222, 182, 26, 29));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 155, 65, 116));
	hurtBoxes.push_back(sf::IntRect(184, 121, 32, 36));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(164, 155, 52, 116));
	hurtBoxes.push_back(sf::IntRect(177, 129, 35, 29));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 155, 55, 116));
	hurtBoxes.push_back(sf::IntRect(169, 141, 39, 18));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 157, 53, 113));
	hurtBoxes.push_back(sf::IntRect(146, 238, 17, 33));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 164, 53, 107));
	hurtBoxes.push_back(sf::IntRect(142, 238, 17, 33));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 174, 71, 28));
	hurtBoxes.push_back(sf::IntRect(141, 202, 73, 69));
	temp->AddHurtBoxes(10, hurtBoxes);
	animManager.AddAnimation(LIGHTNING_UPPER, temp);
	specialCommands.AddCommand("421l", LIGHTNING_UPPER);
	specialCommands.AddCommand("421m", LIGHTNING_UPPER);
	specialCommands.AddCommand("421h", LIGHTNING_UPPER);
	specialCommands.AddCommand("4121l", LIGHTNING_UPPER); // Account for extra inputs
	specialCommands.AddCommand("4121m", LIGHTNING_UPPER); // Account for extra inputs
	specialCommands.AddCommand("4121h", LIGHTNING_UPPER); // Account for extra inputs
	specialCommands.AddCommand("41214l", LIGHTNING_UPPER); // Account for extra inputs
	specialCommands.AddCommand("41214m", LIGHTNING_UPPER); // Account for extra inputs
	specialCommands.AddCommand("41214h", LIGHTNING_UPPER); // Account for extra inputs

	// SHADOW CUT KICK
	temp = new Animation(charPath, SHADOW_CUT_KICK, 16, false);
	temp->SetFramesOfAnimation(48);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(3, do_shadow_cut_kick);
	temp->AddDamageInfo(new DamageInfo(100000, 800, 7, 1, 6, 1, sf::Vector2f(1.f, -10.f), DamageScale::SpecialScale, HitSparkType::Medium));
	temp->AddHitBox(3, sf::IntRect(185, 118, 81, 149));
	temp->AddHitBox(4, sf::IntRect(167, 118, 94, 107));
	temp->AddHitBox(5, sf::IntRect(133, 119, 122, 86));
	temp->AddHitBox(6, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(160, 172, 39, 84));
	//temp->AddBoundBox(0, sf::IntRect(173, 186, 50, 86));
	//temp->AddBoundBox(1, sf::IntRect(138, 206, 50, 65));
	//temp->AddBoundBox(2, sf::IntRect(152, 197, 50, 75));
	//temp->AddBoundBox(3, sf::IntRect(158, 173, 42, 78));
	//temp->AddBoundBox(6, sf::IntRect(152, 174, 50, 59));
	//temp->AddBoundBox(7, sf::IntRect(157, 170, 50, 63));
	//temp->AddBoundBox(9, sf::IntRect(133, 186, 61, 33));
	//temp->AddBoundBox(11, sf::IntRect(152, 184, 50, 47));
	//temp->AddBoundBox(12, sf::IntRect(158, 184, 50, 59));
	//temp->AddBoundBox(13, sf::IntRect(162, 186, 35, 67));
	//temp->AddBoundBox(14, sf::IntRect(160, 172, 39, 84));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(177, 178, 53, 94));
	hurtBoxes.push_back(sf::IntRect(142, 232, 38, 41));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(119, 199, 89, 72));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(132, 190, 53, 82));
	hurtBoxes.push_back(sf::IntRect(181, 205, 34, 42));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(140, 178, 50, 87));
	hurtBoxes.push_back(sf::IntRect(181, 140, 38, 41));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 178, 50, 87));
	hurtBoxes.push_back(sf::IntRect(145, 140, 38, 41));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(136, 167, 98, 71));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 138, 53, 101));
	hurtBoxes.push_back(sf::IntRect(123, 167, 38, 41));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(108, 178, 113, 52));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(169, 170, 55, 50));
	hurtBoxes.push_back(sf::IntRect(125, 206, 47, 48));
	temp->AddHurtBoxes(11, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(169, 170, 55, 50));
	hurtBoxes.push_back(sf::IntRect(142, 214, 45, 54));
	temp->AddHurtBoxes(12, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(169, 162, 50, 32));
	hurtBoxes.push_back(sf::IntRect(154, 193, 38, 80));
	temp->AddHurtBoxes(13, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 149, 56, 37));
	hurtBoxes.push_back(sf::IntRect(154, 185, 40, 87));
	temp->AddHurtBoxes(14, hurtBoxes);
	animManager.AddAnimation(SHADOW_CUT_KICK, temp);
	specialCommands.AddCommand("214l", SHADOW_CUT_KICK);
	specialCommands.AddCommand("214m", SHADOW_CUT_KICK);
	specialCommands.AddCommand("214h", SHADOW_CUT_KICK);
	airSpecialCommands.AddCommand("214l", SHADOW_CUT_KICK);
	airSpecialCommands.AddCommand("214m", SHADOW_CUT_KICK);
	airSpecialCommands.AddCommand("214h", SHADOW_CUT_KICK);

	// SHADOW BREAKER
	temp = new Animation(charPath, SHADOW_BREAKER, 27, false);
	//temp->SetFramesOfAnimation(54);
	framesPerSprite = new int[27] { 2, 2, 10, 1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(2, do_shadow_breaker);
	temp->AddDamageInfo(new DamageInfo(110000, 1, 20, 31, 12, 1, sf::Vector2f(1.f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::Hard_KnockDown, sf::Vector2f(1.f, -1.f)));
	temp->AddBoundBox(0, sf::IntRect(161, 196, 50, 76));
	temp->AddBoundBox(1, sf::IntRect(169, 196, 41, 76));
	temp->AddBoundBox(2, sf::IntRect(154, 162, 39, 85));
	temp->AddBoundBox(3, sf::IntRect(157, 162, 39, 85));
	temp->AddBoundBox(8, sf::IntRect(157, 189, 39, 72));
	temp->AddBoundBox(13, sf::IntRect(157, 189, 39, 66));
	temp->AddBoundBox(26, sf::IntRect(157, 178, 39, 66));
	temp->AddHitBox(9, sf::IntRect(215, 222, 56, 32));
	temp->AddHitBox(11, sf::IntRect(0, 0, 0, 0));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 191, 56, 79));
	hurtBoxes.push_back(sf::IntRect(141, 248, 24, 24));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(168, 167, 63, 103));
	hurtBoxes.push_back(sf::IntRect(146, 242, 24, 30));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 154, 49, 81));
	hurtBoxes.push_back(sf::IntRect(130, 176, 31, 97));
	hurtBoxes.push_back(sf::IntRect(200, 200, 45, 34));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(140, 153, 54, 81));
	hurtBoxes.push_back(sf::IntRect(125, 231, 31, 35));
	hurtBoxes.push_back(sf::IntRect(194, 200, 45, 44));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 153, 54, 95));
	hurtBoxes.push_back(sf::IntRect(125, 236, 31, 24));
	hurtBoxes.push_back(sf::IntRect(194, 246, 26, 24));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 170, 48, 107));
	hurtBoxes.push_back(sf::IntRect(131, 218, 29, 24));
	hurtBoxes.push_back(sf::IntRect(205, 191, 26, 61));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 170, 56, 83));
	hurtBoxes.push_back(sf::IntRect(132, 214, 29, 58));
	temp->AddHurtBoxes(13, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 176, 56, 79));
	hurtBoxes.push_back(sf::IntRect(132, 214, 29, 58));
	temp->AddHurtBoxes(25, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(147, 170, 56, 61));
	hurtBoxes.push_back(sf::IntRect(139, 223, 41, 31));
	temp->AddHurtBoxes(26, hurtBoxes);
	animManager.AddAnimation(SHADOW_BREAKER, temp);
	specialCommands.AddCommand("623l", SHADOW_BREAKER);
	specialCommands.AddCommand("623m", SHADOW_BREAKER);
	specialCommands.AddCommand("623h", SHADOW_BREAKER);
	specialCommands.AddCommand("6323l", SHADOW_BREAKER); // Account for extra inputs
	specialCommands.AddCommand("6323m", SHADOW_BREAKER); // Account for extra inputs
	specialCommands.AddCommand("6323h", SHADOW_BREAKER); // Account for extra inputs
	specialCommands.AddCommand("63236l", SHADOW_BREAKER); // Account for extra inputs
	specialCommands.AddCommand("63236m", SHADOW_BREAKER); // Account for extra inputs
	specialCommands.AddCommand("63236h", SHADOW_BREAKER); // Account for extra inputs

	// HYPER COMMANDS
	// SUPER CROSS CUTTER
	temp = new Animation(charPath, CROSS_CUTTER, 9, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_hyper_attack);
	temp->AddFrameFunction(3, spawn_super_cross_cutter);
	temp->AddBoundBox(0, sf::IntRect(168, 171, 39, 99));
	temp->AddBoundBox(2, sf::IntRect(179, 164, 39, 106));
	temp->AddBoundBox(3, sf::IntRect(189, 197, 45, 73));
	temp->AddBoundBox(6, sf::IntRect(176, 189, 45, 81));
	temp->AddBoundBox(7, sf::IntRect(176, 171, 39, 99));
	temp->AddBoundBox(8, sf::IntRect(168, 171, 39, 99));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(170, 171, 42, 50));
	hurtBoxes.push_back(sf::IntRect(147, 220, 68, 50));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 144, 42, 76));
	hurtBoxes.push_back(sf::IntRect(152, 205, 68, 68));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(181, 151, 33, 69));
	hurtBoxes.push_back(sf::IntRect(159, 212, 68, 58));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(187, 195, 52, 75));
	hurtBoxes.push_back(sf::IntRect(141, 230, 49, 40));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(170, 186, 59, 84));
	hurtBoxes.push_back(sf::IntRect(138, 240, 34, 33));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(175, 171, 42, 50));
	hurtBoxes.push_back(sf::IntRect(147, 220, 74, 50));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(167, 168, 48, 53));
	hurtBoxes.push_back(sf::IntRect(147, 220, 68, 50));
	temp->AddHurtBoxes(8, hurtBoxes);
	animManager.AddAnimation(SUPER_CROSS_CUTTER, temp);
	hyperCommands.AddCommand("236lm", SUPER_CROSS_CUTTER, ONE_SPECIAL_BAR);
	hyperCommands.AddCommand("236lh", SUPER_CROSS_CUTTER, ONE_SPECIAL_BAR);
	hyperCommands.AddCommand("236mh", SUPER_CROSS_CUTTER, ONE_SPECIAL_BAR);

	// SUPER LIGHTNING UPPER
	temp = new Animation(charPath, LIGHTNING_UPPER, 11, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_hyper_attack);
	temp->AddFrameFunction(4, spawn_super_lightning_upper);
	temp->AddBoundBox(0, sf::IntRect(158, 180, 45, 91));
	temp->AddBoundBox(1, sf::IntRect(165, 180, 45, 91));
	temp->AddBoundBox(3, sf::IntRect(170, 180, 45, 91));
	temp->AddBoundBox(4, sf::IntRect(170, 157, 45, 114));
	temp->AddBoundBox(8, sf::IntRect(158, 180, 45, 91));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 174, 71, 28));
	hurtBoxes.push_back(sf::IntRect(141, 202, 73, 69));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(182, 179, 48, 25));
	hurtBoxes.push_back(sf::IntRect(147, 202, 73, 69));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(167, 165, 48, 38));
	hurtBoxes.push_back(sf::IntRect(145, 202, 73, 69));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 155, 65, 116));
	hurtBoxes.push_back(sf::IntRect(222, 182, 26, 29));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 155, 65, 116));
	hurtBoxes.push_back(sf::IntRect(184, 121, 32, 36));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(164, 155, 52, 116));
	hurtBoxes.push_back(sf::IntRect(177, 129, 35, 29));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 155, 55, 116));
	hurtBoxes.push_back(sf::IntRect(169, 141, 39, 18));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 157, 53, 113));
	hurtBoxes.push_back(sf::IntRect(146, 238, 17, 33));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 164, 53, 107));
	hurtBoxes.push_back(sf::IntRect(142, 238, 17, 33));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 174, 71, 28));
	hurtBoxes.push_back(sf::IntRect(141, 202, 73, 69));
	temp->AddHurtBoxes(10, hurtBoxes);
	animManager.AddAnimation(SUPER_LIGHTNING_UPPER, temp);
	hyperCommands.AddCommand("421lm", SUPER_LIGHTNING_UPPER, ONE_SPECIAL_BAR);
	hyperCommands.AddCommand("421lh", SUPER_LIGHTNING_UPPER, ONE_SPECIAL_BAR);
	hyperCommands.AddCommand("421mh", SUPER_LIGHTNING_UPPER, ONE_SPECIAL_BAR);
	hyperCommands.AddCommand("4121lm", SUPER_LIGHTNING_UPPER, ONE_SPECIAL_BAR); // Account for extra inputs
	hyperCommands.AddCommand("4121lh", SUPER_LIGHTNING_UPPER, ONE_SPECIAL_BAR); // Account for extra inputs
	hyperCommands.AddCommand("4121mh", SUPER_LIGHTNING_UPPER, ONE_SPECIAL_BAR); // Account for extra inputs
	hyperCommands.AddCommand("41214lm", SUPER_LIGHTNING_UPPER, ONE_SPECIAL_BAR); // Account for extra inputs
	hyperCommands.AddCommand("41214lh", SUPER_LIGHTNING_UPPER, ONE_SPECIAL_BAR); // Account for extra inputs
	hyperCommands.AddCommand("41214mh", SUPER_LIGHTNING_UPPER, ONE_SPECIAL_BAR); // Account for extra inputs

	// DOUBLE SHADOW CUT KICK
	temp = new Animation(charPath, DOUBLE_SHADOW_CUT_KICK, 12, false, DOUBLE_SHADOW_CUT_KICK_2);
	temp->SetFramesOfAnimation(24);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(0, do_hyper_attack);
	temp->AddFrameFunction(3, do_double_shadow_cut_kick_pt1);
	temp->AddDamageInfo(new DamageInfo(100000, 1, 20, 31, 0, 1, sf::Vector2f(1.f, -9.f), DamageScale::SpecialScale, HitSparkType::Heavy));
	temp->AddHitBox(4, sf::IntRect(205, 122, 59, 141));
	temp->AddHitBox(6, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(159, 166, 50, 106));
	temp->AddBoundBox(1, sf::IntRect(168, 176, 50, 95));
	temp->AddBoundBox(2, sf::IntRect(171, 188, 48, 84));
	temp->AddBoundBox(3, sf::IntRect(177, 184, 50, 85));
	temp->AddBoundBox(6, sf::IntRect(170, 166, 50, 106));
	temp->AddBoundBox(11, sf::IntRect(149, 166, 50, 106));
	temp->AddBoundBox(12, sf::IntRect(145, 196, 47, 77));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(143, 232, 71, 43));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 172, 55, 70));
	hurtBoxes.push_back(sf::IntRect(167, 219, 58, 52));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 189, 63, 83));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(173, 174, 53, 95));
	hurtBoxes.push_back(sf::IntRect(219, 143, 49, 37));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(171, 144, 53, 111));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 165, 67, 73));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 155, 48, 84));
	hurtBoxes.push_back(sf::IntRect(134, 210, 22, 48));
	temp->AddHurtBoxes(11, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 193, 48, 62));
	hurtBoxes.push_back(sf::IntRect(138, 254, 18, 18));
	temp->AddHurtBoxes(12, hurtBoxes);
	animManager.AddAnimation(DOUBLE_SHADOW_CUT_KICK, temp);
	hyperCommands.AddCommand("214lm", DOUBLE_SHADOW_CUT_KICK, THREE_SPECIAL_BARS);
	hyperCommands.AddCommand("214lh", DOUBLE_SHADOW_CUT_KICK, THREE_SPECIAL_BARS);
	hyperCommands.AddCommand("214mh", DOUBLE_SHADOW_CUT_KICK, THREE_SPECIAL_BARS);
	airHyperCommands.AddCommand("214lm", DOUBLE_SHADOW_CUT_KICK, THREE_SPECIAL_BARS);
	airHyperCommands.AddCommand("214lh", DOUBLE_SHADOW_CUT_KICK, THREE_SPECIAL_BARS);
	airHyperCommands.AddCommand("214mh", DOUBLE_SHADOW_CUT_KICK, THREE_SPECIAL_BARS);

	// DOUBLE SHADOW CUT KICK 2
	temp = new Animation(charPath, DOUBLE_SHADOW_CUT_KICK_2, 14, false, DOUBLE_SHADOW_CUT_KICK_3);
	temp->SetFramesOfAnimation(28);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(3, do_double_shadow_cut_kick_pt2);
	temp->AddDamageInfo(new DamageInfo(100000, 1, 30, 31, 0, 1, sf::Vector2f(1.f, -9.f), DamageScale::SpecialScale, HitSparkType::Heavy));
	temp->AddHitBox(4, sf::IntRect(182, 124, 83, 142));
	temp->AddHitBox(6, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(155, 186, 50, 89));
	temp->AddBoundBox(1, sf::IntRect(139, 200, 50, 71));
	temp->AddBoundBox(2, sf::IntRect(146, 186, 50, 86));
	temp->AddBoundBox(3, sf::IntRect(159, 166, 50, 106));
	temp->AddBoundBox(5, sf::IntRect(151, 166, 50, 106));
	temp->AddBoundBox(6, sf::IntRect(159, 166, 50, 106));
	hurtBoxes.push_back(sf::IntRect(145, 193, 48, 62));
	hurtBoxes.push_back(sf::IntRect(138, 254, 18, 18));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(140, 198, 66, 33));
	hurtBoxes.push_back(sf::IntRect(140, 231, 48, 43));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 184, 53, 51));
	hurtBoxes.push_back(sf::IntRect(142, 232, 71, 43));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(118, 197, 91, 73));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(132, 188, 78, 83));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 174, 53, 90));
	hurtBoxes.push_back(sf::IntRect(184, 137, 39, 38));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 177, 53, 80));
	hurtBoxes.push_back(sf::IntRect(143, 136, 39, 43));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(137, 165, 58, 72));
	hurtBoxes.push_back(sf::IntRect(192, 166, 40, 22));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(125, 178, 77, 60));
	hurtBoxes.push_back(sf::IntRect(171, 137, 32, 43));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(112, 183, 109, 48));
	temp->AddHurtBoxes(10, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 171, 64, 45));
	hurtBoxes.push_back(sf::IntRect(123, 216, 49, 39));
	temp->AddHurtBoxes(12, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(168, 165, 49, 53));
	hurtBoxes.push_back(sf::IntRect(145, 218, 43, 48));
	temp->AddHurtBoxes(13, hurtBoxes);
	animManager.AddAnimation(DOUBLE_SHADOW_CUT_KICK_2, temp);

	// DOUBLE SHADOW CUT KICK 3
	temp = new Animation(charPath, DOUBLE_SHADOW_CUT_KICK_3, 14, false);
	temp->SetFramesOfAnimation(28);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, do_double_shadow_cut_kick_pt1);
	temp->AddDamageInfo(new DamageInfo(70000, 800, 33, 31, 0, 1, sf::Vector2f(2.5f, 4.f), DamageScale::SpecialScale, HitSparkType::Nothing));
	temp->AddHitBox(4, sf::IntRect(173, 157, 107, 78));
	temp->AddHitBox(5, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(6, sf::IntRect(196, 181, 110, 78));
	temp->AddHitBox(7, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(144, 149, 50, 97));
	temp->AddBoundBox(2, sf::IntRect(157, 149, 39, 97));
	temp->AddBoundBox(3, sf::IntRect(163, 149, 39, 86));
	temp->AddBoundBox(4, sf::IntRect(166, 149, 39, 86));
	temp->AddBoundBox(12, sf::IntRect(161, 161, 39, 86));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(142, 150, 53, 100));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(138, 146, 53, 112));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 141, 44, 119));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 150, 50, 87));
	hurtBoxes.push_back(sf::IntRect(204, 166, 43, 19));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 145, 55, 91));
	hurtBoxes.push_back(sf::IntRect(123, 215, 40, 38));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 159, 57, 38));
	hurtBoxes.push_back(sf::IntRect(132, 196, 71, 51));
	temp->AddHurtBoxes(12, hurtBoxes);
	animManager.AddAnimation(DOUBLE_SHADOW_CUT_KICK_3, temp);

	// SUPPORT ANIMATIONS
	temp = new Animation(charPath, IDLE, 1, true);
	animManager.AddAnimation(SUPPORT_IDLE, temp);

	// SUPPORT ENTER
	temp = new Animation(charPath, FALLING, 1, true);
	temp->AddBoundBox(0, sf::IntRect(150, 149, 50, 97));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(149, 141, 56, 126));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(SUPPORT_ENTER, temp);

	// SUPPORT
	temp = new Animation(charPath, LIGHTNING_UPPER, 11, false, SUPPORT_END);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(4, spawn_lightning_upper);
	framesPerSprite = new int[11]{ 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddBoundBox(0, sf::IntRect(158, 180, 45, 91));
	temp->AddBoundBox(1, sf::IntRect(165, 180, 45, 91));
	temp->AddBoundBox(3, sf::IntRect(170, 180, 45, 91));
	temp->AddBoundBox(4, sf::IntRect(170, 157, 45, 114));
	temp->AddBoundBox(8, sf::IntRect(158, 180, 45, 91));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 174, 71, 28));
	hurtBoxes.push_back(sf::IntRect(141, 202, 73, 69));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(182, 179, 48, 25));
	hurtBoxes.push_back(sf::IntRect(147, 202, 73, 69));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(167, 165, 48, 38));
	hurtBoxes.push_back(sf::IntRect(145, 202, 73, 69));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 155, 65, 116));
	hurtBoxes.push_back(sf::IntRect(222, 182, 26, 29));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 155, 65, 116));
	hurtBoxes.push_back(sf::IntRect(184, 121, 32, 36));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(164, 155, 52, 116));
	hurtBoxes.push_back(sf::IntRect(177, 129, 35, 29));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 155, 55, 116));
	hurtBoxes.push_back(sf::IntRect(169, 141, 39, 18));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 157, 53, 113));
	hurtBoxes.push_back(sf::IntRect(146, 238, 17, 33));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 164, 53, 107));
	hurtBoxes.push_back(sf::IntRect(142, 238, 17, 33));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 174, 71, 28));
	hurtBoxes.push_back(sf::IntRect(141, 202, 73, 69));
	temp->AddHurtBoxes(10, hurtBoxes);
	animManager.AddAnimation(SUPPORT, temp);

	// SUPPORT END
	temp = new Animation(charPath, SUPPORT_END, 10, false, SUPPORT_EXIT);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(156, 173, 44, 98));
	animManager.AddAnimation(SUPPORT_END, temp);

	// SUPPORT EXIT
	temp = new Animation(charPath, FALLING, 1, true);
	temp->AddFrameFunction(0, do_support_exit);
	temp->AddBoundBox(0, sf::IntRect(150, 149, 50, 97));
	animManager.AddAnimation(SUPPORT_EXIT, temp);

	// CROSS ASSAULT
	temp = new Animation(charPath, CROSS_ASSAULT, 1, true);
	temp->AddDamageInfo(new DamageInfo(90000, 760, 17, 19, 10, 1, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::Knockdown, sf::Vector2f(7.f, -10.f)));
	temp->AddHitBox(0, sf::IntRect(166, 199, 54, 60));
	temp->AddBoundBox(0, sf::IntRect(152, 155, 50, 79));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(139, 152, 70, 50));
	hurtBoxes.push_back(sf::IntRect(173, 200, 43, 57));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(CROSS_ASSAULT, temp);

	// CROSS ASSAULT LANDING
	temp = new Animation(charPath, SUPPORT_END, 10, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(0, do_attack);
	temp->AddBoundBox(0, sf::IntRect(156, 173, 44, 98));
	animManager.AddAnimation(CROSS_ASSAULT_LANDING, temp);

	// SNAP BACK
	temp = new Animation(charPath, H, 9, false);
	temp->AddDamageInfo(new DamageInfo(90000, 760, 1, 19, 10, 0, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::Snap_Back));
	temp->AddFrameFunction(0, do_hyper_attack);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddHitBox(3, sf::IntRect(208, 168, 63, 33));
	temp->AddHitBox(4, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(148, 167, 47, 104));
	temp->AddBoundBox(1, sf::IntRect(155, 167, 47, 104));
	temp->AddBoundBox(2, sf::IntRect(164, 167, 47, 104));
	temp->AddBoundBox(4, sf::IntRect(176, 167, 47, 104));
	temp->AddBoundBox(5, sf::IntRect(173, 167, 47, 104));
	temp->AddBoundBox(6, sf::IntRect(170, 167, 47, 104));
	temp->AddBoundBox(7, sf::IntRect(161, 167, 47, 104));
	temp->AddBoundBox(8, sf::IntRect(157, 167, 47, 104));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(146, 165, 50, 105));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 165, 50, 105));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(163, 165, 50, 72));
	hurtBoxes.push_back(sf::IntRect(148, 225, 79, 50));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(146, 168, 121, 30));
	hurtBoxes.push_back(sf::IntRect(148, 197, 83, 74));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 168, 112, 30));
	hurtBoxes.push_back(sf::IntRect(148, 197, 83, 74));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 168, 105, 30));
	hurtBoxes.push_back(sf::IntRect(148, 197, 83, 74));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(169, 165, 50, 105));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(163, 165, 43, 105));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 165, 50, 105));
	temp->AddHurtBoxes(8, hurtBoxes);
	animManager.AddAnimation(SNAP_BACK, temp);
	hyperCommands.AddCommand("236p", SNAP_BACK, ONE_SPECIAL_BAR);

	// SNAP BACK HURT
	temp = new Animation(charPath, AIR_HURT, 1, true);
	temp->AddFrameFunction(0, check_for_snap_back_swap);
	temp->AddBoundBox(0, sf::IntRect(161, 169, 50, 93));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 162, 63, 102));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(SNAP_BACK_HURT, temp);

	// THROWN ANIMS
	charPath += "Thrown/";

	// RYU FORWARD THROWN
	temp = new Animation(charPath, RYU_FORWARD_THROWN, 4, false);
	framesPerSprite = new int[4]{ 10, 4, 4, 10 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(157, 169, 0, 0));
	animManager.AddAnimation(RYU_FORWARD_THROWN, temp);

	// RYU BACK THROWN
	temp = new Animation(charPath, RYU_BACK_THROWN, 3, false);
	temp->SetFramesAtSprite(0, 14);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(157, 169, 0, 0));
	animManager.AddAnimation(RYU_BACK_THROWN, temp);

	// KYOSUKE FORWARD THROWN
	temp = new Animation(charPath, KYOSUKE_FORWARD_THROWN, 1, false);
	temp->SetFramesOfAnimation(30);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(157, 169, 0, 0));
	animManager.AddAnimation(KYOSUKE_FORWARD_THROWN, temp);

	// KYOSUKE FORWARD THROWN
	temp = new Animation(charPath, KYOSUKE_BACK_THROWN, 3, false);
	framesPerSprite = new int[3]{ 30, 4, 10 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(157, 169, 0, 0));
	animManager.AddAnimation(KYOSUKE_BACK_THROWN, temp);

	lightningUpperBase = new LightningUpper();
	lightningUpperBase->Load();

	shadowWaveBase = new ShadowWave();
	shadowWaveBase->Load();

	superLightningUpperBase = new SuperLightningUpper();
	superLightningUpperBase->Load();

	crossCutterBase = new CrossCutter();
	crossCutterBase->Load();

	crossCutterAltBase = new CrossCutter();
	crossCutterAltBase->SetYScale(-1);
	crossCutterAltBase->Load();

	Fighter::Load();
}

void Kyosuke::CheckActionInput(Controls* playerControls) {
	Fighter::CheckActionInput(playerControls);
}

void Kyosuke::CheckOnHit() {
	if (SHADOW_BREAKER == animManager.GetCurrentAnimationName()) {
		velocity.x = 0.f;
		velocity.y = -5.f;
	}
}

void Kyosuke::UpdateAnimations() {
	Fighter::UpdateAnimations();
}

void Kyosuke::DoForwardThrow() {
	DoAttack();
	//enemyMain->SetPosition(position);
	enemyMain->BeThrown(KYOSUKE_FORWARD_THROWN, xScale * -1);
}

void Kyosuke::DoBackThrow() {
	DoAttack();
	enemyMain->SetPosition(position);
	enemyMain->BeThrown(KYOSUKE_BACK_THROWN, xScale);
}

bool Kyosuke::CallEnumFunction(int functionEnum)
{
	if (Fighter::CallEnumFunction(functionEnum))
		return false;

	switch (functionEnum) {
	case do_c_m:
		DoC_M();
		return true;
	case do_h:
		DoH();
		return true;
	case spawn_lightning_upper:
		SpawnLightningUpper();
		return true;
	case do_shadow_breaker:
		DoShadowBreaker();
		return true;
	case do_shadow_cut_kick:
		DoShadowCutKick();
		return true;
	case spawn_shadow_wave:
		SpawnShadowWave();
		return true;
	case spawn_super_lightning_upper:
		SpawnSuperLightningUpper();
		return true;
	case do_double_shadow_cut_kick_pt1:
		DoDoubleShadowCutKickPt1();
		return true;
	case do_double_shadow_cut_kick_pt2:
		DoDoubleShadowCutKickPt2();
		return true;
	case spawn_cross_cutter:
		SpawnCrossCutter();
		return true;
	case spawn_super_cross_cutter:
		SpawnSuperCrossCutter();
		return true;
	default:
		std::cout << "Function: " << functionEnum << " not found" << std::endl;
		return false;
	}

}

void Kyosuke::SpawnLightningUpper() {
	LightningUpper* newLightningUpper = new LightningUpper(*lightningUpperBase);
	newLightningUpper->SetXScale(xScale);

	if (!isSupport) {
		if (heavyAttack)
			newLightningUpper->SetPosition(sf::Vector2f(position.x + (225.f * xScale), position.y));
		else if (mediumAttack)
			newLightningUpper->SetPosition(sf::Vector2f(position.x + (150.f * xScale), position.y));
		else
			newLightningUpper->SetPosition(sf::Vector2f(position.x + (75.f * xScale), position.y));
	}
	else
		newLightningUpper->SetPosition(sf::Vector2f(position.x + (75.f * xScale), position.y));

	spawnedProjectiles.push_back(newLightningUpper);
}

void Kyosuke::DoShadowBreaker() {
	inAir = true;
	disableActionUntilGrounded = true;

	if (heavyAttack) {
		velocity.x = 5.f * xScale;
		velocity.y = -7.f;
	}
	else if (mediumAttack) {
		velocity.x = 4.f * xScale;
		velocity.y = -6.f;
	}
	else if (lightAttack) {
		velocity.x = 3.f * xScale;
		velocity.y = -5.f;
	}
}

void Kyosuke::DoShadowCutKick() {
	inAir = true;
	disableActionUntilGrounded = true;

	velocity.x = 0.5f * xScale;
	if (heavyAttack)
		velocity.y = -11.f;
	else if (mediumAttack)
		velocity.y = -9.f;
	else if (lightAttack)
		velocity.y = -7.f;
}

void Kyosuke::SpawnShadowWave() {
	velocity.y = -5.f;

	ShadowWave* newShadowWave = new ShadowWave(*shadowWaveBase);
	newShadowWave->SetXScale(xScale);
	newShadowWave->SetPosition(position);

	spawnedProjectiles.push_back(newShadowWave);
}

void Kyosuke::SpawnSuperLightningUpper() {
	SuperLightningUpper* newSLU = new SuperLightningUpper(*superLightningUpperBase);
	newSLU->SetXScale(xScale);
	newSLU->SetPosition(sf::Vector2f(position.x + (100 * xScale), position.y));

	spawnedProjectiles.push_back(newSLU);
}

void Kyosuke::DoDoubleShadowCutKickPt1() {
	inAir = true;
	disableActionUntilGrounded = true;

	velocity.x = 1.f * xScale;
	velocity.y = -7.f;
}

void Kyosuke::DoDoubleShadowCutKickPt2() {
	velocity.y = -7.f;
}

void Kyosuke::SpawnCrossCutter() {
	CrossCutter* newCC = new CrossCutter(*crossCutterBase);
	newCC->SetXScale(xScale);
	newCC->SetPosition(sf::Vector2f(position.x, position.y));
	spawnedProjectiles.push_back(newCC);

	CrossCutter* newCC2 = new CrossCutter(*crossCutterAltBase);
	newCC2->SetYScale(-1);
	newCC2->SetXScale(xScale);
	newCC2->SetPosition(sf::Vector2f(position.x, position.y));
	spawnedProjectiles.push_back(newCC2);

	if (heavyAttack) {
		newCC->SetVelocity(sf::Vector2f(2.5f * xScale, -2.f));
		newCC2->SetVelocity(sf::Vector2f(2.5f * xScale, 2.f));
	}
	else if (mediumAttack) {
		newCC->SetVelocity(sf::Vector2f(2.f * xScale, -2.5f));
		newCC2->SetVelocity(sf::Vector2f(2.f * xScale, 2.5f));
	}
	else if (lightAttack) {
		newCC->SetVelocity(sf::Vector2f(1.5f * xScale, -3.f));
		newCC2->SetVelocity(sf::Vector2f(1.5f * xScale, 3.f));
	}
}

void Kyosuke::SpawnSuperCrossCutter() {
	CrossCutter* newCC = new CrossCutter(*crossCutterBase);
	//newCC->SetYScale(-1);
	newCC->SetXScale(xScale);
	newCC->SetPosition(sf::Vector2f(position.x, position.y));
	newCC->SetVelocity(sf::Vector2f(1.5f * xScale, -2.5f));
	spawnedProjectiles.push_back(newCC);

	newCC = new CrossCutter(*crossCutterBase);
	//newCC->SetYScale(-1);
	newCC->SetXScale(xScale);
	newCC->SetPosition(sf::Vector2f(position.x, position.y));
	newCC->SetVelocity(sf::Vector2f(1.5f * xScale, -1.f));
	spawnedProjectiles.push_back(newCC);

	CrossCutter* newCC2 = new CrossCutter(*crossCutterAltBase);
	newCC2->SetYScale(-1);
	newCC2->SetXScale(xScale);
	newCC2->SetPosition(sf::Vector2f(position.x, position.y));
	newCC2->SetVelocity(sf::Vector2f(1.5f * xScale, 1.f));
	spawnedProjectiles.push_back(newCC2);

	newCC2 = new CrossCutter(*crossCutterAltBase);
	newCC2->SetYScale(-1);
	newCC2->SetXScale(xScale);
	newCC2->SetPosition(sf::Vector2f(position.x, position.y));
	newCC2->SetVelocity(sf::Vector2f(1.5f * xScale, 2.5f));
	spawnedProjectiles.push_back(newCC2);
}

void Kyosuke::SetColor(int colorNum) {
	if (2 == colorNum) {
		colorShader.setParameter("texture", sf::Shader::CurrentTexture);
		colorShader.setParameter("color1", 1.f, 1.f, 1.f);
		colorShader.setParameter("replace1", 0.322f, 0.322f, 0.969f);
		colorShader.setParameter("color2", 0.808f, 0.839f, 0.968f);
		colorShader.setParameter("replace2", 0.259f, 0.192f, 0.870f);
		colorShader.setParameter("color3", 0.580f, 0.611f, 0.776f);
		colorShader.setParameter("replace3", 0.224f, 0.129f, 0.678f);
		colorShader.setParameter("color4", 0.451f, 0.482f, 0.678f);
		colorShader.setParameter("replace4", 0.129f, 0.031f, 0.451f);
		colorShader.setParameter("color5", 0.647f, 0.f, 0.f);
		colorShader.setParameter("replace5", 0.549f, 0.678f, 0.549f);
		colorShader.setParameter("color6", 0.451f, 0.f, 0.f);
		colorShader.setParameter("replace6", 0.388f, 0.482f, 0.388f);
		colorShader.setParameter("color7", 0.223f, 0.223f, 0.321f);
		colorShader.setParameter("replace7", 0.580f, 0.192f, 0.450f);
	}
}

void Kyosuke::DoC_M() {
	velocity.x = 1.f * xScale;
}

void Kyosuke::DoH() {
	velocity.x = 1.f * xScale;
}