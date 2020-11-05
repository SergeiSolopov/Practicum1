#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

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
        printf ("current %d\n", current->number);
        if (current->is_acceptable) printf("good\n");
        else printf("bad\n");
        v.pop_back();
        visited.insert (current);
        for (int i = 0; i < 27; i++) for (int j = 0; j < current -> go [i].size(); j++)
        {

            printf("%d %d %d %d\n", current->number, i, j, (current -> go [i] [j]) -> number);
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
        //printf ("current %d\n", current->number);
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
        printf ("GoEmpty current %d\n", current->number);

        v.pop_back();
        us->insert (current);
        for (int j = 0; j < current -> go [0].size(); j++)
        {
            printf("GoEmpty %d %d %d %d\n", current->number, 0, j, (current -> go [0] [j]) -> number);

            if (us->find(current -> go [0] [j]) == us->end())
            {

                us->insert(current -> go [0] [j]);
                v.push_back (current -> go [0] [j]);

            }

        }



    }
}

int main()
{

	//std::ios_base::sync_with_stdio(false);
	//std::cin.tie(nullptr);
	//std::cout.tie(nullptr);


    string str;
    std::cin >> str;

    //printf ("1111111       ");


    int nodes_num = 0;

    //printf ("sss ");
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
                printf ("ERROR");
                return 0;
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
                printf ("ERROR");
                return 0;
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
                printf ("ERROR");
                return 0;
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
            printf ("ERROR");
            return 0;
        }
    //printf("%d", starts.size());
    GoAndPrint(starts[0]);
    string tested;
    std::cin>>tested;
    int ans = - 1;
    std::unordered_set <Node*> current;
    current.insert(starts[0]);
    GoEmpty(&current);

    printf ("states ");
    for (auto iter = current.begin(); iter != current.end(); iter++) printf("%d ", (*iter) -> number);
    printf ("\n");

    for (auto iter = current.begin(); iter != current.end(); iter++) if ((*iter)->is_acceptable) ans = 0;

    for (int i = 0; i < tested.size(); i++)
    {
        printf ("new step %d\n", i);

        std::unordered_set <Node*> new_current;
        for (auto iter = current.begin(); iter != current.end(); iter++) for (int j = 0; j < (*iter) -> go[tested[i] - 'a' + 1].size(); j++)
            new_current.insert((*iter) -> go[tested[i] - 'a' + 1][j]);
        current = new_current;
        GoEmpty(&current);

        printf ("states ");
        for (auto iter = current.begin(); iter != current.end(); iter++) printf("%d ", (*iter) -> number);
        printf ("\n");

        for (auto iter = current.begin(); iter != current.end(); iter++) if ((*iter)->is_acceptable) ans = i + 1;
    }

    if (ans >= 0) printf("%d", ans);
    else printf("INF");
    return 0;

}





