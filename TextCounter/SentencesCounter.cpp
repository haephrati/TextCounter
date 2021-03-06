#include "stdafx.h"
#include "SentencesCounter.h"
#include "TextCounterDlg.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ctype.h"
#include <limits>
#include <cmath>
#include <set>
#include <queue> 
#include <unordered_set>


Language Albanian =
{
	L"Albanian",
	{
		_T("A"),_T("a"),1,0,
		_T("B"),_T("b"),1,1,
		_T("C"),_T("c"),1,2,
		_T("Ç"),_T("ç"),1,3,
		_T("DH"),_T("dh"),2,5,
		_T("E"),_T("e"),1,6,
		_T("Ë"),_T("ë"),1,7,
		_T("F"),_T("f"),1,8,
		_T("GJ"),_T("gj"),2,10,
		_T("H"),_T("h"),1,11,
		_T("I"),_T("i"),1,12,
		_T("J"),_T("j"),1,13,
		_T("K"),_T("k"),1,14,
		_T("LL"),_T("ll"),2,16,
		_T("M"),_T("m"),1,17,
		_T("NJ"),_T("nj"),2,19,
		_T("O"),_T("o"),1,20,
		_T("P"),_T("p"),1,21,
		_T("Q"),_T("q"),1,22,
		_T("RR"),_T("rr"),2,24,
		_T("SH"),_T("sh"),2,26,
		_T("TH"),_T("th"),2,28,
		_T("U"),_T("u"),1,29,
		_T("V"),_T("v"),1,30,
		_T("XH"),_T("xh"),2,32,
		_T("Y"),_T("y"),1,33,
		_T("ZH"),_T("zh"),2,35,
		_T(""),_T(""),-1,-1
	}
};

float valueFactor[40] = { 1.26f/*a*/,8.3f/*b*/,22.04f/*c*/,52.1f/*ç*/,3.47f/*d*/,8.52f/*dh*/,
								1.01f/*e*/,1.0f/*ë*/,11.02f/*f*/,7.85f/*g*/,20.47f/*gj*/,8.42f/*h*/,
								1.22f/*i*/,4.69f/*j*/,2.83f/*k*/,6.09f/*l*/,22.04f/*ll*/,2.78f/*m*/,
								1.66f/*n*/,14.69f/*nj*/,2.41f/*o*/,3.39f/*p*/,14.33f/*q*/,1.43f/*r*/,
								22.92f/*rr*/,3.33f/*s*/,4.73f/*sh*/,1.17f/*t*/,22.04f/*th*/,2.55f/*u*/,
								7.25f/*v*/,114.64f/*x*/,143.3f/*xh*/,16.37f/*y*/,11.23f/*z*/,52.10f/*zh*/,0.0,0.0,0.0,0.0 };

void SentencesCounter::Encode(Sentence sentence)
{
	sentence.text;
}
void SentencesCounter::Decode(Sentence sentence)
{

}
void SentencesCounter::ResetSentence(Sentence &s)
{
	s.text.clear();
	s.encoded_text.clear();
	for (int i = 0; i < 40; i++)
		s.counter[i] = 0;
}
void SentencesCounter::SetTargets(CounterTotals t)
{
	for (int i = 0; i < 40; i++)
		m_target[i] = t.counter[i];
	ResetResults();
}

BOOL SentencesCounter::ExportSentencesToCsv(vector<Sentence> Data, CString FilePath)
{
	size_t columnLength = 1;
	if (columnLength == 0) return FALSE;

	ofstream fs(FilePath, ios::out | ios::binary);// add BOM to beginning of file otherwise excel doesn't recognize the albanian characters
	if (fs.is_open())
	{
		unsigned char bomMarker[3] = { 0xEF, 0xBB, 0xBF };
		fs << bomMarker;
	}
	fs.close();


	wofstream mFile(FilePath, ios::out | ios::app);//append lines to file in UTF8
	if (mFile.is_open())
	{
		mFile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		for(auto &sentence : Data)
			mFile << sentence.text.c_str() << endl;
	}
	mFile.close();


	return TRUE;
}

void SentencesCounter::UpdateTotals(Sentence data)
{
	for (size_t i = 0; i < 40; i++)
		m_totals.counter[i] += data.counter[i];
	vector<int> diff = GetDifferenceFromGoal();
}

void SentencesCounter::ResetResults()
{
	for (size_t i = 0; i < 40; i++) m_totals.counter[i] = 0;
	MainDlg* pMainDlg = (MainDlg*)AfxGetApp()->GetMainWnd();
	pMainDlg->m_FoundText.SetWindowText(L"");
	pMainDlg->ProcessingCompleted = false;
}

bool SentencesCounter::CreateSentences(vector<Sentence> &data, wstring text)
{
	Sentence curSentence;
	ResetSentence(curSentence);
	size_t textLength = text.length();
#ifdef _DEBUG
	vector<CString> logLines;
#endif

	CString foundText{ L"" };


	for (size_t i = 0; i < textLength; i++)
	{
		static wchar_t lastChar{ L'\0' };
		wchar_t curChar{ text[i] }, nextChar{ L'\0' };

		if (i < textLength - 1) nextChar = text[i + 1];
#ifdef _DEBUG
		logLines.push_back(GetLogLineFormat(L"i=%d curChar = %c", i, curChar));
#endif
		if ((curChar == L'.' && lastChar != L'.') || (curChar == L'?' && lastChar != L'?'))
		{
			curSentence.text.push_back(curChar);
#ifdef _DEBUG
			logLines.push_back(GetLogLineFormat(L"New Sentence: '%s'", curSentence.text.c_str()));
#endif
			UpdateTotals(curSentence);

			//show progress
			MainDlg* pMainDlg = (MainDlg*)AfxGetApp()->GetMainWnd();
			pMainDlg->ShowStatus(L"File %d out of %d files. Data size: %d(Bytes) %0.2f%% (Overall: %0.2f%%)", 
				CurFile, 
				TotalFiles,
				data.size(), 
				(float)i / (float)textLength*100.00,
				(float)CurFile / (float)TotalFiles*100.00
			);

			foundText.Append(curSentence.text.c_str());
			foundText.Append(L"\r\n");

			data.insert(data.end(), curSentence);
#ifdef _DEBUG
			logLines.push_back(GetLogLineFormat(L"Global Data Size = %d", data.size()));
#endif
			ResetSentence(curSentence);
		}
		else if ((curChar == L'\n' || curChar == L'\f' || curChar == L'\r')
			|| curChar == L' ' && curSentence.text == L""
			|| lastChar == L'.' && curChar == L'.')
		{
			// Skipping
		}
		else
		{
			if (curChar == L'\0') continue;
			curSentence.text.push_back(curChar); // First we add the char to the sentence

#ifdef _DEBUG
			// Then we convert it to uppercase
			logLines.push_back(GetLogLineFormat(L"Before transform: char '%c'", curChar));
			//			transform(curChar.begin(), curChar.end(), curChar.begin(), ::toupper);
			logLines.push_back(GetLogLineFormat(L"Checking char '%c'", curChar));
#endif
			for (int j = 0; Albanian.characters[j].index != -1; j++)
			{
				if ((std::size(Albanian.characters[j].m_CharL) > 0 &&
					curChar == Albanian.characters[j].m_CharL[0]) ||
					(std::size(Albanian.characters[j].m_CharU) > 0 && 
					curChar == Albanian.characters[j].m_CharU[0]))
				{
					int Index = Albanian.characters[j].index;
#ifdef _DEBUG
					logLines.push_back(GetLogLineFormat(L"Char %s is %d chars long",
						Albanian.characters[j].m_CharU,
						Albanian.characters[j].m_Count));
#endif
					if (Albanian.characters[j].m_Count == 2)
					{
						wchar_t expected_charU = Albanian.characters[j].m_CharU[1];
						wchar_t expected_charL = Albanian.characters[j].m_CharL[1];
						if (nextChar == expected_charL ||
							nextChar == expected_charU)				// A double character
						{
#ifdef _DEBUG
							logLines.push_back(GetLogLineFormat(L"2nd char '%c'. Count = %d",
								nextChar,
								curSentence.counter[Index] + 1));
#endif
							curSentence.text.push_back(nextChar);
							// Added encoded char
							curSentence.encoded_text.insert(curSentence.encoded_text.end(), j + 1);
							// Update counter
							curSentence.counter[Index]++; // special 2 characters
							//curSentence.sum++;
							nextChar = L'\0';
							i++;
							goto found;
						}
						else
						{
#ifdef _DEBUG
							// A Single character
							logLines.push_back(GetLogLineFormat(L"Char after %c isn't %c but %c",
								curChar,
								expected_charU,
								nextChar));
							logLines.push_back(GetLogLineFormat(L"Normal char (2) %c. Counter = %d",
								curChar,
								curSentence.counter[Index - 1] + 1));
#endif
							// Added encoded char
							curSentence.encoded_text.insert(curSentence.encoded_text.end(), j);

							curSentence.counter[Index - 1]++; // Normal
							//curSentence.sum++;
							nextChar = L'\0';
							goto found;
						}
					}
					else
					{
						// A Single character
					//}
					//{
#ifdef _DEBUG
						logLines.push_back(GetLogLineFormat(L"Normal char (1) %c. Counter=%d", curChar,
							curSentence.counter[Index] + 1));
#endif
						// Added encoded char
						curSentence.encoded_text.insert(curSentence.encoded_text.end(), j);

						curSentence.counter[Index]++; // Normal
						//curSentence.sum++;
						nextChar = L'\0';
						goto found;
					}
				}
			}

#ifdef _DEBUG
			logLines.push_back(GetLogLine(L"Not Found"));
#endif
			continue;
		found:;
#ifdef _DEBUG
			logLines.push_back(GetLogLine(L"Found"));
#endif
		}
		lastChar = curChar;
	}

	if (!curSentence.text.empty())
	{
#ifdef _DEBUG
		logLines.push_back(GetLogLineFormat(L"New Sentence: '%s'", curSentence.text.c_str()));
#endif
		UpdateTotals(curSentence);

		foundText.Append(curSentence.text.c_str());
		foundText.Append(L"\r\n");

		data.insert(data.end(), curSentence);
#ifdef _DEBUG
		logLines.push_back(GetLogLineFormat(L"Global Data Size = %d", data.size()));
#endif
		ResetSentence(curSentence);
	}

	MainDlg* pMainDlg = (MainDlg*)AfxGetApp()->GetMainWnd();
	CString temp;
	pMainDlg->m_FoundText.GetWindowText(temp);
	temp.Append(foundText);
	pMainDlg->m_FoundText.SetWindowTextW(temp);

#ifdef _DEBUG
	WriteLinesToLogFile(logLines);
#endif
	return false;
}

vector<int> SentencesCounter::GetDifferenceFromGoal()
{
	vector<int> result;

	for (size_t i = 0; i < 40; i++)
	{
		result.push_back(abs(m_target[i] - m_totals.counter[i]));
	}
	return result;
}

void SentencesCounter::AddNode(Node* first, Node* second)
{
	for (int i = 0; i < sizeof first->c / 4; i++)
	{
		first->c[i] += second->c[i];
	}
}

int SentencesCounter::GetDelta(Node* total, Node* cur)
{
	int tot = 0;
	for (int i = 0; i < sizeof total->c / 4; i++)
	{
		tot += abs(total->c[i] - cur->c[i]);
	}

	return tot;
}

void SentencesCounter::Extract(vector<int>encoded_str, Node* node)
{
	for (size_t i = 0; i < encoded_str.size(); i++)
	{
		wchar_t ch = encoded_str[i];
		node->c[ch]++;
	}
}

void SentencesCounter::MakeTarget(Node* nTarget, int *target)
{
	for (int i = 0; i < 40; i++)
	{
		nTarget->c[i] = target[i];
	}
}



bool orderByScore(const Sentence &a, const Sentence &b)
{
	return b.score < a.score;
}

bool orderByScoreDistance(const Sentence &a, const Sentence &b)
{
	return b.score < a.score;
}

int SentencesCounter::GetScore(Sentence sentence, int* target)
{
	int sum1 = 0;
	int sum2 = 0;

	for (size_t i = 0; i < 40; i++)
	{
		int sentenceFreq = sentence.counter[i];
		int targetFreq = target[i];

		sum1 += min(sentenceFreq, targetFreq);
		sum2 += max(0, sentenceFreq - targetFreq);
	}

	return sum1 - sum2;
}

/*
euclidean distance in n-Dimensional space
*/
int GetDistance(Sentence sentence, int* target)
{
	int p1 = 0;
	int p2 = 0;
	double sum = 0;

	for (size_t i = 0; i < 40; i++)
	{
		int sentenceFreq = sentence.counter[i];
		int targetFreq = target[i];

		sum += pow((sentenceFreq - targetFreq), 2);
	}

	return static_cast<int>(sqrt(sum));
}

int GetNewScore(Sentence sentence)
{
	double value = 1;
	
	for (int i = 0; i < 40; i++) 
	{
		value += sentence.counter[i] * valueFactor[i];
	}
	value /= (sentence.text.size()+15); //15 is the normal sentence lenght. To avoid selection of fake sentences
	return static_cast<int>( value );
}

void SentencesCounter::CalculateValueFactor(size_t sum)
{
	double value = 1;
	for (size_t i = 0; i < 40; i++) 
	{
		valueFactor[i] = static_cast<double>(sum) / static_cast<double>(m_totals.counter[i]+1) ; // +1 to avoid division to zero
	}
}

void updateSentence(Sentence * allSelectionSentence, Sentence selected)
{
	for (size_t i = 0; i < 40; i++)
	{
		allSelectionSentence->counter[i] += selected.counter[i];
	}
}

void SentencesCounter::SolveExtended(vector<Sentence> &sentences)
{	
	
}

void SentencesCounter::SolveIR(vector<Sentence> &sentences, vector<Sentence> &SelectedData)
{	
	size_t sum = 0;
	vector<Sentence> candidates;
	//========= remove duplicate sentences ===========//
	//set<Sentence> s(candidates.begin(), candidates.end());
	//candidates.assign(s.begin(), s.end());
	//rt(candidates.begin(), candidates.end());
	//candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
	//unordered_set<int> s;
	unordered_set<wstring> c1;
	for (size_t i = 0; i < sentences.size(); i++) //remove duplicates
	{
		if (sentences[i].text.size() < 10) continue; // to avoid fake sentences

		if (c1.find(sentences[i].text) == c1.end()) { //O(1)
			c1.insert(sentences[i].text);
			candidates.push_back(sentences[i]);
			sum += sentences[i].text.length();
		}
	}
	//-----------------------------------------------//

	for (size_t i = 0; i < candidates.size(); i++)
	{
		sum += candidates[i].text.length();
	}
	
	CalculateValueFactor(sum);

	for (size_t i = 0; i < candidates.size(); i++)
	{
		candidates[i].score = GetNewScore(candidates[i]);
	}

	sort(candidates.begin(), candidates.end(), orderByScoreDistance);

	vector<Sentence> selection;
	Sentence sAllSelected;
	ResetSentence(sAllSelected);
	int lastDistance = INT_MAX/2 -1, newDistance = INT_MIN;
	for (auto &s : candidates) // access by reference to avoid copying
	{
		updateSentence(&sAllSelected, s);
		newDistance = GetDistance(sAllSelected, m_target);
		if (lastDistance < newDistance) 
		{
			for (size_t i = 0; i < 40; i++)
			{
				sAllSelected.counter[i] -= s.counter[i];
			}
			break;
		}
		else {
			selection.push_back(s);
			lastDistance = newDistance;
		}
	}


	ResetResults();
	CString foundText{ _T("") };

	for (auto& sentence : selection)
	{
		foundText.AppendFormat(_T("%s\r\n"), sentence.text.c_str());
		UpdateTotals(sentence);
	}

	for (size_t i = 0; i < 40; i++)
	{
		m_totals.counter[i] = sAllSelected.counter[i];
		//foundText.AppendFormat(_T("<%s:%d>,"), getAlbaniLetter(i), sAllSelected.counter[i]);
	}
	foundText.Append(L"\r\n");


	MainDlg* pMainDlg = (MainDlg*)AfxGetApp()->GetMainWnd();
	CString temp;
	pMainDlg->m_FoundText.GetWindowText(temp);
	temp.Append(foundText);
	pMainDlg->m_FoundText.SetWindowTextW(temp);

	SelectedData.clear();
	SelectedData.insert(SelectedData.begin(),
		selection.begin(), selection.end());
	MessageBox(GetForegroundWindow(),
		L"Selected " + (CString)(std::to_wstring(SelectedData.size()).c_str()) +
		(CString)L" sentences", L"Result", MB_OK);

}

