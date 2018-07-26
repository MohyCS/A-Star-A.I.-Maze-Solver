#include "prx/utilities/applications/search.hpp"

namespace prx
{

    namespace util
    {
        cell_t::cell_t(int r, int c, int empty_state)
        {
            row = r;
            column = c;
            empty = empty_state;
        }

        cell_t::~cell_t()
        {}

        node_t::node_t(cell_t* c, node_t* par)
        {
            cell = c;
            parent = par;
        }

        node_t::~node_t()
        {
            cell = NULL;
        }

        int node_t::get_cost_from_parent()
        {
            return 1;
        }

        int node_t::get_cost()
        {
            if (this->parent == NULL)
                return 0;
            else
            {
                return this->parent->get_cost() + this->get_cost_from_parent();
            }
        }

        int node_t::get_cost_and_heur()
        {
            return this->get_cost() + this->heuristic;
        }

        std::vector< std::pair<int, int> > node_t::produce_path()
        {
            // (adds full path from start to end node included)

            std::vector< std::pair<int, int> > path;
            node_t* ptr = this;
            // traverse backwards
            while (ptr != NULL)
            {
                path.push_back(std::make_pair(ptr->cell->row, ptr->cell->column));
                std::cout << "r: " << ptr->cell->row << ", c: " << ptr->cell->column << "\n";
                ptr = ptr->parent;
            }

            std::reverse(path.begin(), path.end()); 
            return path;
        }

        search_t::search_t()
        {}

        search_t::~search_t()
        {}

        std::vector< std::pair<int, int> > search_t::search(std::string file_path,
            int initial_i, int initial_j, int goal_i, int goal_j)
        {
        	std::vector< std::pair<int, int> > path;

            // Naive generation of path that has not awareness of the environment
            //################COMMENT OUT THE FOLLOWING BLOCK OF CODE TO POPULATE path##################
            // for(int i=initial_i; i<=goal_i; ++i)                                      //################
            //     path.push_back(std::make_pair(i,initial_j));                          //################            
            // for(int i=initial_i; i>=goal_i; --i)                                      //################
            //     path.push_back(std::make_pair(i,initial_j));                          //################            
            // for(int j=initial_j+1; j<=goal_j; ++j)                                    //################
            //     path.push_back(std::make_pair(goal_i,j));                             //################        
            // for(int j=initial_j-1; j>=goal_j; --j)                                    //################
            //     path.push_back(std::make_pair(goal_i,j));                             //################ 
            //If using C++, you can choose to populate the following function in search.cpp 
            //path = searcher->search();           
            //################THE PRECEDING CODE SHOULD BE REPLACED BY YOUR SOLUTION####################

            // READ data from file and map it to 2D array
            if (this->cells == NULL)
            {
                std::cout << "*******************Execute once for init\n";
                set_cells_from_file(file_path);
            }
            else
            {
                std::cout << "************NOT NULL!!!!!!!!!!!!!!!!!!!\n";
            }

            path = a_star(initial_i, initial_j, goal_i, goal_j);

        	return path;
        }

        std::vector< std::pair<int, int> > search_t::a_star(int initial_i, int initial_j, int goal_i, int goal_j)
        {
            std::vector< std::pair<int, int> > path;

            // BEGIN A-STAR ALGORITHM
            // create open and visited collections
            std::list< node_t* > open; // nodes which occupy the current search space
            std::list< node_t* > visited; // cells already visited before

            if (initial_i == goal_i && initial_j == goal_j) // edge case where initial == goal
                return path;

            cell_t* initial_cell = this->cells[initial_i][initial_j];
            node_t* initial_node = new node_t(initial_cell, NULL);
            open.push_back(initial_node); // add initial node

            while (!open.empty())
            {
                // search all open node for the least estimated cost
                node_t* least = least_est_cost_node(open);
                open.remove(least);

                // produce successors
                std::vector< cell_t* > adjacent = get_adjacent_cells(least->cell);
                for (auto &adj_cell : adjacent)
                {
                    node_t* successor = new node_t(adj_cell, least);
                    if (adj_cell->row == goal_i && adj_cell->column == goal_j) // check if successor is goal
                    {
                        // debug
                        std::cout << "succ i: " << adj_cell->row << ", succ j: " << adj_cell->column << "\n";
                        std::cout << "goal i: " << goal_i << ", goal j: " << goal_j << "\n";

                        // if goal, make sure there is no open node with a lower cost
                        // (not implementing for now)
                        path = successor->produce_path();
                        return path;
                    }
                    else
                    {
                        // node in open list which references the same cell
                        node_t* open_node_same_cell = find_node_by_cell(open, adj_cell);
                        if (open_node_same_cell != NULL) 
                        {
                            if (open_node_same_cell->get_cost_and_heur() < successor->get_cost_and_heur())
                                continue;
                            // cannot do better cost than current open node, so skip successor
                        }

                        node_t* visited_node_same_cell = find_node_by_cell(visited, adj_cell);
                        if (visited_node_same_cell != NULL)
                        {
                            if (open_node_same_cell->get_cost_and_heur() < successor->get_cost_and_heur())
                                continue;
                                // cannot do better cost than current visited node, so skip successor
                            else
                                open.push_back(successor);
                        }
                    }
                }

                visited.push_back(least);
            }
        }

        node_t* search_t::find_node_by_cell(std::list< node_t* > nodes, cell_t* cell)
        {
            for (auto &node : nodes)
            {
                if (node->cell == cell)
                    return node;
            }
            return NULL;
        }

        node_t* search_t::least_est_cost_node(std::list< node_t* > nodes)
        {
            node_t* least = NULL;
            for (auto &node : nodes)
            {
                if (least == NULL || node->get_cost_and_heur() < least->get_cost_and_heur())
                    least = node;
            }
            return least;
        }

        std::vector< cell_t* > search_t::get_adjacent_cells(cell_t* cell)
        {
            return get_adjacent_cells(cell->row, cell->column);
        }
        
        std::vector< cell_t* > search_t::get_adjacent_cells(int i, int j)
        {
            std::vector< cell_t* > adjacent;
            
            int left = j-1;
            if (left >= 0 && left < rows)
                adjacent.push_back( this->cells[i][left] );
            int right = j+1;
            if (right >= 0 && right < rows)
                adjacent.push_back( this->cells[i][right] );
            int up = i-1;
            if (up >= 0 && up < rows)
                adjacent.push_back( this->cells[up][j] );
            int down = i+1;
            if (down >= 0 && down < rows)
                adjacent.push_back( this->cells[down][j] );

            //debug
            for (auto &cell : adjacent)
            {
                std::cout << "adj i: " << cell->row << ", adj j: " << cell->column << "\n";
            }
            std::cout << "end adj for: " << i << ", " << j << "\n";

            return adjacent;
        }

        void search_t::set_cells_from_file(std::string file_path)
        {
            std::ifstream maze_file (file_path);
            if (maze_file.is_open())
            {
                int i = 0;
                std::string line;
                while (getline(maze_file, line))
                {
                    if (i == 0)
                    {
                        this->rows = stoi(line);
                        this->cells = (cell_t***) malloc(this->rows * sizeof(cell_t**));
                    }
                    else if (i == 1)
                    {
                        this->columns = stoi(line);
                        for(int r = 0; r < this->rows; r++)
                            this->cells[r] = (cell_t**) malloc(this->columns * sizeof(cell_t*));
                    }
                    else
                    {
                        int x = 0;
                        std::string raw_num; // string representation of a number
                        std::stringstream ss (line);
                        while (getline(ss, raw_num, ' '))
                        {
                            this->cells[i-2][x] = new cell_t(i-2, x, stoi(raw_num));
                            x++;
                        }
                    }
                    i++;
                }
                
                // debug saved map
                // for (int o=0; o < this->rows; o++)
                // {
                //     for (int p=0; p < this->columns; p++)
                //         std::cout << this->cells[o][p]->empty << " ";
                //     std::cout << "\n";
                // }
                maze_file.close();
            }
        }
    }
}
