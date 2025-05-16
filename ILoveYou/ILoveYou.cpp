
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

enum class item {
    gun, tommygun, cannon
};

string item_name[] = { "gun","tommygun","cannon" };

struct Portal {
    string name;
    int target;


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

} player;

//
//dfdfdfdsfsdfsfs


int main() {
    room[0].name = "arasaka tower";
    room[0].portal.push_back({ "Northside", 1 });

    room[1].name = "Northside";
    room[1].portal.push_back({ "arasaka tower", 0 });
    room[1].portal.push_back({ "Pacifika", 2 });
    room[1].items.push_back(item::cannon);
    room[1].items.push_back(item::gun);

    room[2].name = "Pacifika";
    room[2].portal.push_back({ "Northside", 1 });
    room[2].portal.push_back({ "Arrays", 3 });

    room[3].name = "Arrays";
    room[3].portal.push_back({"Pacifika", 2});


    player.location = 1;

    string cmd;    
    while (true) {

        std::cout << "your location " << room[player.location].name << "\n";
        std::cin >> cmd;

        if (cmd == "go") {

            bool answer_is_correct = false;
            int dir;
            int sz = room[player.location].portal.size();

           
            while (!answer_is_correct)
            {
                for (int i = 0; i < sz; i++) {
                    cout << "type " << i << " to go " << room[player.location].portal[i].name << "\n";
                }             

                std::cin >> dir;

                if (dir >= 0 && dir < sz) {
                    player.location = room[player.location].portal[dir].target;
                    answer_is_correct = true;
                }
                else
                {
                    cout << "incorrect input\n";
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
