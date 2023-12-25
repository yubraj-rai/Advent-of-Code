/**
 *Implimentation: STL and OOPS
 00 01 02 03 04 05 06
 10 11 12 13 14 15 16
 20 21 22 23 24 25 26
 30 31 32 33 34 35 36
 40 41 42 43 44 45 46

Idea:
=>  (i,j) = digit, check until symbol or dot
=>  check if any of the (i,j) digit crosses symbol in all direction

(i-1, j-1)  (i-1,j)  (i-1, j+1)

(i,j-1)     (i,j)    (i  , j+1)

(i+1, j-1)  (i+1,j)  (i+1, j+1)
 **/

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
vector<string> vMatrix ;

class Matrix {

	public:

		int GetXPos() const {
			return xpos;
		}

		void SetXPos(int newXPos) {
			xpos = newXPos;
		}

		int GetYPos() const {
			return ypos;
		}

		void SetYPos(int newYPos) {
			ypos = newYPos;
		}

		int GetHeight() const {
			return height;
		}

		void SetHeight(int newHeight) {
			height = newHeight;
		}

		int GetWidth() const {
			return width;
		}

		void SetWidth(int newWidth) {
			width = newWidth;
		}

		const std::string& GetName() const {
			return strName;
		}

		void SetName(const string& newName) {
			strName = newName;
		}

		bool checkIfSymbolExist(char charac)
		{
			if ((charac >= '0' && charac <= '9') || charac == '.')
			{
				return false;
			}
			return true ;
		}

		void DisplayMatrix()
		{
			for(size_t i = 0 ; i < vMatrix.size() ; i++)
			{
				for(size_t j = 0 ; j <vMatrix[i].size(); j++)
				{
					cout<<vMatrix[i][j] ;
				}
				cout<<endl;
			}
		}
		//const function can't  modify the constant 
		//object for which it is called
		bool isMatrixCorner() {
			if (xpos == 0 && ypos == 0) {
				SetName("top-left");
				return true;
			} else if (xpos == 0 && ypos == width - 1) {
				SetName("top-right");
				return true;
			} else if (xpos == height - 1 && ypos == 0) {
				SetName("bottom-left");
				return true;
			} else if (xpos == height - 1 && ypos == width - 1) {
				SetName("bottom-right");
				return true;
			}

			return false;
		}

		bool isMatrixWall() {
			if (xpos > 0 && xpos < height - 1 && ypos == 0) {
				SetName("left-wall");
				return true;
			} else if (xpos == 0 && ypos > 0 && ypos < width - 1) {
				SetName("top-wall");
				return true;
			} else if (xpos == height - 1 && ypos > 0 && ypos < width - 1) {
				SetName("bottom-wall");
				return true;
			} else if (xpos > 0 && xpos < height - 1 && ypos == width - 1) {
				SetName("right-wall");
				return true;
			}

			return false;
		}

		bool CheckCornerNeighbours() {
			if(GetName() == "top-left") {
				if(checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()+1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()+1]))
					return true ;

			}
			else if(GetName() == "top-right") {
				if(checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()-1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()-1]))
					return true ;

			}
			else if(GetName() == "bottom-left") {
				if(checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()+1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()+1]))
					return true ;

			}
			else if(GetName() == "bottom-right") {
				if(checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()-1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()-1]))
					return true ;
			}
			return false ;
		}

		bool checkWallNeighbours()
		{
			if(GetName() == "left-wall") {
				if(checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()+1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()+1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()+1]))
					return true ;

			}
			else if(GetName() == "top-wall") {
				if(checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()-1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()+1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()+1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()-1]))
					return true ;

			}
			else if(GetName() == "bottom-wall") {
				if(checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()-1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()+1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()+1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()-1]))
					return true ;

			}
			else if(GetName() == "right-wall") {
				if(checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()]) ||
						checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()-1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()-1]) ||
						checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()-1]))
					return true ;
			}
			return false ;
		}

		bool checkAllSideNeighbours()
		{
			if(checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()]) ||
					checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()]) ||
					checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()-1]) ||
					checkIfSymbolExist(vMatrix[GetXPos()][GetYPos()+1]) ||
					checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()+1]) ||
					checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()-1]) ||
					checkIfSymbolExist(vMatrix[GetXPos()-1][GetYPos()-1]) ||
					checkIfSymbolExist(vMatrix[GetXPos()+1][GetYPos()+1])) {
				return true ;
			}

			return false ;
		}

	private:
		int xpos;
		int ypos;
		int height;
		int width;
		string strName;
};

class Solution
{
	public:
		Solution() : iSum(0){
		}

		~Solution() {
		}

		void ReleaseMemory()
		{
			vector<string>().swap(vMatrix);
		}


		int GetSum() const {
			cout<<"sum is: "<<iSum<<endl;
		}

		void ReadLines()
		{
			string line ;
			while(true)
			{
				getline(cin, line, '\n') ;
				if(line.empty() || cin.eof())
					break ;

				vMatrix.push_back(line) ;
				line.clear() ;
			}
		}


		void processMatrix()
		{
			//cout<<"size of vMatrix.size()       : " <<vMatrix.size()<<endl;
			//cout<<"size of vMatrix[1].size()    : " <<vMatrix[1].size()<<endl;
			//cout<<"length of vMatrix[0][0]      : " <<vMatrix[0][0]<<endl
			//cout<<"length of vMatrix[1][1]      : " <<vMatrix[1][1]<<endl;

			for(size_t i = 0 ; i < vMatrix.size() ; i++)
			{
				for(size_t j = 0 ; j <vMatrix[i].size(); j++)
				{
					if(isdigit(vMatrix[i][j]))
					{
						size_t k = 0;
						size_t l ;
						string digits  = "" ;
						for(k = j; k < vMatrix[i].size() ; k++)
						{
							if(isdigit(vMatrix[i][k]))
								digits += vMatrix[i][k] ;
							else
								break ;
						}

						bool found = false ;
						for(l = j ; l <= k-1; l++)
						{
							Matrix* pMatrix = new Matrix() ;
							pMatrix->SetXPos(i) ;
							pMatrix->SetYPos(l) ;
							pMatrix->SetHeight(vMatrix.size()) ;
							pMatrix->SetWidth(vMatrix[i].size()) ;

							if(pMatrix->isMatrixCorner() && pMatrix->CheckCornerNeighbours()) {
								found = true ;
							}
							else if(pMatrix->isMatrixWall() && pMatrix->checkWallNeighbours()) {
								found = true ;
							}
							else if(pMatrix->GetName().empty() && pMatrix->checkAllSideNeighbours()){
								found = true ;
							}

							delete pMatrix ;
						}

						if (found) {
							iSum +=stoi(digits) ;
						}
						j = l ;
					}
				}
			}
		}

	private:

		int iSum ;
		//vector<string> vMatrix ;


} ;

int main(void)
{
	Solution solution;
	solution.ReadLines() ;
	solution.processMatrix() ;
	solution.GetSum() ;


	return 0 ;
}
