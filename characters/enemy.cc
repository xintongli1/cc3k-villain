#include "enemy.h"
#include "player.h"
#include "tile.h"
#include "merchant.h"
#include <algorithm>
#include <memory>
#include <cmath>
#include <iostream>
using namespace std;

Enemy::Enemy(int r, int c, std::string t, int ch, int h, int a, int d, char cha):
  Characters{r,c,t,ch,h,a,d},c{cha}{}

char Enemy::getChar() const{
  return c;
}

/*void Enemy::setHP(int n) {
  HP += n;
  HP = max(0, HP);
  HP = min(MaxHP, HP);
}*/

//for later
/*
void Enemy::attack(std::shared_ptr<Character> c) {
    c->attackedBy(this);
}

void Enemy::attackedBy(std::shared_ptr<Character> c) {
}
*/

//void Enemy::randomMove(){
    /*std::vector<std::shared_ptr<Tile>> pos;
    for (auto & it : observers){
        if (it->getType() == "tile"){
            std::shared_ptr<Tile> oo = std::dynamic_pointer_cast<Tile> (it);
            if (!oo->getOccupied()) pos.emplace_back(oo);
        }
    }
    if (pos.size() > 0){
        srand(time(NULL));
          int t = rand() % pos.size();
        cout<<row<<"+"<<col<<"+"<<pos[t]->getRow()<<"+"<<pos[t]->getCol()<<endl;
        row = pos[t]->getRow();
        col = pos[t]->getCol();
          pos[t]->setOccupied(true);
          pos[t]->setObject(std::make_shared<Enemy>(*this));
    }*/
   /* bool b=true;
    while(b){
    int aa = (rand() % 3)-1;
    int bb = (rand() % 3)-1;
        //&& f->chambers[getChamberNumber()].[row+aa][col+bb]->getType=="."
    if((aa!=0)&&(bb!=0)){
        //cout<<row<<"+"<<col<<"+"<<aa<<"+"<<bb<<endl;
    row = row+aa;
    col = col+bb;
    //pos[t]->setOccupied(true);
        //pos[t]->setObject(std::make_shared<Enemy>(*this));
        b = false;
    }
    }
}*/


bool Enemy::condition (bool rowGreater, bool colGreater, std::shared_ptr<Object> & o){
    if (o->getType() != "tile"){
        return false;
    }
    //std::shared_ptr<Tile> oo;
  auto oo = std::dynamic_pointer_cast<Tile> (o);
    if (!rowGreater){ // pc.row < this->row
        if (!colGreater){ // pc.col < this->col
            if(o->getRow() < this->getRow() && o->getCol() < this->getCol()){
                     return !oo->getOccupied();
            }
            else return false;
        }
            else{ // pc.row < this->row, pc.col > this->col
                if(o->getRow() < this->getRow() && o->getCol() > this->getCol()){
                        return !oo->getOccupied();
                }
                else return false;
            }
    }
    else{
        if (!colGreater){ // pc.row > this->row, pc.col < this->col
            if(o->getRow() > this->getRow() && o->getCol() < this->getCol()){
                    return !oo->getOccupied();
            }
            else return false;
        }
        else{ // pc.row > this->row, pc.col > this->col
            if(o->getRow() > this->getRow() && o->getCol() > this->getCol()){
                    return !oo->getOccupied();
            }
            else return false;
        }
    }
}


void Enemy::makeAction(){ // move or attack
    if (type == "merchant"){
        shared_ptr<Merchant> m = static_pointer_cast<Merchant>(make_shared<Enemy>(*this));
    //dynamic_pointer_cast<Merchant>(*this);//make_shared<Merchant>(*this);
    //dynamic_pointer_cast<Merchant>(*this);
        if (m->getHostile() == false){
            //andomMove();
            return ;
        }
    }

    auto pc = find_if(observers.begin(), observers.end(), [](std::shared_ptr<Object> & o){
        return o->getType() == "Shade" || o->getType() == "Vampire" || o->getType() == "Troll"
        || o->getType() == "Drow" || o->getType() == "Goblin" ;
    });

    if (pc != observers.end()){
        int r = (*pc)->getRow();
        int c = (*pc)->getCol();

        if (r <= this->getRow()){
              if (r == this->getRow()){
                //attack(std::make_shared<Player>(*(*pc)));
                attack(std::dynamic_pointer_cast<Player>((*pc)));
                //(*pc)->attack(std::make_shared<Enemy>(*this));

              }
              else{ //  r < this->getRow()
                if (c <= this->getCol()){
                    if (c == this->getCol()){
                        //attack(std::make_shared<Player>(*pc));
            attack(std::dynamic_pointer_cast<Player>((*pc)));
                        //(*pc)->attack(std::make_shared<Enemy>(*this));
                    }
                    else{ // c < getCol()
                        auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                                return condition(false, false, o);
                                });
                          std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                          if (p != nullptr && p->getOccupied() == false){
                            row = p->getRow();
                            col = p->getCol();
                            p->setOccupied(true);
                            p->setObject(std::make_shared<Enemy>(*this));
                          }
                        else{
                            auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                                return condition(false, true, o);
                                });
                            std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                            if (p != nullptr && p->getOccupied() == false){
                                row = p->getRow();
                                col = p->getCol();
                                p->setOccupied(true);
                                p->setObject(std::make_shared<Enemy>(*this));
                            }
                            else{
                                auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                                    return condition(true, false, o);
                                    });
                                std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                                if (p != nullptr && p->getOccupied() == false){
                                    row = p->getRow();
                                    col = p->getCol();
                                    p->setOccupied(true);
                                    p->setObject(std::make_shared<Enemy>(*this));
                                }
                                //else randomMove();
                            }
                        }

                    }
                }
                else { // c > getCol()
                    auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                            return condition(false, true, o);
                            });
                    std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                    if (p != nullptr && p->getOccupied() == false){
                        row = p->getRow();
                        col = p->getCol();
                        p->setOccupied(true);
                        p->setObject(std::make_shared<Enemy>(*this));
                    }
                    else{
                        auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                            return condition(false, false, o);
                            });
                        std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                        if (p != nullptr && p->getOccupied() == false){
                            row = p->getRow();
                            col = p->getCol();
                            p->setOccupied(true);
                            p->setObject(std::make_shared<Enemy>(*this));
                        }
                        else{
                            auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                                return condition(true, true, o);
                                });
                            std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                            if (p != nullptr && p->getOccupied() == false){
                                row = p->getRow();
                                col = p->getCol();
                                p->setOccupied(true);
                                p->setObject(std::make_shared<Enemy>(*this));
                            }
                            //else randomMove();
                        }
                    }
                }
              }
        }
        else{ // r > getRow()
            if (c <= this->getCol()){
                  if (c == this->getCol()){
                    //attack(std::make_shared<Player>(*pc));
                    attack(std::dynamic_pointer_cast<Player>((*pc)));
                    //(*pc)->attack(std::make_shared<Enemy>(*this));
                  }
                  else{ //  c < getCol()
                      auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                              return condition(true, false, o);
                              });
                      std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                      if (p != nullptr && p->getOccupied() == false){
                          row = p->getRow();
                          col = p->getCol();
                          p->setOccupied(true);
                          p->setObject(std::make_shared<Enemy>(*this));
                      }
                      else{
                          auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                              return condition(true, true, o);
                              });
                          std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                          if (p != nullptr && p->getOccupied() == false){
                              row = p->getRow();
                              col = p->getCol();
                              p->setOccupied(true);
                              p->setObject(std::make_shared<Enemy>(*this));
                          }
                          else{
                              auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                                  return condition(false, false, o);
                                  });
                              std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                              if (p != nullptr && p->getOccupied() == false){
                                  row = p->getRow();
                                  col = p->getCol();
                                  p->setOccupied(true);
                                  p->setObject(std::make_shared<Enemy>(*this));
                              }
                              //else randomMove();
                          }
                      }
                  }
            }
            else{ // c > getCol()
                auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                        return condition(true, true, o);
                        });
                std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                if (p != nullptr && p->getOccupied() == false){
                    row = p->getRow();
                    col = p->getCol();
                    p->setOccupied(true);
                    p->setObject(std::make_shared<Enemy>(*this));
                }
                else{
                    auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                        return condition(true, false, o);
                        });
                    std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                    if (p != nullptr && p->getOccupied() == false){
                        row = p->getRow();
                        col = p->getCol();
                        p->setOccupied(true);
                        p->setObject(std::make_shared<Enemy>(*this));
                    }
                    else{
                        auto pos = find_if(observers.begin(), observers.end(), [this](std::shared_ptr<Object> o){
                            return condition(false, true, o);
                            });
                        std::shared_ptr<Tile> p = std::dynamic_pointer_cast<Tile> (*pos);
                        if (p != nullptr && p->getOccupied() == false){
                            row = p->getRow();
                            col = p->getCol();
                            p->setOccupied(true);
                            p->setObject(std::make_shared<Enemy>(*this));
                        }
                        //else randomMove();
                    }
                }
            }
        }
    }

    else{ // pc is not in this chamber
         //randomMove();
    }

    observers.clear();
}

std::string Enemy::info(){//helper to see current stat
    std::string c;
    c=std::to_string(this->getHP());
    std::string d;
    d=std::to_string(this->getAtk());
    std::string e;
    e=std::to_string(this->getDef());
    std::string s=" HP is: "+c+" Atk is: "+d+" Def is: "+e;
    return s;
}

void Enemy::attack(std::shared_ptr<Characters> c) {
    int success = rand() % 2;
    if (success) c->attackedBy(std::make_shared<Enemy>(*this));
    //this->attackedBy(c);
}

void Enemy::attackedBy(std::shared_ptr<Characters> c) {
    int damage = ceil((100.0 / (100 + this->getDef()))*(c->getAtk()));
    this->setHP(-damage);
    if(getHP() <= 0) setDead();
}



