#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit(){
        MainFrame* mainFrame = new MainFrame("Manki");
        mainFrame->SetClientSize(800, 600);
        mainFrame->Center();
        mainFrame->Show();
        wxImage::AddHandler(new wxPNGHandler);
        return true;
}
