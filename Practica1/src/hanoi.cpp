#include <vector>
#include <iostream>
#include <math.h>
#include <cctype>
#include <stdlib.h>
#include <chrono>
#include <thread>


using namespace std;

class HanoiTowers {
private:
    int n_discs;
    vector<vector<int>> sticks;
    vector<int> n_discs_on_stick;
    bool animating = false;
    int move_n = 0;
    
    /**
     * @return The row the disk was moved to
    */
    int move(pair<int, int> disc_pos, int to) {
        bool had_on_top = false;
        int row_top_moved;
        int row_moved;
        int top_stick;
        
        if(disc_pos.second != 0 and sticks[disc_pos.first][disc_pos.second -1] != -1) {
            top_stick = 3 - (disc_pos.first + to);
            pair <int, int> aux_pair(disc_pos.first, disc_pos.second-1);
            row_top_moved = move(aux_pair, top_stick);
            had_on_top = true;
        }
        
        if(animating) {
            system("clear");
            print();
            this_thread::sleep_for(chrono::milliseconds(150));
        }
        
        sticks[to][n_discs - 1 - n_discs_on_stick[to]] = sticks[disc_pos.first][disc_pos.second];
        sticks[disc_pos.first][disc_pos.second] = -1;
        row_moved = n_discs - 1 - n_discs_on_stick[to];
        n_discs_on_stick[disc_pos.first]--;
        n_discs_on_stick[to]++;
        move_n++;
        
        if(had_on_top) {
            pair<int, int> aux_pair(top_stick, row_top_moved);
            move(aux_pair, to);
        }
        
        return row_moved;
    }
    
public:
    HanoiTowers(int n_discs) {
        this->n_discs = n_discs;
        sticks = vector<vector<int>>(3, vector<int>(n_discs, -1));
        n_discs_on_stick = vector<int>(3, 0);
        n_discs_on_stick[0] = n_discs;
        
        for(int i=n_discs-1; i>=0; i--) {
            sticks[0][i] = i;
         }
    }

    void print() {
        string blank = " ";
        string block = "█";
        string stick = "║";
        
        for(int fila=-1; fila<n_discs; fila++) {
            cout << blank;
            if(fila == -1) {
                for(int i=0; i<n_discs-1; i++) {
                    cout << blank;
                }
                
                for(int palo=0; palo<2; palo++) {
                    cout << stick;
                    
                    for(int espacio=0; espacio<2*(n_discs - 1); espacio++) {
                        cout << blank;
                    }
                }
                
                cout << stick;
                
                for(int i=0; i<n_discs-1; i++) {
                    cout << blank;
                }
                
                cout << endl;
                
                continue;
            }
            
            for(int columna=0; columna<(2*n_discs - 1)*3; columna++) {
                int n_stick = columna/(2*n_discs - 1);
                int col_stick = (n_discs - 1) + n_stick*(2*n_discs - 1);
                int dis_stick = abs(col_stick - columna);
                
                if(dis_stick <= sticks[n_stick][fila]) {
                    cout << block;
                }
                else if(columna == col_stick) {
                    cout << stick;
                }
                else {
                    cout << blank;
                }
            }
            
            cout << endl;
        }
        
        cout << "Move: " << move_n << endl;
    }
    
    void solve(bool animated = false) {
        animating = animated;
        
        if(animating) {
            system("clear");
            print();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        
        pair<int, int> aux_pair(0, n_discs-1);
        move(aux_pair, 2);
        
        if(animating){
            system("clear");
            print();
        }
        
        animating = false;
    }
};


int main(int argc, char *argv[]) {
    int n_towers = 6;
    bool animated = false;
    
    if(argc > 3) {
        cerr << "ARGUMENT ERROR" << endl;
        cerr << "hanoi.bin  n_discs=6  animated(Y/N)=N";
        return -1;
    }
    
    if (argc >= 2) {
        n_towers = stoi(argv[1]);
    }
    
    if(argc == 3) {
        if(toupper(argv[2][0]) == 'Y' || toupper(argv[2][0]) == 'S') {
            animated = true;
        }
    }
    
    HanoiTowers t_hanoi(n_towers);
    t_hanoi.solve(animated);
    
    return 0;
}
