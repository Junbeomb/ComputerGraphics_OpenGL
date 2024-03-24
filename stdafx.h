#pragma once
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#define PLAYTIME 10
#define ANIMATION 1
#define BULLET 2
#define DASH_SPEED 0.2f
#define MAP_SIZE 30.f
#define MONSTER_GEN 3
#define BOSS_GEN 20
#define BULLET_MAX 20

#define BOSS_TELEPORT 0
#define BOSS_RAZOR 1
#define BOSS_DROP 2
#define BOSS_DASH 3

#define BOSS_STATUS_NOTAPPEAR 0
#define BOSS_STATUS_APPEAR 1
#define BOSS_STATUS_SKILL 2
#define BOSS_STATUS_DEATH 3

#include "stb_image.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

//플레이어 변수
struct Player {
    float x{}, z{};
    float direction{};
    float directionY{};
    int startX{}, currentX{};
    int startY{}, currentY{};
    bool w = false, a = false, s = false, d = false;
    int atk{}, hp = 10, speed{};
    int status{};
    int invincibilityTimer = 0;
};

//공격기
struct Bullet {
    float currentX{}, currentZ{}, currentY{20};
    int monsterNum{};
    int skillEight = 0;
    int skillEightCount = 0;
    int skillBig = 0;
    bool shouldDraw = false;
};

//몬스터 변수
struct MonsterBullet
{
    float x, z;
};

struct Monster {
    float x{}, z{};

    float LookX{}, LookZ{};
    float turnMonster;

    int hp{3};
    int type{};
    int numbering{};
    bool shouldDraw = false;
    int mbtimer{ 0 };
    MonsterBullet mb[4];
};

//보스 몬스터 변수


struct BossObstacle {
    //보스 주위 장애물
    int obstacleDraw = false;
    float ObsX{}, ObsY{}, ObsZ{};
};

struct BossTeleport {
    bool toggle = false;
    int status = 0;
    int timer = 0;
    float bossSize = 1;
    float destinationX{}, destinationZ{};
};

struct BossRazor {
    bool toggle = false;
    int status = 0;
    int timer = 0;
    float size = 0.1;
    float length = 0.0;
};

struct BossDrop {
    bool toggle = false;
    int status = 0;
    int timer = 0;
    float size = 0.05f;
    int number = 30;
    float posX[30], posZ[30];
};

struct BossDash {
    bool toggle = false;
    int status = 0;
    int timer = 0;
    float rememberAngle = 0.f;
    float speed = 0.5f;
};

struct Boss {
    float x{}, y{}, z{};
    int hp{60};
    int bossTimer = 0;
    BossTeleport skillTeleport;
    BossRazor skillRazor;
    BossDrop skillDrop;
    BossDash skillDash;
    bool firstAppearance = false;
    int status = 0; //0 : 나타나지 않음 , 1 : 나타남 , 2 : 스킬 사용중 , 3: 죽음
};

struct Item
{
    float x, z;
    bool shouldDraw = false;
    int type{};
};

int playTimeTimer{ 0 };
int animationTimer{ 0 };

bool bossToggle = false;
bool bossObsToggle = false;
float turnBoss = -90.0f;
Boss boss;
BossObstacle bossObs[200];
Player player;
Bullet bullet[BULLET_MAX];
Monster monster[20];
Item item[20];

int bossCameraAnimationTime = 0;
float cameraX = 0.0;
float cameraZ = 0.0;

bool topViewToggle = false;
float topViewCameraX = 0.0f;
float topViewCameraZ = 0.0f;

int countMonCatch = 0;
float coinRotate = 0.f;

bool zFlag = false;
int zTimer = 0;

int skillXCoolTime = 0;
bool skillXToggle = false;
int skillCCoolTime = 0;
bool skillCToggle = false;

int countSkillEight = 0;