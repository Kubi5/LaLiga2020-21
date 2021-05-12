#include <iostream>
#include "tabela.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctype.h>
#include <sstream>
#include <windows.h>
#include <shellapi.h>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>


using namespace std;

extern string trim(string&str);
extern string trim_left(const string&str);
extern string trim_right(string&str);
extern fstream is;

istream& Club::read(istream &is){
char c;
        is>>position;


        while(1){
        is.get(c);
            if(isdigit(c)) break;
        name+=c;
        }
        name=trim(name);


        is.unget();
        is>>matches;
        is>>wins;
        is>>draws;
        is>>loses;
        is>>goals_scored;
        is>>goals_loses;
        is>>points;
        is>>relegation;

    return is;
}


ostream& Club::write(ostream& os){

    if(name.size()<8){
    os<<position<<"\t"<<name<<"\t"<<'\t'<<'\t'<<matches<<"\t"<<wins<<"\t"<<draws;
    os<<"\t"<<loses<<"\t"<<goals_scored<<"\t"<<goals_loses<<"\t"<<points;
    os<<"\t"<<relegation<<endl;
    }

    else if(name.size()>=16){
    os<<position<<"\t"<<name<<"\t"<<matches<<"\t"<<wins<<"\t"<<draws;
    os<<"\t"<<loses<<"\t"<<goals_scored<<"\t"<<goals_loses<<"\t"<<points;
    os<<"\t"<<relegation<<endl;
    }

    else if(name.size()>=8 && name.size()<16){
    os<<position<<"\t"<<name<<"\t"<<'\t'<<matches<<"\t"<<wins<<"\t"<<draws;
    os<<"\t"<<loses<<"\t"<<goals_scored<<"\t"<<goals_loses<<"\t"<<points;
    os<<"\t"<<relegation<<endl;
    }

    return os;
}


Table::Table(){

}

Table::~Table(){

cout<<endl<<"=========If you want to see current LaLiga table press 's' end click enter"<<endl;
    char c;
    cin>>c;
    while(c!='s'){
    cout<<"You press the wrong key, press 's' end  confirm by clicking enter"<<endl;
    cin>>c;
    }
    ShellExecute(0, 0, "https://www.primeradivision.pl/tabela/", 0, 0 , SW_SHOW );
}

istream& Table::read_table(istream &is){

    if(!is){
        cerr<<"Blad otwarcia pliku"<<endl;
       exit(1);
    }

    getline(is,header);
    getline(is,header2);
    getline(is,header3);
    //getline(is,header4);
    //cout<<header<<endl<<header2<<endl<<header3<<endl;

    for(int i=0;i<20;i++){   // DZIALA
    Club c;
    c.read(is);
    tab[i]=c;
    }

    return is;
}

ostream& Table::write_table(ostream &os){

    os<<'\t'<<header<<endl<<header2<<endl<<header3<<endl<<endl;

    for(int i=0;i<20;i++){
        tab[i].write(os);
    }


        return os;
}

void Table::positioning(){

    for(int i=0;i<20;i++){
        for(int j=i+1;j<20;j++){
            if(tab[i].points<tab[j].points){
                swap(tab[i],tab[j]);
                swap(tab[i].position,tab[j].position);
                }

            if(tab[i].points==tab[j].points){
                if(tab[i].goals_scored-tab[i].goals_loses<tab[j].goals_scored-tab[j].goals_loses){
                 swap(tab[i],tab[j]);
                swap(tab[i].position,tab[j].position);
                }
            }
        }
    }

    for(int i=0;i<17;i++){
        tab[i].relegation=0;
    }
    for(int i=17;i<20;i++){
        tab[i].relegation=1;
    }
}


void Table::match_day(string home_team,string away_team,int score_home,int score_away){

    for(int i=0;i<20;i++){
            if(tab[i].name==home_team){
                tab[i].goals_scored+=score_home;
                tab[i].goals_loses+=score_away;
                    if(score_home>score_away){
                        tab[i].points+=3;
                        tab[i].wins++;
                    }
                    if(score_home==score_away){
                        tab[i].points+=1;
                        tab[i].draws++;
                    }
                    if(score_home<score_away){
                        tab[i].loses++;
                    }
                    tab[i].matches++;

            }
    }

    for(int i=0;i<20;i++){
            if(tab[i].name==away_team){
                tab[i].goals_scored+=score_away;
                tab[i].goals_loses+=score_home;

                if(score_home<score_away){
                        tab[i].points+=3;
                        tab[i].wins++;
                    }
                if(score_home==score_away){
                        tab[i].points+=1;
                        tab[i].draws++;
                    }
                if(score_home>score_away){
                        tab[i].loses++;
                    }
                tab[i].matches++;
            }
    }

    positioning();
}

void Table::zeros(){

    for(int i=0;i<20;i++){
    tab[i].matches=0;
    tab[i].wins=0;
    tab[i].draws=0;
    tab[i].loses=0;
    tab[i].goals_scored=0;
    tab[i].goals_loses=0;
    tab[i].points=0;
    }

positioning();
}





