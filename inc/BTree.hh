#include <bits/stdc++.h>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
using namespace std;
template <class T>
class BTree {
public:
  BTree(int _order) {
    root = nullptr;
    order = _order;
    Key_max = 2 * order - 1;
    Key_min = order - 1;
    Child_max = Key_max + 1;
    Child_min = Key_min + 1;
  }
  ~BTree() {
    clear(root);
  }
  bool remove(const T& key) {
    if (!find(root, key)) return 0;
    if (root->count == 1) {
      if (root->isleaf) {
        clear();
        return 1;
      } else {
        auto s1 = root->son[0];
        auto s2 = root->son[1];
        if (s1->count == Key_min && s2->count == Key_min) {
          merge(root, 0);
          deletenode(root);
          root = s1;
        }
      }
    }
    son_remove(root, key);
    return 1;
  }

  int order, Key_max, Key_min, Child_max, Child_min;
  struct Node {
    int count;
    bool isleaf;
    vector <T> val;
    vector <Node*> son;
    Node(int Child_max, int Key_max, bool t = 1, int num = 0) :
      count(num), isleaf(t) {
      son.resize(Child_max + 2);
      val.resize(Key_max + 1);
    }
  };
  Node* root;
  bool insert(const T& key) {
    if (find(root, key)) {
      return 0;
    } else {
      if (root == nullptr) {
        root = new Node(Child_max, Key_max);
      }
      if (root->count == Key_max) {
        auto nd = new Node(Child_max, Key_max);
        nd->isleaf = 0;
        nd->son[0] = root;
        split(nd, 0, root);
        root = nd;
      }
      insertNonfull(root, key);
      return 1;
    }
  }

  void clear(Node* nd) {
    if (nd != nullptr) {
      if (!nd->isleaf)
        for (int i = 0; i < nd->count; i++)
          clear(nd->son[i]);
      delete nd;
    }
  }
  bool find(Node* nd, const T& key) {
    if (nd == nullptr)   return 0;
    int pos = 0;
    while (pos < nd->count && key > nd->val[pos])    pos++;
    if (pos < nd->count && key == nd->val[pos])  return 1;
    if (nd->isleaf)    return 0;
    else return find(nd->son[pos], key);
  }
  void split(Node* pa, int sindex, Node* nd) {
    auto rs = new Node(Child_max, Key_max);
    rs->isleaf = nd->isleaf;
    rs->count = Key_min;
    for (int i = 0; i < Key_min; i++) {
      rs->val[i] = nd->val[i + Child_min];
    }
    if (!nd->isleaf) {
      for (int i = 0; i < Child_min; i++) {
        rs->son[i] = nd->son[i + Child_min];
      }
    }

    nd->count = Key_min;
    for (int i = pa->count; i > sindex; i--) {
      pa->son[i + 1] = pa->son[i];
      pa->val[i] = pa->val[i - 1];
    }
    pa->count++;
    pa->son[sindex + 1] = rs;
    pa->val[sindex] = nd->val[Key_min];
  }
  void insertNonfull(Node* nd, const T& key) {
    int num = nd->count;
    if (nd->isleaf) {
      while (num && key < nd->val[num - 1]) {
        nd->val[num] = nd->val[num - 1];
        num--;
      }
      nd->val[num] = key;
      nd->count++;
    } else {
      while (num && key < nd->val[num - 1])  num--;
      auto nnd = nd->son[num];
      if (nnd->count == Key_max) {
        split(nd, num, nnd);
        if (key > nd->val[num])
          nnd = nd->son[num + 1];
      }
      insertNonfull(nnd, key);
    }
  }
  void merge(Node* nd, int index) {
    auto s1 = nd->son[index];
    auto s2 = nd->son[index + 1];
    s1->count = Key_max;
    s1->val[Key_min] = nd->val[index];
    for (int i = 0; i < Key_min; i++)
      s1->val[i + Key_min + 1] = s2->val[i];
    if (!s1->isleaf) {
      for (int i = 0; i < Child_min; i++)
        s1->son[i + Child_min] = s2->son[i];
    }

    nd->count--;
    for (int i = index; i <= nd->count; i++) {
      nd->val[i] = nd->val[i + 1];
      nd->son[i + 1] = nd->son[i + 2];
    }
    deletenode(s2);
  }
  T getprev(Node* nd) {
    while (!nd->isleaf)
      nd = nd->son[nd->count];
    return nd->val[nd->count - 1];
  }
  T getnxtv(Node* nd) {
    while (!nd->isleaf)
      nd = nd->son[0];
    return nd->val[0];
  }
  void son_remove(Node* nd, const T& key) {
    int num = 0;
    while (num < nd->count && key > nd->val[num])    num++;
    if (num < nd->count && key == nd->val[num]) {
      if (nd->isleaf) {
        nd->count--;
        for (; num < nd->count; num++)
          nd->val[num] = nd->val[num + 1];
        return;
      } else {
        auto pre = nd->son[num];
        auto nxt = nd->son[num + 1];
        if (pre->count >= Child_min) {
          T prekey = getprev(pre);
          son_remove(pre, prekey);
          nd->val[num] = prekey;
          return;
        } else if (nxt->count >= Child_min) {
          T nxtkey = getnxtv(nxt);
          son_remove(nxt, nxtkey);
          nd->val[num] = nxtkey;
          return;
        } else {
          merge(nd, num);
          son_remove(pre, key);
        }
      }
    } else {
      auto nnd = nd->son[num];
      if (nnd->count == Key_min) {
        auto ls = num ? nd->son[num - 1] : nullptr;
        auto rs = num < nd->count ? nd->son[num + 1] : nullptr;
        if (ls && ls->count >= Child_min) {
          for (int j = nnd->count; j; j--)
            nnd->val[j] = nd->val[j - 1];
          nnd->val[0] = nd->val[num - 1];
          if (!ls->isleaf) {
            for (int j = nnd->count + 1; j; j--)
              nnd->son[j] = nnd->son[j - 1];
            nnd->son[0] = ls->son[ls->count];
          }
          nnd->count++;
          nd->val[num] = ls->val[ls->count - 1];
          ls->count--;
        } else if (rs && rs->count >= Child_min) {
          nnd->val[nnd->count] = nd->val[num];
          nnd->count++;
          nd->val[num] = rs->val[0];
          rs->count--;
          for (int j = 0; j < rs->count; j++)
            rs->val[j] = rs->val[j + 1];
          if (!rs->isleaf) {
            nnd->son[nnd->count] = rs->son[0];
            for (int j = 0; j <= rs->count; j++)
              rs->son[j] = rs->son[j + 1];
          }
        } else if (ls) {
          merge(nd, num - 1);
          nnd = ls;
        } else if (rs) {
          merge(nd, num);
        }
      }
      son_remove(nnd, key);
    }
  }
  void dumpToFile(const string& path = "cache.png", const string& type = "png") const {
    Agraph_t* g = agopen("BTree", Agdirected, nullptr);
    GVC_t* gvc = gvContext();

    function<void(Agnode_t*, Node*)> dfs = [&](Agnode_t* agfa, Node* ptr) {
      if (ptr == nullptr) return;
      Agnode_t* cur = agnode(g, nullptr, 1);
      if (agfa != nullptr) agedge(g, agfa, cur, nullptr, 1);
      agsafeset(cur, "shape", "record", "");
      ostringstream oss;
      for (int i = 0; i < ptr->count; ++i) {
        oss << " " << ptr->val[i];
      }
      oss << " ";
      // cout << oss.str() << endl;
      agsafeset(cur, "label", oss.str().c_str(), "");
      if (ptr->isleaf) return;
      for (auto each : ptr->son)
        dfs(cur, each);
    };
    dfs(nullptr, root);
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, type.c_str(), path.c_str());
    gvFreeLayout(gvc, g);
    agclose(g);
  }
};

template<typename T>
void treeDemo(BTree<T>& tr, int n, int m, const vector<T>& arr) {
  for (const auto& x : arr)
    tr.insert(x);
  tr.dumpToFile();
}

// signed main() {
//   ios_base::sync_with_stdio(false);
//   int n, m;
//   cin >> n >> m;
//   vector<int> arr;
//   for (int i = 0; i < n; i++) {
//     int a; cin >> a;
//     char ch;
//     while (~(ch = cin.get()) && ch != ',' && ch != '\n' && ch != '\r') {}
//     arr.push_back(a);
//   }
//   BTree<int> tr(m);
//   treeDemo(tr, n, m, arr);
//   tr.dumpToFile();
// }