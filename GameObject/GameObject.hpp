#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"
#include "GameWorld.hpp"

// Declares the class name GameWorld so that its pointers can be used.
using pGameWorld = std::shared_ptr<GameWorld>;

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject> {
public:
  using std::enable_shared_from_this<GameObject>::shared_from_this; // Use shared_from_this() instead of "this".
  GameObject(int, int , int , LayerID , int , int , AnimID , GameWorld& );
  GameWorld& Getworld() { return m_world; };
  void Setlifestate(int x) { lifestate=x; };
  int Getlifestate() { return lifestate; };
  void Determinelifestate(int x) ;
  bool isAlive() { return (lifestate == 1); };
  void SetMovetime(int t) { falltime = t; };
  int GetMovetime() { return falltime; }
  void Settype(ObjectType x) { type = x; };
  ObjectType Gettype() { return type; };
  int GetHP() { return HP; };
  void SetHP(int x) { HP = x; };
  bool isEating(AnimID N) { return N == ANIMID_EAT_ANIM; };
  bool isRunning(AnimID N) { return N == ANIMID_RUN_ANIM; };
  bool isJumping(AnimID N) { return N == ANIMID_JUMP_ANIM; };
  bool isWalking(AnimID N) { return N == ANIMID_WALK_ANIM; };
  void Setcoldtime(int x) { coldtime = x; };
  int Getcoldtime() { return coldtime; };
private:
	GameWorld& m_world;
	int lifestate=1;
	int falltime = 0;
	ObjectType type = None;
	int HP = 10;
	int coldtime = -1;
};
class Background : public GameObject {
public:
  Background(GameWorld&);
  void Update() override{}
  void OnClick() override{}
};
class Sun : public GameObject {
public:
 Sun(int, int, GameWorld&, int);
 void Update() override;
 void OnClick() override;
 void Setfalltick(int t) { falltick = t; };
 int Getfalltick() { return falltick; };
 int Getfalltime() { return falltime; };
 bool isNatural() { return Fromnature == 1; };
private:
	int falltime = randInt(63, 263);//理应下落的时间
	int falltick=0;//已经下落的时间
	int Fromnature;
};

class Sunflower : public GameObject {
public:
	void Update() override;
	void OnClick() override;
	Sunflower(int, int, GameWorld&);
	void Setlifetime(int x) { lifetime = x; };
	int Getlifetime() { return lifetime; };
	int Getfirstsun() { return FirstSun; };
private:
	int lifetime = 0;
	int FirstSun = randInt(30, 600);
};
class Peashooter : public GameObject {
public:
	void Update() override;
	void OnClick() override;
	Peashooter(int, int, GameWorld&);
	void Setcooltime(int x) { cooltime = x; };
	int Getcooltime() { return cooltime; };
private:
	int cooltime = 0;
};
class Repeater : public GameObject {
public:
	void Update() override;
	void OnClick() override;
	Repeater(int, int, GameWorld&);
	void Setcooltime(int x) { cooltime = x; };
	int Getcooltime() { return cooltime; };
private:
	int cooltime = 0;
};
class Wallnut : public GameObject {
public:
	void Update() override;//还没写
	void OnClick() override;
	Wallnut(int, int, GameWorld&);
	void Setlifetime(int x) { lifetime = x; };
	int Getlifetime() { return lifetime; };
	bool notCracked() { return Cracked == 0; };
	void setCracked(int n) { Cracked = n; };
private:
	int lifetime = 0;
	int Cracked = 0;
};
class Cherry: public GameObject {
public:
	void Update() override;
	void OnClick() override;//
	Cherry(int, int, GameWorld&);//
	void Setlifetime(int x) { lifetime = x; };
	int Getlifetime() { return lifetime; };
private:
	int lifetime = 0;
};

class Plantingspot : public GameObject {
public:
	void Update() override {};
	void OnClick() override;
	Plantingspot(int, int, GameWorld&);
};

class Flowerseed : public GameObject {
public:
	void Update() override {};
	void OnClick() override;
	Flowerseed(GameWorld&);
	int Getprice() { return price; };
private:
	int price = 50;
};
class Peashooterseed : public GameObject {
public:
	void Update() override {};
	void OnClick() override;
	Peashooterseed(GameWorld&);
	int Getprice() { return price; };
private:
	int price = 100;
};
class Repeaterseed : public GameObject {
public:
	void Update() override {};
	void OnClick() override;
	Repeaterseed(GameWorld&);
	int Getprice() { return price; };
private:
	int price = 200;
};
class Wallnutseed : public GameObject {
public:
	void Update() override {};
	void OnClick() override;
	Wallnutseed(GameWorld&);
	int Getprice() { return price; };
private:
	int price = 50;
};
class Cherryseed : public GameObject {
public:
	void Update() override {};
	void OnClick() override;
	Cherryseed(GameWorld&);
	int Getprice() { return price; };
private:
	int price = 150;
};
class Shovel :public GameObject {
public:
	void Update() override {};
	void OnClick() override;
	Shovel(GameWorld&);
private:
};
class Pea :public GameObject {
public:
	void Update() override ;
	void OnClick() override {};
	Pea(int ,int, GameWorld&);
private:
};
class Explosion :public GameObject {
public:
	void Update() override;
	void OnClick() override {};
	Explosion(int, int, GameWorld&);
	int Getlifetime() { return lifetime; };
	void Setlifetime(int x) { lifetime = x; };
private:
	int lifetime = 0;
};
class RegularZombie :public GameObject {
public:
	void Update() override;
	void OnClick()override {};
	RegularZombie(int, int, GameWorld&);
private:
};
//class PoleZombie :public GameObject {
//public:
//	void Update() override;
//	void OnClick()override {};
//	PoleZombie(int, int, GameWorld&);
//	void Setjumptick(int x) { jumptick = x; };
//	int Getjumptick() { return jumptick; };
//private:
//	int jumptick = 0;
//};
class PoleZombie :public GameObject {
public:
	void Update() override;
	void OnClick()override {};
	PoleZombie(int, int, GameWorld&);
private:
};
class BucketZombie :public GameObject {
public:
	void Update() override;
	void OnClick()override {};
	BucketZombie(int, int, GameWorld&);
	void Setbucket(int x) { bucket = x; };
	bool isBucket() { return bucket == 1; };
private:
	int bucket = 1;
};
class Coolmask :public GameObject {
public:
	void Update()override;
	void OnClick()override {};
	Coolmask(int, int, GameWorld&, int);
	int GetColdtick() { return coldtick; };
	void Setcoldtick(int x) { coldtick = x; };
	int Gettottime() { return tottime; };
private:
	int coldtick = 0;
	int tottime;
};


#endif // !GAMEOBJECT_HPP__
