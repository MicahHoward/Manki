#pragma once
#include <wx/wx.h>
#include <wx/collpane.h>

class MainFrame : public wxFrame
{
        public:
                MainFrame(const wxString& title);
        private:
                void OnCollapsiblePaneClicked(wxCollapsiblePaneEvent& evt);
                void UpdateMainPanel();
                void OnSkillButtonClicked(wxCommandEvent& evt);
                void GenerateNewProblem(int skillID);
                void OnStatsButtonClicked(wxCommandEvent& evt);
                void OnAddSkillButtonClicked(wxCommandEvent& evt);
                //void OnSubtractionButtonClicked(wxCommandEvent& evt);
                //void OnMultiplicationButtonClicked(wxCommandEvent& evt);
                void OnBackButtonClicked(wxCommandEvent& evt);
                void OnBrowserButtonClicked(wxCommandEvent& evt);
                void OnTextChanged(wxCommandEvent& evt);
                void OnTextEntered(wxCommandEvent& evt);
};
