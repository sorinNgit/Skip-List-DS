#include<bits/stdc++.h>

using namespace std;

ifstream f("Untitled2.c");
ofstream g("abce.out");

// clasele Nod si SkipList
class Nod{
public:
    int inf;
    Nod(int, int);
    Nod** next;
};

class SkipList{

    Nod* first;
    int level;
    int maxLevel;
    float k;

public:
    SkipList(int, float);
    Nod* newNode(int, int);
    int coinflipLevel();
    bool find(int);
    void print();
    void stergere(int);
    void inserare(int);

};

Nod::Nod(int inf, int level){

    this->inf = inf;
    next = new Nod * [level + 1];
    memset(next, 0, sizeof(Nod*) * (level + 1));

}

SkipList::SkipList(int maxLevel, float k){

    this->maxLevel = maxLevel;
    this->k = k;
    level = 0;
    first = new Nod(-1, maxLevel);

}

int SkipList::coinflipLevel(){

    int level = 0;
    float r = (float)rand() / RAND_MAX;
    while (level <= maxLevel && r < k) //coinflip
    {
        level++;
        r = (float)rand() / RAND_MAX;
    }

    return level;
}
Nod* SkipList::newNode(int info, int level){

    Nod* n = new Nod(info, level);
    return n;
}


void SkipList::inserare(int inf){

    int i;
    Nod* v[maxLevel + 1];
    Nod* k = first;

    memset(v, 0, sizeof(Nod*) * maxLevel + 1);

    for (i = level; i >= 0; i--){

        while (k->next[i]->inf < inf && k->next[i] != NULL)
            k = k->next[i];
        v[i] = k;
    }

    k = k->next[0];

    if (k->inf != inf || k==NULL){

        int newLevel;
        int i;
        newLevel = coinflipLevel();
        if (level<newLevel){

            for (i = level + 1; i <= newLevel; i++)
                v[i] = first;
            level = newLevel;
        }

        Nod* n = newNode(inf, newLevel);

        for (i = 0; i <= newLevel; i++){

            n->next[i] = v[i]->next[i];
            v[i]->next[i] = n;
        }

    }
}

void SkipList::stergere(int inf){

    Nod* v[maxLevel + 1];
    memset(v, 0, sizeof(Nod*) * (maxLevel + 1));

    Nod* k = first;
    int i;

    for (i = level; i >= 0; i--){

        while (k->next[i]->inf < inf && k->next[i] != NULL)
            k = k->next[i];
        v[i] = k;
    }

    k = k->next[0];

    if (k->inf == inf && k!=NULL){

        for (i = 0; i <= level; i++){

            if (v[i]->next[i] != k)
                break;
            v[i]->next[i] = k->next[i];
        }
    }

    while (first->next[level] == 0 && level>0)
        level--;
}

bool SkipList::find(int inf){

    Nod* k = first;
    int i;
    bool ok = 0;
    for (i = level; i >= 0; i--){

        while (k->next[i]->inf < inf && k->next[i])
            k = k->next[i];
    }
    k = k->next[0];

    if (k->inf == inf && k!=NULL){

        ok = 1;
    }
    return ok;
}

void SkipList::print(){

    Nod* p = first->next[0];
    while (p != NULL){

        g << p->inf << " ";
        p = p->next[0];
    }
    g << "\n";
}

int main() {
    int n;
    srand((unsigned)time(nullptr));
    f >> n;

    SkipList list(n, 0.5);

    int i, j, x;
    for (i = 0; i < n; i++) {
        f >> j;
        if (j == 1) {
            f >> x;
            list.inserare(x);
        }
        if (j == 2)
        {
            f >> x;
            list.stergere(x);
        }

        if (j == 3)
        {
            f >> x;
            g << list.find(x) << endl;
        }
    }
    list.print();
    f.close();
    g.close();
    return 0;
}
