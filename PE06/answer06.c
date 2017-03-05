#include "answer06.h"
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
// You may add more functions in this file.

// do NOT modify any #ifdef or #endif
// they are used for giving partial credits

// The following line must be above divideDeck
#ifdef TEST_DIVIDE 
void divideDeck(CardDeck origdeck, 
		CardDeck * upperdeck, CardDeck * lowerdeck)
{

  int index1;
  int index2;
  int index3;
  for(index1= 0; index1<origdeck.size -1; index1++)
  {
    upperdeck[index1].size = 0;
	lowerdeck[index1].size = 0;

	for(index2=0; index2 < index1 + 1; index2++)
	{
	  upperdeck[index1].cards[index2] = origdeck.cards[index2];
	  upperdeck[index1].size ++;
	}
	for(index3 = 0; index3<origdeck.size -1 -index1;index3++)
	{
	  lowerdeck[index1].cards[index3] = origdeck.cards[index2+index3];
	  lowerdeck[index1].size ++;
	}
  }
  // if the original deck has n cards, there are n - 1 pairs of
  // upper and low decks: 
  // 1.   upper deck has 1 card,      low deck has n - 1 cards
  // 2.   upper deck has 2 cards,     low deck has n - 2 cards
  // 3.   upper deck has 3 cards,     low deck has n - 3 cards
  // ...
  // n-1. upper deck has n - 1 cards, low deck has 1 cards
  
  // upperdeck[0] should store the first card in the original deck
  // upperdeck[1] should store the top two cards in the original deck
  // upperdeck[2] should store the top three cards in the original deck

  // be careful that in CardDeck, cards is an array (thus a pointer)
}
#endif
// The previous line must be below divideDeck

#ifdef TEST_INTERLEAVE
// reuse what you wrote for PE05
void helper(CardDeck upperdeck,CardDeck lowerdeck,CardDeck newcards,int upperdeck_index, int lowerdeck_index);

void interleave(CardDeck upperdeck, 
		CardDeck lowerdeck)
{
  // create a new deck storing the result
 // this new deck's size should be the sum of the
  // sizes of upperdeck and lowerdeck
 // int lowsize = strlen (lowerdeck);
 // int newsize = upsize + lowsize;
  CardDeck newcards;  
 
  // call the helper function with appropriate arguments
    int lowerdeck_index = 0;
   int upperdeck_index = 0;
   
   newcards.size = upperdeck.size + lowerdeck.size; 
   helper(upperdeck, lowerdeck, newcards, upperdeck_index, lowerdeck_index);     


}

void helper(CardDeck upperdeck,CardDeck lowerdeck,CardDeck newcards,int upperdeck_index, int lowerdeck_index)
{
  int index4;
  int index5;
  //Upper condition
  //End condition
  if(upperdeck_index == upperdeck.size || lowerdeck_index == lowerdeck.size)
  {
    if(upperdeck_index == upperdeck.size  )
	{
	  upperdeck_index--;
	  for(index4 = upperdeck_index + lowerdeck_index + 1; index4 < newcards.size ; index4++)
	     {
		  newcards.cards[index4] =lowerdeck.cards[lowerdeck_index++];
		  
		 }
    }
	else if(lowerdeck_index == lowerdeck.size)

	{
	 lowerdeck_index--;
     for(index5 =  upperdeck_index + lowerdeck_index + 1; index5 < newcards.size; index5++)
	{
	  newcards.cards[index5] = upperdeck.cards[upperdeck_index ++];
	}
    }
    printDeck(newcards);
	printf("\n");
	return;
  }
  newcards.cards[lowerdeck_index + upperdeck_index] = upperdeck.cards[upperdeck_index];
  //Change the upperdeck to the new upperdeck 
      
 //Recurision 
   helper(upperdeck, lowerdeck, newcards, upperdeck_index + 1, lowerdeck_index);
 

 //Lower condition
  newcards.cards[lowerdeck_index + upperdeck_index] = lowerdeck.cards[lowerdeck_index]; 
  

  helper(upperdeck, lowerdeck, newcards, upperdeck_index, lowerdeck_index + 1 );




}
#endif

#ifdef TEST_SHUFFLE
void shuffle(CardDeck origdeck)
{
  // origdeck contains the number of cards
  // the number of upper-low deck pairs should be 
  //     the number of cards - 1
  // this function has the following steps:
  //    calculate the number of upper-low deck pairs
  //    allocate enough memory to accommodate the pairs
  //    call divideDeck to find these pairs
  //    for each pair of upper-lower deck, interleave the cards
  //    release the allocated memory
  // 
  // The amount of memory allocated in this function must be
  // determined based on the size of the original deck. The program
  // may fail if the allocated memory has a fixed size (some students
  // like to use 1000 but nobody could explain why 1000).  If you do
  // not know how much memory to allocate, please refer to PE05's
  // README.
  // 
  // You will lose 50% points if the amount of allocated memory is not
  // determined by the size of the original deck.  To be more precise,
  // you will use 50% point if you use 100, 1000, 10000 (or any other
  // fixed number) without clear explanation.
  //

  // the following code gives you some hints. You may make any changes
  // as appropriate;
  int numpairs = origdeck.size -1;
  
  CardDeck * upperdeck = NULL;
  CardDeck * lowerdeck = NULL;
//upperdeck[0] 
//upperdeck[1]
//upperdeck[1]->cards[0] pointer
  // allocate memory
  if (upperdeck == NULL)
    {
	 upperdeck = (CardDeck*)malloc(numpairs *sizeof(CardDeck));
    }
  if (lowerdeck == NULL)
    {
	 lowerdeck = (CardDeck*)malloc(numpairs* sizeof(CardDeck));
    }

  // call divideDeck to fill upperdeck and lowerdeck 
  divideDeck(origdeck, upperdeck, lowerdeck);
  int i=0;
  while (i < numpairs)
    {
	 print2Deck(upperdeck[i],lowerdeck[i]);
	 interleave(upperdeck[i],lowerdeck[i]);

      // for each pairs call interleave
	  i++;
    }
	free(upperdeck);
	free(lowerdeck);
} 
#endif
