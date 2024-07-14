#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__
#include <cmath>
#include <list>
#include <memory>
#define MAX(x,y) ((x)>(y)?(x):(y))
#include "WorldBase.hpp"
#include "utils.hpp"
typedef enum type {
	None,
	Back_ground,
	Sunshine,
	Planting_spot,
	Objecttype_shovel,
	Plants,
	Flower_seed,
	Peashooter_seed,
	Repeater_seed,
	Wallnut_seed,
	Cherry_seed,
	PEA,
	EXPLOSION,
	Zombies,
	MASK
}ObjectType;
class GameObject;

class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld> {
public:
  // Use shared_from_this() instead of "this".
  GameWorld();
  virtual ~GameWorld();

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;
  int Gettick();
  std::list<std::shared_ptr<GameObject>> FindObject() { return objects; };
  void Setclicktime(int x) { Clicktime = x; };
  int Getclicktime() { return Clicktime; };
  void Setclicktype(ObjectType x) { ClickType = x; };
  ObjectType Getclicktype() { return ClickType; };
  void putinto(std::shared_ptr<GameObject> obj) { objects.push_back(obj); };
  //int GetShovelclick() { return Shovelclick; };
  void SetShovelclick(int x) { Shovelclick = x; };
  bool isShovel() { return Shovelclick == 1; };
  int GetShovelclick() { return Shovelclick; };
  int Getwavezobie() { return Wavezombie; };
  void Setwavezobie(int x) { Wavezombie = x; };
  bool isZombie(int);
private: 
	std::list<std::shared_ptr<GameObject>> objects;
	int m_tick;
	int Clicktime = 0;
	ObjectType ClickType = None;
	int Shovelclick = 0;
	int Lastwave_tick = 1200;
	int Wavezombie = 0;
};

#endif // !GAMEWORLD_HPP__
