#include <core/stdafx.h>
#include <core/smartview/TombStone.h>
#include <core/smartview/SmartView.h>

namespace smartview
{
	TombstoneRecord::TombstoneRecord(std::shared_ptr<binaryParser> parser)
	{
		StartTime.parse<DWORD>(parser);
		EndTime.parse<DWORD>(parser);
		GlobalObjectIdSize.parse<DWORD>(parser);
		GlobalObjectId.parse(parser, GlobalObjectIdSize, false);
		UsernameSize.parse<WORD>(parser);
		szUsername.parse(parser, UsernameSize);
	}

	void TombStone::Parse()
	{
		m_Identifier.parse<DWORD>(m_Parser);
		m_HeaderSize.parse<DWORD>(m_Parser);
		m_Version.parse<DWORD>(m_Parser);
		m_RecordsCount.parse<DWORD>(m_Parser);
		m_RecordsSize.parse<DWORD>(m_Parser);

		// Run through the parser once to count the number of flag structs
		const auto ulFlagOffset = m_Parser->GetCurrentOffset();
		for (;;)
		{
			// Must have at least 2 bytes left to have another flag
			if (m_Parser->RemainingBytes() < sizeof(DWORD) * 3 + sizeof(WORD)) break;
			(void) m_Parser->advance(sizeof DWORD);
			(void) m_Parser->advance(sizeof DWORD);
			const auto& len1 = blockT<DWORD>(m_Parser);
			m_Parser->advance(len1);
			const auto& len2= blockT<WORD>(m_Parser);
			m_Parser->advance(len2);
			m_ActualRecordsCount++;
		}

		// Now we parse for real
		m_Parser->SetCurrentOffset(ulFlagOffset);

		if (m_ActualRecordsCount && m_ActualRecordsCount < _MaxEntriesSmall)
		{
			m_lpRecords.reserve(m_ActualRecordsCount);
			for (ULONG i = 0; i < m_ActualRecordsCount; i++)
			{
				m_lpRecords.emplace_back(std::make_shared<TombstoneRecord>(m_Parser));
			}
		}
	}

	void TombStone::ParseBlocks()
	{
		setRoot(L"Tombstone:\r\n");
		addChild(m_Identifier, L"Identifier = 0x%1!08X!\r\n", m_Identifier.getData());
		addChild(m_HeaderSize, L"HeaderSize = 0x%1!08X!\r\n", m_HeaderSize.getData());
		addChild(m_Version, L"Version = 0x%1!08X!\r\n", m_Version.getData());
		addChild(m_RecordsCount, L"RecordsCount = 0x%1!08X!\r\n", m_RecordsCount.getData());
		addHeader(L"ActualRecordsCount (computed) = 0x%1!08X!\r\n", m_ActualRecordsCount);
		addChild(m_RecordsSize, L"RecordsSize = 0x%1!08X!", m_RecordsSize.getData());

		auto i = 0;
		for (const auto& record : m_lpRecords)
		{
			terminateBlock();
			addHeader(L"Record[%1!d!]\r\n", i++);
			addChild(
				record->StartTime,
				L"StartTime = 0x%1!08X! = %2!ws!\r\n",
				record->StartTime.getData(),
				RTimeToString(record->StartTime).c_str());
			addChild(
				record->EndTime,
				L"Endtime = 0x%1!08X! = %2!ws!\r\n",
				record->EndTime.getData(),
				RTimeToString(record->EndTime).c_str());
			addChild(
				record->GlobalObjectIdSize,
				L"GlobalObjectIdSize = 0x%1!08X!\r\n",
				record->GlobalObjectIdSize.getData());
			addChild(record->GlobalObjectId.getBlock());
			terminateBlock();

			addChild(record->UsernameSize, L"UsernameSize= 0x%1!04X!\r\n", record->UsernameSize.getData());
			addChild(record->szUsername, L"szUsername = %1!hs!", record->szUsername.c_str());
		}
	}
} // namespace smartview