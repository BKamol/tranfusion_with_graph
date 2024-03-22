#include <vector>
#include <set>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

//состояние сосудов описывается тройкой чисел
struct triple
{
    int a, b, c;

    bool operator==(const triple& other) const
    {
        return this->a == other.a && this->b == other.b && this->c == other.c;
    }

    bool operator<=(const triple& other) const
    {
        return this->a <= other.a && this->b <= other.b && this->c <= other.c;
    }

    bool operator<(const triple& other) const
    {
        return this->a < other.a && this->b < other.b && this->c < other.c;
    }

    void print() const
    {
        cout << '(' << this->a << ", " << this->b << ", " << this->c << ") ";
    }
};

//в сосудах не может быть больше воды, чем вместимость и меньше нуля
bool right_triple(triple tr, triple max)
{
    return tr <= max && tr.a >= 0 && tr.b >= 0 && tr.c >= 0;
}

//функция принимает текущее состояние сосудов и вместимость; возвращает вектор таких состояний, которые можно получить переливанием из исходного
vector<triple> neighbours(triple t, triple max)
{
    vector<triple> neighbours;
    triple probe;
    int a, b, c, diff;
    a = t.a; 
    b = t.b; 
    c = t.c;
    
    if (a < max.a)
    {
        diff = max.a - a;

        if (b >= diff)
            probe = { a+diff, b - diff, c };
        else
            probe = { a + b, 0, c };

        //probe.print();
        if (right_triple(probe, max))
            neighbours.push_back(probe);

        if (c >= diff)
            probe = { a+diff, b, c - diff };
        else
            probe = { a + c, b, 0 };

        //probe.print();
        if (right_triple(probe, max))
            neighbours.push_back(probe);
        
    }

    if (b < max.b)
    {
        diff = max.b - b;

        if (a >= diff)
            probe = { a - diff, b + diff, c };
        else
            probe = { 0, b+a, c };

        //probe.print();
        if (right_triple(probe, max))
            neighbours.push_back(probe);


        if (c >= diff)
            probe = { a, b+diff, c-diff };
        else
            probe = { a , b+c, 0 };

        //probe.print();
        if (right_triple(probe, max))
            neighbours.push_back(probe);
    }

    if (c < max.c)
    {
        diff = max.c - c;

        if (b >= diff)
            probe = { a, b-diff, c+diff };
        else
            probe = { a , 0, c+b };

        //probe.print();
        if (right_triple(probe, max))
            neighbours.push_back(probe);


        if (a >= diff)
            probe = { a - diff, b, c +diff };
        else
            probe = { 0 , b, c + a };

        //probe.print();
        if (right_triple(probe, max))
            neighbours.push_back(probe);
    }

    return neighbours;
}

//модификация bfs
vector<triple> bfs(triple initial_state, triple max)
{
    vector<triple> visited;
    queue<triple> q;
    vector<triple> ns;
    triple t;
    visited.push_back(initial_state);
    q.push(initial_state);
    
    //мы будем перебирать все непроверенные состяния, в которые можно попасть из начального по очереди, и если попадется нужное, то задача имеет решение, иначе не имеет
    while (!q.empty())
    {
        t = q.front();
        q.pop();

        ns = neighbours(t, max);
        for (auto& n : ns)
        {
            if (n.b == 2 || n.c == 2)
            {
                visited.push_back(n);
                return visited; //если нашли вершину, у которой второй или последний сосуд имеет ровно 2 литра воды, то задача решена
            }
            if (find(visited.begin(), visited.end(), n) == visited.end())
            {
                q.push(n);
                visited.push_back(n);
            }
        }
    }

    return {};
}

int main()
{
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    triple max = { n1, n2, n3 };

    triple initial_state = { 0, n2, n3 };

    /*vector<triple> ns = neighbours(initial_state, max);
    cout << endl;
    for (auto& n : ns)
        n.print();*/

    vector<triple> visited = bfs(initial_state, max);
    for (auto& t : visited)
        t.print();
}
