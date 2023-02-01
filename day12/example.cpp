
struct Pos {
    int64_t row;
    int64_t column;
    Pos left() { return {row,column-1}; }
    Pos right() { return {row,column+1}; }
    Pos down() { return {row+1,column}; }
    Pos up() { return {row-1,column}; }
};

int64_t hill_climb(const std::vector<std::string>& map, 
                   Pos start, Pos end) {
  // Costs of paths  
  std::vector<std::vector<int64_t>> visited(
    map.size(), std::vector<int64_t>(map[0].length(), INT64_MAX));
  
  // Helper to check whether we can step one elevation to another.
  auto elevation_ok = [](char from, char to) {
    if (from >= to) return true;
    return from+1 == to;
  };
  
  // Main check: is from->to a valid step that isn't more expensive
  // than an already existing path?
  auto can_step = [&](Pos from, Pos to, int64_t cost) {
    // Check bounds
    if (to.row >= std::ssize(map) || to.row < 0) return false;
    if (to.column >= std::ssize(map[0]) || to.column < 0) return false;
    // Check if not longer than the shortest known path.
    if (cost + 1 >= visited[to.row][to.column]) return false;
    // Check whether the elevation change is ok.
    if (map[from.row][from.column] == 'S') // Treat 'S' as 'a'
        return elevation_ok('a', map[to.row][to.column]);
    if (map[to.row][to.column] == 'E') // Treat 'E' as 'z'
        return elevation_ok(map[from.row][from.column], 'z');
    return elevation_ok(map[from.row][from.column], 
                        map[to.row][to.column]);
  };

  // BFS implementation
  std::queue<std::pair<Pos,int64_t>> queue;
  // Init with the start point
  queue.push(std::make_pair(start,0));
  visited[start.row][start.column] = 0;

  while (!queue.empty()) {
    auto [from, cost] = queue.front();
    queue.pop();

    // Do not explore past end
    if (map[from.row][from.column] == 'E') continue;

    // Try to step in each direction:
    for (auto dir : {&Pos::left, &Pos::right, &Pos::up, &Pos::down}) {
        Pos to = (from.*dir)();
        if (!can_step(from, to, cost + 1)) continue;

        queue.push(std::make_pair(to, cost + 1));
        visited[to.row][to.column] = cost + 1;
    }
  }
  // Return the shortest path cost.
  return visited[end.row][end.column];
}