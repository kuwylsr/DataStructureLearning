#include<iostream>
#include<vector>
#include "stdio.h"

using namespace std;

struct ListNode{
    int team_id;
    ListNode *next;
    ListNode(int val) : team_id(val),next(NULL) {}
};

class Score {
public:
    vector<vector<int>> mat;
    int team_num;

    Score(int num){
        mat.resize(num);
        for(int i = 0 ; i < num ; i++){
            mat[i].resize(num);
        }
        team_num = num;
    }

    void init(){
        for(int i = 0; i < team_num; i++){
            for(int j = i+1; j < team_num;j ++){
                printf("Can team:%d beat team:%d(yes:1,no:0)",i,j);
                int val;
                cin >> val;
                mat[i][j] = val;
                mat[j][i] = 1-val;
                mat[i][i] = -1;
            }
        }
    }

    ListNode* search(){
        int i = 0; // 初始比较team0 和 team1
        ListNode *root = new ListNode(i);
        ListNode *p = root;
        
        for(int j = 1; j < team_num ;j++){
            if(mat[p->team_id][j] == 1){ // i 胜 j
                ListNode *tmp1 = p;
                while(tmp1 -> next != NULL && mat[tmp1 -> next->team_id][j] == 1){
                    tmp1 = tmp1->next;
                }
                if(tmp1 -> next == NULL){
                    tmp1 -> next = new ListNode(j);
                }else{ // 链表插入
                    ListNode *tmp2 = tmp1-> next;
                    tmp1->next = new ListNode(j);
                    tmp1->next->next = tmp2;
                }
            }else if(mat[p->team_id][j] == 0){ // j 胜 i
                // cout << "??" << endl;
                ListNode * newHead = new ListNode(j);
                newHead->next = p;
                p = newHead;
            }
        }
        return p;
    }

};

int main(){
    int team_num = 5;
    Score *S = new Score(team_num);
    cout << S->mat[0].size() << endl;
    S->init();
    ListNode *head = S->search();
    while(head != NULL){
        cout << head->team_id << " -> ";
        head = head->next;
    }
    cout << endl;
    return 0;
}