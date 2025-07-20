#include "Sparse1D.h"

// Simple bubble sort to order `indices` and `data` vectors 
// by ascending indices. Called after reading from file.
void Sparse1D::bubbleSortByIndex()
{
    int n = static_cast<int>(indices.size());
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(indices[j] > indices[j + 1])
            {
                // Swap indices
                int tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;

                // Swap corresponding data values
                double tempVal = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tempVal;
            }
        }
    }
}

// Default constructor
Sparse1D::Sparse1D()
{
    // No initialization needed
}

// Constructor that reads from file.
// Each line is space-separated "index|value" entries.
// Only non-zero values are stored.
Sparse1D::Sparse1D(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        // If file can't be opened, leave empty
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        if (line.empty())  // Skip empty lines
            continue;

        stringstream ss(line);
        string token;

        // Parse each "index|value" entry
        while (ss >> token)
        {
            size_t sepPos = token.find('|');
            if (sepPos != string::npos)
            {
                string idxStr = token.substr(0, sepPos);
                string valStr = token.substr(sepPos + 1);

                int idx = stoi(idxStr);
                double val = stod(valStr);

                if (val != 0.0)
                {
                    indices.push_back(idx);
                    data.push_back(val);
                }
            }
        }
    }
    inFile.close();

    // Sort the entries by index
    bubbleSortByIndex();
}

// Element-wise addition
Sparse1D Sparse1D::operator+(const Sparse1D &other) const
{
    Sparse1D result;
    result.indices.reserve(indices.size() + other.indices.size());
    result.data.reserve(indices.size() + other.indices.size());

    int i = 0, j = 0;
    int sizeA = static_cast<int>(indices.size());
    int sizeB = static_cast<int>(other.indices.size());

    while(i < sizeA && j < sizeB)
    {
        if(indices[i] == other.indices[j])
        {
            double sumVal = data[i] + other.data[j];
            if(sumVal != 0.0)
            {
                result.indices.push_back(indices[i]);
                result.data.push_back(sumVal);
            }
            i++;
            j++;
        }
        else if(indices[i] < other.indices[j])
        {
            result.indices.push_back(indices[i]);
            result.data.push_back(data[i]);
            i++;
        }
        else
        {
            result.indices.push_back(other.indices[j]);
            result.data.push_back(other.data[j]);
            j++;
        }
    }

    // Remaining elements from this vector
    while(i < sizeA)
    {
        result.indices.push_back(indices[i]);
        result.data.push_back(data[i]);
        i++;
    }
    // Remaining elements from other vector
    while(j < sizeB)
    {
        result.indices.push_back(other.indices[j]);
        result.data.push_back(other.data[j]);
        j++;
    }

    return result;
}

// Element-wise subtraction
Sparse1D Sparse1D::operator-(const Sparse1D &other) const
{
    Sparse1D result;
    result.indices.reserve(indices.size() + other.indices.size());
    result.data.reserve(indices.size() + other.indices.size());

    int i = 0, j = 0;
    int sizeA = static_cast<int>(indices.size());
    int sizeB = static_cast<int>(other.indices.size());

    while(i < sizeA && j < sizeB)
    {
        if(indices[i] == other.indices[j])
        {
            double diffVal = data[i] - other.data[j];
            if(diffVal != 0.0)
            {
                result.indices.push_back(indices[i]);
                result.data.push_back(diffVal);
            }
            i++;
            j++;
        }
        else if(indices[i] < other.indices[j])
        {
            result.indices.push_back(indices[i]);
            result.data.push_back(data[i]);
            i++;
        }
        else
        {
            // Only in other: 0 - value = -value
            double negVal = -other.data[j];
            if(negVal != 0.0)
            {
                result.indices.push_back(other.indices[j]);
                result.data.push_back(negVal);
            }
            j++;
        }
    }

    // Remaining entries from this vector
    while(i < sizeA)
    {
        result.indices.push_back(indices[i]);
        result.data.push_back(data[i]);
        i++;
    }
    // Remaining entries from other vector (negated)
    while(j < sizeB)
    {
        double negVal = -other.data[j];
        if(negVal != 0.0)
        {
            result.indices.push_back(other.indices[j]);
            result.data.push_back(negVal);
        }
        j++;
    }

    return result;
}

// Unary minus: negate each value
Sparse1D Sparse1D::operator-() const
{
    Sparse1D result;
    int sizeA = static_cast<int>(indices.size());
    result.indices.reserve(sizeA);
    result.data.reserve(sizeA);

    for(int i = 0; i < sizeA; i++)
    {
        result.indices.push_back(indices[i]);
        result.data.push_back(-data[i]);
    }
    return result;
}

// Dot product: only multiply matching indices
double Sparse1D::dot(const Sparse1D &other) const
{
    double sum = 0.0;
    int i = 0, j = 0;
    int sizeA = static_cast<int>(indices.size());
    int sizeB = static_cast<int>(other.indices.size());

    while(i < sizeA && j < sizeB)
    {
        if(indices[i] == other.indices[j])
        {
            sum += data[i] * other.data[j];
            i++;
            j++;
        }
        else if(indices[i] < other.indices[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return sum;
}

// Output format: index|value index|value ...
ostream& operator<<(ostream &os, const Sparse1D &obj)
{
    int n = static_cast<int>(obj.indices.size());
    for(int i = 0; i < n; i++)
    {
        os << obj.indices[i] << "|" << obj.data[i];
        if(i < n - 1)
        {
            os << " ";
        }
    }
    return os;
}
