#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/simplebook.h>
#include <wx/intl.h>
#include <wx/collpane.h>
#include "backend.h"
#include "db.h"
#include "fsrs.h"
#include <chrono>
#include <thread>
#include <map>

static wxSimplebook* main_book;
wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
std::string solution;
wxStaticBitmap* image;
wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
wxBoxSizer* browser_box_sizer = new wxBoxSizer(wxVERTICAL);
int current_skill_id = 0;
wxTextCtrl* textEntry; 
wxCollapsiblePane* due_coll_pane; 
wxCollapsiblePane* learnt_coll_pane; 
wxCollapsiblePane* unlearnt_coll_pane; 
wxCollapsiblePane* not_retaining_coll_pane; 
wxWindow* due_win;
wxWindow* learnt_win;
wxWindow* unlearnt_win;
wxWindow* not_retaining_win;
wxSizer* dueSz;
wxSizer* learntSz;
wxSizer* unlearntSz;
wxSizer* not_retaining_sizer;
int due_coll_pane_height;
int learnt_coll_pane_height;
int unlearnt_coll_pane_height;

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
        initialize_database();
        insert_default_values();
        update_retrievability();

        // Creates
        main_book = new wxSimplebook(this, wxID_ANY);

        //
        wxPanel* main_panel = new wxPanel(main_book);
        due_coll_pane_height = 200;
        learnt_coll_pane_height = 200;
        unlearnt_coll_pane_height = 200;
        due_coll_pane = new wxCollapsiblePane(main_panel, 200, "Due Skills:", wxDefaultPosition, wxSize(400, 50));
        learnt_coll_pane = new wxCollapsiblePane(main_panel, 201, "Learnt Skills:", wxDefaultPosition, wxSize(400, 50));
        unlearnt_coll_pane = new wxCollapsiblePane(main_panel, 202, "Unlearnt Skills:", wxDefaultPosition, wxSize(400, 50));
        wxStaticBitmap* logo = new wxStaticBitmap(main_panel, wxID_ANY, wxBitmap(wxImage(wxBitmap("logo.png", wxBITMAP_TYPE_PNG).ConvertToImage()).Scale(200,200)), wxPoint(150,50), wxSize(200, 200));
        wxButton* browser_button = new wxButton(main_panel, wxID_ANY, "Skill Browser", wxPoint(150,50), wxSize(100,35));
        browser_button->Bind(wxEVT_BUTTON, &MainFrame::OnBrowserButtonClicked, this);
        int number_of_skills = get_number_of_skills();

        due_win = due_coll_pane->GetPane();
        learnt_win = learnt_coll_pane->GetPane();
        unlearnt_win = unlearnt_coll_pane->GetPane();
        dueSz = new wxGridSizer(number_of_skills, 2, 0, 0);
        learntSz = new wxGridSizer(number_of_skills, 2, 0, 0);
        unlearntSz = new wxGridSizer(number_of_skills, 2, 0, 0);
        due_win->SetSizer(dueSz);
        learnt_win->SetSizer(learntSz);
        unlearnt_win->SetSizer(unlearntSz);
        dueSz->SetSizeHints(due_win);
        learntSz->SetSizeHints(learnt_win);
        unlearntSz->SetSizeHints(unlearnt_win);
        main_sizer->Add(logo, wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
        main_sizer->Add(due_coll_pane, wxALL, 5);
        main_sizer->Add(learnt_coll_pane, wxALL, 5);
        main_sizer->Add(unlearnt_coll_pane, wxGROW | wxALL, 5);

        main_panel->SetSizer(main_sizer);
        
        main_book->Bind(wxEVT_COLLAPSIBLEPANE_CHANGED, &MainFrame::OnCollapsiblePaneClicked, this);

        // Sets up browser panel 
        wxPanel* browser_panel = new wxPanel(main_book);
        wxButton* browser_back_button = new wxButton(browser_panel, wxID_ANY, "Back to Main Menu", wxPoint(150,50), wxSize(100,35));
        browser_back_button->Bind(wxEVT_BUTTON, &MainFrame::OnBackButtonClicked, this);
        wxStaticBitmap* browser_panel_logo = new wxStaticBitmap(browser_panel, wxID_ANY, wxBitmap(wxImage(wxBitmap("logo.png", wxBITMAP_TYPE_PNG).ConvertToImage()).Scale(200,200)), wxPoint(150,50), wxSize(200, 200));
        
        browser_panel->SetSizer(browser_box_sizer);
        not_retaining_coll_pane = new wxCollapsiblePane(browser_panel, 203, "New Skills", wxDefaultPosition, wxSize(400, 50));
        not_retaining_win = not_retaining_coll_pane->GetPane();
        not_retaining_sizer = new wxGridSizer(number_of_skills, 2, 0, 0);
        not_retaining_win->SetSizer(not_retaining_sizer);
        not_retaining_sizer->SetSizeHints(not_retaining_win);
        browser_box_sizer->Add(browser_panel_logo, wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
        browser_box_sizer->Add(not_retaining_coll_pane, wxALL, 5);

        // Creates buttons for each skill
        std::string* skill_names = get_skill_names();

        std::cout << skill_names[0] << '\n';

        std::map<int, int> skill_status;
        int current_skill_status;

        for(int i = 0; i < number_of_skills; i++){
               current_skill_status = get_skill_status(i+1); 
               skill_status[i] = current_skill_status;

        }
        bool not_retaining = false;
        for(int i = 0; i < number_of_skills; i++){
                // wx_IDs may not be one or zero, so we use 2i for the skill button and 2i+1 for the stats button
                switch(skill_status[i])
                {
                        case 0:
                                due_coll_pane_height += 35;
                                dueSz->Add(new wxButton(due_win, 2*(i+1), skill_names[i] , wxPoint(150, due_coll_pane_height - 200), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                dueSz->Add(new wxButton(due_win, 2*(i+1) + 1, "Stats", wxPoint(150, due_coll_pane_height - 200), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                due_win->Fit();
                                due_coll_pane->SetMinSize(wxSize(400,due_coll_pane_height));
                                dueSz->Layout();
                                break;
                        case 1:
                                std::cout << "Adding to learnt win\n";
                                learnt_coll_pane_height += 35;
                                learntSz->Add(new wxButton(learnt_win, 2*(i+1), skill_names[i] , wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                learntSz->Add(new wxButton(learnt_win, 2*(i+1) + 1, "Stats", wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                break;
                        case 2:
                                if(get_skill_retaining(i+1) == "TRUE"){
                                        unlearnt_coll_pane_height += 35;
                                        unlearntSz->Add(new wxButton(unlearnt_win, 2*(i+1), skill_names[i] , wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                        unlearntSz->Add(new wxButton(unlearnt_win, 2*(i+1) + 1, "Stats", wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                        break;
                                } else{
                                        not_retaining_sizer->Add(new wxButton(not_retaining_win, 2*(i+1), skill_names[i] , wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                        not_retaining_sizer->Add(new wxButton(not_retaining_win, 2*(i+1) + 1, "Add Skill", wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                        Connect(2*(i+1), wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnSkillButtonClicked));
                                        Connect(2*(i+1) + 1, wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnAddSkillButtonClicked));
                                        not_retaining = true;
                                        break;
                                }
                        default:
                                throw std::invalid_argument("Invalid skill status");
                }
                if(not_retaining == false){
                        Connect(2*(i+1), wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnSkillButtonClicked));
                        Connect(2*(i+1) + 1, wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnStatsButtonClicked));
                }
                not_retaining = false;
        }
        due_coll_pane->Expand();


        main_book->AddPage(main_panel, "Welcome");

        wxPanel* skill_panel = new wxPanel(main_book, wxID_ANY);
        wxButton* back_button = new wxButton(skill_panel, wxID_ANY, "Back", wxPoint(150,50), wxSize(100,35));
        textEntry = new wxTextCtrl(skill_panel, wxID_ANY, "", wxPoint(150,50), wxSize(400,35), wxTE_PROCESS_ENTER);
        back_button->Bind(wxEVT_BUTTON, &MainFrame::OnBackButtonClicked, this);
        textEntry->Bind(wxEVT_TEXT, &MainFrame::OnTextChanged, this);
        textEntry->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnTextEntered, this);
        
        //image stuff
        image = new wxStaticBitmap(skill_panel, wxID_ANY, wxBitmap("problem.png", wxBITMAP_TYPE_PNG), wxPoint(150,50), wxSize(400, 100), wxCENTER);
        boxSizer->Add(back_button, 0, wxCENTER | wxALL, 10);
        boxSizer->Add(image, 0, wxCENTER | wxALL, 10);
        boxSizer->Add(textEntry, 0, wxCENTER | wxALL, 10);
        skill_panel->SetSizer(boxSizer);
        main_book->AddPage(skill_panel, "Practice");
        main_book->AddPage(browser_panel, "New Skills");
}

void MainFrame::UpdateMainPanel(){

        int number_of_skills = get_number_of_skills();
        due_win->DestroyChildren();
        learnt_win->DestroyChildren();
        unlearnt_win->DestroyChildren();
        not_retaining_win->DestroyChildren();
        
        // Creates buttons for each skill
        std::string* skill_names = get_skill_names();

        std::cout << skill_names[0] << '\n';

        std::map<int, int> skill_status;
        int current_skill_status;

        for(int i = 0; i < number_of_skills; i++){
               current_skill_status = get_skill_status(i+1); 
               skill_status[i] = current_skill_status;

        }
        bool not_retaining = false;
        for(int i = 0; i < number_of_skills; i++){
                // wx_IDs may not be one or zero, so we use 2i for the skill button and 2i+1 for the stats button
                switch(skill_status[i])
                {
                        case 0:
                                due_coll_pane_height += 35;
                                dueSz->Add(new wxButton(due_win, 2*(i+1), skill_names[i] , wxPoint(150, due_coll_pane_height - 200), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                dueSz->Add(new wxButton(due_win, 2*(i+1) + 1, "Stats", wxPoint(150, due_coll_pane_height - 200), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                due_win->Fit();
                                due_coll_pane->SetMinSize(wxSize(400,due_coll_pane_height));
                                dueSz->Layout();
                                break;
                        case 1:
                                std::cout << "Adding to learnt win\n";
                                learnt_coll_pane_height += 35;
                                learntSz->Add(new wxButton(learnt_win, 2*(i+1), skill_names[i] , wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                learntSz->Add(new wxButton(learnt_win, 2*(i+1) + 1, "Stats", wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                break;
                        case 2:
                                if(get_skill_retaining(i+1) == "TRUE"){
                                        unlearnt_coll_pane_height += 35;
                                        unlearntSz->Add(new wxButton(unlearnt_win, 2*(i+1), skill_names[i] , wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                        unlearntSz->Add(new wxButton(unlearnt_win, 2*(i+1) + 1, "Stats", wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                        break;
                                } else{
                                        not_retaining_sizer->Add(new wxButton(not_retaining_win, 2*(i+1), skill_names[i] , wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                        not_retaining_sizer->Add(new wxButton(not_retaining_win, 2*(i+1) + 1, "Add Skill", wxPoint(150,50), wxSize(200,35)), wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
                                        Connect(2*(i+1), wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnSkillButtonClicked));
                                        Connect(2*(i+1) + 1, wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnAddSkillButtonClicked));
                                        not_retaining = true;
                                        break;
                                }
                        default:
                                throw std::invalid_argument("Invalid skill status");
                }
                if(not_retaining == false){
                        Connect(2*(i+1), wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnSkillButtonClicked));
                        Connect(2*(i+1) + 1, wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnStatsButtonClicked));
                }
                not_retaining = false;
        }
        not_retaining_sizer->Layout();
}

void MainFrame::OnCollapsiblePaneClicked(wxCollapsiblePaneEvent& evt) {
                
                main_sizer->Layout();
                int adjusted_pane_id = evt.GetId();
                int adjusted_pane_height;
                wxCollapsiblePane* adjusted_pane; 

                switch(adjusted_pane_id){
                        case 200:
                                adjusted_pane = due_coll_pane;
                                adjusted_pane_height = due_coll_pane_height;
                                break;
                        case 201:
                                adjusted_pane = learnt_coll_pane;
                                adjusted_pane_height = learnt_coll_pane_height;
                                break;
                        case 202:
                                adjusted_pane = unlearnt_coll_pane;
                                adjusted_pane_height = unlearnt_coll_pane_height;
                                break;
                        case 203:
                                adjusted_pane = not_retaining_coll_pane;
                }

                // std::cout << std::to_string(adjusted_pane_height) + "\n";

                if(adjusted_pane->IsCollapsed() == true){
                        adjusted_pane->SetMinSize(wxSize(400, 50));
                } else{
                        adjusted_pane->SetMinSize(wxSize(400, due_coll_pane_height));
                }
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
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        image->SetBitmap(wxBitmap("problem.png", wxBITMAP_TYPE_PNG));
        solution = problem_and_solution[1];
        current_skill_id = skillID;
        main_book->SetSelection(1);

}

void MainFrame::OnBrowserButtonClicked(wxCommandEvent& evt) {
        main_book->SetSelection(2);
        textEntry->Clear();
}

void MainFrame::OnStatsButtonClicked(wxCommandEvent& evt) {
        // skillIDs start at 1 and button ids start at 2, so we subtract 1
        int skillID = ((evt.GetId()-1)/2);
        std::string stats = get_skill_info(skillID);
        std::string skill_name = get_skill_name(skillID);

        wxMessageBox(stats, skill_name + " Stats");
}

void MainFrame::OnAddSkillButtonClicked(wxCommandEvent& evt) {
        // skillIDs start at 1 and button ids start at 2, so we subtract 1
        int skillID = ((evt.GetId()-1)/2);
        update_skill_value(skillID, "RETAINING", "TRUE");

        wxMessageBox("Skill Added!");
        wxWindow* skill_ctrl = wxWindow::FindWindowById(evt.GetId()-1, this);
        wxWindow* add_ctrl = wxWindow::FindWindowById(evt.GetId(), this);
        skill_ctrl->Destroy();
        add_ctrl->Destroy();
        browser_box_sizer->Layout(); 
        MainFrame::UpdateMainPanel();
        main_sizer->Layout();

}



void MainFrame::OnTextChanged(wxCommandEvent& evt) {
        wxString str = wxString::Format("Text: %s", evt.GetString());
}

void MainFrame::OnTextEntered(wxCommandEvent& evt) {
        if(evt.GetString() == solution){
                wxMessageBox(wxT("The solution was " + solution), "Correct!");
                update_fsrs_on_answer(current_skill_id, 3);
                textEntry->Clear();
        } else{
                wxMessageBox(wxT("The solution was " + solution), "Incorrect!");
                update_fsrs_on_answer(current_skill_id, 1);
                textEntry->Clear();
        }
        MainFrame::UpdateMainPanel();
}

void MainFrame::OnBackButtonClicked(wxCommandEvent& evt) {
        main_book->SetSelection(0);
        textEntry->Clear();
}
