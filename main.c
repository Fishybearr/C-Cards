#include "raylib.h"
#include "cardSystem.c"
#include <stdio.h>
#include "main.h"
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    
    double clickTime = -1.0; //Error Value
    
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth,screenHeight,"Cards Test window");
    
    //set fps
    SetTargetFPS(60);
    
    //stops escape from closing game
    SetExitKey(KEY_NULL);
    
    //MENU
    
    //Would create main menu here and run use some sort of loop that can
    //be broken when button is clicked
    Rectangle PlayButton = {400-50,200,100,25};
    Vector2 menuMousePos = {0.0,0.0};
    
    char* Title = "Weird Card Game";
    
    //IDEA: If I ever want to get horribly crazy I could start loading game logic
    // and assets on a different thread while in the menu
    //This game is so small though that I think that would honestly be worse for
    //performance (really funny though)
    while(!WindowShouldClose())
    {
        //get mousePos
        menuMousePos = GetMousePosition();
        //Check if button is pressed
        if(CheckCollisionPointRec(menuMousePos,PlayButton))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                    break;
            }
            
        }
        //DrawButton
        BeginDrawing();
         ClearBackground(BLACK);
         DrawText(Title,400-150,100,34,RAYWHITE);
         DrawRectangleRec(PlayButton,RAYWHITE);
         DrawText("Play",400-25,200,24,BLACK);
        EndDrawing();
    }
    //closes window without running any of the gameplay code
    if(WindowShouldClose())
    {
        //fprintf(stderr,"closing");
        return 0;
    }
    
    //Actual Game
    
    //TODO: look into swapping mouseDown and mouseUp for a simple mousePressed
    
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
    
    
    //mouse location
    Vector2 mousePoint ={0.0f,0.0f};
    
    //TODO: Create a hashmap for each card as well as their draw rectangles
    
    //creates an enemy card for testing
    cardArr[0] = CreateCard(2,14);
    cardArr[0]->isFlipped = 0;
    
    //creates a health card for testing
    cardArr[1] = CreateCard(1,-1); //currently only uses hearts
    cardArr[1]->isFlipped = 1;
    
    //Creates attackCard1
    cardArr[2] = CreateCard(2,14);
    cardArr[2]->isFlipped = 0;
    
    //Creates attackCard2
    cardArr[3] = CreateCard(2,14);
    cardArr[3]->isFlipped = 0;
   
    //current mouse state
    bool mouseState = 0;
    
    Vector2 orig = {0.0f,0.0f};
    
    //source rectangle of enemy
    Rectangle enemySource = setCardIndex(cardArr[0]);
    
    //source rect of health
    Rectangle healthSource = setCardIndex(cardArr[1]);
    
    //Anytime CreateCard is used, that card will then have to be freed as it was malloced
    Rectangle attack1Source = setCardIndex(cardArr[2]);
    
    Rectangle attack2Source = setCardIndex(cardArr[3]);
    
    
    //TODO: Write card center function and then offset the locations of draw rects from there
 
    //enemy Draw Rect
    Rectangle enemyDraw = {(float)(screenWidth/2) -(cardText->width/8),(float)(screenHeight/2) - (cardText->height),(float)(cardText->width/14) * 5,(float)(cardText->height/4) *5};
    
    //health Draw Rect
    Rectangle healthDraw = {(float)(screenWidth/2) -(cardText->width/8),(float)(screenHeight/2) - (cardText->height/2) + 200,(float)(cardText->width/14) * 5,(float)(cardText->height/4) *5};
    
    //attackLeft Draw Rect
    Rectangle attackLDraw = {(float)(screenWidth/2 - 100) -(cardText->width/8),(float)(screenHeight/2) - (cardText->height/2) + 200,(float)(cardText->width/14) * 5,(float)(cardText->height/4) *5};
    
    //attackRight Draw Rect
    Rectangle attackRDraw = {(float)(screenWidth/2 + 100) -(cardText->width/8),(float)(screenHeight/2) - (cardText->height/2) + 200,(float)(cardText->width/14) * 5,(float)(cardText->height/4) *5};
    
    //Main game loop
    while(!WindowShouldClose())
    {
        /*
        if(IsWindowResized())
        {
            screenWidth = GetScreenWidth();
           screenHeight = GetScreenHeight(); 
        }
        */
        //gets current mousePos
        mousePoint = GetMousePosition();
        
        /*
            This is all for one obj, ideally this can all be moved to a function
            so each obj doesn't take up half of the script
        */
        
        /*
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
                //enemyPtr-> num = 10;
                cardArr[0]->suit = 1;
                //Eventually this will probably how cards are generated
                cardArr[0]->num = GetRandomValue(1,13);
                
                 if(cardArr[0]->isFlipped == 0)
                 {
                  enemySource = FlipCard(cardArr[0]);
                 
                 //set time of click
                 clickTime = GetTime();
                 //set anim to flip frame
                 Rectangle change = {((float)cardText->width/14) *13,((float)cardText->height/4) *0,(float)cardText->width/14,(float)cardText->height/4};
                 enemySource = change;
                 }
                 
            }
  
        }
        */
        
        //TODO: Most of this logic can probaby be moved to another function to keep
        // the main update loop cleaner
        
                //click handling for enemy card
                if(checkCardClicked(mousePoint,enemyDraw))
                {
                    if(cardArr[0]->isFlipped == 0)
                    {
                        cardArr[0]->num= GetRandomValue(1,13);
                        cardArr[0]->suit = 1;
                        cardArr[0]->isFlipped = 1;
                        enemySource = setCardIndex(cardArr[0]);   
                    }
                }
                
                //Have extra logic in attacks cards so only one can be pick at a time
                 if(checkCardClicked(mousePoint,attackLDraw))
                {
                    if(cardArr[2]->isFlipped == 0)
                    {
                        cardArr[2]->num= GetRandomValue(1,13);
                        cardArr[2]->suit = 1;
                        cardArr[2]->isFlipped = 1;
                        attack1Source = setCardIndex(cardArr[2]);       
                    }
                    else
                    {
                        //attacks enemy
                        enemySource = AttackCard(cardArr[2],cardArr[0]);
                        
                        //removes card from player
                        attackLDraw.x -=400;
                        attackLDraw.y -= 400;
                    }
                }
                
                if(checkCardClicked(mousePoint,attackRDraw))
                {
                    if(cardArr[3]->isFlipped == 0)
                    {
                        cardArr[3]->num= GetRandomValue(1,13);
                        cardArr[3]->suit = 1;
                        cardArr[3]->isFlipped = 1;
                        attack2Source = setCardIndex(cardArr[3]);                        
                    }
                     else
                    {
                        //attacks enemy
                        enemySource = AttackCard(cardArr[3],cardArr[0]);
                        
                        //removes card from player
                        attackRDraw.x +=400;
                        attackRDraw.y += 400;
                    }
                }
           
           /*)
                //click handling for health card
               if(checkCardClicked(mousePoint,healthDraw))
               {
               
                    if(cardArr[1]->isFlipped == 0)
                    {
                        cardArr[1]->num= GetRandomValue(1,13);
                        cardArr[1]->suit = 1;
                        cardArr[1]->isFlipped = 1;
                        healthSource = setCardIndex(cardArr[1]);
                    }
               }
               */
               
               
              
        
        //There's prob going to have to be one of these for each card
        //so it can easily be made a function
        
        /*
         if(clickTime + .1f <= GetTime())
            {
                enemySource = setCardIndex(cardArr[0]);
            }
            */
            
        
        BeginDrawing();
        ClearBackground(DARKGREEN);
        //DrawTexture(cards,15,40,WHITE);
        
        //enemyCard
        DrawTexturePro(*cardText,enemySource,enemyDraw,orig,0.0f,WHITE);
        
        //HealthCard
        DrawTexturePro(*cardText,healthSource,healthDraw,orig,0.0f,WHITE);
        
        //attackCards
        DrawTexturePro(*cardText,attack1Source,attackLDraw,orig,0.0f,WHITE);
        DrawTexturePro(*cardText,attack2Source,attackRDraw,orig,0.0f,WHITE);
        
        EndDrawing();
        
       
    }
    
    //fprintf(stderr,"enemyCard suit: %d",enemyCard.suit);
    //create some sort of procedural card system
    
    //Will free all cards in cardArr. Will probably have to do this with hashmap later
    //Using magic numbers but this will just be the size of cardArr
   for(int i = 0; i < 10;i++)
    {
        if(cardArr[i] != NULL)
        {
            free(cardArr[i]);
        }
    }
    
    

    //Used as a test for freeing malloced cards
    //free(cardArr[6]);
        
    //Unload cards texture
    UnloadTexture(*cardText);
    return 0;
}