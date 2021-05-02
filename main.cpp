#include <iostream>
#include "tabela.h"
#include<fstream>
using namespace std;

fstream is("tabela.txt");

//FUNKCJE DODATKOWE
string trim_left(const string &str){
string pattern = " \f\n\r\t\v";
return str.substr(str.find_first_not_of(pattern));
}

string trim_right(string& str)
{
string pattern = " \f\n\r\t\v";
return str.substr(0,str.find_last_not_of(pattern) + 1);
}

string trim(string& str)
{
return trim_left(trim_right(str));
}

//TESTY
void test_read_write()
{
    Club c1;

    if(!is){
        cerr<<"Blad otwarcia pliku"<<endl;
        return;
    }
    string header,header2,header3;
    getline(is,header);
    cout<<header<<endl;
    getline(is,header2);
    cout<<header2<<endl;
    getline(is,header3);
    cout<<header3<<endl;
    cout << endl;
    while(is) {
        Club c1;
        c1.read(is);
        if(!is) break;
        //zapisz na cout
        c1.write(cout);
    }

}

void test_read_write_table(){
Table t;
t.read_table(is);
t.write_table(cout);
}


//KOLEJKI


void game_round(){
Table t;
t.read_table(is);

//KOLEJKA 34
t.match_day("Celta Vigo","Levante",2,0);
t.match_day("Eibar","Deportivo Alaves",3,0);
t.match_day("Elche","Atletico Madryt",0,1);
t.match_day("SD Huesca","Real Sociedad",1,0);
t.match_day("Real Madryt","Osasuna Pampeluna",2,0);
t.match_day("Real Valladolid","Real Betis",1,1);
t.match_day("Villarreal","Getafe",1,0);
//t.match_day("Granada","Cadiz",0,0);
//t.match_day("Valencia CF","FC Barcelona",0,0);
//t.match_day("Sevilla FC","Athletic Bilbao",0,0);

//KOLEJKA 35



t.write_table(cout);
}



int main()
{

//test_read_write(); //DZIALA


//test_read_write_table();  //DZIALA

//t.zeros();

//mecze lepiej jak nie sa rozbite na funkcje kolejki bo nowy
//obiekt trzeba tworzyc tabela wiec lepiej raz i po sobie w 1 funkcji wyniki kolejki

game_round();



    return 0;
}
