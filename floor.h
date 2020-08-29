#ifndef _FLOOR_H_
#define _FLOOR_H_
#include "chamber.h"
#include "passage.h"
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <ncurses.h>


class DragonHoard;
class Cell;

class Floor{
    int level;
    bool end;
    std::shared_ptr<Player> pc;
    std::vector<Chamber> chambers;
    std::map<int, std::map<int, std::shared_ptr<Passage>>> passages;
	std::string message;
	bool enemyStop;
	bool generateItem;
	// ------------ helper fields and methods --------------------
    std::vector<std::vector<int>> status; // denotes the chamber to which cells belong
    /* status[i][j] = num 
		 means the cell at [i][j] belongs to chambers[num] 
        num = 9 means cell at [i][j] is a passage 
        num = -1 means cell at [i][j] is blank
    */
    std::vector<std::vector<char>> charStatus; // denotes the type of the cell 
    void adjust(int chamberAdjusted, int indicator); // helper function
    bool checkForDragon(int r, int c); // helper function
  std::shared_ptr<Cell> findCell(int chamber); //helper
	void setObservers(std::shared_ptr<Characters> ); 
	void spawnDragon(int i, int j, int cn, std::shared_ptr<DragonHoard> );
	// ------------------------------------------------------

	public:
    Floor();
	void init(std::unique_ptr<std::ifstream> infile);
  	void generatePC(char race);
  	void generate();
	void setEnemyStop();
	bool getEnd();
	void reset(int flag);
	void resetTile(int x, int y, int chamber);      
 
 	// Implementation after Game begins
	void PCAction(char mode, const std::string & direction = {});
    
    void randomMove(std::shared_ptr<Enemy> e);

  	std::vector<std::vector<int>> getStatus();

    ~Floor();

	friend class FloorDisplay; // display pc, enemies, items ...

};

#endif
