#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"
#include "../include/rules.h"

#define row 5  
#define col 6 
using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

class  Node{
    private:
        Board currentboard;
        Node *nextNode[30];
        Node *preNode;
        Player* player ; 
        int index[2];   
 
    public:
        Node(Board  , int  , int, Player*);
        Node(Board , Player*) ;
        int setnextNode(Node* ,Player*);
        Node* setoppoNode(Node* , Player*) ;
        int countscore() ; 
        void chooseindex(Node* , Player* , int*);
        Node* getNextNode(int i)
        {
            return nextNode[i];
        }
        Board getboard()
        {
            return currentboard ; 
        }
        Player* getplayer()
        {
            return player ;
        } 
        int* getindex()
        {
             return index;
        }
      
};

Node::Node(Board board , int i , int j , Player* play )
{
     currentboard = board ; 
     index[0] = i ; 
     index[0] = j ; 
     player  = play ; 
     
     for(int i=0 ; i<30 ; i++)
       nextNode[i] = NULL ;  
     
}

Node::Node(Board board , Player *play)
{
     currentboard = board ; 
     player  = play ;  
     for(int i=0 ; i<30 ; i++)
       nextNode[i] = NULL ;  

}

int Node::countscore()
{
     int score = 0 ;
     char color = player->get_color() ; 
     Board board = this->getboard() ; 

     for(int i=0 ; i<row ; i++)
     {
         for(int j=0 ; j<col ; j++)
         {
             if(board.get_cell_color(i, j)==color)
             score+=board.get_orbs_num( i, j) ; 
         }
     }
     return score ; 

} 

void Node::chooseindex(Node* now , Player*, int * index)
{
    int highscore =  0 ;
    int tempscore;  
    int nodenumber = 0 ; 
    int  oppcolor ='w' ;
    nodenumber= setnextNode(this ,player) ; 
    Node* resultnode ; 
    char color = player->get_color() ;

    if(color=='r')oppcolor ='b' ; 
    else   oppcolor ='r' ; 

    Player *opponent =  new Player(oppcolor) ; 

    for(int i=0  ; i<nodenumber  ; i++)
    {
        Node* temp  = (now->getNextNode(i))->setoppoNode( nextNode[i] , opponent);
        tempscore = temp->countscore();
        if(tempscore>highscore)
        {
            highscore = tempscore ; 
        }
         resultnode =now->getNextNode(i) ; 

    }
    index[0] = resultnode->getindex()[0];
    index[1] = resultnode->getindex()[1];
    

}

int Node::setnextNode(Node* now , Player* play)
{
    int index = 0 ; 
   
    for(int i=0  ; i<row ; i++)
    {
        for(int j=0 ; j<col ; j++)
        {
             Board newboard  = now->getboard() ;
             if(newboard.place_orb(i , j , play))
             {
                 Node* newnode = new Node(newboard, i , j , play);
                 now->nextNode[index++] = newnode ;
             }
             
        }
    }
    return index ; 

}
Node* Node::setoppoNode(Node* now , Player* oppo)
{

        int score = 0 ; 
        Node *bestnode = NULL ; 
   
    for(int i=0  ; i<row ; i++)
    {
        for(int j=0 ; j<col ; j++)
        {
             Board newboard  = now->getboard() ;
             if(newboard.place_orb(i , j , oppo))
             {
                 Node* newnode = new Node(newboard, i , j , oppo);
                 if(newnode->countscore()>score )
                 bestnode =newnode ; 
             }
             
        }
    }
    return bestnode ; 

}
void algorithm_A(Board board, Player player, int index[]){
    Node *head = new Node(board, &player) ; 
     
    head->chooseindex(head , &player,  index); 


}
