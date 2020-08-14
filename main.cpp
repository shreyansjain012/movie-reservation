#include <bits/stdc++.h>
using namespace std;
class Seat{
    private:
        bool aisle;
        bool occupied;
    public:
        Seat(){
            aisle = false;
            occupied = false;
        }
        void set_aisle(bool b){
            aisle = b;
        }
        bool is_aisle(){
            return aisle;
        }
        bool is_occupied(){
            return occupied;
        }
        void set_occupied(bool ans){
            occupied = ans;
        }
};

class Screen{
    private:
        string name;
        int rows;
        int cols;
        vector<vector<Seat> > seats;
    public: 
        Screen(string n, int r, int c, const vector<int> aisle){
            name = n;
            rows = r;
            cols = c;
            seats.resize(rows, vector<Seat> (cols));
            
            for(int x=0; x<rows; x++){
                for(int y=0; y<cols; y++){
                    Seat s{};
                    seats[x][y] = s;
                }
                for(auto i: aisle){
                    int y = i - 1;
                    seats[x][y].set_aisle(true);
                }
            }
            cout << "success\n";
        }
    
        void print(){
            cout << "Screen name: " << name << " ";
            cout << "Rows: " << rows << " ";
            cout << "Cols: " << cols << "\n";
            cout << "Seat 1: " << "aisle: " << seats[0][0].is_aisle() << " " 
                << "occupied: " << seats[0][0].is_occupied() << "\n";
        }
        
        bool reserveSeats(int r, const vector<int>& req){
            int x = r - 1;
            for(auto i: req){
                int y = i - 1;
                if(seats[x][y].is_occupied()) return false;
            }
            for(auto i: req){
                int y = i - 1;
                seats[x][y].set_occupied(true);
            }
            return true;
        }
        vector<int> getUnreservedSeats(int r){
            vector<int> res;
            int x = r-1;
            for(int y=0; y<cols; y++){
                if(!seats[x][y].is_occupied()) res.push_back(y+1);
            }
            return res;
        }
        vector<int> suggestSeats(int no_of_seats, int r, int req_seat_no){
            vector<int> res;
            int x = r-1;
            int y = req_seat_no - 1;
            bool left = true, right = true;
            if(seats[x][y].is_occupied()) return res;
            if(seats[x][y].is_aisle()){
                if(y-1>=0 && seats[x][y-1].is_aisle()) left = false;
                if(y+1<cols && seats[x][y+1].is_aisle()) right = false;
            }
            no_of_seats--;
            res.push_back(req_seat_no);
            int i = y-1, j = y+1;
            while(left && no_of_seats>0 && i>=0){
                if(seats[x][i].is_occupied()) break;
                res.push_back(i+1);
                no_of_seats--;
                if(seats[x][i].is_aisle()) break;
                i--;
            }
            while(right && no_of_seats>0 && j<cols){
                if(seats[x][j].is_occupied()) break;
                res.push_back(j+1);
                no_of_seats--;
                if(seats[x][j].is_aisle()) break;
                j++;
            }
            if(no_of_seats>0) res.clear();
            sort(res.begin(), res.end());
            return res;
        }
};

vector<string> getWords(string s){
    vector<string> words;
    string word = "";
    for(char c: s){
        if(c == ' '){
            words.push_back(word);
            word="";
        }
        word += c;
    }
    words.push_back(word);
    return words;
}

int main(){
    int tests;
    string input, operation;
    vector<string> words;
    map<string, Screen*> mp;
    getline(cin, input);
    tests = stoi(input);
    
    while(tests--){
        getline(cin, input);
        words = getWords(input);
        operation = words[0];
        
        if(operation == "add-screen"){
            vector<int> aisle_seats;
            string screen_name = words[1];
            int rows = stoi(words[2]);
            int cols = stoi(words[3]);
            for(int i=4; i<words.size(); i++) aisle_seats.push_back(stoi(words[i]));
            
            mp[screen_name] = new Screen(screen_name, rows, cols, aisle_seats);
        } 
        else if(operation == "reserve-seat"){
            vector<int> req_seats;
            string screen_name = words[1];
            int row = stoi(words[2]);
            for(int i=3; i<words.size(); i++) req_seats.push_back(stoi(words[i]));
            
            bool res = mp[screen_name]->reserveSeats(row, req_seats);
            
            if(res) cout << "success\n";
            else cout << "failure\n";
        }
        else if(operation == "get-unreserved-seats"){
            string screen_name = words[1];
            int row = stoi(words[2]);
            vector<int> unreserved_seats;
            unreserved_seats = mp[screen_name]->getUnreservedSeats(row);
            for(auto i: unreserved_seats) cout << i << " ";
            cout << "\n";
        }
        else if(operation == "suggest-contiguous-seats"){
            string screen_name = words[1];
            int no_of_seats = stoi(words[2]);
            int row = stoi(words[3]);
            int req_seat_no = stoi(words[4]);
            vector<int> suggested_seats;
            
            suggested_seats = mp[screen_name]->suggestSeats(no_of_seats, row,  req_seat_no);
            if(suggested_seats.size() == 0) cout << "none\n";
            else {
                for(auto i: suggested_seats) cout << i << " ";
                cout << "\n";
            }
        }
    }
    return 0;
}
