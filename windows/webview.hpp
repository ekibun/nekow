#include <windows.h>
#include <comdef.h>
#include <wrl.h>
#include <winerror.h>

namespace webview
{
#include "webview/WebView2.h"
#include "webview/WebView2EnvironmentOptions.h"

  class WebView
      : public ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler,
        public ICoreWebView2CreateCoreWebView2ControllerCompletedHandler
  {
    ICoreWebView2Controller *webviewController = nullptr;
    ICoreWebView2 *webviewWindow = nullptr;
    HWND hwnd;

  public:
    ULONG STDMETHODCALLTYPE AddRef() { return 1; }
    ULONG STDMETHODCALLTYPE Release() { return 1; }
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID *ppv)
    {
      return S_OK;
    }
    HRESULT STDMETHODCALLTYPE Invoke(
        HRESULT res,
        ICoreWebView2Environment *env)
    {
      env->CreateCoreWebView2Controller(hwnd, this);
      return S_OK;
    }
    HRESULT STDMETHODCALLTYPE Invoke(HRESULT res,
                                     ICoreWebView2Controller *controller)
    {
      controller->AddRef();
      this->webviewController = controller;

      EventRegistrationToken token;
      controller->get_CoreWebView2(&webviewWindow);
      webviewWindow->AddRef();
      webviewWindow->Navigate(L"https://www.bing.com");
      SendMessage(hwnd, WM_SIZE, NULL, NULL);
      // webviewWindow->AddWebResourceRequestedFilter(L"*", COREWEBVIEW2_WEB_RESOURCE_CONTEXT_ALL);
      // webviewWindow->add_WebResourceRequested(this, &token);
      // webviewWindow->add_NavigationCompleted(this, &token);
      return S_OK;
    }
    void put_Bounds(RECT bounds)
    {
      if (webviewController != nullptr) {
        webviewController->put_Bounds(bounds);
      }
    }
    WebView(HWND hwnd) : hwnd(hwnd)
    {
      auto options = Microsoft::WRL::Make<CoreWebView2EnvironmentOptions>();
      // options->put_AdditionalBrowserArguments(L"--mute-audio"); // --headless
      if (FAILED(CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, options.Get(), this)))
      {
        exit(1);
      }
    }

    ~WebView()
    {
      if (webviewController)
      {
        webviewController->Close();
        webviewController = nullptr;
      }
    }
  };
}