
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

enum class item {
    gun, tommygun, cannon
};

string item_name[] = { "gun","tommygun","cannon" };

class location {
public:
    string name;
    vector<int> portal;
    vector<item> items;
};

location room[4];
struct {
    int location;
    vector<item> items;
} player;




int main()
{
    room[0].name = "arasaka tower";
    room[0].portal.push_back(1);

    room[1].name = "Northside";
    room[1].portal.push_back(0);
    room[1].portal.push_back(2);
    room[1].items.push_back(item::cannon);
    room[1].items.push_back(item::gun);

    room[2].name = "Pacifika";
    room[2].portal.push_back(1);
    room[2].portal.push_back(3);

    room[3].name = "Arrays";
    room[3].portal.push_back(2);


    player.location = 1;

    string cmd;
    while (true) {

        std::cout << "your location " << room[player.location].name << "\n";
        std::cin >> cmd;

        if (cmd == "go") {

            bool answer_is_correct = false;

            while (!answer_is_correct)
            {

                int sz = room[player.location].portal.size();
                for (int i = 0; i < sz; i++) {
                    cout << "type " << i << " to go " << room[room[player.location].portal[i]].name << "\n";
                }

                int dir;
                std::cin >> dir;

                if (dir >= 0 && dir < sz) {
                    player.location = room[player.location].portal[dir];
                    answer_is_correct = true;
                }
                else
                {
                    cout << "incorrect input\n";

                }
            }
        }

        if (cmd == "list") {
            int sz = room[player.location].items.size();
            for (int i = 0; i < sz; i++) {
                cout << item_name[(int)room[player.location].items[i]] << "\n";
            }
        }

        if (cmd == "invent") {
            int sz = player.items.size();
            for (int i = 0; i < sz; i++) {
                cout << item_name[(int)player.items[i]] << "\n";
            }
        }

        //if (cmd == "d") {

        //int sz = room[player.location].items.size();
        /*for (int i = 0; i < sz; i++) {
            cout << room[i].items << "\n";

        }

         }*/




        if (cmd == "pick") {
            int sz = room[player.location].portal.size();
            for (int i = 0; i < sz; i++) {
                cout << "type " << i << " to pick " << item_name[(int)room[player.location].items[i]] << "\n";
            }

            std::cin >> cmd;

            pick_by_name(cmd);//ffegegrrrg
            cout << "done";
            //player.items.emplace_back(room[player.location].items[i]);
            //player.items.push_back(item::);
            //room[player.location].items.erase(room[player.location].items.begin() + i);


        }

    }
}
