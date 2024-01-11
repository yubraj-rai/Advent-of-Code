/**
 *Implimentation: STL and OOPS
 (i-1, j-1)  (i-1,j)  (i-1, j+1)

 (i,j-1)     (i,j)    (i  , j+1)

 (i+1, j-1)  (i+1,j)  (i+1, j+1)
 **/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
vector<string> vMatrix ;

class Matrix {

	public:
		Matrix(int x, int y, int h, int w) : xpos(x), ypos(y), height(h), width(w) {}

		const std::string& GetName() const {
			return strName;
		}

		map<string, map<string, pair<int, int> > >& getCoordinateCache() {
			return mapCordinateXY ;
		}


		void setNames() {
			if (xpos == 0 && ypos == 0) {         
				strName = "top-left";
			} else if (xpos == 0 && ypos == width - 1) {    
				strName = "top-right";
			} else if (xpos == height - 1 && ypos == 0)  { 
				strName = "bottom-left";
			} else if (xpos == height - 1 && ypos == width - 1) {
				strName = "bottom-right";
			} else if (xpos > 0 && xpos < height - 1 && ypos == 0) {
				strName = "left-wall";
			} else if (xpos == 0 && ypos > 0 && ypos < width - 1) {
				strName = "top-wall";
			} else if (xpos == height - 1 && ypos > 0 && ypos < width - 1) {
				strName = "bottom-wall";
			} else if (xpos > 0 && xpos < height - 1 && ypos == width - 1) {
				strName = "right-wall";
			} else {
				strName = "all-side";
			}
		}

		void insertCacheXY() {

			int xStart, xFinish ;
			int yStart, yFinish ;
			if(GetName() == "left-wall") {
				xStart = xpos-1 ;
				xFinish= xpos+1 ;
				yStart = ypos ;
				yFinish= ypos+1 ;
			} else if(GetName() == "right-wall") {
				xStart = xpos-1 ;
				xFinish= xpos+1 ;
				yStart = ypos-1 ;
				yFinish= ypos ;
			} else if(GetName() == "top-wall") {
				xStart = xpos ;
				xFinish= xpos+1 ;
				yStart = ypos-1 ;
				yFinish= ypos+1 ;
			} else if(GetName() == "top-wall") {
				xStart = xpos-1 ;
				xFinish= xpos ;
				yStart = ypos-1 ;
				yFinish= ypos+1 ;
			} else if(GetName() == "top-left") {
				xStart = xpos;
				xFinish= xpos+1 ;
				yStart = ypos ;
				yFinish= ypos+1 ;
			} else if(GetName() == "top-right") {
				xStart = xpos;
				xFinish= xpos+1 ;
				yStart = ypos-1 ;
				yFinish= ypos ;
			} else if(GetName() == "bottom-left") {
				xStart = xpos-1;
				xFinish= xpos ;
				yStart = ypos ;
				yFinish= ypos+1 ;
			} else if(GetName() == "bottom-right") {
				xStart = xpos-1;
				xFinish= xpos ;
				yStart = ypos-1 ;
				yFinish= ypos ;
			} else if(GetName() == "all-side") {
				xStart = xpos-1;
				xFinish= xpos+1 ;
				yStart = ypos-1 ;
				yFinish= ypos+1 ;
			}

			for(size_t i = xStart; i <= xFinish; i++) {
				for(size_t j = yStart; j <= yFinish; j++ ) {
					if(i == xpos && j == ypos)
						continue ;

					if(isdigit(vMatrix[i][j])) {
						if(i == xpos-1) {
							mapCordinateXY["toprow"][getPosition(j)] = make_pair(i, j);
						} else if(i == xpos) {
							mapCordinateXY["midrow"][getPosition(j)] = make_pair(i, j);
						} else if(i == xpos+1) {
							mapCordinateXY["lowrow"][getPosition(j)] = make_pair(i, j);
						}
					}
				}
			}
		}

	private:
		int xpos;
		int ypos;
		int height;
		int width;
		string strName;
		map<string, map<string, pair<int, int> > > mapCordinateXY ;

		string getPosition(int j) const {
			if (j == ypos - 1) {
				return "left";
			} else if (j == ypos) {
				return "mid";
			} else if (j == ypos + 1) {
				return "right";
			} else {
				return "";
			}
		}
};

class Solution
{
	public:
		Solution() : iSum(0){
		}

		~Solution() {
		}

		void GetSum() const {
			cout<<"sum is: "<<iSum<<endl;
		}

		void ReadLines() {
			string line ;
			while(true) {
				getline(cin, line, '\n') ;
				if(line.empty() || cin.eof())
					break ;

				vMatrix.push_back(line) ;
				line.clear() ;
			}
		}

		void processPartNumber(map<string, string>& mapTemp, string sPosition, int xpos, int ypos) {
			size_t k ;
			string digits = "" ;
			for(k = ypos-1; k >= 0 ; k--) {
				if(!isdigit(vMatrix[xpos][k])) {
					k++ ;
					break ;
				}
			}
			for(; k < vMatrix[xpos].size() ; k++) {
				if(isdigit(vMatrix[xpos][k]))
					digits += vMatrix[xpos][k] ;
				else
					break ;
			}
			mapTemp[sPosition] = digits ;
		}

		void processMatrix()
		{
			for(size_t i = 0 ; i < vMatrix.size(); i++) {
				for(size_t j = 0 ; j < vMatrix[i].size(); j++) {
					if(!isdigit(vMatrix[i][j]) && vMatrix[i][j] != '.') {
						Matrix* pMatrix = new Matrix(i, j, vMatrix.size(), vMatrix[i].size());
						pMatrix->setNames() ;
						pMatrix->insertCacheXY() ;

						if(pMatrix->getCoordinateCache().size() > 2) {
							continue ;
						}

						vector<string> vDigits ;
						map<string, map<string, pair<int, int> > >::iterator it = pMatrix->getCoordinateCache().begin() ;
						for(; it != pMatrix->getCoordinateCache().end(); it++) {

							map<string, string> mapTemp ;
							mapTemp["left"]  = "L" ;
							mapTemp["mid"]   = "m" ;
							mapTemp["right"] = "R" ;

							if(it->first == "toprow" || it->first == "lowrow") {
								for(map<string, pair<int,int> >::iterator itr = it->second.begin(); itr != it->second.end(); itr++) {
									processPartNumber(mapTemp, itr->first, itr->second.first, itr->second.second) ;
									if(mapTemp["left"] == mapTemp["mid"] || 
									   mapTemp["right"] == mapTemp["mid"] ||
									  (mapTemp["left"] == mapTemp["mid"] && 
									   mapTemp["right"] == mapTemp["mid"]))
										continue ;
									else {
										vDigits.push_back(mapTemp[itr->first]) ;
									}
								}

								mapTemp.clear() ;

							} else if(it->first == "midrow") {
								for(map<string, pair<int,int> >::iterator itr = it->second.begin(); itr != it->second.end(); itr++) {
									processPartNumber(mapTemp, itr->first, itr->second.first, itr->second.second) ;
									vDigits.push_back(mapTemp[itr->first]) ;
								}
							}
						}
						if(vDigits.size() ==  2) {
							iSum += (stoi(vDigits[0]) * stoi(vDigits[1])) ;
						}

						delete pMatrix ;
					}
				}
			}
		}

	private:

		int iSum ;
} ;

int main(void)
{
	Solution solution;
	solution.ReadLines() ;
	solution.processMatrix() ;
	solution.GetSum() ;
	return 0 ;
}
