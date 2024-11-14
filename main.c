#include "raylib.h"
#include "cardSystem.c"
#include <stdio.h>
#include "main.h"
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    
    double clickTime = -1.0; //Error Value
    
    InitWindow(screenWidth,screenHeight,"Cards Test window");
    
    //Textures always have to be loaded after WindowInit
    Texture2D cards = LoadTexture("images/CardFullTest.png");
    
    //TODO: This needs to be a double pointer so everything is actually freed
    //Array to manage all cards
    card *cardArr[10]; //sizeOf 10 for now but that should be change eventually
    
    //TODO: Fix magix number here and above, and at end of file
    //set all cards to NULL
    for(int i = 0; i < 10; i++)
    {
        cardArr[i] = NULL;
    }
    
    //sets global card* var = to actual texture
    cardText =  &cards; //don't call any cardSystem func before this
    
    //set fps
    SetTargetFPS(60);
    
    //stops escape from closing game
    SetExitKey(KEY_NULL);
    
    //mouse location
    Vector2 mousePoint ={0.0f,0.0f};
    
    //creates an enemy card for testing
    card enemyCard;
    enemyCard.suit = 2;
    enemyCard.num = 14;
    enemyCard.isFlipped = 0;
    card* enemyPtr = &enemyCard;
    cardArr[0] = enemyPtr;
    
    //creates a health card for testing
    card healthCard;
    healthCard.suit = 2;
    healthCard.num = 14;
    healthCard.isFlipped = 0;
    card* healthPtr = &healthCard;
    cardArr[1] = healthPtr;
    
    //Creates attackCard1
    card attack1;
    attack1.suit = 1;
    attack1.num = 4;
    attack1.isFlipped = 0;
    card* A1Ptr = &attack1;
    cardArr[2] = A1Ptr;
    
    //Creates attackCard2
    card attack2;
    attack2.suit = 1;
    attack2.num = 7;
    attack2.isFlipped = 0;
    card* A2Ptr = &attack2;
    cardArr[3] = A2Ptr;
   
    //current mouse state
    bool mouseState = 0;
    
    Vector2 orig = {0.0f,0.0f};
    
    //source rectangle of enemy
    Rectangle enemySource = setCardIndex(enemyPtr);
    
    //source rect of health
    Rectangle healthSource = setCardIndex(healthPtr);
    
    //TODO: Write card center function and then offset the locations of draw rects from there
 
    //enemy Draw Rect
    Rectangle enemyDraw = {(float)(screenWidth/2) -(cardText->width/8),(float)(screenHeight/2) - (cardText->height),(float)(cardText->width/14) * 5,(float)(cardText->height/4) *5};
    
    //health Draw Rect
    Rectangle healthDraw = {(float)(screenWidth/2) -(cardText->width/8),(float)(screenHeight/2) - (cardText->height/2) + 200,(float)(cardText->width/14) * 5,(float)(cardText->height/4) *5};
    
    //Main game loop
    while(!WindowShouldClose())
    {
        //gets current mousePos
        mousePoint = GetMousePosition();
        
        /*
            This is all for one obj, ideally this can all be moved to a function
            so each obj doesn't take up half of the script
        */
        if(CheckCollisionPointRec(mousePoint,enemyDraw))
        {
            //create fucntion that does all this and just pass in enemyDraw and mousePoint
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                mouseState = 1;  
            }
            
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && mouseState == 1)
            {
                //resest mouse state
                //mouseState = 0;
                enemyPtr-> num = 10;
                enemyPtr->suit = 1;
                
                 if(enemyPtr->isFlipped == 0)
                 {
                  enemySource = FlipCard(enemyPtr);
                 
                 //set time of click
                 clickTime = GetTime();
                 //set anim to flip frame
                 Rectangle change = {((float)cardText->width/14) *13,((float)cardText->height/4) *0,(float)cardText->width/14,(float)cardText->height/4};
                 enemySource = change;
                 }
                 
            }
  
        }
        
        //There's prob going to have to be one of these for each card
        //so it can easily be made a function
         if(clickTime + .1f <= GetTime())
            {
                enemySource = setCardIndex(enemyPtr);
            }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawTexture(cards,15,40,WHITE);
        DrawTexturePro(*cardText,enemySource,enemyDraw,orig,0.0f,WHITE);
        DrawTexturePro(*cardText,healthSource,healthDraw,orig,0.0f,WHITE);
        EndDrawing();
        
       
    }
    
    //fprintf(stderr,"enemyCard suit: %d",enemyCard.suit);
    //create some sort of procedural card system
    
    //This 10 needs to be a variable
    for(int i = 0; i < 10;i++)
    {
        if(cardArr[i] != NULL)
        {
            card* tmpFree = NULL;
            //fprintf(stderr,"freeing %d: ",i);
            tmpFree = cardArr[i];
            free(tmpFree);
        }
    }
    //Proves that cardArr[] is story copies so cards are not actually freed
    //fprintf(stderr,"cardArr1: %d",cardArr[0]->num);
    //FIXME: This is the temp solution until I switch cardArr to a card**
    free(cardArr[0]);
    free(cardArr[1]);
    free(cardArr[2]);
    free(cardArr[3]);
        
    //Unload cards texture
    UnloadTexture(*cardText);
    return 0;
}