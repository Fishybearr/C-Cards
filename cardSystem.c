#include <stdlib.h> 
#include "main.h" //I think it's okay to include this here as well as main.c
typedef struct card
{
    int suit;
    int num;
    int isFlipped; //0 means face down, 1 means face up
} card;

 //extern Texture2D* cards;
   // const Texture2D cardsBase = LoadTexture("images/CardFullTest.png");

Rectangle setCardIndex(card* card)
{
    //Set up a ref for this because it should not be crearted twice
    //Texture2D cards = LoadTexture("images/CardFullTest.png");
    //Texture2D cards = *cardText;
    int xPos = 0;
    int yPos = 0;
    
    
    xPos = (card->num) -1;
    yPos = (card->suit) -1;
    //calc index based on suit and num
    Rectangle sourceRect = {((float)cardText->width/14) *xPos,((float)cardText->height/4) *yPos,(float)cardText->width/14,(float)cardText->height/4};
    
    return sourceRect;
}