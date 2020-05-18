// RegExp.h: interface for the CRegExp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGEXP_H__B144C526_5353_4593_8785_ACC862AF23BE__INCLUDED_)
#define AFX_REGEXP_H__B144C526_5353_4593_8785_ACC862AF23BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NSUBEXP  10
 
 
class CRegExp
{
public:
	CRegExp();
	~CRegExp();
	
	CRegExp *RegComp( const TCHAR *re );
	int RegFind(const TCHAR *str);
	TCHAR* GetReplaceString( const TCHAR* sReplaceExp );
	int GetFindLen()
	{
		if( startp[0] == NULL || endp[0] == NULL )
			return 0;
		
		return endp[0] - startp[0];
	}
	
	
private:
	TCHAR *regnext(TCHAR *node);
	void reginsert(TCHAR op, TCHAR *opnd);
	
	int regtry(TCHAR *string);
	int regmatch(TCHAR *prog);
	size_t regrepeat(TCHAR *node);
	TCHAR *reg(int paren, int *flagp);
	TCHAR *regbranch(int *flagp);
	void regtail(TCHAR *p, TCHAR *val);
	void regoptail(TCHAR *p, TCHAR *val);
	TCHAR *regpiece(int *flagp);
	TCHAR *regatom(int *flagp);
	
	// Inline functions
private:
	TCHAR OP(TCHAR *p) {return *p;};
	TCHAR *OPERAND( TCHAR *p) {return (TCHAR*)((short *)(p+1)+1); };
	
	// regc - emit (if appropriate) a byte of code
	void regc(TCHAR b)
	{
		if (bEmitCode)
			*regcode++ = b;
		else
			regsize++;
	};
	
	// regnode - emit a node
	TCHAR *	regnode(TCHAR op)
	{
		if (!bEmitCode) {
			regsize += 3;
			return regcode;
		}
		
		*regcode++ = op;
		*regcode++ = _T('\0');		/* Null next pointer. */
		*regcode++ = _T('\0');
		
		return regcode-3;
	};
	
	
private:
	BOOL bEmitCode;
	BOOL bCompiled;
	TCHAR *sFoundText;
	
	TCHAR *startp[NSUBEXP];
	TCHAR *endp[NSUBEXP];
	TCHAR regstart;		// Internal use only. 
	TCHAR reganch;		// Internal use only. 
	TCHAR *regmust;		// Internal use only. 
	int regmlen;		// Internal use only. 
	TCHAR *program;		// Unwarranted chumminess with compiler. 
	
	TCHAR *regparse;	// Input-scan pointer. 
	int regnpar;		// () count. 
	TCHAR *regcode;		// Code-emit pointer; �dummy = don't. 
	TCHAR regdummy[3];	// NOTHING, 0 next ptr 
	long regsize;		// Code size. 
	
	TCHAR *reginput;	// String-input pointer. 
	TCHAR *regbol;		// Beginning of input, for ^ check. 
};

#endif // !defined(AFX_REGEXP_H__B144C526_5353_4593_8785_ACC862AF23BE__INCLUDED_)
