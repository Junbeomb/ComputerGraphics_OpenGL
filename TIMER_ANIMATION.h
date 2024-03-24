#pragma once
#include "shader.h"

class Animation {
public:
    float bossL = 0;
    float playerL = 0;
    float inner = 0;

	void SetAnimation() {
        animationTimer++; //1�ʴ� 100
        coinRotate += 3.6f;
        //���� �浹ó��
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
        //�÷��̾� �̵�
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
            //��ֹ� ������ �� �����

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
        //�÷��̾ ��� ���� ���� ����
        if (player.status == 1) {
            player.invincibilityTimer++;
            if (player.invincibilityTimer == 200) {
                player.invincibilityTimer = 0;
                player.status = 0;
            }
        }

        if (!bossToggle) {
            //���� �̵�
            for (int i = 0; i < BOSS_GEN; i++) {
                if (monster[i].shouldDraw) {
                    if (monster[i].x > player.x)monster[i].x -= 0.02f;
                    if (monster[i].x < player.x)monster[i].x += 0.02f;
                    if (monster[i].z > player.z)monster[i].z -= 0.02f;
                    if (monster[i].z < player.z)monster[i].z += 0.02f;

                    //�÷��̾�� �浹
                    if (player.status == 0) {
                        //�Ϲ� ����
                        if (sqrt(pow(player.x - monster[i].x, 2) + pow(player.z - monster[i].z, 2)) < 0.2 && monster[i].type != 3) {
                            player.hp--;
                            player.status = 1;
                            if (player.hp == 0) exit(-1);
                        }
                        //���� ����
                        else if (sqrt(pow(player.x - monster[i].x, 2) + pow(player.z - monster[i].z, 2)) < 1 && monster[i].type == 3) {
                            player.hp--;
                            player.status = 1;
                            if (player.hp == 0) exit(-1);
                        }
                    }
                }
                if (monster[i].type == 2) //���� ��ų
                {
                    monster[i].mb[0].x += 0.03f;
                    monster[i].mb[1].x -= 0.03f;
                    monster[i].mb[2].z += 0.03f;
                    monster[i].mb[3].z -= 0.03f;
                    //�÷��̾�� �浹
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
            //1�ʸ��� ���� ���� �Ѿ� �߻�
            if (animationTimer != 0 && animationTimer % 100 == 0) {
                //���� �������ִ� ���� ���ϱ�
                float minDistance = 100.f;
                int minNumbering = -1;
                int checkMon = 0;
                for (int i = 0; i < BOSS_GEN; i++) {
                    if (monster[i].shouldDraw) {
                        checkMon = 1;
                        int tempDistance = sqrt(pow(monster[i].x - player.x, 2) + pow(monster[i].z - player.z, 2));
                        if (minDistance > tempDistance) { //���� ����� �Ÿ����ϱ�
                            minDistance = tempDistance;
                            minNumbering = monster[i].numbering; //���� ����� �Ÿ� ���� ���� �ѹ�
                        }
                    }
                }
                if (checkMon == 1) {
                    //�� ���� ���� �Ѿ� ���󰡰� �ϱ�
                    for (int i = 0; i < BULLET_MAX; i++) {
                        if (bullet[i].shouldDraw == false) { //��� ���¿� �ִ� �Ѿ� �ϳ� �߻��� �����
                            bullet[i].shouldDraw = true;
                            bullet[i].currentY = 0.5f;
                            bullet[i].currentX = player.x;
                            bullet[i].currentZ = player.z;
                            bullet[i].monsterNum = minNumbering; //���� ���� �ѹ�
                            break;
                        }
                    }
                }
            }
        }
        else { //�������� �Ѿ˹߻�
            //1�ʸ��� ���� ���� �Ѿ� �߻�
            if (animationTimer != 0 && animationTimer % 100 == 0) {
                for (int i = 0; i < BULLET_MAX; i++) {
                    if (bullet[i].shouldDraw == false) { //��� ���¿� �ִ� �Ѿ� �ϳ� �߻��� �����
                        bullet[i].shouldDraw = true;
                        bullet[i].currentY = 0.5f;
                        bullet[i].currentX = player.x;
                        bullet[i].currentZ = player.z;
                        break;
                    }
                }
            }
        }


        //����
        if (bossToggle) {

            if (bossCameraAnimationTime < 400)
                bossCameraAnimationTime++;

            //���� ù ���� ��
            if (boss.firstAppearance) {
                boss.y -= 0.5;
                if (boss.y <= 0.5) {
                    boss.firstAppearance = false;
                }
            }
            else if (bossCameraAnimationTime >= 400) { //���� ���� �ִϸ��̼� ������, ī�޶� �ִϸ��̼� ������ �̵�
                boss.bossTimer++;

                //ĳ���Ϳ��� �̵� (������ �Ϲ� ������ ����)
                if (boss.status == BOSS_STATUS_APPEAR) {
                    if (boss.x > player.x)boss.x -= 0.01f;
                    if (boss.x < player.x)boss.x += 0.01f;
                    if (boss.z > player.z)boss.z -= 0.01f;
                    if (boss.z < player.z)boss.z += 0.01f;

                    //���� �÷��̾� �ٶ󺸰� �ϱ�
                    bossL = boss.x - player.x;
                    playerL = boss.z - player.z;
                    inner = atan2(playerL, bossL);
                    turnBoss = inner * 180 / M_PI;
                }

                if (boss.skillRazor.toggle == true && boss.skillRazor.status == 1) {
                    //���� �÷��̾� �ٶ󺸰� �ϱ�
                    bossL = boss.x - player.x;
                    playerL = boss.z - player.z;
                    inner = atan2(playerL, bossL);
                    turnBoss = inner * 180 / M_PI;
                }

                if (boss.bossTimer != 0 && boss.bossTimer % 300 == 0) { //3�ʿ� �ѹ��� ��ų �ߵ�

                    int randomSkill = -1;
                    if (boss.status == BOSS_STATUS_APPEAR) //(������ �Ϲ� ������ ����)
                        randomSkill = rand() % 4; //��ų �ֻ��� ������

                    if (randomSkill == BOSS_TELEPORT) { // �ڷ���Ʈ
                        boss.status = BOSS_STATUS_SKILL; // ��ų �����
                        boss.skillTeleport.toggle = true;
                        boss.skillTeleport.status = 0;
                    }
                    else if (randomSkill == BOSS_RAZOR) {
                        boss.status = BOSS_STATUS_SKILL; // ��ų �����
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

                if (boss.status == BOSS_STATUS_SKILL) { //������ ��ų �����
                    if (boss.skillTeleport.toggle == true) { //�ڷ���Ʈ
                        boss.skillTeleport.timer++;

                        //ó���� �÷��̾� ��ġ ���
                        if (boss.skillTeleport.timer == 30) {
                            boss.skillTeleport.destinationX = player.x;
                            boss.skillTeleport.destinationZ = player.z;
                        }

                        if (boss.skillTeleport.timer >= 30 && boss.skillTeleport.timer <= 50) { //���� ũ�� ������ ����
                            boss.skillTeleport.bossSize -= 0.05; //1.0���� ���� timer20���� 0.05�� ����
                        }

                        if (boss.skillTeleport.timer == 50) { //0.5�ʵڿ� ���� �����
                            boss.skillTeleport.status = 1; //0:�״�� , 1: �����
                        }

                        if (boss.skillTeleport.timer == 70) { //1.2�ʵڿ� ĳ���� ��ġ�� ����
                            boss.skillTeleport.status = 0;
                            boss.x = boss.skillTeleport.destinationX;
                            boss.z = boss.skillTeleport.destinationZ;
                        }
                        if (boss.skillTeleport.timer >= 70 && boss.skillTeleport.timer <= 90) { //���� ũ�� ������ ����
                            boss.skillTeleport.bossSize += 0.05; //0.0���� ���� timer20���� 0.05�� ����
                        }

                        if (boss.skillTeleport.timer == 90) {
                            //�ٽÿ������
                            boss.skillTeleport.timer = 0;
                            boss.skillTeleport.toggle = false;
                            boss.status = BOSS_STATUS_APPEAR;
                        }
                    }
                    else if (boss.skillRazor.toggle == true) {//������
                        boss.skillRazor.timer++;
                        if (boss.skillRazor.timer == 1) {
                            boss.skillRazor.status = 1; //1:���� �÷��̾� �ٶ󺸰� �ϱ�
                        }
                        if (boss.skillRazor.timer == 25) {
                            boss.skillRazor.size = 0.1;
                            boss.skillRazor.length = 20.0;
                        }
                        if (boss.skillRazor.timer == 95) {
                            boss.skillRazor.status = 0;//0:ȸ�� ����
                        }

                        if (boss.skillRazor.timer >= 120 && boss.skillRazor.timer <= 123) { //1.2�ʵڿ� ������ �߻�
                            if (zFlag == 0) {
                                if (player.status == 0) {
                                    player.hp--;
                                    player.status = 1;
                                    if (player.hp == 0) exit(-1);
                                }
                            }
                            boss.skillRazor.size += 0.63333; //����ũ�� 2.0
                            boss.skillRazor.length = 20.0;
                        }

                        if (boss.skillRazor.timer == 180) {
                            //�ٽÿ������
                            boss.skillRazor.size = 0.1;
                            boss.skillRazor.length = 20.0;
                            boss.skillRazor.timer = 0;
                            boss.skillRazor.toggle = false;
                            boss.status = BOSS_STATUS_APPEAR;
                        }
                    }
                    else if (boss.skillDrop.toggle == true) { //��� ����
                        boss.skillDrop.timer++;
                        if (boss.skillDrop.timer == 1) {
                            //��� 30�� ��ġ �ʱ�ȭ
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

                        if (boss.skillDrop.timer >= 120 && boss.skillDrop.timer <= 125) { //0.05�� ���� ��� Ŀ��
                            boss.skillDrop.size += 1.0;
                            //�浹ó��
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
                        if (boss.skillDrop.timer == 160) {//0.01�� ���� ��� �۾���
                            boss.skillDrop.size = 0;
                        }

                        if (boss.skillDrop.timer == 180) { //1.8���� ����

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
                    else if (boss.skillDash.toggle == true) { //�뽬
                        boss.skillDash.timer++;
                        if (boss.skillDash.timer == 1) { //�÷��̾� ���� ���
                            boss.skillDash.rememberAngle = turnBoss;
                        }

                        if (boss.skillDash.timer >= 20 && boss.skillDash.timer <= 25) { //����
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

            //���� �浹ó��
            if (boss.x + 1.5 >= player.x && boss.x - 1.5 <= player.x && boss.z + 1.25 >= player.z && boss.z - 1.25 <= player.z) {
                if (player.status == 0) {
                    player.hp--;
                    player.status = 1;
                    if (player.hp == 0) exit(-1);
                }
            }

            //���� ���� �ִϸ��̼�
            if (bossCameraAnimationTime > 0 && bossCameraAnimationTime < 500) {
                cameraX += 0.1;
                cameraZ += 0.1;
            }

            //���� ��ֹ�
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
                    boss.firstAppearance = true; //��ֹ� �ִϸ��̼� ������ ���� ����
                }

            }
        }
	}
};