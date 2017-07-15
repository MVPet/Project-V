#include "Ryu.h"
#include "Controls.h"
#include <iostream>

Ryu::Ryu() {
}

Ryu::~Ryu() {
}

void Ryu::Load() {
	name = RYU;
	isPlayable = true;
	hunterStyle = true;
	center = sf::Vector2f(174, 210);
	maxHealth = 1300000;
	//maxHealth = 10;
	maxSpeed = 2.5f;

	Animation* temp;
	DamageInfo* dInfo;
	std::vector<sf::IntRect> hurtBoxes;
	int* framesPerSprite;
	std::string charPath = "Textures/Chars/" + name + "/";

	// Movement
	// IDLE	X
	temp = new Animation(charPath, IDLE, 7, true);
	temp->AddFrameFunction(0, reset_to_idle);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(156, 179, 40, 91));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 168, 46, 102));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(IDLE, temp);

	// WIN	X
	temp = new Animation(charPath, WIN, 4, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(3, start_end_countdown);
	temp->AddBoundBox(0, sf::IntRect(156, 179, 40, 91));
	animManager.AddAnimation(WIN, temp);

	// LOSE	X
	temp = new Animation(charPath, LOSE, 3, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(2, start_end_countdown);
	temp->AddBoundBox(0, sf::IntRect(156, 179, 40, 91));
	animManager.AddAnimation(LOSE, temp);

	// INTRO
	temp = new Animation(charPath, INTRO, 10, false, IDLE);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(9, intro_done);
	temp->AddBoundBox(0, sf::IntRect(157, 169, 50, 102));
	animManager.AddAnimation(INTRO, temp);

	// HURT	X
	temp = new Animation(charPath, HURT, 4, false, HURT_END);
	temp->AddFrameFunction(0, destroy_metsu_hadouken);
	temp->AddBoundBox(0, sf::IntRect(153, 185, 50, 85));
	temp->AddBoundBox(2, sf::IntRect(147, 185, 50, 85));
	temp->AddBoundBox(3, sf::IntRect(140, 185, 50, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 167, 48, 104));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(140, 167, 53, 104));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(133, 167, 57, 56));
	hurtBoxes.push_back(sf::IntRect(146, 220, 57, 50));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(121, 167, 57, 56));
	hurtBoxes.push_back(sf::IntRect(146, 220, 57, 50));
	temp->AddHurtBoxes(3, hurtBoxes);
	animManager.AddAnimation(HURT, temp);

	// HURT END	X
	temp = new Animation(charPath, HURT_END, 3, false);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[3]{ 2,2,2 };
	temp->AddBoundBox(0, sf::IntRect(153, 219, 50, 52));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(138, 167, 53, 104));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(142, 167, 53, 104));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 167, 53, 104));
	temp->AddHurtBoxes(2, hurtBoxes);
	animManager.AddAnimation(HURT_END, temp);

	// AIR HURT	X
	temp = new Animation(charPath, AIR_HURT, 2, false, AERIAL_RECOVERY);
	temp->AddFrameFunction(0, destroy_metsu_hadouken);
	temp->AddBoundBox(0, sf::IntRect(158, 162, 46, 76));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(135, 180, 84, 65));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(135, 180, 107, 59));
	temp->AddHurtBoxes(1, hurtBoxes);
	animManager.AddAnimation(AIR_HURT, temp);

	// AERIAL RECOVERY	X
	temp = new Animation(charPath, AERIAL_RECOVERY, 6, false);
	temp->SetFramesOfAnimation(12);
	temp->AddFrameFunction(0, do_aerial_recovery);
	temp->AddBoundBox(0, sf::IntRect(159, 162, 50, 50));
	temp->AddBoundBox(1, sf::IntRect(159, 162, 50, 58));
	temp->AddBoundBox(2, sf::IntRect(159, 162, 50, 50));
	temp->AddBoundBox(4, sf::IntRect(159, 162, 43, 79));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 169, 68, 50));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 157, 56, 68));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 169, 67, 50));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(143, 169, 68, 50));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 159, 50, 102));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 158, 56, 106));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(AERIAL_RECOVERY, temp);

	// CROUCH HURT	X
	temp = new Animation(charPath, CROUCH_HURT, 4, false, CROUCH_HURT_END);
	temp->AddBoundBox(0, sf::IntRect(153, 214, 50, 57));
	temp->AddBoundBox(1, sf::IntRect(148, 214, 50, 57));
	temp->AddBoundBox(2, sf::IntRect(143, 214, 50, 57));
	temp->AddBoundBox(3, sf::IntRect(139, 214, 50, 57));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(151, 199, 54, 75));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(140, 199, 61, 75));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(133, 199, 66, 75));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(126, 203, 67, 69));
	temp->AddHurtBoxes(3, hurtBoxes);
	animManager.AddAnimation(CROUCH_HURT, temp);

	// CROUCH HURT END	X
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

	// HARD KNOCKDOWN	X
	temp = new Animation(charPath, HARD_KNOCKDOWN, 3, false);
	temp->AddBoundBox(0, sf::IntRect(158, 162, 43, 50));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(129, 178, 107, 90));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(129, 195, 114, 40));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(129, 172, 107, 90));
	temp->AddHurtBoxes(2, hurtBoxes);
	animManager.AddAnimation(HARD_KNOCKDOWN, temp);

	// ON GROUND	X
	temp = new Animation(charPath, ON_GROUND, 7, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(153, 214, 50, 57));
	temp->AddBoundBox(2, sf::IntRect(145, 214, 63, 57));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 173, 63, 98));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(135, 202, 79, 69));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(121, 198, 125, 65));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(121, 205, 125, 65));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(121, 217, 125, 55));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(121, 224, 125, 51));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(ON_GROUND, temp);

	// GET UP	X
	temp = new Animation(charPath, GETUP, 5, false, IDLE);
	temp->SetFramesOfAnimation(15);
	temp->AddBoundBox(0, sf::IntRect(146, 219, 50, 52));
	temp->AddBoundBox(1, sf::IntRect(143, 214, 50, 57));
	temp->AddBoundBox(2, sf::IntRect(141, 188, 50, 83));
	temp->AddBoundBox(3, sf::IntRect(134, 199, 55, 71));
	temp->AddBoundBox(4, sf::IntRect(143, 214, 50, 57));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(138, 219, 67, 52));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(138, 192, 59, 81));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(136, 151, 60, 123));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(131, 177, 59, 96));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(134, 190, 63, 63));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(GETUP, temp);

	// BACK ROLL	X
	temp = new Animation(charPath, BACK_ROLL, 6, false, IDLE);
	temp->SetFramesOfAnimation(18);
	temp->AddFrameFunction(0, do_back_roll);
	temp->AddBoundBox(0, sf::IntRect(153, 214, 50, 57));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(120, 213, 102, 59));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(138, 192, 59, 81));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(136, 151, 60, 123));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(127, 174, 73, 99));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(134, 190, 63, 63));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(BACK_ROLL, temp);

	// FORWARD WALK	X
	temp = new Animation(charPath, FORWARD_WALK, 8, true);
	temp->AddBoundBox(0, sf::IntRect(154, 185, 45, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 166, 50, 105));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(FORWARD_WALK, temp);

	// BACK WALK	X
	temp = new Animation(charPath, BACK_WALK, 8, true);
	temp->AddBoundBox(0, sf::IntRect(158, 185, 44, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 169, 48, 103));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(BACK_WALK, temp);

	// FORWARD DASH	X
	temp = new Animation(charPath, FORWARD_DASH, 5, false);
	temp->AddFrameFunction(0, do_forward_dash);
	temp->AddBoundBox(0, sf::IntRect(156, 185, 50, 85));
	temp->AddBoundBox(1, sf::IntRect(161, 194, 54, 77));
	temp->AddBoundBox(3, sf::IntRect(153, 185, 50, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 175, 54, 97));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 184, 55, 65));
	hurtBoxes.push_back(sf::IntRect(130, 248, 103, 24));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 171, 53, 100));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 167, 52, 103));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(FORWARD_DASH, temp);
	basicCommands.AddCommand("66", FORWARD_DASH);

	// BACK DASH	X
	temp = new Animation(charPath, BACK_DASH, 4, false);
	temp->AddFrameFunction(0, do_back_dash);
	temp->AddBoundBox(0, sf::IntRect(161, 191, 39, 80));
	temp->AddBoundBox(1, sf::IntRect(147, 191, 49, 80));
	temp->AddBoundBox(3, sf::IntRect(154, 191, 42, 80));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 179, 43, 92));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 176, 53, 83));
	hurtBoxes.push_back(sf::IntRect(196, 232, 25, 39));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 179, 49, 92));
	temp->AddHurtBoxes(3, hurtBoxes);
	animManager.AddAnimation(BACK_DASH, temp);
	basicCommands.AddCommand("44", BACK_DASH);

	// JUMP	X
	temp = new Animation(charPath, JUMP, 7, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(1, do_jump);
	temp->AddBoundBox(0, sf::IntRect(158, 162, 43, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 146, 47, 123));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 153, 47, 108));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 161, 47, 81));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 161, 47, 73));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 161, 47, 81));
	temp->AddHurtBoxes(6, hurtBoxes);
	animManager.AddAnimation(JUMP, temp);

	// FORWARD JUMP	X
	temp = new Animation(charPath, FORWARD_JUMP, 8, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(1, do_jump);
	temp->AddBoundBox(0, sf::IntRect(155, 162, 43, 82));
	temp->AddBoundBox(5, sf::IntRect(155, 162, 43, 53));
	temp->AddBoundBox(7, sf::IntRect(155, 162, 43, 82));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 156, 43, 117));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(147, 166, 69, 56));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 156, 43, 117));
	temp->AddHurtBoxes(7, hurtBoxes);
	animManager.AddAnimation(FORWARD_JUMP, temp);

	// BACKWARD JUMP	X
	temp = new Animation(charPath, BACK_JUMP, 9, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(1, do_jump);
	temp->AddBoundBox(0, sf::IntRect(155, 162, 43, 82));
	temp->AddBoundBox(2, sf::IntRect(155, 162, 43, 53));
	temp->AddBoundBox(6, sf::IntRect(155, 162, 43, 82));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 156, 43, 117));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(147, 166, 69, 56));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 156, 43, 117));
	temp->AddHurtBoxes(6, hurtBoxes);
	animManager.AddAnimation(BACK_JUMP, temp);

	// SUPER_JUMP	X
	temp = new Animation(charPath, SUPER_JUMP, 7, false);
	temp->AddFrameFunction(0, do_super_jump);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(158, 162, 43, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 146, 47, 123));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 153, 47, 108));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 161, 47, 81));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 161, 47, 73));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 161, 47, 81));
	temp->AddHurtBoxes(6, hurtBoxes);
	animManager.AddAnimation(SUPER_JUMP, temp);
	basicCommands.AddCommand("28", SUPER_JUMP);

	// FALLING	X
	temp = new Animation(charPath, FALLING, 1, true);
	temp->AddFrameFunction(0, reset_to_idle);
	temp->AddBoundBox(0, sf::IntRect(158, 162, 43, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 155, 45, 105));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(FALLING, temp);

	// CROUCH	X
	temp = new Animation(charPath, CROUCH, 1, true);
	temp->AddFrameFunction(0, reset_to_idle);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(153, 214, 50, 57));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 200, 52, 71));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(CROUCH, temp);

	// Blocking	X
	temp = new Animation(charPath, BLOCK, 2, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(153, 214, 50, 57));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 166, 54, 105));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(BLOCK, temp);

	// C.Block	X
	temp = new Animation(charPath, C_BLOCK, 2, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(153, 214, 45, 57));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 203, 53, 71));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(C_BLOCK, temp);

	// J.Block	X
	temp = new Animation(charPath, J_BLOCK, 2, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(164, 162, 43, 69));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 160, 48, 91));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(J_BLOCK, temp);


	// FORWARD THROW	X
	// Need to set the position when dealing damage otherwise it looks weird
	temp = new Animation(charPath, FORWARD_THROW, 9, false);
	temp->SetFramesAtSprite(0, 10);
	temp->AddDamageInfo(new DamageInfo(50000, 400, 13, 0, 0, 0, sf::Vector2f(0, 0), DamageScale::SpecialScale, HitSparkType::Nothing, false, AdditionalEffect::Hard_KnockDown, sf::Vector2f(5.f, 5.f)));
	temp->AddFrameFunction(0, do_forward_throw);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(5, do_throw_damage);
	temp->AddBoundBox(0, sf::IntRect(153, 166, 0, 0));
	animManager.AddAnimation(FORWARD_THROW, temp);

	// BACK THROW	X
	temp = new Animation(charPath, BACK_THROW, 10, false);
	temp->SetFramesAtSprite(0, 10);
	temp->AddDamageInfo(new DamageInfo(50000, 400, 13, 0, 0, 0, sf::Vector2f(0, 0), DamageScale::SpecialScale, HitSparkType::Nothing, false, AdditionalEffect::Hard_KnockDown, sf::Vector2f(-5.5f, -7.f)));
	temp->AddFrameFunction(0, do_back_throw);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(3, do_throw_damage);
	temp->AddBoundBox(0, sf::IntRect(153, 166, 0, 0));
	animManager.AddAnimation(BACK_THROW, temp);

	// Normals
	// L	X
	temp = new Animation(charPath, L, 5, false);
	temp->AddDamageInfo(new DamageInfo(50000, 400, 13, 11, 6, 1, sf::Vector2f(1.5f, 0.f), DamageScale::LightScale, HitSparkType::Light));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[5]{ 2, 3, 3, 5, 5 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(195, 173, 55, 23));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(153, 219, 50, 52));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 167, 52, 104));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 167, 52, 104));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 167, 52, 104));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 167, 52, 104));
	hurtBoxes.push_back(sf::IntRect(211, 174, 33, 17));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(163, 167, 52, 104));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(L, temp);
	
	// c.L	X
	temp = new Animation(charPath, C_L, 6, false);
	temp->AddDamageInfo(new DamageInfo(45000, 360, 14, 12, 6, 0, sf::Vector2f(1.5f, 0.f), DamageScale::LightScale, HitSparkType::Light));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[6]{ 2, 3, 2, 4, 4, 3 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(182, 249, 75, 24));
	temp->AddHitBox(4, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(157, 214, 46, 57));
	temp->AddBoundBox(1, sf::IntRect(161, 214, 50, 57));
	temp->AddBoundBox(5, sf::IntRect(157, 214, 46, 57));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 206, 51, 69));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 209, 52, 66));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 209, 47, 66));
	hurtBoxes.push_back(sf::IntRect(207, 251, 48, 24));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 209, 52, 66));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 206, 51, 69));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(C_L, temp);

	// j.L	X
	temp = new Animation(charPath, J_L, 5, false);
	temp->AddDamageInfo(new DamageInfo(55000, 440, 14, 12, 6, 1, sf::Vector2f(0.5f, 0.f), DamageScale::LightScale, HitSparkType::Light));
	temp->AddFrameFunction(0, do_attack);
	framesPerSprite = new int[5]{ 3, 3, 7, 6, 5 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(176, 190, 39, 50));
	temp->AddHitBox(4, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 162, 43, 60));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 159, 46, 73));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 159, 55, 73));
	temp->AddHurtBoxes(1, hurtBoxes);
	animManager.AddAnimation(J_L, temp);

	// M	X
	temp = new Animation(charPath, M, 10, false);
	temp->AddDamageInfo(new DamageInfo(75000, 600, 18, 16, 8, 1, sf::Vector2f(1.f, 0.f), DamageScale::MediumScale, HitSparkType::Medium));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(2, do_m);
	temp->AddFrameFunction(4, stop_x_movement);
	framesPerSprite = new int[10]{ 2, 3, 3, 3, 4, 4, 4, 3, 3, 3 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(3, sf::IntRect(206, 175, 43, 59));
	temp->AddHitBox(7, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(159, 185, 43, 85));
	temp->AddBoundBox(1, sf::IntRect(169, 185, 43, 85));
	temp->AddBoundBox(3, sf::IntRect(184, 185, 43, 85));
	temp->AddBoundBox(7, sf::IntRect(169, 185, 43, 85));
	temp->AddBoundBox(8, sf::IntRect(159, 185, 43, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 162, 50, 109));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(171, 162, 50, 109));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(179, 162, 45, 109));
	hurtBoxes.push_back(sf::IntRect(221, 178, 27, 52));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(179, 162, 45, 109));
	hurtBoxes.push_back(sf::IntRect(221, 184, 22, 60));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(171, 162, 50, 109));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 167, 50, 104));
	temp->AddHurtBoxes(8, hurtBoxes);
	animManager.AddAnimation(M, temp);

	// c.M	X
	temp = new Animation(charPath, C_M, 7, false);
	temp->AddDamageInfo(new DamageInfo(68000, 544, 18, 16, 8, 0, sf::Vector2f(1.f, 0.f), DamageScale::MediumScale, HitSparkType::Medium));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(2, do_c_m);
	temp->AddFrameFunction(4, stop_x_movement);
	framesPerSprite = new int[7]{ 6, 2, 3, 4, 4, 4, 7 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(176, 245, 87, 30));
	temp->AddHitBox(6, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(149, 214, 50, 57));
	temp->AddBoundBox(1, sf::IntRect(153, 219, 50, 52));
	temp->AddBoundBox(2, sf::IntRect(153, 219, 68, 52));
	temp->AddBoundBox(5, sf::IntRect(153, 219, 50, 52));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(143, 207, 62, 64));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 215, 52, 60));
	hurtBoxes.push_back(sf::IntRect(197, 249, 67, 26));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(143, 207, 62, 64));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(140, 204, 70, 66));
	temp->AddHurtBoxes(6, hurtBoxes);
	animManager.AddAnimation(C_M, temp);

	// j.M	X
	temp = new Animation(charPath, J_M, 4, false);
	temp->AddDamageInfo(new DamageInfo(6000, 480, 18, 16, 6, 1, sf::Vector2f(0.5f, 0.f), DamageScale::MediumScale, HitSparkType::Medium));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(2, reset_hit);
	framesPerSprite = new int[4]{ 9, 2, 2, 19 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(1, sf::IntRect(180, 161, 38, 33));
	temp->AddHitBox(2, sf::IntRect(180, 123, 38, 57));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 162, 43, 64));
	temp->AddBoundBox(2, sf::IntRect(150, 162, 43, 64));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 154, 50, 89));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(147, 154, 50, 89));
	hurtBoxes.push_back(sf::IntRect(176, 124, 26, 30));
	temp->AddHurtBoxes(2, hurtBoxes);
	animManager.AddAnimation(J_M, temp);

	// H	X
	temp = new Animation(charPath, H, 7, false);
	temp->AddDamageInfo(new DamageInfo(90000, 760, 17, 19, 12, 1, sf::Vector2f(1.3f, 0.f), DamageScale::HeavyScale, HitSparkType::Heavy));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(2, do_h);
	temp->AddFrameFunction(4, stop_x_movement);
	framesPerSprite = new int[7]{ 5, 5, 3, 6, 5, 5, 5 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(205, 176, 51, 24));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(161, 185, 50, 85));
	temp->AddBoundBox(1, sf::IntRect(165, 185, 50, 85));
	temp->AddBoundBox(2, sf::IntRect(173, 185, 50, 85));
	temp->AddBoundBox(4, sf::IntRect(167, 185, 50, 85));
	temp->AddBoundBox(5, sf::IntRect(165, 185, 50, 85));
	temp->AddBoundBox(6, sf::IntRect(161, 185, 50, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 168, 54, 102));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 168, 57, 102));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(166, 168, 57, 102));
	hurtBoxes.push_back(sf::IntRect(223, 178, 31, 20));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(166, 168, 52, 102));
	hurtBoxes.push_back(sf::IntRect(217, 179, 28, 20));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 168, 57, 102));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 168, 57, 102));
	temp->AddHurtBoxes(6, hurtBoxes);
	animManager.AddAnimation(H, temp);

	// c.H	X
	temp = new Animation(charPath, C_H, 9, false);
	temp->AddDamageInfo(new DamageInfo(80000, 640, 26, 22, 12, 0, sf::Vector2f(1.3f, 0.f), DamageScale::HeavyScale, HitSparkType::Heavy, false, AdditionalEffect::Hard_KnockDown, sf::Vector2f(0.f, -5.f)));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[9]{ 5, 5, 4, 4, 4, 4, 4, 5, 5 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(178, 242, 84, 34));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(165, 214, 43, 57));
	temp->AddBoundBox(5, sf::IntRect(154, 214, 43, 57));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 204, 54, 67));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 204, 54, 67));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 208, 54, 63));
	hurtBoxes.push_back(sf::IntRect(212, 250, 45, 22));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 204, 54, 67));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 205, 46, 66));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(C_H, temp);

	// j.H	X
	temp = new Animation(charPath, J_H, 6, false);
	temp->AddDamageInfo(new DamageInfo(90000, 720, 26, 24, 6, 1, sf::Vector2f(1.f, 0.f), DamageScale::HeavyScale, HitSparkType::Heavy));
	temp->AddFrameFunction(0, do_attack);
	framesPerSprite = new int[6]{ 4, 5, 4, 8, 8, 7 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(195, 187, 50, 26));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 162, 43, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 157, 43, 111));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 157, 45, 111));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 157, 45, 111));
	hurtBoxes.push_back(sf::IntRect(204, 190, 37, 23));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 157, 50, 111));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 157, 50, 89));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 157, 46, 38));
	hurtBoxes.push_back(sf::IntRect(158, 195, 59, 50));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(J_H, temp);

	// Sp	X
	temp = new Animation(charPath, SP, 9, false);
	temp->AddDamageInfo(new DamageInfo(100000, 800, 22, 21, 10, 1, sf::Vector2f(0.5f, -14.f), DamageScale::SpecialScale, HitSparkType::Heavy));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(4, check_super_jump);
	framesPerSprite = new int[9]{ 5, 4, 2, 3, 5, 5, 4, 4, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(195, 175, 50, 94));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(166, 185, 50, 85));
	temp->AddBoundBox(8, sf::IntRect(161, 185, 45, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 180, 61, 90));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 169, 61, 101));
	hurtBoxes.push_back(sf::IntRect(191, 146, 27, 24));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 169, 61, 101));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 169, 53, 101));
	temp->AddHurtBoxes(8, hurtBoxes);
	animManager.AddAnimation(SP, temp);

	// j.Sp	X
	temp = new Animation(charPath, J_SP, 5, false);
	temp->AddDamageInfo(new DamageInfo(95000, 760, 39, 37, 10, 1, sf::Vector2f(1.f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::Screen_Fly));
	temp->AddFrameFunction(0, do_attack);
	framesPerSprite = new int[5]{ 5, 4, 8, 12, 7 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(176, 200, 73, 33));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 162, 43, 60));
	temp->AddBoundBox(2, sf::IntRect(158, 162, 49, 60));
	temp->AddBoundBox(4, sf::IntRect(158, 162, 43, 60));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(149, 154, 58, 86));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(149, 154, 58, 77));
	hurtBoxes.push_back(sf::IntRect(207, 202, 37, 28));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(149, 154, 58, 76));
	hurtBoxes.push_back(sf::IntRect(207, 204, 34, 23));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(149, 154, 58, 86));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(J_SP, temp);

	// Command Normals	
	// Collarbone Breaker	X
	temp = new Animation(charPath, COLLARBONE_BREAKER, 14, false);
	temp->AddDamageInfo(new DamageInfo(35000, 280, 25, 27, 12, 1, sf::Vector2f(1.f, 0.f), DamageScale::MediumScale, HitSparkType::Medium));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(6, reset_hit);
	framesPerSprite = new int[14]{ 4, 4, 4, 4, 4, 3, 2, 2, 4, 4, 4, 4, 3, 3 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(5, sf::IntRect(193, 171, 51, 62));
	temp->AddHitBox(6, sf::IntRect(206, 186, 51, 84));
	temp->AddHitBox(7, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(164, 180, 41, 90));
	temp->AddBoundBox(4, sf::IntRect(174, 180, 41, 90));
	temp->AddBoundBox(5, sf::IntRect(181, 180, 41, 90));
	temp->AddBoundBox(6, sf::IntRect(190, 180, 41, 90));
	temp->AddBoundBox(10, sf::IntRect(181, 180, 41, 90));
	temp->AddBoundBox(12, sf::IntRect(161, 180, 41, 90));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 168, 56, 102));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(165, 168, 56, 102));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(172, 168, 56, 102));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(172, 183, 69, 87));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(172, 183, 56, 87));
	temp->AddHurtBoxes(10, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(172, 183, 50, 87));
	temp->AddHurtBoxes(11, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 168, 47, 102));
	temp->AddHurtBoxes(12, hurtBoxes);
	animManager.AddAnimation(COLLARBONE_BREAKER, temp);

	// Roundhouse Kick	X
	temp = new Animation(charPath, ROUNDHOUSE_KICK, 11, false);
	temp->AddDamageInfo(new DamageInfo(95000, 760, 17, 19, 10, 1, sf::Vector2f(1.5f, 0.f), DamageScale::HeavyScale, HitSparkType::Heavy));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[11]{ 4, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(4, sf::IntRect(211, 160, 50, 50));
	temp->AddHitBox(5, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 185, 45, 85));
	temp->AddBoundBox(1, sf::IntRect(162, 185, 45, 85));
	temp->AddBoundBox(4, sf::IntRect(172, 185, 57, 85));
	temp->AddBoundBox(7, sf::IntRect(172, 185, 45, 85));
	temp->AddBoundBox(8, sf::IntRect(158, 185, 45, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 167, 50, 103));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(163, 167, 50, 103));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(165, 167, 50, 103));
	hurtBoxes.push_back(sf::IntRect(212, 161, 42, 50));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(165, 167, 50, 103));
	hurtBoxes.push_back(sf::IntRect(214, 164, 43, 38));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(165, 167, 50, 103));
	hurtBoxes.push_back(sf::IntRect(213, 187, 42, 30));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(169, 167, 50, 103));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 167, 50, 103));
	temp->AddHurtBoxes(8, hurtBoxes);
	animManager.AddAnimation(ROUNDHOUSE_KICK, temp);

	// Specials
	// Hadouken	X
	temp = new Animation(charPath, HADOUKEN, 13, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_y_movement);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(0, disable_gravity);
	temp->AddFrameFunction(4, spawn_hadouken);
	framesPerSprite = new int[13]{ 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddBoundBox(0, sf::IntRect(162, 185, 43, 85));
	temp->AddBoundBox(3, sf::IntRect(169, 185, 43, 85));
	temp->AddBoundBox(4, sf::IntRect(178, 185, 47, 85));
	temp->AddBoundBox(9, sf::IntRect(169, 185, 43, 85));
	temp->AddBoundBox(11, sf::IntRect(162, 185, 43, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 167, 47, 103));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(165, 176, 55, 93));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(184, 176, 69, 50));
	hurtBoxes.push_back(sf::IntRect(163, 226, 70, 44));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(184, 176, 63, 50));
	hurtBoxes.push_back(sf::IntRect(163, 226, 70, 44));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(165, 176, 55, 93));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 167, 47, 103));
	temp->AddHurtBoxes(11, hurtBoxes);
	animManager.AddAnimation(HADOUKEN, temp);
	specialCommands.AddCommand("236l", HADOUKEN);
	specialCommands.AddCommand("236m", HADOUKEN);
	specialCommands.AddCommand("236h", HADOUKEN);
	airSpecialCommands.AddCommand("236l", HADOUKEN);
	airSpecialCommands.AddCommand("236m", HADOUKEN);
	airSpecialCommands.AddCommand("236h", HADOUKEN);

	// Shoryuken	X
	temp = new Animation(charPath, SHORYUKEN, 11, false);
	temp->SetDisablSpriteAdvancement(true);
	temp->AddDamageInfo(new DamageInfo(100000, 800, 7, 1, 6, 1, sf::Vector2f(1.f, -10.f), DamageScale::SpecialScale, HitSparkType::Medium));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(3, do_shoryuken);
	temp->AddFrameFunction(5, stop_y_movement);
	framesPerSprite = new int[11]{ 1, 1, 1, 14, 4, 4, 4, 4, 4, 4, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(3, sf::IntRect(176, 118, 41, 121));
	temp->AddHitBox(4, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(165, 185, 40, 85));
	temp->AddBoundBox(3, sf::IntRect(165, 162, 40, 75));
	temp->AddBoundBox(7, sf::IntRect(161, 162, 40, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(164, 180, 44, 90));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 166, 50, 104));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(164, 147, 46, 119));
	hurtBoxes.push_back(sf::IntRect(183, 120, 19, 29));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(164, 147, 46, 119));
	hurtBoxes.push_back(sf::IntRect(167, 125, 26, 24));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 147, 46, 119));
	hurtBoxes.push_back(sf::IntRect(161, 125, 17, 24));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 163, 46, 108));
	temp->AddHurtBoxes(10, hurtBoxes);
	animManager.AddAnimation(SHORYUKEN, temp);
	specialCommands.AddCommand("623l", SHORYUKEN);
	specialCommands.AddCommand("623m", SHORYUKEN);
	specialCommands.AddCommand("623h", SHORYUKEN);
	specialCommands.AddCommand("6323l", SHORYUKEN); // Account for extra inputs
	specialCommands.AddCommand("6323m", SHORYUKEN); // Account for extra inputs
	specialCommands.AddCommand("6323h", SHORYUKEN); // Account for extra inputs
	specialCommands.AddCommand("63236l", SHORYUKEN); // Account for extra inputs
	specialCommands.AddCommand("63236m", SHORYUKEN); // Account for extra inputs
	specialCommands.AddCommand("63236h", SHORYUKEN); // Account for extra inputs

	// Supers
	// Shin Shoryu pt 1	X
	temp = new Animation(charPath, SHIN_SHORYU1, 14, false);
	temp->SetDisablSpriteAdvancement(true);
	temp->AddDamageInfo(new DamageInfo(80000, 0, 20, 22, 6, 1, sf::Vector2f(0.f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, true));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_hyper_attack);
	temp->AddFrameFunction(5, do_shin_shoryuken);
	temp->AddFrameFunction(7, stop_y_movement);
	framesPerSprite = new int[14]{ 2, 3, 3, 3, 4, 7, 7, 4, 4, 4, 4, 4, 4, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(4, sf::IntRect(186, 178, 40, 37));
	temp->AddHitBox(5, sf::IntRect(176, 116, 48, 131));
	temp->AddHitBox(6, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(152, 185, 40, 85));
	temp->AddBoundBox(1, sf::IntRect(161, 185, 40, 85));
	temp->AddBoundBox(3, sf::IntRect(164, 185, 40, 85));
	temp->AddBoundBox(5, sf::IntRect(159, 162, 40, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 169, 50, 101));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 188, 57, 83));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(164, 175, 50, 95));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 169, 50, 101));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 150, 44, 117));
	hurtBoxes.push_back(sf::IntRect(179, 121, 21, 31));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 150, 44, 117));
	hurtBoxes.push_back(sf::IntRect(164, 121, 21, 31));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 150, 44, 117));
	hurtBoxes.push_back(sf::IntRect(171, 121, 21, 31));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 150, 44, 117));
	hurtBoxes.push_back(sf::IntRect(179, 121, 21, 31));
	temp->AddHurtBoxes(10, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 150, 44, 117));
	hurtBoxes.push_back(sf::IntRect(183, 121, 21, 31));
	temp->AddHurtBoxes(11, hurtBoxes);
	animManager.AddAnimation(SHIN_SHORYU1, temp);
	hyperCommands.AddCommand("623lm", SHIN_SHORYU1, THREE_SPECIAL_BARS);
	hyperCommands.AddCommand("623lh", SHIN_SHORYU1, THREE_SPECIAL_BARS);
	hyperCommands.AddCommand("623mh", SHIN_SHORYU1, THREE_SPECIAL_BARS);
	hyperCommands.AddCommand("6323lm", SHIN_SHORYU1, THREE_SPECIAL_BARS);
	hyperCommands.AddCommand("6323lh", SHIN_SHORYU1, THREE_SPECIAL_BARS);
	hyperCommands.AddCommand("6323mh", SHIN_SHORYU1, THREE_SPECIAL_BARS);
	specialCommands.AddCommand("63236l", SHIN_SHORYU1, THREE_SPECIAL_BARS); // Account for extra inputs
	specialCommands.AddCommand("63236m", SHIN_SHORYU1, THREE_SPECIAL_BARS); // Account for extra inputs
	specialCommands.AddCommand("63236h", SHIN_SHORYU1, THREE_SPECIAL_BARS); // Account for extra inputs

	// Shin Shoryu pt 2	X
	temp = new Animation(charPath, SHIN_SHORYU2, 4, false);
	temp->SetDisablSpriteAdvancement(true);
	temp->AddDamageInfo(new DamageInfo(100000, 0, 999, 1, 6, 1, sf::Vector2f(0.f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, true));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_hyper_attack);
	temp->SetFramesAtSprite(0, 16);
	temp->AddHitBox(3, sf::IntRect(178, 165, 50, 50));
	temp->AddBoundBox(0, sf::IntRect(163, 185, 45, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 166, 50, 104));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 175, 50, 95));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 166, 50, 104));
	temp->AddHurtBoxes(2, hurtBoxes);
	animManager.AddAnimation(SHIN_SHORYU2, temp);

	// Shin Shoryu pt 3
	temp = new Animation(charPath, SHIN_SHORYU3, 11, false);
	temp->SetDisablSpriteAdvancement(true);
	temp->AddDamageInfo(new DamageInfo(200000, 0, 50, 1, 6, 1, sf::Vector2f(1.f, -10.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::Hard_KnockDown, sf::Vector2f(1.5f, -16.f)));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_hyper_attack);
	temp->AddFrameFunction(2, do_shin_shoryuken);
	temp->AddFrameFunction(4, stop_y_movement);
	framesPerSprite = new int[11]{ 16, 4, 7, 7, 4, 4, 4, 4, 4, 4, 4 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->SetFramesAtSprite(0, 16);
	temp->SetFramesAtSprite(1, 1);
	temp->AddHitBox(2, sf::IntRect(167, 118, 54, 125));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(163, 185, 43, 85));
	temp->AddBoundBox(2, sf::IntRect(161, 162, 43, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 172, 50, 97));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 153, 50, 113));
	hurtBoxes.push_back(sf::IntRect(179, 120, 20, 36));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 153, 50, 113));
	hurtBoxes.push_back(sf::IntRect(166, 120, 20, 36));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 153, 50, 113));
	hurtBoxes.push_back(sf::IntRect(171, 120, 20, 36));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 153, 50, 113));
	hurtBoxes.push_back(sf::IntRect(176, 120, 20, 36));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 153, 50, 113));
	hurtBoxes.push_back(sf::IntRect(179, 120, 20, 36));
	temp->AddHurtBoxes(7, hurtBoxes);
	animManager.AddAnimation(SHIN_SHORYU3, temp);

	// METSU HADOUKEN	X
	temp = new Animation(charPath, HADOUKEN, 13, false);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(0, disable_gravity);
	temp->AddFrameFunction(2, do_hyper_attack);
	temp->AddFrameFunction(4, spawn_metsu_hadouken);
	framesPerSprite = new int[13]{ 4, 4, 3, 3, 86, 3, 3, 3, 3, 3, 3, 3, 2 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddBoundBox(0, sf::IntRect(162, 185, 43, 85));
	temp->AddBoundBox(3, sf::IntRect(169, 185, 43, 85));
	temp->AddBoundBox(4, sf::IntRect(178, 185, 47, 85));
	temp->AddBoundBox(9, sf::IntRect(169, 185, 43, 85));
	temp->AddBoundBox(11, sf::IntRect(162, 185, 43, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 167, 47, 103));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(165, 176, 55, 93));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(184, 176, 69, 50));
	hurtBoxes.push_back(sf::IntRect(163, 226, 70, 44));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(184, 176, 63, 50));
	hurtBoxes.push_back(sf::IntRect(163, 226, 70, 44));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(165, 176, 55, 93));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(159, 167, 47, 103));
	temp->AddHurtBoxes(11, hurtBoxes);
	animManager.AddAnimation(METSU_HADOUKEN, temp);
	hyperCommands.AddCommand("236lm", METSU_HADOUKEN, ONE_SPECIAL_BAR);
	hyperCommands.AddCommand("236lh", METSU_HADOUKEN, ONE_SPECIAL_BAR);
	hyperCommands.AddCommand("236mh", METSU_HADOUKEN, ONE_SPECIAL_BAR);
	airHyperCommands.AddCommand("236lm", METSU_HADOUKEN, ONE_SPECIAL_BAR);
	airHyperCommands.AddCommand("236lh", METSU_HADOUKEN, ONE_SPECIAL_BAR);
	airHyperCommands.AddCommand("236mh", METSU_HADOUKEN, ONE_SPECIAL_BAR);

	// SUPPORT ANIMATIONS
	// SUPPORT IDLE	X
	temp = new Animation(charPath, IDLE, 1, true);
	temp->AddBoundBox(0, sf::IntRect(0, 0, 0, 0));
	animManager.AddAnimation(SUPPORT_IDLE, temp);

	// SUPPORT ENTER	X
	temp = new Animation(charPath, SUPPORT_ENTER, 1, true);
	temp->AddBoundBox(0, sf::IntRect(158, 162, 43, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(157, 155, 45, 105));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(SUPPORT_ENTER, temp);

	// SUPPORT	X
	temp = new Animation(charPath, SUPPORT, 22, false, SUPPORT_END);
	temp->AddDamageInfo(new DamageInfo(143000, 1280, 23, 20, 6, 1, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Medium, false, AdditionalEffect::Knockdown, sf::Vector2f(2.5f, -5.5f)));
	//temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_tatsumaki);
	temp->AddFrameFunction(11, reset_hit);
	temp->SetFramesOfAnimation(44);
	temp->AddHitBox(6, sf::IntRect(176, 181, 72, 35));
	temp->AddHitBox(7, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(8, sf::IntRect(109, 181, 72, 35));
	temp->AddHitBox(9, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(12, sf::IntRect(176, 181, 72, 35));
	temp->AddHitBox(13, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(14, sf::IntRect(109, 181, 72, 35));
	temp->AddHitBox(15, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 162, 45, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 102));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 80));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 101));
	hurtBoxes.push_back(sf::IntRect(130, 185, 29, 43));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 40, 104));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 40, 28));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 49, 28));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(115, 182, 49, 28));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(122, 182, 40, 28));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	temp->AddHurtBoxes(10, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 40, 28));
	temp->AddHurtBoxes(11, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 49, 28));
	temp->AddHurtBoxes(12, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(130, 196, 27, 50));
	temp->AddHurtBoxes(13, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(115, 182, 49, 28));
	temp->AddHurtBoxes(14, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(122, 182, 40, 28));
	temp->AddHurtBoxes(15, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	temp->AddHurtBoxes(16, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(203, 196, 27, 50));
	temp->AddHurtBoxes(17, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(18, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(130, 196, 27, 50));
	temp->AddHurtBoxes(19, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 103));
	temp->AddHurtBoxes(21, hurtBoxes);
	animManager.AddAnimation(SUPPORT, temp);

	// SUPPORT END	X
	temp = new Animation(charPath, SUPPORT_END, 8, false, SUPPORT_EXIT);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(158, 185, 41, 85));
	animManager.AddAnimation(SUPPORT_END, temp);

	// SUPPORT EXIT	X
	temp = new Animation(charPath, SUPPORT_ENTER, 1, true);
	temp->AddBoundBox(0, sf::IntRect(0, 0, 0, 0));
	temp->AddFrameFunction(0, do_support_exit);
	temp->AddFrameFunction(0, destroy_metsu_hadouken);
	animManager.AddAnimation(SUPPORT_EXIT, temp);

	// CROSS ASSAULT	X
	temp = new Animation(charPath, CROSS_ASSAULT, 1, true);
	temp->AddDamageInfo(new DamageInfo(90000, 760, 17, 19, 10, 1, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::Knockdown, sf::Vector2f(7.f, -10.f)));
	temp->AddHitBox(0, sf::IntRect(176, 197, 69, 35));
	temp->AddBoundBox(0, sf::IntRect(158, 162, 47, 66));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(149, 163, 52, 67));
	hurtBoxes.push_back(sf::IntRect(199, 192, 44, 38));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(CROSS_ASSAULT, temp);

	// CROSS ASSAULT LANDING	X
	temp = new Animation(charPath, CROSS_ASSAULT_LANDING, 6, false);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(0, do_attack);
	temp->AddBoundBox(0, sf::IntRect(158, 185, 45, 85));
	temp->AddBoundBox(1, sf::IntRect(151, 185, 45, 85));
	temp->AddBoundBox(5, sf::IntRect(158, 185, 45, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 165, 50, 105));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 176, 61, 47));
	hurtBoxes.push_back(sf::IntRect(140, 222, 62, 50));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(145, 182, 58, 41));
	hurtBoxes.push_back(sf::IntRect(140, 222, 62, 50));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 182, 54, 41));
	hurtBoxes.push_back(sf::IntRect(143, 222, 62, 50));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(153, 175, 50, 95));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(CROSS_ASSAULT_LANDING, temp);

	// SNAP BACK	X
	temp = new Animation(charPath, H, 7, false);
	temp->AddDamageInfo(new DamageInfo(90000, 760, 1, 19, 10, 0, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::Snap_Back));
	temp->AddFrameFunction(0, do_hyper_attack);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	framesPerSprite = new int[7]{ 5, 5, 3, 6, 5, 5, 5 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddHitBox(2, sf::IntRect(205, 176, 51, 24));
	temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(161, 185, 50, 85));
	temp->AddBoundBox(1, sf::IntRect(165, 185, 50, 85));
	temp->AddBoundBox(2, sf::IntRect(173, 185, 50, 85));
	temp->AddBoundBox(4, sf::IntRect(167, 185, 50, 85));
	temp->AddBoundBox(5, sf::IntRect(165, 185, 50, 85));
	temp->AddBoundBox(6, sf::IntRect(161, 185, 50, 85));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 168, 54, 102));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 168, 57, 102));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(166, 168, 57, 102));
	hurtBoxes.push_back(sf::IntRect(223, 178, 31, 20));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(166, 168, 52, 102));
	hurtBoxes.push_back(sf::IntRect(217, 179, 28, 20));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(162, 168, 57, 102));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(158, 168, 57, 102));
	temp->AddHurtBoxes(6, hurtBoxes);
	animManager.AddAnimation(SNAP_BACK, temp);
	hyperCommands.AddCommand("236p", SNAP_BACK, ONE_SPECIAL_BAR);

	// SNAP BACK HURT	X
	temp = new Animation(charPath, AIR_HURT, 1, true);
	temp->AddFrameFunction(0, check_for_snap_back_swap);
	temp->AddFrameFunction(0, destroy_metsu_hadouken);
	temp->AddBoundBox(0, sf::IntRect(158, 162, 46, 76));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(135, 180, 84, 65));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(SNAP_BACK_HURT, temp);

	LoadTatsumaki(charPath);

	// THROWN ANIMS
	charPath += "Thrown/";

	// RYU FORWARD THROWN	X
	temp = new Animation(charPath, RYU_FORWARD_THROWN, 4, false);
	framesPerSprite = new int[4]{ 10, 4, 4, 10 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(153, 166, 0, 0));
	animManager.AddAnimation(RYU_FORWARD_THROWN, temp);

	// RYU BACK THROWN	X
	temp = new Animation(charPath, RYU_BACK_THROWN, 3, false);
	temp->SetFramesAtSprite(0, 14);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(153, 166, 0, 0));
	animManager.AddAnimation(RYU_BACK_THROWN, temp);

	// KYOSUKE FORWARD THROWN	X
	temp = new Animation(charPath, KYOSUKE_FORWARD_THROWN, 1, false);
	temp->SetFramesOfAnimation(30);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(153, 166, 0, 0));
	animManager.AddAnimation(KYOSUKE_FORWARD_THROWN, temp);

	// KYOSUKE FORWARD THROWN	X
	temp = new Animation(charPath, KYOSUKE_BACK_THROWN, 3, false);
	framesPerSprite = new int[3]{ 30, 4, 10 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddBoundBox(0, sf::IntRect(153, 166, 0, 0));
	animManager.AddAnimation(KYOSUKE_BACK_THROWN, temp);

	hadoukenBase = new Hadouken();
	hadoukenBase->Load();

	metsuHadoukenBase = new MetsuHadouken();
	metsuHadoukenBase->Load();

	Fighter::Load();
}

void Ryu::LoadTatsumaki(std::string filePath) {
	Animation* temp;
	std::vector<sf::IntRect> hurtBoxes;
	int* framesPerSprite;

	// L TATSUMAKI	X
	temp = new Animation(filePath, L_TATSUMAKI, 16, false);
	temp->AddDamageInfo(new DamageInfo(90000, 720, 23, 20, 6, 1, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Medium, false, AdditionalEffect::Knockdown, sf::Vector2f(2.f, -5.5f))); // Should be regular knockdown, not HARD
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_tatsumaki);
	temp->SetFramesOfAnimation(32);
	temp->AddHitBox(6, sf::IntRect(176, 181, 72, 35));
	temp->AddHitBox(7, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(8, sf::IntRect(109, 181, 72, 35));
	temp->AddHitBox(9, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 162, 45, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 102));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 80));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 101));
	hurtBoxes.push_back(sf::IntRect(130, 185, 29, 43));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 40, 104));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 40, 28));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 49, 28));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(115, 182, 49, 28));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(122, 182, 40, 28));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	temp->AddHurtBoxes(10, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(203, 196, 27, 50));
	temp->AddHurtBoxes(11, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(12, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(130, 196, 27, 50));
	temp->AddHurtBoxes(13, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 103));
	temp->AddHurtBoxes(15, hurtBoxes);
	animManager.AddAnimation(L_TATSUMAKI, temp);
	specialCommands.AddCommand("214l", L_TATSUMAKI);
	airSpecialCommands.AddCommand("214l", L_TATSUMAKI);

	// M TATSUMAKI	X
	temp = new Animation(filePath, M_TATSUMAKI, 22, false);
	temp->AddDamageInfo(new DamageInfo(114000, 960, 23, 20, 6, 1, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Medium, false, AdditionalEffect::Knockdown, sf::Vector2f(2.5f, -5.5f)));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_tatsumaki);
	temp->AddFrameFunction(11, reset_hit);
	temp->SetFramesOfAnimation(44);
	temp->AddHitBox(6, sf::IntRect(176, 181, 72, 35));
	temp->AddHitBox(7, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(8, sf::IntRect(109, 181, 72, 35));
	temp->AddHitBox(9, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(12, sf::IntRect(176, 181, 72, 35));
	temp->AddHitBox(13, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(14, sf::IntRect(109, 181, 72, 35));
	temp->AddHitBox(15, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 162, 45, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 102));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 80));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 101));
	hurtBoxes.push_back(sf::IntRect(130, 185, 29, 43));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 40, 104));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 40, 28));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 49, 28));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(115, 182, 49, 28));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(122, 182, 40, 28));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	temp->AddHurtBoxes(10, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 40, 28));
	temp->AddHurtBoxes(11, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 49, 28));
	temp->AddHurtBoxes(12, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(130, 196, 27, 50));
	temp->AddHurtBoxes(13, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(115, 182, 49, 28));
	temp->AddHurtBoxes(14, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(122, 182, 40, 28));
	temp->AddHurtBoxes(15, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	temp->AddHurtBoxes(16, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(203, 196, 27, 50));
	temp->AddHurtBoxes(17, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(18, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(130, 196, 27, 50));
	temp->AddHurtBoxes(19, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 103));
	temp->AddHurtBoxes(21, hurtBoxes);
	animManager.AddAnimation(M_TATSUMAKI, temp);
	specialCommands.AddCommand("214m", M_TATSUMAKI);
	airSpecialCommands.AddCommand("214m", M_TATSUMAKI);

	// H TATSUMAKI	X
	temp = new Animation(filePath, H_TATSUMAKI, 22, false);
	temp->AddDamageInfo(new DamageInfo(143000, 1280, 23, 20, 6, 1, sf::Vector2f(1.50f, 0.f), DamageScale::SpecialScale, HitSparkType::Medium, false, AdditionalEffect::Knockdown, sf::Vector2f(2.5f, -5.5f)));
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(1, do_tatsumaki);
	temp->AddFrameFunction(11, reset_hit);
	temp->SetFramesOfAnimation(44);
	temp->AddHitBox(6, sf::IntRect(176, 181, 72, 35));
	temp->AddHitBox(7, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(8, sf::IntRect(109, 181, 72, 35));
	temp->AddHitBox(9, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(12, sf::IntRect(176, 181, 72, 35));
	temp->AddHitBox(13, sf::IntRect(0, 0, 0, 0));
	temp->AddHitBox(14, sf::IntRect(109, 181, 72, 35));
	temp->AddHitBox(15, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(158, 162, 45, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 102));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 80));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 101));
	hurtBoxes.push_back(sf::IntRect(130, 185, 29, 43));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 40, 104));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 40, 28));
	temp->AddHurtBoxes(5, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 49, 28));
	temp->AddHurtBoxes(6, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(7, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(115, 182, 49, 28));
	temp->AddHurtBoxes(8, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(122, 182, 40, 28));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	temp->AddHurtBoxes(10, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 40, 28));
	temp->AddHurtBoxes(11, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(195, 182, 49, 28));
	temp->AddHurtBoxes(12, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(130, 196, 27, 50));
	temp->AddHurtBoxes(13, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(115, 182, 49, 28));
	temp->AddHurtBoxes(14, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 41, 105));
	hurtBoxes.push_back(sf::IntRect(122, 182, 40, 28));
	temp->AddHurtBoxes(15, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	temp->AddHurtBoxes(16, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(203, 196, 27, 50));
	temp->AddHurtBoxes(17, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 113));
	temp->AddHurtBoxes(18, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 104));
	hurtBoxes.push_back(sf::IntRect(130, 196, 27, 50));
	temp->AddHurtBoxes(19, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(155, 155, 50, 103));
	temp->AddHurtBoxes(21, hurtBoxes);
	animManager.AddAnimation(H_TATSUMAKI, temp);
	specialCommands.AddCommand("214h", H_TATSUMAKI);
	airSpecialCommands.AddCommand("214h", H_TATSUMAKI);
		
	// Shinku Tatsumaki Start	X
	temp = new Animation(filePath, SHINKU_TATSUMAKI, 4, false, SHINKU_ATSUMAKI_MIDDLE);
	temp->AddFrameFunction(0, do_attack);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(0, do_hyper_attack);
	framesPerSprite = new int[4]{ 4, 3, 3, 3 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddBoundBox(0, sf::IntRect(156, 162, 46, 75));
	temp->AddBoundBox(2, sf::IntRect(149, 162, 42, 75));
	temp->AddBoundBox(3, sf::IntRect(145, 162, 46, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(154, 156, 50, 113));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(152, 156, 50, 98));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(150, 156, 44, 76));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(143, 148, 50, 105));
	temp->AddHurtBoxes(3, hurtBoxes);
	animManager.AddAnimation(SHINKU_TATSUMAKI, temp);
	hyperCommands.AddCommand("214lm", SHINKU_TATSUMAKI, ONE_SPECIAL_BAR);
	hyperCommands.AddCommand("214mh", SHINKU_TATSUMAKI, ONE_SPECIAL_BAR);
	hyperCommands.AddCommand("214lh", SHINKU_TATSUMAKI, ONE_SPECIAL_BAR);

	// Tatsumaki Middle	X
	temp = new Animation(filePath, SHINKU_ATSUMAKI_MIDDLE, 6, true, SHINKU_TATSUMAKI_END, 14);
	temp->AddDamageInfo(new DamageInfo(16000, 0, 23, 23, 0, 1, sf::Vector2f(0.f, 0.f), DamageScale::SpecialScale, HitSparkType::Medium, true));
	framesPerSprite = new int[6]{ 1,1,1,1,1,1 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddFrameFunction(1, reset_hit);
	temp->AddFrameFunction(3, reset_hit);
	//temp->AddFrameFunction(5, reset_hit);
	temp->AddHitBox(2, sf::IntRect(119, 179, 111, 36));
	//temp->AddHitBox(2, sf::IntRect(176, 181, 72, 36));
	//temp->AddHitBox(3, sf::IntRect(0, 0, 0, 0));
	//temp->AddHitBox(4, sf::IntRect(113, 181, 72, 36));
	//temp->AddHitBox(5, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(154, 162, 53, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 141, 45, 117));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 141, 39, 117));
	hurtBoxes.push_back(sf::IntRect(198, 182, 36, 28));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 141, 39, 117));
	hurtBoxes.push_back(sf::IntRect(198, 182, 46, 28));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(156, 141, 45, 117));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 141, 39, 117));
	hurtBoxes.push_back(sf::IntRect(117, 182, 44, 28));
	temp->AddHurtBoxes(4, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(160, 141, 39, 117));
	hurtBoxes.push_back(sf::IntRect(124, 182, 36, 28));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(SHINKU_ATSUMAKI_MIDDLE, temp);

	// Tatsumaki End	X
	temp = new Animation(filePath, SHINKU_TATSUMAKI_END, 6, false);
	temp->AddDamageInfo(new DamageInfo(12000, 0, 23, 23, 0, 1, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::Hard_KnockDown, sf::Vector2f(15.f, -6.f)));
	framesPerSprite = new int[6]{ 2,7,7,7,7,7 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddFrameFunction(0, reset_hit);
	temp->AddHitBox(0, sf::IntRect(119, 179, 111, 36));
	//temp->AddHitBox(0, sf::IntRect(132, 175, 108, 37));
	//temp->AddHitBox(1, sf::IntRect(0, 0, 0, 0));
	temp->AddBoundBox(0, sf::IntRect(161, 162, 39, 75));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 141, 38, 116));
	hurtBoxes.push_back(sf::IntRect(198, 201, 24, 43));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 141, 44, 116));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 141, 38, 116));
	hurtBoxes.push_back(sf::IntRect(132, 194, 29, 43));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(161, 141, 44, 116));
	temp->AddHurtBoxes(5, hurtBoxes);
	animManager.AddAnimation(SHINKU_TATSUMAKI_END, temp);
}

void Ryu::CheckActionInput(Controls* playerControls) {
	Fighter::CheckActionInput(playerControls);

	if ((!isAttacking || (canCombo && lastAttack < Command)) && !isHurt && !commandFound && !inAir) {

		// Check Ryu's Command Normals
		//if (!downHeld || Combo) {
			if (!downHeld && ((forwardHeld && 1 == xScale) || (backHeld && -1 == xScale)) && playerControls->isActionPressed(Controls::Actions::Heavy)) {
				isAttacking = true;
				nextActionAnim = ROUNDHOUSE_KICK;
				canCombo = true;
				lastAttack = Command;
			}

			if (!downHeld && ((forwardHeld && 1 == xScale) || (backHeld && -1 == xScale)) && playerControls->isActionPressed(Controls::Actions::Medium)) {
				isAttacking = true;
				nextActionAnim = COLLARBONE_BREAKER;
				canCombo = true;
				lastAttack = Command;
			}
		//}
	}
}

void Ryu::CheckOnHit() {
	if (SHIN_SHORYU1 == animManager.GetCurrentAnimationName())
		nextAnimToPlay = SHIN_SHORYU2;
	if (SHIN_SHORYU2 == animManager.GetCurrentAnimationName())
		nextAnimToPlay = SHIN_SHORYU3;
}

void Ryu::UpdateAnimations() {
	Fighter::UpdateAnimations();
}

void Ryu::DoForwardThrow() {
	DoAttack();
	enemyMain->SetPosition(position);
	enemyMain->BeThrown(RYU_FORWARD_THROWN, xScale);
}

void Ryu::DoBackThrow() {
	DoAttack();
	enemyMain->SetPosition(position);
	enemyMain->BeThrown(RYU_BACK_THROWN, xScale);
}

/*
////////// SCRIPTING FUNCTIONS //////////////////////////////////////
*/

bool Ryu::CallEnumFunction(int functionEnum)
{
	if (Fighter::CallEnumFunction(functionEnum))
		return false;

	switch (functionEnum) {
	case spawn_hadouken:
		SpawnHadouken();
		return true;
	case spawn_metsu_hadouken:
		SpawnMetsuHadouken();
		return true;
	case do_tatsumaki:
		DoTatsumaki();
		return true;
	case do_shoryuken:
		DoShoryuken();
		return true;
	case do_shin_shoryuken:
		DoShinShoryuken();
		return true;
	case destroy_metsu_hadouken:
		DestroyMetsuHadouken();
		return true;
	case do_m:
		DoM();
		return true;
	case do_c_m:
		DoC_M();
		return true;
	case do_h:
		DoH();
		return true;
	default:
		std::cout << "Function: " << functionEnum << " not found" << std::endl;
		return false;
	}

}

void Ryu::SpawnHadouken() {
	Hadouken* newhadouken = new Hadouken(*hadoukenBase);
	newhadouken->SetXScale(xScale);
	newhadouken->SetPosition(position);
	if (heavyAttack)
		newhadouken->SetVelocity(sf::Vector2f(5.f * xScale, 0.f));
	else if (mediumAttack)
		newhadouken->SetVelocity(sf::Vector2f(4.f * xScale, 0.f));
	else if (lightAttack)
		newhadouken->SetVelocity(sf::Vector2f(3.f * xScale, 0.f));

	spawnedProjectiles.push_back(newhadouken);
}

void Ryu::SpawnMetsuHadouken() {
	MetsuHadouken* newMetsuHadouken = new MetsuHadouken(*metsuHadoukenBase);
	newMetsuHadouken->SetXScale(xScale);
	newMetsuHadouken->SetPosition(position);

	spawnedProjectiles.push_back(newMetsuHadouken);
}

void Ryu::DoTatsumaki() {
	if (!isAssisting) {
		inAir = true;
		disablePhysics = true;
	}
	velocity.x = 3.f * xScale;

	if (mediumAttack || heavyAttack)
		disableActionUntilGrounded = true;
}

void Ryu::DoShoryuken() {
	inAir = true;
	disableActionUntilGrounded = true;
	if (heavyAttack) {
		velocity.x = 1.5f * xScale;
		velocity.y = -15.f;
	}
	else if (mediumAttack) {
		velocity.x = 1.5f * xScale;
		velocity.y = -12.f;
	}
	else if (lightAttack) {
		velocity.x = 1.5f * xScale;
		velocity.y = -8.f;
	}
}

void Ryu::DoShinShoryuken() {
	inAir = true;
	disableActionUntilGrounded = true;
	velocity.x = 1.5f * xScale;
	velocity.y = -15.f;
}

void Ryu::DestroyMetsuHadouken() {
	for (int i = 0; i < spawnedProjectiles.size(); i++) {
		if (METSU_HADOUKEN == spawnedProjectiles[i]->GetName()) {
			spawnedProjectiles.erase(spawnedProjectiles.begin() + i);
			return;
		}
	}
}

void Ryu::SetColor(int colorNum) {

	if (2 == colorNum) {
		colorShader.setParameter("texture", sf::Shader::CurrentTexture);
		colorShader.setParameter("color1", 1.f, 1.f, 0.937f);
		colorShader.setParameter("replace1", 0.235f, 0.235f, 0.219f);
		colorShader.setParameter("color2", 0.807f, 0.741f, 0.580f);
		colorShader.setParameter("replace2", 0.188f, 0.172f, 0.137f);
		colorShader.setParameter("color3", 0.678f, 0.647f, 0.517f);
		colorShader.setParameter("replace3", 0.167f, 0.152f, 0.121f);
		colorShader.setParameter("color4", 0.517f, 0.517f, 0.419f);
		colorShader.setParameter("replace4", 0.121f, 0.121f, 0.098f);
		colorShader.setParameter("color5", 0.905f, 0.905f, 0.776f);
		colorShader.setParameter("replace5", 0.211f, 0.211f, 0.184f);
		colorShader.setParameter("color6", 0.968f, 0.f, 0.f);
		colorShader.setParameter("replace6", 0.f, 0.494f, 0.847f);
		colorShader.setParameter("color7", 0.709f, 0.f, 0.f);
		colorShader.setParameter("replace7", 0.f, 0.290f, 0.498f);
	}
}

void Ryu::DoM() {
	velocity.x = 1.f * xScale;
}

void Ryu::DoC_M() {
	velocity.x = 1.f * xScale;
}

void Ryu::DoH() {
	velocity.x = 1.f * xScale;
}