#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std; 
class Solution
{
	public:
		Solution():iRedBallCount(12), iBlueBallCount(13), iGreenBallCount(14), iGameTotalCounter(0) { }
		~Solution(){ }

		int GetGameTotalCounter() const
		{
			return iGameTotalCounter ;
		}

		void LTrim(string & str, char ch)
		{
			size_t chFirst;
			if ((chFirst = str.find_first_not_of(ch)) != string::npos)
				str.erase(0, chFirst);
			else
				str.erase();
		}

		void RTrim(string & str, char ch)
		{
			size_t chFirst;
			if ((chFirst = str.find_last_not_of(ch)) != string::npos
				&& ++chFirst < str.length())
				str.erase(chFirst, str.length());
			else if (str.empty())
				str.erase();
		}

		vector<string> SplitLines(string strLine, string strDelimiter)
		{
			//cout<<"=== starting SplitLines() ==="<<endl;
			//cout<<"strLine: "<<strLine<<endl;
			//cout<<"strDelimiter: "<<strDelimiter<<endl;

			size_t start = 0 ;

			string token ;
			vector<string> vToken ;
			size_t end ; //= strLine.find(strDelimiter, start) ;
			while((end = strLine.find(strDelimiter, start)) != string::npos )
			{
				token = strLine.substr(start, end-start) ;
				start = end+strDelimiter.length() ;

				//cout<<"end: "<<end<<endl;
				//cout<<"token: "<<token<<endl;
				//cout<<"start: "<<start<<endl;
				vToken.push_back(token) ;
				//exit(0) ;
			}

			vToken.push_back(strLine.substr(start)) ;
			//cout<<"=== ending SplitLines() ==="<<endl;
			return vToken ;

		}

		void GetGameLines()
		{
			//cout<<"===starting GetGameLines()==="<<endl;
			while(true)
			{
				string line ;
				getline(cin, line, '\n') ;
				if(line.empty() || cin.eof())
					break ;

				//cout<<endl<<endl<<endl ;
				//cout<<"line: "<<line<<endl;
				vLines.push_back(line) ;
				line.clear() ;
			}
			//cout<<"===ending GetGameLines()==="<<endl;
		}

		void ProcessGameLines()
		{
			//cout<<"===starting ProcessGameLines()==="<<endl ;
			/*Game 1: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue */
			vector<string>::iterator itr = vLines.begin() ;
			while(itr != vLines.end())
			{
				string tempGameKey = (*itr).substr(0, (*itr).find(":")) ;
				//cout<<"tempGameKey : "<<tempGameKey<<endl;
				vector<tuple<int, int , int> > vTuple ;
				vector<string> vBoxLines  = SplitLines(((*itr).substr((*itr).find(":")+1)), ";") ;
				vector<string>::iterator itr1 = vBoxLines.begin() ;
				while(itr1 != vBoxLines.end())
				{
					//cout<<"Boxlines: "<<*itr1<<endl;
					vector<pair<string,string> > pColor ;
					vector<string> vColorsLines = SplitLines((*itr1), ",") ;
					vector<string>::iterator itr2 = vColorsLines.begin() ;
					while(itr2 != vColorsLines.end())
					{
						//cout<<"Colorlines: "<<*itr2<<endl;
						size_t pos ;
						pair<string, string> pColorValue ;
						LTrim((*itr2), ' ') ;
						RTrim((*itr2), ' ') ;
						if(pos = (*itr2).find(" ") != string::npos)
						{
							string	color = (*itr2).substr(pos+1) ;
							string	value = (*itr2).substr(0,pos+1) ;
							LTrim(color, ' ') ;
							RTrim(color, ' ') ;

							LTrim(value, ' ') ;
							RTrim(value, ' ') ;
							
							//cout<<"color: "<<color<<endl;
							//cout<<"value: "<<value<<endl;
							pColorValue = make_pair(color, value) ;
						}

						pColor.push_back(pColorValue) ;
						++itr2 ;
					}

					int iRed	= 0;
					int iGreen	= 0;
					int iBlue	= 0;
					vector<pair<string,string> >::iterator itr3 = pColor.begin() ;
					while(itr3 != pColor.end())
					{
						if((*itr3).first == "red")
						{
							iRed = stoi((*itr3).second) ;
						}

						if((*itr3).first == "blue")
						{
							iBlue = stoi((*itr3).second) ;
						}

						if((*itr3).first == "green")
						{
							iGreen = stoi((*itr3).second) ;
						}
						++itr3 ;
					}

					vector<pair<string,string> >().swap(pColor) ;
					tuple<int, int , int> rgbTuple(iRed , iGreen, iBlue);
					vTuple.push_back(rgbTuple) ;
					++itr1 ;
				}


				mapLine.insert(make_pair(tempGameKey, vTuple)) ;
				vector<tuple<int, int , int> >().swap(vTuple);
				++itr ;
			}
		}

		void MatchingGamesIDTotal()
		{
			cout<<"===starting MatchingGamesIDTotal()==="<<endl;
			//Game 1: 1 green, 2 blue; 15 blue, 12 red, 2 green; 4 red, 6 blue; 10 blue, 8 red; 3 red, 12 blue;
			map<string, vector<tuple<int, int , int> > >:: iterator itr = mapLine.begin() ;
			while(itr != mapLine.end())
			{
				int debug_counter = 1 ;
				//cout<<"Game ID: "<<itr->first<<endl ;
				bool bValidGame = true ;
				vector<tuple<int, int , int> >::iterator itr1 = itr->second.begin() ;
				while(itr1 != itr->second.end())
				{
					//cout<<"grab time: "<<debug_counter<<endl;  
					//cout<<"R "<<get<0>(*itr1)<< endl;
					//cout<<"G "<<get<1>(*itr1)<< endl;
					//cout<<"B "<<get<2>(*itr1)<< endl;

					if(get<0>(*itr1) > iRedBallCount || 
							get<1>(*itr1) > iBlueBallCount ||
							get<2>(*itr1) > iGreenBallCount)
					{
						bValidGame = false ;
					}

					debug_counter++ ;
					itr1++ ;
				}

				if(true == bValidGame)
				{
					string game  = itr->first ;
					int iGameNumber = stoi(game.substr(game.find(" ")+1)) ;
					iGameTotalCounter += iGameNumber ;
				}

				itr++ ;
			}
		}


	private:
		map<string, vector<tuple<int, int , int> > > mapLine ;
		vector<string> vLines ;
		int iRedBallCount ;
		int iBlueBallCount ;
		int iGreenBallCount ;
		int iGameTotalCounter ;
		vector<int> vGamesIDs ;

} ;


int main(void)
{
	Solution solution;
	solution.GetGameLines();
	solution.ProcessGameLines();
	solution.MatchingGamesIDTotal();

	cout << "Total games counter: " << solution.GetGameTotalCounter() << endl;

	return 0 ;
}
