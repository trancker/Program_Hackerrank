//Walking the approximate Longest Path


#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <algorithm>
#include <iterator>
#include <array>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <cassert>
#include <bitset>
#include <queue>
#include <stack>
#include <chrono>
#include <sys/resource.h>
    

using namespace std;


template <class T> 
std::ostream& operator<<(std::ostream& os, const vector<T>& rhs)
{
	for (const auto& x : rhs)
		os << x << " ";
	return os;
}

template <class T> 
std::ostream& operator<<(std::ostream& os, const vector<vector<T>>& A)
{
	os << endl;
	for (int i = 1; i < A.size(); ++i)
		os << i << ": [" << A[i] << "]" <<endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const map<long,long>& t)
{
	for (auto p : t)
		os << p.first << "^" << p.second << "*";
	os << endl;
	return os;
}


template <class T> 
T max(const vector<T>& v)
{
// 	if (v.size() == 0)
// 		cout << "SHIT!" << endl;
	T m = v[0];
	size_t sz = v.size();
	for (size_t i = 0; i < sz; ++i)
	{
		if (v[i] > m)
			m = v[i];
	}
	return m;
}

template <class T> std::vector<T> range (T n) 
{
	std::vector<T> toReturn(n, 0);
	for (T i = 1; i < n ; ++i)
		toReturn[i] = i;
	return toReturn;
}

typedef std::chrono::time_point<std::chrono::high_resolution_clock> clockt;

inline double diffclockt(clockt a, clockt b)
{
	
	const double t = 0.000001;
	return std::chrono::duration_cast<std::chrono::microseconds>(a-b).count()*t;
}

class Chronometer
{
public:
	Chronometer() : m_timer(std::chrono::high_resolution_clock::now()) {}
	
	double Reset()
	{
		auto tlast = m_timer;
		m_timer = std::chrono::high_resolution_clock::now();
	
		return diffclockt(m_timer, tlast);
	}
	
	double Peek() const
	{
		auto tnow = std::chrono::high_resolution_clock::now();
	
		return diffclockt(tnow, m_timer);
	}
	
	std::chrono::time_point<std::chrono::high_resolution_clock> m_timer;
};

inline double TimeFromStart()
{
	static Chronometer C;
	return C.Peek();
}

inline std::default_random_engine & random_engine()
{
	static std::default_random_engine e{};
	return e;
}

inline void randomize()
{
	static std::random_device rd{};
	random_engine().seed(rd());
}

inline bool probability_of_true(double p)
{
	static std::bernoulli_distribution d(p);
	return d(random_engine());
}

inline double random_real( double from, double upto )
{
	static std::uniform_real_distribution<> d{};
	using parm_t = decltype(d)::param_type;
	return d( random_engine(), parm_t{from, upto} );
}

inline int random_integer(int from, int to)
{
	static std::uniform_int_distribution<> d{};
	using parm_t = decltype(d)::param_type;
	return d( random_engine(), parm_t{from, to-1} );
}

inline int random_give_priority_to_primeros(int a, int b)
{
	int n = b-a;
	random_engine();
	int t = random_integer(0,(n*(n+1))/2);
	int u = n-1;
	int i = n-1;
	int toreturn = a;
	while (u < t && i > 0)
	{
		u += i;
		--i;
		++toreturn;
	}
	return toreturn;
}


using node_t = int;
const node_t INVALID_NODE = -1;

using weight_t = int;

// something larger than weight_t for when you have that weight_t doesn't properly hold a sum of weight_t
using sumweight_t = int;
// const sumweight_t INF = 200000000;

struct NeighborNode
{
	explicit NeighborNode() : node(INVALID_NODE) {} 
	
	explicit NeighborNode(node_t v, weight_t w) : node(v) {}
	
	inline operator node_t() const
	{
		return node;
	}
	
	weight_t Weight() const
	{
// 		return weight;
		return 1;
	}
	
	node_t node;
// 	weight_t weight{1}; //comment 
};

class Path
{
public:
    Path(size_t n) : m_path(), m_explored(n), m_value(0) {}
    Path(size_t n, node_t initialnode) : m_path(), m_explored(n), m_value(0) 
    {
        emplace_back(initialnode,0);
    }
    const deque<NeighborNode>& get_path() const { return m_path; }
    inline operator const deque<NeighborNode>&() const { return m_path; }
//     inline operator vector<NeighborNode>&()  { return m_path; }
    long value() const { return m_value; }
    long cost() const { return m_value; }
    long weight() const { return m_value; }
    
    bool is_node_in_path(node_t v) const
	{
		return m_explored[v] > 0;
	}
    
    void push_back(const NeighborNode& v)
    {
//         assert(v.weight == 0 || !m_path.empty());
        assert(v < m_explored.size());

        ++m_explored[v];
//         m_value += v.weight;
        m_path.push_back(v);
    }
    
    void emplace_back(node_t node, weight_t weight = 1)
    {
        assert(weight == 0 || !m_path.empty());
        assert(node < m_explored.size());
        ++m_explored[node];
        m_value += weight;
        m_path.emplace_back(node,weight);
    }
    
    void push_front(NeighborNode v)
	{
//         swap(m_path.front().weight,v.weight);
        assert(!m_path.empty() && "Use push_back when it's empty");
        assert(v < m_explored.size());
//         m_path.front().weight = v.weight;
        m_path.emplace_front(v,0);
		m_value += v.Weight();
        ++m_explored[v];
	}
	
    void emplace_front(node_t node, weight_t weight = 1)
	{
//         auto w = m_path.front().weight;
        assert(!m_path.empty() && "Use emplace_back when it's empty");
        assert(node < m_explored.size());
// 		m_path.front().weight = weight;
		m_path.emplace_front(node,0);
		m_value += weight;
        ++m_explored[node];
	}
    
    void pop_back()
    {
        assert(!m_path.empty() && "Can't pop when it's already empty!");
        auto v = m_path.back();
        --m_explored[v];
        m_value -= v.Weight();
        m_path.pop_back();
    }
    
    void pop_front()
    {
        assert(!m_path.empty() && "Can't pop when it's already empty!");
        auto v = m_path.front();
        --m_explored[v];
        m_path.pop_front();
        m_value -= m_path.front().Weight();
//         m_path.front().weight = 0;
    }
    
    void clear()
    {
        m_value = 0;
//         m_explored = vector<char>(m_explored.size(),0);
        auto n = m_explored.size();
        m_explored.clear();
        m_explored.resize(n,0);
        m_path.clear();
    }
    
    NeighborNode operator[](size_t i) const { return m_path[i]; }
    NeighborNode& operator[](size_t i) { return m_path[i]; }
    
    bool empty() const
    {
        return m_path.empty();
    }
    
    size_t size() const
    {
        return m_path.size();
    }
    
    template <class Compare>
    NeighborNode first_not_explored_binary(const vector<NeighborNode>& Nodes, node_t start, Compare comp) const
    {
        auto it = std::upper_bound(Nodes.begin(), Nodes.end(), start, comp);
    // 	++it;
        while (it != Nodes.end() && m_explored[*it])
            ++it;
        if (it == Nodes.end())
            return NeighborNode(INVALID_NODE,0);
        return *it;
    }
    
    NeighborNode first_not_explored_binary(const vector<NeighborNode>& Nodes, node_t start) const
    {
        return first_not_explored_binary(Nodes,start,std::less<node_t>());
    }
    
    NeighborNode first_not_explored(const vector<NeighborNode>& Nodes, node_t start) const
    {
        bool seenstart = false;
        for (auto x : Nodes)
        {
            if (x == start)
            {
                seenstart = true;
                continue;
            }	
            
            if (seenstart && !m_explored[x])
                return x;
        }
        return NeighborNode(INVALID_NODE,0);
    }
    
    NeighborNode first_not_explored(const vector<NeighborNode>& Nodes) const
    {
        for (auto x : Nodes)
        {
            if (!m_explored[x])
                return x;
        }
        return NeighborNode(INVALID_NODE,0);
    }
    
    NeighborNode back() const
    {
        return m_path.back();
    }
    
    NeighborNode front() const
    {
        return m_path.front();
    }
    
    
private:
    deque<NeighborNode> m_path;
    vector<char> m_explored;
//     vector<bool> m_explored;
    long m_value;
public:
    const decltype(m_path)& data() const { return m_path; }

};

// inline std::ostream& operator<<(std::ostream& os, const Path& P)
// {
//     auto B = P.get_path();
//     for (size_t i = 0; i < B.size()-1; ++i)
// 	{
// 	}
// 	os << P.get_digraph()->get_vertex_name(B.back()) << endl;
// 	return os;
// }

struct Edge
{
	Edge() : from(INVALID_NODE), to(INVALID_NODE), weight(0) {}
	Edge(node_t f, node_t t, weight_t w = 1) : from(f), to(t), weight(w) {}
	node_t operator[](bool i)
	{
		if (i)
			return to;
		return from;
	}
	node_t from;
	node_t to;
	weight_t weight;
};


class PseudoTopoOrder;

using ParamType = std::array<double, 8>;


class DiGraph
{
public:
    explicit DiGraph(node_t numberOfNodes);
    explicit DiGraph(const vector<string>& vertex_names);

	//		Graph modification functions
	void add_edge(node_t from, node_t to, weight_t weight = 1);
	void add_edge(const string& from, const string& to, weight_t weight = 1);
	
	// Find connected components, heuristics, etc.
	void process(); // WARNING! Since it removes and renames nodes, after "processing" your nodes might have been renamed!

	// Get Graph Info
	node_t get_size() const { return m_n; }
	node_t num_vertices() const { return m_n; }
	size_t num_edges() const;
    
    const string& get_vertex_name(node_t i) const { return m_node_names[i]; }
    node_t get_vertex_index(const string& name) const 
    { 
        auto it = m_namemap.find(name);
        return (*it).second; 
        
    }
    const vector<string>& get_vertex_names() const { return m_node_names; } 
    
    void set_parameters(const ParamType& new_params) 
    {
        m_params = new_params;
        heuristic_processing();
    }
    
    static DiGraph ReadFromStdin(int n, int m);
    
	int rank_out(node_t node) const { return 0; }
	int rank_in(node_t node) const { return 0; }
	
	inline const vector<NeighborNode>& outneighbors(node_t n) const { return m_outgraph[n]; }
	inline const vector<NeighborNode>& inneighbors(node_t n) const { return m_ingraph[n]; }
// 	inline const weight_t edge_value(node_t from, node_t to) const { return m_edge_values(from,to); }
	
	// This is the order in which the outneighbors are sorted
	inline bool ex_compare(node_t a, node_t b) const { return m_basic_topological_ordering_inverse[a] < m_basic_topological_ordering_inverse[b]; }

	// This is the order in which the outneighbors are sorted
	inline bool in_compare(node_t a, node_t b) const { return m_basic_topological_ordering_inverse_in[a] < m_basic_topological_ordering_inverse_in[b]; }
	
	// Functions related to paths
	
	void dfs_search_path_forward(Path& P, double maxnumseconds) const;
	void dfs_search_path_reverse(Path& P, double maxnumseconds) const;
	
	Path dfs_search_path_forward(node_t start, double maxnumseconds) const;
	Path dfs_search_path_reverse(node_t start, double maxnumseconds) const;

	Path dfs_search(double maxnumsecondswithoutimprovement) const;
    void pto_search(Path& A, double maxnumseconds) const;
    
	PseudoTopoOrder get_random_pseudotopological_order() const;
	//Paths
	Path FindLongestSimplePath(double numseconds);
	Path FindLongestSimplePathPureDFS(double numseconds);
	
	bool TopologicalLessThan(node_t a, node_t b) const { return m_basic_topological_ordering_inverse[a] < m_basic_topological_ordering_inverse[b]; }
	
	static DiGraph CreateRandomDiGraph(int n, double p);
	static DiGraph CreateRandomWeightedDiGraph(int n, double p, weight_t minweight, weight_t maxweight);
	
private:
    // Utils for creating the graph
	void remove_bad_nodes();
	void remove_nodes(vector<node_t>& toRemove);
	
	DiGraph with_nodes_removed(vector<node_t>& toRemove) const;
	
	void heuristic_processing();
	double get_heuristic_out(node_t node);
	double get_heuristic_in(node_t node);
	
// 	void branch_and_bound();
	
	// Utils to find connected components
// 	void find_weakly_connected_components();
	void find_strongly_connected_components();
	void find_strongly_connected_componentsBOOST();
	void topo_fill_order( node_t v, vector< char >& visited, stack< node_t >& Stack ); 
	void topo_fill_order( node_t v, vector< char >& visited, vector< node_t >& Stack ); 
    void DFSUtil( node_t v, vector< bool >& visited );
    void DFSUtilReversed( node_t v, vector< char >& visited, int current );
//     void DFSUtilWeak(node_t start, int minvalidcoloring);
	
protected:
	// DiGraph insides
	node_t m_n;
	vector<vector<NeighborNode>> m_outgraph;
	vector<vector<NeighborNode>> m_ingraph;

private:
	bool m_processed;
	//Heuristics
	vector<double> m_heuristic_out;
	vector<double> m_heuristic_in;
	
	vector<node_t> m_basic_topological_ordering;
	vector<node_t> m_basic_topological_ordering_in;
	vector<node_t> m_basic_topological_ordering_inverse;
	vector<node_t> m_basic_topological_ordering_inverse_in;
	
    vector<string> m_node_names;
    unordered_map<string, node_t> m_namemap;
    
    
    ParamType m_params {{-43,31,11,58,-4,23,43,45}};
//     ParamType m_params {{1,4,16,64,1,4,16,64}};
    
	friend class PseudoTopoOrder;
};

DiGraph DiGraph::ReadFromStdin(int n, int m)
{
	DiGraph D(n);
	for (int i = 0; i < m; ++i)
	{
		int x,y;
		cin >> x >> y;
		--x;
		--y;
		D.add_edge(x,y);
		D.add_edge(y,x);
	}
	return D;
}


std::ostream& operator<<(std::ostream& os, const DiGraph& M);
std::ostream& operator<<(std::ostream& os, const ParamType& a);



void ExpandGreedyBack(const DiGraph& G, Path& P);


void ExpandGreedyFront(const DiGraph& G, Path& P);

template <class Compare>
bool dfs_outnext(const DiGraph& G, Path& P, Compare comp)
{
    auto lastNode = P.back();
    
    auto Neighs = &G.outneighbors(lastNode);

    auto t = P.first_not_explored(*Neighs);

    while (t == INVALID_NODE && P.size() > 1) //this means all nodes in Neigh have been explored
    {
        lastNode = P.back();
        P.pop_back();
        int father = P.back();
        Neighs = &G.outneighbors(father);
        t = P.first_not_explored_binary(*Neighs,lastNode, comp);
    }
    if (t == INVALID_NODE)
        return false; // this means we have finished DFS!!
    P.push_back(t);
	ExpandGreedyBack(G,P);
    return true;
}

template <class Compare>
bool dfs_innext(const DiGraph& G, Path& P, Compare comp)
{
    auto firstNode = P.front();
    
    auto Neighs = &G.inneighbors(firstNode);

    auto t = P.first_not_explored(*Neighs);

    while (t == INVALID_NODE && P.size() > 1) //this means all nodes in Neigh have been explored
    {
        firstNode = P.front();
        P.pop_front();
        int father = P.front();
        Neighs = &G.inneighbors(father);
        t = P.first_not_explored_binary(*Neighs,firstNode, comp);
    }
    if (t == INVALID_NODE)
        return false; // this means we have finished DFS!!
    P.push_front(t);
	ExpandGreedyFront(G,P);
    return true;
}


class PseudoTopoOrder
{
public:
	PseudoTopoOrder(const DiGraph& m, const vector<node_t>& ts, const vector<node_t>& tsi) : 
	pto(ts), 
	pto_inverse(tsi), 
	dynamic_programming(ts.size(),0), 
	best_index(0), 
	first_unknown(0),
	path_filled(false),
	m_path(),
	m_parent(m) {}

	size_t size() const { return dynamic_programming.size(); }
	
	inline void set(int i, int v)
	{
		pto[i] = v;
		pto_inverse[v] = i;
		AnnounceModification(i);
	}

	inline void transpose(int i, int j)
	{
		swap(pto[i],pto[j]);
		pto_inverse[pto[i]] = i;
		pto_inverse[pto[j]] = j;
		AnnounceModification(i);
		AnnounceModification(j);
	}
	
	void transfer(int a, int b, int c, int d, int h);
	
	void reverse_order(int a, int b);
	
	Path get_path();

	void shuffle(int  a, int b); // this assumes already a < b and they belong to the same component
	sumweight_t  Value() { FillDP(); return dynamic_programming[best_index]; }
	void apply(const Path& P);
	void apply(const Path& P, int u, int v);
// 	void random_apply(const Path& P);
	
	bool eXtreme_edge_opener();
	
	void open_edges_until_no_more_improvement_found(double maxnumseconds);
	
	void open_edge();
	
	void randomize();
	
	// sorts range from a to b (must be same scc) according to a heuristic so as to maximize the improvement chance.
	void heuristic_sort(int a, int b, int numtimes);
	int get_outneighbor_in_range(int a, int b, node_t node);

private:
	void FillDP();
	void FillPath();
	void RecalcTopoInverse();
	
	inline void AnnounceModification(node_t i) { if  (i < first_unknown) first_unknown = i; path_filled = false; }
	inline void transpose_na(int i, int j)
	{
		swap(pto[i],pto[j]);
		pto_inverse[pto[i]] = i;
		pto_inverse[pto[j]] = j;
	}
	
	inline void set_na(int i, int v)
	{
		pto[i] = v;
		pto_inverse[v] = i;
	}
	
	vector<node_t> pto;
	vector<node_t> pto_inverse;
	vector<sumweight_t> dynamic_programming;
	int best_index;
	int first_unknown;
	bool path_filled;
	vector<NeighborNode> m_path; //Path is filled with indices in REVERSE ORDER
	const DiGraph& m_parent;
};



void PseudoTopoOrder::shuffle(int a, int b)
{
	random_shuffle(pto.begin()+a, pto.begin()+b);
	for (int i = a; i < b; ++i)
	{
		pto_inverse[pto[i]] = i;
	}
	AnnounceModification(a);
}

void PseudoTopoOrder::RecalcTopoInverse()
{
	int n = pto.size();
	for (int i = 0; i < n; ++i)
	{
		pto_inverse[pto[i]] = i;
	}
	AnnounceModification(0);
}

void PseudoTopoOrder::apply(const Path& P)
{
	auto it = P.get_path().begin();
	int fu = -1;
	int n = pto.size();
	for (int i = 0; i < n; ++i)
	{
		int x = pto[i];
		if (P.is_node_in_path(x))
		{
			if (fu == -1)
				fu = i;
			pto[i] = *it;
			pto_inverse[*it] = i;
			++it;
		}
	}
	AnnounceModification(fu);
}

void PseudoTopoOrder::apply(const Path& P, int u, int v)
{

	vector<int> indexesofPbetweenuandv;
	vector<int> nodesofPbetweenuandv;
	for (auto x : P.get_path())
	{
		int index = pto_inverse[x];
		if (u <= index && index < v)
		{
			indexesofPbetweenuandv.push_back(index);
			nodesofPbetweenuandv.push_back(x);
		}
	}
	sort(indexesofPbetweenuandv.begin(), indexesofPbetweenuandv.end());
	int i = 0;
	for (auto p : indexesofPbetweenuandv)
	{
		pto[p] = nodesofPbetweenuandv[i];
		pto_inverse[pto[p]] = p;
		++i;
	}
	AnnounceModification(u);
}


Path PseudoTopoOrder::get_path()
{
	FillPath();
	Path P(size());
	for (auto i : m_path)
	{
		P.emplace_front(pto[i],i.Weight());
	}
	return P;
}

void PseudoTopoOrder::FillDP()
{
	int n = pto.size();
	int best_val = 0;
	if (best_index < first_unknown)
		best_val = dynamic_programming[best_index];
	
	for ( ; first_unknown < n; ++first_unknown)
	{
		int u = pto[first_unknown];
		dynamic_programming[first_unknown] = 0;
		
		auto& neigh = m_parent.inneighbors(u);
		for (auto v : neigh)
		{
			auto j = pto_inverse[v];
			if (first_unknown < j) // should be ignored
				continue;
			auto candidate = dynamic_programming[j] + v.Weight();
			if (candidate > dynamic_programming[first_unknown])
			{
				dynamic_programming[first_unknown] = candidate;
				if (candidate > best_val)
				{
					best_val = candidate;
					best_index = first_unknown;
				}
			}
		}
	}
}

void PseudoTopoOrder::randomize()
{
	random_shuffle(pto.begin(), pto.end());
	for (int i = 0; i < pto.size(); ++i)
	{
		pto_inverse[pto[i]] = i;
	}
	
	AnnounceModification(0);
}

void PseudoTopoOrder::transfer(int a, int b, int c, int d, int h)
{
	if (h == b-a)
	{
		return;
	}
	
	while (h > b-a) // we must transfer from end to start
	{
		transpose(b,c);
		++b;
		++c;
	}
	
	
	while (h < b-a) // we must transfer from start to end
	{
		--b;
		--c;
		transpose(b,c);
	}
}

void PseudoTopoOrder::reverse_order(int a, int b)
{
	std::reverse(pto.begin()+a, pto.begin()+b);
	for (int i = a; i < b; ++i)
	{
		pto_inverse[pto[i]] = i;
	}
	AnnounceModification(a);
}

void PseudoTopoOrder::heuristic_sort(int a, int b, int numtimes)
{
	if (a == b)
		return;
	for (int r = b-1; r >= a; --r)
	{
		node_t node = pto[r];
		int iu = get_outneighbor_in_range(a,r,node);
		if (iu != -1)
			transpose(iu,r);
	}
	for (int i = 0; i < numtimes; ++i)
	{
		int r = rand()%(b-a)+a;
		node_t node = pto[r];
		int iu = get_outneighbor_in_range(a,r,node);
		if (iu != -1)
			transpose(iu,r);
	}
}

int PseudoTopoOrder::get_outneighbor_in_range(int a, int b, node_t node)
{
	for (auto u : m_parent.outneighbors(node))
	{
		int iu = pto_inverse[u];
		if (a <= iu && iu < b)
			return iu;
	}
	return -1;
}

bool PseudoTopoOrder::eXtreme_edge_opener()
{
	auto oldval = Value();
	FillPath();

// 	for (const auto& x : m_parent.big_scc())
// 	{
		int a = 0;
		int d = pto.size();
// 		if (d - a < 5)
// 			continue;
		
		// true true true *false false
		auto f = std::partition_point(m_path.rbegin(), m_path.rend(), [this,a](node_t i) -> bool
		{
			return i < a;
		});

		int aa = a;
		while (*f < d && f != m_path.rend())
		{
			if (*f != aa)
				transpose(aa,*f);
			++f;
			++aa;
		}
		
		int c = d;
		int b = aa;
		
		auto order = range<int>(b-a+1);
		random_shuffle(order.begin(), order.end());
		shuffle(b,c);
		for (auto h : order)
		{
			transfer(a,b,c,d,h);
			int total = b-a + d-c;
			b = a+h;
			c = d-(total-h);
			heuristic_sort(b,c,10000);
			if (Value() > oldval)
			{
				FillPath();
				return true;
			}
		}
// 	}
	FillPath();
	return false;
}

void PseudoTopoOrder::open_edges_until_no_more_improvement_found(double maxnumseconds)
{
	Chronometer C;
	while (C.Peek() < maxnumseconds)
	{
		eXtreme_edge_opener();
	}
}


void PseudoTopoOrder::FillPath()
{
	if (path_filled)
		return;
	m_path.clear();
	FillDP();
	auto m = Value();
	weight_t currweight = 0;
	int a = best_index;
	path_filled = true;

	while (true)
	{
		bool found = false;
		node_t u = pto[a];
		m_path.emplace_back(a,currweight);
		for (auto v : m_parent.inneighbors(u))
		{
			node_t b = pto_inverse[v];
			if (b > a)
				continue;
			if (dynamic_programming[b] == dynamic_programming[a] - v.Weight())
			{
				a = b;
				m = dynamic_programming[b];
				currweight = v.Weight();
				found = true;
				break;
			}
		}
		if (!found)
		{
			return;
		}
	}
}


DiGraph::DiGraph(node_t numNodes) :
			m_n(numNodes),
			m_outgraph(numNodes),
			m_ingraph(numNodes),
			m_processed(false),
			m_heuristic_out(),
			m_heuristic_in(),
			m_basic_topological_ordering(),
			m_basic_topological_ordering_in(),
			m_basic_topological_ordering_inverse(),
			m_basic_topological_ordering_inverse_in(),
			m_node_names(numNodes),
			m_namemap()
{
	for (node_t i = 0; i < numNodes; ++i)
    {
        m_node_names[i] = to_string(i);
        m_namemap[to_string(i)] = i;
    }
    
}

DiGraph::DiGraph(const vector<string>& vnames) :
			m_n(vnames.size()),
			m_outgraph(vnames.size()),
			m_ingraph(vnames.size()),
			m_processed(false),
			m_heuristic_out(),
			m_heuristic_in(),
			m_basic_topological_ordering(),
			m_basic_topological_ordering_in(),
			m_basic_topological_ordering_inverse(),
			m_basic_topological_ordering_inverse_in(),
			m_node_names(vnames),
			m_namemap()
{
	for (node_t i = 0; i < vnames.size(); ++i)
    {
        m_namemap[vnames[i]] = i;
    }
    
}

void DiGraph::add_edge(node_t from, node_t to, weight_t weight)
{
// 	if (m_edge_values(from,to) == 0)
// 	{
		m_outgraph[from].emplace_back(to,weight);
		m_ingraph[to].emplace_back(from,weight);
// 	}
// 	m_edge_values(from,to) = weight;
	m_processed = false;
}

void DiGraph::add_edge(const string& from, const string& to, weight_t weight)
{
    add_edge(m_namemap[from],m_namemap[to],weight);
}


void DiGraph::process()
{
	if (!m_processed)
	{
		heuristic_processing();
		
		m_processed = true;
	}
}

Path DiGraph::dfs_search(double mnswi) const
{
	Chronometer C;
	Path A = dfs_search_path_forward(m_basic_topological_ordering[0],mnswi);
	for (int i = 1; i < min(4,num_vertices()); ++i)
	{
		Path P = dfs_search_path_forward(m_basic_topological_ordering[i],mnswi);
		if (P.value() > A.value())
			A = P;
	}
    return A;
}


Path DiGraph::FindLongestSimplePath(double numseconds)
{
    Chronometer C;
	process();
	
	double dfstime = 0.02 + numseconds/20.0; 
	
	Path best = dfs_search(dfstime);
// 	double timeleft = numseconds-C.Peek();
	
	
// 	pto_search(best,timeleft);
	
	return best;
}

void DiGraph::pto_search(Path& A, double maxnumseconds) const
{
	Chronometer C;
	
    PseudoTopoOrder PTO = get_random_pseudotopological_order();
	PTO.apply(A);
	
	PTO.open_edges_until_no_more_improvement_found(maxnumseconds);
	
	
    if (A.value() < PTO.Value())
        A = PTO.get_path();
	
	
}
size_t DiGraph::num_edges() const
{
	size_t toReturn = 0;
	for (node_t i = 0; i < m_n; ++i)
	{
		toReturn += m_outgraph[i].size();
	}
	return toReturn;
}


void DiGraph::dfs_search_path_forward(Path& P, double maxnumseconds) const
{
	ExpandGreedyBack(*this,P);
	
	Chronometer C;
	Path Q = P;
	auto comp = [this](node_t a, node_t b)
	{
		return ex_compare(a,b);
	};
	while (C.Peek() < maxnumseconds && dfs_outnext(*this,Q,comp))
	{
		if (Q.value() > P.value())
		{
			P = Q;
			C.Reset();
		}
	}
}

void DiGraph::dfs_search_path_reverse(Path& P, double maxnumseconds) const
{
	ExpandGreedyBack(*this,P);
	
	Chronometer C;
	Path Q = P;
	auto comp = [this](node_t a, node_t b)
	{
		return in_compare(a,b);
	};
	while (C.Peek() < maxnumseconds && dfs_innext(*this,Q,comp))
	{
		if (Q.value() > P.value())
		{
			P = Q;
			C.Reset();
		}
	}
}

Path DiGraph::dfs_search_path_forward(node_t start, double maxnumseconds) const
{
	Path P(num_vertices(),start);
	dfs_search_path_forward(P,maxnumseconds);
	return P;
}

Path DiGraph::dfs_search_path_reverse(node_t start, double maxnumseconds) const
{
	Path P(num_vertices(),start);
	dfs_search_path_reverse(P,maxnumseconds);
	return P;
}

void DiGraph::heuristic_processing()
{
	m_heuristic_out.resize(m_n,0);
	m_heuristic_in.resize(m_n,0);
	
	// 	double maxtime = 0.2/n;
	
// 	#pragma omp parallel for
	for (node_t i = 0; i < m_n; ++i)
	{
		m_heuristic_out[i] = get_heuristic_out(i);
		m_heuristic_in[i] = get_heuristic_in(i);
	}
	
	m_basic_topological_ordering = range<node_t>(m_n);
	
	for (auto a : m_basic_topological_ordering)
	{
		if (a >= m_n) cout << "SUPER ERROR!" << endl;
		assert(a < m_n);
	}
	
	sort (m_basic_topological_ordering.begin(), m_basic_topological_ordering.end(), [this](node_t a, node_t b) -> bool
	{
		assert(a < m_n && b < m_n);
		if (rank_out(a) == rank_out(b))
		{
			if (m_heuristic_out[a] == 0)
			{
				return false;
			}
			if (m_heuristic_out[b] == 0)
			{
				return true;
			}
			
			if (m_ingraph[a].size() == 1 )
				return true;
			if (m_ingraph[b].size() == 1)
				return false;
			return m_heuristic_out[a] < m_heuristic_out[b];
		}
		
		
		return rank_out(a) > rank_out(b);
		
	});
	
	m_basic_topological_ordering_inverse.resize(m_n);
	for (node_t i = 0; i < m_n; ++i)
	{
		m_basic_topological_ordering_inverse[m_basic_topological_ordering[i]] = i; 
	}
	
	m_basic_topological_ordering_in = range<node_t>(m_n);
	sort (m_basic_topological_ordering_in.begin(), m_basic_topological_ordering_in.end(), [this](node_t a, node_t b) -> bool
	{
		if (rank_in(a) < rank_in(b))
			return true;
		if (rank_in(a) > rank_in(b))
			return false;
		
// 		if (m_heuristic_in[a] == 0 && m_heuristic_in[b] == 0)
// 		{
// 			return vertex_values[a] > vertex_values[b];
// 		}
		
		if (m_heuristic_in[a] == 0)
			return false;
		if (m_heuristic_in[b] == 0)
			return true;
		
// 		if (ingraph[a].size() == 1 && ingraph[b].size() == 1)
// 			return heuristic_out[a] < heuristic_out[b];
		
		if (m_outgraph[a].size() == 1 )
			return true;
		if (m_outgraph[b].size() == 1)
			return false;
		
		return m_heuristic_in[a] < m_heuristic_in[b];
	});
// 	random_shuffle(basic_topological_ordering.begin(), basic_topological_ordering.end());
	m_basic_topological_ordering_inverse_in.resize(m_n);
	for (node_t i = 0; i < m_n; ++i)
	{
		m_basic_topological_ordering_inverse_in[m_basic_topological_ordering_in[i]] = i; 
	}
	
	
	for (size_t i = 0; i < m_n; ++i)
	{
// 		random_shuffle(outgraph[i].begin(), outgraph[i].end());
// 		random_shuffle(ingraph[i].begin(), ingraph[i].end());
		sort(m_outgraph[i].begin(), m_outgraph[i].end(), [this] (node_t a, node_t b) -> bool
		{
			return ex_compare(a,b);
		});
		
		sort(m_ingraph[i].begin(), m_ingraph[i].end(), [this] (node_t a, node_t b) -> bool
		{
			return in_compare(a,b);
		});
	}
	
}

PseudoTopoOrder DiGraph::get_random_pseudotopological_order() const
{
	vector<int> topo_sort(num_vertices());
	for (int i = 0; i < topo_sort.size(); ++i)
	{
		topo_sort[i] = i;
	}
	random_shuffle(topo_sort.begin(),topo_sort.end());
	vector<int> topo_sort_inverse(num_vertices());
	for (int i = 0; i < topo_sort.size(); ++i)
	{
		topo_sort_inverse[topo_sort[i]] = i;
	}
	return PseudoTopoOrder(*this, std::move(topo_sort),std::move(topo_sort_inverse));
}


double DiGraph::get_heuristic_out(node_t node)
{
    double a1 = m_params[0];
	double a2 = m_params[1];
	double a3 = m_params[2];
	double a4 = m_params[3];
	double heuristicex = 0;
	
	for (auto x : m_outgraph[node])
	{
		heuristicex += a1;
		for (auto y : m_outgraph[x])
		{
			heuristicex += a2;
			for (auto z : m_outgraph[y])
			{
				heuristicex += a3+a4*m_outgraph[z].size();
// 				for (auto r : outgraph[z])
// 				{
// 					heuristicex += a4+a5*outgraph[r]./*size()*/;
// 				}
			}
		}
	}
	return heuristicex;
}


double DiGraph::get_heuristic_in(node_t node)
{
// 	return 0;
	double a1 = m_params[4];
	double a2 = m_params[5];
	double a3 = m_params[6];
	double a4 = m_params[7];
	double heuristicin = 0;

	for (auto x : m_ingraph[node])
	{
		heuristicin += a1;
		for (auto y : m_ingraph[x])
		{
			heuristicin  += a2;
			for (auto z : m_ingraph[y])
			{
				heuristicin  += a3+a4*m_ingraph[z].size(); 
			}
		}
	}
	return heuristicin;
}

DiGraph DiGraph::CreateRandomDiGraph(int n, double p)
{
	DiGraph D(n);
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			if (probability_of_true(p))
			{
				int a = i;
				int b = j;
				if (rand()%2 == 1) swap(a,b);
				D.add_edge(a,b);
			}
		}
	}
	return D;
}


DiGraph DiGraph::CreateRandomWeightedDiGraph(int n, double p, weight_t minweight, weight_t maxweight)
{
	DiGraph D(n);
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			if (probability_of_true(p))
			{
				int a = i;
				int b = j;
				weight_t w = random_real(minweight,maxweight);
				if (rand()%2 == 1) swap(a,b);
				D.add_edge(a,b,w);
			}
		}
	}
// 	D.process();
	return D;
}

std::ostream& operator<<(std::ostream& os, const ParamType& a)
{
	os << endl << "\tex: ";
	for (int i = 0; i < 4; ++i)
		os << a[i] << " ";
	os << endl;
	
	os << "\tin: ";
	for (int i = 4; i < 8; ++i)
		os << a[i] << " ";
	os << endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const DiGraph& M)
{
    cout << "Digraph on " << M.num_vertices() << " vertices: " << M.get_vertex_names() << endl;
    for (int i = 0; i < M.num_vertices(); ++i)
    {
        string name = M.get_vertex_name(i);
        for (auto v : M.outneighbors(i))
        {
            string vname = M.get_vertex_name(v);
        }
    }
    return os;
}

void ExpandGreedyBack(const DiGraph& G, Path& P)
{
	while (true)
	{
		auto l = P.back();
		auto& Neighs = G.outneighbors(l);
		
		auto t = P.first_not_explored(Neighs);
		if (t == INVALID_NODE)
			break;
		P.emplace_back(t,t.Weight());
	}
}


void ExpandGreedyFront(const DiGraph& G, Path& P)
{
	while (true)
	{
		auto l = P.front();
		auto& Neighs = G.inneighbors(l);
		
		auto t = P.first_not_explored(Neighs);
		if (t == INVALID_NODE)
			break;
		P.emplace_front(t,t.Weight());
	}
}



int main() 
{
	
	int n,m;
	cin >> n >> m;
	DiGraph D = DiGraph::ReadFromStdin(n,m);
	auto P = D.FindLongestSimplePath(1.5);
	cout << P.size() << endl;
	for (int p : P.data())
		cout << p+1 << " ";
	return 0; 
}