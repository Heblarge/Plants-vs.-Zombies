#include "GameObject.hpp"

#include<iostream>
GameObject::GameObject(int imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, GameWorld& world) :ObjectBase(imageID, x, y, layer, width, height, animID), m_world(world) {};
void GameObject::Determinelifestate(int x) {
	if (x > 0) {Setlifestate(1);}
	else { Setlifestate(0); }
}

Background::Background(GameWorld& world) : GameObject(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION, world) { Settype(Back_ground); };
Sun::Sun(int x, int y, GameWorld& world, int N) : GameObject(IMGID_SUN, x, y, LAYER_SUN, 80, 80, ANIMID_IDLE_ANIM, world), Fromnature(N) { Settype(Sunshine); };
Coolmask::Coolmask(int x, int y, GameWorld& world, int coldtime) : GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, 50, 70, ANIMID_NO_ANIMATION, world), tottime(coldtime) { Settype(MASK); };
void Sun::Update() {
	if (isNatural()) {
		Setfalltick(Getfalltick() + 1);
		if (Getfalltick() < Getfalltime()) {
			shared_from_this()->MoveTo(GetX(), GetY() - 2);
		}
		else if (Getfalltick() == Getfalltime() + 300) {
			Setlifestate(0);
		}
	}
	else if(!isNatural()){
		if (Getfalltick() < 12) {
			shared_from_this()->MoveTo(GetX() - 1, GetY() + 4 - Getfalltick());
		}
		else if (Getfalltick() == 12 + 300) {
			Setlifestate(0);
		}
		Setfalltick(Getfalltick() + 1);
	}
}
void Sun::OnClick() {
	Setlifestate(0);
	Getworld().SetSun(Getworld().GetSun() + 25);
	
}
Sunflower::Sunflower(int x, int y, GameWorld& world) : GameObject(IMGID_SUNFLOWER, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { SetHP(300); Settype(Plants);  };
void Sunflower::Update() {
	shared_from_this()->Determinelifestate(GetHP());
	if (Getlifetime() % 600 == Getfirstsun()) {
		Getworld().putinto(std::make_shared<Sun>(GetX(), GetY(), Getworld(), 0));
	}
	for (auto& object : Getworld().FindObject()) {
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->GetX() > shared_from_this()->GetX()) && (object->Gettype() == Zombies)) {
			SetHP(GetHP() - 3);
		}
	}
	Setlifetime(Getlifetime() + 1);
}
void Sunflower::OnClick() {
	if (Getworld().isShovel()) {
		Setlifestate(0);
		SetHP(0);
		Getworld().Setclicktime(0);
		Getworld().SetShovelclick(0);
	}
}
Plantingspot::Plantingspot(int x, int y, GameWorld& world): GameObject(IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION, world) { Settype(Planting_spot); };
void Plantingspot::OnClick() {
	if (Getworld().Getclicktime()>0) {
		if(Getworld().Getclicktype()== Flower_seed){
			Getworld().putinto(std::make_shared<Sunflower>(GetX(), GetY(), Getworld()));
			Getworld().Setclicktype(None);
		}
		if (Getworld().Getclicktype() == Peashooter_seed) {
			Getworld().putinto(std::make_shared<Peashooter>(GetX(), GetY(), Getworld()));
			Getworld().Setclicktype(None);
		}
		if (Getworld().Getclicktype() == Repeater_seed) {
			Getworld().putinto(std::make_shared<Repeater>(GetX(), GetY(), Getworld()));
			Getworld().Setclicktype(None);
		}
		if (Getworld().Getclicktype() == Wallnut_seed) {
			Getworld().putinto(std::make_shared<Wallnut>(GetX(), GetY(), Getworld()));
			Getworld().Setclicktype(None);
		}
		if (Getworld().Getclicktype() == Cherry_seed) {
			Getworld().putinto(std::make_shared<Cherry>(GetX(), GetY(), Getworld()));
			Getworld().Setclicktype(None);
		}
		Getworld().Setclicktime(0);
	}
}
Shovel::Shovel(GameWorld& world) :GameObject(IMGID_SHOVEL, 600, WINDOW_HEIGHT - 40, LAYER_UI, 50, 50, ANIMID_NO_ANIMATION, world) { Settype(Objecttype_shovel); };
void Shovel::OnClick() {
	if (Getworld().isShovel()) {
		Getworld().SetShovelclick(0);
	}
	else if(!Getworld().isShovel()) {//没拿铲子
		if (Getworld().Getclicktime() == 0) {//没拿着未种下的种子
			Getworld().SetShovelclick(1);
		}
	}
}
Flowerseed::Flowerseed(GameWorld& world) : GameObject(IMGID_SEED_SUNFLOWER, 130, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world) { Settype(Flower_seed); Setcoldtime(240); };
void Flowerseed::OnClick() {
	if (Getworld().GetSun() >= 50) {
		Getworld().Setclicktime(Getworld().Getclicktime() + 1);
		Getworld().Setclicktype(Flower_seed);
		Getworld().SetSun(Getworld().GetSun() - 50);
		Getworld().putinto(std::make_shared<Coolmask>(GetX(), GetY(), Getworld(), Getcoldtime()));
	}
}

Peashooter::Peashooter(int x, int y, GameWorld& world) : GameObject(IMGID_PEASHOOTER, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { SetHP(300); Settype(Plants);  };
Repeater::Repeater(int x, int y, GameWorld& world) : GameObject(IMGID_REPEATER, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { SetHP(300); Settype(Plants);  };
Wallnut::Wallnut(int x, int y, GameWorld& world) : GameObject(IMGID_WALLNUT, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { SetHP(4000); Settype(Plants); };
Cherry::Cherry(int x, int y, GameWorld& world) : GameObject(IMGID_CHERRY_BOMB, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, world) { SetHP(4000); Settype(Plants); };
void Peashooter::OnClick() {
	if (Getworld().isShovel()) {
		Setlifestate(0);
		SetHP(0);
		Getworld().Setclicktime(0);
		Getworld().SetShovelclick(0);
	}
}
void Repeater::OnClick() {
	if (Getworld().isShovel()) {
		Setlifestate(0);
		SetHP(0);
		Getworld().Setclicktime(0);
		Getworld().SetShovelclick(0);
	}
}
void Wallnut::OnClick() {
	if (Getworld().isShovel()) {
		Setlifestate(0);
		SetHP(0);
		Getworld().Setclicktime(0);
		Getworld().SetShovelclick(0);
	}
}
void Cherry::OnClick() {
	if (Getworld().isShovel()) {
		Setlifestate(0);
		SetHP(0);
		Getworld().Setclicktime(0);
		Getworld().SetShovelclick(0);
	}

}
void Wallnut::Update() {
	shared_from_this()->Determinelifestate(GetHP());
	for (auto& object : Getworld().FindObject()) {
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->GetX() > shared_from_this()->GetX()) && (object->Gettype() == Zombies)&&(object->isAlive())) {
			SetHP(GetHP() - 3);
		}
	}
	if (GetHP() <= 4000 / 3) {
		if (notCracked()) {
			ChangeImage(IMGID_WALLNUT_CRACKED);
			setCracked(1);
		}
	}
}
void Peashooter::Update() {
	if (Getcooltime() < 0) {
		Setcooltime(0);
	}
	if (Getcooltime() == 0) {
		if (Getworld().isZombie(GetY())) {
			Getworld().putinto(std::make_shared<Pea>(GetX() + 30, GetY() + 20, Getworld()));
			Setcooltime(30);
		}
	}
	for(auto& object:Getworld().FindObject()){
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2)  && (object->Gettype() == Zombies) && (object->isAlive())) {
			SetHP(GetHP() - 3);
		}
	}
	Setcooltime(Getcooltime() - 1);
}
void Cherry::Update() {
	shared_from_this()->Determinelifestate(GetHP());
	Setlifetime(Getlifetime() + 1);
	if (Getlifetime()  == 15) {
		Setlifestate(0);
		Getworld().putinto(std::make_shared<Explosion>(GetX(), GetY(), Getworld()));
	}
	for (auto& object : Getworld().FindObject()) {
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->GetX() > shared_from_this()->GetX()) && (object->Gettype() == Zombies) && (object->isAlive())) {
			SetHP(GetHP() - 3);
		}
	}
}
void Explosion::Update() {
	if (Getlifestate() == 1) {
		for (auto& object : Getworld().FindObject()) {
			if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->Gettype() == Zombies)) {
				object->Setlifestate(0);
			}
		}
	}
	Setlifetime(Getlifetime() + 1);
	if (Getlifetime() == 3) {
		Setlifestate(0);
	}
}

void Repeater::Update() {
	shared_from_this()->Determinelifestate(GetHP());
	if (Getcooltime() < 0) {
		Setcooltime(0);
	}
	if (Getcooltime() == 0) {
		if (Getworld().isZombie(GetY())) {
			Getworld().putinto(std::make_shared<Pea>(GetX() + 30, GetY() + 20, Getworld()));
			Setcooltime(30);
		}
	}

	if (Getcooltime() == 25) {
		if (Getworld().isZombie(GetY())) {
			Getworld().putinto(std::make_shared<Pea>(GetX() + 30, GetY() + 20, Getworld()));
		}
	}
	for (auto& object:Getworld().FindObject()){

		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->Gettype() == Zombies) && (object->isAlive())) {
			SetHP(GetHP() - 3);
		}
	}
	Setcooltime(Getcooltime() - 1);
}
Peashooterseed::Peashooterseed(GameWorld& world) : GameObject(IMGID_SEED_PEASHOOTER, 130+60, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world) { Settype(Peashooter_seed);Setcoldtime(240); };
Repeaterseed::Repeaterseed(GameWorld& world) : GameObject(IMGID_SEED_REPEATER, 130 + 4*60, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world) { Settype(Repeater_seed); Setcoldtime(240);};
Wallnutseed::Wallnutseed(GameWorld& world) : GameObject(IMGID_SEED_WALLNUT, 130 + 2 * 60, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world) { Settype(Wallnut_seed);Setcoldtime(900); };
Cherryseed::Cherryseed(GameWorld& world) : GameObject(IMGID_SEED_CHERRY_BOMB, 130 + 3 * 60, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, world) { Settype(Cherry_seed); Setcoldtime(1200); };
void Peashooterseed::OnClick() {
	if (Getworld().GetSun() >= 100 ) {
		Getworld().Setclicktime(Getworld().Getclicktime() + 1);
		Getworld().Setclicktype(Peashooter_seed);
		Getworld().SetSun(Getworld().GetSun() - 100);
		Getworld().putinto(std::make_shared<Coolmask>(GetX(), GetY(), Getworld(), Getcoldtime()));
	}
}
void Repeaterseed::OnClick() {
	if (Getworld().GetSun() >= 200 ) {
		Getworld().Setclicktime(Getworld().Getclicktime() + 1);
		Getworld().Setclicktype(Repeater_seed);
		Getworld().SetSun(Getworld().GetSun() - 200);
		Getworld().putinto(std::make_shared<Coolmask>(GetX(), GetY(), Getworld(), Getcoldtime()));
	}
}
void Wallnutseed::OnClick() {
	if (Getworld().GetSun() >= 50) {
		Getworld().Setclicktime(Getworld().Getclicktime() + 1);
		Getworld().Setclicktype(Wallnut_seed);
		Getworld().SetSun(Getworld().GetSun() - 50);
		Getworld().putinto(std::make_shared<Coolmask>(GetX(), GetY(), Getworld(), Getcoldtime()));
	}

}
void Cherryseed::OnClick() {
	if (Getworld().GetSun() >= 150) {
		Getworld().Setclicktime(Getworld().Getclicktime() + 1);
		Getworld().Setclicktype(Cherry_seed);
		Getworld().SetSun(Getworld().GetSun() - 150);
		Getworld().putinto(std::make_shared<Coolmask>(GetX(), GetY(), Getworld(), Getcoldtime()));
	}
}
void Coolmask::Update() {
	Setcoldtick(GetColdtick() + 1);
	if (GetColdtick() == Gettottime()) {
		shared_from_this()->Setlifestate(0);
	}
}
Pea::Pea(int x, int y, GameWorld& world) : GameObject(IMGID_PEA, x, y, LAYER_PROJECTILES, 28, 28, ANIMID_NO_ANIMATION, world) { Settype(PEA); };
Explosion::Explosion(int x, int y, GameWorld& world) : GameObject(IMGID_EXPLOSION, x, y, LAYER_PROJECTILES, 3*LAWN_GRID_WIDTH, 3*LAWN_GRID_HEIGHT, ANIMID_NO_ANIMATION, world) { Settype(EXPLOSION); };
void Pea::Update() {
	if (GetX() < WINDOW_WIDTH) {
		shared_from_this()->MoveTo(GetX() + 8, GetY());
	}
	else{
		Setlifestate(0);
	}
}

RegularZombie::RegularZombie(int x, int y,GameWorld& world) : GameObject(IMGID_REGULAR_ZOMBIE, x, y, LAYER_ZOMBIES, 20, 80, ANIMID_WALK_ANIM, world) { Settype(Zombies); SetHP(200); };
void RegularZombie::Update(){
	shared_from_this()->Determinelifestate(GetHP());
	int Speed = 1;
	int isCollide=Flower_seed;
	ObjectType plant = None;
	for (auto& object : Getworld().FindObject()) {
		isCollide = None;
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->GetX() < shared_from_this()->GetX()) && (object->Gettype() == PEA)) {
			isCollide = PEA;
		}
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->GetX() < shared_from_this()->GetX()) && (object->Gettype() == Plants)) {
			plant = Plants;
		}
		if (isCollide == PEA) {
			SetHP(GetHP() - 20);
			object->Setlifestate(0);
		}
	}
	if (plant == Plants) {
		if (isWalking(GetCurrentAnimation())) {
			PlayAnimation(ANIMID_EAT_ANIM);
		}
		Speed = 0;
	}
	if (plant == None) {
		if (isEating(GetCurrentAnimation())) {
			PlayAnimation(ANIMID_WALK_ANIM);
		}
	}



	shared_from_this()->MoveTo(GetX() - Speed, GetY());
}
void PoleZombie::Update() {
	shared_from_this()->Determinelifestate(GetHP());
	int Speed = 1;
	int isCollide = None;
	for (auto& object : Getworld().FindObject()) {
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->GetX() < shared_from_this()->GetX()) && (object->Gettype() == PEA)) {
			isCollide = PEA;
		}
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->GetX() < shared_from_this()->GetX()) && (object->Gettype() == Plants)) {
			isCollide = Plants;
		}
		if (isCollide == PEA) {
			SetHP(GetHP() - 20);
			object->Setlifestate(0);
		}
	}
	if (isCollide == Plants) {
		if (isWalking(GetCurrentAnimation())) {
			PlayAnimation(ANIMID_EAT_ANIM);
		}
		Speed = 0;
	}
	if (isCollide == None) {
		if (isEating(GetCurrentAnimation())) {
			PlayAnimation(ANIMID_WALK_ANIM);
		}
	}



	shared_from_this()->MoveTo(GetX() - Speed, GetY());
}
PoleZombie::PoleZombie(int x, int y, GameWorld& world) : GameObject(IMGID_POLE_VAULTING_ZOMBIE, x, y, LAYER_ZOMBIES, 20, 80, ANIMID_WALK_ANIM, world) { Settype(Zombies); SetHP(340); };

BucketZombie::BucketZombie(int x, int y, GameWorld& world) : GameObject(IMGID_BUCKET_HEAD_ZOMBIE, x, y, LAYER_ZOMBIES, 20, 80, ANIMID_WALK_ANIM, world) { Settype(Zombies); SetHP(1300); };
void BucketZombie::Update() {
	shared_from_this()->Determinelifestate(GetHP());
	int Speed = 1;
	int isCollide = Flower_seed;
	ObjectType plant = None;
	for (auto& object : Getworld().FindObject()) {
		isCollide = None;
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->GetX() < shared_from_this()->GetX()) && (object->Gettype() == PEA)) {
			isCollide = PEA;
		}
		if ((abs(object->GetX() - shared_from_this()->GetX()) < (object->GetWidth() + shared_from_this()->GetWidth()) / 2) && (abs(object->GetY() - shared_from_this()->GetY()) < (object->GetHeight() + shared_from_this()->GetHeight()) / 2) && (object->GetX() < shared_from_this()->GetX()) && (object->Gettype() == Plants)) {
			plant = Plants;
		}
		if (isCollide == PEA) {
			SetHP(GetHP() - 20);
			object->Setlifestate(0);
		}
	}
	if (plant == Plants) {
		if (isWalking(GetCurrentAnimation())) {
			PlayAnimation(ANIMID_EAT_ANIM);
		}
		Speed = 0;
	}
	if (plant == None) {
		if (isEating(GetCurrentAnimation())) {
			PlayAnimation(ANIMID_WALK_ANIM);
		}
	}

	shared_from_this()->MoveTo(GetX() - Speed, GetY());
	if (GetHP() <= 200) {
		if (isBucket()) {
			ChangeImage(IMGID_REGULAR_ZOMBIE);
			Setbucket(0);
		}
	}
}