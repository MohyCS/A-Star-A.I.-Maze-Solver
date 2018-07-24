#pragma once

#ifndef PRX_UTIL_SEARCH_HPP
#define	PRX_UTIL_SEARCH_HPP

#include <fstream>
#include <ros/ros.h>

namespace prx
{
    namespace util
    {
        class cell_t
        {
          public:
            cell_t(int r, int c, int empty_state);
            virtual ~cell_t();

            int row = -1;
            int column = -1;   
            int empty = 1;
        };

        class search_t
        {
          private:
            int rows = 0;
            int columns = 0;
            cell_t*** cells = NULL;

            std::vector< cell_t* > get_adjacent_cells(int i, int j);
            void set_cells_from_file(std::string file_path);

          public:
            search_t();
            virtual ~search_t();

            std::vector< std::pair<int, int> > search(std::string file_path, int initial_i, int initial_j, int goal_i, int goal_j);
        };


    }
}

#endif