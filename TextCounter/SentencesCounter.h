#pragma once
#define FIRST_CHAR			L'a'
#define INF					0x7ffffff

typedef struct
{
	wchar_t m_CharU[3]{ L"" };
	wchar_t m_CharL[3]{ L"" };
	int m_Count{ 1 };
	int index{ -1 };
} Char;
typedef struct
{
	wstring LangName;
	Char characters[80];
} Language;

struct Node
{
	//vector<int> c;
	//std::array<int, 40> c;
	//vector<int> c = vector<int>(40, 0);
	int c[40]
	{
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	};     // frequency table
	int delta;      // delta between total
	vector<int> s;  // indices of selected sentences

	Node()
	{
		//memset(c, 0, sizeof(c));
		delta = INF;
	}
};


typedef struct
{
	int counter[40]
	{
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	};
} CounterTotals;

typedef struct
{
	wstring text{ L"" };			
	vector<int>encoded_text;		// Here we will hold an integer for each character (including double characters)
	int counter[40]
	{
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	};
	//int sum = 0;
	//int diffToTarget = 0;
	int score = INT_MIN;
	//int index = -1;
	//int position_i = 0;
	//int positive = 0;
	//int negative = 0;
	//int diffToTarget;
} Sentence;

class SentencesCounter
{
	private:
	int m_target[40]
	{
		-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1
	};
	CounterTotals m_totals
	{
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	};

	double valueFactor[40] = { 1.26/*a*/,8.3/*b*/,22.04/*c*/,52.1/*ç*/,3.47/*d*/,8.52/*dh*/,
							1.01/*e*/,1.0/*ë*/,11.02/*f*/,7.85/*g*/,20.47/*gj*/,8.42/*h*/,
							1.22/*i*/,4.69/*j*/,2.83/*k*/,6.09/*l*/,22.04/*ll*/,2.78/*m*/,
							1.66/*n*/,14.69/*nj*/,2.41/*o*/,3.39/*p*/,14.33/*q*/,1.43/*r*/,
							22.92/*rr*/,3.33/*s*/,4.73/*sh*/,1.17/*t*/,22.04/*th*/,2.55/*u*/,
							7.25/*v*/,114.64/*x*/,143.3/*xh*/,16.37/*y*/,11.23/*z*/,52.10/*zh*/,0.0,0.0,0.0,0.0 };


	public:
	CounterTotals GetTotals()
	{
		return m_totals;
	}


	int globalIndex = 0;

	void Decode(Sentence sentence);
	void Encode(Sentence sentence);
	void SetTargets(CounterTotals t);
	void ResetSentence(Sentence &s);
	void Extract(vector<int>encoded_str, Node* node);
	int GetDelta(Node* total, Node* cur);
	void AddNode(Node* first, Node* second);
	void SolveExtended(vector<Sentence> &Data);
	BOOL ExportSentencesToCsv(vector<Sentence> Data, CString FilePath);
	void ResetResults();
	void MakeTarget(Node* nTarget, int *target);
	int GetScore(Sentence freqTable, int *target);
	void SolveIR(vector<Sentence>& sentences, vector<Sentence> &SelectedData);
	void CalculateValueFactor(size_t sum);
	bool CreateSentences(vector<Sentence> &data, wstring text);
	vector<int> GetDifferenceFromGoal();

	void UpdateTotals(Sentence data);
};

