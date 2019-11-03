struct lct {
    bool tree_rooted;
    struct node {
        node *l, *r; // сыновья
        node *p; // корень
        bool flip; // flip сыновей
        ll depth; // размер поддерева в splay
        ll sz; // размера поддерева
        ll lz; // проталкивание в splay
        ll label; // номер вершины
        node() {
            l = r = p = nullptr;
            flip = false;
            lz = 0;
            sz = 1;
        }
    };
    node *T;
    lct(ll n, bool tree = false) {
        T = new node[n] ;
        for (ll i = 0; i < n; i++) {
            T[i].label = i, T[i].sz = 1;
        }
        tree_rooted = tree; // конструктор
    }
    void rest(ll n) {
        node *u = &T[n];
        u->label = n;
        u->l = u->r = u->p = nullptr;
        u->flip = false;
        u->lz = 0;
        u->sz = 1;
        u->depth = 0;
    }
    inline void lazy_push(node *u) { // проталкивание в splay
        if (!tree_rooted && u->flip) {
            u->flip = false ;
            swap(u->l, u->r) ;
            if (u->l != nullptr) {
                u->l->flip ^= 1;
            }
            if (u->r != nullptr) {
                u->r->flip ^= 1;
            }
        }
        if (u->l != nullptr) {
            u->l->lz += u->lz;
        }
        if (u->r != nullptr) {
            u->r->lz += u->lz;
        }
        u->sz += u->lz;
        u->lz = 0;
    }
    inline void update(node *u) { //обновляем значение веришну в splay
        u->depth = 1 ;
        if (u->l != nullptr) {
            u->depth += u->l->depth;
        }
        if (u->r != nullptr) {
            u->depth += u->r->depth;
        }
    }
    inline ll is_root(node *u) { // является ли вершина корнем splay дерева
        return u->p == nullptr || (u->p->l != u && u->p->r != u) ;
    }
    void rotate(node *u) { //zig zig-zig zig-zag
        node *p = u->p;
        if (u == p->l) {
            p->l = u->r ;
            if (p->l != nullptr) {
                p->l->p = p ;
            }
            u->r = p;
        } else {
            p->r = u->l;
            if (p->r != nullptr) {
                p->r->p = p;
            }
            u->l = p;
        }
        u->p = p->p;
        p->p = u;
        if (u->p != nullptr) {
            if (p == u->p->l) {
                u->p->l = u;
            }
            else if (p == u->p->r) {
                u->p->r = u;
            }
        }
        update(p);
        update(u);
    }
    void splay(node* u) {//проталакивание вершины в корень в splay дереве
        while (!is_root(u)) {
            node* p = u->p;
            if (!is_root(p)) {
                lazy_push(p->p);
            }
            lazy_push(p);
            lazy_push(u);
            if (!is_root(p)) {
                if ((p->l == u) != (p->p->l == p)) {
                    rotate(u);
                }
                else {
                    rotate(p);
                }
            }
            rotate(u);
        }
        lazy_push(u);
        update(u);
    }
    node* access(node* v) {//создает splay дерево содержащее путь от вершины до корня и становится коренем splay дерева
        node* last = nullptr;
        for (node* u = v ; u != nullptr; u = u->p) {
            splay(u);
            u->r = last;
            update(u);
            last = u;
        }
        splay(v);
        return last;
    }
    void reroot(node *v) { //переподвешивание дерева
        access(v);
        v->flip ^= 1;
    }
    node* find_root(node *u) { //возвращает корень дерева
        access(u);
        while (u->l != nullptr) {
            u = u -> l;
        }
        splay(u);
        return u;
    }
    bool conn(ll x, ll y) { //связаны ли две вершины
        node *u = &T[x], *v = &T[y];
        if (u == v) {
            return true;
        }
        access(u);
        access(v);
        return u->p != nullptr;
    }
    void link(ll x , ll y) { //добавить ребро x -> y
        node *v = &T[x], *u = &T[y];
        if (tree_rooted) {
            access(u);
        } else {
            reroot(u);
        }
        if (tree_rooted) {
            v->l = u;
        }
        u->p = v;
        update(v);
        u->sz += v->sz;
        if  (u->l != nullptr) {
            u->l->lz += v->sz;
        }
    }
    void cut(ll x) { // отрезать ребро x -> parent[x]
        node *u = &T[x];
        access(u) ;
        assert(u->l != nullptr);
        u->l->lz -= u->sz;
        u->l->p = nullptr;
        u->l = nullptr;
        update(u);
    }
    void cut(ll x , ll y) { // отрезать ребро x -> y
        node *u  = &T[x] ;
        if (!tree_rooted) {
            reroot(u);
        }
        cut(y);
    }
    ll lca(ll x, ll y) { // lca x, y
        node *u  = &T[x], *v = &T[y];
        access(u);
        return access(v)->label;
    }
    ll depth(ll x) { // глубина x
        node *u = &T[x] ;
        access(u);
        return u->depth - 1;
    }
    long long SZ(ll x) { // размер поддерева x
        node *u = &T[x] ;
        access(u);
        lazy_push(u);
        return u->sz;
    }
    void makeroot(ll u) { // переподвешивание
        reroot(&T[u]);
    }
    ll root(ll u) { // корень дерева
        node *x = &T[u];
        access(x);
        while (x->l != nullptr) {
            x = x->l;
        }
        splay(x);
        return x->label;
    }
 
    /*
     * работает, как с обычным декартовым деревом по неявному ключу
     */
 
    ll solve(int x, int r) {
        node *v = &T[x];
        access(v);
        // DO SMTH WITH V
    }
};
