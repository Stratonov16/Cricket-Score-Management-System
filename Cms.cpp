//DSA Project
//Nikhil 2019B5A71079H
//Ajinkya 2019B5A71375H
//Shlok Mongia 2019B2A71527H

#include <bits/stdc++.h>

using namespace std;
//Cricket Score management system
class CMS {
private:
    int currentTeam = 1;  //current batting team
    int striker = 1;        //player on strike
    int non_striker = 2;    //player on non strike
    int bowler = 1;         //bowling team player
    int total_balls = 0;    //total balls in current innings
    int total_overs = 0;    //overs
    bool wideBall = false;  //if wide 
    bool noBall = false;    //if no ball

    //DATA structures 

    string team1_name = "", team2_name = "";        //Name of team
    vector <pair<string, string>> team1, team2;     //Players of team, ex: {"MS", "Dhoni"}
    
    //total latest score of teams
    int team1_runs = 0, team2_runs = 0, team1_wickets = 0, team2_wickets = 0, team1_balls = 0, team2_balls = 0;
    
    //Vector of Total Score of teams, updated for every ball
    vector <vector<int> > totalScore1, totalScore2; 
    
    //Stats of players of teams
    map<pair<string, string>, map<string, int>> team1_stats, team2_stats; 
    //for example: map[{Rohit , Sharma}][ map["RUNS"][2] ]

public:
    int players_number; //Count of number of players in each team depends on input
    bool matchEnd = false; //if match is ended or not
    int winner = 0;     //winner = 0 if draw else winner = team number
    
    //Function that intialize team name and players
    void setTeam(int team_number, string team_name, vector <pair<string, string>> team)
    {
        if (team_number == 1)
        {
            team1_name = team_name;
            for (auto i : team)
                team1.push_back(i);
        }
        else
        {
            team2_name = team_name;
            for (auto i : team)
                team2.push_back(i);
        }
    }

    //Function that set who is going to ball
    void setBowler(int player)
    {
        bowler = player;
    }

    //Functions that set wide ball and no ball
    void setWideBall(bool value)
    {
        wideBall = value;
    }
    void setNoBall(bool value)
    {
        noBall = value;
    }

    //Function that return name of both the teams
    bool teamsEntered()
    {
        return team1_name != "" && team2_name != "";
    }
    int getBalls()
    {
        return total_balls;
    }
    int getWickets(int team)
    {
        if (team == 1)
            return team1_wickets;
        return team2_wickets;
    }
    int getTeamSize()
    {
        return team1.size();
    }

    void showCurrentBatters(int team)
    {
        if (team == 1)
        {
            cout << "Striker = " << team1[striker - 1].first << " " << team1[striker - 1].second;
            cout << endl;
            cout << "Non-Striker = " << team1[non_striker - 1].first << " " << team1[non_striker - 1].second << endl;
        }
        else
        {
            cout << "Striker = " << team2[striker - 1].first << " " << team2[striker - 1].second;
            cout << endl;
            cout << "Non-Striker = " << team2[non_striker - 1].first << " " << team2[non_striker - 1].second << endl;
        }
    }
    void updateWickets(int team)
    {
        if (team == 1)
            team1_wickets++;
        else
            team2_wickets++;
    }
    void changeBatsman()
    {
        striker = max(striker, non_striker) + 1;
    }
    //change non_striker
    void strikeChange()
    {
        int temp = striker;
        striker = non_striker;
        non_striker = temp;
    }
    int getStriker() {
        return striker;
    }
    int getNonStriker() {
        return non_striker;
    }
    int getBowler() {
        return bowler;
    }
    // update stats after every ball
    int getBattingTeam()
    {
        return currentTeam;
    }
    void increaseBalls() {
        total_balls++;
        if (total_balls % 6 == 0) {
            total_overs++;
        }
    }
    int getRuns(int team_number)
    {
        if(team_number == 1)
            return team1_runs;
        else
            return team2_runs;

    }

    //Fumction that display score of both teams
    void showScore()
    {
        cout << left << setw(4) << setfill(separator) << team1_name << ": " << team1_runs << "/" << team1_wickets << endl;
        cout << left << setw(4) << setfill(separator) <<  team2_name << ": " << team2_runs << "/" << team2_wickets << endl;
    }

    //Show players of both teams
    void showTeam(int team)
    {
        if(team == 1)
        {
            for (int i = 1; i <= team1.size(); i++)
                cout << i << ": "<< team1[i - 1].first << " " << team1[i - 1].second <<endl;
        }
        else
        {
            for (int i = 1; i <= team2.size(); i++)
                cout << i << ": "<< team2[i - 1].first << " " << team2[i - 1].second <<endl;
        }
    }
    
    //Function that update stats, used with update score function in public
    void updateStats(int runs,int wicket,int wide,int noBall)
    {
        pair <string, string> currentBatsman, currentBowler;
        if (getBattingTeam() == 1)
        {
            currentBatsman = {team1[striker - 1].first, team1[striker-1].second};
            currentBowler = {team2[bowler - 1].first, team2[bowler-1].second};

            team1_stats[currentBatsman]["RUNS"] += runs;
            if (runs == 4)
                team1_stats[currentBatsman]["FOURS"]++;
            else if (runs == 6)
                team1_stats[currentBatsman]["SIXES"]++;
            if(wide==0 && noBall==0)
            team1_stats[currentBatsman]["BALLS"]++;
            if(noBall==0 &&wide==0)
                team2_stats[currentBowler]["BALLS_BOWLED"]++;
            team2_stats[currentBowler]["RUNS_GIVEN"]+= runs + noBall+wide;
            team2_stats[currentBowler]["WICKETS"] += wicket;
        }
        else
        {
            currentBatsman = {team2[striker - 1].first, team2[striker-1].second};
            currentBowler = {team1[bowler - 1].first, team1[bowler-1].second};
            team2_stats[currentBatsman]["RUNS"] += runs;
            if (runs == 4)
                team2_stats[currentBatsman]["FOURS"]++;
            else if (runs == 6)
                team2_stats[currentBatsman]["SIXES"]++;
            team1_stats[currentBatsman]["BALLS"]++;
            if(noBall==0)
                team1_stats[currentBowler]["BALLS_BOWLED"]++;
            team1_stats[currentBowler]["RUNS_GIVEN"]+= runs + noBall;
            team1_stats[currentBowler]["WICKETS"] += wicket;

        }

    }

    //Function that show stat of teams
    void showStats(int team_number)
    {
        // STATS FOR TEAM NUMBER 1
        if (team_number == 1)
        {
            cout <<"\nBatting stats:\n";
            cout << "Player           Runs Balls Fours Sixes\n";
            //Batting stats of team1
            for (int i = 0; i < team1.size(); i++)
            {
                //ith player
                pair<string, string> player = {team1[i].first, team1[i].second};

                cout << left << setw(nameWidth) << setfill(separator) <<team1[i].first << " ";
                cout << left << setw(nameWidth) << setfill(separator) <<team1[i].second << " ";
                cout << left << setw(numWidth) << setfill(separator) <<team1_stats[player]["RUNS"] << " ";
                cout << left << setw(numWidth) << setfill(separator) <<team1_stats[player]["BALLS"] << " ";
                cout << left << setw(numWidth) << setfill(separator) <<team1_stats[player]["FOURS"] << " ";
                cout << left << setw(numWidth) << setfill(separator) <<team1_stats[player]["SIXES"] << " ";
                cout<<endl;
            }
            //Bowling Stats of team2 
            cout <<"\nBowling stats:\n";
            cout << "Player           Balls Wickets Runs\n";
            for (int i = 0; i < team2.size(); i++)
            {
                //ith bowler
                pair<string, string> bowler = {team2[i].first, team2[i].second};
                // re(team2_stats[bowler]["BALLS_BOWLED"]);
                //If no ball is bowled by him don't print
                // if(team2_stats[bowler]["BALLS_BOWLED"] == 0)
                //  continue;
                cout << left << setw(nameWidth) << setfill(separator) << team2[i].first << " ";
                cout << left << setw(nameWidth) << setfill(separator) <<team2[i].second << " ";
                cout << setw(numWidth) << setfill(separator) << team2_stats[bowler]["BALLS_BOWLED"] << " ";
                cout << setw(numWidth) << setfill(separator) << team2_stats[bowler]["WICKETS"] << " ";
                cout << setw(numWidth) << setfill(separator) << team2_stats[bowler]["RUNS_GIVEN"] << " ";
                cout<<endl;
            }

        }
        //STATS FOR TEAM NUMBER 2
        else
        {
            cout <<"\nBatting stats:\n";
            cout << "Player           Runs Balls Fours Sixes\n";
            //Batting stats of team2
            for (int i = 0; i < team2.size(); i++)
            {
                //ith player
                pair<string, string> player = {team2[i].first, team2[i].second};

                cout << left << setw(nameWidth) << setfill(separator) <<team2[i].first << " ";
                cout << left << setw(nameWidth) << setfill(separator) <<team2[i].second << " ";
                cout << left << setw(numWidth) << setfill(separator) <<team2_stats[player]["RUNS"] << " ";
                cout << left << setw(numWidth) << setfill(separator) <<team2_stats[player]["BALLS"] << " ";
                cout << left << setw(numWidth) << setfill(separator) <<team2_stats[player]["FOURS"] << " ";
                cout << left << setw(numWidth) << setfill(separator) <<team2_stats[player]["SIXES"] << " ";
                cout<<endl;
            }
            //Bowling Stats of team1 
            cout <<"\nBowling stats:\n";
            cout << "Player           Balls Wickets Runs\n";
            for (int i = 0; i < team1.size(); i++)
            {
                //ith bowler
                pair<string, string> bowler = {team1[i].first, team1[i].second};

                //If no ball is bowled by him don't print
                // if(team1_stats[bowler]["BALLS_BOWLED"] == 0)
                //  continue;
                cout << left << setw(nameWidth) << setfill(separator) << team1[i].first << " ";
                cout << left << setw(nameWidth) << setfill(separator) <<team1[i].second << " ";
                cout << setw(numWidth) << setfill(separator) << team1_stats[bowler]["BALLS_BOWLED"] << " ";
                cout << setw(numWidth) << setfill(separator) << team1_stats[bowler]["WICKETS"] << " ";
                cout << setw(numWidth) << setfill(separator) << team1_stats[bowler]["RUNS_GIVEN"] << " ";
                cout<<endl;
            }
        }
    }

    //Function that change Innings
    void changeInnings()
    {
        cout << "INNINGS OVER\n" << endl;
        currentTeam = 2;
        striker = 1;
        non_striker = 2;
        total_balls = 0;
        total_overs = 0;
        wideBall = false, noBall = false;
    }
    //Function that add runs to team score
    void addRuns(int runs, int team_no)
    {
        if (team_no == 1)
            team1_runs += runs;
        else
            team2_runs += runs;
    }

    //Vector that store what happen in every ball
    void putScore(vector <int>& v) {
        if (getBattingTeam() == 1)
            totalScore1.push_back(v);
        else
            totalScore2.push_back(v);
    }
    //Export ball by ball stat in data file from vector
    void outFile()
    {
        ofstream myfile ("data.txt");
        if (myfile.is_open())
        {
            myfile <<team1_name <<" V/S " << team2_name <<endl; //Team Names 

            //Team1 players
            myfile <<team1_name <<":\n";
            for(auto i = 0; i < players_number; ++i)
                myfile << i+1 <<". "<< team1[i].first << " " << team1[i].second <<endl;
            myfile << endl;

            //Team2 players
            myfile <<team2_name <<":\n";
            for(auto i = 0; i < players_number; ++i)
                myfile << i+1 <<". " << team2[i].first << " " << team2[i].second <<endl;
            
            //Team 1 stats
            myfile << "-----------------Team1--------------\n\n";
            myfile << "(playerNumber, Runs, Bowler, Out or not, type of ball)\n";
            for(auto i = totalScore1.begin(); i != totalScore1.end(); ++i)
            {
                for(auto j = (*i).begin(); j != (*i).end(); ++j)
                    myfile << *j << " ";
                myfile << endl;
            }
            cout << endl;

            //Team 2 stats
            myfile << "-----------------Team2--------------\n\n";
            myfile << "(playerNumber, Runs, Bowler, Out or not, type of ball)\n";
            for(auto i = totalScore2.begin(); i != totalScore2.end(); ++i)
            {
                for(auto j = (*i).begin(); j != (*i).end(); ++j)
                    myfile << *j << " ";
                myfile << endl;
            }

            myfile.close();
        }
        else
            cout << "Unable to open file\n";
    }

    //These are used to set spaces while printing stats in table format
    const char separator = ' ';
    const int nameWidth = 8;
    const int numWidth = 5;

};


//Function that initialize team name and players
void createDatabase(CMS &match)
{
    //Number of players
    int noOfPlayers;
    cout << "Enter the number of players: ";
    cin >> noOfPlayers;
    match.players_number = noOfPlayers;

    //Team names
    string team1_name, team2_name;
    cout << "Enter first batting team name: ";
    cin >> team1_name;
    vector <pair<string, string>> team1, team2;
    cout << "Enter Players according to the Batting Order:\n";
    
    //Players name
    for (int i = 1; i <= match.players_number; ++i)
    {
        cout << "Player " << i << " (FIRSTNAME LASTNAME) " << ": ";
        string fn, ln;
        cin >> fn >> ln;
        pair<string, string> player;
        player = make_pair(fn, ln);
        team1.push_back(player);
    }
    cout << endl;
    
    cout << "Enter Second team name: ";
    cin >> team2_name;
    cout << "Enter Players according to the Batting Order:\n";
    for (int i = 1; i <= match.players_number; ++i)
    {
        cout << "Player " << i << " (FirstName LastName) " << ": ";
        string fn, ln;
        cin >> fn >> ln;
        pair<string, string> player;
        player = make_pair(fn, ln);
        team2.push_back(player);
    }

    //intializing private members of Match using setTeam function
    match.setTeam(1, team1_name, team1);
    match.setTeam(2, team2_name, team2);

}

//Function to show output to user to update score and call updatestat function of Class 
bool updateScore(CMS &match)  //return 0 if not able to update score (whhen match ended)
{
    //Check if match is going on or end
    if(match.matchEnd == true)
    {
        cout << "Can't update score, match is finished\n";
        return false;
    }

    //Before start of every over ask who is the bowler
    if( ( match.getBalls() )%6 == 0)
    {
        cout << "Select bowler:\n";
        if(match.getBattingTeam() == 1)
            match.showTeam(2); //if batting team is team1 then show bowlers of team2 and viceversa
        else
            match.showTeam(1);
        int res;
        cin >> res;
        match.setBowler(res);
    }

    int wide = 0, noball = 0; //temporary store if it is wide and no ball
    //Ask type of ball
    cout << "Enter Type of Ball\n";
    cout << "1 : Normal Ball\n";
    cout << "2 : Wide ball\n";
    cout << "3 : No ball\n";
    int response;
        cin >> response;
    if(response == 2) //wide
    {
        wide++;
        match.setWideBall(true);
    }
    else if(response == 3) //noball
    {
        noball++;
        match.setNoBall(true);
    }
    else
    {
        match.setWideBall(false);
        match.setNoBall(false);
    }

    //Runs scored on that ball by batsman
    cout << "Enter runs scored: "; 
    int runs;
    cin >> runs;
    cout << "Was is a wicket/run-out?(Y/N) ";
    string input;
    cin >> input;


    //Store all the response in vector and update it
    vector<int> v;

    v.push_back(match.getStriker()); //player number into vector
    v.push_back(runs); //Runs scored into vector
    v.push_back(match.getBowler()); //bowler number into vector
    if(input == "y" || input == "Y") //Was it a wicket or not 
        v.push_back(1); //if Wicket store 1 else store 0
    else
        v.push_back(0); 
    v.push_back(response); //Type of ball into vector
    match.putScore(v);

    //update stats
    if (input == "Y" || input =="y") //if it is a wicket
    {
        match.updateStats(runs,1,wide,noball); //runs , wicket
        match.changeBatsman();
        match.updateWickets(match.getBattingTeam());
        if (match.getTeamSize() == match.getWickets(match.getBattingTeam()))
            match.changeInnings();
        if(!(wide || noball))
            match.increaseBalls();
    }
    else
    {
        match.updateStats(runs, 0,wide,noball);
        if(!(wide || noball))
            match.increaseBalls();
        if (runs == 1 || runs == 3 || runs == 5)
            match.strikeChange();
    }
    //add extra runs in teams
    int extra = 0;
    if(wide || noball)
        extra++;
    match.addRuns(runs + extra, match.getBattingTeam());


    //Check if match is finished
    if((match.getBattingTeam() == 2) && (match.getRuns(2) > match.getRuns(1))) //If current team is 2 and score is greater than team 1 score
    {
        cout << "TEAM 2 won the match\n";
        match.winner = 2;
        match.matchEnd = true;
    }

    if((match.getBattingTeam() == 2) && (match.getWickets(2) == (match.players_number - 1) ))
    {
        cout << "TEAM 1 won the match\n";
        match.winner = 1;
        match.matchEnd = true;
    }
    return 1; //return true after updating score
}


//Shows what are the choices available
void choices()
{
    cout << "Enter one of the following choices:\n";
    cout << "1: Create Match:\n";
    cout << "2: Update Score\n";
    cout << "3: View Stats\n";
    cout << "4: Change Innings\n";
    cout << "5: End Match\n";
    cout << "6: Export stats\n";
    cout << endl;
}


int main()
{
    //freopen("input.txt", "r", stdin);

    CMS match;          //Object of class CMS (CricketScore Management System)
    int option = -1;     //Options that user select
    bool matchGoingOn = 0; //If match is already going on or not
    while (option != 5)
    {
        if (matchGoingOn)
        {
            cout << endl;       //Show score and batters everytime if match is going on
            match.showScore();
            match.showCurrentBatters(match.getBattingTeam());
            cout << endl;
        }
        choices();      //Show available choices to user
        cin >> option;
        switch (option)
        {

        case 1:             //create match
            if (matchGoingOn)
            {
                cout << "Match is already going on...\n";
                cout << "First End this Match, to create another match.\n\n";
            }
            else
            {
                createDatabase(match);
                matchGoingOn = 1;
            }
            break;

        case 2:             //update stats
            if(matchGoingOn == false)
            {
                cout <<"First create Match..\n";
                break;
            }
            updateScore(match);
            break;

        case 3:             //show stats
            cout << "1: First Innings stats\n";
            cout << "2: Second Innings stats\n";
            int input;
            cin >> input;
            if (input == 1)
                match.showStats(1);
            else
                match.showStats(2);
            break;

        case 4:             //change innings
            match.changeInnings();
            break;

        case 5:             //exit/ end match
            if(match.winner == 0)
                cout << "Match tie\n";
            else if(match.winner == 1)
                cout << "Team 1 have won the match\n";
            else
                cout << "Team 2 have won the match\n";
            cout << "exiting...\n";
            break;
            
        case 6:             //export match data to file
            match.outFile();
            cout << "Stats stored in data.txt\n";
            break;

        default:            //else discard input
            cout << "Invalid entry.\n";
            cin.clear();         //if input is invalid clear cin
            cin.ignore(1, '\n'); // and ignore 1 character from input stream
            break;
        }
    }
    return 0;

}

