#include <bits/stdc++.h>
#include <iostream>

using namespace std;
class SnakesandLadders
{
    unordered_map<int, int> snakes;
    unordered_map<int, int> ladders;
    unordered_map<int, string> player_name;
    int number_of_players;
    int *player_position;

    public:
    SnakesandLadders(int num_players)
    {
        if(num_players <= 0)
        {
            printf("Invalid number of players provided\n");
            return;
        }

        number_of_players = num_players;
        player_position = new int [number_of_players];

        for(int i = 0 ; i < number_of_players ; i++)
        {
            player_position[i] = 0;
        }
        return;
    }

    void assign_snakes(int start, int end)
    {
        if(start < 0 || start > 100 || end < 0 || end > 100)
        {
            return;
        }
        snakes[start] = end;
        return;
    }

    void assign_ladders(int start, int end)
    {
        if(start < 0 || start > 100 || end < 0 || end > 100)
        {
            return;
        }
        ladders[start] = end;
        return;
    }

    void assign_players(int player_index, string name_of_player)
    {
        if(player_index < 0)
        {
            return;
        }
        player_name[player_index] = name_of_player;
        return;
    }

    int get_player_position(int index)
    {
        if(index < 0 || index >= number_of_players)
        {
            cout<<"Invalid player index"<<endl;
            return -1;
        }

        return player_position[index];
    }

    int roll_dice()
    {
        int number = (rand() % 6);
        return number;
    }
    void set_player_position(int index, int position)
    {
        if(index < 0 || index >= number_of_players)
        {
            cout<<"Invalid player index"<<endl;
            return;
        }

        player_position[index] = position;
    }

    string fetch_player_name(int index)
    {
        if(index < 0 || index >= number_of_players)
        {
            cout<<"Invalid player index"<<endl;
            return "Invalid";
        }

        return player_name[index];
    }

    bool check_if_player_won(int position)
    {
        if(position == 100)
        {
            return true;
        }
        return false;
    }

    bool check_valid_position(int position)
    {
        if(position <=0 || position >100)
        {
            return false;
        }
        return true;
    }
    bool check_if_snake_present(int position)
    {
        if(snakes.find(position) == snakes.end())
        {
            return false;
        }

        return true;
    }
    bool check_if_ladder_present(int position)
    {
        if(ladders.find(position) == ladders.end())
        {
            return false;
        }
        return true;
    }

    int get_snake_destination(int start_position)
    {
        if(snakes.find(start_position) == snakes.end())
        {
            cout<<"Not a valid snake start position"<<endl;
            return -1;
        }

        return snakes[start_position];
    }
    int get_ladder_destination(int start_position)
    {
        if(ladders.find(start_position) == ladders.end())
        {
            cout<<"Not a valid ladder start position"<<endl;
            return -1;
        }

        return ladders[start_position];
    }
};

int main()
{
    int num_snakes, num_players, num_ladders;
    cout<<"Enter number of players"<<endl;
    cin>>num_players;

    SnakesandLadders board(num_players);
    
    cout<<"Enter player name for " <<num_players<< " players"<<endl;

    for(int i = 0 ; i < num_players ; i++)
    {
        string name;
        cin>>name;
        board.assign_players(i, name);
    }

    cout<<"Enter number of snakes"<<endl;
    cin>>num_snakes;

    while(num_snakes)
    {
        cout<<"Enter starting and ending position"<<endl;
        int start, end;
        cin>>start>>end;
        board.assign_snakes(start, end);
        num_snakes--;
    }

    cout<<"Enter number of ladders"<<endl;

    cin>>num_ladders;

    while(num_ladders)
    {
        cout<<"Enter starting and ending position"<<endl;
        int start, end;
        cin>>start>>end;
        board.assign_ladders(start, end);
        num_ladders--;
    }

    int current_player = 0;

    while(1)
    {
        int current_position = board.get_player_position(current_player);
        int dice_number = board.roll_dice();

        int new_position = current_position + dice_number;
        string current_player_name = board.fetch_player_name(current_player);

        if(!board.check_valid_position(new_position))
        {
            cout<<"Player "<<current_player_name<<" could not move because dice gave invalid result"<<endl;
            current_player = (current_player + 1)%num_players;
            continue;
        }

        if(board.check_if_snake_present(new_position))
        {
            new_position = board.get_snake_destination(new_position);

        }
        else if(board.check_if_ladder_present(new_position))
        {
            new_position = board.get_ladder_destination(new_position);
        }
        cout<<"Player "<<current_player_name<<" moved from "<<current_position<<" to new position "<<new_position<<endl;
        if(new_position == 100)
        {
            cout<<"Player "<<current_player_name<<" won"<<endl;
            break;
        }
        board.set_player_position(current_player, new_position);
        current_player = (current_player + 1)%num_players;
    }
}
