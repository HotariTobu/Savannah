#pragma once
#include"creatures.hpp"
#include<random>

//動物クラス
class Animal : public Creatures {
private:
    double distance = 100.0;
protected:
    Vec2 distination_coord = Vec2(window_width / 2.0, window_height / 2.0);
    double maxSatiety = one_year * 2;
    double satiety = maxSatiety;
public:
    //新しい座標の設定
    void move();
    //目的地にいるかどうかの判定
    bool isDistination();
    //目的地をランダムに設定
    void setRandomDistination();
    //目的地の設定
    void setDistination(const Vec2 new_coord);
    //目的地との距離
    void calculateDistinationDistance(const Vec2& distination_coord);
    //生命活動を管理
    void lifeActivity(const double mi_spf, bool& is_die);
    //繁殖期かどうかの判定
    bool isBreedingSeason();
};

//動物クラス実装
void Animal::move() {
    if (distance == 0.0) {
        setRandomDistination();
    }
    calculateDistinationDistance(distination_coord);
    Vec2 const coord = getCoord();
    const double spf = getSpf();
    const  Vec2 dCoord = Vec2((distination_coord.x - coord.x) / distance*spf*60, (distination_coord.y - coord.y) / distance*spf*60);
    setCoord (Vec2(coord.x + dCoord.x, coord.y + dCoord.y));
    Draw::circleDraw(coord, herbivoreE);
}
bool Animal::isDistination() {
    const Vec2 coord = getCoord();
    return ((coord.x - distination_coord.x) < 1.0 && (coord.y - distination_coord.y) < 1.0);
}
void Animal::calculateDistinationDistance(const Vec2& distination_coord) {
    const Vec2 coord = getCoord();
    distance = std::sqrt(std::pow(coord.x - distination_coord.x, 2) + std::pow(coord.y - distination_coord.y, 2));
}
void Animal::setRandomDistination() {
    constexpr int MIN = 0;
    constexpr int wMAX = window_width;
    constexpr int hMAX = window_height;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> wDistr(MIN, wMAX);
    std::uniform_int_distribution<int> hDistr(MIN, hMAX);
    distination_coord.x = wDistr(eng);
    distination_coord.y = hDistr(eng);
    calculateDistinationDistance(distination_coord);
}
void Animal::setDistination(const Vec2 new_coord) {
    distination_coord = new_coord;
    calculateDistinationDistance(distination_coord);
}
void Animal::lifeActivity(const double mi_spf, bool& is_die) {
    setSpf(mi_spf);
    getOld();
    satiety -= getSpf();
    is_die = (getAge() > one_year * lifespan||satiety<0);
}
bool Animal::isBreedingSeason() {
    return (satiety > maxSatiety * 3.0 / 4.0);
}
