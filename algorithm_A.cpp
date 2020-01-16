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
        int index[2];   
        int score ; 
        int level ; 
    public:
        Node(Board , Player* , int  , int  ,int);
        Node(Board board) ;
        void setnextNode(Node* node);
        int countscore(Node* , Player*) ; 
        void chooseindex(Node*);
        Node* getNextNode();
        Board getboard()
        {
            return currentboard ; 
        }
      
};
Node::Node(Board board,Player* player , int i , int j , int level )
{
     currentboard = board ; 
     index[0] = i ; 
     index[0] = j ; 
     this->level = level ; 
     
     for(int i=0 ; i<30 ; i++)
       nextNode[i] = NULL ;  

     
}
Node::Node(Board board)
{
     currentboard = board ; 
     
     for(int i=0 ; i<30 ; i++)
       nextNode[i] = NULL ;  

}

int Node::countscore(Node* node, Player* play)
{
     int score = 0 ;
     char player = play->get_color() ; 
     Board board = node->getboard() ; 

     for(int i=0 ; i<row ; i++)
     {
         for(int j=0 ; j<col ; j++)
         {
             if(board.get_cell_color(i, j)==player)
             score+=board.get_orbs_num( i, j) ; 
         }
     }
     return score ; 

} 

void Node::chooseindex(Node* , Player*)
{
    int highscore =  0 ;
    for(int k=0 ; k<4 ; k++)
    {
       for(int i =0 ; i<row ; i++)
       {
           for(int j=0 ; j<col ; j++)
           {
            if()
           }
       }
    }


}

void algorithm_A(Board board, Player player, int index[]){
    Node *head = new Node(board) ; 
     
    chooseindex(head); 

    srand(time(NULL));
    int row, col;
    int color = player.get_color();
    
    while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }

    index[0] = row;
    index[1] = col;
}
