#pragma once
#include "shader.h"

class Animation {
public:
    float bossL = 0;
    float playerL = 0;
    float inner = 0;

	void SetAnimation() {
        animationTimer++; //1초당 100
        coinRotate += 3.6f;
        //동전 충돌처리
        for (int i = 0; i < 20; i++)
        {
            if (player.x<item[i].x + 0.2f && player.x>item[i].x - 0.2f && player.z<item[i].z + 0.2f && player.z>item[i].z - 0.2f && item[i].shouldDraw)
            {
                item[i].shouldDraw = false;
                int randSpec = rand() % 2;
                if (randSpec == 1)
                {
                    if (player.atk < 3)player.atk++;
                    else player.speed++;
                }
            }
        }
        //플레이어 이동
        if (!bossToggle) {
            if (player.w)
            {
                player.x -= sin(player.direction) * 0.03f * player.speed;
                player.z -= cos(player.direction) * 0.03f * player.speed;
                if (zFlag)
                {
                    player.x -= sin(player.direction) * DASH_SPEED;
                    player.z -= cos(player.direction) * DASH_SPEED;
                }
            }
            if (player.a)
            {
                player.x -= cos(player.direction) * 0.03f * player.speed;
                player.z += sin(player.direction) * 0.03f * player.speed;
                if (zFlag)
                {
                    player.x -= cos(player.direction) * DASH_SPEED;
                    player.z += sin(player.direction) * DASH_SPEED;
                }
            }
            if (player.s)
            {
                player.x += sin(player.direction) * 0.03f * player.speed;
                player.z += cos(player.direction) * 0.03f * player.speed;
                if (zFlag)
                {
                    player.x += sin(player.direction) * DASH_SPEED;
                    player.z += cos(player.direction) * DASH_SPEED;
                }
            }
            if (player.d)
            {
                player.x += cos(player.direction) * 0.03f * player.speed;
                player.z -= sin(player.direction) * 0.03f * player.speed;
                if (zFlag)
                {
                    player.x += cos(player.direction) * DASH_SPEED;
                    player.z -= sin(player.direction) * DASH_SPEED;
                }
            }
        }
        else {
            //장애물 밖으로 못 벗어나게

            if (player.w)
            {
                player.x -= sin(player.direction) * 0.03f * player.speed;
                player.z -= cos(player.direction) * 0.03f * player.speed;
                if (zFlag)
                {
                    player.x -= sin(player.direction) * DASH_SPEED;
                    player.z -= cos(player.direction) * DASH_SPEED;
                }
                if (sqrt(pow(player.x, 2) + pow(player.z, 2)) >= 10) {
                    player.x += sin(player.direction) * 0.03f * player.speed;
                    player.z += cos(player.direction) * 0.03f * player.speed;
                    if (zFlag)
                    {
                        player.x += sin(player.direction) * DASH_SPEED;
                        player.z += cos(player.direction) * DASH_SPEED;
                    }
                }
            }
            if (player.a)
            {
                player.x -= cos(player.direction) * 0.03f * player.speed;
                player.z += sin(player.direction) * 0.03f * player.speed;
                if (zFlag)
                {
                    player.x -= cos(player.direction) * DASH_SPEED;
                    player.z += sin(player.direction) * DASH_SPEED;
                }
                if (sqrt(pow(player.x, 2) + pow(player.z, 2)) >= 10) {
                    player.x += cos(player.direction) * 0.03f * player.speed;
                    player.z -= sin(player.direction) * 0.03f * player.speed;
                    if (zFlag)
                    {
                        player.x += cos(player.direction) * DASH_SPEED;
                        player.z -= sin(player.direction) * DASH_SPEED;
                    }
                }

            }
            if (player.s)
            {
                player.x += sin(player.direction) * 0.03f * player.speed;
                player.z += cos(player.direction) * 0.03f * player.speed;
                if (zFlag)
                {
                    player.x -= sin(player.direction) * DASH_SPEED;
                    player.z -= cos(player.direction) * DASH_SPEED;
                }
                if (sqrt(pow(player.x, 2) + pow(player.z, 2)) >= 10) {
                    player.x -= sin(player.direction) * 0.03f * player.speed;
                    player.z -= cos(player.direction) * 0.03f * player.speed;
                    if (zFlag)
                    {
                        player.x += sin(player.direction) * DASH_SPEED;
                        player.z += cos(player.direction) * DASH_SPEED;
                    }
                }
            }
            if (player.d)
            {
                player.x += cos(player.direction) * 0.03f * player.speed;
                player.z -= sin(player.direction) * 0.03f * player.speed;
                if (zFlag)
                {
                    player.x += cos(player.direction) * DASH_SPEED;
                    player.z -= sin(player.direction) * DASH_SPEED;
                }
                if (sqrt(pow(player.x, 2) + pow(player.z, 2)) >= 10) {
                    player.x -= cos(player.direction) * 0.03f * player.speed;
                    player.z += sin(player.direction) * 0.03f * player.speed;
                    if (zFlag)
                    {
                        player.x -= cos(player.direction) * DASH_SPEED;
                        player.z += sin(player.direction) * DASH_SPEED;
                    }
                }
            }
        }
        //플레이어가 방금 공격 당한 상태
        if (player.status == 1) {
            player.invincibilityTimer++;
            if (player.invincibilityTimer == 200) {
                player.invincibilityTimer = 0;
                player.status = 0;
            }
        }

        if (!bossToggle) {
            //몬스터 이동
            for (int i = 0; i < BOSS_GEN; i++) {
                if (monster[i].shouldDraw) {
                    if (monster[i].x > player.x)monster[i].x -= 0.02f;
                    if (monster[i].x < player.x)monster[i].x += 0.02f;
                    if (monster[i].z > player.z)monster[i].z -= 0.02f;
                    if (monster[i].z < player.z)monster[i].z += 0.02f;

                    //플레이어와 충돌
                    if (player.status == 0) {
                        //일반 몬스터
                        if (sqrt(pow(player.x - monster[i].x, 2) + pow(player.z - monster[i].z, 2)) < 0.2 && monster[i].type != 3) {
                            player.hp--;
                            player.status = 1;
                            if (player.hp == 0) exit(-1);
                        }
                        //장판 몬스터
                        else if (sqrt(pow(player.x - monster[i].x, 2) + pow(player.z - monster[i].z, 2)) < 1 && monster[i].type == 3) {
                            player.hp--;
                            player.status = 1;
                            if (player.hp == 0) exit(-1);
                        }
                    }
                }
                if (monster[i].type == 2) //몬스터 스킬
                {
                    monster[i].mb[0].x += 0.03f;
                    monster[i].mb[1].x -= 0.03f;
                    monster[i].mb[2].z += 0.03f;
                    monster[i].mb[3].z -= 0.03f;
                    //플레이어와 충돌
                    if (player.status == 0) {
                        for (int j = 0; j < 4; j++) {
                            if (sqrt(pow(player.x - monster[i].mb[j].x, 2) + pow(player.z - monster[i].mb[j].z, 2)) < 0.2) {
                                player.hp--;
                                player.status = 1;
                                if (player.hp == 0) exit(-1);
                            }

                        }
                    }
                    monster[i].mbtimer++;
                    if (monster[i].mbtimer > 500)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            monster[i].mb[j].x = monster[i].x;
                            monster[i].mb[j].z = monster[i].z;
                        }
                        monster[i].mbtimer = 0;
                    }
                }
            }
            //1초마다 몬스터 에게 총알 발사
            if (animationTimer != 0 && animationTimer % 100 == 0) {
                //가장 가까이있는 몬스터 구하기
                float minDistance = 100.f;
                int minNumbering = -1;
                int checkMon = 0;
                for (int i = 0; i < BOSS_GEN; i++) {
                    if (monster[i].shouldDraw) {
                        checkMon = 1;
                        int tempDistance = sqrt(pow(monster[i].x - player.x, 2) + pow(monster[i].z - player.z, 2));
                        if (minDistance > tempDistance) { //가장 가까운 거리구하기
                            minDistance = tempDistance;
                            minNumbering = monster[i].numbering; //가장 가까운 거리 가진 몬스터 넘버
                        }
                    }
                }
                if (checkMon == 1) {
                    //그 몬스터 에게 총알 날라가게 하기
                    for (int i = 0; i < BULLET_MAX; i++) {
                        if (bullet[i].shouldDraw == false) { //대기 상태에 있는 총알 하나 발사모드 만들기
                            bullet[i].shouldDraw = true;
                            bullet[i].currentY = 0.5f;
                            bullet[i].currentX = player.x;
                            bullet[i].currentZ = player.z;
                            bullet[i].monsterNum = minNumbering; //목적 몬스터 넘버
                            break;
                        }
                    }
                }
            }
        }
        else { //보스에게 총알발사
            //1초마다 몬스터 에게 총알 발사
            if (animationTimer != 0 && animationTimer % 100 == 0) {
                for (int i = 0; i < BULLET_MAX; i++) {
                    if (bullet[i].shouldDraw == false) { //대기 상태에 있는 총알 하나 발사모드 만들기
                        bullet[i].shouldDraw = true;
                        bullet[i].currentY = 0.5f;
                        bullet[i].currentX = player.x;
                        bullet[i].currentZ = player.z;
                        break;
                    }
                }
            }
        }


        //보스
        if (bossToggle) {

            if (bossCameraAnimationTime < 400)
                bossCameraAnimationTime++;

            //보스 첫 등장 시
            if (boss.firstAppearance) {
                boss.y -= 0.5;
                if (boss.y <= 0.5) {
                    boss.firstAppearance = false;
                }
            }
            else if (bossCameraAnimationTime >= 400) { //보스 등장 애니메이션 끝나고, 카메라 애니메이션 끝나면 이동
                boss.bossTimer++;

                //캐릭터에게 이동 (보스가 일반 상태일 때만)
                if (boss.status == BOSS_STATUS_APPEAR) {
                    if (boss.x > player.x)boss.x -= 0.01f;
                    if (boss.x < player.x)boss.x += 0.01f;
                    if (boss.z > player.z)boss.z -= 0.01f;
                    if (boss.z < player.z)boss.z += 0.01f;

                    //보스 플레이어 바라보게 하기
                    bossL = boss.x - player.x;
                    playerL = boss.z - player.z;
                    inner = atan2(playerL, bossL);
                    turnBoss = inner * 180 / M_PI;
                }

                if (boss.skillRazor.toggle == true && boss.skillRazor.status == 1) {
                    //보스 플레이어 바라보게 하기
                    bossL = boss.x - player.x;
                    playerL = boss.z - player.z;
                    inner = atan2(playerL, bossL);
                    turnBoss = inner * 180 / M_PI;
                }

                if (boss.bossTimer != 0 && boss.bossTimer % 300 == 0) { //3초에 한번씩 스킬 발동

                    int randomSkill = -1;
                    if (boss.status == BOSS_STATUS_APPEAR) //(보스가 일반 상태일 때만)
                        randomSkill = rand() % 4; //스킬 주사위 돌리기

                    if (randomSkill == BOSS_TELEPORT) { // 텔레포트
                        boss.status = BOSS_STATUS_SKILL; // 스킬 사용중
                        boss.skillTeleport.toggle = true;
                        boss.skillTeleport.status = 0;
                    }
                    else if (randomSkill == BOSS_RAZOR) {
                        boss.status = BOSS_STATUS_SKILL; // 스킬 사용중
                        boss.skillRazor.toggle = true;
                        boss.skillRazor.status = 0;
                    }
                    else if (randomSkill == BOSS_DROP) {
                        boss.status = BOSS_STATUS_SKILL;
                        boss.skillDrop.toggle = true;
                        boss.skillDrop.status = 0;
                    }
                    else if (randomSkill == BOSS_DASH) {
                        boss.status = BOSS_STATUS_SKILL;
                        boss.skillDash.toggle = true;
                        boss.skillDash.status = 0;
                    }

                }

                if (boss.status == BOSS_STATUS_SKILL) { //보스가 스킬 사용중
                    if (boss.skillTeleport.toggle == true) { //텔레포트
                        boss.skillTeleport.timer++;

                        //처음에 플레이어 위치 기억
                        if (boss.skillTeleport.timer == 30) {
                            boss.skillTeleport.destinationX = player.x;
                            boss.skillTeleport.destinationZ = player.z;
                        }

                        if (boss.skillTeleport.timer >= 30 && boss.skillTeleport.timer <= 50) { //보스 크기 서서히 감소
                            boss.skillTeleport.bossSize -= 0.05; //1.0에서 시작 timer20동안 0.05씩 감소
                        }

                        if (boss.skillTeleport.timer == 50) { //0.5초뒤에 보스 사라짐
                            boss.skillTeleport.status = 1; //0:그대로 , 1: 사라짐
                        }

                        if (boss.skillTeleport.timer == 70) { //1.2초뒤에 캐릭터 위치에 등장
                            boss.skillTeleport.status = 0;
                            boss.x = boss.skillTeleport.destinationX;
                            boss.z = boss.skillTeleport.destinationZ;
                        }
                        if (boss.skillTeleport.timer >= 70 && boss.skillTeleport.timer <= 90) { //보스 크기 서서히 증가
                            boss.skillTeleport.bossSize += 0.05; //0.0에서 시작 timer20동안 0.05씩 증가
                        }

                        if (boss.skillTeleport.timer == 90) {
                            //다시원래대로
                            boss.skillTeleport.timer = 0;
                            boss.skillTeleport.toggle = false;
                            boss.status = BOSS_STATUS_APPEAR;
                        }
                    }
                    else if (boss.skillRazor.toggle == true) {//레이저
                        boss.skillRazor.timer++;
                        if (boss.skillRazor.timer == 1) {
                            boss.skillRazor.status = 1; //1:보스 플레이어 바라보게 하기
                        }
                        if (boss.skillRazor.timer == 25) {
                            boss.skillRazor.size = 0.1;
                            boss.skillRazor.length = 20.0;
                        }
                        if (boss.skillRazor.timer == 95) {
                            boss.skillRazor.status = 0;//0:회전 멈춤
                        }

                        if (boss.skillRazor.timer >= 120 && boss.skillRazor.timer <= 123) { //1.2초뒤에 레이저 발사
                            if (zFlag == 0) {
                                if (player.status == 0) {
                                    player.hp--;
                                    player.status = 1;
                                    if (player.hp == 0) exit(-1);
                                }
                            }
                            boss.skillRazor.size += 0.63333; //최종크기 2.0
                            boss.skillRazor.length = 20.0;
                        }

                        if (boss.skillRazor.timer == 180) {
                            //다시원래대로
                            boss.skillRazor.size = 0.1;
                            boss.skillRazor.length = 20.0;
                            boss.skillRazor.timer = 0;
                            boss.skillRazor.toggle = false;
                            boss.status = BOSS_STATUS_APPEAR;
                        }
                    }
                    else if (boss.skillDrop.toggle == true) { //기둥 공격
                        boss.skillDrop.timer++;
                        if (boss.skillDrop.timer == 1) {
                            //기둥 30개 위치 초기화
                            for (int i = 0; i < boss.skillDrop.number; i++) {
                                int minusX = rand() % 2;
                                int minusZ = rand() % 2;
                                //0~14
                                boss.skillDrop.posX[i] = rand() % 10;
                                boss.skillDrop.posZ[i] = rand() % 10;
                                if (minusX == 1) boss.skillDrop.posX[i] *= -1;
                                if (minusZ == 1) boss.skillDrop.posZ[i] *= -1;
                            }
                        }

                        if (boss.skillDrop.timer >= 120 && boss.skillDrop.timer <= 125) { //0.05초 동안 기둥 커짐
                            boss.skillDrop.size += 1.0;
                            //충돌처리
                            for (int i = 0; i < boss.skillDrop.number; i++) {
                                if (sqrt(pow(boss.skillDrop.posZ[i] - player.z, 2) + pow(boss.skillDrop.posX[i] - player.x, 2)) <= 2) {
                                    if (player.status == 0) {
                                        player.hp--;
                                        player.status = 1;
                                        if (player.hp == 0) exit(-1);
                                    }
                                }
                            }
                        }
                        if (boss.skillDrop.timer == 160) {//0.01초 동안 기둥 작아짐
                            boss.skillDrop.size = 0;
                        }

                        if (boss.skillDrop.timer == 180) { //1.8초후 종료

                            for (int i = 0; i < boss.skillDrop.number; i++) {
                                boss.skillDrop.posX[i] = 0;
                                boss.skillDrop.posZ[i] = 0;
                            }

                            boss.skillDrop.size = 0.05;
                            boss.skillDrop.timer = 0;
                            boss.skillDrop.status = 0;
                            boss.skillDrop.toggle = false;
                            boss.status = BOSS_STATUS_APPEAR;
                        }

                    }
                    else if (boss.skillDash.toggle == true) { //대쉬
                        boss.skillDash.timer++;
                        if (boss.skillDash.timer == 1) { //플레이어 각도 기억
                            boss.skillDash.rememberAngle = turnBoss;
                        }

                        if (boss.skillDash.timer >= 20 && boss.skillDash.timer <= 25) { //돌진
                            if (boss.x <= player.x) {
                                boss.x -= sin(boss.skillDash.rememberAngle);
                            }
                            if (boss.x > player.x) {
                                boss.x += sin(boss.skillDash.rememberAngle);
                                if (boss.z <= player.z) {
                                    boss.z -= cos(boss.skillDash.rememberAngle);
                                }
                                if (boss.z > player.z) {
                                    boss.z += cos(boss.skillDash.rememberAngle);
                                }
                            }
                        }

                        if (boss.skillDash.timer == 26) {
                            boss.skillDash.timer = 0;
                            boss.skillDash.toggle = false;
                            boss.status = BOSS_STATUS_APPEAR;
                        }
                    }
                }
            }

            //보스 충돌처리
            if (boss.x + 1.5 >= player.x && boss.x - 1.5 <= player.x && boss.z + 1.25 >= player.z && boss.z - 1.25 <= player.z) {
                if (player.status == 0) {
                    player.hp--;
                    player.status = 1;
                    if (player.hp == 0) exit(-1);
                }
            }

            //보스 등장 애니메이션
            if (bossCameraAnimationTime > 0 && bossCameraAnimationTime < 500) {
                cameraX += 0.1;
                cameraZ += 0.1;
            }

            //보스 장애물
            if (bossObsToggle && bossObs[199].ObsY > 0) {
                player.x = 0;
                player.z = 5;
                for (int i = 0; i < 200; i++) {
                    if (bossObs[i].obstacleDraw == false) {
                        bossObs[i].obstacleDraw = true;
                        break;
                    }
                }

                for (int i = 0; i < 200; i++) {
                    if (bossObs[i].obstacleDraw == true) {
                        if (bossObs[i].ObsY > 0)
                            bossObs[i].ObsY -= 2;
                    }
                }

                if (bossObs[199].ObsY == 0) {
                    boss.firstAppearance = true; //장애물 애니메이션 끝나면 보스 등장
                }

            }
        }
	}
};