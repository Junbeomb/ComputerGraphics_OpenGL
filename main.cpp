#define _CRT_SECURE_NO_WARNINGS
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

#include "shader.h"
#include "load_OBJ.h"

Objectload Hero_Load;
GLint Hero = Hero_Load.loadObj("OBJ/minecraft_steve.obj");

Objectload Boss_Load;
GLint BossMon = Boss_Load.loadObj("OBJ/Boss.obj");

Objectload Cylinder_Load;
GLint Cylinder = Cylinder_Load.loadObj("OBJ/Cylinder.obj");

Objectload Floor_Load;
GLint Floor = Floor_Load.loadObj("OBJ/Floor.obj");

Objectload Cone_Load;
GLint Cone = Cone_Load.loadObj("OBJ/Cone.obj");

Objectload Sphere_Load;
GLint Sphere = Sphere_Load.loadObj("OBJ/sphere.obj");

Objectload HP_Load;
GLint HP = HP_Load.loadObj("OBJ/Cylinder.obj");

Objectload Coin_Load;
GLint Coin = Coin_Load.loadObj("OBJ/coin.obj");

void initTextures() {
    Hero_Load.InitTexture("TEXTURE/Minecraft_steve_skin.jpg");
    Boss_Load.InitTexture("TEXTURE/BossRough_TEX.jpg");
    Cylinder_Load.InitTexture("TEXTURE/Boss_TEX.jpg");
    Floor_Load.InitTexture("TEXTURE/Floor_TEX.jpg");
    Cone_Load.InitTexture("TEXTURE/Cone_TEX.jpg");
    Sphere_Load.InitTexture("TEXTURE/sphere_TEX.jpg");
    Coin_Load.InitTexture("TEXTURE/coin_TEX.jpg");
    HP_Load.InitTexture("TEXTURE/sphere_TEX.jpg");
}

GLuint VAO_Hero, VBO_Hero_VERTEX, VBO_Hero_NORMAL, VBO_Hero_UV;
GLuint VAO_Boss, VBO_Boss_VERTEX, VBO_Boss_NORMAL, VBO_Boss_UV;
GLuint VAO_Cylinder, VBO_Cylinder_VERTEX, VBO_Cylinder_NORMAL, VBO_Cylinder_UV;
GLuint VAO_Floor, VBO_Floor_VERTEX, VBO_Floor_NORMAL, VBO_Floor_UV;
GLuint VAO_Cone, VBO_Cone_VERTEX, VBO_Cone_NORMAL, VBO_Cone_UV;
GLuint VAO_Sphere, VBO_Sphere_VERTEX, VBO_Sphere_NORMAL, VBO_Sphere_UV;
GLuint VAO_HP, VBO_HP_VERTEX, VBO_HP_NORMAL, VBO_HP_UV;
GLuint VAO_COIN, VBO_COIN_VERTEX, VBO_COIN_NORMAL, VBO_COIN_UV;
GLuint VAO_skybox, VBO_pos_skybox;

unsigned int skyTexture;

std::vector<std::string> faces
{
    "TEXTURE/right.jpg",
    "TEXTURE/left.jpg",
    "TEXTURE/top.jpg",
    "TEXTURE/bottom.jpg",
    "TEXTURE/front.jpg",
    "TEXTURE/back.jpg",
};
int playTimeTimer{ 0 };
int animationTimer{ 0 };
GLvoid SpecialKeyBoard(int key, int x, int y);

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

void InitBuffer() {

    //Hero
    glGenVertexArrays(1, &VAO_Hero);
    glBindVertexArray(VAO_Hero);
    //vertex
    glGenBuffers(1, &VBO_Hero_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Hero_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Hero_Load.outvertex.size() * sizeof(glm::vec3), &Hero_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Hero_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Hero_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Hero_Load.outnormal.size() * sizeof(glm::vec3), &Hero_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Hero_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Hero_UV);
    glBufferData(GL_ARRAY_BUFFER, Hero_Load.outuv.size() * sizeof(glm::vec2), &Hero_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //Boss
    glGenVertexArrays(1, &VAO_Boss);
    glBindVertexArray(VAO_Boss);
    //vertex
    glGenBuffers(1, &VBO_Boss_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Boss_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Boss_Load.outvertex.size() * sizeof(glm::vec3), &Boss_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Boss_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Boss_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Boss_Load.outnormal.size() * sizeof(glm::vec3), &Boss_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Boss_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Boss_UV);
    glBufferData(GL_ARRAY_BUFFER, Boss_Load.outuv.size() * sizeof(glm::vec2), &Boss_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //Cylinder
    glGenVertexArrays(1, &VAO_Cylinder);
    glBindVertexArray(VAO_Cylinder);
    //vertex
    glGenBuffers(1, &VBO_Cylinder_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cylinder_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Cylinder_Load.outvertex.size() * sizeof(glm::vec3), &Cylinder_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Cylinder_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cylinder_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Cylinder_Load.outnormal.size() * sizeof(glm::vec3), &Cylinder_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Cylinder_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cylinder_UV);
    glBufferData(GL_ARRAY_BUFFER, Cylinder_Load.outuv.size() * sizeof(glm::vec2), &Cylinder_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //Floor
    glGenVertexArrays(1, &VAO_Floor);
    glBindVertexArray(VAO_Floor);
    //vertex
    glGenBuffers(1, &VBO_Floor_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Floor_Load.outvertex.size() * sizeof(glm::vec3), &Floor_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Floor_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Floor_Load.outnormal.size() * sizeof(glm::vec3), &Floor_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Floor_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor_UV);
    glBufferData(GL_ARRAY_BUFFER, Floor_Load.outuv.size() * sizeof(glm::vec2), &Floor_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //Cone
    glGenVertexArrays(1, &VAO_Cone);
    glBindVertexArray(VAO_Cone);
    //vertex
    glGenBuffers(1, &VBO_Cone_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cone_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Cone_Load.outvertex.size() * sizeof(glm::vec3), &Cone_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Cone_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cone_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Cone_Load.outnormal.size() * sizeof(glm::vec3), &Cone_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Cone_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cone_UV);
    glBufferData(GL_ARRAY_BUFFER, Cone_Load.outuv.size() * sizeof(glm::vec2), &Cone_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //Sphere
    glGenVertexArrays(1, &VAO_Sphere);
    glBindVertexArray(VAO_Sphere);
    //vertex
    glGenBuffers(1, &VBO_Sphere_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Sphere_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Sphere_Load.outvertex.size() * sizeof(glm::vec3), &Sphere_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Sphere_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Sphere_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Sphere_Load.outnormal.size() * sizeof(glm::vec3), &Sphere_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Sphere_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Sphere_UV);
    glBufferData(GL_ARRAY_BUFFER, Sphere_Load.outuv.size() * sizeof(glm::vec2), &Sphere_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //HP
    glGenVertexArrays(1, &VAO_HP);
    glBindVertexArray(VAO_HP);
    //vertex
    glGenBuffers(1, &VBO_HP_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_HP_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, HP_Load.outvertex.size() * sizeof(glm::vec3), &HP_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_HP_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_HP_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, HP_Load.outnormal.size() * sizeof(glm::vec3), &HP_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_HP_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_HP_UV);
    glBufferData(GL_ARRAY_BUFFER, HP_Load.outuv.size() * sizeof(glm::vec2), &HP_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //Coin
    glGenVertexArrays(1, &VAO_COIN);
    glBindVertexArray(VAO_COIN);
    //vertex
    glGenBuffers(1, &VBO_COIN_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_COIN_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Coin_Load.outvertex.size() * sizeof(glm::vec3), &Coin_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_COIN_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_COIN_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Coin_Load.outnormal.size() * sizeof(glm::vec3), &Coin_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_COIN_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_COIN_UV);
    glBufferData(GL_ARRAY_BUFFER, Coin_Load.outuv.size() * sizeof(glm::vec2), &Coin_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //skybox
    float SkyboxVertices[] =
    {
            -30.0f,  30.0f, -30.0f,
            -30.0f, -30.0f, -30.0f,
             30.0f, -30.0f, -30.0f,
             30.0f, -30.0f, -30.0f,
             30.0f,  30.0f, -30.0f,
            -30.0f,  30.0f, -30.0f,

            -30.0f, -30.0f,  30.0f,
            -30.0f, -30.0f, -30.0f,
            -30.0f,  30.0f, -30.0f,
            -30.0f,  30.0f, -30.0f,
            -30.0f,  30.0f,  30.0f,
            -30.0f, -30.0f,  30.0f,

             30.0f, -30.0f, -30.0f,
             30.0f, -30.0f,  30.0f,
             30.0f,  30.0f,  30.0f,
             30.0f,  30.0f,  30.0f,
             30.0f,  30.0f, -30.0f,
             30.0f, -30.0f, -30.0f,

            -30.0f, -30.0f,  30.0f,
            -30.0f,  30.0f,  30.0f,
             30.0f,  30.0f,  30.0f,
             30.0f,  30.0f,  30.0f,
             30.0f, -30.0f,  30.0f,
            -30.0f, -30.0f,  30.0f,

            -30.0f,  30.0f, -30.0f,
             30.0f,  30.0f, -30.0f,
             30.0f,  30.0f,  30.0f,
             30.0f,  30.0f,  30.0f,
            -30.0f,  30.0f,  30.0f,
            -30.0f,  30.0f, -30.0f,

            -30.0f, -30.0f, -30.0f,
            -30.0f, -30.0f,  30.0f,
             30.0f, -30.0f, -30.0f,
             30.0f, -30.0f, -30.0f,
            -30.0f, -30.0f,  30.0f,
             30.0f, -30.0f,  30.0f
    };
    glGenVertexArrays(1, &VAO_skybox);
    glGenBuffers(1, &VBO_pos_skybox);
    glBindVertexArray(VAO_skybox);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_pos_skybox);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SkyboxVertices), &SkyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

GLvoid drawScene();
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid KeyBoardUp(unsigned char key, int x, int y);
GLvoid Reshape(int w, int h);
GLvoid TimerFunc(int x);
GLvoid Motion(int x, int y);

int main(int argc, char** argv)
{
    for (int i = 0; i < 20; i++)
    {
        monster[i].shouldDraw = false;
    }
    player.atk = 1;
    player.speed = 1;
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Example1");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    skyShaderID.makeShader("skyBoxFragmentVertex.glsl", "skyBoxFragment.glsl");
    InitBuffer();
    initTextures();
    skyTexture = loadCubemap(faces);
    shaderID.makeShader("vertexShaderSource.glsl", "fragmentShaderSource.glsl");
    glutKeyboardFunc(KeyBoard);
    glutKeyboardUpFunc(KeyBoardUp);
    glutSpecialFunc(SpecialKeyBoard);
    glutMotionFunc(Motion);

    glutTimerFunc(1, TimerFunc,BULLET);
    glutTimerFunc(10, TimerFunc, ANIMATION);
    glutTimerFunc(1000, TimerFunc, PLAYTIME);

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}

GLvoid drawScene()
{
    shaderID.use();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //조명
    shaderID.setVec3("lightPos", 0.f, 3.f, 0.f);
    shaderID.setVec3("lightColor", 1.f, 1.f, 1.f);


    //투영 변환
    glm::mat4 pTransform = glm::mat4(1.0f);
    pTransform = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 50.0f);
    shaderID.setMat4("projectionTransform", pTransform);

    //뷰잉 변환
    glm::vec3 cameraPos;
    glm::vec3 cameraDirection;
    glm::vec3 cameraUp;
    glm::mat4 vTransform = glm::mat4(1.0f);
    if (topViewToggle) { //탑뷰 모드
        vTransform = glm::mat4(1.0f);
        cameraPos = glm::vec3(topViewCameraX, 40.0f, topViewCameraZ);
        cameraDirection = glm::vec3(0.0f + topViewCameraX, 0.0f, 0.0f + topViewCameraZ);
        cameraUp = glm::vec3(0.0f, 0.0f, -1.0f);
        vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
        shaderID.setMat4("viewTransform", vTransform);
        shaderID.setVec3("viewPos", 0, 40.0f, 0);
    }
    else {
        if (bossCameraAnimationTime > 0 && bossCameraAnimationTime < 400) {
            vTransform = glm::mat4(1.0f);
            cameraPos = glm::vec3(12 * sin(cameraX * 0.01), 1, 12 * cos(cameraZ * 0.01));
            cameraDirection = glm::vec3(0, 0, 0);
            cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
            vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
            shaderID.setMat4("viewTransform", vTransform);
            shaderID.setVec3("viewPos", player.x, 0, player.z);
        }
        else { //카메라 일반 상태
            vTransform = glm::mat4(1.0f);
            cameraPos = glm::vec3(player.x + sin(player.direction)*5, 2.5f, player.z + cos(player.direction) * 5);
            cameraDirection = glm::vec3(player.x, 0.8f, player.z);
            cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
            vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
            shaderID.setMat4("viewTransform", vTransform);
            shaderID.setVec3("viewPos", player.x, 1, player.z);
        }
    }
    //바닥
    glBindTexture(GL_TEXTURE_2D, Floor_Load.texture);
    glm::mat4 floorTransform = glm::mat4(1.0f);
    floorTransform = glm::scale(floorTransform, glm::vec3(MAP_SIZE, 0.05f, MAP_SIZE));
    shaderID.setMat4("modelTransform", floorTransform);
    shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
    glBindVertexArray(VAO_Floor);
    glDrawArrays(GL_TRIANGLES, 0, Floor);

    //플레이어

    //플레이어 카메라 등지게 하기
    glm::vec3 direction = normalize(cameraPos - glm::vec3(player.x,1.5f,player.z));
    float atanA = atan2(direction.x, direction.z);
    float degree = glm::degrees(atanA);

    if (player.status == 0) {
        glBindTexture(GL_TEXTURE_2D, Hero_Load.texture);
        glm::mat4 PlayerTransform = glm::mat4(1.0f);
        PlayerTransform = glm::translate(PlayerTransform, glm::vec3(player.x, 0.25f, player.z));
        PlayerTransform = glm::rotate(PlayerTransform, glm::radians(degree+90), glm::vec3(0.f, 1.f, 0.f));
        PlayerTransform = glm::scale(PlayerTransform, glm::vec3(0.05f, 0.05f, 0.05f));
        shaderID.setMat4("modelTransform", PlayerTransform);
        shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
        glBindVertexArray(VAO_Hero);
        glDrawArrays(GL_TRIANGLES, 0, Hero);
    }
    else { //플레이어 무적 상태
        if ((player.invincibilityTimer / 10) % 2 == 0) {
            glBindTexture(GL_TEXTURE_2D, Hero_Load.texture);
            glm::mat4 PlayerTransform = glm::mat4(1.0f);
            PlayerTransform = glm::translate(PlayerTransform, glm::vec3(player.x, 0.25f, player.z));
            PlayerTransform = glm::rotate(PlayerTransform, glm::radians(degree + 90), glm::vec3(0, 1.f, 0));
            PlayerTransform = glm::scale(PlayerTransform, glm::vec3(0.05f, 0.05f, 0.05f));
            shaderID.setMat4("modelTransform", PlayerTransform);
            shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
            glBindVertexArray(VAO_Hero);
            glDrawArrays(GL_TRIANGLES, 0, Hero);
        }
    }

    //플레이어 총알
    for (int i = 0; i < BULLET_MAX; i++) {
        if (bullet[i].shouldDraw == true) {
            if (bullet[i].skillBig) {
                glBindTexture(GL_TEXTURE_2D, Sphere_Load.texture);
                glm::mat4 PlayerBullet = glm::mat4(1.0f);
                PlayerBullet = glm::translate(PlayerBullet, glm::vec3(bullet[i].currentX, bullet[i].currentY, bullet[i].currentZ));
                PlayerBullet = glm::scale(PlayerBullet, glm::vec3(0.5f, 0.5f, 0.5f));
                shaderID.setMat4("modelTransform", PlayerBullet);
                shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
                glBindVertexArray(VAO_Sphere);
                glDrawArrays(GL_TRIANGLES, 0, Sphere);
            }
            else {
                glBindTexture(GL_TEXTURE_2D, Sphere_Load.texture);
                glm::mat4 PlayerBullet = glm::mat4(1.0f);
                PlayerBullet = glm::translate(PlayerBullet, glm::vec3(bullet[i].currentX, bullet[i].currentY, bullet[i].currentZ));
                PlayerBullet = glm::scale(PlayerBullet, glm::vec3(0.05f, 0.05f, 0.05f));
                shaderID.setMat4("modelTransform", PlayerBullet);
                shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
                glBindVertexArray(VAO_Sphere);
                glDrawArrays(GL_TRIANGLES, 0, Sphere);
            }
        }
    }
    //아이템
    glm::mat4 ItemTransform = glm::mat4(1.0f);
    glBindTexture(GL_TEXTURE_2D, Coin_Load.texture);
    glBindVertexArray(VAO_COIN);
    for (int i = 0; i < 20; i++)
    {
        if (item[i].shouldDraw)
        {
            
            ItemTransform = glm::mat4(1.0f);
            ItemTransform = glm::translate(ItemTransform, glm::vec3(item[i].x, 0.5f, item[i].z));
            ItemTransform = glm::rotate(ItemTransform, glm::radians(coinRotate), glm::vec3(0, 1.f, 0));
            ItemTransform = glm::scale(ItemTransform, glm::vec3(0.02f, 0.02f, 0.02f));
            shaderID.setMat4("modelTransform", ItemTransform);
            shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
            
            glDrawArrays(GL_TRIANGLES, 0, Coin);
        }
    }
    //몬스터
    glBindTexture(GL_TEXTURE_2D, Sphere_Load.texture);

    glm::mat4 MonsterTransform = glm::mat4(1.0f);
    glm::mat4 mpTransform = glm::mat4(1.0f);
    glm::mat4 pmTransform = glm::mat4(1.0f);
    for (int i = 0; i < 20; i++)
    {
        MonsterTransform = glm::mat4(1.0f);
        MonsterTransform = glm::translate(MonsterTransform, glm::vec3(monster[i].x, 0.05f, monster[i].z));
        MonsterTransform = glm::scale(MonsterTransform, glm::vec3(0.05f, 0.05f, 0.05f));
        shaderID.setMat4("modelTransform", MonsterTransform);
        glBindVertexArray(VAO_Hero);
        switch (monster[i].type)
        {
        case 1:
            shaderID.setVec3("objectColor", 0.f, 1.f, 0.f);
            if (monster[i].shouldDraw)glDrawArrays(GL_TRIANGLES, 0, Hero);
            break;
        case 2:
            shaderID.setVec3("objectColor", 1.f, 1.f, 0.f);
            if (monster[i].shouldDraw)
            {
                glDrawArrays(GL_TRIANGLES, 0, Hero);
                for (int j = 0; j < 4; j++)
                {
                    pmTransform = glm::mat4(1.0f);
                    pmTransform = glm::translate(pmTransform, glm::vec3(monster[i].mb[j].x, 0.25f, monster[i].mb[j].z));
                    pmTransform = glm::scale(pmTransform, glm::vec3(0.05f, 0.05f, 0.05f));
                    shaderID.setMat4("modelTransform", pmTransform);
                    glBindVertexArray(VAO_Sphere);
                    shaderID.setVec3("objectColor", 1.f, 0.f, 1.f);
                    glDrawArrays(GL_TRIANGLES, 0, Sphere);
                }
            }
            break;
        case 3:
            shaderID.setVec3("objectColor", 0.f, 1.f, 1.f);
            if (monster[i].shouldDraw)
            {
                glDrawArrays(GL_TRIANGLES, 0, Sphere);
                pmTransform = glm::mat4(1.0f);
                pmTransform = glm::translate(pmTransform, glm::vec3(monster[i].x, 0.05f, monster[i].z));
                pmTransform = glm::scale(pmTransform, glm::vec3(1.f, 0.005f, 1.f));
                shaderID.setMat4("modelTransform", pmTransform);
                glBindVertexArray(VAO_Sphere);
                shaderID.setVec3("objectColor", 1.f, 0.f, 1.f);
                glDrawArrays(GL_TRIANGLES, 0, Sphere);
            }
            break;
        }

    }

    glBindTexture(GL_TEXTURE_2D, Boss_Load.texture);
    //보스 몬스터
    if (bossToggle) {
        if (boss.skillTeleport.status != 1) { //텔레포트 중이 아닐 때
            //보스 그리기
            glBindVertexArray(VAO_Boss);
            shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
            glm::mat4 BossTransform = glm::mat4(1.0f);
            BossTransform = glm::translate(BossTransform, glm::vec3(boss.x, boss.y - 0.6, boss.z));
            BossTransform = glm::rotate(BossTransform, glm::radians(turnBoss * -1 - 90), glm::vec3(0, 1.f, 0));
            BossTransform = glm::scale(BossTransform, glm::vec3(boss.skillTeleport.bossSize, boss.skillTeleport.bossSize, boss.skillTeleport.bossSize)); //텔레포트 시
            BossTransform = glm::scale(BossTransform, glm::vec3(0.5f, 0.5f, 0.5f));
            shaderID.setMat4("modelTransform", BossTransform);
            glDrawArrays(GL_TRIANGLES, 0, BossMon);


            //레이저 스킬
            if (boss.skillRazor.toggle == true) {
                glBindTexture(GL_TEXTURE_2D, Cylinder_Load.texture);
                glBindVertexArray(VAO_Cylinder);
                shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
                glm::mat4 BossRazor = glm::mat4(1.0f);
                BossRazor = glm::translate(BossRazor, glm::vec3(boss.x, boss.y + 2.7, boss.z));
                BossRazor = glm::rotate(BossRazor, glm::radians(turnBoss * -1 - 90), glm::vec3(0, 1.f, 0));
                BossRazor = glm::rotate(BossRazor, glm::radians(90.f), glm::vec3(1.f, 0, 0));
                BossRazor = glm::scale(BossRazor, glm::vec3(1 * boss.skillRazor.size, 1 * boss.skillRazor.length, 1 * boss.skillRazor.size));
                shaderID.setMat4("modelTransform", BossRazor);
                glDrawArrays(GL_TRIANGLES, 0, Cylinder);
            }

            //drop 스킬
            if (boss.skillDrop.toggle == true) {
                for (int i = 0; i < boss.skillDrop.number; i++) { //발판
                    glBindTexture(GL_TEXTURE_2D, Cylinder_Load.texture);
                    glBindVertexArray(VAO_Cylinder);
                    shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
                    glm::mat4 BossDrop = glm::mat4(1.0f);
                    BossDrop = glm::translate(BossDrop, glm::vec3(boss.skillDrop.posX[i], 0.05f, boss.skillDrop.posZ[i]));
                    BossDrop = glm::scale(BossDrop, glm::vec3(2, boss.skillDrop.size, 2));
                    shaderID.setMat4("modelTransform", BossDrop);
                    glDrawArrays(GL_TRIANGLES, 0, Cylinder);
                }
            }

        }
    }
    //보스 장애물
    if (bossObsToggle) {
        glBindTexture(GL_TEXTURE_2D, Cone_Load.texture);
        glBindVertexArray(VAO_Cone);
        shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
        for (int i = 0; i < 200; i++) {
            glm::mat4 BossObsTransform = glm::mat4(1.0f);
            BossObsTransform = glm::translate(BossObsTransform, glm::vec3(bossObs[i].ObsX, bossObs[i].ObsY, bossObs[i].ObsZ));
            BossObsTransform = glm::scale(BossObsTransform, glm::vec3(0.1f, 0.15f, 0.1f));
            shaderID.setMat4("modelTransform", BossObsTransform);
            glDrawArrays(GL_TRIANGLES, 0, Cone);
        }
    }
    glDepthFunc(GL_LEQUAL);
    skyShaderID.use();
    skyShaderID.setMat4("viewTransform", vTransform);
    //투영 변환
    glm::mat4 cubeTransform = glm::mat4(1.0f);
    cubeTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
    skyShaderID.setMat4("projectionTransform", cubeTransform);
    glBindVertexArray(VAO_skybox);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
    skyShaderID.setInt("skybox", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

GLvoid KeyBoard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        player.w = true;
        break;
    case 'a':
        player.a = true;
        break;
    case 's':
        player.s = true;
        break;
    case 'd':
        player.d = true;
        break;
    case 'x': //스킬 8개 총알 발사
        if (!skillXToggle) {
            skillXToggle = true;
            for (int i = 0; i < BULLET_MAX; i++) {
                if (bullet[i].shouldDraw == false) {
                    countSkillEight++;
                    bullet[i].shouldDraw = true;
                    bullet[i].currentX = player.x;
                    bullet[i].currentZ = player.z;
                    bullet[i].currentY = 0.5;
                    bullet[i].skillEight = countSkillEight;
                    if (countSkillEight >= 8) {
                        countSkillEight = 0;
                        break;
                    }
                }
            }
        }
        break;
    case 'c':
        if (bossToggle && !skillCToggle) {
            skillCToggle = true;
            for (int i = 0; i < BULLET_MAX; i++) {
                if (bullet[i].shouldDraw == false) {
                    bullet[i].shouldDraw = true;
                    bullet[i].currentX = player.x;
                    bullet[i].currentZ = player.z;
                    bullet[i].currentY = 0.5;
                    bullet[i].skillBig = 1;
                    break;
                }
            }
        }
        break;
    case 'b'://보스소환
        bossToggle = !bossToggle;
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

        break;
    case 't'://탑뷰
        topViewToggle = !topViewToggle;
        break;
    case 'q':
        exit(-1);
    }
    glutPostRedisplay();
}
GLvoid KeyBoardUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        player.w = false;
        break;
    case 'a':
        player.a = false;
        break;
    case 's':
        player.s = false;
        break;
    case 'd':
        player.d = false;
        break;
    case 32:
        if (!zFlag && zTimer == 0)zFlag = true;
        break;
    case 'q':
        exit(-1);
    }
    glutPostRedisplay();
}
GLvoid Motion(int x, int y) {
    player.startX = player.currentX;
    player.currentX = x;

    if (player.startX < player.currentX)player.direction -= 0.05f;
    else if (player.startX > player.currentX)player.direction += 0.05f;
}

GLvoid SpecialKeyBoard(int key, int x, int y)
{
    if (topViewToggle) {
        switch (key)
        {
        default:
        case GLUT_KEY_UP:
            topViewCameraZ--;
            break;
        case GLUT_KEY_DOWN:
            topViewCameraZ++;
            break;
        case GLUT_KEY_LEFT:
            topViewCameraX--;
            break;
        case GLUT_KEY_RIGHT:
            topViewCameraX++;
            break;
        }
    }
    glutPostRedisplay();
}

float bossL = 0;
float playerL = 0;
float inner = 0;
float theta = 0;

GLvoid TimerFunc(int x)
{
    switch (x)
    {
    case PLAYTIME:
        playTimeTimer++;

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
        glutTimerFunc(1000, TimerFunc, PLAYTIME);
        break;
    case ANIMATION:
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
            if (boss.x + 1.5 >= player.x && boss.x - 1.5 <= player.x && boss.z + 1.25 >= player.z && boss.z - 1.25 <= player.z ) {
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
        glutTimerFunc(10, TimerFunc, ANIMATION);
        break;
    case BULLET:
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
                        if (bullet[i].skillEightCount>3000) {
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
                                boss.hp-=player.atk;
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
        glutTimerFunc(1, TimerFunc, BULLET);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}