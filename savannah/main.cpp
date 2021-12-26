#include"init.hpp"
#include"actor.hpp"
#include<random>
#include<vector>
#include <chrono>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    DxLib::SetOutApplicationLogValidFlag(FALSE);
    DxLib::ChangeWindowMode(TRUE);
    DxLib::SetGraphMode(window_width, window_height, 32);
    DxLib::SetMainWindowText("Sample");
    if (DxLib::DxLib_Init() == -1) return -1;
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    Main();
    return DxLib::DxLib_End();
}

void Main() {
    //配列の確保
    std::vector<Herbivore> herbivore;
    std::vector<Plant> plant;
    //時間
    std::chrono::system_clock::time_point  old_time, new_time;
    //ランダム
    std::random_device rd;
    std::mt19937 eng(rd());
    //死亡判定
    bool plant_is_die,plant_is_breed,herbivore_is_die;
    //確率
    std::bernoulli_distribution uid(0.01);
    //時間
    new_time = std::chrono::system_clock::now();
    //植物生成
    plant.emplace_back();
    while (System::Update()) {
        for (int j = 0; j < 1; ++j) {
            //1フレームあたりの時間計測
            old_time = new_time;
            new_time = std::chrono::system_clock::now();
            //ランダムで草食動物生成
            if (uid(eng)) herbivore.emplace_back();
            //植物それぞれの生命活動
            for (size_t i = 0; i < plant.size();) {
                plant[i].lifeActivity(double(std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time).count()), plant_is_die,plant_is_breed);
                if (plant_is_die) {
                    plant.erase(plant.begin() + i);
                }
                else {
                    i++;
                }
            }
            //草食動物それぞれの行動
            for (size_t i = 0; i < herbivore.size();) {
                auto& h = herbivore[i];
                h.lifeActivity(double(std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time).count()), herbivore_is_die);
                if (herbivore_is_die) {
                    herbivore.erase(herbivore.begin() + i);
                }
                else {
                    h.behavior();
                    i++;
                }
            }

        }

    }
}