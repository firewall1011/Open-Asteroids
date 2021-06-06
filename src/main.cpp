/*
Trabalho de Computação Gráfica USP - ICMC, São Carlos
Tiago Marino @firewall1011
Laura Genari @LauraGenari
João Pedro Secundino @jpsecundino
*/

#include "main.h"

using namespace std::chrono_literals;
using namespace std::chrono;
using namespace TLibrary;

#define FPS 30
#define MS_FTIME 1000ms/FPS
#define NANO_TO_SEC_F(t) (float)(t).count()*1e-9;

int main(void) {

    

    GLFWwindow* window = create_window(720, 720, "Asteroids");

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s\n", glewGetErrorString(GlewInitResult));

    // Create Default Shader
    TLibrary::Shader shader("color.shader");
    
    // Initialize objects buffer
    BufferData bufferData;

    //definindo cor dos objetos e do background
    vec3 obj_color = vec3(0.0f, 1.0f, 0.0f);
    vec3 background_color = vec3(0.176f, 0.886f, 0.901f);
    
    // Generate asteroids
    Random::InitState(1);
    AsteroidsGenerator asteroidsGenerator = AsteroidsGenerator(0.03f, 0.08f, 50, 100, 0.1f, 0.2f, 2.0f);
    asteroidsGenerator.CreateAsteroids(10);
    
    //Create Player
    Player* player = new Player(window, 15);
    
    // Generate Bullets for shooting
    BulletFireSystem::CreateBullets(bufferData);
    
    //generate background
    Random::InitState(255);
    BackgroundSystem::CreateBackground(0.9f, 0.035f, 0.01f, 50, background_color);

    //insert background to buffer
    bufferData.data.insert(std::end(bufferData.data), std::begin(BackgroundSystem::universe), std::end(BackgroundSystem::universe));
    // Insert Asteroids data to buffer
    bufferData.data.insert(std::end(bufferData.data), std::begin(AsteroidPoolingSystem::asteroids), std::end(AsteroidPoolingSystem::asteroids));
    //insert Player to data buffer
    bufferData.data.push_back(player);
    // Insert Bullets to buffer
    bufferData.data.insert(std::end(bufferData.data), std::begin(BulletFireSystem::bullets), std::end(BulletFireSystem::bullets));
    
    bufferData.SendToGPU();
    
    glEnableVertexAttribArray(shader.loc_position);
    glVertexAttribPointer(shader.loc_position, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0);

    // Exibindo nossa janela
    glfwShowWindow(window);

    //Contador de pontos do jogador
    int points = 0;

    //variável de loop do jogo
    bool game_is_running = true;

    float delta_time = (float)(MS_FTIME).count() * 1e-3;
    while (!glfwWindowShouldClose(window) && game_is_running)
    {
        auto start = steady_clock::now();
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
        AsteroidPoolingSystem::Tick(delta_time);
        
        CheckCollisionWithPlayer(player, game_is_running);
        CheckBulletToAsteroidCollision(points);
            
        if (!game_is_running) break;

        // Update and Render Objects
        bufferData.Update(delta_time);
        bufferData.Draw(shader);

        glfwSwapBuffers(window);

        auto sleepTime = (start + MS_FTIME) - steady_clock::now();
        std::this_thread::sleep_for(sleepTime);

        delta_time = NANO_TO_SEC_F(sleepTime);
    }
    close_window(window);

    std::cout << "\nForam marcados " << points << " pontos!!" << std::endl;
    std::cin.get();
    return EXIT_SUCCESS;
}

void CheckBulletToAsteroidCollision(int& points)
{
    for (Bullet*& bullet : BulletFireSystem::bullets) 
    {
        if (!bullet->isActive) continue;

        for (Asteroid*& ast : AsteroidPoolingSystem::asteroids) {
            if (!ast->isActive) continue;
            
            if (ast->Collision(bullet->position, bullet->radius)) 
            {
                ast->Damage();
                bullet->isActive = false;
                points++;
                break;
            }
        }

    }
}

void CheckCollisionWithPlayer(Player* player, bool& game_is_running)
{
    for (Asteroid*& ast : AsteroidPoolingSystem::asteroids) 
    {
        if (!ast->isActive) continue;

        if (ast->Collision(player->position, player->scale.x)) 
        {
            game_is_running = false;
        }
    }
}

GLFWwindow* create_window(int width, int height, const char* name) 
{
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);

    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    return window;
}

void close_window(GLFWwindow* window) 
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
