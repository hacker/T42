class CT42Secretary	: public CT42Robot	{
public:
	virtual ~CT42Secretary();
	BOOL OnMinute();
	UINT m_limitBytes;
	CTimeSpan m_limitTime;
	static DWORD CALLBACK ESINProc(DWORD dwCookie,LPBYTE pbBuff,LONG cb,LONG FAR *pcb);
	BOOL OnIPResolved();
	CT42Secretary();
	CT42CallLogEntry m_logEntry;
	BOOL OnDetach();
	BOOL OnDisconnect();
	BOOL OnReceive(char* pData,int nBytes);
	BOOL OnConnect();
	BOOL OnAttach(T42Document* pDocument);
};

