#include <stdlib.h> 
#include "main.h" //I think it's okay to include this here as well as main.c

//TODO: Move this to a shard header file
typedef struct card
{
    int suit;
    int num;
    int isFlipped; //0 means face down, 1 means face up
} card;

Rectangle setCardIndex(card* card)
{
    int xPos = 0;
    int yPos = 0;
    
    xPos = (card->num) -1;
    yPos = (card->suit) -1;
    //calc index based on suit and num
    Rectangle sourceRect = {((float)cardText->width/14) *xPos,((float)cardText->height/4) *yPos,(float)cardText->width/14,(float)cardText->height/4};
    
    return sourceRect;
}

//FlipCard
Rectangle FlipCard(card* card)
{
    Rectangle outRect;
    //This runs anytime card is not 2,14 which is back card
    if(card->num != 14 || card->num != 2)
    {
        //flip to face
        card->isFlipped = 1;
        Rectangle outRect = setCardIndex(card);
        return outRect;
    }
    else //This is where you would flip card to back if needed
    {
        //means card was already flipped
        return outRect;
    }
   
}

//return 0 for false, non 0 for true

//So this will run each frame for each card. mouse State will need to be set unique for each card
//This will stop you from clicking on one card and releasing on another
int checkCardClicked(Vector2 mousePos,Rectangle cardDrawRect,double mouseState)
{
    if(CheckCollisionPointRec(mousePos,cardDrawRect))
    {
        //if()
        return 0;
    }
    else
    {
        return 0;
    }
}