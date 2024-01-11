#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Solution {
	private:
		map<string, int> mapNumbers;
		vector<string> vLines;

	public:
		Solution() {
			Initialize();
		}

		void Initialize() {
			mapNumbers["zero"]   = 0 ;
			mapNumbers["one"]    = 1 ;
			mapNumbers["two"]    = 2 ;
			mapNumbers["three"]  = 3 ;
			mapNumbers["four"]   = 4 ;
			mapNumbers["five"]   = 5 ;
			mapNumbers["six"]    = 6 ;
			mapNumbers["seven"]  = 7 ;
			mapNumbers["eight"]  = 8 ;
			mapNumbers["nine"]   = 9 ;
		}

		void ReadLines() {
			string line;
			while (true) {
				getline(cin, line, '\n');
				if (line.empty() || cin.eof())
					break;

				vLines.push_back(line);
				line.clear();
			}
		}

		bool IsNumber(const string& strLine, vector<int>& vDigitList) {
			int i = 0;
			while (i < strLine.size()) {
				if (isdigit(strLine[i])) {
					vDigitList.push_back(strLine[i] - '0');
				} else {
					for (map<string, int>::iterator it = mapNumbers.begin(); it != mapNumbers.end(); ++it) {
						size_t foundPos = strLine.find(it->first, i);
						if (string::npos != foundPos && foundPos == i) {
							vDigitList.push_back(it->second);
						}
					}
				}
				i++;
			}

			return !vDigitList.empty();
		}

		int ProcessLines() {
			int sum = 0;
			for (vector<string>::iterator itr = vLines.begin(); itr != vLines.end(); ++itr) {
				vector<int> vDigitList;
				if (IsNumber(*itr, vDigitList)) {
					stringstream ss;
					ss << vDigitList.front();
					string strFirst = ss.str();
					ss.str("");  // Clear the stringstream
					ss << vDigitList.back();
					string strLast = ss.str();
					sum += atoi((strFirst + strLast).c_str());
				}
			}
			return sum;
		}
};

int main() {
	Solution solution;
	solution.ReadLines();
	int sum = solution.ProcessLines();

	cout << sum << endl;

	return 0;
}

