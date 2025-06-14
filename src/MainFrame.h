#pragma once
#include <wx/wx.h>
#include <wx/collpane.h>

// wxWidgets main class
class MainFrame : public wxFrame
{
        public:
                MainFrame(const wxString& title);
        private:
                void OnCollapsiblePaneClicked(wxCollapsiblePaneEvent& evt);
                void RefreshPanels();
                void OnSkillButtonClicked(wxCommandEvent& evt);
                void GenerateNewProblem(int skillID);
                void OnStatsButtonClicked(wxCommandEvent& evt);
                void OnTimer(wxTimerEvent&);
                void OnAddSkillButtonClicked(wxCommandEvent& evt);
                void OnAddTimedSkillButtonClicked(wxCommandEvent& evt);
                void OnBackButtonClicked(wxCommandEvent& evt);
                void OnMySkillsButtonClicked(wxCommandEvent& evt);
                void OnBrowserButtonClicked(wxCommandEvent& evt);
                void OnLearntButtonClicked(wxCommandEvent& evt);
                void OnTimedSkillsButtonClicked(wxCommandEvent& evt);
                void OnTextChanged(wxCommandEvent& evt);
                void OnTextEntered(wxCommandEvent& evt);
};
