#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

typedef pair <string,string> ss;
map <string,string> myMap;
map <string,int> UNQ,lowerCase;
int LabelCounter=0;


//this method takes a string and clear out spaces
string withoutSpace( string s ){
	string newStr="";
	for( auto e : s ) {
		if( e != ' ' ) newStr+=e;
	}
	return newStr;
}

void parseThis( string s , ofstream& write );

//count number of equal signs in a string
int countEquals( string s ){
	int count=0;
	for( auto e:s ){
		count += e=='=';
	}
	return count;
}

//find the location of the first equal sign
int findEqual( string s ){
	for( int i=0 ; i<(int)s.size() ; i++ ){
		if( s[i] == '=' ) return i;
	}
	return -1;
}

// true if string contains a plus sign wrong if it does not
bool containsPlus( string s ){
	for( auto e : s )
		if( e == '+' ) return true;
	return false; 
}

// true if string contains multiplication sign wrong if it does not
bool containsMult( string s ){
	for( auto e : s )
		if( e == '*' ) return true;
	return false;
}

//true if contains pow funciton, wring if it does not
bool containsPow( string s ){
	for( int i=1 ; i<(int)s.size()-2 ; i++ ) if( s[i-1] == 'p' && s[i] == 'o' && s[i+1] == 'w' && s[i+2] == '(' ) return true;
	return false; 
}

// check if a string is an expression
bool isExpression( string s ){
	if( containsPow(s) || containsMult(s) || containsPow(s) ) return true;
	return false;
}

//check if a string is variable
bool isVariable( string s ){
	for( int i=1 ; i<(int)s.size()-1 ; i++ ) if( s[i+1]!=' ' && s[i-1]!=' ' && s[i] == ' ' ) return false; 
	s=withoutSpace( s );
	if( isExpression(s) ) return false;
	for( auto e:s )
		if( e == '(' || e == ')' ) return false;
	return true;
}

//checks if operations are valid or not
bool legalOperations( string s ){
	for( int i=0 ; i<(int)s.size()-1 ; i++ ){
		if( (s[i] == '+' || s[i] == '*') && ( s[i+1] == '+' || s[i+1] == '*' ) )	return false;
		if( s[i] == '(' && ( s[i+1] == '+' || s[i+1] == '*' ) ) 	return false;
		if( (s[i] == '+' || s[i] == '*' ) && s[i+1] == ')' )	return false;
		if( s[i] == ')' && !( s[i+1] == '+' || s[i+1] == '*' || s[i+1] == ')' || s[i+1] == ',' ) ) 	return false;
		if( s[i+1] == '(' && !( s[i] == '(' || s[i] == '+' || s[i] == '*' || s[i] == ',' || s[i] == 'w' ) )	return false;
	}
	return true;
}

//checks if the pharanteses are balanced or not
bool isBalanced( string s ){
	int ph=0;
	for( auto e:s ){
		if( e == '(' ) ph++;
		if( e == ')' ) ph--;
		if( ph < 0 ) return false;
	}
	return ph==0;
}

//checks if usage of power function is legal or not
bool legalPow( string s ){
	for( int i=3 ; i<(int)s.size() ; i++ ){
		if( s[i-3] == 'p' && s[i-2] == 'o' && s[i-1] == 'w' && s[i] == '(' ){
			int numComas=0,coma=0,end=0;
			for( int j=i+1 , ph=0 ; j<(int)s.size() ; j++ ){
				if( s[j] == '(' ) ph++;
				if( s[j] == ')' ) ph--;
				if( s[j] == ',' && !ph ){
					numComas++;
					coma=j;
				}
				if( ph < 0 ){
					end=j;
					break;
				}
			}
			if( numComas != 1 ) return false;
			if( coma == i+1 ) return false;
			if( coma == end-1 ) return false;
		}
	}
	return true;
}

// find syntax errors here
bool isIllegal( string s ){
	if( countEquals( s ) > 1 ) return true;
	if( countEquals( s ) == 0  && ( !isBalanced( s ) || !legalOperations( s ) || !legalPow( s ) ) )  return true;
	if( countEquals( s ) == 0 ) return false;
	string left=s.substr( 0 , findEqual( s ) ),right=s.substr( findEqual( s )+1 , s.size() );
	if( !isVariable(left) ) return true;
	if( !isBalanced( right ) || !legalOperations( right ) || !legalPow( right ) ) return true;
	return false;
}


//convert a hexadecimal number given as a string to a integer
int hexaToDec( string s ){
	int res=0;
	int pow=1;
	for( int i=s.size()-1 ; i>=0 ; i-- ){
		if( s[i] >= 'a' && s[i] <= 'f' ){
			res+=(s[i]-'a'+10)*pow;
		}else{
			res+=(s[i]-'0')*pow;
		}
		pow*=16;
	}
	return res;
}

//assembly implementation of power function
void doPower( ofstream& write ){
	LabelCounter++;

	write << "  POP AX" << endl;
	write << "  MOV _blo,AX" << endl;
	write << "  POP AX" << endl;
	write << "  MOV _bhi,AX" << endl;
	write << "  POP AX" << endl;
	write << "  MOV _varlo,AX" << endl;
	write << "  POP AX" << endl;
	write << "  MOV _varhi,AX" << endl;
	write << "  MOV _powlo,1d" << endl;
	write << "  MOV _powhi,0" << endl;
	write << "  MOV _reslo,1d" << endl;
	write << "  MOV _reshi,0" << endl;
	write << "  MOV _dummylo,0" << endl;
	write << "  MOV _dummyhi,0" << endl;
	write << "  MOV _carry,0" << endl;
	write << "  MOV _dummylo,0" << endl;
	write << "  MOV AX,00" << endl;
	write << "  MOV BX,00" << endl;
	write << "  MOV CX,00" << endl;
	write << "  MOV DX,00" << endl;

	write << "Start" << LabelCounter << ":" << endl;

	write << "  MOV AX,_powlo" << endl;
	write << "  MOV BX,_blo" << endl;
	write << "  AND AX,BX" << endl;
	write << "  MOV CX,AX" << endl;
	write << "  MOV AX,_powhi" << endl;
	write << "  MOV BX,_bhi" << endl;
	write << "  AND AX,BX" << endl;
	write << "  ADD CX,AX" << endl;
	write << "  CMP CX,00" << endl;
	write << "  JE SkipRes" << LabelCounter << endl;
	write << "  MOV AX,_varlo" << endl;
	write << "  MOV BX,_reslo" << endl;
	write << "  MUL BX" << endl;
	write << "  MOV _dummylo,0" << endl;
	write << "  MOV _dummyhi,0" << endl; 
	write << "  ADD _dummyhi,DX" << endl;
	write << "  ADD _dummylo,AX" << endl;
	write << "  MOV AX,_varhi" << endl; 
	write << "  MOV BX,_reslo" << endl; 
	write << "  MUL BX" << endl;
	write << "  ADD _dummyhi,AX" << endl;
	write << "  MOV AX,_varlo" << endl; 
	write << "  MOV BX,_reshi" << endl; 
	write << "  MUL BX" << endl;
	write << "  ADD _dummyhi,AX" << endl;
	write << "  MOV AX,_dummyhi" << endl;
	write << "  MOV BX,_dummylo" << endl;
	write << "  MOV _reshi,AX" << endl;
	write << "  MOV _reslo,BX" << endl;

	write << "SkipRes" << LabelCounter << ":" << endl;

	write << "  MOV AX,_powlo" << endl;
	write << "  MOV BX,_powlo" << endl;
	write << "  ADD AX,BX" << endl;
	write << "  MOV _carry,00" << endl;
	write << "  JNC HC" << LabelCounter << endl;
	write << "  MOV _carry,1d" << endl;

	write << "HC" << LabelCounter << ":" << endl;

	write << "  MOV _powlo,AX" << endl;
	write << "  MOV AX,_powhi" << endl;
	write << "  MOV BX,_powhi" << endl;
	write << "  ADD AX,BX" << endl;
	write << "  ADD AX,_carry" << endl;
	write << "  MOV _powhi,AX" << endl;

	write << "expVar" << LabelCounter << ":" << endl;

	write << "  MOV DX,00" << endl;
	write << "  MOV AX,_varlo" << endl;
	write << "  MOV BX,_varlo" << endl;
	write << "  MUL BX" << endl;
	write << "  MOV _dummylo,00" << endl;
	write << "  MOV _dummyhi,00" << endl;
	write << "  ADD _dummylo,AX" << endl;
	write << "  ADD _dummyhi,DX" << endl;
	write << "  MOV AX,_varhi" << endl;
	write << "  MOV BX,_varlo" << endl;
	write << "  MUL BX" << endl;
	write << "  ADD _dummyhi,AX" << endl;
	write << "  MOV AX,_varlo" << endl;
	write << "  MOV BX,_varhi" << endl;
	write << "  MUL BX" << endl;
	write << "  ADD _dummyhi,AX" << endl;
	write << "  MOV AX,_dummylo" << endl;
	write << "  MOV BX,_dummyhi" << endl;
	write << "  MOV _varlo,AX" << endl;
	write << "  MOV _varhi,BX" << endl;

	write << "Compare" << LabelCounter << ":" << endl;

	write << "  MOV AX,_powhi" << endl;
	write << "  MOV BX,_bhi" << endl;
	write << "  CMP AX,BX" << endl;
	write << "  JNZ CompareHi" << LabelCounter << endl;
	write << "  MOV AX,_powlo" << endl;
	write << "  MOV BX,_blo" << endl;
	write << "  CMP AX,BX" << endl;
	write << "  JA Finish" << LabelCounter << endl;
	write << "  JMP Start" << LabelCounter << endl;

	write << "CompareHi" << LabelCounter << ":" << endl;

	write << "  CMP AX,BX" << endl;
	write << "  JA Finish" << LabelCounter << endl;
	write << "  JMP Start" << LabelCounter << endl;

	write << "Finish" << LabelCounter << ":" << endl;

	write << "  MOV AX,_reshi" << endl;
	write << "  MOV BX,_reslo" << endl;
	write << "  PUSH AX" << endl;
	write << "  PUSH BX" << endl;
}

//assembly implementation of multiplication
void doMult( ofstream& write ){
	LabelCounter++;
	write << "Start" << LabelCounter << ":" << endl;
	write << "MOV _dummylo,00" << endl;
	write << "MOV _dummyhi,00" << endl;
	write << "  MOV AX,00" << endl;
	write << "  MOV BX,00" << endl;
	write << "  MOV CX,00" << endl;
	write << "  MOV DX,00" << endl;

	write << "  POP AX" << endl;
	write << "  MOV _ylo,AX" << endl;
	write << "  POP AX" << endl;
	write << "  MOV _yhi,AX" << endl;
	write << "  POP AX" << endl;
	write << "  MOV _xlo,AX" << endl;
	write << "  POP AX" << endl;
	write << "  MOV _xhi,AX" << endl;
	write << "  MOV AX,_xlo" << endl;
	write << "  MOV BX,_ylo" << endl;
	write << "  MUL BX" << endl;
	write << "  ADD _dummylo,AX" << endl;
	write << "  ADD _dummyhi,DX" << endl;
	write << "  MOV AX,_xhi" << endl;
	write << "  MOV BX,_ylo" << endl;
	write << "  MUL BX" << endl;
	write << "  ADD _dummyhi,AX" << endl;
	write << "  MOV AX,_xlo" << endl;
	write << "  MOV BX,_yhi" << endl;
	write << "  MUL BX" << endl;
	write << "  ADD _dummyhi,AX" << endl;

	write << "Finish" << LabelCounter << ":" << endl;

	write << "  MOV AX,_dummyhi" << endl;
	write << "  PUSH AX" << endl;
	write << "  MOV AX,_dummylo" << endl;
	write << "  PUSH AX" << endl;
}

//assembly implementation of sum operation
void doSum( ofstream& write ){
	LabelCounter++;

	write << "Start" << LabelCounter << ":" << endl;
	write << "  MOV AX,00" << endl;
	write << "  MOV BX,00" << endl;
	write << "  MOV CX,00" << endl;
	write << "  MOV DX,00" << endl;
	write << "  MOV _carry,00" << endl;
	write << "  MOV _dummylo,00" << endl;

	write << "  POP AX" << endl;
	write << "  MOV _ylo,AX" << endl;
	write << "  POP AX" << endl;
	write << "  MOV _yhi,AX" << endl;
	write << "  POP AX" << endl;
	write << "  MOV _xlo,AX" << endl;
	write << "  POP AX" << endl;
	write << "  MOV _xhi,AX" << endl;
	write << "  MOV AX,_xlo" << endl;
	write << "  MOV BX,_ylo" << endl;
	write << "  ADD AX,BX" << endl;
	write << "  MOV _dummylo,AX" << endl;
	write << "  JNC HandleCarry" << LabelCounter << endl;
	write << "  MOV _carry,1d" << endl;

	write << "HandleCarry" << LabelCounter << ":" << endl;

	write << "  MOV AX,_xhi" << endl;
	write << "  MOV BX,_yhi" << endl;
	write << "  ADD AX,BX" << endl;
	write << "  ADD AX,_carry" << endl;

	write << "Finish" << LabelCounter << ":" << endl;

	write << "  PUSH AX" << endl;
	write << "  MOV AX,_dummylo" << endl;
	write << "  PUSH AX" << endl;
}

//split according to global multiplications
void pushToStack( string s , ofstream& write ){

	s=s+"*";
	string exp="";
	int countMult=0;
	for( int i=0,ph=0 ; i<=(int)s.size() ; i++ ){
		if( s[i] == '(' ) ph++;
		else if( s[i] == ')' ) ph--;
		if( s[i] == '*' && !ph ){
			countMult++;
			if( exp[0] >= '0' && exp[0] <= '9' ){
				int X=hexaToDec( exp );
				int lo=X & ((1<<16)-1);
				int hi=(X - lo)>>16;
				//cout << X << " " << hi << " " << lo << endl;
				//exit(0);
				if( hi == 0 )
					write << "  PUSH 0" << endl;	
				else
					write << "  PUSH " << hi << "d" << endl;
				if( lo == 0 )
					write << "  PUSH 0" << endl;	
				else
					write << "  PUSH " << lo << "d" << endl;
			}else if( exp.size()>=4 && exp[0]=='p' && exp[1]=='o' && exp[2]=='w' && exp[3]=='(' ){
				int cnt=0;
				string lft="",rght="";
				bool coma=false;
				for( int j=4 ; j<(int)exp.size()-1 ; j++ ){
					char e=exp[j];
					if( e == '(' ) cnt++;
					if( e == ')' ) cnt--; 
					if( e == ',' && !cnt ) coma=true;
					else{
						if( coma ) rght+=e;
						else lft+=e;
					}
				}
				parseThis(lft , write );
				parseThis(rght , write );
				doPower( write );
			}else if( exp[0]=='(' && exp[exp.size()-1]==')' ){
				parseThis( exp.substr( 1 , exp.size()-2 ) , write );
			}else{
				if( myMap.count( exp ) == 0 ){
					write << "  PUSH 0" << endl;
					write << "  PUSH 0" << endl;
				}else{
					write << "  MOV AX," << myMap[exp] << "hi" << endl;
					write << "  MOV BX," << myMap[exp] << "lo" << endl;
					write << "  PUSH AX" << endl;
					write << "  PUSH BX" << endl;
				}
			}
			exp="";
		}else
			exp+=s[i];
	}
	for( int i=1 ; i<countMult ; i++ )
		doMult( write );
}

//split according to global plusses
void parseThis( string s , ofstream& write ){
	s=s+"+";
	string exp="";
	int countPlusses=0;
	if( !s.size() ) return;
	for( int i=0,ph=0 ; i<(int)s.size() ; i++ ){
		if( s[i] == '(' )	ph++;
		else if( s[i] == ')' ) ph--;
		if( !ph && s[i] == '+' ){
			countPlusses++;
			pushToStack( exp , write );
			exp="";
		}
		else exp+=s[i];
	}

	for( int i=1 ; i<countPlusses ; i++ )
		doSum( write );
}


//assembly implementation of printing in hexadecimal
void Printer( ofstream& write ){
	LabelCounter++;
	write << "Start" << LabelCounter << ":" << endl;

	write << "  MOV AX,00" << endl;
	write << "  MOV BX,00" << endl;
	write << "  MOV CX,00" << endl;
	write << "  MOV DX,00" << endl;
	write << "  MOV _dummylo,00" << endl;

	write << "  POP AX" << endl;
	write << "  MOV _dummylo,AX" << endl;
	write << "  POP CX" << endl;

	write << "Initialize" << LabelCounter << ":" << endl;

	write << "  MOV DX,04" << endl;
	write << "  MOV BX,offset _number+7" << endl;
	write << "  MOV b[BX],'$'" << endl;

	write << "Generate" << LabelCounter << ":" << endl;

	write << "  MOV AX,CX" << endl;	
	write << "  AND AX,0fh" << endl;
	write << "  DEC BX" << endl;
	write << "  CMP AX,0ah" << endl;
	write << "  JAE Hexa" << LabelCounter << endl;	
	write << "  ADD AL,48d" << endl;
	write << "  MOV b[BX],AL" << endl;	
	write << "  JMP Cont" << LabelCounter << endl;	

	write << "Hexa" << LabelCounter << ":" << endl;	

	write << "  SUB AL,10d" << endl;
	write << "  ADD AL,65d" << endl;
	write << "  MOV b[BX],AL" << endl;

	write << "Cont" << LabelCounter << ":" << endl;		

	write << "  SHR CX,4" << endl;
	write << "  DEC DX" << endl;
	write << "  CMP DX,00" << endl;
	write << "  JNZ Generate" << LabelCounter << endl;

	write << "Print" << LabelCounter << ":" << endl;

	write << "  MOV AH,09" << endl;
	write << "  MOV DX,BX" << endl;
	write << "  INT 21h" << endl;

	LabelCounter++;

	write << "Start" << LabelCounter << ":" << endl;

	write << "  MOV CX,_dummylo" << endl;

	write << "Initialize" << LabelCounter << ":" << endl;

	write << "  MOV DX,04" << endl; 
	write << "  MOV BX,offset _number+7" << endl;
	write << "  MOV b[BX],'$'" << endl;

	write << "Generate" << LabelCounter << ":" << endl;

	write << "  MOV AX,CX" << endl;	
	write << "  AND AX,0fh" << endl;
	write << "  DEC BX" << endl;
	write << "  CMP AX,0ah" << endl;
	write << "  JAE Hexa" << LabelCounter << endl;	
	write << "  ADD AL,48d" << endl;
	write << "  MOV b[BX],AL" << endl;	
	write << "  JMP Cont" << LabelCounter << endl;	

	write << "Hexa" << LabelCounter << ":" << endl;	

	write << "  SUB AL,10d" << endl;
	write << "  ADD AL,65d" << endl;
	write << "  MOV b[BX],AL" << endl;

	write << "Cont" << LabelCounter << ":" << endl;		

	write << "  SHR CX,4" << endl;
	write << "  DEC DX" << endl;
	write << "  CMP DX,00" << endl;
	write << "  JNZ Generate" << LabelCounter << endl;

	write << "Print" << LabelCounter << ":" << endl;

	write << "  MOV AH,09" << endl;
	write << "  MOV DX,BX" << endl;
	write << "  INT 21h" << endl;

	write << "  MOV DL,10d" << endl;
	write << "  MOV AH,02" << endl;
	write << "  INT 21h" << endl;	
}

int main( int argc,  char* argv[] ){

	ifstream myFile( argv[1] );
	string abc=argv[1],writeHere="";
	bool flag=true;
	for( auto e:abc ){
		if( e == '.' ) flag=false;
		if( flag ) writeHere+=e;
	}
	writeHere+=".asm";
	ofstream write( writeHere );
	int row=1,count=1;
	string s;
	while( getline(myFile,s) ){
		if( s.size() && (s[s.size()-1] == '\r' || s[s.size()-1] == '\n') ) s=s.substr( 0 , s.size()-1 );
		if( isIllegal( withoutSpace( s ) ) ){
			cout << "Syntax error on row: " << row << endl;
			exit( 0 );
		}
		if( countEquals( s ) == 1 ){
			string left=withoutSpace( s.substr( 0 , findEqual( s ) ) );
			string tmp=left;
			std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower );
			if( myMap.count( left ) == 0 ){
				if( lowerCase.count( tmp ) == 0 ){
					myMap[left]=left;
					lowerCase[tmp]=1;
				}else{
					string dmp="dumpvar"+count;
					count++;
					myMap[left]=dmp;
				}
			}
		}
		row++;
	}
	myFile.clear();
	myFile.seekg(0, myFile.beg);

	cout << writeHere << " was generated." << endl;

	write << "JMP Start" << endl;
	map <string,string> :: iterator it;
	for( it = myMap.begin() ; it!=myMap.end() ; it++ ){
		write << "  " << it->second << "hi dw 0" << endl;
		write << "  " << it->second << "lo dw 0" << endl;
	}
	write << "  _number db 8 dup 0" << endl;
	write << "  _carry dw 0" << endl;
	write << "  _dummyhi dw 0" << endl;
	write << "  _dummylo dw 0" << endl;
	write << "  _varlo dw 0" << endl;
	write << "  _varhi dw 0" << endl;
	write << "  _powlo dw 0" << endl;
	write << "  _powhi dw 0" << endl;
	write << "  _blo dw 0" << endl;
	write << "  _bhi dw 0" << endl;
	write << "  _reslo dw 0" << endl;
	write << "  _reshi dw 0" << endl;
	write << "  _xlo dw 0" << endl;
	write << "  _xhi dw 0" << endl;
	write << "  _ylo dw 0" << endl;
	write << "  _yhi dw 0" << endl;


	write << "Start:" << endl;

	while( getline(myFile,s) ){
		if( s.size() && (s[s.size()-1] == '\r' || s[s.size()-1] == '\n') ) s=s.substr( 0 , s.size()-1 );
		if( countEquals( s ) == 1 ){
			string left=withoutSpace( s.substr( 0 , findEqual( s ) ) ),right=withoutSpace( s.substr( findEqual( s )+1 , s.size() ));
			parseThis( right , write );
			write << "  POP AX" << endl;
			write << "  MOV " << myMap[left] << "lo,AX" << endl;
			write << "  POP AX" << endl;
			write << "  MOV " << myMap[left] << "hi,AX" << endl;
		}else{
			s=withoutSpace( s );
			parseThis( s , write );
			Printer( write );
		}
	}

	write << "Exit:" << endl;
	write << "  MOV AH,4Ch" << endl;
	write << "  MOV AL,00" << endl;
	write << "  INT 21h" << endl;


	return 0;
}