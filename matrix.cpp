#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

class Matrix {
    private:
        std::vector<std::vector<int>> matrix = {};

    public:
        Matrix(std::string name, int i, int j = 0, std::vector<std::vector<int>> start = {}) {
            if (j == 0) {
                std::ifstream input(name);
                int num;
                int a = 0;
                int amount = 0;
                if (input.is_open()) {
                    while (input >> num) {
                        if (a == 0) {
                            amount = num;
                            matrix = std::vector(amount,std::vector(amount,0));
                        }
                        if (a >= 1 && a <= amount*amount && i == 1) {
                            matrix[(a-1)/amount][(a-1)%amount] = num;
                        }
                        if (a >= amount*amount+1 && a <= 2*amount*amount && i == 2) {
                            matrix[(a-amount*amount-1)/amount][(a-amount*amount-1)%amount] = num;
                        }
                        a += 1;
                    }
                } else {
                    std::cout << name << " not found." << std::endl;
                }
                input.close();
            } else {
                matrix = start;
            }
        }

        std::vector<std::vector<int>> getMatrix() {
            return matrix;
        }

        Matrix operator+(Matrix &other) {
            std::vector<std::vector<int>> result = std::vector(matrix.size(),std::vector(matrix.size(),0));
            for (int m = 0; m < matrix.size(); m++) {
                for (int n = 0; n < matrix.size(); n++) {
                    result[m][n] = matrix[m][n] + other.getMatrix()[m][n];
                }
            }
            return Matrix("",0,1,result);
        }
        Matrix operator*(Matrix &other) {
            std::vector<std::vector<int>> result = std::vector(matrix.size(),std::vector(matrix.size(),0));
            for (int m = 0; m < matrix.size(); m++) {
                for (int n = 0; n < matrix.size(); n++) {
                    for (int o = 0; o < matrix.size(); o++) {
                        result[m][n] += matrix[m][o] * other.getMatrix()[o][n];
                    }
                }
            }
            return Matrix("",0,1,result);
        }

        int diagonal(int a) {
            if (a==1) {
                int result = 0;
                for (int i = 0; i<matrix.size(); i++) {
                    result += matrix[i][i];
                }
                return result;
            } else {
                int result = 0;
                for (int i = 0; i<matrix.size(); i++) {
                    result += matrix[matrix.size()-1-i][i];
                }
                return result;
            }
        }

        Matrix row(int a=0,int b=1) {
            std::vector<std::vector<int>> result = matrix;
            for (int i = 0; i < matrix.size(); i++) {
                int num = result[a][i];
                result[a][i] = result[b][i];
                result[b][i] = num;
            }
            return Matrix("",0,1,result);
        }

        Matrix column(int a=0,int b=1) {
            std::vector<std::vector<int>> result = matrix;
            for (int i = 0; i < matrix.size(); i++) {
                int num = result[i][a];
                result[i][a] = result[i][b];
                result[i][b] = num;
            }
            return Matrix("",0,1,result);
        }

        Matrix change(int a=0, int b=0, int c=100) {
            std::vector<std::vector<int>> result = matrix;
            result[a][b] = c;
            return Matrix("",0,1,result);
        }

        void output() {
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix.size() ; j++) {
                    std::cout << std::setw(5) << matrix[i][j];
                    if (j == matrix.size() - 1) {
                        std::cout << std::endl;
                    }
                }
            }
        }
};

int main() {
    int n = 0;
    std::string name = "";
    std::cout << "What is the name of the input file?" << std::endl;
    std::cin >> name;
    int choice = -1;
    Matrix a = Matrix(name,1);
    Matrix b = Matrix(name,2);
    if (a.getMatrix().size() == 0 || b.getMatrix().size() == 0) {
        return 1;
    }
    std::cout << std::endl;
    std::cout << "Matrix 1:" << std::endl;
    a.output();
    std::cout << std::endl;
    std::cout << "Matrix 2:" << std::endl;
    b.output();
    while (1) {
        choice = -1;
        while (choice > 7 || choice < 0) {
            std::cout << std::endl;
            if (n == 0) {
                std::cout << "Which function do you want to use?" << std::endl;
                std::cout << "1: Print matrices read from file" << std::endl;
                std::cout << "2: Add the matrices and print the result" << std::endl;
                std::cout << "3: Multiply the matrices and print the result" << std::endl;
                std::cout << "4: Print the sum of a diagonal" << std::endl;
                std::cout << "5: Swap rows and print the result" << std::endl;
                std::cout << "6: Swap columns and print the result" << std::endl;
                std::cout << "7: Change a value and print the result" << std::endl;
                std::cout << "0: Exit" << std::endl;
                n = 1;
            } else {
                std::cout << "Which function do you want to use? (1-7 or 0 to exit)" << std::endl;
            }
            std::cin >> choice;
        }
        if (choice == 0) {
            return 0;
        }
        if (choice == 1) {
            Matrix a = Matrix("input.txt",1);
            Matrix b = Matrix("input.txt",2);
            if (a.getMatrix().size() == 0 || b.getMatrix().size() == 0) {
                return 1;
            }
            std::cout << std::endl;
            std::cout << "Matrix 1:" << std::endl;
            a.output();
            std::cout << std::endl;
            std::cout << "Matrix 2:" << std::endl;
            b.output();
        }
        if (choice == 2) {
            Matrix c = a+b;
            std::cout << std::endl;
            c.output();
        }
        if (choice == 3) {
            int order = 0;
            while (order < 1 || order > 2) {
                std::cout << "Do you want matrix 1 or 2 to be on the left? (1 or 2)" << std::endl;
                std::cin >> order;
            }
            if (order == 1) {
                std::cout << std::endl;
                Matrix c = a*b;
                c.output();
            } else {
                std::cout << std::endl;
                Matrix c = b*a;
                c.output();
            }
        }
        if (choice == 4) {
            int num = 0;
            int m = 0;
            while (m < 1 || m > 2) {
                std::cout << "Do you want to add the values on a diagonal of matrix 1 or matrix 2? (1 or 2)" << std::endl;
                std::cin >> m;
            }
            while (num < 1 || num > 2) {
                std::cout << "Which diagonal do you want to add the values of?" << std::endl;
                std::cout << "1: Main" << std::endl;
                std::cout << "2: Secondary" << std::endl;
                std::cin >> num;
            }
            if (m == 1) {
                if (num == 1) {
                    int c = a.diagonal(1);
                    std::cout << std::endl << "Sum: " << c << std::endl;
                } else {
                    int c = a.diagonal(2);
                    std::cout << std::endl << "Sum: " << c << std::endl;
                }
            } else {
                if (num == 1) {
                    int c = b.diagonal(1);
                    std::cout << std::endl << "Sum: " << c << std::endl;
                } else {
                    int c = b.diagonal(2);
                    std::cout << std::endl << "Sum: " << c << std::endl;
                }
            }
        }
        if (choice == 5) {
            int r = -1;
            int other = -1;
            int m = 0;
            while (m < 1 || m > 2) {
                std::cout << "Do you want to swap the rows of matrix 1 or matrix 2? (1 or 2)" << std::endl;
                std::cin >> m;
            }
            while (r < 0 || r > a.getMatrix().size()-1) {
                std::cout << "What is the first row to swap?" << std::endl;
                std::cin >> r;
            }
            while (other < 0 || other > a.getMatrix().size()-1) {
                std::cout << "What is the second row to swap?" << std::endl;
                std::cin >> other;
            }
            if (m == 1) {
                std::cout << std::endl;
                a.row(r,other).output();
            }
            if (m == 2) {
                std::cout << std::endl;
                b.row(r,other).output();
            }
        }
        if (choice == 6) {
            int val = -1;
            int other = -1;
            int m = 0;
            while (m < 1 || m > 2) {
                std::cout << "Do you want to swap the columns of matrix 1 or matrix 2? (1 or 2)" << std::endl;
                std::cin >> m;
            }
            while (val < 0 || val > a.getMatrix().size()-1) {
                std::cout << "What is the first column to swap?" << std::endl;
                std::cin >> val;
            }
            while (other < 0 || other > a.getMatrix().size()-1) {
                std::cout << "What is the second column to swap?" << std::endl;
                std::cin >> other;
            }
            if (m == 1) {
                std::cout << std::endl;
                a.column(val,other).output();
            }
            if (m == 2) {
                std::cout << std::endl;
                b.column(val,other).output();
            }
        }
        if (choice == 7) {
            int r = -1;
            int val = -1;
            int num = -1;
            int m = 0;
            while (m < 1 || m > 2) {
                std::cout << "Do you want to change a value in matrix 1 or matrix 2? (1 or 2)" << std::endl;
                std::cin >> m;
            }
            while (r < 0 || r > a.getMatrix().size()-1) {
                std::cout << "What is the row where you want to change a value?" << std::endl;
                std::cin >> r;
            }
            while (val < 0 || val > a.getMatrix().size()-1) {
                std::cout << "What is the column where you want to change a value?" << std::endl;
                std::cin >> val;
            }
            std::cout << "What is the value that should go there?" << std::endl;
            std::cin >> num;
            if (m == 1) {
                std::cout << std::endl;
                a.change(r,val,num).output();
            }
            if (m == 2) {
                std::cout << std::endl;
                b.change(r,val,num).output();
            }
        }
    }
}