#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <limits>
#include <random>
#include <cmath>

/* this program simulates a volleyball player's journey to greatness!
this program is entirely text based, and it utilizes random numbers to determine interactions on the court. enjoy :) */

void shortdelay() { // function used to delay text appearance; for cosmetic purposes
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
}

void longdelay() { // same purpose as shortdelay, but delays code execution for longer
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

class Player { // the Player class holds the attributes of the digital volleyball players
    private:
        std::string name, position;
        int gamesPlayed, kills, blocks, digs, aces;
    public:
        // setter functions; changes object attributes
        void setName(std::string n) {
            name = n;
            std::cout << "Set player name to " << n << ".\n";
            longdelay();
        }
        void setPosition(int p) {
            switch (p) {
                case 1:
                    position = "Setter";
                    break;
                case 2:
                    position = "Outside Hitter";
                    break;
                case 3:
                    position = "Middle Blocker";
                    break;
                case 4:
                    position = "Opposite Hitter";
                    break;
                case 5:
                    position = "Libero";
                    break;
                case 6:
                    position = "Defensive Specialist";
                    break;
            }
            std::cout << "\n" << name << " now has the position: " << position << ".\n";
            longdelay();
        }
        void setGamesPlayed(int g) {
            gamesPlayed = g;
        }
        void setKills(int k) {
            kills = k;
        }
        void setBlocks(int b) {
            blocks = b;
        }
        void setDigs(int d) {
            digs = d;
        }
        void setAces(int a) {
            aces = a;
        }
        
        // getter functions; retrieves object attributes
        std::string getName() {
            return name;
        }
        int getGamesPlayed() {
            return gamesPlayed;
        }
        int getKills() {
            return kills;
        }
        int getBlocks() {
            return blocks;
        }
        int getDigs() {
            return digs;
        }
        int getAces() {
            return aces;
        }
        
        // player constructor; parameters are the player's attributes
        Player(std::string n, int g = 0, int k = 0, int b = 0, int d = 0, int a = 0) {
            name = n;
            gamesPlayed = g;
            kills = k;
            blocks = b;
            digs = d;
            aces = a;
            std::cout << "Player " << n << " registered.\n";
            longdelay();
        }
};

class Team { // the team class holds a roster (std::vector<Player>) of players
    private:
        std::vector<Player> roster;
        std::string name;
        int wins;
    public:
        // setter functions
        void setName(std::string n) {
            name = n;
            std::cout << "Updated team name to " << n << ".\n";
            longdelay();
        }
        void setWins(int w) {
            wins = w;
            std::cout << "Updated " << name << " wins to " << w << ".\n";
            longdelay();
        }

        // getter functions
        std::string getName() {
            return name;
        }
        int getWins() {
            return wins;
        }
        std::vector<Player>& getRoster() {
            return roster;
        }

        void addToRoster(Player& p) { // adds a player object to the team's roster
            roster.push_back(p);
            std::cout << "Added player " << p.getName() << " to " << name << ".\n";
            longdelay();
        }

        Team() : name("Unnamed Team"), wins(0) {} // default team constructor for when teams are declared without a name
        Team(std::string n, int w = 0) { // team constructor
            name = n;
            wins = w;
            std::cout << "Registered " << n << " with " << w << " wins.\n";
            longdelay();
        }
};

class Game { // the game class allows a match to start and uses team and player objects
    private:
        static inline std::string volleyballCourt = "-------------------\n|  4  |  3  |  2  |\n-------------------\n|  5  |  6  |  1  |\n-------------------\n"; // a volleyball court with labeled positions
        Team homeTeam, awayTeam;
        unsigned int homeTeamPoints, awayTeamPoints;
    public:
        void runGame(Team& home, Team& away, unsigned int pointLimit = 25, int userTeam = 1) { // begins a match between the home and away teams
            homeTeamPoints = 0;
            awayTeamPoints = 0;

            std::cout << "The match between " << home.getName() << " and " << away.getName() << " is starting!\n";
            for (int i = 0; i < 40; i++) {
                std::cout << "-";
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }

            std::cout << "\n";
            longdelay();
            std::cout << home.getName() << " will serve first.";
            longdelay();

            if (userTeam == 1) { // runs when the user's team is the home team
                while (serve(home.getRoster().front()) == 1) {
                    homeTeamPoints += 1;
                    std::cout << home.getName() << "\tVS.\t" << away.getName() << "\n" << homeTeamPoints << "-" << awayTeamPoints << "\n";
                    longdelay();
                }
            } else { // runs when the user's team is the away team
                while (serve(away.getRoster().front()) == 1) {
                    awayTeamPoints += 1;
                    std::cout << home.getName() << "\tVS.\t" << away.getName() << "\n" << homeTeamPoints << "-" << awayTeamPoints << "\n";
                    longdelay();
                }
            }
        }
        int serve(Player& p) { // serves the ball; the user can select a spot to serve at and whether or not it scores will be randomly decided
            std::random_device rd;
            std::mt19937 gen(rd());

            int servingSpot;
            std::cout << "\n" << p.getName() << " is serving!\n";
            shortdelay();
            std::cout << "What spot should they serve at?\n";
            shortdelay();
            std::cout << volleyballCourt;
            std::cout << "Enter a number between 1 and 6: ";
            while (!(std::cin >> servingSpot) || servingSpot < 1 || servingSpot > 6) {
                std::cout << "\nError. Please enter a number between 1 and 6: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::uniform_int_distribution<int> distrib(-1, 8);
            int randomNum = distrib(gen);

            std::cout << p.getName() << " served at spot " << servingSpot << ".";
            if (std::abs(servingSpot - randomNum) <= 3) {
                shortdelay();
                std::cout << "\nIt was received!\n";
                longdelay();
                return 0;
            } else {
                shortdelay();
                std::cout << "\nACE! " << p.getName() << " scored for their team!\n";
                p.setAces(p.getAces() + 1);
                longdelay();
                return 1;
            }
        }
        Game() {
            std::cout << "Game initiated.\n";
            shortdelay();
        }

};

int main() {

    std::string coachName;
    std::cout << "Welcome, coach! What should we call you?: ";
    std::getline(std::cin, coachName);

    std::cout << "\nNice to meet you, " << coachName << "!";
    longdelay();
    std::cout << "\nLet's get you your first player.\n";
    longdelay();
    Player larry("Larry");

    int larryPosition;
    std::cout << "Larry needs to pick a position before he can start playing.";
    longdelay();
    std::cout << "\nWhat position would you like Larry to play? Enter a number.\n\t1 - Setter\n\t2 - Outside Hitter\n\t3 - Middle Blocker\n\t4 - Opposite Hitter\n\t5 - Libero\n\t6 - Defensive Specialist\nYour choice: ";
    while (!(std::cin >> larryPosition) || larryPosition > 6 || larryPosition < 1) {
        std::cout << "Error. Please enter a number between 1 and 6: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    larry.setPosition(larryPosition);


    std::cout << "Right now, Larry isn't officially on a team. Let's get him to one.\n";
    longdelay();
    std::string teamName;
    std::cout << "What would you like to name your new team? You can change this later: ";
    std::getline(std::cin, teamName);
    Team team(teamName);
    team.addToRoster(larry);

    std::cout << "Let's get Larry used to his new environment.\n";
    shortdelay();
    std::cout << "He'll start by playing with a few other players.\n";
    longdelay();

    Team botTeam("SPIKES AND BOLTS");
    Player bot1("BOT1");
    botTeam.addToRoster(bot1);
    
    Game game;
    game.runGame(team, botTeam, 10);

    return 0;
}