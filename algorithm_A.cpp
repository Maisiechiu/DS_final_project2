#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"
#include "../include/rules.h"
#include <iostream>


using namespace std;

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
        int countscore(Node* , Player*) ; 
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
     index[1] = j ; 
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

int Node::countscore(Node*now , Player* player)
{
     int score = 0 ;
     char color = player->get_color() ; 
     Board board = now->getboard() ; 

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

void Node::chooseindex(Node* now , Player*player, int * index )
{
    int highscore =  0 ;
    int tempscore;  
    int fristnodenumber = 0 ; 
    int secondnodenumber = 0 ; 
    int thirdnodenumber = 0 ; 
    int forthnodenumber = 0 ; 
    int  oppcolor ='w' ; 
    Node* resultnode ; 
    char color = player->get_color() ;
    if(color == 'r')
    oppcolor = 'b';
    else oppcolor = 'r';
    Player *opponent =  new Player(oppcolor) ;

    int nodenumber= setnextNode(this ,player) ; 
    for(int i=0  ; i<nodenumber  ; i++)
    {
        Node* temp  = (now->getNextNode(i))->setoppoNode( nextNode[i] , opponent);
        secondnodenumber =temp->setnextNode(temp  , player);
        for(int j=0 ; j<secondnodenumber;j++)
        {
             Node* temp2  = (temp->getNextNode(j))->setoppoNode(temp->getNextNode(j) , opponent);
             thirdnodenumber = temp2->setnextNode(temp2  , player);
             for(int k=0 ; k<thirdnodenumber ; k++)
             {
                int tempscore = temp2->getNextNode(k)->countscore(temp2->getNextNode(k),player);
                if(highscore<tempscore)
               {
                   resultnode = now->getNextNode(i) ;  
                   highscore = tempscore ;

               }
             }
      
        }

    }
    
    index[0] = resultnode->getindex()[0];
    index[1] = resultnode->getindex()[1];
    

}

int Node::setnextNode(Node* now , Player* play)
{
    int index = 0 ; 
    Player* temp =play ; 
    
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
             else  play = temp ; 
             
        }
    }
    return index ; 

}
Node* Node::setoppoNode(Node* now , Player* oppo)
{

        int score = 0 ; 
        Node *bestnode = NULL ; 
        Player* temp = oppo ; 
   
    for(int i=0  ; i<row ; i++)
    {
        for(int j=0 ; j<col ; j++)
        {
             Board newboard  = now->getboard() ;
             if(newboard.place_orb(i , j , oppo))
             {
                 Node* newnode = new Node(newboard, i , j , oppo);
                 if(newnode->countscore(newnode,oppo)>score )
                 bestnode =newnode ; 
             }
             else oppo=temp ; 
             
        }
    }
    return bestnode ; 

}
void algorithm_A(Board board, Player player, int index[]){

    Node *head = new Node(board, &player) ;     
    head->chooseindex(head , &player,  index); 


}
