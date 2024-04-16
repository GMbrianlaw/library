#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

template <typename F>
class YCombinator {

private:

    const F f = nullptr;

public:

    explicit YCombinator(F&& f) : f(f) {}

    template <typename... Ts>
    decltype(auto) operator()(Ts&&... arguments) const {

        return f(*this, std::forward<Ts>(arguments)...);

    }

};

template <typename F>
YCombinator(F) -> YCombinator<F>;

template <typename T>
class Dinic {

private:

    using Edge = std::pair<int, T>;

    std::vector<std::vector<int>> adj = std::vector<std::vector<int>>();
    std::vector<Edge> edges = std::vector<Edge>();
    T mx_flow = 0;
    int sz = 0;

public:

    std::vector<int> lvls = std::vector<int>();

    explicit Dinic(int sz) : sz(sz) {

        adj.resize(sz);

        lvls.resize(sz);

    }

    auto addEdge(int node_f, int node_t, T cap) {

        edges.emplace_back(node_t, cap);
        edges.emplace_back(node_f, 0);

        adj[node_f].push_back(std::size(edges) - 2);
        adj[node_t].push_back(std::size(edges) - 1);

        mx_flow += cap;

    }

    auto pushFlow(int src, int sink) {

        auto tot_flow = T();

        while (true) {
            std::fill_n(std::begin(lvls), sz, -1);
            lvls[src] = 0;
            auto process = std::queue<int>();
            process.push(src);
            while (!std::empty(process)) {
                const auto node = process.front();
                process.pop();
                for (auto x : adj[node]) {
                    const auto& [neighbor, cap] = edges[x];
                    if (lvls[neighbor] == -1 && cap) {
                        lvls[neighbor] = lvls[node] + 1;
                        process.push(neighbor);
                    }
                }
            }
            if (lvls[sink] == -1) {
                break;
            }
            auto ptrs = std::vector<int>(sz);
            tot_flow += YCombinator(
                [&](auto self, int node, T flow_i) {
                    if (node == sink) {
                        return flow_i;
                    }
                    auto flow_o = T();
                    while (ptrs[node] < static_cast<int>(std::size(adj[node])) && flow_o < flow_i) {
                        const auto edge_idx = adj[node][ptrs[node]];
                        auto& [neighbor, cap] = edges[edge_idx];
                        if (lvls[neighbor] == lvls[node] + 1 && cap) {
                            const auto cur_flow = self(neighbor, std::min(cap, flow_i - flow_o));
                            flow_o += cur_flow;
                            cap -= cur_flow;
                            edges[edge_idx ^ 1].second += cur_flow;
                        }
                        ptrs[node] += flow_o < flow_i;
                    }
                    return flow_o;
                }
            )(src, mx_flow + 1);
        }

        return tot_flow;

    }

};
