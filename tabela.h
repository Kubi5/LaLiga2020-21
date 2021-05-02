#include <iostream>

using namespace std;

class Club{
public:
int position;
string name;
int matches;
int wins;
int loses;
int draws;
int goals_scored;
int goals_loses;
int points;
bool relegation;


istream& read(istream& is);
ostream& write(ostream& os);

};

class Table{
public:
string header,header2,header3;
Club tab[20];

Table();
~Table();

void zeros();
void match_day(string home_team,string away_team,int score_home,int score_away);
void positioning();
istream& read_table(istream& is);
ostream& write_table(ostream& os);


};
