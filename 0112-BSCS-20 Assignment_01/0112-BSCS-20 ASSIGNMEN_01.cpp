#include<iostream>
#include<fstream>
using namespace std;

class TOKEN
{
	private:
	
	int Count=0;
	string TName;
	string AtValue;
	
	public:
		
	TOKEN()
	{
		this->TName = "";
		this->AtValue = "";
	}
	
	string getTName()
	{
		return TName;
	}
	
	string getAtValue()
	{
		return AtValue;
	}
	
	void setTName(string TName)
	{
		this->TName = TName;
	}
	
	void setAtValue(string AtValue)
	{
		this->AtValue = AtValue;
	}
	
	void Display()
	{
		if(Count == 0)
		{
			cout<<"\t\t\n\n\t\t\t\t\t\t[TOKENS FOR INPUT FILE]\n\n";
			cout<<"\t\t-----------------------------------------------------------------------------------------\n";
			cout<<"\t\t|\tLEXEME\t\t|\t\t TOKEN\t\t|\t\t TOKEN No\t|\n";
			cout<<"\t\t|---------------------------------------------------------------------------------------|\n";
		}
		cout<<"\t\t|\t"<<AtValue;
		cout<<"\t\t|\t\t"<<TName;
		cout<<"\t\t|\t\t\t"<<Count+1<<"\t|"<<endl;
		
		fstream OutFile;
		OutFile.open("Output.txt" , ios::app);
		if(Count == 0)
		{
			OutFile<<"\t\t\n\n\t\t\t\t\t\t[TOKENS FOR INPUT FILE]\n\n";
			OutFile<<"\t\t-----------------------------------------------------------------------------------------\n";
			OutFile<<"\t\t|\tLEXEME\t\t|\t\t TOKEN\t\t|\t\t TOKEN No\t|\n";
			OutFile<<"\t\t|---------------------------------------------------------------------------------------|\n";
		}
		
		OutFile<<"\t\t|\t"<<AtValue;
		OutFile<<"\t\t|\t\t"<<TName;
		OutFile<<"\t\t|\t\t\t"<<Count+1<<"\t|"<<endl;
		Count++;
		OutFile<<"\t\t-----------------------------------------------------------------------------------------\n";
		OutFile.close();
		cout<<"\t\t-----------------------------------------------------------------------------------------\n";
		
	}
};

//----------------------------------------------------------------------------------------------------------------------

class BUFFER
{
	private:
	
	string KeyWords[21] = {"int" , "float" , "double" , "short" , "char" ,
	"bool" , "if" , "else" , "while" , "for" , "break" , "continue" , "class" ,
	"long" , "string" , "const" , "static" , "goto" , "do" , "return" , "default"};
	string Buff;
	int Forward;
	int Begin;
	int TGs[9] = {0 , 9 , 13 , 21 , 23 , 27 , 29 , 32 , 34};
	int TGc;
	
	public:
		
	BUFFER()
	{
		Forward=0;
		Begin=0;
		TGc=0;
		Buff = readFile();
	}	
	
	string readFile()
	{
		string Temp = "" , Temp1;
		fstream InFile;
		InFile.open("Input.txt" , ios::in);
		while(!InFile.eof())
		{
			getline(InFile , Temp1);
			Temp += Temp1;
		}
		InFile.close();
		return Temp;
	}
		
	void setTGc(int TGc)
	{
		this->TGc = TGc;
	}
		
	char getChar()
	{
		Forward++;
		return Buff[Forward-1];
	}
	
	int fail()
	{
		Forward = Begin;
		TGc++;
		return TGs[TGc];
	}
	
	void retract()
	{
		Forward--;	
	}
	
	void retract2()
	{
		Forward-=2;	
	}
	
	void tokSuccess()
	{
		Begin = Forward;	
	}
	
	bool chkKeyword(string Str)
	{
		for(int i=0 ; i<21 ; i++)
		{
			if(KeyWords[i].compare(Str) == 0)
			{
				return true;
			}
		}
		return false;
	}	
	
	bool stop()
	{	
		if(Forward == Buff.size())
		{	
			return false;
		}
		else
		{
			return true;
		}
	}
};

//-----------------------------------------------------------------------------------------------------------------

int main()
{
	BUFFER B = BUFFER();
	int State = 0 , Temp;
	TOKEN RetToken = TOKEN();
	char C;
	bool Test = true;
	string Str;
	
	while(Test)
	{	
		switch(State)
		{
			//RELATIONAL OPERATORS MACHINE
			case 0:
			B.setTGc(0);
			C = B.getChar();
			if(C == '<')State=1;
			else if(C == '=')State=5;
			else if(C == '>')State=6;
			else State = B.fail();
			break;		
						
			case 1:
			C = B.getChar();
			if(C == '=')State=2;
			else if(C == '>')State=3;
			else State=4;
			break;
			
			case 2:
			RetToken.setTName("RelOp");
			RetToken.setAtValue("LE");
			RetToken.Display();
			B.tokSuccess();
			cout<<B.stop();
			if(B.stop())
			{
				State=0;
			}
			else
			{
				Test = false;
			}
			break; 
				
			case 3:
			RetToken.setTName("RelOp");
			RetToken.setAtValue("NE");
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
				Test = false;
			}
			break;
			
			case 4:
			B.retract();
			RetToken.setTName("RelOp");
			RetToken.setAtValue("LT");
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
				Test = false;
			}
			break;
			
			case 5:
			RetToken.setTName("RelOp");
			RetToken.setAtValue("EQ");
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
				Test = false;
			}
			break;
			
			case 6:
			C = B.getChar();
			if(C == '=')State=7;
			else State=8;
			break;
			
			case 7:	
			RetToken.setTName("RelOp");
			RetToken.setAtValue("GE");
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
				Test = false;
			}
			break;
			
			case 8:
			B.retract();
			RetToken.setTName("RelOp");
			RetToken.setAtValue("GT");
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
				Test = false;
			}
			break;
			//IDENTIFIER AND KEYWORDS MACHINE
			case 9:
			Str = "";
			C = B.getChar();
			Temp = int(C);
			if((Temp>=65 && Temp<=90) ||  (Temp>=97 && Temp<=122))
			{
				Str = C;
				State=10;
			}
			else State = B.fail();
			break;
			
			case 10:
			C = B.getChar();
			Temp = int(C);
			if((Temp>=65 && Temp<=90) ||  (Temp>=97 && Temp<=122) || (Temp>=48 && Temp<=57))
			{
				Str += C;
				State=10;
			}
			else State = 11;
			break;
			
			case 11:	
			if(B.chkKeyword(Str) == true)
			{
				State = 12;
			}
			else
			{
				B.retract();
				RetToken.setTName("ID");
				RetToken.setAtValue(Str);
				RetToken.Display();
				B.tokSuccess();
				if(B.stop())
				{
					State=0;
				}
				else
				{
					Test = false;
				}
			}
			break;
			
			case 12:
			B.retract();
			RetToken.setTName("Keyword");
			RetToken.setAtValue(Str);
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
					Test = false;
			}
			break;
			//DIGITS MACHINE
			case 13:
			Str = "";
			C = B.getChar();
			Str = C;
			Temp = int(C);
			if(Temp>=48 && Temp<=57)State = 14;
			else if(C == '.')State = 15;
			else State  = B.fail();
			break;
			
			case 14:
			C = B.getChar();
			Temp = int(C);
			if(Temp>=48 && Temp<=57){Str += C;State = 14;}
			else if(C == '.'){Str += C;State = 15;}
			else if(C == 'E'){Str += C;State = 17;}
			else State  = 20;
			break;
			
			case 15:
			C = B.getChar();
			Temp = int(C);
			if(Temp>=48 && Temp<=57){Str += C;State = 16;}
			break;
			
			case 16:
			C = B.getChar();
			Temp = int(C);
			if(Temp>=48 && Temp<=57){Str += C;State = 16;}
			else if(C == 'E'){Str += C;State = 17;}
			else State = 20;
			break;
			
			case 17:
			C = B.getChar();
			Temp = int(C);
			if(C=='-' || C=='+'){Str += C;State = 18;}
			else if(Temp>=48 && Temp<=57){Str += C;State = 19;}
			break;
			
			case 18:
			C = B.getChar();
			Temp = int(C);
			if(Temp>=48 && Temp<=57){Str += C;State = 19;}
			break;
			
			case 19:
			C = B.getChar();
			Temp = int(C);
			if(Temp>=48 && Temp<=57){Str += C;State = 19;}
			else State = 20;
			break;
			
			case 20:
			B.retract();
			RetToken.setTName("Number");
			RetToken.setAtValue(Str);
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
					Test = false;
			}
			break;
			//ARITHMATIC OPERATORS MACHINE
			case 21:
			Str = "";
			C = B.getChar();
			if(C == '+' || C == '-' || C == '*' || C == '/' || C == '%'){Str = C;State = 22;}
			else State = B.fail();
			break;
				
			case 22:
			RetToken.setTName("ArithOp");
			RetToken.setAtValue(Str);
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
					Test = false;
			}
			break;	
			
			//LOGICAL OPERATOR MACHINE
			
			case 23:
			Str = "";
			C = B.getChar();
			if( C == '|'){Str = C;State = 24;}
			else if(C == '&'){Str = C;State = 25;}
			else if(C == '!'){Str = C;State = 26;}
			else State = B.fail();
			break;
			
			case 24:
			C = B.getChar();
			if(C == '|' && !(Str.compare("|"))){Str += C;State = 26;}
			else {B.retract2();State = 34;}
			break;
			
			case 25:
			C = B.getChar();
			if(C == '&' && !(Str.compare("&"))){Str += C;State = 26;}
			else {B.retract2();State = 34;}
			break;
			
			
			case 26:
			RetToken.setTName("LogicOp");
			RetToken.setAtValue(Str);
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
					Test = false;
			}
			
		
			//BRACKETS IDENTIFIER MACHINE
		
			case 27:
			Str = "";
			C = B.getChar();
			if(C == '(' || C == ')' || C == '{' || C == '}' || C == '[' || C == ']') {Str = C;State = 28;}
			else State = B.fail();
			break;
				
			case 28:
			RetToken.setTName("BracKet");
			RetToken.setAtValue(Str);
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
					Test = false;
			}
			break;	
	
			// DILIMTERS MASHINE
			
			case 29:
			Str = "";
			C = B.getChar();
			Temp = int(C);
			if(Temp == 9){Str += "VT";State = 30;}
			else if(Temp == 10){Str += "LF";State = 30;}
			else if(Temp == 11){Str += "HT";State = 30;}
			else if(Temp == 32){Str += "SPC";State = 30;}
			else State = B.fail();
			break;
			
			case 30:
			C = B.getChar();
			Temp = int(C);
			if(Temp == 9){Str += "VT";State = 30;}
			else if(Temp == 10){Str += "LF";State = 30;}
			else if(Temp == 11){Str += "HT";State = 30;}
			else if(Temp == 32){Str += "SPC";State = 30;}
			else State = 31;
			break;
			
			case 31:
			B.retract();
			RetToken.setTName("Delim");
			RetToken.setAtValue(Str);
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
					Test = false;
			}
			break;	
			//PUNTUATORS MACHINE
			case 32:
			Str = "";
			C = B.getChar();
			if(C == ';' || C == ',' || C == ':'){Str = C;State = 33;}
			else State = B.fail();	
			break;
			
			case 33:
			RetToken.setTName("Puntu");
			RetToken.setAtValue(Str);
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
					Test = false;
			}
			break;	
			
			case 34:
			Str = "";
			C = B.getChar();
			Str = C;
			RetToken.setTName("NotInLang");
			RetToken.setAtValue(Str);
			RetToken.Display();
			B.tokSuccess();
			if(B.stop())
			{
				State=0;
			}
			else
			{
					Test = false;
			}
			break;
		}	
	}
}

