#pragma once
class CDataStruct
{
public:
	CDataStruct();
	virtual ~CDataStruct();
public:
	operator INT()
	{
		return _ttoi(m_data);
	}
private:
	CString m_data;
};

