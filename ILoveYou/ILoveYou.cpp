﻿
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

enum class item {
    gun, tommygun, cannon, ar_glasses, tth
};

string item_name[] = { "gun","tommygun","cannon","ar_glasses", "tth"};

struct Portal {
    string name;
    int target;
    bool activiti_flag;
    bool visiblity_flag;

};

class location {
public:
    string name;
    vector <Portal> portal;
    vector<item> items;
};

location room[4];
struct {
    int location;
    vector<item> items;
    int health;
} player;


int main() {
    room[0].name = "Corp. alley";
    room[0].portal.push_back({ "Northside", 1, false, false });

    room[1].name = "Northside";
    room[1].portal.push_back({ "Corp. alley", 0, false, false });
    room[1].portal.push_back({ "Pacifika", 2, true, true });
    room[1].portal.push_back({ "Arrays", 3, true, true });
    room[1].items.push_back(item::cannon);
    room[1].items.push_back(item::gun); 
    room[1].items.push_back(item::ar_glasses);
    room[1].items.push_back(item::tth);



    room[2].name = "Pacifika";
    room[2].portal.push_back({ "Northside", 1, true, false });
    room[2].portal.push_back({ "Arrays", 3, true, false });

    room[3].name = "Arrays";
    room[3].portal.push_back({ "Pacifika", 2, false, false });


    player.location = 1;

    string cmd;
    while (true) {

        std::cout << "your location " << room[player.location].name << "\n";
        std::cin >> cmd;

        if (cmd == "go") {

            bool answer_is_correct = false;
            int dir;
            int sz = room[player.location].portal.size();


            /*while (!answer_is_correct)
            {*/
                for (int i = 0; i < sz; i++) {
                    if (room[player.location].portal[i].visiblity_flag) {
                    cout << "type " << i << " to go " << room[player.location].portal[i].name << "\t" << (room[player.location].portal[i].activiti_flag ? "unlocked\n" : "locked\n");
                    }
                }

                std::cin >> dir;
                    
                if (dir >= 0 && dir < sz) {
                    player.location = room[player.location].portal[dir].target;
                    answer_is_correct = true;
                }
                else
                {
                    cout << "incorrect input \n";
                    /*cin.ignore(10000, '\n');
                    cin.clear();*/
                    break;
                }
            //}

        }
        if (cmd == "use") {

            

            string item_to_use;
            cin >> item_to_use;

            if (item_to_use == "tth") {
                int sz = room[player.location].portal.size(); // исправить сз, не то берет для расчета полюбому!

                for (int i = 0; i < room[player.location].portal.size(); i++) {

                    if (room[player.location].portal[i].name == "Corp. alley") {

                        room[player.location].portal[i].activiti_flag = true;
                        cout << " You have access to: " << room[player.location].portal[i].name << "\n";
                    }
                }
            }




            if (item_to_use == "ar_glasses") {

                int sz = room[player.location].portal.size(); // исправить сз, не то берет для расчета полюбому!

                for (int i = 0; i < sz; i++) {
                    room[player.location].portal[i].visiblity_flag = true;
                    cout << " Looks like appears new door(s)" << "\n";
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
