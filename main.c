#include "raylib.h"
#include "cardSystem.c"
//#include <stdio.h>
#include "main.h"
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    
    double clickTime;
    
    InitWindow(screenWidth,screenHeight,"Cards Test window");
    
    //Textures always have to be loaded after WindowInit
    Texture2D cards = LoadTexture("images/CardFullTest.png");
    
    //sets global card* var = to actual texture
    cardText =  &cards; //don't call any cardSystem func before this
    
    //set fps
    SetTargetFPS(60);
    
    //stops escape from closing game
    SetExitKey(KEY_NULL);
    
    //mouse location
    Vector2 mousePoint ={0.0f,0.0f};
    
    //creates a tmp card for testing
    card card1;
    card1.suit = 1;
    card1.num = 10;
    
    //creates another tmp card for testing
    card healthCard1;
    healthCard1.suit = 2;
    healthCard1.num = 14;
    
    card* healthPtr = &healthCard1;
    
    card* cardPtr = &card1;
    bool mouseState = 0;
    
     
     //Texture2D* cards = InitCardTexture();
    /*
        So first card is just cards.width/14 * 14 and cards.height/4 * 4
        second is cards.width/14 *1 and cards.height/4 *1
        3rd cards.width/14 * 2 and cards.height/4 *2
        
    */
    //Rectangle frameRec = {((float)cards.width/14) *0,((float)cards.height/4) *0,(float)cards.width/14,(float)cards.height/4};
    Vector2 orig = {0.0f,0.0f};
    
    Rectangle frameRec = setCardIndex(cardPtr);
    
    Rectangle healthSource = setCardIndex(healthPtr);
 
    Rectangle drawRect = {(float)(screenWidth/2) -(cardText->width/8),(float)(screenHeight/2) - (cardText->height),(float)(cardText->width/14) * 5,(float)(cardText->height/4) *5};
    
    Rectangle healthCard = {(float)(screenWidth/2) -(cardText->width/8),(float)(screenHeight/2) - (cardText->height/2) + 200,(float)(cardText->width/14) * 5,(float)(cardText->height/4) *5};
    
    while(!WindowShouldClose())
    {
        //TODO: Create a function that takes in a rect for collision
        //and sets the card data when clicked
        mousePoint = GetMousePosition();
        if(CheckCollisionPointRec(mousePoint,drawRect))
        {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                mouseState = 1;  
            }
            
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && mouseState == 1)
            {
                mouseState = 0;
                if(cardPtr->suit == 2)
                {
                    cardPtr->suit = 1;
                }
                 if(cardPtr->num > 1)
                {
                    //for anims just check getTime and make sure enough time
                    //has elapsed
                    
                    //set actualValue that will get used
                    cardPtr->num = cardPtr->num-1;   
                }
                else
                {
                    cardPtr->suit = 2;
                    cardPtr->num = 14;

                }
                 //frameRec = setCardIndex(cardPtr);
                 
                 //set time of click
                 clickTime = GetTime();
                 //set anim to flip frame
                 Rectangle change = {((float)cardText->width/14) *13,((float)cardText->height/4) *0,(float)cardText->width/14,(float)cardText->height/4};
                 frameRec = change;
            }
  
        }
        
         if(clickTime + .1f <= GetTime())
            {
                frameRec = setCardIndex(cardPtr);
            }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(cards,15,40,WHITE);
        DrawTexturePro(*cardText,frameRec,drawRect,orig,0.0f,WHITE);
        DrawTexturePro(*cardText,healthSource,healthCard,orig,0.0f,WHITE);
        EndDrawing();
        
       
    }
    
    //fprintf(stderr,"Card1 suit: %d",card1.suit);
    //create some sort of procedural card system
    
    //Unload cards texture
    UnloadTexture(*cardText);
    return 0;
}