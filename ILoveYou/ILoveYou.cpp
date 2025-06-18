
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <ctime>
using namespace std;
enum class item {
    gun, ar_glasses, tth, jacket
};

string item_name[] = { "gun", "ar_glasses", "tth", "jacket"};

struct Portal {
    string name;
    int target;
    bool activiti_flag;
    bool visiblity_flag;

};
struct  Enemy {
    string name;
    bool alive_flag;
    vector<item> items;
    int health = 100;
    int damage;
    
};

class location {
public:
    string name;
    vector <Portal> portal;
    vector<item> items;
    vector<Enemy> enemy;
};

location room[4];


struct {
    int location;
    bool alive_flag = true;
    vector<item> items;
    int health = 150;
    int attack;
} player;

 




void attack_enemy() {
    srand(time(0));
    player.attack = 15 + rand() % 50;
    if (!room[player.location].enemy.empty()) {

        for (int i = 0; i < room[player.location].enemy.size(); i++) {

            room[player.location].enemy[i].damage = rand() % 50;

            if (room[player.location].enemy[i].alive_flag && player.health > 0 && room[player.location].enemy[i].health > 0) {

                cout << room[player.location].enemy[i].health << " <-enemy, player -> " << player.health << "\n";

                room[player.location].enemy[i].health -= player.attack;
                cout << "You attacked : " << "'" << room[player.location].enemy[i].name << "'" << " with " << player.attack << " damage" << "\n";
                player.health -= room[player.location].enemy[i].damage;
                cout << "You takes: " << room[player.location].enemy[i].damage << " damage" << "\n";
            }
            else
            {
                if (room[player.location].enemy[i].alive_flag && room[player.location].enemy[i].health <= 0) {
                    cout << "You killed: " << room[player.location].enemy[i].name << "\n";
                    cout << room[player.location].enemy[i].name <<" drop out " << item_name[(int)room[player.location].enemy[i].items[i]] << "\n";
                    room[player.location].items.push_back(room[player.location].enemy[i].items[i]);
                    room[player.location].enemy[i].items.erase(room[player.location].enemy[i].items.begin() + i);
                    room[player.location].enemy[i].alive_flag = false;
                    room[player.location].enemy.erase(room[player.location].enemy.begin() + i);
                }
                else if (room[player.location].enemy[i].alive_flag && player.health <= 0) {
                    cout << " You Died " << "\n";
                    player.alive_flag = false;
                    exit;
                }
                
            }
        }


    }
    
    else {
        cout << "No enemies around" << "\n"; 
        exit;
    }
}

int main() {
    srand(time(NULL));

   
    room[0].name = "Corp. alley";
    room[0].portal.push_back({ "Northside", 1, false, false });

    room[1].name = "Northside";
    room[1].portal.push_back({ "Corp. alley", 0, false, false });
    room[1].portal.push_back({ "Pacifika", 2, true, true });
    room[1].portal.push_back({ "Arrays", 3, true, true });
    room[1].enemy.push_back({"Cyberpsycho", true});
    room[1].enemy[0].items.push_back(item::tth);
    room[1].items.push_back(item::gun);
    room[1].items.push_back(item::ar_glasses);
    
    room[1].items.push_back(item::jacket);
  
    

    room[2].name = "Pacifika";
    room[2].portal.push_back({ "Northside", 1, true, false });
    room[2].portal.push_back({ "Arrays", 3, true, false });
    room[2].enemy.push_back({ "Cyberpsycho", true });
    room[2].enemy[0].items.push_back(item::tth);


    room[3].name = "Arrays";
    room[3].portal.push_back({ "Pacifika", 2, false, false });
    //room[3].enemy.push_back({ "Cyberpsycho", false });

    player.location = 1;

    string cmd;
    while (player.alive_flag) {

        std::cout << "your location " << room[player.location].name << "\n";
        std::cin >> cmd;

        if (cmd == "go") {

            bool answer_is_correct = false;
            string loc_to_go;
            int sz = room[player.location].portal.size();


            while (!answer_is_correct)
            {
                
                for (int i = 0; i < sz; i++) {
                    if (room[player.location].portal[i].visiblity_flag) {
                        cout << "type Location name to go"  << room[player.location].portal[i].name << "\t" << (room[player.location].portal[i].activiti_flag ? "unlocked\n" : "locked\n");
                        exit;
                    }
;               }

                cout << "else type Exit " << "\n";
                std::cin >> loc_to_go;
                if (loc_to_go == "Exit") {

                    answer_is_correct = true;
                    exit;
                }
                else {

                    for (int i = 0; i < sz; i++) {
                        if (room[player.location].portal[i].name == loc_to_go) {
                            player.location = room[player.location].portal[i].target;
                            answer_is_correct = true;

                            break;
                        }

                    }
                }
            }

                
        }
        if (cmd == "use") {



            string item_to_use;
            cin >> item_to_use;

            for (int i = 0; i < player.items.size(); i++) {
                if (item_name[(int)player.items[i]] == item_to_use) {

                    if (item_to_use == "tth") {

                                room[player.location].portal[0].activiti_flag = true;
                                cout << " You have access to: " << room[player.location].portal[0].name << "\n";
                            
                    }


                    if (item_to_use == "ar_glasses") {

                        int sz = room[player.location].portal.size(); // исправить сз, не то берет для расчета полюбому!

                        for (int i = 0; i < sz; i++) {
                            room[player.location].portal[i].visiblity_flag = true;
                            cout << " Looks like appears new door(s)" << "\n";
                        }
                    }

                    if (item_to_use == "jacket") {
                        player.health += 100;
                       cout << "Your health has been increased." << "\n";
                    }

                    if (item_to_use == "gun") {
                        //cout << enemy.damage << "\n";
                        
                                attack_enemy();
                        
                    }
                }

            }
        }

       if (cmd == "list") {
           if (room[player.location].items.empty()) {
               cout << "There are no items here.\n";
           }
           else {
               for (int i = 0; i < room[player.location].items.size(); i++) {
    
                   cout << item_name[(int)room[player.location].items[i]] << "\n";
               }
           }
       }
    
       if (cmd == "invent") {
    
           if (player.items.empty()) {
               cout << "There are no items here.\n";
           }
           else {
               for (int i = 0; i < player.items.size(); i++) {
                   cout << item_name[(int)player.items[i]] << "\n";
               }
           }
       }
       if (cmd == "drop") {
           if (player.items.empty()) {
               cout << "There are no items to pick up here.\n";
           }
           else {
               for (int i = 0; i < player.items.size(); i++) {
                   cout << item_name[(int)player.items[i]] << "\n";
               }
           }

           string item_to_drop;
           cin >> item_to_drop;

           for (int i = 0; i < player.items.size(); i++) {
               if (item_name[(int)player.items[i]] == item_to_drop) {
                   room[player.location].items.push_back(player.items[i]);
                   cout << "You drop out " << item_name[(int)player.items[i]] << "\n";
                   player.items.erase(player.items.begin() + i);
               }
           }
       }

        if (cmd == "pick") {
            if (room[player.location].items.empty()) {
                cout << "There are no items to pick up here.\n";
            }
            else {
                for (int i = 0; i < room[player.location].items.size(); i++) {
                    cout << item_name[(int)room[player.location].items[i]] << "\n";
                }
            }
            string item_to_pick;
            cin >> item_to_pick;
   
            for (int i = 0; i < room[player.location].items.size(); i++) {
                if (item_name[(int)room[player.location].items[i]] == item_to_pick) {
                    player.items.push_back(room[player.location].items[i]);
                    cout << "You picked up " << item_name[(int)room[player.location].items[i]] << "\n";
                    room[player.location].items.erase(room[player.location].items.begin() + i);
                }
            }
   
   
        }
        if (cmd == "exit") {
            break;
        }
    }

}




























/*if (cmd == "pick") {
    int sz = room[player.location].portal.size();
    for (int i = 0; i < sz; i++) {
        cout << "type "     << " to pick " << item_name[(int)room[player.location].items[i]] << "\n";
    }

    std::cin >> cmd;
    if (cmd == )


}*/

/*if (cmd == "pick") {
    int sz = room[player.location].items.size();
    if (sz == 0) {
        cout << "There are no items to pick up here.\n";
        continue;
    }
    for (int i = 0; i < sz; i++) {
        cout << "Type " << i << " to pick " << item_name[(int)room[player.location].items[i]] << "\n";
    }

    int item_index;
    std::cin >> item_index;


    if (item_index >= 0 && item_index < sz) {
        player.items.push_back(room[player.location].items[item_index]);
        room[player.location].items.erase(room[player.location].items.begin() + item_index);
        cout << "You picked up " << item_name[(int)player.items.back()] << "\n";
    }
    else {
        cout << "Incorrect input\n";
    }
}

}*/

/*if (cmd == "pick") {
    if (room[player.location].items.empty()) {
        cout << "There are no items to pick up here.\n";
    }
    else {
        cout << "Available items to pick:\n";
        for (auto& it : room[player.location].items) {
            cout << "- " << item_name[(int)it] << "\n";
        }

        string item_to_pick;
        cin >> item_to_pick;

        for (int i = 0; i < room[player.location].items.size(); i++) {
            if (item_name[(int)room[player.location].items[i]] == item_to_pick) {
                player.items.push_back(room[player.location].items[i]);
                room[player.location].items.erase(room[player.location].items.begin() + i);
                cout << "You picked up " << item_to_pick << "\n";
            }
        }
        cout << "Item not found.\n";
    }
}*/
