#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>

using std::string;
using std::vector;




struct Node
{
    vector <vector <Node*> > go;
    bool is_acceptable = false;
    int number = 0;
    Node ()
    {
        go.resize(27);
    }

};

void GoAndPrint(Node* start)
{

    std::unordered_set <Node*> visited;
    vector <Node*> v;
    v.push_back(start);
    visited.insert (start);
    while (!v.empty())
    {
        Node* current = v.back();

        v.pop_back();
        visited.insert (current);
        for (int i = 0; i < 27; i++) for (int j = 0; j < current -> go [i].size(); j++)
        {


            if (visited.find(current -> go [i] [j]) == visited.end())
            {

                visited.insert(current -> go [i] [j]);
                v.push_back (current -> go [i] [j]);

            }
        }



    }


}

void Acc_To_New (Node* start, Node* new_final)
{
    std::unordered_set <Node*> visited;
    vector <Node*> v;
    v.push_back(start);
    visited.insert (start);
    while (!v.empty())
    {
        Node* current = v.back();

        v.pop_back();
        visited.insert (current);
        for (int i = 0; i < 27; i++) for (int j = 0; j < current -> go [i].size(); j++)
            if (visited.find(current -> go [i] [j]) == visited.end())
            {

                visited.insert(current -> go [i] [j]);
                v.push_back (current -> go [i] [j]);

            }
        if (current -> is_acceptable)
        {

            current -> is_acceptable = false;
            current -> go [0].push_back(new_final);

        }

    }
}

void GoEmpty(std::unordered_set <Node*>* us)
{

    vector <Node*> v;
    for (auto iter = us->begin(); iter != us->end(); iter++) v.push_back(*iter);


    while (!v.empty())
    {
        Node* current = v.back();

        v.pop_back();
        us->insert (current);
        for (int j = 0; j < current -> go [0].size(); j++)
        {


            if (us->find(current -> go [0] [j]) == us->end())
            {

                us->insert(current -> go [0] [j]);
                v.push_back (current -> go [0] [j]);

            }

        }



    }
}

string Accepting(string str, string tested)
{






    int nodes_num = 0;


    int len = str.length();

    vector <Node*> starts;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '0')
        {
            Node* newnode = new Node();
            newnode->number = nodes_num;
            nodes_num++;
            starts.push_back(newnode);

        }
        else if (str[i] == '1')
        {
            Node* newnode = new Node();
            newnode -> is_acceptable = true;
            newnode->number = nodes_num;
            nodes_num++;
            starts.push_back(newnode);

        }
        else if (str[i] == '+')
        {
            if (starts.size() < 2)
            {
                return ("ERROR");

            }
            Node* newnode = new Node();

            newnode -> go[0].push_back(starts.back());
            starts.pop_back();
            newnode -> go[0].push_back(starts.back());
            starts.pop_back();
            newnode->number = nodes_num;
            nodes_num++;
            starts.push_back(newnode);

        }
        else if (str[i] == '*')
        {
            if (starts.size() < 1)
            {
                return ("ERROR");

            }
            Node* newnode = new Node();
            Acc_To_New (starts[starts.size() - 1], newnode);
            newnode -> go[0].push_back(starts.back());
            starts.pop_back();
            newnode->is_acceptable = true;
            newnode->number = nodes_num;
            nodes_num++;
            starts.push_back(newnode);


        }
        else if (str[i] == '.')
        {
            if (starts.size() < 2)
            {
                return ("ERROR");

            }
            Acc_To_New (starts[starts.size() - 2], starts[starts.size() - 1]);
            starts.pop_back();

        }
        else
        {
            Node* newnode1 = new Node();
            Node* newnode2 = new Node();
            newnode2 -> is_acceptable = true;
            newnode1 -> go [str[i] - 'a' + 1].push_back(newnode2);
            newnode1->number = nodes_num;
            nodes_num++;
            newnode2->number = nodes_num;
            nodes_num++;
            starts.push_back(newnode1);

        }
    }

    if (starts.size() != 1)
        {
            return ("ERROR");

        }

    //GoAndPrint(starts[0]);

    int ans = - 1;
    std::unordered_set <Node*> current;
    current.insert(starts[0]);
    GoEmpty(&current);


    for (auto iter = current.begin(); iter != current.end(); iter++) if ((*iter)->is_acceptable) ans = 0;

    for (int i = 0; i < tested.size(); i++)
    {

        std::unordered_set <Node*> new_current;
        for (auto iter = current.begin(); iter != current.end(); iter++) for (int j = 0; j < (*iter) -> go[tested[i] - 'a' + 1].size(); j++)
            new_current.insert((*iter) -> go[tested[i] - 'a' + 1][j]);
        current = new_current;
        GoEmpty(&current);



        for (auto iter = current.begin(); iter != current.end(); iter++) if ((*iter)->is_acceptable) ans = i + 1;
    }

    if (ans >= 0) return std::to_string(ans);
    else return ("INF");
    return 0;


}


int main ()
{

    vector <string> in1;
    vector <string> in2;
    vector <string> out;

    in1.push_back("*a");
    in1.push_back("a.b");
    in1.push_back("b+a*");
    in1.push_back("ba.*cc.");
    in1.push_back("01+");
    in1.push_back("ab+*");
    in1.push_back("ab*a..*a.");
    in1.push_back("ab+c.aba.*.bac.+.+*");
    in1.push_back("acb..bab.c.*.ab.ba.+.+*a.");
    in1.push_back("ab.*");
    in1.push_back("c*");

    in2.push_back("aaab");
    in2.push_back("aa");
    in2.push_back("bb");
    in2.push_back("cca");
    in2.push_back("aaa");
    in2.push_back("aabbaa");
    in2.push_back("ababaaa");
    in2.push_back("abacb");
    in2.push_back("cb");
    in2.push_back("abababd");
    in2.push_back("ccccccccd");

    out.push_back("ERROR");
    out.push_back("ERROR");
    out.push_back("ERROR");
    out.push_back("ERROR");
    out.push_back("0");
    out.push_back("6");
    out.push_back("1");
    out.push_back("4");
    out.push_back("INF");
    out.push_back("6");
    out.push_back("8");


    int s = out.size();
    for (int i = 0; i < s; i++)
        if (Accepting(in1[i], in2[i]) != out[i]) printf("error in %d", i);

    return 0;
}


