#include "Sparse2D.h"

// "Helper: sorts row_indices and data based on row_indices using bubble sort."
void Sparse2D::bubbleSortByRowIndex()
{
    int n = static_cast<int>(row_indices.size());
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (row_indices[j] > row_indices[j + 1])
            {
                // swap row indice
                int tempRow = row_indices[j];
                row_indices[j] = row_indices[j + 1];
                row_indices[j + 1] = tempRow;
                // "Also swap the corresponding Sparse1D at the same position."
                Sparse1D tempS1D = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tempS1D;
            }
        }
    }
}

// Default constructor
Sparse2D::Sparse2D()
{
    // create empty matrix
}

// "Constructor that reads from file"
Sparse2D::Sparse2D(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        // file opening
        return;
    }

    string line;
    // read the file line by line
    while (getline(inFile, line))
    {
        if (line.empty())
            continue; // skip empty lines

        // row format: "rowIndex col1|val1 col2|val2 ..."
        // first token row index, rest column–value pairs.
        stringstream ss(line);
        int rowIndex;
        ss >> rowIndex;  //first token: row index

        Sparse1D rowData; // we will keep datas of this line

        string token;
        // Read rest tokens by seperating empties
        while (ss >> token)
        {
            size_t pos = token.find('|');
            if (pos != string::npos)
            {
                string colStr = token.substr(0, pos);       // col insex (eg. "3")
                string valStr = token.substr(pos + 1);        // value(eg. "24.6")
                int col = stoi(colStr);
                double val = stod(valStr);
                if (val != 0.0)
                {
                    // add non-zero values
                    rowData.indices.push_back(col);
                    rowData.data.push_back(val);
                }
            }
        }

       /* Also sort the column information inside RowData using bubble sort 
      (we're using our own bubble sort here, and the columns are already indexed) */
        rowData.bubbleSortByIndex();

        //Add datas of this row to the  matrix
        row_indices.push_back(rowIndex);
        data.push_back(rowData);
    }
    inFile.close();

    // Sort row_indices using buble sort
    bubbleSortByRowIndex();
}

// operator+ : Matris adding (in row format)
Sparse2D Sparse2D::operator+(const Sparse2D &other) const
{
    Sparse2D result;
    int i = 0, j = 0;
    int sizeA = static_cast<int>(row_indices.size());
    int sizeB = static_cast<int>(other.row_indices.size());

    while (i < sizeA && j < sizeB)
    {
        if (row_indices[i] == other.row_indices[j])
        {
            // "Common row; perform Sparse1D addition."
            Sparse1D sumRow = data[i] + other.data[j];
            if (!sumRow.indices.empty())
            {
                result.row_indices.push_back(row_indices[i]);
                result.data.push_back(sumRow);
            }
            i++;
            j++;
        }
        else if (row_indices[i] < other.row_indices[j])
        {
            //Row that exists only in matrix A
            result.row_indices.push_back(row_indices[i]);
            result.data.push_back(data[i]);
            i++;
        }
        else
        {
            //"Row that exists only in matrix B"
            result.row_indices.push_back(other.row_indices[j]);
            result.data.push_back(other.data[j]);
            j++;
        }
    }
    // add remaining rows
    while (i < sizeA)
    {
        result.row_indices.push_back(row_indices[i]);
        result.data.push_back(data[i]);
        i++;
    }
    while (j < sizeB)
    {
        result.row_indices.push_back(other.row_indices[j]);
        result.data.push_back(other.data[j]);
        j++;
    }

    return result;
}

// operator- : Matris substraction (in row format)
Sparse2D Sparse2D::operator-(const Sparse2D &other) const
{
    Sparse2D result;
    int i = 0, j = 0;
    int sizeA = static_cast<int>(row_indices.size());
    int sizeB = static_cast<int>(other.row_indices.size());

    while (i < sizeA && j < sizeB)
    {
        if (row_indices[i] == other.row_indices[j])
        {
            Sparse1D diffRow = data[i] - other.data[j];
            if (!diffRow.indices.empty())
            {
                result.row_indices.push_back(row_indices[i]);
                result.data.push_back(diffRow);
            }
            i++;
            j++;
        }
        else if (row_indices[i] < other.row_indices[j])
        {
            result.row_indices.push_back(row_indices[i]);
            result.data.push_back(data[i]);
            i++;
        }
        else
        {
            // Row not in A but present in B: 0 - B = -B"
            Sparse1D negB = -other.data[j];
            if (!negB.indices.empty())
            {
                result.row_indices.push_back(other.row_indices[j]);
                result.data.push_back(negB);
            }
            j++;
        }
    }
    while (i < sizeA)
    {
        result.row_indices.push_back(row_indices[i]);
        result.data.push_back(data[i]);
        i++;
    }
    while (j < sizeB)
    {
        Sparse1D negB = -other.data[j];
        if (!negB.indices.empty())
        {
            result.row_indices.push_back(other.row_indices[j]);
            result.data.push_back(negB);
        }
        j++;
    }

    return result;
}

// operator-() :"Unary minus, negates all elements in the matrix."
Sparse2D Sparse2D::operator-() const
{
    Sparse2D result;
    int n = static_cast<int>(row_indices.size());
    result.row_indices.reserve(n);
    result.data.reserve(n);

    for (int i = 0; i < n; i++)
    {
        result.row_indices.push_back(row_indices[i]);
        Sparse1D negRow = -data[i]; // Sparse1D's unary minus operator
        result.data.push_back(negRow);
    }
    return result;
}

// operator<< : print matrix(in row format)
// Format: row_index col|val col|val ...
ostream& operator<<(ostream &os, const Sparse2D &obj)
{
    int n = static_cast<int>(obj.row_indices.size());
    for (int i = 0; i < n; i++)
    {
        os << obj.row_indices[i] << " " << obj.data[i] << endl; //burada geri kalanını <<sparse1D hallediyor(obj.data[i])
    }
    return os;
}
// operator* : Matrix multiplication (classic matrix multiplication)
// Non-existing values are considered as 0
/* 'other' corresponds to matrix B.

  other.data.size() = Number of non-zero rows in matrix B. 
 We iterate over these rows using i.

 other.data[i].indices.size() = Number of non-zero columns in row i of matrix B.
 We examine them using j.

other.data[i].indices[j] = The column index of the j-th non-zero element in the i-th row of matrix B. */

Sparse2D Sparse2D::operator*(const Sparse2D &other) const
{                                                            // class    burada other.data.size = 2
    Sparse2D result;                                         // class   

    // "Find the maximum column index in the other matrix"     
    int maxColB = 0;
    for (int i = 0; i < static_cast<int>(other.data.size()); i++) //we can think of this as the number of rows — each one is like a Sparse1D object.
    {
        for (int j = 0; j < static_cast<int>(other.data[i].indices.size()); j++) //we can consider as a number of columns
        {
            if (other.data[i].indices[j] > maxColB)
                maxColB = other.data[i].indices[j];
        }
    }

    // A matrisinin her satırı için    iA  is the index of A matrix
    for (int iA = 0; iA < static_cast<int>(row_indices.size()); iA++)
    {
        int rA = row_indices[iA];  //"For each row of matrix A — iA:is the index in matrix A"
        Sparse1D rowResult; //"Temporary storage for the results of this row"

        //"For each column of matrix B"
        for (int colB = 0; colB <= maxColB; colB++)
        {
            Sparse1D colVector = other.column(colB);  // B matrix's colB column
            double prod = data[iA].dot(colVector);    // A row  B column

            if (prod != 0.0)
            {
                rowResult.indices.push_back(colB);
                rowResult.data.push_back(prod);
            }
        }

        if (!rowResult.indices.empty()) //if prod is not 0.0 do below
        {
            result.row_indices.push_back(rA);
            result.data.push_back(rowResult);
        }
    }

    result.bubbleSortByRowIndex(); //sort them

    return result;
}
Sparse2D Sparse2D::transpose() const
{
    Sparse2D result;

    // "Iterate through the elements of each row" 
    for (int i = 0; i < static_cast<int>(row_indices.size()); i++)
    {
        int currentRow = row_indices[i];
        const Sparse1D &row_reference = data[i];

        for (int j = 0; j < static_cast<int>(row_reference.indices.size()); j++) //we are in columns of that class
        {
            int colIndex = row_reference.indices[j];
            double val = row_reference.data[j];

            // "In the transpose, this value will be at (colIndex, currentRow)"
            bool found = false;
            
            // Has a row corresponding to this column index (colIndex) already been created in the transposed matrix?
            // If yes, add currentRow and val to the corresponding Sparse1D
            for (int k = 0; k < static_cast<int>(result.row_indices.size()); k++)
            {
                if (result.row_indices[k] == colIndex)
                {
                    result.data[k].indices.push_back(currentRow);
                    result.data[k].data.push_back(val);
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                result.row_indices.push_back(colIndex);
                Sparse1D newRow;
                newRow.indices.push_back(currentRow);
                newRow.data.push_back(val);
                result.data.push_back(newRow);
            }
        }
    }

    result.bubbleSortByRowIndex();

    //"Also sort each Sparse1D row"
    for (int i = 0; i < static_cast<int>(result.data.size()); i++)
    {
        result.data[i].bubbleSortByIndex();
    }

    return result;
}
Sparse1D& Sparse2D::row(int row_index)
{
    // This function returns the row with the given row_index.
    // If such a row doesn't exist,exit.

    //Search is there a row?
    for (int i = 0; i < static_cast<int>(row_indices.size()); i++)
    {
        if (row_indices[i] == row_index)
        {
            return data[i]; // if found return 
        }
    }

    // if not found exit the code
    cerr << "Error: Row index " << row_index << " not found in Sparse2D." << std::endl;
    exit(1);

}
Sparse1D Sparse2D::column(int column_index) const 
{
    // This function creates and returns a Sparse1D representing the given column (by value), since it cannot return a reference
    // because there is no direct structure to access a column
    Sparse1D resultCol;

    // Iterate all rows
    for (int i = 0; i < static_cast<int>(row_indices.size()); i++)
    {
        const Sparse1D &rowS1D = data[i];

        //"Check if column_index exists in rowS1D"
        for (int j = 0; j < static_cast<int>(rowS1D.indices.size()); j++)
        {
            if (rowS1D.indices[j] == column_index)
            {
                // column_index has been found
                // row = row_indices[i], value = rowS1D.data[j]
                int actualRow = row_indices[i];
                double val = rowS1D.data[j];

                // zero check
                if (val != 0.0)
                {
                    resultCol.indices.push_back(actualRow);
                    resultCol.data.push_back(val);
                }
                break; //"A column appears only once in the same row"
            }
        }
    }

    //"Sort resultCol at the end"
    resultCol.bubbleSortByIndex();
    return resultCol;
}