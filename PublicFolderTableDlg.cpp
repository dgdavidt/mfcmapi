// PublicFolderTableDlg.cpp : implementation file
#include "stdafx.h"
#include "PublicFolderTableDlg.h"
#include "ContentsTableListCtrl.h"
#include "MAPIFunctions.h"
#include "ColumnTags.h"
#include "UIFunctions.h"
#include "PropertyTagEditor.h"
#include "InterpretProp2.h"

static wstring CLASS = L"CPublicFolderTableDlg";

CPublicFolderTableDlg::CPublicFolderTableDlg(
	_In_ CParentWnd* pParentWnd,
	_In_ CMapiObjects* lpMapiObjects,
	_In_ LPCTSTR lpszServerName,
	_In_ LPMAPITABLE lpMAPITable
) :
	CContentsTableDlg(
		pParentWnd,
		lpMapiObjects,
		IDS_PUBLICFOLDERTABLE,
		mfcmapiDO_NOT_CALL_CREATE_DIALOG,
		lpMAPITable,
		(LPSPropTagArray)&sptPFCols,
		NUMPFCOLUMNS,
		PFColumns,
		NULL,
		MENU_CONTEXT_PUBLIC_FOLDER_TABLE)
{
	TRACE_CONSTRUCTOR(CLASS);
	HRESULT hRes = S_OK;

	EC_H(CopyString(&m_lpszServerName, lpszServerName, NULL));

	CreateDialogAndMenu(NULL);
}

CPublicFolderTableDlg::~CPublicFolderTableDlg()
{
	TRACE_DESTRUCTOR(CLASS);
	MAPIFreeBuffer(m_lpszServerName);
}

void CPublicFolderTableDlg::CreateDialogAndMenu(UINT nIDMenuResource)
{
	DebugPrintEx(DBGCreateDialog, CLASS, L"CreateDialogAndMenu", L"id = 0x%X\n", nIDMenuResource);
	CContentsTableDlg::CreateDialogAndMenu(nIDMenuResource);

	UpdateMenuString(
		m_hWnd,
		ID_CREATEPROPERTYSTRINGRESTRICTION,
		IDS_PFRESMENU);
}

void CPublicFolderTableDlg::OnDisplayItem()
{
}

_Check_return_ HRESULT CPublicFolderTableDlg::OpenItemProp(int /*iSelectedItem*/, __mfcmapiModifyEnum /*bModify*/, _Deref_out_opt_ LPMAPIPROP* lppMAPIProp)
{
	if (lppMAPIProp) *lppMAPIProp = NULL;
	return S_OK;
}

void CPublicFolderTableDlg::OnCreatePropertyStringRestriction()
{
	HRESULT hRes = S_OK;
	LPSRestriction lpRes = NULL;

	CPropertyTagEditor MyPropertyTag(
		IDS_PROPRES, // title
		NULL, // prompt
		PR_DISPLAY_NAME,
		m_bIsAB,
		m_lpContainer,
		this);

	WC_H(MyPropertyTag.DisplayDialog());
	if (S_OK == hRes)
	{
		CEditor MyData(
			this,
			IDS_SEARCHCRITERIA,
			IDS_PFSEARCHCRITERIAPROMPT,
			2,
			CEDITOR_BUTTON_OK | CEDITOR_BUTTON_CANCEL);
		MyData.SetPromptPostFix(AllFlagsToString(flagFuzzyLevel, true));

		MyData.InitPane(0, CreateSingleLinePane(IDS_NAME, false));
		MyData.InitPane(1, CreateSingleLinePane(IDS_ULFUZZYLEVEL, false));
		MyData.SetHex(1, FL_IGNORECASE | FL_PREFIX);

		WC_H(MyData.DisplayDialog());
		if (S_OK != hRes) return;

		wstring szString = MyData.GetStringW(0);
		// Allocate and create our SRestriction
		EC_H(CreatePropertyStringRestriction(
			CHANGE_PROP_TYPE(MyPropertyTag.GetPropertyTag(), PT_UNICODE),
			szString,
			MyData.GetHex(1),
			NULL,
			&lpRes));
		if (S_OK != hRes && lpRes)
		{
			MAPIFreeBuffer(lpRes);
			lpRes = NULL;
		}

		m_lpContentsTableListCtrl->SetRestriction(lpRes);

		SetRestrictionType(mfcmapiNORMAL_RESTRICTION);
	}
}