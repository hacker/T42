class	CT42CallLogEntry : public CObject	{
public:
	enum {
		statusOk = 0, statusFailed, statusProcessed,
		statusNone
	};
	UINT m_Status;
	CTime m_Time;
	CString m_Caller;
	CString m_Callee;
	CString m_TTY;
	CTimeSpan m_Duration;
	CString m_Message;

	CT42CallLogEntry() : m_Status(statusNone) {}
	CT42CallLogEntry(CT42CallLogEntry& src) { Copy(src); }

	void Copy(const CT42CallLogEntry& src) {
		m_Status = src.m_Status;
		m_Time = src.m_Time;
		m_Caller = src.m_Caller; m_Callee = src.m_Callee;
		m_TTY = src.m_TTY;
		m_Duration = src.m_Duration;
		m_Message = src.m_Message;
	}
	CT42CallLogEntry& operator=(const CT42CallLogEntry& src) {
		Copy(src);
		return *this;
	}

	void Serialize(CArchive& ar) {
		if(ar.IsStoring()){
			ar << m_Status; 
			ar << m_Time;
			ar << m_Caller; ar << m_Callee; ar << m_TTY;
			ar << m_Duration;
			ar << m_Message;
		}else{
			ar >> m_Status;
			ar >> m_Time;
			ar >> m_Caller; ar >> m_Callee; ar >> m_TTY;
			ar >> m_Duration;
			ar >> m_Message;
		}
	}
};

inline void SerializeElements(CArchive& ar, CT42CallLogEntry* pElements, int nCount) {
	for(int tmp=0;tmp<nCount;tmp++)
		pElements[tmp].Serialize(ar);
}

typedef Klever::CBTreendex<CTime,CT42CallLogEntry,16,512> CT42CallLog;
