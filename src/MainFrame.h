#pragma once
#include <wx/wx.h>
#include <wx/collpane.h>

class MainFrame : public wxFrame
{
        public:
                MainFrame(const wxString& title);
        private:
                void OnCollapsiblePaneClicked(wxCollapsiblePaneEvent& evt);
                void OnAdditionButtonClicked(wxCommandEvent& evt);
                void OnSubtractionButtonClicked(wxCommandEvent& evt);
                void OnMultiplicationButtonClicked(wxCommandEvent& evt);
                void OnBackButtonClicked(wxCommandEvent& evt);
                void OnTextChanged(wxCommandEvent& evt);
                void OnTextEntered(wxCommandEvent& evt);
};
