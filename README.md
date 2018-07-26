# AStar

### Instructions:
- Clone into prx_core_ws/src/prx_core/prx/utilities/
    1. cd $PRACSYS_PATH/prx_core/prx/utilities/
    2. git clone https://github.com/Mejikan/AStar.git
    3. rm -rf applications
    4. mv AStar applications

### Notes on current behavior:
- Does not actively checked for blocked (non-empty) cells. (Maybe use high cost or heuristic to accomplish this?)
- Returns solution path at the first encounter of a goal state, this may not be desired (if you want to check if there are other nodes in the open list with a lower cost path)

### TODO:
- Implement heuristic