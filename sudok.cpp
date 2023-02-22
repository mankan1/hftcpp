// SodokuSolver.cpp : Solves Sudoku and shows a snapshot of the board at various point in the recursion when it tries a number between 1 thru 9 .
//

#include "SodokuSolver.h"
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define BUFSIZE 4096
#define LONG_DIR_NAME TEXT("c:\\longdirectoryname")


bool SudokuSolver::FindEmptySpot(int& r, int& c) {
	for (int i = 0; i < boardDimensions; ++i) {
		for (int j = 0; j < boardDimensions; ++j) {
			if (board[i][j] == 0) {
				r = i;
				c = j;
				return true;
			}
		}
	}
	return false;
}

bool SudokuSolver::AbidesRuleConstraints(int r, int c, int tryVals) {

	// if row has the value that we are trying
	for (int col = 0; col < boardDimensions; ++col) {
		if (board[r][col] == tryVals) {
			return false;
		}
	}

	// if col has the value that we are trying
	for (int row = 0; row < boardDimensions; ++row) {
		if (board[row][c] == tryVals) {
			return false;
		}
	}

	// check the correct grid
	int currGridR = r - r % 3;
	int currGridC = c - c % 3;

	// search is this 3 x 3 grid
	for (int row = currGridR; row < currGridR + 3; ++row) {
		for (int col = currGridC; col < currGridC + 3; ++col) {
			if (board[row][col] == tryVals) {
				return false;
			}
		}
	}

	return true;
}

void EQueens::PrintBoard() {
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			cout << board[row][col] << " ";
		}
		cout << endl;
	}
}

void SudokuSolver::PrintBoard(vector<vector<int>> intermediate_board, STATE state) {
	for (int row = 0; row < boardDimensions; ++row) {
		for (int col = 0; col < boardDimensions; ++col) {
			state == SOLVED ? (cout << board[row][col] << " ") : (cout << intermediate_board[row][col] << " ");
		}
		cout << endl;
	}
}

bool EQueens::NoConflict(int r, int c) {

	bool col_conflict = false;
	for (int i = 0; i < r; ++i) {
		if (board[i][c] == 1) {
			col_conflict = true;
		}
	}
	// 3,1
	// go all the cols left, right
	// go all the rows up and down
	// 0, 1
	// 1, 2
	// 2, 3

	// 2,1
	// 1,2
	// 0,3

	// 3,2
	bool diag_conflict = false;
	for (int r1 = 0; r1 < r; ++r1) {
		for (int c1 = 0; c1 < 8; ++c1) {
			if (abs(r - r1) == abs(c - c1) && board[r1][c1] == 1) {
				diag_conflict = true;
			}
		}
	}

	return !col_conflict && !diag_conflict;
}

bool EQueens::Place(int row) {

	if (row == 8) {
		return true;
	}

	for (int col = 0; col < 8; ++col) {

		if (NoConflict(row, col)) {

			board[row][col] = 1;

			cout << row << " , " << col << endl;
			bool p = Place(row + 1);

			if (p) {
				return true;
			}

			board[row][col] = 0;
		}
	}

	return false;
}

bool EQueens::Solve() {
	return Place(0);
}

bool SudokuSolver::Solve(){
	int r = 0, c = 0;
	bool foundSlot = FindEmptySpot(r, c);

	cout << "Found Spot " << r << " " << c << endl;

	if (!foundSlot) {
		return true;
	}
	else {
		for (int tryVals = 1; tryVals <= boardDimensions; ++tryVals) {
			if (AbidesRuleConstraints(r, c, tryVals)) {

				board[r][c] = tryVals;

				cout << "AbidesRuleConstraints " << tryVals << " " << r << " " << c << endl;
				board_state.push_back(board);
				bool solveAgain = Solve();
				if (solveAgain) {
					return true;
				}
				board[r][c] = 0; // this recursive failed, reset and try another value
			}
		}
		// non of the tries worked, return false.
		return false;
	}
}

bool
Decode1(
	__in_z LPCSTR src,
	__out std::string& dst,
	__in bool substitute
)
{
	bool ok = false;

	if (src != nullptr)
	{
		try
		{
			size_t cch = strlen(src);

			if (cch > 0)
			{
				// The destination string will never be larger than the source string.
				std::unique_ptr<char> tmp = std::unique_ptr<char>(new char[cch + 1]);

				size_t srcIndex = 0;
				size_t dstIndex = 0;

				while (srcIndex < cch)
				{
					char c = src[srcIndex++];

					if (c == '+' && substitute)
					{
						if (srcIndex < cch && src[srcIndex] == '+')
						{
							tmp.get()[dstIndex++] = '+';
							srcIndex++;
							continue;
						}

						tmp.get()[dstIndex++] = ' ';
						continue;
					}

					if (c == '%')
					{
						if (srcIndex < cch && src[srcIndex] == '%')
						{
							tmp.get()[dstIndex++] = '%';
							srcIndex++;
							continue;
						}

						char hi;
						char lo;

						// If there isn't room for two hex digits after the '%' or 
						// either of the two is not a valid hex digit, then break
						// out.
						// Using isxdigit is perilous: debug builds trip asserts for non-hex chars > 127
						if (srcIndex + 2 > cch)
						{
							tmp.get()[dstIndex++] = c;
							continue;
						}

						hi = src[srcIndex + 0];
						lo = src[srcIndex + 1];

						// 0..9, A..F, a..f are valid
						// otherwise bail out  (fugly, but avoids isxdigit)
						if (!(((hi >= '0') && (hi <= '9')) ||
							((hi >= 'A') && (hi <= 'F')) ||
							((hi >= 'a') && (hi <= 'f')) ||
							((lo >= '0') && (lo <= '9')) ||
							((lo >= 'A') && (lo <= 'F')) ||
							((lo >= 'a') && (lo <= 'f'))))
						{
							tmp.get()[dstIndex++] = c;
							continue;
						}

						if (hi >= 'a' && hi <= 'f')
						{
							hi = (hi - 'a') + 10;
						}
						else if (hi >= 'A' && hi <= 'F')
						{
							hi = (hi - 'A') + 10;
						}
						else
						{
							hi -= '0';
						}

						if (lo >= 'a' && lo <= 'f')
						{
							lo = (lo - 'a') + 10;
						}
						else if (lo >= 'A' && lo <= 'F')
						{
							lo = (lo - 'A') + 10;
						}
						else
						{
							lo -= '0';
						}

						tmp.get()[dstIndex++] = (hi << 4) | lo;

						srcIndex += 2;
						continue;
					}

					tmp.get()[dstIndex++] = c;
				}

				if (srcIndex == cch)
				{
					dst = std::string(tmp.get(), dstIndex);
					ok = true;
				}
			}
		}
		catch (std::bad_alloc)
		{
		}
	}

	return ok;
}

bool MultiByteToWideChar(
	__in UINT codepage,
	__in_ecount(cch) LPCSTR src,
	__in int cch,
	__in bool lowercase,
	__out std::wstring& dst
)
{
	bool ok = false;

	dst.clear();

	int cchDst;

	if ((cchDst = ::MultiByteToWideChar(codepage, 0, src, cch, nullptr, 0)) != 0)
	{
		try
		{
			std::unique_ptr<WCHAR> tmp =
				std::unique_ptr<WCHAR>(new WCHAR[cchDst]);

			if (::MultiByteToWideChar(codepage, 0, src, cch, tmp.get(), cchDst) > 0)
			{
				dst = tmp.get();

				if (lowercase)
				{
					std::transform(dst.begin(), dst.end(), dst.begin(), ::tolower);
				}

				ok = true;
			}
		}
		catch (std::bad_alloc)
		{
		}
	}

	return ok;
}

bool DG_WideCharToMultiByte(DWORD codepage, LPCWSTR str, int cb, bool lowerCase, std::string& result)
{
	char* mbstr = 0;

	result.erase();

	if (NULL == str)
	{
		return false;
	}

	try
	{
		if (codepage == 0)
		{
			codepage = CP_ACP;
		}

		if (cb == -1)
		{
			cb = ((int)wcslen(str) + 1) * sizeof(wchar_t);
		}

		int cch;
		if ((cch = WideCharToMultiByte(codepage, 0, str, cb /
			sizeof(wchar_t), 0, 0, 0, 0)) != 0)
		{
			mbstr = new char[cch + 1];

			if ((cch = WideCharToMultiByte(codepage, 0, str, cb /
				sizeof(wchar_t), mbstr, cch + 1, 0, 0)) != 0)
			{
				mbstr[cch] = '\0';

				if (lowerCase)
				{
					_strlwr_s(mbstr, cch + 1);
				}

				result = mbstr;
			}

			delete[] mbstr;
			mbstr = 0;
		}
	}
	catch (...)
	{
		// We will send back an empty string result in this case, as below.
	}

	return !result.empty();
}

std::string DG_WideCharToMultiByte(DWORD codepage, LPCWSTR str, int cb, bool lowerCase)
{
	std::string result;
	DG_WideCharToMultiByte(codepage, str, cb, lowerCase, result);
	return result;
}

std::string wstring_to_utf8_hex(const std::wstring& input)
{
	std::string output;
	int cbNeeded = WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, NULL, 0, NULL, NULL);
	if (cbNeeded > 0) {
		char* utf8 = new char[cbNeeded];
		if (WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, utf8, cbNeeded, NULL, NULL) != 0) {
			for (char* p = utf8; *p; *p++) {
				char onehex[5];
				_snprintf_s(onehex, sizeof(onehex), "%%%02.2X", (unsigned char)*p);
				output.append(onehex);
			}
		}
		delete[] utf8;
	}
	return output;
}

std::string unhexlify(const std::string& input)
{
	std::string output;
	for (const char* p = input.c_str(); *p; ) {
		if (p[0] == '%' && isxdigit(p[1]) && isxdigit(p[2])) {
			int ch = (isdigit(p[1]) ? p[1] - '0' : toupper(p[1]) - 'A' + 10) * 16 +
				(isdigit(p[2]) ? p[2] - '0' : toupper(p[2]) - 'A' + 10);
			output.push_back((char)ch);
			p += 3;
		}
		else if (p[0] == '%' && p[1] == '#' && isdigit(p[2])) {
			int ch = atoi(p + 2);
			output.push_back((char)ch);
			p += 2;
			while (*p && isdigit(*p)) p++;
			if (*p == ';') p++;
		}
		else {
			output.push_back(*p++);
		}
	}
	return output;
}

std::wstring utf8_hex_to_wstring(const std::string& input)
{
	std::wstring output;
	std::string utf8 = unhexlify(input);
	int cchNeeded = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
	if (cchNeeded > 0) {
		wchar_t* widebuf = new wchar_t[cchNeeded];
		if (MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, widebuf, cchNeeded) != 0) {
			output = widebuf;
		}
		delete[] widebuf;
	}
	return output;
}

bool Decode2(__in_z LPCWSTR src,
	__out std::wstring& dst,
	__in bool substitute
)
{
	//std::wstring wSS(src);
	std::string s = wstring_to_utf8_hex(src);
	//s.assign(wSS.begin(), wSS.end());

	std::string outStr;
	if (Decode1(s.c_str(), outStr, substitute))
	{
		wstring ws = utf8_hex_to_wstring(outStr.c_str());
		MultiByteToWideChar(CP_ACP, outStr.c_str(), -1, true, dst);
		return true;
	}
	return false;
}

bool Decodex(__in_z LPCWSTR src,
	__out std::wstring& dst,
	__in bool substitute
)
{
	std::wstring wSS(src);
	std::string s;
	s.assign(wSS.begin(), wSS.end());

	std::string outStr;
	if (Decode1(s.c_str(), outStr, substitute))
	{
		MultiByteToWideChar(CP_ACP, outStr.c_str(), -1, true, dst);
		return true;
	}
	return false;
}

bool Decode(__in_z LPCWSTR src,
	__out std::wstring& dst,
	__in bool substitute
)
{
	std::wstring wSS(src);
	std::string s;
	s.assign(wSS.begin(), wSS.end());

	std::string outStr;
	if (Decode1(s.c_str(), outStr, substitute))
	{
		MultiByteToWideChar(CP_ACP, outStr.c_str(), -1, true, dst);
		return true;
	}
	return false;
}

void GetDisplayName(LPWSTR* ppszName) {
	LPCWSTR dn = //L"more text";
	// L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt";
	// L"C:/Users/jkim/Desktop/ローカル/dummy.csv";
		L"file:///C:/Users/jkim/Desktop/ローカル/¡¢£¤¥¦§¨©ª«¬-®¯°±²³´µº»½Áôõ.doc";
	//char source[] = "once upon a midnight dreary...", dest[4];
	wchar_t* x = new wchar_t[sizeof(L"file:///C:/Users/jkim/Desktop/ローカル/¡¢£¤¥¦§¨©ª«¬-®¯°±²³´µº»½Áôõ.doc")];
	std::memcpy(ppszName, x, sizeof sizeof(L"file:///C:/Users/jkim/Desktop/ローカル/¡¢£¤¥¦§¨©ª«¬-®¯°±²³´µº»½Áôõ.doc"));
}

BOOL IsUnicode(const char* pBuffer, int cb/*,LPBOOL lpbBOM,LPBOOL lpbReverse*/)
{
	int i = 0xFFFF;

	BOOL bIsTextUnicode;

	BOOL bHasBOM;
	BOOL bHasRBOM;

	if (!pBuffer || cb < 2)
		return FALSE;
	//DWORD IsTextUnicode(CONST PVOID pvBuffer, int cb,PINT pResult);
	//文本文件存在的问题是，它们的内容没有严格和明确的规则，因此很难确定该文件是包含ANSI字符还是Unicode字符。
	// IsTextUnicode使用一系列统计方法和定性方法，以便猜测缓存的内容。由于这不是一种确切的科学方法，因此IsTextUnicode有可能返回不正确的结果。
	//第一个参数pvBuffer用于标识要测试的缓存的地址。该数据是个无效指针，因为你不知道你拥有的是ANSI字符数组还是Unicode字符数组。
	//第二个参数cb用于设定pvBuffer指向的字节数。同样，由于你不知道缓存中放的是什么，因此cb是个字节数，而不是字符数。
	//	请注意，不必设定缓存的整个长度。当然，IsTextUnicode能够测试的字节越多，得到的结果越准确。
	//第三个参数pResult是个整数的地址，必须在调用IsTextUnicode之前对它进行初始化。
	//	对该整数进行初始化后，就可以指明你要IsTextUnicode执行哪些测试。也可以为该参数传递NULL，
	//	在这种情况下，IsTextUnicode将执行它能够进行的所有测试（详细说明请参见PlatformSDK文档）。
	//如果IsTextUnicode认为缓存包含Unicode文本，便返回TRUE，否则返回FALSE。
	//	确实是这样，尽管Microsoft将该函数的原型规定为返回DWORD，但是它实际上返回一个布尔值。
	//	如果在pResult参数指向的整数中必须进行特定的测试，该函数就会在返回之前设定整数中的信息位，以反映每个测试的结果。

	bIsTextUnicode = IsTextUnicode(pBuffer, cb, &i);

	bHasBOM = (*((UNALIGNED PWCHAR)pBuffer) == 0xFEFF);
	bHasRBOM = (*((UNALIGNED PWCHAR)pBuffer) == 0xFFFE);

	if (i == 0xFFFF) // i doesn't seem to have been modified ...
		i = 0;

	if (bIsTextUnicode || bHasBOM || bHasRBOM ||
		((i & (IS_TEXT_UNICODE_UNICODE_MASK | IS_TEXT_UNICODE_REVERSE_MASK)) &&
			!((i & IS_TEXT_UNICODE_UNICODE_MASK) && (i & IS_TEXT_UNICODE_REVERSE_MASK)) &&
			!(i & IS_TEXT_UNICODE_ODD_LENGTH) &&
			!(i & IS_TEXT_UNICODE_ILLEGAL_CHARS && !(i & IS_TEXT_UNICODE_REVERSE_SIGNATURE)) &&
			!((i & IS_TEXT_UNICODE_REVERSE_MASK) == IS_TEXT_UNICODE_REVERSE_STATISTICS)))
	{

		//if (lpbBOM)
		//	*lpbBOM = (bHasBOM || bHasRBOM ||
		//	(i & (IS_TEXT_UNICODE_SIGNATURE | IS_TEXT_UNICODE_REVERSE_SIGNATURE)))
		//	? TRUE : FALSE;

		//if (lpbReverse)
		//	*lpbReverse = (bHasRBOM || (i & IS_TEXT_UNICODE_REVERSE_MASK)) ? TRUE : FALSE;

		return TRUE;
	}
	else
		return FALSE;
}

/*
class LruCacheC {
	Node** hash_map;
	int cache_capacity = 0;
	int page_counts = 0;
	LruCacheC() {}
};*/

Queue::Queue() : prev(nullptr), next(nullptr) {}

LruCacheC::LruCacheC(int page_counts_, int cache_capacity_) {

	page_counts = page_counts_;
	cache_capacity = cache_capacity_;
	hash_map = new Node* [page_counts_];
	for (int i = 0; i < page_counts; ++i) {
		hash_map[i] = nullptr;
	}

	queue = new Queue(cache_capacity_);
}

void LruCache::display() {

	cout << "Lru Cache" << endl;
	for (auto it = cache.begin(); it != cache.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
}

char LruCache::get(int page_number, char ch) {

	// get
	if (!cache.empty()) {
		// referred new one

		auto it = find(cache.begin(), cache.end(), ch);
		if (it == cache.end()) {
			return '\0';
		}
		else {
			cache.erase(it);
			cache.push_front(ch);
		}
	}
	else {
		return '\0';
	}

	return cache.front();
}

char LruCache::refer(int page_number, char ch) {

	// 1234
	// refer 3
	// 3124
	// move page to front

	// refer 5
	// remove 4
	// 123
	// 123
	// 5123
	// put
	if (!cache.empty()) {
		// referred new one

		auto it = find(cache.begin(), cache.end(), ch);
		if (it == cache.end()) {
			// full
			if (cache.size() == cache_capacity) {
				// get end
				//auto back = cache.back();
				// remove end
				//if (back != cache.end()) {
					//cache.pop_back();
				//}
				cache.pop_back();
			}
			else {
			}
			// refer 5
			// 12
			// 512
		}
		else {
			// not new
			// swap around
			// 123
			// 312
			cache.erase(it);
		}
	}

	cache.push_front(ch);
	
	return cache.front();
}
#include <windows.h>
#include <string>
#include <iostream>
#include <objidl.h>   /* For IPersistFile */
#include <shlobj.h>   /* For IShellLink */
#include "objbase.h"

using namespace std;


/*********************************************************************
* Function......: ResolveShortcut
* Parameters....: lpszShortcutPath - string that specifies a path
									 and file name of a shortcut
*          lpszFilePath - string that will contain a file name
* Returns.......: S_OK on success, error code on failure
* Description...: Resolves a Shell link object (shortcut)
*********************************************************************/
HRESULT ResolveShortcut(/*in*/ LPCTSTR lpszShortcutPath,
	/*out*/ LPTSTR lpszFilePath)
{
	HRESULT hRes = E_FAIL;
	IShellLink* psl = NULL;

	// buffer that receives the null-terminated string
	// for the drive and path
	TCHAR szPath[MAX_PATH];
	// buffer that receives the null-terminated
	// string for the description
	TCHAR szDesc[MAX_PATH];
	// structure that receives the information about the shortcut
	WIN32_FIND_DATA wfd;
	WCHAR wszTemp[MAX_PATH];

	lpszFilePath[0] = '\0';

	// Get a pointer to the IShellLink interface
	hRes = CoCreateInstance(CLSID_ShellLink,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IShellLink,
		(void**)&psl);

	if (SUCCEEDED(hRes))
	{
		// Get a pointer to the IPersistFile interface
		IPersistFile* ppf = NULL;
		psl->QueryInterface(IID_IPersistFile, (void**)&ppf);


		// IPersistFile is using LPCOLESTR,
				// so make sure that the string is Unicode
#if !defined _UNICODE
		MultiByteToWideChar(CP_ACP, 0, lpszShortcutPath,
			-1, wszTemp, MAX_PATH);
#else
		wcsncpy_s(wszTemp, lpszShortcutPath, MAX_PATH);
#endif

		// Open the shortcut file and initialize it from its contents
		hRes = ppf->Load(wszTemp, STGM_READ);
		if (SUCCEEDED(hRes))
		{
			// Try to find the target of a shortcut,
						// even if it has been moved or renamed
			hRes = psl->Resolve(NULL, SLR_UPDATE);
			if (SUCCEEDED(hRes))
			{
				// Get the path to the shortcut target
				hRes = psl->GetPath(szPath,
					MAX_PATH, &wfd, SLGP_RAWPATH);
				if (FAILED(hRes))
					return hRes;

				// Get the description of the target
				hRes = psl->GetDescription(szDesc,
					MAX_PATH);
				if (FAILED(hRes))
					return hRes;

				lstrcpyn(lpszFilePath, szPath, MAX_PATH);

			}
		}
	}

	return hRes;
}

void CheckAndLogInvalidDomain(const std::wstring& strUserDomain) {
	InvalidDomainFlag = false;
	if (!InvalidDomainFlag) {
		InvalidDomainFlag = true;
		// Convert domain name to byte sequence then log it
		printf("Invalid domain name1 ");// << endl;

			// Convert domain name to byte sequence then log it
		std::string utf8Bytes;
		DG_WideCharToMultiByte(CP_UTF8, strUserDomain.c_str(), -1, false, utf8Bytes);
		auto buildUTF8WithHex = [](const char* s) {
			std::string res;
			auto p = s;
			while (*p) {
				unsigned char c = *p & 0xFF;
				if (c < 127) {
					res += c;
				}
				else {
					char hex[6];
					snprintf(hex, _countof(hex), "hex%02X", c);
					res += hex;
				}
				++p;
			}
			return res;
		};

		auto utf8HexStr = buildUTF8WithHex(utf8Bytes.c_str());
		printf("ByteSequence: %hs\n",
			utf8HexStr.c_str());
	}
	else {
		// Success case so clear the flag
		InvalidDomainFlag = false;
		printf("Valid domain name1 ");// << endl;
	}
}

//int main()
void _tmain(int argc, TCHAR* argv[])
{
	CoInitialize(NULL);   //<< add

	CheckAndLogInvalidDomain(L"Manoj¢");
	//CheckAndLogInvalidDomain();
	//CheckAndLogInvalidDomain();

	LPCTSTR lpszShortcutPath = L"C:\\dg\\git\\sasource\\sREADME.md";//(L"文件");
	TCHAR szFilePath[MAX_PATH];

	HRESULT hRes = ResolveShortcut(lpszShortcutPath, szFilePath);
	printf("Succeeded: path = %ws ", szFilePath);// << endl;

	CoUninitialize();     //<< add
	DWORD  retval = 0;
	BOOL   success;
	TCHAR  buffer[BUFSIZE] = TEXT("");
	TCHAR  buf[BUFSIZE] = TEXT("");
	TCHAR** lppPart = { NULL };

	if (argc != 2)
	{
		_tprintf(TEXT("Usage: %s [file]\n"), argv[0]);
		return;
	}

	// Retrieve the full path name for a file. 
	// The file does not need to exist.

	retval = GetFullPathName(argv[1],
		BUFSIZE,
		buffer,
		lppPart);

	if (retval == 0)
	{
		// Handle an error condition.
		printf("GetFullPathName failed (%d)\n", GetLastError());
		return;
	}
	else
	{
		_tprintf(TEXT("The full path name is:  %s\n"), buffer);
		if (lppPart != NULL && *lppPart != 0)
		{
			_tprintf(TEXT("The final component in the path name is:  %s\n"), *lppPart);
		}
	}


	// Create a long directory name for use with the next two examples.

	success = CreateDirectory(LONG_DIR_NAME,
		NULL);

	if (!success)
	{
		// Handle an error condition.
		printf("CreateDirectory failed (%d)\n", GetLastError());
		return;
	}


	// Retrieve the short path name.  

	retval = GetShortPathName(LONG_DIR_NAME,
		buf,
		BUFSIZE);

	if (retval == 0)
	{
		// Handle an error condition.
		printf("GetShortPathName failed (%d)\n", GetLastError());
		return;
	}
	else _tprintf(TEXT("The short name for %s is %s\n"),
		LONG_DIR_NAME, buf);


	// Retrieve the long path name.  

	retval = GetLongPathName(buf,
		buffer,
		BUFSIZE);

	if (retval == 0)
	{
		// Handle an error condition.
		printf("GetLongPathName failed (%d)\n", GetLastError());
		return;
	}
	else _tprintf(TEXT("The long name for %s is %s\n"), buf, buffer);

	// Clean up the directory.

	success = RemoveDirectory(LONG_DIR_NAME);
	if (!success)
	{
		// Handle an error condition.
		printf("RemoveDirectory failed (%d)\n", GetLastError());
		return;
	}

	int boardDimensions = 9;
	
	cout << " SOLVE SUDOKU " << endl;
	vector<vector<int>> board{ 
		{ 3, 0, 6, 5, 0, 8, 4, 0, 0 },
		{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
		{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
		{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
		{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
		{ 1, 9, 1, 0, 0, 0, 2, 5, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
		{ 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

	SudokuSolver soduku(board, boardDimensions);
	bool solved = true;// soduku.Solve();
	if (solved) {
		cout << " SOLVED " << endl;
		//soduku.PrintBoard({}, soduku.SOLVED);
	}
	else {
		cout << " NO SOLUTION , print why it couldnt be solved, board state show all the tries that were made :" << endl;
		/*for (auto b : soduku.board_state) {
			cout << " Intermediate State " << endl;
			soduku.PrintBoard(b, soduku.UNSOLVED_BOARD);
		}*/
	}

	/*vector<vector<int>> board1{
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 } };*/

	vector<vector<int>> board1{
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 } };

	
	/*vector<vector<int>> board1{
		{ 0, 0, 0, 0},
		{ 0, 0, 0, 0},
		{ 0, 0, 0, 0},
		{ 0, 0, 0, 0} };*/

	EQueens queens(board1);

	bool s = true;//queens.Solve();
	//void Print();
	if (s) {
		cout << " SOLVED " << endl;
		//queens.PrintBoard();
	} else {
		cout << " NO SOLUTION , Queens :" << endl;
	}

	BinaryTree* root = new BinaryTree(1);
	root->left = new BinaryTree(2);
	root->right = new BinaryTree(3);
	root->left->left = new BinaryTree(4);
	root->left->right = new BinaryTree(5);

	//root->right->left = new BinaryTree(6);
	root->right->right = new BinaryTree(7);

	root->left->left->left = new BinaryTree(8);
	root->left->left->right = new BinaryTree(9);

	root->left->right->right = new BinaryTree(10);
	root->right->right->left = new BinaryTree(11);

	PrintLevel(root);
	PrintLevelR(root, 0);

	cout << endl;

	for (auto l = levels.begin(); l != levels.end(); ++l) {
		for (auto v = l->second.begin(); v != l->second.end(); ++v) {
			cout << *v << " ";
		}
		cout << endl;
	}

	vector<int> nums{ 2,3,1,1,4 };
	//cout << "jumps : " << jump(nums) << endl;
	cout << "jumps : " << 9%8 << endl;

	LruCache cache(4);
	cache.refer(1, 'A');
	cache.display();
	cache.refer(2, 'B');
	cache.display();
	cache.refer(3, 'C');
	cache.display();
	cache.get(1, 'A');
	cache.display();
	/*cache.refer(5);
	cache.display();
	cache.refer(2);
	cache.display();
	cache.refer(4);
	cache.display();*/

	if (true) {
		std::wstring wcs;

		LPCWSTR dn = //L"more text";
			// L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt";
			// L"C:/Users/jkim/Desktop/ローカル/dummy.csv";
			// L"file:///C:/Users/jkim/Desktop/ローカル/¡¢£¤¥¦§¨©ª«¬-®¯°±²³´µº»½Áôõ.doc";
			L"file:///C:/Users/jkim/Desktop/good.doc";


		LPCWSTR dn1 = L"ローカル";
		std::string s = wstring_to_utf8_hex(dn1);
		//s.assign(wSS.begin(), wSS.end());

		std::string outStr;
		if (Decode1(s.c_str(), outStr, false))
		{
			std::wstring dst;
			MultiByteToWideChar(CP_ACP, outStr.c_str(), -1, true, dst);
			//return true;
		}

		LPWSTR dn2 = nullptr;
		GetDisplayName(&dn2);

		bool r = Decode(dn, wcs, false);

		//if (_wcsnicmp(wcs.c_str(), L"file:///", 8) == 0)
		{
			wcs = wcs.substr(8);
		}

		std::string strPathMultiByte = DG_WideCharToMultiByte(CP_UTF8, wcs.c_str(), -1, false);
		cout << strPathMultiByte << endl;
	}

	/*
	std::wstring wcs;

	LPCWSTR dn = //L"more text";
		//L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt";
	//L"C:/Users/jkim/Desktop/ローカル/dummy.csv";

	std::wstring string_to_convert;

	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	std::string converted_str = converter.to_bytes(dn);

	std::string outStr;
	std::wstring dst1;
	
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	std::wstring convws = converterX.from_bytes(converted_str);

	if (Decode1(converted_str.c_str(), outStr, false))
	{
		std::wstring dst;
		MultiByteToWideChar(CP_ACP, outStr.c_str(), -1, true, dst1);
		//wstring ws = utf8_hex_to_wstring(outStr.c_str());
		//MultiByteToWideChar(CP_ACP, outStr.c_str(), -1, true, dst);
		//return true;
	}


	Decode(dn, wcs, false);

	//Decode2(dn, wcs, false);

	//Decode2();
	//LPCWSTR dn1 = L"ローカル";
	std::string s4 = wstring_to_utf8_hex(dn);

	std::wstring newja3 = utf8_hex_to_wstring(s4);

	LPCWSTR dn1 = L"ローカル";
	std::string s2 = wstring_to_utf8_hex(dn1);

	std::wstring newja2 = utf8_hex_to_wstring(s2);

	std::wstring ja = L"ドイツ語で検索していてこちらのサイトにたどり着きました。";
	//wstring_to_utf8_hex()

	std::string s1 = wstring_to_utf8_hex(ja);

	std::wstring dst;
	//MultiByteToWideChar(CP_ACP, s1.c_str(), -1, true, dst);
	
	std::wstring newja1 = utf8_hex_to_wstring(s1);

	std::string hex = "%E3%83%89%E3%82%A4%E3%83%84%E8%AA%9E%E3%81%A7%E6%A4%9C%E7%B4%A2%E3%81%97%E3%81%A6%E3%81%84%E3%81%A6%E3%81%93%E3%81%A1%E3%82%89%E3%81%AE%E3%82%B5%E3%82%A4%E3%83%88%E3%81%AB%E3%81%9F%E3%81%A9%E3%82%8A%E7%9D%80%E3%81%8D%E3%81%BE%E3%81%97%E3%81%9F%E3%80%82";
	
	std::wstring newja = utf8_hex_to_wstring(hex);

	std::cout << "match?=" << (newja == ja ? "yes" : "no") << std::endl;
	*/

	if (true) {
		LPCWSTR dn = //L"more text";

			//L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt"; // if
			//L"file:///C:/Users/jkim/Desktop/ローカル/¡¢£¤¥¦§¨©ª«¬-®¯°±²³´µº»½Áôõ.doc"; // if
			L"file:///C:/Users/jkim/Desktop/good.doc"; // else
			//L"file:///C:/Users/jkim/Desktop/ローカル/abc.doc";

		auto cch = WideCharToMultiByte(CP_UTF8, 0, dn, -1, nullptr, 0, nullptr, nullptr);
		std::unique_ptr<char> mbs(new char[cch + 1]);
		WideCharToMultiByte(CP_UTF8, 0, dn, -1, mbs.get(), cch + 1, nullptr, nullptr);

		BOOL b = IsUnicode(mbs.get(), cch + 1);

	}

	if (true) {
		std::wstring wcs1;

		LPCWSTR dn = //L"more text";

			//L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt"; // if
			L"file:///C:/Users/jkim/Desktop/ローカル/¡¢£¤¥¦§¨©ª«¬-®¯°±²³´µº»½Áôõ.doc"; // if
			//L"file:///C:/Users/jkim/Desktop/good.doc"; // else
			//L"file:///C:/Users/jkim/Desktop/ローカル/abc.doc";

		auto cch = WideCharToMultiByte(CP_UTF8, 0, dn, -1, nullptr, 0, nullptr, nullptr);
		std::unique_ptr<char> mbs(new char[cch + 1]);
		WideCharToMultiByte(CP_UTF8, 0, dn, -1, mbs.get(), cch + 1, nullptr, nullptr);

		std::string s;

		std::wstring wcs;


		INT iMask = IS_TEXT_UNICODE_UNICODE_MASK;      // The value is a combination of 
		INT iMask1 = IS_TEXT_UNICODE_UNICODE_MASK;      // The value is a combination of 

		bool u1 = ::IsTextUnicode(dn, wcslen(dn), NULL);
		
		bool u2 = ::IsTextUnicode(dn, wcslen(dn), &iMask1);

		bool u3 = ::IsTextUnicode(mbs.get(), cch + 1, NULL);

		bool u4 = ::IsTextUnicode(mbs.get(), cch + 1, &iMask);

		//if (!u3)
		{
			// Not UNICODE
			Decode(dn, wcs, false);
			if (_wcsnicmp(wcs.c_str(), L"file:///", 8) == 0)
			{
				wcs = wcs.substr(8);
			}
		}
		/*else {
			// is UNICODE
			// 
			// AG-45515 and AG-47471 : when the file path has unicode characters, call to Decode(), messes up the
			// unicode folder path or filename. Hence removed call to Decode.
			if (_wcsnicmp(dn, L"file:///", 8) == 0)
			{
				wcs = dn + 8;
			}
		}*/
	}

	if (true)
	{   // SA-15484; work around for outlook only; a full regression testing for all application is not an
		// option;  localize change to outlook only.  Problem with the code in the else block is converting 
		// from wide to multibyte and back to wide with C_UTF8 does not work for files with urlencoded
		// filenames (e.g. ¡¢£¤¥¦§¨©ª«¬-®¯°±²³´µº»½Áôõ.doc).  To avoid this problem, we simply decode the 
		// the wide string.
		std::wstring wcs1;

		LPCWSTR dn = //L"more text";
			
			//L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt";
			L"file:///C:/Users/jkim/Desktop/ローカル/¡¢£¤¥¦§¨©ª«¬-®¯°±²³´µº»½Áôõ.doc";


		/*Decode(
			dn,
			wcs1, false);*/

		if (_wcsnicmp(dn, L"file:///", 8) == 0)
		{
			wcs1 = dn + 8;
		}

		//==============================================
		// SA-15484 7.4.1 dante 2017/11/09
		// We're doing all this work to get the correct
		// "wcs" and then we don't do anything with it!
		//
		// Call the callback function.
		//==============================================
		/*if (fnCB != nullptr)
		{
			fnCB(wcs.c_str());
		}*/

		auto cch = WideCharToMultiByte(CP_UTF8, 0,
			//L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt", 
			wcs1.c_str(),
			-1, nullptr, 0, nullptr, nullptr);

		std::unique_ptr<char> mbs(new char[cch + 1]);
		WideCharToMultiByte(CP_UTF8, 0,
			//L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt", 
			wcs1.c_str(),
			-1, mbs.get(), cch + 1, nullptr, nullptr);

		std::string s;
		Decode1(mbs.get(), s, false);

		if (_strnicmp(s.c_str(), "file:///", 8) == 0)
		{
			s = s.substr(8);
		}

		//::DebugTrace (_DG ("%hs"), s.c_str ());

		//std::wstring wsTmp(s.begin(), s.end());


		cch = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
		std::unique_ptr<WCHAR> wcs(new WCHAR[cch + 1]);
		MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, wcs.get(), cch + 1);

		std::string strPathMultiByte = DG_WideCharToMultiByte(CP_UTF8, wcs.get(), -1, false);
		cout << strPathMultiByte << endl;
	}
	else
	{
		auto cch = WideCharToMultiByte(CP_UTF8, 0, L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt", -1, nullptr, 0, nullptr, nullptr);
		std::unique_ptr<char> mbs(new char[cch + 1]);
		WideCharToMultiByte(CP_UTF8, 0, 
			L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt", -1, mbs.get(), cch + 1, nullptr, nullptr);

		std::string s;
		Decode1(mbs.get(), s, false);

		if (_strnicmp(s.c_str(), "file:///", 8) == 0)
		{
			s = s.substr(8);
		}

		//::DebugTrace (_DG ("%hs"), s.c_str ());

		//std::wstring wsTmp(s.begin(), s.end());


		cch = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
		std::unique_ptr<WCHAR> wcs(new WCHAR[cch + 1]);
		MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, wcs.get(), cch + 1);
		
		std::wstring wcs1;
		//LPCWSTR dn = //L"more text";
			//L"file:///C:/Users/jkim/Desktop/ローカル/%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC-%AE%AF%B0%B1%B2%B3%B4%B5%BA%BB%BD%C1%F4%F5.doc.csv.txt";
		Decode(
			wcs.get(),
			wcs1, false);
		//ok = true;

		/*if (fnCB != nullptr)
		{
			fnCB(wcs.get());
		}*/
	}
}

/*
	2 - a b c
	3 - d e f

	v[c] - abc
	v[]

	gen (m 0)
	for (each) {
	  gen ()

*/