#include <time.h>
#include <vector>
#include <iostream> 
#include <algorithm>

enum directions {
    dir_up, dir_down, dir_right, dir_left, dir_none
};

const int N = 16;
const int M = 32;
const int maxX = 100;
const int maxY = 50;
const int maxHeight = 9;
const int numMountains = 7;

struct Pos {
  int x; 
  int y;
  Pos() {} //creadora per defecte
  Pos(int ii, int jj) : x(ii), y(jj) { }    //creadora which set i = ii and j = jj (ii and jj are the parameters)
};

class Randoms {
    
public:
    Randoms(){}
    Randoms(int i){
       for(int k = 0; k < i; ++k) {
           nums.push_back(k);
           std::cerr << "added " << k << std::endl;
       }
    }
    ~Randoms(){}
    int getNum(){
        if(nums.size() >0) {
            int pos = rand()%nums.size();
            int ret = nums[pos];
            nums.erase(nums.begin()+pos);
        std::cerr << "number returned " << ret << std::endl;
            return ret;
        }
        std::cerr << "no numbers YO " << std::endl;
        return dir_none;
    }
    bool haveNumbers(){
        std::cerr << "checked " << (nums.size() > 0) << std::endl;
        return (nums.size() > 0);
    }
    
private:
    std::vector<int> nums;
};

//                    N   S   E   W  NONE
const int dirx[5] = { 0,  0,  1, -1, 0};
const int diry[5] = { 1, -1,  0,  0, 0};
const int inverseDir[5] = {1, 0, 3, 2, 5};


void drawMap(std::vector< std::vector < int> >& map){
    std::cout << map[0].size() << " " << map.size() << std::endl;
    for(int i = 0 ; i < map.size(); ++i){
        for(int j = 0 ; j < map[0].size(); ++j){
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool valid(std::vector< std::vector < int> > & map, int posx, int posy, int dir){
    std::cerr << "lets validate... " << std::endl; 
    
    if     ((!(posx < 0 ))
        && (!(posy < 0 ))
        && (!(posx >= map[0].size()))
        && (!(posy >= map.size()))
        && ( (map[posy][posx] == 0)) ){
            
            for(int i = 0; i < 4 ; ++i){
                
                if(i != inverseDir[dir]){
                    int posx2 = posx + dirx[i];
                    int posy2 = posy + diry[i];

                    if ((posx2 >= 0 )
                    && (posy2 >= 0 )
                    && (posy2 < map.size())
                    && (posx2 < map[0].size())) {
                        if ((map[posy2][posx2] == 1)) return false;
                    }
                }
                
            }
            
            return true;
        }
        return false;
        
//     return (
//            (!(posx < 0 ))
//         && (!(posy < 0 ))
//         && (!(posx2 < 0 ))
//         && (!(posy2 < 0 ))
//         && (!(posy >= map.size()))
//         && (!(posy2 >= map.size()))
//         && ( (map[posy][posx] == 0))
//         && (!(posx >= map[0].size()))
//         && (!(posx2 >= map[0].size()))
//         && ( (map[posy2][posx2] == 0))
//         
//     );
}

void generateMaze(std::vector< std::vector < int> > & map, int iniX, int iniY){
    std::cerr << "generating Maze" << std::endl;
    Pos pos(iniX, iniY);
    
    Randoms randoms(4);
    
    while(randoms.haveNumbers()){
        int dir = randoms.getNum();
        if(dir != dir_none) {
            std::cerr << pos.x + dirx[dir] << " , " << pos.y + diry[dir] << std::endl;
                        std::cerr <<"           "<< pos.x + 2*dirx[dir] << " , " << pos.y + 2*diry[dir] << std::endl;
                        std::cerr << "dir " << dir << dirx[dir] << diry[dir] << std::endl;
            if(valid(map,pos.x + dirx[dir], pos.y + diry[dir], dir)){
                std::cerr << "validated" << std::endl;
                map[pos.y + diry[dir]][pos.x + dirx[dir]] = 1;
                generateMaze(map, pos.x + dirx[dir], pos.y + diry[dir]);
            }
        }
    }
    
}


int main(int argc, char *argv[]){
    
    std::srand(time(0));
    char arg1, arg2;
    if(argc >= 3){
        arg1 = *(argv[1]);
        arg2 = *(argv[2]);
    }
   // else std::cerr << "need the x and y of the map" << std::endl;
    
    int argv1, argv2;
    argv1 = N, 
    argv2 = M;
    
    //variable map
    std::vector< std::vector < int> > map( argv1, std::vector<int>(argv2, 0));
    
    generateMaze(map, 0,0);
    
    drawMap(map);
    
}