#include<iostream>
#include<random>
#include<time.h>
#include<string>
using namespace std;
class Team {
private:
	string team_name;
	bool batting;
	int score;
	int overs;
	int bowls;
	int players;
public:
	Team( string team_name, bool batting, int score, int overs) {
		this->team_name = team_name;
		this->batting = batting;
		this->score = score;
		this->overs = overs;
		this->bowls = 6;
		this->players = 11;
	}
	string get_team_name() {
		return team_name;
	}
	bool is_batting() {
		return batting;
	}
	void set_batting(bool batting) {
		this->batting = batting;
	}
	int get_score() {
		return score;
	}
	void set_score(int score) {
		this->score = score;
	}
	void increase_score(int score) {
		this->score += score;
	}
	float get_overs() {
		if (bowls != 6 && bowls!=0)
			return (overs - 1) + (bowls / 10.0f);
		else 
			return overs;
	}
	int get_bowls() {
		return bowls;
	}
	void set_overs(int overs) {
		this->overs = overs;
	}
	void decrease_overs(int overs) {
		this->overs-=overs;
	}
	void set_bowls(int bowls) {
		this->bowls = bowls;
	}
	void decrease_bowls(int bowls) {
		this->bowls -= bowls;
	}
	void set_players(int players) {
		this->players = players;
	}
	void out() {
		this->players--;
	}
	int get_players() {
		return this->players;
	}
};
int main() {
	srand(time(NULL));
	int total_overs;
	int scores[] = { -1,0,1,2,3,4,5,6 };
	string toss_values[] = { "Head", "Tails" };
	string toss_flip_value;
	bool team_a_batting;
	bool team_b_batting;
	string batting;
	cout << "**********CRICKET MATCH**********" << endl;
	string teamA_name, teamB_name;
	char toss_value_for_team_A;
	cout << "Please enter name for team 1 : ";
	getline(cin, teamA_name);
	cout << "Please enter name for team 2 : ";
	getline(cin, teamB_name);
	cout << "Head or Tails for Team " << teamA_name << " (H/T): ";
	cin >> toss_value_for_team_A;
	cin.clear();
	toss_flip_value = toss_values[rand() % 2];
	cout << "TOSS ? " << toss_flip_value << endl;
	cout << (toss_flip_value[0] == toupper(toss_value_for_team_A) ? teamA_name : teamB_name) << " won the toss" << endl;
	cout << (toss_flip_value[0] == toupper(toss_value_for_team_A) ? teamA_name : teamB_name) << " batting or bowling (ba/bo)? ";
	cin >> batting;
	(toss_flip_value[0] == toupper(toss_value_for_team_A) ? team_a_batting : team_b_batting) = (batting.substr(0, 2) == "ba");
	(toss_flip_value[0] == toupper(toss_value_for_team_A) ? team_b_batting : team_a_batting) = !(toss_flip_value[0] == toupper(toss_value_for_team_A) ? team_a_batting : team_b_batting);
	cout << "Please enter match overs : ";
	cin >> total_overs;
	Team teamA(teamA_name, team_a_batting, 0, total_overs);
	Team teamB(teamB_name, team_b_batting, 0, total_overs);
	for (int team = 1; team <= 2; team++) {
		Team* bowling_team = &(team_a_batting ? teamB : teamA);
		Team* batting_team = &(team_a_batting ? teamA : teamB);
		bool all_out = false;
		cout << "BATTING TEAM : " << batting_team->get_team_name() << endl << endl;
		//for( ; ; )
		for (; bowling_team->get_overs() > 0 && !all_out; bowling_team->decrease_overs(1)) {
			cout << "Over " << (total_overs - bowling_team->get_overs())+1 << endl;
			int over_score = 0;
			int players_bold = 0;
			for (bowling_team->set_bowls(6); bowling_team->get_bowls() > 0 && !all_out; bowling_team->decrease_bowls(1)) {
				int score = scores[rand() % 8];
				if (score == -1) {
					batting_team->out();
					players_bold++;
				}
				else {
					batting_team->increase_score(score);
					over_score += score;
					//over_score = over_score + socre
				}
				all_out = (batting_team->get_players() == 0);
			}
			cout << "Over Score : " << over_score << endl;
			cout << "Players bold in over : " << players_bold << endl;
			cout << "Total Score : " << batting_team->get_score() << endl;
			cout << "Total bolds : " << 11 - batting_team->get_players() << endl;
		}
		team_a_batting = !team_a_batting;
		team_b_batting = !team_b_batting;
		cout << endl << endl;
	}
	cout << "Results : \n";
	cout << "Total Overs : " << total_overs << endl;
	cout << "**********" << teamA.get_team_name() << "**********\n";
	cout << "Score : " << teamA.get_score() << endl;
	cout << "Bolds : " << 11 - teamA.get_players() << endl;
	cout << "Overs Played : " << total_overs - teamB.get_overs() << endl;
	cout << "**********" << teamB.get_team_name() << "**********\n";
	cout << "Score : " << teamB.get_score() << endl;
	cout << "Bolds : " << 11 - teamB.get_players() << endl;
	cout << "Overs Played : " << total_overs - teamA.get_overs() << endl;
	if (teamA.get_score() != teamB.get_score())
		cout << "********************" << (teamA.get_score() > teamB.get_score() ? teamA.get_team_name() : teamB.get_team_name()) << " WON!********************\n";
	else
		cout << "********************DRAW!********************\n";
}