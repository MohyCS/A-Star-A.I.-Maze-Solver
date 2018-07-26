# AStar

### Instructions:
- Clone into prx_core_ws/src/prx_core/prx/utilities/
    1. cd $PRACSYS_PATH/prx_core/prx/utilities/
    2. git clone https://github.com/Mejikan/AStar.git
    3. rm -rf applications
    4. mv AStar applications

---

### Notes on current behavior:
- Does not actively check for blocked (non-empty) cells. (Maybe use high cost or heuristic to accomplish this?)
- Returns solution path at the first encounter of a goal state, this may not be desired (if you want to check if there are other nodes in the open list with a lower cost path)

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