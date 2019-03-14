#include <core/stdafx.h>
#include <core/smartview/TimeZone.h>

namespace smartview
{
	void TimeZone::Parse()
	{
		m_lBias.parse<DWORD>(m_Parser);
		m_lStandardBias.parse<DWORD>(m_Parser);
		m_lDaylightBias.parse<DWORD>(m_Parser);
		m_wStandardYear.parse<WORD>(m_Parser);
		m_stStandardDate.wYear.parse<WORD>(m_Parser);
		m_stStandardDate.wMonth.parse<WORD>(m_Parser);
		m_stStandardDate.wDayOfWeek.parse<WORD>(m_Parser);
		m_stStandardDate.wDay.parse<WORD>(m_Parser);
		m_stStandardDate.wHour.parse<WORD>(m_Parser);
		m_stStandardDate.wMinute.parse<WORD>(m_Parser);
		m_stStandardDate.wSecond.parse<WORD>(m_Parser);
		m_stStandardDate.wMilliseconds.parse<WORD>(m_Parser);
		m_wDaylightDate.parse<WORD>(m_Parser);
		m_stDaylightDate.wYear.parse<WORD>(m_Parser);
		m_stDaylightDate.wMonth.parse<WORD>(m_Parser);
		m_stDaylightDate.wDayOfWeek.parse<WORD>(m_Parser);
		m_stDaylightDate.wDay.parse<WORD>(m_Parser);
		m_stDaylightDate.wHour.parse<WORD>(m_Parser);
		m_stDaylightDate.wMinute.parse<WORD>(m_Parser);
		m_stDaylightDate.wSecond.parse<WORD>(m_Parser);
		m_stDaylightDate.wMilliseconds.parse<WORD>(m_Parser);
	}

	void TimeZone::ParseBlocks()
	{
		setRoot(L"Time Zone: \r\n");
		addChild(m_lBias, L"lBias = 0x%1!08X! (%1!d!)\r\n", m_lBias.getData());
		addChild(m_lStandardBias, L"lStandardBias = 0x%1!08X! (%1!d!)\r\n", m_lStandardBias.getData());
		addChild(m_lDaylightBias, L"lDaylightBias = 0x%1!08X! (%1!d!)\r\n", m_lDaylightBias.getData());
		addBlankLine();
		addChild(m_wStandardYear, L"wStandardYear = 0x%1!04X! (%1!d!)\r\n", m_wStandardYear.getData());
		addChild(
			m_stStandardDate.wYear, L"stStandardDate.wYear = 0x%1!X! (%1!d!)\r\n", m_stStandardDate.wYear.getData());
		addChild(
			m_stStandardDate.wMonth, L"stStandardDate.wMonth = 0x%1!X! (%1!d!)\r\n", m_stStandardDate.wMonth.getData());
		addChild(
			m_stStandardDate.wDayOfWeek,
			L"stStandardDate.wDayOfWeek = 0x%1!X! (%1!d!)\r\n",
			m_stStandardDate.wDayOfWeek.getData());
		addChild(m_stStandardDate.wDay, L"stStandardDate.wDay = 0x%1!X! (%1!d!)\r\n", m_stStandardDate.wDay.getData());
		addChild(
			m_stStandardDate.wHour, L"stStandardDate.wHour = 0x%1!X! (%1!d!)\r\n", m_stStandardDate.wHour.getData());
		addChild(
			m_stStandardDate.wMinute,
			L"stStandardDate.wMinute = 0x%1!X! (%1!d!)\r\n",
			m_stStandardDate.wMinute.getData());
		addChild(
			m_stStandardDate.wSecond,
			L"stStandardDate.wSecond = 0x%1!X! (%1!d!)\r\n",
			m_stStandardDate.wSecond.getData());
		addChild(
			m_stStandardDate.wMilliseconds,
			L"stStandardDate.wMilliseconds = 0x%1!X! (%1!d!)\r\n",
			m_stStandardDate.wMilliseconds.getData());
		addBlankLine();
		addChild(m_wDaylightDate, L"wDaylightDate = 0x%1!04X! (%1!d!)\r\n", m_wDaylightDate.getData());
		addChild(
			m_stDaylightDate.wYear, L"stDaylightDate.wYear = 0x%1!X! (%1!d!)\r\n", m_stDaylightDate.wYear.getData());
		addChild(
			m_stDaylightDate.wMonth, L"stDaylightDate.wMonth = 0x%1!X! (%1!d!)\r\n", m_stDaylightDate.wMonth.getData());
		addChild(
			m_stDaylightDate.wDayOfWeek,
			L"stDaylightDate.wDayOfWeek = 0x%1!X! (%1!d!)\r\n",
			m_stDaylightDate.wDayOfWeek.getData());
		addChild(m_stDaylightDate.wDay, L"stDaylightDate.wDay = 0x%1!X! (%1!d!)\r\n", m_stDaylightDate.wDay.getData());
		addChild(
			m_stDaylightDate.wHour, L"stDaylightDate.wHour = 0x%1!X! (%1!d!)\r\n", m_stDaylightDate.wHour.getData());
		addChild(
			m_stDaylightDate.wMinute,
			L"stDaylightDate.wMinute = 0x%1!X! (%1!d!)\r\n",
			m_stDaylightDate.wMinute.getData());
		addChild(
			m_stDaylightDate.wSecond,
			L"stDaylightDate.wSecond = 0x%1!X! (%1!d!)\r\n",
			m_stDaylightDate.wSecond.getData());
		addChild(
			m_stDaylightDate.wMilliseconds,
			L"stDaylightDate.wMilliseconds = 0x%1!X! (%1!d!)",
			m_stDaylightDate.wMilliseconds.getData());
	}
} // namespace smartview