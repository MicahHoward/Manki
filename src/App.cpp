#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

/**
 * Root function for wxWidgets 
 *
 * @return True
 */
bool App::OnInit(){
        MainFrame* mainFrame = new MainFrame("Manki");
        mainFrame->SetClientSize(800, 600);
        mainFrame->Center();
        mainFrame->Show();
        mainFrame->SetIcon(wxIcon("icon.png"));
        wxImage::AddHandler(new wxPNGHandler);
        return true;
}
