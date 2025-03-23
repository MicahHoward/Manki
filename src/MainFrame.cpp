#include "MainFrame.h"
#include "skills/addition.h"
#include "skills/subtraction.h"
#include "skills/multiplication.h"
#include <wx/wx.h>
#include <wx/simplebook.h>
#include <wx/intl.h>
#include <wx/collpane.h>
#include "backend.h"
#include "db.h"
#include <chrono>
#include <thread>

static wxSimplebook* main_book;
wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
std::string solution;
wxStaticBitmap* image;
wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
        // Creates
        main_book = new wxSimplebook(this, wxID_ANY);

        //
        wxPanel* main_panel = new wxPanel(main_book);
        wxCollapsiblePane* coll_pane = new wxCollapsiblePane(main_panel, wxID_ANY, "Skills:", wxDefaultPosition, wxSize(200,200));
        wxStaticBitmap* logo = new wxStaticBitmap(main_panel, wxID_ANY, wxBitmap(wxImage(wxBitmap("logo.png", wxBITMAP_TYPE_PNG).ConvertToImage()).Scale(200,200)), wxPoint(150,50), wxSize(200, 200));
        int number_of_skills = get_number_of_skills();

        wxWindow* win = coll_pane->GetPane();
        wxSizer* paneSz = new wxGridSizer(number_of_skills, 2, 0, 0);
        win->SetSizer(paneSz);
        paneSz->SetSizeHints(win);
        main_sizer->Add(logo, wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
        main_sizer->Add(coll_pane, wxGROW | wxALL, 5);

        main_panel->SetSizer(main_sizer);
        
        main_book->Bind(wxEVT_COLLAPSIBLEPANE_CHANGED, &MainFrame::OnCollapsiblePaneClicked, this);


        // Creates buttons for each skill
        std::string* skill_names = get_skill_names();

        std::cout << skill_names[0] << '\n';

        for(int i = 0; i < number_of_skills; i++){
                // wx_IDs may not be one or zero, so we use 2i for the skill button and 2i+1 for the stats button
                paneSz->Add(new wxButton(win, 2*(i+1), skill_names[i] , wxPoint(150,50), wxSize(100,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                paneSz->Add(new wxButton(win, 2*(i+1) + 1, "Stats", wxPoint(150,50), wxSize(100,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                Connect(2*(i+1), wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnSkillButtonClicked));
                Connect(2*(i+1) + 1, wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnStatsButtonClicked));
        }

       CreateStatusBar();

        main_book->AddPage(main_panel, "Welcome");

        wxPanel* skill_panel = new wxPanel(main_book, wxID_ANY);
        wxButton* back_button = new wxButton(skill_panel, wxID_ANY, "Back", wxPoint(150,50), wxSize(100,35));
        wxTextCtrl* textEntry = new wxTextCtrl(skill_panel, wxID_ANY, "", wxPoint(150,50), wxSize(100,35), wxTE_PROCESS_ENTER);
        back_button->Bind(wxEVT_BUTTON, &MainFrame::OnBackButtonClicked, this);
        textEntry->Bind(wxEVT_TEXT, &MainFrame::OnTextChanged, this);
        textEntry->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnTextEntered, this);
        
        //image stuff
        image = new wxStaticBitmap(skill_panel, wxID_ANY, wxBitmap("problem.png", wxBITMAP_TYPE_PNG), wxPoint(150,50), wxSize(100, 100), wxCENTER);
        boxSizer->Add(back_button, 0, wxCENTER | wxALL, 10);
        boxSizer->Add(image, 0, wxCENTER | wxALL, 10);
        boxSizer->Add(textEntry, 0, wxCENTER | wxALL, 10);
        skill_panel->SetSizer(boxSizer);

        main_book->AddPage(skill_panel, "Welcome");
}

void MainFrame::OnCollapsiblePaneClicked(wxCollapsiblePaneEvent& event) {
                main_sizer->Layout();
}

void MainFrame::OnSkillButtonClicked(wxCommandEvent& evt) {
        // skillIDs start at 1 and button ids start at 2, so we subtract 1
        int skillID = (evt.GetId()/2);
        std::string* problem_and_solution = generate_problem(skillID);

        // TODO: REPLACE THIS GARBAGE BY SWITCHING TO MicroLaTeX OR SOME OTHER LIBRARY
        int mypid = fork();

        if(0 == mypid){
                char* args[]={"./latex_generator", problem_and_solution[0].data(), "problem.png", NULL};
                execvp(args[0], args);

        }
        // waits for
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        image->SetBitmap(wxBitmap("problem.png", wxBITMAP_TYPE_PNG));
        solution = problem_and_solution[1];
        main_book->SetSelection(1);

}

void MainFrame::OnStatsButtonClicked(wxCommandEvent& evt) {
        // skillIDs start at 1 and button ids start at 2, so we subtract 1
        int skillID = ((evt.GetId()-1)/2);
        std::string stats = get_skill_info(skillID);

        wxMessageBox(stats);
}

void MainFrame::OnTextChanged(wxCommandEvent& evt) {
        wxString str = wxString::Format("Text: %s", evt.GetString());
        wxLogStatus(str);
}

void MainFrame::OnTextEntered(wxCommandEvent& evt) {
        if(evt.GetString() == solution){
                wxMessageBox(wxT("Correct"));
        } else{
                wxMessageBox(wxT("Incorrect, solution was " + solution));
        }
}

void MainFrame::OnBackButtonClicked(wxCommandEvent& evt) {
        main_book->SetSelection(0);
}
