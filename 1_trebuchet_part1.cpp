#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Solution {
	private:
		vector<string> vLines;

	public:
		void ReadLines() {
			while (true) {
				string strLine;
				getline(cin, strLine);
				if (strLine.empty() || cin.eof())
					break;

				vLines.push_back(strLine);
			}
		}

		int ProcessLines() {
			int sum = 0;
			for (vector<string>::iterator itr = vLines.begin(); itr != vLines.end(); ++itr) {
				map<int, string> mDigit;
				string tempStr = (*itr);
				for (int i = 0; i < tempStr.size(); ++i) {
					if (isdigit(tempStr[i]))
						mDigit[i] = tempStr[i];
				}

				string tempSecondStr;
				if (mDigit.begin()->first != mDigit.rbegin()->first)
					tempSecondStr = (mDigit.begin()->second + mDigit.rbegin()->second);
				else
					tempSecondStr = (mDigit.begin()->second + mDigit.begin()->second);

				sum += atoi(tempSecondStr.c_str());
				mDigit.clear();
			}
			return sum;
		}
};

int main() {
	Solution solution;
	solution.ReadLines();

	cout << "Value of sum: " << solution.ProcessLines() << endl;

	return 0;
}

