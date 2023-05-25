#include <map>
#include <utility>
#include <iostream>
 
const int DEFAULT_VALUE = 0;
 
struct cell_data {
    int row;
    int col;
    int value;
};

class sparse_matrix {
public:
    
    sparse_matrix() : occupied_cells(0) {}
    
    ~sparse_matrix() {}
     
    int get_occupied_cells() const {
        return occupied_cells;
    }
     
    void set_value(int row, int col, int value = DEFAULT_VALUE) {
        
        auto cell = std::make_pair(row, col);
        if (matrix.find(cell) == matrix.end()) {
            
            matrix[cell] = {row, col, value};
            occupied_cells++;
        } else {
            
            matrix[cell].value = value;
        }
         
        if (value == DEFAULT_VALUE) {
            matrix.erase(cell);
            occupied_cells--;
        }
    }
     
    cell_data get_cell(int index) const {
        
        if (index < 0 || index >= occupied_cells) {
            throw std::out_of_range("Invalid index");
        }
         
        int i = 0;
        for (auto& p : matrix) {
            if (i == index) {
                return p.second;
            }
            i++;
        }
         
        throw std::runtime_error("Index out of range");
    }
     
    void print_matrix() const {
        for (auto& p : matrix) {
            std::cout << "(" << p.second.row << ", " << p.second.col << "): " << p.second.value << std::endl;
        }
    }
 private:
   
    std::map<std::pair<int, int>, cell_data> matrix;
    
    int occupied_cells;
};

int main() {
    sparse_matrix matrix;
     matrix.set_value(0, 0, 1); 
    matrix.set_value(1, 1, 2); 
    matrix.set_value(0, 0);    
    matrix.set_value(2, 2, 3); 
     std::cout << "Occupied cells: " << matrix.get_occupied_cells() << std::endl;
    matrix.print_matrix();
     std::cout << "Cell 0: (" << matrix.get_cell(0).row << ", " << matrix.get_cell(0).col << "): " << matrix.get_cell(0).value << std::endl;
    std::cout << "Cell 1: (" << matrix.get_cell(1).row << ", " << matrix.get_cell(1).col << "): " << matrix.get_cell(1).value << std::endl;
    std::cout << "Cell 2: (" << matrix.get_cell(2).row << ", " << matrix.get_cell(2).col << "): " << matrix.get_cell(2).value << std::endl;
     matrix.set_value(3, 3);   
    matrix.print_matrix();
     return 0;
}