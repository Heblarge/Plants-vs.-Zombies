#include "GameWorld.hpp"
#include "GameObject.hpp"



GameWorld::GameWorld():objects(),m_tick(0) {}



GameWorld::~GameWorld() {}

int GameWorld::Gettick(){ return m_tick; } 

void GameWorld::Init() {
  // YOUR CODE HERE

	objects.emplace_back(std::make_shared<Background>(*shared_from_this()));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			objects.emplace_back(std::make_shared<Plantingspot>(FIRST_COL_CENTER+j*LAWN_GRID_WIDTH,FIRST_ROW_CENTER+i*LAWN_GRID_HEIGHT,*shared_from_this()));
		}
	}
	objects.emplace_back(std::make_shared<Flowerseed>(*shared_from_this()));
	objects.emplace_back(std::make_shared<Peashooterseed>(*shared_from_this()));
	objects.emplace_back(std::make_shared<Repeaterseed>(*shared_from_this()));
	objects.emplace_back(std::make_shared<Wallnutseed>(*shared_from_this()));
	objects.emplace_back(std::make_shared<Cherryseed>(*shared_from_this()));
	objects.emplace_back(std::make_shared<Shovel>(*shared_from_this()));
}
bool GameWorld::isZombie(int y) {
	for (auto& object : objects) {
		if (object->Gettype() == Zombies&&object->isAlive()) {
			if (object->GetY() == y) {
				return true;
			}
		}
	}
	return false;
}
LevelStatus GameWorld::Update() {
  // YOUR CODE HERE
	m_tick++;
	int P1 = 20;
	int P2 = 2 * MAX(GetWave() - 8, 0);
	int P3 = 3 * MAX(GetWave(), 0);
	int sum = P1 + P2 + P3;
	for (int i = 0; i < (15 + GetWave()); i++) {

	}
	if (m_tick % 300 == 180) {

		objects.emplace_back(std::make_shared<Sun>(randInt(75, WINDOW_WIDTH - 75), WINDOW_HEIGHT - 1, *shared_from_this(),1));
	}
	
	if (m_tick == Lastwave_tick) {
		SetWave(GetWave() + 1);
		//3. determine the zombie type
		int P1 = 20;
		int P2 = 2 * std::max((GetWave() - 8), 0);
		int P3 = 3 * std::max((GetWave() - 15), 0);
		int sum = P1 + P2 + P3;
		for (int i = 0; i < (15 + GetWave()) / 10; i++) {
			int p = randInt(1, sum);
			int x = randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1);
			int y = randInt(0, 4) * LAWN_GRID_HEIGHT + FIRST_ROW_CENTER;
			if (p <= P1)
				objects.emplace_back(std::make_shared<RegularZombie>(x,y,*shared_from_this()));
			else if (p <= P1 + P2)
				objects.emplace_back(std::make_shared<PoleZombie>(x,y,*shared_from_this()));
			else
				objects.emplace_back(std::make_shared<BucketZombie>(x,y,*shared_from_this()));
		}
		Lastwave_tick = Lastwave_tick + std::max(150, 600 - 20 * GetWave());
	}
  for (auto& object : objects) object->Update();
  for (auto& object : objects){
	  if (object->GetX() < 0) { return LevelStatus::LOSING; };
  }
  objects.remove_if([](auto& object)
	  { return !(object->isAlive()); });
  return LevelStatus::ONGOING;

}

void GameWorld::CleanUp() {
	objects.clear();
  // YOUR CODE HERE
}

