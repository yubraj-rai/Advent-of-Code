#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std; 
int main(void)
{
	vector<string> vLine ;
	while (true) {
		string strLine ;
		getline(cin, strLine) ;
		if(strLine.empty() || cin.eof())
			break ;	

		vLine.push_back(strLine) ; ;
	}

	int sum = 0 ;
	vector<string>::iterator itr = vLine.begin() ;
	while(itr != vLine.end()) {
		map<int, string> mDigit ;
		string tempStr = (*itr)  ;
		for(int i = 0 ; i < tempStr.size() ; i++) {
			if(isdigit(tempStr[i]))
				mDigit[i] = tempStr[i];
		}

		string tempSecondStr ;
		if(mDigit.begin()->first != mDigit.rbegin()->first)
			tempSecondStr = (mDigit.begin()->second + mDigit.rbegin()->second) ;
		else
			tempSecondStr = (mDigit.begin()->second + mDigit.begin()->second) ;

		sum += stoi(tempSecondStr) ;
		mDigit.clear() ;
		itr++ ;
	}

	cout<<"Value of sum: "<<sum<<endl;

	return 0 ;
}
