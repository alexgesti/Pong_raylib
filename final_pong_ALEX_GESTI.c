#include "raylib.h"
void Reset();
void Check_In();

int screenWidth = 800;
int screenHeight = 450;

//GAMEPLAY

//Contador
int framesCounter = 0;
int currentTime = 99;
    
//Medidas
int ancho = 15;
int altura = 70;
int margi = 10;
    
//Vida que se resta
int enemyLife = 50;
int playerLife = 50;

//Raquetas
Rectangle raqueta1Rec;
Rectangle raqueta2Rec;

//Velocidad Player 1 y 2
Vector2 speed;
Vector2 speed2;

//Centro y velocidad pelota
Vector2 center;
Vector2 speedp;
float radio = 20;
Color color = WHITE;

//Vida player 1
Rectangle blackRec;
Rectangle redRec;
Rectangle lifeRec;

//Vida player 2
Rectangle black2Rec;
Rectangle red2Rec;
Rectangle life2Rec;

//Cambiador de velocidades
bool changer = false;
    
//Cambiador de pantalla
bool changertitle = false;
    
//Cambiador de pausa y escritura de pausa
bool pause = false;
const char textpause[10] = "Pause";
    
//Cambiador de resultado
bool fin = false;
   
int result = -2;        // 0 - Loose, 1 - Win, -1 - Draw, -2 - Not defined

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

int main()
{
    // Initialization
    //-------------------------------------------------------------------------------------- 
    char windowTitle[30] = "raylib game - FINAL PONG";
    
    GameScreen screen = LOGO;
    
    // TODO: Define required variables here..........................(0.5p)
    // NOTE: Here there are some useful variables (should be initialized)
    //LOGO
    //YEESTUDIOS
    bool fadeIn = true;
    int fadeFrames = 90;
    int logovisibleframes = 120;
    int fadecounter = 0;
    float alpha = 0.0f;
    
    //PIXELCUAK
    bool fadeIn2 = true;
    int outFrames = 90;
    int logovisibleframesout = 120;
    int fadecounterout = 0;
    float alphaout = 0.0f;
    
    //TITLE
    //Contador de "blink"
    int blinkCounter = 0;
  
    //Iniciador de "blink"
    bool blink = false;
    
    //Color "Title" y "Start"
    Color colortitle = WHITE;
    Color colorstart = WHITE;
    
    //"Title" y "Start"
    const char title[50] = "Experimental Pong";
    const char started[100] = "Press SPACE to start";
 
    //GAMEPLAY
   
    //Pelota
    center = (Vector2) {screenWidth / 2, screenHeight /2};
    speedp.x = GetRandomValue(-4, 4);
    speedp.y = GetRandomValue(-5, 5);
    
    //Raquetas
    raqueta1Rec.x = screenWidth / 35;
    raqueta1Rec.y = screenHeight / 2 - 30;
    raqueta1Rec.width = ancho;
    raqueta1Rec.height = altura;
    speed = (Vector2) {0, 4};
    
    raqueta2Rec.x = screenWidth / 1.045;
    raqueta2Rec.y = screenHeight / 2 - 30;
    raqueta2Rec.width = ancho;
    raqueta2Rec.height = altura;
    speed2 = (Vector2) {0, 4};
    
    bool twoplayer = false;
    
    //Vida Player 1
    blackRec.x = 0;
    blackRec.y = 0;
    blackRec.width = screenWidth; 
    blackRec.height = screenHeight - 400;
    
    redRec.x = blackRec.x + margi;
    redRec.y = blackRec.y + margi;
    redRec.width = (screenWidth - 450) - margi*2;
    redRec.height = blackRec.height - margi*2;
    
    lifeRec.x = redRec.x;
    lifeRec.y = redRec.y;
    lifeRec.width = redRec.width;
    lifeRec.height = redRec.height;
    Color lifecolor = GREEN;
    
    //Vida Player 2
    black2Rec.x = screenWidth / 1.78;
    black2Rec.y = screenHeight / (screenWidth - 10);
    black2Rec.width = screenWidth - 450; 
    black2Rec.height = screenHeight - 400;
    
    red2Rec.x = black2Rec.x + margi;
    red2Rec.y = black2Rec.y + margi;
    red2Rec.width = black2Rec.width - margi*2;
    red2Rec.height = black2Rec.height - margi*2;
    
    life2Rec.x = red2Rec.x;
    life2Rec.y = red2Rec.y;
    life2Rec.width = red2Rec.width;
    life2Rec.height = red2Rec.height;
    Color life2color = GREEN;
    
   
    InitWindow(screenWidth, screenHeight, windowTitle);
    
        
    // NOTE: If using textures, declare Texture2D variables here (after InitWindow)
    // NOTE: If using SpriteFonts, declare SpriteFont variables here (after InitWindow)
    // NOTE: If using sound or music, InitAudioDevice() and load Sound variables here (after InitAudioDevice)
    
    //LOGO
    InitAudioDevice();
    
    //YEESTUDIOS
    //Texture
    Texture2D Yee = LoadTexture ("resources/Sprites/YeeStudios.png");
    Rectangle YeesourceRec = { 0, 0, Yee.width, Yee.height};
    Rectangle YeedestRec = {screenWidth/2, screenHeight/2, YeesourceRec.width, YeesourceRec.height}; //poner el sitio y el tamaño del trozo
    Vector2 Yeeorigin = {YeedestRec.width/2, YeedestRec.height/2};
    Color yeecolor = WHITE;

    //Sound
    Sound Yeefx = LoadSound ("resources/Sounds/Yee.wav");
    
    int Yeesound = false;
    
    //PIXELCUAK
    //Texture
    Texture2D cuak = LoadTexture ("resources/Sprites/PixelcuaK.png");
    Rectangle cuaksourceRec = { 0, 0, cuak.width, cuak.height};
    Rectangle cuakdestRec = {screenWidth/2, screenHeight/2, cuaksourceRec.width, cuaksourceRec.height}; //poner el sitio y el tamaño del trozo
    Vector2 cuakorigin = {cuakdestRec.width/2, cuakdestRec.height/2};
    Color cuakcolor = WHITE;

    //Sound
    Sound cuakfx = LoadSound ("resources/Sounds/cuak.wav");
    
    int cuaksound = false;
    
    //TITLE
    //Tipologia de letra y tamaño
    SpriteFont titleFont = LoadSpriteFontEx("resources/bit_outline.ttf", 45, 0, 0); 
    int titletama = titleFont.baseSize;
    
    //Encuadre de "Title"
    Vector2 titlemesura = MeasureTextEx(titleFont, title, titletama, 0);
    Vector2 titleposicion = {screenWidth / 8, 0};
    Vector2 titleposicionend = {screenWidth / 8, 150};
    
    //Sound
    Music titlesong = LoadMusicStream ("resources/Music/theme.ogg");
    PlayMusicStream(titlesong);
    SetMusicVolume(titlesong, 40);
    
    //GAMEPLAY
    //Tipologia de letra y tamaño
    SpriteFont pauseFont = LoadSpriteFontEx("resources/bit_outline.ttf", 30, 0, 0); 
    int pausetama = pauseFont.baseSize;
    
    //Encuadre de "Pause" y el contador
    Vector2 pausemesura = MeasureTextEx(pauseFont, textpause, pausetama, 0);
    Vector2 pauseposicion = {screenWidth / 2.36, screenHeight / 2};
    
    //Sound
    Music gamesong = LoadMusicStream ("resources/Music/normal.ogg");
    PlayMusicStream(gamesong);
    SetMusicVolume(gamesong, 20);
    Sound rebotefx = LoadSound ("resources/Sounds/rebote.wav");
    Sound wallfx = LoadSound ("resources/Sounds/wall.wav");
    Sound golfx = LoadSound ("resources/Sounds/gol.wav");
    
    //ENDING
    //Escritura "WIN", "LOSE" y "DRAW"
    const char textwin[10] = "YOU WIN!";
    const char textlose[10] = "YOU LOSE!";
    const char textdraw[10] = "DRAW";
    
    //Escritura "Continue" y "Exit"
    const char continua[100] = "If you want to continue, press ENTER.";
    const char exit[100] = "If you want to leave, press ESC.";
    
    //WIN
    //Tipologia de letra y tamaño
    SpriteFont winFont = LoadSpriteFontEx("resources/bit_outline.ttf", 60, 0, 0); 
    int wintama = winFont.baseSize;
    
    //Encuadre de "Win" y el contador
    Vector2 winmesura = MeasureTextEx(winFont, textwin, wintama, 0);
    Vector2 winposicion = {screenWidth / 3.5, screenHeight / 2};
    
    //Sound Win
    Music winsong = LoadMusicStream ("resources/Music/win.ogg");
    PlayMusicStream(winsong);
    SetMusicVolume(winsong, 40);
    
    //LOSE
    //Tipologia de letra y tamaño
    SpriteFont loseFont = LoadSpriteFontEx("resources/bit_outline.ttf", 60, 0, 0); 
    int losetama = loseFont.baseSize;
    
    //Encuadre de "Lose" y el contador
    Vector2 losemesura = MeasureTextEx(loseFont, textlose, losetama, 0);
    Vector2 loseposicion = {screenWidth / 3.9, screenHeight / 2};
    
    //Sound Lose
    Music losesong = LoadMusicStream ("resources/Music/lose.ogg");
    PlayMusicStream(losesong);
    SetMusicVolume(losesong, 40);
    
    //DRAW
    //Tipologia de letra y tamaño
    SpriteFont drawFont = LoadSpriteFontEx("resources/bit_outline.ttf", 60, 0, 0); 
    int drawtama = drawFont.baseSize;
    
    //Encuadre de "Draw" y el contador
    Vector2 drawmesura = MeasureTextEx(drawFont, textdraw, drawtama, 0);
    Vector2 drawposicion = {screenWidth / 2.65, screenHeight / 2};
    
    //Sound Draw
    Music drawsong = LoadMusicStream ("resources/Music/draw.ogg");
    PlayMusicStream(drawsong);
    SetMusicVolume(drawsong, 40);
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        switch(screen) 
        {
            case LOGO: 
            {
                // Update LOGO screen data here!
                PauseMusicStream(titlesong);
                PauseMusicStream(gamesong);
                PauseMusicStream(winsong);
                PauseMusicStream(losesong);
                PauseMusicStream(drawsong);
                // TODO: Logo fadeIn and fadeOut logic...............(0.5p)
                //YEESTUDIOS
                if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) screen = TITLE;
                if(fadeIn)
                {
                alpha += 1.0f / fadeFrames;
                if(alpha >= 1.0f)
                {
                    alpha = 1;
                    fadecounter++;
                    Yeesound = true;
                    if(Yeesound == true && fadecounter == 5) PlaySound(Yeefx);
                    
                    if(fadecounter >= logovisibleframes)
                    {
                        Yeesound = false;
                        fadecounter = 0;
                        fadeIn = false;
                    }
                }
                }
                else
                {
                    alpha -= 1.0f / fadeFrames;
                    if(alpha <= 0.0f)
                    {
                        alpha = 0;
                        //PIXELCUAK
                        if(fadeIn2)
                        {
                        alphaout += 1.0f / outFrames;
                        if(alphaout >= 1.0f)
                        {
                            alphaout = 1;
                            fadecounterout++;
                            cuaksound = true;
                            if(cuaksound == true && fadecounterout == 5) PlaySound(cuakfx);
                            if(fadecounterout >= logovisibleframesout)
                            {
                                cuaksound = false;
                                fadecounterout = 0;
                                fadeIn2 = false;
                            }
                        }
                        }
                        else
                        {
                            alphaout -= 1.0f / outFrames;
                            if(alphaout <= 0.0f)
                            {
                                alphaout = 0;
                                screen = TITLE;
                            }
                        }
                    }
                }
                
            } break;
            case TITLE: 
            {
                // Update TITLE screen data here!
                UpdateMusicStream(titlesong);
                ResumeMusicStream(titlesong);
                // TODO: Title animation logic.......................(0.5p)
                if(titleposicion.y < titleposicionend.y)
                {
                    titleposicion.y += 2;
                    
                    if(IsKeyPressed(KEY_SPACE) && titleposicion.y != titleposicionend.y)
                    {
                        titleposicion.y = titleposicionend.y;
                    }
                }
                //En caso de haber termniado la animación
                else
                {
                    titleposicion.y = titleposicionend.y;
                    // TODO: "PRESS ENTER" logic.........................(0.5p)
                    blinkCounter++;
                    if(blinkCounter % 30 == 0)
                    {
                        blink = !blink;
                        colortitle = WHITE;
                        colorstart = WHITE;
                    } 
                    if(IsKeyPressed(KEY_SPACE))
                    {
                        blink = false;
                        screen = GAMEPLAY;
                    }
                    if(IsKeyPressed(KEY_K))
                    {
                        blink = false;
                        twoplayer = true;
                        screen = GAMEPLAY;
                    }
                    
                }
               
            } break;
            case GAMEPLAY: 
            {
            StopMusicStream(titlesong);
            if(!fin)
            {
            if(!pause)
            {
                // Update GAMEPLAY screen data here!
                UpdateMusicStream(gamesong);
                ResumeMusicStream(gamesong);
                // TODO: Ball movement logic.........................(0.2p)
                center.x += speedp.x;
                center.y += speedp.y;
    
                if(changer == false)
                {
                    if(speedp.x >= 0)
                    {
                        speedp.x = 4;
                    }
                    if(speedp.x <= -1)
                    {
                        speedp.x = -4;
                    }
                    if(speedp.y == 0)
                    {
                        speedp.y = 4;
                    }
                }
                
                // TODO: Life bars decrease logic....................(1p)
                if((center.x - radio) >= screenWidth)
                {
                    Check_In();
                    changer = false;
                    life2Rec.width -= enemyLife;
                    life2Rec.x += enemyLife;
                    PlaySound(golfx);
                    if(life2Rec.width <= 0)
                    {
                        life2Rec.width = 0;
                        result = 1;
                        fin = true;
                    }
                }
                else if((center.x + radio) <= 0)
                {
                    Check_In();
                    changer = false;
                    lifeRec.width -= playerLife;
                    PlaySound(golfx);
                    if(lifeRec.width <= 0)
                    {
                        lifeRec.width = 0;
                        result = 0;
                        fin = true;
                    }
                }
        
                // TODO: Player movement logic.......................(0.2p)
                if(IsKeyDown(KEY_D)) raqueta1Rec.y += speed.y;
                if(IsKeyDown(KEY_S)) raqueta1Rec.y -= speed.y;
                
                // TODO: Enemy movement logic (IA)...................(1p)
                if(twoplayer == true)
                {
                    if(IsKeyDown(KEY_K)) raqueta2Rec.y += speed.y;
                    if(IsKeyDown(KEY_L)) raqueta2Rec.y -= speed.y;
                }
                else
                {
                    if(center.x >= screenWidth / 2 && center.y >= raqueta2Rec.height / 2 + raqueta2Rec.y && speedp.x > 0) raqueta2Rec.y += speed2.y;
                    if(center.x >= screenWidth / 2 && center.y <= raqueta2Rec.height / 2 + raqueta2Rec.y && speedp.x > 0) raqueta2Rec.y -= speed2.y;
                }
                
                // TODO: Collision detection (ball-player) logic.....(0.5p)
                if(CheckCollisionCircleRec(center, radio, raqueta1Rec)) 
                {
                    if(speedp.x < 0)
                    {
                        speedp.y = (center.x - raqueta1Rec.x)/(raqueta1Rec.height/2)*10;
                        speedp.x *= -1;
                        changer = true;
                        PlaySound(rebotefx);
                    }
                }
                
                //Limites jugador
                if((raqueta1Rec.y + raqueta1Rec.height) >= screenHeight - 10) raqueta1Rec.y = (screenHeight - 10) - raqueta1Rec.height;
                if(raqueta1Rec.y <= blackRec.height + 5) raqueta1Rec.y =  blackRec.height + 9;
                
                // TODO: Collision detection (ball-enemy) logic......(0.5p)
                if(CheckCollisionCircleRec(center, radio, raqueta2Rec)) 
                {
                    if(speedp.x > 0)
                    {
                        speedp.y = (center.x - raqueta2Rec.x)/(raqueta2Rec.height/2)*10;
                        speedp.x *= -1;
                        changer = true;
                        PlaySound(rebotefx);
                    }
                }
                
                //Limites enemigo
                if((raqueta2Rec.y + raqueta2Rec.height) >= screenHeight - 10) raqueta2Rec.y = (screenHeight - 10) - raqueta2Rec.height;
                if(raqueta2Rec.y <= black2Rec.height + 5) raqueta2Rec.y =  black2Rec.height + 9;
        
                // TODO: Collision detection (ball-limits) logic.....(1p)
                if((center.y + radio) >= screenHeight) 
                {
                    PlaySound(wallfx);
                    speedp.y *= -1.05f;
                }
                if((center.y - radio) <= blackRec.height) 
                {
                    PlaySound(wallfx);
                    speedp.y *= -1.05f;
                }
                
                //Limites pelota
                if(center.y >= screenHeight - 10) center.y = (screenHeight - 10) - raqueta2Rec.height;
                if(center.y <= black2Rec.height + 5) center.y =  black2Rec.height + 9;
                
                // TODO: Time counter logic..........................(0.2p)
                framesCounter++;
                if(framesCounter % 60 == 0)
                {
                    currentTime--;
                }
                else if(currentTime == 0)
                {
                    framesCounter = 0;
                }
            }
            }
            
                // TODO: Game ending logic...........................(0.2p)
                if(fin)
                {
                    screen = ENDING; 
                }
               
                // TODO: Pause button logic..........................(0.2p)    
                if(IsKeyPressed(KEY_P)) pause = !pause;
             
            } break;
            case ENDING: 
            {
                StopMusicStream(gamesong);
                twoplayer = false;
                if(result == 1)
                {
                    UpdateMusicStream(winsong);
                    ResumeMusicStream(winsong);
                }
                if(result == 0) 
                {
                    UpdateMusicStream(losesong);
                    ResumeMusicStream(losesong);
                }
                if(result == -1) 
                {
                    UpdateMusicStream(drawsong);
                    ResumeMusicStream(drawsong);
                }
                // Update END screen data here!
                // TODO: Replay / Exit game logic....................(0.5p)
                if(IsKeyPressed(KEY_ENTER))
                {
                    StopMusicStream(winsong);
                    StopMusicStream(losesong);
                    StopMusicStream(drawsong);
                    Reset();
                    screen = GAMEPLAY;
                }
                if(IsKeyPressed(KEY_K))
                {
                    StopMusicStream(winsong);
                    StopMusicStream(losesong);
                    StopMusicStream(drawsong);
                    Reset();
                    twoplayer = true;
                    screen = GAMEPLAY;
                }
                if(IsKeyPressed(KEY_ESCAPE))
                {
                    return 0;
                }
                
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            ClearBackground(BLACK);
            
            switch(screen) 
            {
                case LOGO: 
                {
                    // Draw LOGO screen here!
                    ClearBackground(BLACK);
                    // TODO: Draw Logo...............................(0.2p)
                    //YEESTUDIOS
                    DrawTexturePro(Yee, YeesourceRec, YeedestRec, Yeeorigin, 0, Fade(yeecolor, alpha));
                    //PIXELCUAK
                    DrawTexturePro(cuak, cuaksourceRec, cuakdestRec, cuakorigin, 0, Fade(cuakcolor, alphaout));
                    
                } break;
                case TITLE: 
                {
                    // Draw TITLE screen here!
                    ClearBackground(BLACK);
        
                    // TODO: Draw Title..............................(0.2p)
                    DrawTextEx(titleFont, title, titleposicion, titletama, 0, colortitle);
                    
                    // TODO: Draw "PRESS ENTER" message..............(0.2p)
                    int tama = MeasureText(started, 30);
                    if(blink) DrawText(started, screenWidth / 2 - tama / 2, 300, 30, colorstart);
                    
                } break;
                case GAMEPLAY:
                { 
                    // Draw GAMEPLAY screen here!
                    
                    //Fondo Color Pong
                    ClearBackground(BLACK);
                    
                    // TODO: Draw player and enemy...................(0.2p)
                    DrawRectangleRec(raqueta1Rec, WHITE);
                    DrawRectangleRec(raqueta2Rec, WHITE);
                    
                    // TODO: Draw player and enemy life bars.........(0.5p)
                    DrawRectangleRec(blackRec, WHITE);
                    DrawRectangleRec(redRec, RED);
                    DrawRectangleRec(lifeRec, lifecolor);
                    DrawRectangleRec(black2Rec, WHITE);
                    DrawRectangleRec(red2Rec, RED);
                    DrawRectangleRec(life2Rec, lifecolor);
                    
                    //Pelota
                    DrawCircleV(center, radio, color);
                    
                    // TODO: Draw time counter.......................(0.5p)
                    int tama = MeasureText(FormatText("%02i", currentTime), 50);
                    DrawText(FormatText("%02i", currentTime), screenWidth / 2 - tama / 2, 5, 50, BLACK);
                    
                    // TODO: Draw pause message when required........(0.5p)
                    if(pause) 
                    {
                        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(GRAY, 0.5f));
                        DrawTextEx(pauseFont, textpause, pauseposicion, pausetama, 0, WHITE);
                    }
                    
                } break;
                case ENDING: 
                {
                    // Draw END screen here!
                    // TODO: Draw ending message (win or loose)......(0.2p)
                    ClearBackground(BLACK);
                    //WIN
                    if(result == 1)
                    {
                        DrawTextEx(winFont, textwin, winposicion, wintama, 0, GREEN);  
                    }
                    //LOSE
                    if(result == 0)
                    {
                        DrawTextEx(loseFont, textlose, loseposicion, losetama, 0, RED);
                    }
                    //DRAW
                    if(result == -1)
                    {
                        DrawTextEx(drawFont, textdraw, drawposicion, drawtama, 0, BLUE);
                    }
                    
                    //Continue or "kick"
                    int tama = MeasureText(continua, 25);
                    DrawText(continua, screenWidth / 2 - tama / 2, 300, 25, colorstart);
                    tama = MeasureText(exit, 25);
                    DrawText(exit, screenWidth / 2 - tama / 2, 330, 25, colorstart);
                    
                } break;
                default: break;
            }
        
            DrawFPS(10, 10);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}

//Reset total del juego
void Reset()
{
    //Contador
    int framesCounter = 0;
    int currentTime = 99;
    
    //Pelota
    center = (Vector2) {screenWidth / 2, screenHeight /2};
    speedp.x = GetRandomValue(-4, 4);
    speedp.y = GetRandomValue(-5, 5);
    
    //Raquetas
    raqueta1Rec.x = screenWidth / 35;
    raqueta1Rec.y = screenHeight / 2 - 30;
    raqueta1Rec.width = ancho;
    raqueta1Rec.height = altura;
    speed = (Vector2) {0, 4};
    
    raqueta2Rec.x = screenWidth / 1.045;
    raqueta2Rec.y = screenHeight / 2 - 30;
    raqueta2Rec.width = ancho;
    raqueta2Rec.height = altura;
    speed2 = (Vector2) {0, 3};
    
    //Vida Player 1
    blackRec.x = 0;
    blackRec.y = 0;
    blackRec.width = screenWidth; 
    blackRec.height = screenHeight - 400;
    
    redRec.x = blackRec.x + margi;
    redRec.y = blackRec.y + margi;
    redRec.width = (screenWidth - 450) - margi*2;
    redRec.height = blackRec.height - margi*2;
    
    lifeRec.x = redRec.x;
    lifeRec.y = redRec.y;
    lifeRec.width = redRec.width;
    lifeRec.height = redRec.height;
    
    //Vida Player 2
    black2Rec.x = screenWidth / 1.78;
    black2Rec.y = screenHeight / (screenWidth - 10);
    black2Rec.width = screenWidth - 450; 
    black2Rec.height = screenHeight - 400;
    
    red2Rec.x = black2Rec.x + margi;
    red2Rec.y = black2Rec.y + margi;
    red2Rec.width = black2Rec.width - margi*2;
    red2Rec.height = black2Rec.height - margi*2;
    
    life2Rec.x = red2Rec.x;
    life2Rec.y = red2Rec.y;
    life2Rec.width = red2Rec.width;
    life2Rec.height = red2Rec.height;
    
    //Cambiador de velocidades
    changer = false;
    
    //Cambiador de pantalla
    changertitle = false;
    
    //Cambiador de pausa y escritura de pausa
    pause = false;
    
    //Cambiador de resultado
    fin = false;
   
    result = -2;        // 0 - Loose, 1 - Win, -1 - Draw, -2 - Not defined
}

//Reset de la pelota cada vez que se marca gol
void Check_In()
{
    center.x = screenWidth / 2;
    center.y = screenHeight / 2;
    speedp.x = GetRandomValue(-4, 4); 
    speedp.y = GetRandomValue(-5, 5);   
}