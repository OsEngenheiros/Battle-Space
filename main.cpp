// =============================================================================
//  OPERAÇÃO NAVE ESTELAR — Workshop de C++ (2h)
// =============================================================================

#include "raylib.h"
#include <string>
#include <vector>
#include <cstdlib>   
#include <ctime>     

using namespace std;

// =============================================================================
//  MÓDULO 3 — estruturas de dados (precisam ficar fora do main)
// =============================================================================

struct Meteoro {
    float x, y;
    bool ativo = true;
};

struct Bala {
    float x, y;
    bool ativa = true;
};

// =============================================================================
//  MAIN
// =============================================================================

int main() {

    srand(time(0));  // não mexa aqui

    // -------------------------------------------------------------------------
    //  MÓDULO 1 — O Espaço e a Nave
    // -------------------------------------------------------------------------
    string nomePiloto = "___";       // PREENCHA: coloque escolha o seu nome aqui (entre aspas)
    float naveX      = 380;          // posição inicial X da nave
    float naveY      = 500;          // posição inicial Y da nave 

    // Variáveis de jogo — prontas, não mexa aqui
    float velocidade  = 5.0f;
    int   vidas       = 3;
    bool  gameOver    = false;
    float timerTiro   = 0.0f;

    // Variáveis de Dificuldade
    float velMeteoro  = 3.0f;        
    float tempoSpawn  = 1.0f;        

    // Variáveis do Módulo 3
    vector<Meteoro> meteoros;
    vector<Bala>    balas;
    float timerSpawn      = 0.0f;
    float tempoVivo       = 0.0f;
    int   meterosGerados  = 0;
    int   meterosDesviados = 0;
    int   meterosDestruidos = 0;

    // -------------------------------------------------------------------------
    //  Setup da janela — pronto, não mexa aqui
    // -------------------------------------------------------------------------
    InitWindow(800, 600, ("Nave Estelar — Piloto: " + nomePiloto).c_str());
    SetTargetFPS(60);

    // =========================================================================
    //  GAME LOOP — o coração do jogo
    // =========================================================================

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        if (!gameOver) {

            // -- Tarefa A: movimento -----------------------------------------
            // PREENCHA: use a variável 'velocidade' para mover a nave
            if (IsKeyDown(KEY_LEFT))  naveX -= ___; 
            if (IsKeyDown(KEY_RIGHT)) naveX += ___;
            if (IsKeyDown(KEY_UP))    naveY -= ___;
            if (IsKeyDown(KEY_DOWN))  naveY += ___;

            // -- Tarefa B: limites de tela ------------------------------------
            // PREENCHA: não deixe a nave sair da tela de 800x600
            if (naveX < ___)  naveX = ___;     
            if (naveX > ___)  naveX = ___;   // (dica: 800 - largura da nave)
            if (naveY < ___)  naveY = ___;     
            if (naveY > ___)  naveY = ___;   // (dica: 600 - altura da nave)

            // -- Contador de tempo vivo e Dificuldade -------------------------
            tempoVivo += dt; 

            velMeteoro = 3.0f + (tempoVivo * 0.1f); 
            tempoSpawn = 1.0f - (tempoVivo * 0.015f); 
            if (tempoSpawn < 0.2f) tempoSpawn = 0.2f; 

            // =================================================================
            //  MÓDULO 3 — Chuva de Meteoros e Sistema de Tiro
            // =================================================================

            // -- Tarefa C: spawn de meteoro ----------------------------------
            timerSpawn += dt;
            if (timerSpawn > tempoSpawn) { 
                Meteoro novo;
                novo.x     = (float)(rand() % 760);
                novo.y     = 0;
                novo.ativo = true;

                meteoros.push_back(novo);

                meterosGerados++;
                timerSpawn = 0.0f;
            }

            // -- Tarefa D: atirar com a metralhadora -----------------
            timerTiro += dt;
            // PREENCHA: Qual tecla devemos checar? (dica: KEY_Nome)
            if (IsKeyDown(___) && timerTiro > 0.15f) {
                Bala b;
                // PREENCHA: Some um valor para o tiro sair da nave (40 - 20)
                b.y = naveY;
                b.ativa = true;
                balas.push_back(b);

                timerTiro = 0.0f;
            }                                                          

            // -- Mover balas + Tarefa E: colisão bala x meteoro --------------
            for (auto& b : balas) {
                if (!b.ativa) continue;

                b.y -= 6.0f;  

                if (b.y < 0) {
                    b.ativa = false;
                    continue;
                }

                Rectangle retBala = { b.x - 4, b.y - 4, 8, 8 };

                for (auto& m : meteoros) {
                    if (!m.ativo) continue;

                    Rectangle retMeteoro = { m.x, m.y, 30, 30 };

                    // PREENCHA: Passe os dois retângulos corretos para checar a colisão
                    if (CheckCollisionRecs(___, ___)) {
                        b.ativa = false;
                        m.ativo = false;
                        meterosDestruidos++;
                    }
                }
            }

            // -- Mover meteoros + Tarefa F: colisão nave x meteoro -----------
            for (auto& m : meteoros) {
                if (!m.ativo) continue;

                m.y += velMeteoro;  

                Rectangle retMeteoro = { m.x, m.y, 30, 30 };
                Rectangle retNave    = { naveX, naveY, 40, 40 };

                // PREENCHA: Passe os dois retângulos corretos para checar a colisão
                if (CheckCollisionRecs(___, ___)) {
                    m.ativo = false;
                    vidas--;
                }

                if (m.y > 620 && m.ativo) {
                    m.ativo = false;
                    meterosDesviados++;
                }
            }

            if (vidas <= 0) gameOver = true;
        } 

        // =====================================================================
        //  DESENHO 
        // =====================================================================
        BeginDrawing();
        ClearBackground(BLACK);

        if (!gameOver) {

            for (auto& m : meteoros) {
                if (m.ativo) {
                    DrawRectangle((int)m.x, (int)m.y, 30, 30, RED);
                }
            }

            for (auto& b : balas) {
                if (b.ativa) {
                    DrawCircle((int)b.x, (int)b.y, 5, YELLOW);
                }
            }

            Vector2 p1 = { naveX + 20, naveY      };  
            Vector2 p2 = { naveX,      naveY + 40 };  
            Vector2 p3 = { naveX + 40, naveY + 40 };  
            DrawTriangle(p1, p2, p3, SKYBLUE);

            //TROQUE A PALAVRA "COR" POR UMA DAS DISPONÍVEIS: WHITE, GREEN, PURPLE, YELLOW, GRAY, DARKGRAY
            DrawText(("Piloto: " + nomePiloto).c_str(), 10, 10, 18, COR);
            DrawText(TextFormat("Vidas: %d",    vidas),  10, 35, 18, COR);

            int nivel = (int)(tempoVivo / 5.0f) + 1;
            DrawText(TextFormat("Nível: %d", nivel), 10, 60, 18, COR);
            DrawText(TextFormat("Tempo: %.1fs", tempoVivo), 10, 85, 18, COR);

            DrawText(TextFormat("Destruidos: %d | Desviados: %d | Perdidos: %d",
                                meterosDestruidos, meterosDesviados,
                                meterosGerados - meterosDestruidos - meterosDesviados),
                     10, 110, 15, GRAY);
            DrawText("SPACE = atirar   Setas = mover", 530, 10, 15, DARKGRAY);

        } else {

            // =================================================================
            //  MÓDULO 4 — Relatório da Missão
            // =================================================================
            float pctDestruidos = 0.0f;
            if (meterosGerados > 0) {
                pctDestruidos = (meterosDestruidos / (float)meterosGerados) * 100.0f;
            }

            float pctDesviados = 0.0f;
            if (meterosGerados > 0) {
                pctDesviados = (meterosDesviados / (float)meterosGerados) * 100.0f;
            }

            float mediaPorSegundo = 0.0f;
            if (tempoVivo > 0) {
                mediaPorSegundo = meterosDestruidos / tempoVivo;
            }

            DrawText("MISSAO ENCERRADA", 220, 30, 30, RED);
            DrawText(("Piloto: " + nomePiloto).c_str(), 220, 68, 20, WHITE);

            DrawText("Meteoros destruidos (tiro):", 200, 130, 19, WHITE);
            int largBarra1 = (int)(pctDestruidos * 4.0f);
            DrawRectangle(200, 155, largBarra1, 32, YELLOW);
            DrawText(TextFormat("%.1f%%", pctDestruidos),
                     200 + largBarra1 + 8, 160, 19, YELLOW);

            DrawText("Meteoros desviados (esquivou):", 200, 210, 19, WHITE);
            int largBarra2 = (int)(pctDesviados * 4.0f);
            DrawRectangle(200, 235, largBarra2, 32, GREEN);
            DrawText(TextFormat("%.1f%%", pctDesviados),
                     200 + largBarra2 + 8, 240, 19, GREEN);

            DrawText("Tempo vivo:", 200, 290, 19, WHITE);
            // PREENCHA: Multiplique o tempo vivo por 4.0f para criar a barra
            int largBarra3 = (int)(tempoVivo * ___);
            if (largBarra3 > 400) largBarra3 = 400;
            DrawRectangle(200, 315, largBarra3, 32, SKYBLUE);
            DrawText(TextFormat("%.1fs", tempoVivo),
                     200 + largBarra3 + 8, 320, 19, SKYBLUE);

            DrawText("Media de destruicoes/segundo:", 200, 370, 19, WHITE);
            int largBarra4 = (int)(mediaPorSegundo * 80.0f);
            if (largBarra4 > 400) largBarra4 = 400;
            DrawRectangle(200, 395, largBarra4, 32, ORANGE);
            DrawText(TextFormat("%.2f /s", mediaPorSegundo),
                     200 + largBarra4 + 8, 400, 19, ORANGE);

            DrawText("Pressione R para jogar novamente", 210, 460, 18, GRAY);

            if (IsKeyPressed(KEY_R)) {
                naveX             = 380;
                naveY             = 500;
                vidas             = 3;
                tempoVivo         = 0.0f;
                timerSpawn        = 0.0f;
                meterosGerados    = 0;
                meterosDesviados  = 0;
                meterosDestruidos = 0;
                meteoros.clear();
                balas.clear();
                gameOver          = false;

                velMeteoro        = 3.0f;
                tempoSpawn        = 1.0f;
            }
        }

        EndDrawing();
    } 

    CloseWindow();
    return 0;
}