#include <algorithm>
#include <iostream>
#include <utility>
#include <climits>
#include <vector>
#include <random>

struct Segment
{
    int start, end;
    int start_index, end_index;
};

struct SegmentQuery
{
    Segment segment;
    bool add;
};

struct Block
{
    int block_start, block_end;
};

class Solver
{
public:
    explicit Solver(const std::vector<SegmentQuery>& queries) : queries(queries)
    {
    }

    std::vector<int> solve()
    {
        const int n_queries = queries.size();
        std::vector<std::pair<int, std::pair<bool, int> > > events;
        events.reserve(n_queries * 2);

        
        for (int index = 0; index < n_queries; ++index)
        {
            const SegmentQuery &segment_query = queries[index];

            events.push_back(std::make_pair(segment_query.segment.start, std::make_pair(true, index)));
            events.push_back(std::make_pair(segment_query.segment.end, std::make_pair(false, index)));
        }

        std::sort(events.begin(), events.end());

        std::vector<int> points;
        for (auto& event : events)
        {
            int x = event.first;
            int segment = event.second.second;
            bool start = event.second.first;

            if (points.size() == 0 || points.back() != event.first)
            {
                points.push_back(x);
            }

            if (start)
                queries[segment].segment.start_index = points.size() - 1;
            else
                queries[segment].segment.end_index = points.size() - 1;
        }

    }

private:
    std::vector<SegmentQuery> queries;

    int square_root(int n)
    {
        if (n == 0)
            return 0;

        int result = 1;
        while (result*result < n)
        {
            ++result;
        }

        return result;
    }
};

int main() {

#ifdef LOCAL_SOLUTION
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    int operations;
    std::cin >> operations;

    std::vector<SegmentQuery> queries;

    for (int index = 0; index < operations; ++index)
    {
        char op;
        int start, end;

        std::cin >> op;
        std::cin >> start >> end;

        SegmentQuery sq = { { start, end, -1, -1 }, op == '+' };
        queries.push_back(sq);
    }

    Solver solver(queries);
    std::vector<int> answers = solver.solve();

    for (auto area : answers)
    {
        std::cout << area << std::endl;
    }



    return 0;
}
