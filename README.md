# AStar

### Instructions:

**SCRIPT**
```bash
    git clone https://github.com/Mejikan/AStar.git
    cd AStar
    chmod +x mvtodir.sh
    ./mvtodir.sh
```
**MANUAL**
- Clone into prx_core_ws/src/prx_core/prx/utilities/
```bash
    cd $PRACSYS_PATH/prx_core/prx/utilities/
    git clone https://github.com/Mejikan/AStar.git
    rm -rf applications
    mv AStar applications
```

---

### Notes on current behavior:
- Actively check for blocked (non-empty) cells.
- Returns solution path at the first encounter of a goal state.

### Classes
- **cell_t**
    - represents a cell in the environment which the agent can travel on
    - it is also analagous to an element/position in a graph, where the graph is environment
    - contains position
    - does not change every search, *do not change values within this class during runtime*
- **node_t**
    - instance of a cell in a graph, the search algorithm may encounter a cell multiple times
    during its search
    - analagous to a node in a search tree
    - contains cost, heuristic, reference to the cell it is an instance of
    - nodes do not exist past one search process, a new search tree and solution path is produced
    for every new goal and thus every new search process

### Pipeline
- application.plan()
    - application.searcher.search()
        - searcher.astar() (A-Star performed here)

### TODO:
- Implement heuristic
- Generate environments (may need to store environments in repo?)
- Test in different environments (weird issue with the goal state only being a unit distance of one away)
- Remove debug statements
