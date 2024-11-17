#include <stdlib.h> 
#include "main.h" //I think it's okay to include this here as well as main.c
#include <stdlib.h>

//TODO: Move this to a shard header file
typedef struct card
{
    int suit;
    int num;
    int isFlipped; //0 means face down, 1 means face up
    int health;
} card;

//Creates a card and adds it to the Card array;
// -1 means random, otherwise suit needs to be between  1 and 4, num needs to be between 1 and 14
card* CreateCard(int suit, int num)
{
    card* tmp =  malloc(sizeof(card));
    if(suit == -1)
    {
        tmp->suit = GetRandomValue(1,4);
    }
    else if(suit > 0 && suit < 5)
    {
        tmp->suit = suit;
    }
     //catch for anything invalid
    else
    {
        return NULL;
    }
    
    if(num == -1) //Random does not assign special cards
    {
        tmp->num = GetRandomValue(1,13);
    }
    else if(num > 0 && num < 15) //this allows you to assign special card
    {
        tmp->num = num;
    }
    //catch for anything invalid
    else
    {
        return NULL;
    }

    return tmp;   
}

//returns a source rectangle mapped to provided card num and suit
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
int checkCardClicked(Vector2 mousePos,Rectangle cardDrawRect)
{
    if(CheckCollisionPointRec(mousePos,cardDrawRect))
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            //this card has been clicked
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}