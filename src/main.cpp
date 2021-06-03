#include "main.h"

using namespace std::chrono_literals;
using namespace std::chrono;
using namespace TLibrary;

#define FPS 144
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

    // Generate asteroids
    AsteroidsGenerator asteroidsGenerator = AsteroidsGenerator(0.03f, 0.08f, 50, 100, 0.2f, 0.6f, 2.0f);
    asteroidsGenerator.CreateAsteroids(20);
    
    // Insert Asteroids data to buffer
    bufferData.data.insert(std::end(bufferData.data), std::begin(AsteroidPoolingSystem::asteroids), std::end(AsteroidPoolingSystem::asteroids));
        
    //srand(1);
    //Create Player and insert to buffer
    Player* player = new Player(window, 15);
    bufferData.data.push_back(player);
    
    // Generate Bullets for shooting
    BulletFireSystem::CreateBullets(bufferData);
    // TODO: bufferData.data.insert

    bufferData.SendToGPU();

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc_position = glGetAttribLocation(shader.GetID(), "position");
    GLint loc_transform = glGetUniformLocation(shader.GetID(), "transformation_matrix");
    GLint loc_color = glGetUniformLocation(shader.GetID(), "color");

    glEnableVertexAttribArray(loc_position);
    glVertexAttribPointer(loc_position, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

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

        glUniform4f(loc_color, 1, 0, 0, 1);
            
        AsteroidPoolingSystem::Tick(delta_time);
        
        CheckCollisionWithPlayer(player, game_is_running, points);
        CheckBulletToAsteroidCollision(points);
            
        if (!game_is_running) break;

        // Update and Render Objects
        bufferData.Update(delta_time);
        bufferData.Draw(shader, loc_transform);

        glfwSwapBuffers(window);

        auto sleepTime = (start + MS_FTIME) - steady_clock::now();
        std::this_thread::sleep_for(sleepTime);

        delta_time = NANO_TO_SEC_F(sleepTime);
    }
    close_window(window);

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

void CheckCollisionWithPlayer(Player* player, bool& game_is_running, int points)
{
    for (Asteroid*& ast : AsteroidPoolingSystem::asteroids) 
    {
        if (!ast->isActive) continue;

        if (ast->Collision(player->position, player->scale.x)) 
        {
            game_is_running = false;
            std::cout << "\nForam marcados " << points << " pontos!!" << std::endl;
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