
// Client->Server request message
struct	TalkCtlMessage	{
	u_char		m_Version;	// Protocol Version
	u_char		m_Type;		// Request type
	u_char		m_Answer;	// Unused
	u_char		m_Pad;
	u_long		m_ID;		// Request ID
	osockaddr	m_Addr;
	osockaddr	m_ctlAddr;
	long		m_PID;		// Caller's process id
	char		m_LName[12];// Caller's name (local)
	char		m_RName[12];// Callee's name (remote)
	char		m_RTTY[16];	// Callee's tty name

};

// Server->Client response message
struct	TalkCtlResponse	{
	u_char		m_Version;	// Protocol Version
	u_char		m_Type;		// Request type
	u_char		m_Answer;	// Response itself
	u_char		m_Pad;
	u_long		m_ID;		// Request ID
	osockaddr	m_Addr;		// Adress for establishing communication
};

enum	{
	talkCtlVersion = 1,
	// Message Types
	talkCtlReqLeaveInvite		= 0,	// Leave an invitation with server
	talkCtlReqLookUp		= 1,	// Check for invitation by callee
	talkCtlReqDelete		= 2,	// Delete invitation by caller
	talkCtlReqAnnounce		= 3,	// Announce invitation by caller
	// Answers
	talkCtlSuccess			= 0,	// Operation completed properly
	talkCtlNotHere			= 1,	// Callee not logged in
	talkCtlFailed			= 2,	// Failed for unexplained reason
	talkCtlMachineUnknown	= 3,	// Caller's machine name unknown
	talkCtlPermissionDenied	= 4,	// Callee's tty doesn't permit announce
	talkCtlUnknownRequest	= 5,	// Request has invalid type
	talkCtlBadVersion		= 6,	// Request has invalid protocol version
	talkCtlBadAddr			= 7,	// Request has invalid addr value
	talkCtlBadCtlAddr		= 8,	// Request has invalid ctlAddr value

	talkCtlReserved			= 255	// Internal use
};