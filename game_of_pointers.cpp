#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row,
		      int rows, int columns, int *reserves, ofstream &output){
    //returns true if the invaders breach the walls.
    //rows and cols are in relation to protectors!

    //I will set dead people to have power =1 and weapon = "empty"
    int cols = columns;
        for(int i=0; i<rows; i++){
            if(skirmish_row >= 0 && skirmish_row < cols){//ORIGINALLY ROWS
            	//if invader position is empty
                if(invaders[skirmish_row][i][0].power == 1){
                    output<<"No assault\n";
                }
                //if protector position is empty
                if(protectors[i][skirmish_row][0].power == 1){
                    return true;
                }
                    if((invaders[skirmish_row][i][0].weapon == "sword" &&
                        protectors[i][skirmish_row][0].weapon == "sword")||
                        (invaders[skirmish_row][i][0].weapon == "axe" &&
                            protectors[i][skirmish_row][0].weapon == "axe")){
                                //if same weapon, check power
                                if(invaders[skirmish_row][i][0].power ==
                                    protectors[i][skirmish_row][0].power){
                                        output<<"Duel ends in draw\n";
                                    }
                                    //protector wins
                    else if((invaders[skirmish_row][i][0].power <
                        protectors[i][skirmish_row][0].power)){
                            output<<"Invader killed\n";
                            //1 power and "empty" means dead invader
                            invaders[skirmish_row][i][0].power = 1;
                            invaders[skirmish_row][i][0].weapon = "empty";
                        }
                                    //protector loses
                                else if(invaders[skirmish_row][i][0].power >
                                    protectors[i][skirmish_row][0].power){

                                		//checks for holes in invader army
                                		int filled = 0;
			                            for(int u=0;u<cols;u++){
			                                if(filled!=0){
			                                    break;
			                                }
			                                for(int y=0;y<rows;y++){
			                                    if(filled!=0){
			                                        break;
			                                    }
			                                    for(int z=0;z<1;z++){
			                                        if(filled!=0){
			                                            break;
			                                        }
                                if(invaders[u][y][z].power == 1){
                                    invaders[u][y][z].power =
                                        protectors[u][skirmish_row][0].power;
                                    invaders[u][y][z].weapon =
                                        protectors[u][skirmish_row][0].weapon;
                                    filled = 1;
                                    output<<"Protector defected\n";
                                }
			                                    }
			                                }
			                            }
                        if(filled==0){
                            output<<"Protector killed\n";
                            protectors[i][skirmish_row][0].power = 1;
                            protectors[i][skirmish_row][0].weapon = "empty";
                            //1 power and "empty" means dead protector
                        }
                        if(*reserves > 0){
                        	protectors[i][skirmish_row][0].power = 100;
                            protectors[i][skirmish_row][0].weapon = "axe";
                            (*reserves)--;
                        }
                            }
                            }
                    else if((invaders[skirmish_row][i][0].weapon == "axe" &&
                        protectors[i][skirmish_row][0].weapon == "sword")){
                            //checks for holes in invader army
                            int filled = 0;
                            for(int u=0;u<cols;u++){
                                if(filled!=0){
                                    break;
                                }
                                for(int y=0;y<rows;y++){
                                    if(filled!=0){
                                        break;
                                    }
                                    for(int z=0;z<1;z++){
                                        if(filled!=0){
                                            break;
                                        }
                                if(invaders[u][y][z].power == 1){
                                    invaders[u][y][z].power =
                                        protectors[u][skirmish_row][0].power;
                                    invaders[u][y][z].weapon =
                                        protectors[u][skirmish_row][0].weapon;
                                    filled = 1;
                                    output<<"Protector defected\n";
                                }
                                    }
                                }
                            }
                        if(filled==0){
                            output<<"Protector killed\n";
                            protectors[i][skirmish_row][0].power = 1;
                            protectors[i][skirmish_row][0].weapon = "empty";
                            //1 power and "empty" means dead protector
                        }


                if(*reserves > 0){
                            	protectors[i][skirmish_row][0].power = 100;
                                protectors[i][skirmish_row][0].weapon = "axe";
                                (*reserves)--;
                }






                            }
                else if((invaders[skirmish_row][i][0].weapon == "sword" &&
                    protectors[i][skirmish_row][0].weapon == "axe")){
                        invaders[skirmish_row][i][0].power = 1;
                        invaders[skirmish_row][i][0].weapon = "empty";
                        //1 power and "empty" denotes empty position
                        output<<"Invader killed\n";
                    }
            }
            else{
                continue;
            }
        }



    return false;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserves;
    int skirmishes;

    //read the input file and initialize the values here.
    input >> rows >> cols >> reserves >> skirmishes;

    Warrior ***protectors;
    Warrior ***invaders;

    //initialize the protectors and invaders here.
    //protectors first
    protectors = NULL;
    invaders = NULL;

    //allocate protectors
    protectors = new Warrior**[rows];
    for(int i=0; i<rows; i++){
        protectors[i] = new Warrior*[cols];
        for(int j=0; j<cols; j++){
            protectors[i][j] = new Warrior[1];
            //first line of protectors (set weapon/power)
            for(int k=0;k<1;k++){
                protectors[i][j][k].power = (i*10)+((j+1)*10);
                if(i%2==0){
                    protectors[i][j][k].weapon = "axe";
                }
                else{
                    protectors[i][j][k].weapon = "sword";
                }
            }
        }
    }
    //invaders next
    invaders = new Warrior**[cols];
    for(int i=0; i<cols; i++){
        invaders[i] = new Warrior*[rows];
        for(int j=0; j<rows; j++){
            invaders[i][j] = new Warrior[1];
            for(int k=0; k<1; k++){
                invaders[i][j][k].power = (i*10)+((j+1)*10);
                if(i%2!=0){
                    invaders[i][j][k].weapon = "axe";
                }
                else{
                    invaders[i][j][k].weapon = "sword";
                }
            }
        }
    }

    bool end = false;
    for (int i=1; i <= skirmishes; i++){
        int skirmish_row;

        //read the input file to find the value for skirmish row
    input>>skirmish_row;
    //In general, it is bad style to throw everything into your main function
    end = skirmish(protectors, invaders,
        skirmish_row, rows, cols, &reserves, output);
}

    //output the winner and deallocate your memory.
    if(end){
        output<<"Winner: invaders";
    }
    else{
        output<<"Winner: protectors";
    }
    //time to deallocate
    for(int i=0; i<rows;i++){
        for(int j=0;j<cols;j++){
            delete[] protectors[i][j];
        }
        delete[] protectors[i];
    }
    delete protectors;

    for(int i=0; i<cols;i++){
        for(int j=0;j<rows;j++){
            delete[] invaders[i][j];
        }
        delete[] invaders[i];
    }
    delete invaders;

    return 0;
}
