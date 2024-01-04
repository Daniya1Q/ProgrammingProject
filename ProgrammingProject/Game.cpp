#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<limits>


using namespace std;

int Cchoice = 0; //role choice
int qchoice = 0;//quest chice
int qcount = 0;//quest counter 
int randcount = 0;//quest counter


struct Player
{
    string name;
    string role;
    int health;
    int xp;
    int level;
    string activity;
    int h_full = 100;
    string loot[4];//inventory
}player;

struct Quest
{
    string info; //dsc
    int Difficulty;
    int XPreward; //
    string Treasure;//artifact
    string enemy;
};

void buildCharacter();//make
bool verifyRole(int& Cchoice);//roles select
void view_character_information();
void menu();
void decidechoice();
bool reviewchoice(int& primarychoice);//check
void beginmission();
bool questchoice(int& qchoice);
void combat(Quest& quest);//hit = attack 

//q_intensity -- quest difficulty
bool attackchoice(int& attack_choice);
void Handle_Attack_Choice(int attack_choice, int& playerstrike);
void Perform_Enemy_Attack(int& enemyhit, int& q_intensity, string& enemy, int& e_health, bool& e_escaped, int Max_enemy_health);
void Story_line();
void Level_Up(Quest& quest);


int main()
{

    srand(time(0));


    buildCharacter();

    while (1)
    {
        Story_line();
        view_character_information();
        menu();
        decidechoice();
    }

    cout << "\n\n";
    system("pause");

    return 0;
}

void buildCharacter()
{
    cout << "\t\t-----------Welcome to Battle Realms-----------" << endl;
    cout << "\t\t\n\nEnter your Name: ";
    getline(cin, player.name);

    while (true) {
        cout << "\n\nChoose Your Role: ";
        cout << "\n1.Sage\n2.Phoenix\n3.omen";
        cout << "\n\nEnter Your Choice: ";
        cin >> Cchoice;

        if (!verifyRole(Cchoice)) {
            cout << "Invalid input\n";
            continue; // Restart the loop to prompt for a valid input
        }
        else {
            break; // Exit the loop if the input is valid
        }
    }




    switch (Cchoice)
    {

    case 1:
        player.role = "Sage";
        break;
    case 2:
        player.role = "Phoenix";
        break;
    case 3:
        player.role = "omen";
        break;
    }



    player.xp = 0;
    player.health = player.h_full;//max =100
    player.level = 1;
    player.activity = "\t\t--------Activity---------\n";



}



bool verifyRole(int& Cchoice)
{
    if (cin.fail() || Cchoice < 1 || Cchoice > 3)
    {
        cin.clear();

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

        cout << "\nInvalid input. Please enter a number between 1 and 3." << endl;

        return false;
    }

    return true;
}

void view_character_information()
{

    cout << "\t\t|Character Info |\n";


    cout << "\n\n1. Name: " << player.name;
    cout << "\n2. roles: " << player.role;
    cout << "\n3. Experience: " << player.xp;
    cout << "\n4. Health: " << player.health;
    cout << "\n5. Level: " << player.level;

    cout << endl << endl;


    cout << "\t\t\n\n" << player.activity;



    cout << "\t\t\n| Loot |\n";


    for (int i = 0; i < 5; ++i)
    {
        cout << endl;
        cout << i + 1 << ". " << player.loot[i];
    }
    cout << endl << endl;

}

void menu()
{

    cout << "  Menu |\n";
    cout << "\n\n1.Begin Adventure(mission).";
    cout << "\n2.exit the Game.";


}

void decidechoice()
{
    int primarychoice;//main  menu choice

    do
    {
        cout << "\n\nEnter Your Choice: ";
        cin >> primarychoice;

    } while (!reviewchoice(primarychoice));

    switch (primarychoice)
    {
    case 1:
        beginmission();//go on mission
        break;
    case 2:
        cout << "\n\nSee you next time";
        exit(0);
        break;
    }

}

bool reviewchoice(int& primarychoice)
{
    if (cin.fail() || primarychoice < 1 || primarychoice > 2)
    {
        cin.clear();
        cin.ignore();  // Discard invalid input
        cout << "\nInvalid input. Please enter a number between 1 and 3." << endl;
        return false;
    }

    return true;
}

void beginmission()//go on advanture /quest
{

    Quest sage_quests[] = {
                       {"Sage's Wisdom ", 1 , 25 , "Book of wisdom","Sauron"},

                       {"Ancient scrolls", 2 , 50 , "Elixir of clarity","Saruman"},



    };
    Quest phoenix_quests[] = {
                      {"Flames of Renewal", 1 , 25 , "Eternal flame","Nicromancer"},

                      {"Guardian of skies", 2 , 50 , "wings of eternal gaurdian ","Azog"},



    };
    Quest omen_quests[] = {
                     {"Veil of Visions", 1 , 25 , "Whispering ORB","Shadow"},

                     {"Echoes of destiny", 2 , 50 , "seer crystal lens","Nazgul"},


    };

    if (Cchoice == 1)
    {

        for (int i = 0; i < sizeof(sage_quests) / sizeof(sage_quests[i]); ++i)
        {
            cout << "\n" << i + 1 << ". " << sage_quests[i].info << ", (Difficulty: " << sage_quests[i].Difficulty << ")";
        }

    }

    else if (Cchoice == 2)
    {

        for (int i = 0; i < sizeof(phoenix_quests) / sizeof(phoenix_quests[i]); ++i)
        {
            cout << "\n" << i + 1 << ". " << phoenix_quests[i].info << ", (Difficulty: " << phoenix_quests[i].Difficulty << ")";
        }
    }

    else
    {
        for (int i = 0; i < sizeof(omen_quests) / sizeof(omen_quests[i]); ++i)
        {
            cout << "\n" << i + 1 << ". " << omen_quests[i].info << ", (Difficulty: " << omen_quests[i].Difficulty << ")";
        }
    }


    do {
        cout << "\n\nEnter your choice: ";
        cin >> qchoice;

    } while (!questchoice(qchoice));

    Quest Selected_Quest;


    if (Cchoice == 1)
    {
        Selected_Quest = sage_quests[qchoice - 1];
    }
    else if (Cchoice == 2)
    {
        Selected_Quest = phoenix_quests[qchoice - 1];
    }
    else if (Cchoice == 3)
    {
        Selected_Quest = omen_quests[qchoice - 1];
    }

    combat(Selected_Quest);


}

bool questchoice(int& qchoice)
{

    if (cin.fail() || qchoice < 1 || qchoice > 3)
    {
        cin.clear();  // Clear eror flag
        cin.ignore();  // Discard input
        cout << "\nInvalid input. Please enter a number between 1 and 3." << endl;
        return false;
    }

    return true;
}

void combat(Quest& quest)
{
    bool Battle_result = false;

    int e_health = 100 * quest.Difficulty;

    int Max_enemy_health = e_health;

    int playerstrike = 0;

    int enemyhit = 0;

    int randcount = 0;

    bool e_escaped = false;

    cout << "\n\n-----Combat Begins-----";

    do
    {
        cout << "\n------------------------";
        cout << "\n\n" << player.name << " Health: " << player.health;
        cout << "\n" << quest.enemy << "'s Health: " << e_health;
        cout << "\n------------------------";

        cout << endl << endl;


        cout << "\n\n-----" << player.name << "'s Turn-----";

        cout << "\n\n\n------Choose Your Attack----- ";
        cout << "\n\n1.Intensive assault";
        cout << "\n2.Minor Strike";
        cout << "\n3.Retreat from battle";

        int attack_choice;

        do
        {
            cout << "\n\nEnter Your Choice: ";
            cin >> attack_choice;

        } while (!attackchoice(attack_choice));

        Handle_Attack_Choice(attack_choice, playerstrike);

        if (attack_choice != '3')
        {
            e_health -= playerstrike;

            cout << "\n\nYou imposed damage of " << playerstrike << " on " << quest.enemy;

            cout << "\n\n-----" << quest.enemy << "'s Turn";



            Perform_Enemy_Attack(enemyhit, quest.Difficulty, quest.enemy, e_health, e_escaped, Max_enemy_health);

            if (e_escaped == true)
            {
                break;
            }

            else
            {
                player.health -= enemyhit;

                cout << "\n\nThe " << quest.enemy << " Imposed a Damage of " << enemyhit << " on You.";


            }

        }

    } while (player.health > 0 && e_health > 0);

    if (e_health <= 0 || e_escaped == true)
    {
        cout << "\n\nVictory!";
        player.xp += quest.XPreward;

        if (player.xp >= 100)
        {
            Level_Up(quest);
        }

        player.loot[qchoice - 1] = quest.Treasure;
        cout << "\t\t\n\nReward item " << player.loot[qchoice - 1];
        player.activity += "\t\t\n\nSuccess " + quest.info;
        qcount++;
        randcount = 0;
        player.health = player.h_full;
        cout << endl;

    }

    else
    {
        cout << "\t\t\n\nDefeat";

        player.xp -= 10 * quest.Difficulty;

        if (player.xp < 0)
        {
            player.xp = 0;
        }

        player.activity += "\t\t\nLOST: " + quest.info;
        randcount = 0;
        qcount++;
        player.health = player.h_full;
    }
}

bool attackchoice(int& attack_choice)
{
    if (cin.fail() || attack_choice < 1 || attack_choice > 3)
    {
        cin.clear();  // Clear error flag
        cin.ignore();  // Discard invalid input
        cout << "\nInvalid input. Please enter a number between 1 and 3." << endl;
        return false;
    }

    return true;
}

void Handle_Attack_Choice(int attack_choice, int& playerstrike)
{

    switch (attack_choice)
    {
    case 1:
        playerstrike = rand() % (player.level * 50) + 1;
        break;

    case 2:
        playerstrike = rand() % (player.level * 30) + 1;
        break;

    case 3:

        if (player.health < (50 * player.h_full) / 100)            //Player Health less the 50%
        {
            cout << "\t\t\n\nYou were not Lucky to Escape";
            cout << "\t\t\n\nGame Over!";
            exit(0);
        }
        else
        {
            cout << "\n\nYou successfully escaped from the Enemy";

            if (player.xp > 50) {

                player.xp -= 50;
                cout << "\n\nYou Lost 30 Experience points.";
            }
            else if (player.xp < 50) {

                player.xp -= 0;
                cout << "\n\nYou lost All Experience points.";
            }
            player.health = player.h_full;
            menu();
            decidechoice();
            break;
        }
        break;

    default:

        cout << "\nChoose a valid option";
    }
}

void Perform_Enemy_Attack(int& enemyhit, int& q_intensity, string& enemy, int& e_health, bool& e_escaped, int Max_enemy_health)
{
    int enemy_attack_choice = rand() % 3 + 1;

    if (enemy_attack_choice == 1)
    {
        enemyhit = rand() % (q_intensity * 30) + 1;
    }
    else if (enemy_attack_choice == 2)
    {
        enemyhit = rand() % (q_intensity * 20) + 1;
    }

    else if (enemy_attack_choice == 3)
    {
        if (e_health <= (20 * Max_enemy_health) / (100))
        {
            cout << "\n\n" << enemy << " fled from the battle ground.";
            e_escaped = true;
            return;
        }


    }

}

void Level_Up(Quest& quest)
{
    player.level++;
    player.xp = 0;
    player.h_full += 100;
}



void Story_line()
{
    if (qcount == 0)
    {
        if (player.role == "Sage")
        {

            cout << "\n\n I am Sage, keeper of ancient knowledge and guardian of the elements.";


            cout << "The Sage seeks an apprentice to impart ancient wisdom and knowledge. Embark on a journey to distant lands, overcome trials, and prove your worth to learn the secrets of the ages";
            cout << endl;


            system("pause");
        }
        else if (player.role == "Phoenix")
        {

            cout << "\n\n I am Phoenix, born of fire and forged in battle. Ember Ridge, where the flames dance in eternal glory, is my domain..";


            cout << " The Phoenix, an embodiment of rebirth and flame, has lost its eternal fire. Venture into the heart of volcanic realms, retrieve the sacred embers, and restore the Phoenix to its glorious form.";
            cout << endl;
            system("pause");
        }
        else if (player.role == "omen")
        {

            cout << "\n\nI am Omen, bearer of arcane gifts and harbinger of unseen truths..";


            cout << "Omen's visions are obscured by a mystical veil. Travel through dreamscapes and ethereal realms, facing surreal challenges to lift the veil obstructing Omen's visions. ";
            cout << endl;
            system("pause");
        }
    }



}
