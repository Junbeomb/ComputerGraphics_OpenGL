#pragma once
#include "shader.h"
class PlayTime {
public:
	void setPlayTime() {
        playTimeTimer++;
        std::cout << playTimeTimer << std::endl;
        //스킬x
        if (skillXToggle) {
            skillXCoolTime++;
            if (skillXCoolTime >= 5) {
                skillXToggle = false;
                skillXCoolTime = 0;
            }
        }
        //스킬c
        if (skillCToggle) {
            skillCCoolTime++;
            if (skillCCoolTime >= 5) {
                skillCToggle = false;
                skillCCoolTime = 0;
            }
        }

        //대쉬
        if (zFlag)
        {
            zTimer++;
            if (zTimer == 1)
            {
                zTimer = 0;
                zFlag = false;
            }
        }
        if (!bossToggle)
        {
            if (playTimeTimer >= 1)//3초마다 몬스터 생성
            {
                for (int i = 0; i < 20; i++)
                {
                    if (!monster[i].shouldDraw)
                    {
                        monster[i].shouldDraw = true;
                        monster[i].type = rand() % 3 + 1;
                        monster[i].hp = 3;
                        monster[i].x = (float)(rand() % 2000) / 100 - 10;
                        monster[i].z = (float)(rand() % 2000) / 100 - 10;
                        monster[i].numbering = i;
                        playTimeTimer = 0;
                        monster[i].mbtimer = 0;
                        if (monster[i].type == 2)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                monster[i].mb[j].x = monster[i].x;
                                monster[i].mb[j].z = monster[i].z;
                            }
                        }
                        break;
                    }
                }
            }
        }
	}
};