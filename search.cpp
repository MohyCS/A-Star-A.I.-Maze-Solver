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
            for(int i=initial_i; i<=goal_i; ++i)                                      //################
                path.push_back(std::make_pair(i,initial_j));                          //################            
            for(int i=initial_i; i>=goal_i; --i)                                      //################
                path.push_back(std::make_pair(i,initial_j));                          //################            
            for(int j=initial_j+1; j<=goal_j; ++j)                                    //################
                path.push_back(std::make_pair(goal_i,j));                             //################        
            for(int j=initial_j-1; j>=goal_j; --j)                                    //################
                path.push_back(std::make_pair(goal_i,j));                             //################ 
            //If using C++, you can choose to populate the following function in search.cpp 
            //path = searcher->search();           
            //################THE PRECEDING CODE SHOULD BE REPLACED BY YOUR SOLUTION####################

            // models the data
            if (this->cells == NULL)
            {
                std::cout << "*******************Execute once for init\n";
                set_cells_from_file(file_path);
            }
            else
            {
                std::cout << "************NOT NULL!!!!!!!!!!!!!!!!!!!\n";
            }


        	return path;
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

                std::cout << "##########################33Execute once for init\n";
                
                for (int o=0; o < this->rows; o++)
                {
                    for (int p=0; p < this->columns; p++)
                        std::cout << this->cells[o][p]->empty << " ";
                    std::cout << "\n";
                }
                maze_file.close();
            }
        }
    }
}
