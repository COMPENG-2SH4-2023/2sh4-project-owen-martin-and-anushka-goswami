#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = '\0';

    boardSizeX = 30;
    boardSizeY = 15;

    exitFlag = false;
    loseFlag = false;

    score = 0;

    arraySize = ARRAYSIZE;
    binSize = 0;
    itemBin = new objPos[arraySize];

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';

    boardSizeX = boardX;
    boardSizeY = boardY;

    exitFlag = false;
    loseFlag = false;

    score = 0;

    arraySize = ARRAYSIZE;
    binSize = 0;
    itemBin = new objPos[arraySize];

}

// do you need a destructor?
GameMechs::~GameMechs()
{
    delete itemBin;
}



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}


bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    return input;
}

void GameMechs::updateInput()
{
    if(MacUILib_hasChar() == 1)
    {
        input = MacUILib_getChar();
    }
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

int GameMechs::getBinSize()
{
    return binSize;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = MacUILib_getChar();
}

void GameMechs::clearInput()
{
    input = '\0';
}

void GameMechs::incrementScore()
{
    score += 1;
}

void GameMechs::checkStatus()
{
    if(input == ((char)27))
    {
        exitFlag = 1;
    }
}

void GameMechs::generateFood(objPosArrayList* blockOff)
{

    if(arraySize <= (boardSizeX * boardSizeY) - blockOff->getSize() - 3 && arraySize != binSize)
    {
        binSize = arraySize;
    }
    else if(arraySize > (boardSizeX * boardSizeY) - blockOff->getSize() - 3)
    {
        binSize = (boardSizeX * boardSizeY) - blockOff->getSize() - 3;
    } 
    else if((boardSizeX * boardSizeY) - blockOff->getSize() <= 3)
    {
        binSize = 1;
    }

    int random_num_x;
    int random_num_y;
    char random_symbol;

    srand(time(NULL));

    char food_symbols_string[] = "*$?";
    int str_len;
    int max_rand_symbols = 3;
    for(str_len = 0;food_symbols_string[str_len]!= '\0';str_len++);

    int generation_flag = 1;

    int m = blockOff->getSize();

    objPos tempObj;
    
    int i,j,k;
    for(i = 0 ; i < binSize ; i++)
    {
        
        do
        {
            generation_flag = 0;

            random_num_x = rand() % (boardSizeX-1);
            random_num_y = rand() % (boardSizeY-1);
            random_symbol = food_symbols_string[(rand() % (str_len))];


            for(k = 0; k < m ; k++)
            {
                blockOff->getElement(tempObj,k);
                if(random_num_x == tempObj.x && random_num_y == tempObj.y) generation_flag = 1;
            }
            

           
            for(j=0; j < i; j++)
            {
                if((random_num_x == itemBin[j].x)||(random_num_y == itemBin[j].y))
                {
                    generation_flag = 1;
                }

                if(j >= max_rand_symbols)
                {
                    random_symbol = '*';
                }
            }
            

            
        } while(generation_flag == 1);
        itemBin[i].x = random_num_x;
        itemBin[i].y = random_num_y;
        itemBin[i].symbol = random_symbol;
    }

}

const objPos* GameMechs::getFoodPos()
{
    return itemBin;
}


