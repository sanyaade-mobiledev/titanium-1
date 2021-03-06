/**
 * Appcelerator Titanium - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#include "webkit_ui_delegate.h"

#include "win32_user_window.h"
#include "win32_ui_binding.h"
#include <comutil.h>

using namespace ti;

Win32WebKitUIDelegate::Win32WebKitUIDelegate(Win32UserWindow *window_) : window(window_), ref_count(1) {
	logger = Logger::Get("UI.Win32WebKitUIDelegate");
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = 0;

    if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<IWebUIDelegate*>(this);
    else if (IsEqualGUID(riid, IID_IWebUIDelegate))
        *ppvObject = static_cast<IWebUIDelegate*>(this);
        /*
    else if (IsEqualGUID(riid, IID_IWebUIDelegatePrivate))
        *ppvObject = static_cast<IWebUIDelegatePrivate*>(this);
    else if (IsEqualGUID(riid, IID_IWebUIDelegatePrivate2))
        *ppvObject = static_cast<IWebUIDelegatePrivate2*>(this);
    else if (IsEqualGUID(riid, IID_IWebUIDelegatePrivate3))
        *ppvObject = static_cast<IWebUIDelegatePrivate3*>(this);
		*/
    else
        return E_NOINTERFACE;

	return S_OK;
}

ULONG STDMETHODCALLTYPE
Win32WebKitUIDelegate::AddRef()
{
	return ++ref_count;
}

ULONG STDMETHODCALLTYPE
Win32WebKitUIDelegate::Release()
{
	ULONG new_count = --ref_count;
	if (!new_count) delete(this);

	return new_count;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::createWebViewWithRequest(
	/* [in] */ IWebView *sender,
	/* [in] */ IWebURLRequest *request,
	/* [retval][out] */ IWebView **newWebView)
{
	logger->Debug("createWebViewWithRequest() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::webViewClose(
	/* [in] */ IWebView *sender)
{
	logger->Debug("webViewClose() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::webViewFocus(
	/* [in] */ IWebView *sender)
{
	logger->Debug("webViewFocus() called");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::webViewUnfocus(
	/* [in] */ IWebView *sender)
{
	logger->Debug("webViewUnfocus() called");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::setStatusText(
	/* [in] */ IWebView *sender,
	/* [in] */ BSTR text)
{
	std::string s;

	if(text)
	{
		s.append(_bstr_t(text));
	}
	logger->Debug("setStatusText() called '%s'", s.c_str());
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::setFrame(
	/* [in] */ IWebView *sender,
	/* [in] */ RECT *frame)
{
	Bounds b;
	b.x = frame->left;
	b.y = frame->top;
	b.width = frame->right - frame->left;
	b.height = frame->bottom - frame->top;
	window->SetBounds(b);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::webViewFrame(
	/* [in] */ IWebView *sender,
	/* [retval][out] */ RECT *frame)
{
	frame->left = window->GetX();
	frame->top = window->GetY();
	frame->right = window->GetX() + window->GetWidth();
	frame->bottom = window->GetY() + window->GetHeight();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::runJavaScriptAlertPanelWithMessage(
	/* [in] */ IWebView *sender,
	/* [in] */ BSTR message)
{
	HWND handle = window->GetWindowHandle();
	std::string title(window->GetTitle());
	std::string msg;

	if(message)
	{
		msg.append(bstr_t(message));
	}

	//Win32PopupDialog popupDialog(handle);
	//popupDialog.SetTitle(title);
	//popupDialog.SetMessage(msg);
	//int r = popupDialog.Show();

	MessageBox(0,msg.c_str(),title.c_str(),0);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::runJavaScriptConfirmPanelWithMessage(
	/* [in] */ IWebView *sender,
	/* [in] */ BSTR message,
	/* [retval][out] */ BOOL *result)
{
	HWND handle = window->GetWindowHandle();
	std::string title(window->GetTitle());
	std::string msg;

	if(message)
	{
		msg.append(bstr_t(message));
	}

	//Win32PopupDialog popupDialog(handle);
	//popupDialog.SetTitle(title);
	//popupDialog.SetMessage(msg);
	//popupDialog.SetShowCancelButton(true);
	//int r = popupDialog.Show();

	int r = MessageBox(0,msg.c_str(),title.c_str(),MB_ICONINFORMATION | MB_OKCANCEL);

	*result = (r == IDYES);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::runJavaScriptTextInputPanelWithPrompt(
	/* [in] */ IWebView *sender,
	/* [in] */ BSTR message,
	/* [in] */ BSTR defaultText,
	/* [retval][out] */ BSTR *result)
{
	HWND handle = window->GetWindowHandle();
	std::string title(window->GetTitle());
	std::string msg = _bstr_t(message);
	std::string def;

	if(defaultText)
	{
		def.append(_bstr_t(defaultText));
	}

	Win32PopupDialog popupDialog(handle);
	popupDialog.SetTitle(title);
	popupDialog.SetMessage(msg);
	popupDialog.SetShowInputText(true);
	popupDialog.SetInputText(def);
	popupDialog.SetShowCancelButton(true);
	int r = popupDialog.Show();

	if(r == IDYES)
	{
		_bstr_t bstr1(popupDialog.GetInputText().c_str());
		*result = bstr1.copy();
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::runBeforeUnloadConfirmPanelWithMessage(
	/* [in] */ IWebView *sender,
	/* [in] */ BSTR message,
	/* [in] */ IWebFrame *initiatedByFrame,
	/* [retval][out] */ BOOL *result)
{
	logger->Debug("runBeforeUnloadConfirmPanelWithMessage() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::hasCustomMenuImplementation(
	/* [retval][out] */ BOOL *hasCustomMenus)
{
	*hasCustomMenus = TRUE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::trackCustomPopupMenu(
	/* [in] */ IWebView *sender,
	/* [in] */ OLE_HANDLE menu,
	/* [in] */ LPPOINT point)
{
	HMENU contextMenu = this->window->GetContextMenuHandle();
	if(! contextMenu)
	{
		contextMenu = Win32UIBinding::getContextMenuInUseHandle();
	}
	if(! contextMenu)
	{
		contextMenu = Win32MenuItemImpl::GetDefaultContextMenu();
	}

	if(contextMenu)
	{
		TrackPopupMenu(contextMenu,
			TPM_BOTTOMALIGN,
			point->x, point->y, 0,
			this->window->GetWindowHandle(), NULL);
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::registerUndoWithTarget(
	/* [in] */ IWebUndoTarget *target,
	/* [in] */ BSTR actionName,
	/* [in] */ IUnknown *actionArg)
{
	logger->Debug("registerUndoWithTarget() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::removeAllActionsWithTarget(
	/* [in] */ IWebUndoTarget *target)
{
	logger->Debug("removeAllActionsWithTarget() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::setActionTitle(
	/* [in] */ BSTR actionTitle)
{
	logger->Debug("setActionTitle() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::undo()
{
	logger->Debug("undo() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::redo()
{
	logger->Debug("redo() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::canUndo(
	/* [retval][out] */ BOOL *result)
{
	logger->Debug("canUndo() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::canRedo(
	/* [retval][out] */ BOOL *result)
{
	logger->Debug("canRedo() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::webViewAddMessageToConsole(
	/* [in] */ IWebView *sender,
	/* [in] */ BSTR message,
	/* [in] */ int lineNumber,
	/* [in] */ BSTR url,
	/* [in] */ BOOL isError)
{
	logger->Debug("webViewAddMesageToConsole() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::doDragDrop(
	/* [in] */ IWebView *sender,
	/* [in] */ IDataObject *dataObject,
	/* [in] */ IDropSource *dropSource,
	/* [in] */ DWORD okEffect,
	/* [retval][out] */ DWORD *performedEffect)
{
	logger->Debug("doDragDrop() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::webViewGetDlgCode(
	/* [in] */ IWebView *sender,
	/* [in] */ UINT keyCode,
	/* [retval][out] */ LONG_PTR *code)
{
	logger->Debug("webViewGetDlgCode() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::webViewPainted(
	/* [in] */ IWebView *sender)
{
	logger->Debug("webViewPainted() not implemented");
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
Win32WebKitUIDelegate::exceededDatabaseQuota(
	/* [in] */ IWebView *sender,
	/* [in] */ IWebFrame *frame,
	/* [in] */ IWebSecurityOrigin *origin,
	/* [in] */ BSTR databaseIdentifier)
{
	logger->Debug("exceededDatabaseQuota() not implemented");

    static const unsigned long long defaultQuota = 100 * 1024 * 1024;	// 100MB
    origin->setQuota(defaultQuota);

	return E_NOTIMPL;
}
