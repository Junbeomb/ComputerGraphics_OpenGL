#pragma once
#include "shader.h"

class TimerBullet {
public:
	void SetBullet() {
        //총알 날라가게 하기
        if (!bossToggle) {
            for (int i = 0; i < BULLET_MAX; i++) {
                if (bullet[i].shouldDraw == true) { //발사 모드 총알
                    int desMonNum = bullet[i].monsterNum;
                    if (bullet[i].skillEight == 0) {
                        if (monster[desMonNum].x > bullet[i].currentX) {
                            bullet[i].currentX += 0.02;
                        }
                        else {
                            bullet[i].currentX -= 0.02;
                        }

                        if (monster[desMonNum].z > bullet[i].currentZ) {
                            bullet[i].currentZ += 0.02;
                        }
                        else {
                            bullet[i].currentZ -= 0.02;
                        }
                    }
                    else { //스킬 총알
                        bullet[i].skillEightCount++;
                        if (bullet[i].skillEight == 1) {
                            bullet[i].currentZ -= 0.02;
                        }
                        else if (bullet[i].skillEight == 2) {
                            bullet[i].currentZ -= 0.02;
                            bullet[i].currentX += 0.02;
                        }
                        else if (bullet[i].skillEight == 3) {
                            bullet[i].currentX += 0.02;
                        }
                        else if (bullet[i].skillEight == 4) {
                            bullet[i].currentX += 0.02;
                            bullet[i].currentZ += 0.02;
                        }
                        else if (bullet[i].skillEight == 5) {
                            bullet[i].currentZ += 0.02;
                        }
                        else if (bullet[i].skillEight == 6) {
                            bullet[i].currentZ += 0.02;
                            bullet[i].currentX -= 0.02;
                        }
                        else if (bullet[i].skillEight == 7) {
                            bullet[i].currentX -= 0.02;
                        }
                        else if (bullet[i].skillEight == 8) {
                            bullet[i].currentX -= 0.02;
                            bullet[i].currentZ -= 0.02;
                        }
                    }

                    if (bullet[i].skillEight == 0) {
                        //총알이 해당 몬스터 안에 들어오면
                        if (sqrt(pow(monster[desMonNum].x - bullet[i].currentX, 2) + pow(monster[desMonNum].z - bullet[i].currentZ, 2)) <= 0.5) {
                            bullet[i].shouldDraw = false;
                            bullet[i].currentX = 0;
                            bullet[i].currentZ = 0;
                            bullet[i].currentY = 20;
                            if (monster[desMonNum].hp > 0) {
                                monster[desMonNum].hp -= player.atk;
                                if (monster[desMonNum].hp <= 0) {
                                    for (int j = 0; j < 20; j++)
                                    {
                                        if (!item[j].shouldDraw)
                                        {
                                            item[j].x = monster[i].x;
                                            item[j].z = monster[i].z;
                                            item[j].shouldDraw = true;
                                            break;
                                        }
                                    }

                                    countMonCatch++;
                                    if (countMonCatch == 20) { //20마리 잡으면 보스 소환
                                        bossToggle = true;
                                        boss.status = BOSS_STATUS_APPEAR;
                                        boss.firstAppearance = false; //장애물애니메이션 끝나면 true 로 바꿈
                                        boss.x = 0;
                                        boss.z = 0;
                                        boss.y = 20;
                                        bossCameraAnimationTime = 0;
                                        cameraX = 0;
                                        cameraZ = 0;

                                        //보스 장애물
                                        bossObsToggle = !bossObsToggle;
                                        for (int i = 0; i < 200; i++) {
                                            bossObs[i].obstacleDraw = false;
                                            bossObs[i].ObsX = 10 * cos(i * 1.8);
                                            bossObs[i].ObsZ = 10 * sin(i * 1.8);
                                            bossObs[i].ObsY = 20;
                                        }

                                        for (int i = 0; i < 20; i++) {
                                            monster[i].shouldDraw = false;

                                        }
                                    }

                                    monster[desMonNum].x = -100;
                                    monster[desMonNum].z = -100;
                                    monster[desMonNum].shouldDraw = false;

                                    for (int i = 0; i < BULLET_MAX; i++) {
                                        if (bullet[i].shouldDraw == true && bullet[i].monsterNum == desMonNum) {
                                            for (int i = 0; i < BOSS_GEN; i++) {
                                                if (monster[i].shouldDraw == true) {
                                                    bullet[i].monsterNum = i;
                                                    break;
                                                }
                                            }
                                        }
                                    }

                                }
                            }
                        }
                    }
                    else { //스킬 총알
                        if (bullet[i].skillEightCount > 3000) {
                            bullet[i].shouldDraw = false;
                            bullet[i].currentX = 0;
                            bullet[i].currentZ = 0;
                            bullet[i].currentY = 20;
                            bullet[i].skillEightCount = 0;
                            bullet[i].skillEight = 0;
                        }
                        else {
                            for (int j = 0; j < BOSS_GEN; j++) {
                                if (monster[j].shouldDraw == true) {
                                    if (sqrt(pow(monster[j].x - bullet[i].currentX, 2) + pow(monster[j].z - bullet[i].currentZ, 2)) <= 0.5) {

                                        bullet[i].shouldDraw = false;
                                        bullet[i].currentX = 0;
                                        bullet[i].currentZ = 0;
                                        bullet[i].currentY = 20;
                                        if (monster[j].hp > 0) {
                                            monster[j].hp -= player.atk;
                                            if (monster[j].hp == 0) {
                                                //몬스터 아이템
                                                for (int k = 0; k < 20; k++)
                                                {
                                                    if (!item[k].shouldDraw)
                                                    {
                                                        item[k].x = monster[j].x;
                                                        item[k].z = monster[j].z;
                                                        item[k].shouldDraw = true;
                                                        break;
                                                    }
                                                }

                                                countMonCatch++;
                                                if (countMonCatch == 20) { //20마리 잡으면 보스 소환
                                                    bossToggle = true;
                                                    boss.status = BOSS_STATUS_APPEAR;
                                                    boss.firstAppearance = false; //장애물애니메이션 끝나면 true 로 바꿈
                                                    boss.x = 0;
                                                    boss.z = 0;
                                                    boss.y = 20;
                                                    bossCameraAnimationTime = 0;
                                                    cameraX = 0;
                                                    cameraZ = 0;

                                                    //보스 장애물
                                                    bossObsToggle = !bossObsToggle;
                                                    for (int o = 0; o < 200; o++) {
                                                        bossObs[o].obstacleDraw = false;
                                                        bossObs[o].ObsX = 10 * cos(o * 1.8);
                                                        bossObs[o].ObsZ = 10 * sin(o * 1.8);
                                                        bossObs[o].ObsY = 20;
                                                    }

                                                    for (int t = 0; t < 20; t++) {
                                                        monster[t].shouldDraw = false;
                                                    }
                                                }
                                                monster[j].x = -100;
                                                monster[j].z = -100;
                                                monster[j].shouldDraw = false;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } //몬스터
        //보스
        else {
            for (int i = 0; i < BULLET_MAX; i++) {
                if (bullet[i].shouldDraw == true) { //발사 모드 총알
                    if (boss.x > bullet[i].currentX) {
                        bullet[i].currentX += 0.02;
                    }
                    else {
                        bullet[i].currentX -= 0.02;
                    }

                    if (boss.z > bullet[i].currentZ) {
                        bullet[i].currentZ += 0.02;
                    }
                    else {
                        bullet[i].currentZ -= 0.02;
                    }

                    //총알이 해당 몬스터 안에 들어오면
                    if (sqrt(pow(boss.x - bullet[i].currentX, 2) + pow(boss.z - bullet[i].currentZ, 2)) <= 0.5) {

                        bullet[i].shouldDraw = false;
                        bullet[i].currentX = 0;
                        bullet[i].currentZ = 0;
                        bullet[i].currentY = 20;

                        if (boss.hp > 0) {
                            if (bullet[i].skillBig == 1) {
                                bullet[i].skillBig = 0;
                                boss.hp -= player.atk * 3;
                            }
                            else {
                                boss.hp -= player.atk;
                            }
                            if (boss.hp <= 0) {
                                std::cout << "게임종료";
                                boss.y = 20;
                                boss.status = BOSS_STATUS_SKILL;
                            }
                        }

                    }
                }
            }
        }
	}
};