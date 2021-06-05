#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

#define ROWS 19
#define COLS 19

using namespace std;

struct gridData
{
    string words;
    int rows;
    int cols;
    bool LR,RL,TB,BT;
    bool found;
    void initialize()
    {
        LR = false;
        RL = false;
        TB = false;
        BT = false;
        found = false;
    }
};

// Input Function
void getGrid(char grid[][COLS])
{
    ifstream theFile("Input.txt");
    if(theFile.is_open())
    {
        for(int rows = 0; rows < ROWS; rows++)
       {
           for(int cols = 0; cols < COLS; cols++)
          {
              theFile >> grid[rows][cols];
          }
       }
    }
    theFile.close();
}

// Output Function 1
void printGrid(char grid[][COLS])
{
    ofstream thefile("output.txt");
    int noofcols = 0;
    if(thefile.is_open())
    {   
      thefile << endl;
      for(int rows = 0; rows < COLS - 1; rows++)
      {
          noofcols++;
          for(int cols = 0; cols < ROWS; cols++)
          {
              thefile << grid[rows][cols] << " ";
          }
          thefile << endl;
      }
    thefile << "   ";
    thefile << endl;
    thefile.close();
   }
}
 
// Output Function 2
void printData(struct gridData &Data)
{
	ofstream thefile("Output.txt");
    if(thefile.is_open())
    {     
       if( Data.LR == true || Data.RL == true ||
            Data.TB == true || Data.BT == true)
       {
        Data.found = true;
       }
	   if(Data.found == true)
	   {
	    thefile << "The Correct Coordinates are: " << "[" << Data.rows << "," << Data.cols << "]" << endl;
   	}	
   	else if(Data.found == false)
  	{
	    thefile << endl;
	    thefile << "The entered word hadn't been found!!!" << endl;
	    thefile << endl;
  	}
    thefile << endl << endl;
    }
}

// Output Function 3
void askForSearchTerm(struct gridData &Data)
{
     int n;
     string word;
    cout << "Enter number of words: "; 
    cin >> n;
    cout << "Now, enter " << n << " words to be searched in uppercase of the Grid: " << endl;
    for(int x = 0; x < n; x++)
    {
    	cin >> word;
	}  
    Data.words = word;
}

// Bool for Horizintal Left to Right
bool searchForHorizontalLtoR(char grid[][COLS], struct gridData &Data)
{
    char GridRow[ROWS];
    int rows = 0;
    while(rows < ROWS)
    {
        for(int i = 0; i < ROWS; i++)
        {
            GridRow[i] = grid[rows][i];
        } 
        for(int x = 0; x < (ROWS - Data.words.size()); x++)
        {
            int y = 0;
            while((y < Data.words.size()) && (Data.words[y] == GridRow[x+y]))
            {
                y++;
            }
            if(y == Data.words.size())
            {
                Data.cols = x;
                Data.rows = rows;
                return true;
            }
        }
        rows++;
    }
    return false;
}

// Bool for Horizintal Right to Left
bool searchForHorizontalRtoL(char grid[][COLS], struct gridData &Data)
{
    char GridRow[ROWS];
    int rows = 0;
    int inverserows = 0;
    while(rows < ROWS)
    {
        inverserows = 0;
        for(int x = (ROWS - 1); x >= 0; x--)
        {
            GridRow[inverserows] = grid[rows][x];
            inverserows++;
        } 
        for(int y = 0; y < (ROWS - Data.words.size()); y++)
        {
            int z = 0;
            while((z < Data.words.size()) && (Data.words[z] == GridRow[y+z]))
            {
                z++;
            }
            if(z == Data.words.size())
            {
                Data.cols = 11 - y;
                Data.rows = rows;
                return true;
            }
        }
        rows++;
    }
    return false;
}

// Bool for Vertical top to bottom
bool searchForVerticalTtoB(char grid[][COLS], struct gridData &Data)
{
    char GridCol[COLS];
    int cols = 0;
    while(cols < COLS)
    {
        for(int x = 0;x < COLS; x++)
        {
            GridCol[x] = grid[x][cols];
        } 
        for(int y = 0; y < (COLS - Data.words.size()); y++)
        {
            int z = 0;
            while((z < Data.words.size()) && (Data.words[z] == GridCol[y+z]))
            {
                z++;
            }
            if(z == Data.words.size())
            {
                Data.cols = cols;
                Data.rows = y; 
                return true;
            }
        }
        cols++;
    }
    return false;
}

// Bool for Vertical bottom to top
bool searchForVerticalBtoT(char grid[][COLS], struct gridData &Data)
{
    char GridCol[COLS];
    int cols= 0;
    while(cols < COLS)
    {
        int inversecols = 0;
        for(int x = (COLS - 1); x >= 0; x--)
        {
            GridCol[inversecols] = grid[x][cols];
            inversecols++;
        } 
        for(int y = 0; y < (COLS - Data.words.size()); y++)
        {
            int z =0;
            while((z < Data.words.size()) && (Data.words[z] == GridCol[y+z]))
            {
                z++;
            }
            if(z == Data.words.size())
            {
                Data.cols = cols;
                Data.rows = 11 - y;
                return true;
            }
        }
        cols++;
    }
  return false;
}

// Search Function
void search(char grid[][COLS], struct gridData &Data)
{
    Data.LR = searchForHorizontalLtoR(grid, Data);
    if(Data.LR == false)
    {
        Data.RL = searchForHorizontalRtoL(grid, Data);
    }
    if(Data.LR == false &&  Data.RL == false)
    {
        Data.TB = searchForVerticalTtoB(grid, Data);
    }
    if(Data.LR == false &&  Data.RL == false &&
          Data.TB == false)
    {
        Data.BT = searchForVerticalBtoT(grid, Data);
    }
}

void reverseStr(string& input)
{
    int length = input.length();
    for (int x = 0; x < length / 2; x++)
    {
        swap(input[x], input[length - x - 1]);
    }
}

// Main Function
int main()
{
	string input;
	char grid[ROWS][COLS];
	gridData Data;
    Data.initialize();
	char option = ' ';
	while (option != 'Q' && option != 'q')
	{
		cout << "\n1- Create Grid and Search words (C)\n";
		cout << "2- Quit (Q)\n";
		cout << "\nEnter your option: ";
		cin >> option;
		if (option == 'C' || option == 'c')
		{     
           getGrid(grid);
           printGrid(grid);
           askForSearchTerm(Data);
	       reverseStr(input);
           search(grid, Data);
           printData(Data);
           cout << "Results have been saved in the File" << endl;
		}
		else if (option == 'Q' || option == 'q')
		{
			cout << "\nProgram will now close!!!\n";
		}
		else
		{
			cout << "\nOption not available!!!\nChoose valid option!\n";
	}
  }
    return 0;
}
